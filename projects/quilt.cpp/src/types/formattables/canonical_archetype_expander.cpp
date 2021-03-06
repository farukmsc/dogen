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
#include <typeindex>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_support_types.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.canonical_archetype_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void canonical_archetype_expander::expand(const formatters::repository& frp,
    formattables::element_properties& eprops, const yarn::element& e) const {
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << e.name().id();
    const auto cs(formatters::inclusion_support_types::canonical_support);
    const auto& safti(frp.stock_artefact_formatters_by_type_index());

    /*
     * For each element segment, find the corresponding formatters.
     */
    const auto ti(std::type_index(typeid(e)));
    BOOST_LOG_SEV(lg, debug) << "Type index: " << ti.name();

    /*
     * Not all elements have formatters; for example, concepts don't
     * have any at present. If so, skip the element.
     */
    const auto i(safti.find(ti));
    if (i == safti.end()) {
        BOOST_LOG_SEV(lg, debug) << "Element has no formatters.";
        return;
    }

    /*
     * Find the canonical formatter for the element and slot it in,
     * pairing the canonical name against the formatter name.
     */
    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        if (fmt.inclusion_support_type() != cs)
            continue;

        const auto& al(fmt.archetype_location());
        const auto arch(al.archetype());
        const auto fct(al.facet());

        const auto carch(formatters::traits::canonical_archetype(fct));
        eprops.canonical_archetype_to_archetype()[carch] = arch;
        BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << arch;
    }
    BOOST_LOG_SEV(lg, debug) << "Processed element.";
}

void canonical_archetype_expander::
expand(const formatters::repository& frp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expansion.";
    for (auto& pair : fm.formattables()) {
        auto& formattable(pair.second);
        auto& eprops(pair.second.element_properties());
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            expand(frp, eprops, e);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished expansion.";
}

} } } }
