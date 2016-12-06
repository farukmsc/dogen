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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/yarn.json/types/dehydrator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.json.dehydrator"));

const std::string scope("::");
const std::string comma_space(", ");

}

using boost::algorithm::join;

namespace dogen {
namespace yarn {
namespace json {

std::string dehydrator::tidy_up_string(std::string s) const {
    boost::replace_all(s, "\r", "\\r");
    boost::replace_all(s, "\n", "\\n");
    boost::replace_all(s, "\"", "\\\"");
    return s;
}

bool dehydrator::has_elements(const intermediate_model& im) const {
    return
        !im.objects().empty() ||
        !im.primitives().empty() ||
        !im.enumerations().empty() ||
        !im.modules().empty();
}

void dehydrator::dehydrate_name(const name& n, std::ostream& s) const {
    formatters::utility_formatter uf(s);
    s << " { ";
    uf.insert_quoted("simple_name");
    s << " : ";
    uf.insert_quoted(n.simple());

    const auto& l(n.location());
    if (!l.internal_modules().empty()) {
        s << comma_space;
        uf.insert_quoted("internal_modules");
        s << " : ";
        uf.insert_quoted(join(l.internal_modules(), scope));
    }
    s << " } ";
}

void dehydrator::dehydrate_annotations(const intermediate_model& im,
    const std::string& id, std::ostream& s) const {

    formatters::utility_formatter uf(s);
    bool has_annotations(false);
    const auto& scribble_groups(im.indices().scribble_groups());
    const auto i(scribble_groups.find(id));
    if (i == scribble_groups.end())
        return;

    bool is_first(true);
    const auto scribble(i->second.parent());
    has_annotations = !scribble.entries().empty();
    if (!has_annotations)
        return;

    s << comma_space;
    uf.insert_quoted("annotation");
    s << " : {";

    for (const auto& entry : scribble.entries()) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(entry.first);
        s << " : ";
        uf.insert_quoted(entry.second);
        is_first = false;
    }
    s << " }";
}

void dehydrator::dehydrate_element(const intermediate_model& im,
    const element& e, const std::string& meta_type, std::ostream& s) const {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    dehydrate_name(e.name(), s);
    s << comma_space;

    uf.insert_quoted("meta_type");
    s << ": ";
    uf.insert_quoted(meta_type);

    if (!e.documentation().empty()) {
        s << comma_space;
        uf.insert_quoted("documentation");
        s << " : ";
        uf.insert_quoted(tidy_up_string(e.documentation()));
    }

    if (!e.stereotypes().empty()) {
        s << comma_space;
        uf.insert_quoted("stereotypes");
        s << " : [ ";
        bool is_first(true);
        for (const auto& stereotype : e.stereotypes()) {
            if (!is_first)
                s << comma_space;

            uf.insert_quoted(stereotype);

            is_first = false;
        }
        s << " ] ";
    }

    dehydrate_annotations(im, e.name().id(), s);
}

void dehydrator::dehydrate_attributes(const std::list<attribute>& attrs,
    std::ostream& s) const {
    formatters::utility_formatter uf(s);
    uf.insert_quoted("attributes");
    s << ": [";

    bool is_first(true);
    for(const auto& a : attrs) {
        if (!is_first)
            s << comma_space;

        s << " { ";
        uf.insert_quoted("simple_name");
        s << " : ";
        uf.insert_quoted(a.name().simple());

        s << comma_space;

        uf.insert_quoted("type");
        s << " : ";
        uf.insert_quoted(a.unparsed_type());

        if (!a.documentation().empty()) {
            s << comma_space;
            uf.insert_quoted("documentation");
            s << " : ";
            uf.insert_quoted(tidy_up_string(a.documentation()));
        }

        s << " }";
        is_first = false;
    }
    s << " ]";
}

void dehydrator::
dehydrate_objects(const intermediate_model& im, std::ostream& s) const {

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool is_first(true);

    const auto objects(to_map(im.objects()));
    for (const auto& pair : objects) {
        if (!is_first)
            s << comma_space;

        const auto& o(pair.second);
        s << " { ";
        dehydrate_element(im, o, "object", s);

        if (o.parent()) {
            s << comma_space;
            uf.insert_quoted("parent");
            s << " : ";
            dehydrate_name(*o.parent(), s);
        }

        if (!o.local_attributes().empty()) {
            s << comma_space;
            dehydrate_attributes(o.local_attributes(), s);
        }
        s << " }";
        is_first = false;
    }
}

void dehydrator::
dehydrate_concepts(const intermediate_model& im, std::ostream& s) const {

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(!im.objects().empty());

    const auto concepts(to_map(im.concepts()));
    for (const auto& pair : concepts) {
        if (output_comma)
            s << comma_space;

        const auto& c(pair.second);
        s << " { ";
        dehydrate_element(im, c, "concept", s);

        if (!c.refines().empty()) {
            s << comma_space;
            uf.insert_quoted("refines");
            s << " : [ ";
            bool is_first(true);
            for (const auto& n : c.refines()) {
                if (!is_first)
                    s << comma_space;

                dehydrate_name(n, s);
                is_first = false;
            }
            s << " ] ";
        }

        if (!c.local_attributes().empty()) {
            s << comma_space;
            dehydrate_attributes(c.local_attributes(), s);
        }
        s << " }";
        output_comma = true;
    }
}

void dehydrator::
dehydrate_modules(const intermediate_model& im, std::ostream& s) const {
    /*
     * Remove the root module.
     */
    auto modules(to_map(im.modules()));
    const auto i(modules.find(im.name().id()));
    if (i != modules.end())
        modules.erase(i);

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(!im.objects().empty() || !im.concepts().empty());
    for (const auto& pair : modules) {
        if (output_comma)
            s << comma_space;

        const auto& o(pair.second);
        s << " { ";
        dehydrate_element(im, o, "module", s);
        s << " }";
        output_comma = true;
    }
}

void dehydrator::
dehydrate_enumerations(const intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(!im.objects().empty() || !im.concepts().empty() ||
        im.modules().empty());
    const auto enumerations(to_map(im.enumerations()));
    for (const auto& pair : enumerations) {
        if (output_comma)
            s << comma_space;

        const auto& o(pair.second);
        s << " { ";
        dehydrate_element(im, o, "enumeration", s);
        s << comma_space;

        /*
         * Remove invalid from enumerators.
         */
        std::vector<enumerator> enumerators;
        enumerators.reserve(o.enumerators().size());
        for (const auto& en : o.enumerators()) {
            if (en.name() != "invalid")
                enumerators.push_back(en);
        }

        uf.insert_quoted("enumerators");
        s << ": [";

        bool is_first(true);
        for(const auto& en : enumerators) {
            if (!is_first)
                s << comma_space;

            s << " { ";
            uf.insert_quoted("simple_name");
            s << " : ";
            uf.insert_quoted(en.name());

            if (!en.documentation().empty()) {
                s << comma_space;
                uf.insert_quoted("documentation");
                s << " : ";
                uf.insert_quoted(tidy_up_string(en.documentation()));
            }

            s << " }";
            is_first = false;
        }
        s << " ]";

        s << " }";
        output_comma = true;
    }
}

void dehydrator::
dehydrate_exceptions(const intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);

