/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/io/formattables/inclusion_directives_repository_io.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_directives_repository_factory"));

const std::string duplicate_qname("Duplicate qname: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all inclusion directives.
 */
class generator {
public:
    generator(const dynamic::repository& srp,
        const formatters::container& fc,
        const path_derivatives_repository& pdrp) : factory_(srp, fc, pdrp) { }

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename ExtensibleAndNameable>
    void generate(const ExtensibleAndNameable& e) {
        const auto id(factory_.make(e.extensions(), e.name()));
        if (!id)
            return;

        auto& id_qn(result_.inclusion_directives_by_qname());
        const auto pair(id_qn.insert(std::make_pair(e.name(), *id)));
        if (pair.second)
            return;

        const auto n(sml::string_converter::convert(e.name()));
        BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
        BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
    }

public:
    void operator()(const dogen::sml::object& o) { generate(o); }
    void operator()(const dogen::sml::enumeration& e) { generate(e); }
    void operator()(const dogen::sml::primitive& p) { generate(p); }
    void operator()(const dogen::sml::module& m) { generate(m); }
    void operator()(const dogen::sml::concept& c) { generate(c); }

public:
    const inclusion_directives_repository& result() const { return result_; }

private:
    const inclusion_directives_factory factory_;
    inclusion_directives_repository result_;
};

}

inclusion_directives_repository inclusion_directives_repository_factory::make(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making inclusion directives repository.";

    generator g(srp, fc, pdrp);
    sml::all_model_items_traversal(m, g);
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } }
