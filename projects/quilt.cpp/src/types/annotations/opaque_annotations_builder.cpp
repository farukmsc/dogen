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
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_builder.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_factory_interface.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.annotations.opaque_annotations_builder"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

std::shared_ptr<cpp::annotations::registrar>
opaque_annotations_builder::registrar_;

cpp::annotations::registrar& opaque_annotations_builder::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::annotations::registrar>();

    return *registrar_;
}

void opaque_annotations_builder::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating workflow.";

    registrar().validate();
    const auto& factories(registrar().opaque_annotations_factories());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(factories.begin(),
                                 factories.end())
                             << " registered opaque annotations factories(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all opaque annotations factories.";
    for (const auto& f : factories)
        BOOST_LOG_SEV(lg, debug) << "Key: '" << f->annotations_key() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating workflow.";
}

void opaque_annotations_builder::setup(const dynamic::repository& rp) {
    BOOST_LOG_SEV(lg, debug) << "Setting up all opaque annotations factories.";
    const auto& factories(registrar().opaque_annotations_factories());
    for (auto f : factories)
        f->setup(rp);
}

std::unordered_map<std::string, boost::shared_ptr<opaque_annotations>>
opaque_annotations_builder::build(const dynamic::object& o) const {

    std::unordered_map<std::string, boost::shared_ptr<opaque_annotations> > r;
    for (const auto f : registrar().opaque_annotations_factories()) {
        auto os(f->make(o));
        if (os)
            r[f->annotations_key()] = os;
    }
    return r;
}

} } } }