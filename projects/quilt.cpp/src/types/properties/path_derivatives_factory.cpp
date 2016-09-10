/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <unordered_set>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/io/formatters/file_types_io.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.path_derivatives_factory"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");
const std::string unsupported_file_type("File type not supported: ");

const std::string missing_path_settings(
    "Could not find any path settings for formatter: ");
const std::string empty_formatter_name("Empty formatter name was supplied.");
}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class module_id_collector : public yarn::element_visitor {
public:
    const std::unordered_set<std::string>& result() { return module_ids_; }

public:
    using yarn::element_visitor::visit;
    void visit(const yarn::module& m) override {
        module_ids_.insert(m.name().id());
    }

private:
    std::unordered_set<std::string> module_ids_;
};

path_derivatives_factory::path_derivatives_factory(
    const config::cpp_options& opts, const yarn::model& m,
    const std::unordered_map<std::string, settings::path_settings>& ps)
    : options_(opts), model_(m), path_settings_(ps),
      module_ids_(module_ids(m)) { }

std::unordered_set<std::string> path_derivatives_factory::
module_ids(const yarn::model& m) const {
    module_id_collector c;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(c);
    }
    return c.result();
}

boost::filesystem::path path_derivatives_factory::
make_inclusion_path(const settings::path_settings& ps,
    const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making inclusion path for: " << n.id();

    boost::filesystem::path r;

    /*
     * Header files require both the external module path and the
     * model module path in the file name path.
     */
    if (ps.file_type() == formatters::file_types::cpp_header) {
        for (const auto& m : n.location().external_modules())
            r /= m;

        const auto& mmp(n.location().model_modules());
        r /= boost::algorithm::join(mmp, dot);
    }

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    if (!ps.facet_directory().empty() && !ps.disable_facet_directories())
        r /= ps.facet_directory();

    /*
     * Add the module path of the modules internal to this model.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_.name()) {
        const auto i(module_ids_.find(n.id()));
        if (i != module_ids_.end())
            r /= n.simple();
    }

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << n.simple();

    if (!ps.formatter_postfix().empty())
        stream << underscore << ps.formatter_postfix();

    if (!ps.facet_postfix().empty())
        stream << underscore << ps.facet_postfix();

    if (ps.file_type() == formatters::file_types::cpp_header)
        stream << dot << ps.header_file_extension();
    else if (ps.file_type() == formatters::file_types::cpp_implementation)
        stream << dot << ps.implementation_file_extension();

    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the inclusion path. Result: " << r;
    return r;
}

boost::filesystem::path path_derivatives_factory::
make_file_path(const settings::path_settings& ps,
    const boost::filesystem::path& inclusion_path,
    const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file path for: " << n.id();

    boost::filesystem::path r;

    const auto ft(ps.file_type());
    const auto& mmp(n.location().model_modules());
    switch (ft) {
    case formatters::file_types::cpp_header:
        r = options_.project_directory_path();
        r /= boost::algorithm::join(mmp, dot);
        r /= ps.include_directory_name();
        break;

    case formatters::file_types::cpp_implementation:
        r = options_.project_directory_path();
        r /= boost::algorithm::join(mmp, dot);
        r /= ps.source_directory_name();
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_file_type << ft;
        BOOST_THROW_EXCEPTION(building_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= inclusion_path;

    BOOST_LOG_SEV(lg, debug) << "Done creating file path. Result: " << r;
    return r;
}

std::string path_derivatives_factory::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

std::string path_derivatives_factory::
to_header_guard_name(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}

std::unordered_map<std::string, path_derivatives>
path_derivatives_factory::make(const yarn::name& n) const {
    std::unordered_map<std::string, path_derivatives> r;

    for (const auto& pair : path_settings_) {
        if (pair.first.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        const auto& s(pair.second);
        const auto inclusion_path(make_inclusion_path(s, n));

        path_derivatives pd;
        const auto file_path(make_file_path(s, inclusion_path, n));
        pd.file_path(file_path);

        if (s.file_type() == formatters::file_types::cpp_header) {
            pd.inclusion_directive(to_inclusion_directive(inclusion_path));
            pd.header_guard(to_header_guard_name(inclusion_path));
        }

        r[pair.first] = pd;
    }
    return r;
}

} } } }