    bool output_comma(!im.objects().empty() || !im.concepts().empty() ||
        im.modules().empty() || im.modules().empty() ||
        im.enumerations().empty());
    const auto exceptions(to_map(im.exceptions()));
    for (const auto& pair : exceptions) {
        if (output_comma)
            s << comma_space;

        const auto& o(pair.second);
        s << " { ";
        dehydrate_element(im, o, "exception", s);
        s << " }";
        output_comma = true;
    }
}

std::string dehydrator::dehydrate(const intermediate_model& im) const {
    std::ostringstream s;
    formatters::utility_formatter uf(s);
    using boost::algorithm::join;

    const auto& l(im.name().location());
    s << "{ ";
    uf.insert_quoted("model_name");
    s << " : ";
    uf.insert_quoted(join(l.model_modules(), scope));
    s << comma_space;

    uf.insert_quoted("external_modules");
    s << " : ";
    uf.insert_quoted(join(l.external_modules(), scope));

    const auto i(im.modules().find(im.name().id()));
    if (i != im.modules().end()) {
        const auto& root_module(i->second);
        if (!root_module.documentation().empty()) {
            s << comma_space;
            uf.insert_quoted("documentation");
            s << " : ";
            uf.insert_quoted(tidy_up_string(root_module.documentation()));
        }
    }

    dehydrate_annotations(im, im.name().id(), s);

    if (has_elements(im)) {
        s << comma_space;
        uf.insert_quoted("elements");
        s << ": [";
        dehydrate_objects(im, s);
        dehydrate_concepts(im, s);
        dehydrate_modules(im, s);
        dehydrate_enumerations(im, s);
        dehydrate_exceptions(im, s);
        s << " ]";
    }

    s << " }";

    return s.str();
}

void dehydrator::dehydrate(const intermediate_model& im,
    const boost::filesystem::path& p) const {

    const auto s(dehydrate(im));
    utility::filesystem::write_file_content(p, s);
}

} } }