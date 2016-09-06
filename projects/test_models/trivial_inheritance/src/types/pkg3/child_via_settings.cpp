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
#include <ostream>
#include "dogen/test_models/trivial_inheritance/io/pkg2/parent_io.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg3/child_via_settings.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {
namespace pkg3 {

child_via_settings::child_via_settings()
    : prop_1_(static_cast<int>(0)) { }

child_via_settings::child_via_settings(
    const int prop_0,
    const int prop_1)
    : dogen::test_models::trivial_inheritance::pkg2::parent(prop_0),
      prop_1_(prop_1) { }

void child_via_settings::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::trivial_inheritance::pkg3::child_via_settings\"" << ", "
      << "\"__parent_0__\": ";
    parent::to_stream(s);
    s << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void child_via_settings::swap(child_via_settings& other) noexcept {
    parent::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool child_via_settings::equals(const dogen::test_models::trivial_inheritance::pkg2::parent& other) const {
    const child_via_settings* const p(dynamic_cast<const child_via_settings* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool child_via_settings::operator==(const child_via_settings& rhs) const {
    return parent::compare(rhs) &&
        prop_1_ == rhs.prop_1_;
}

child_via_settings& child_via_settings::operator=(child_via_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int child_via_settings::prop_1() const {
    return prop_1_;
}

void child_via_settings::prop_1(const int v) {
    prop_1_ = v;
}

} } } }
