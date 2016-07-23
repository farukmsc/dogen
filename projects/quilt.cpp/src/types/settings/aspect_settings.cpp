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
#include "dogen/quilt.cpp/types/settings/aspect_settings.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

aspect_settings::aspect_settings()
    : disable_complete_constructor_(static_cast<bool>(0)),
      disable_xml_serialization_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)) { }

aspect_settings::aspect_settings(
    const bool disable_complete_constructor,
    const bool disable_xml_serialization,
    const bool requires_manual_default_constructor,
    const bool requires_manual_move_constructor,
    const bool requires_stream_manipulators)
    : disable_complete_constructor_(disable_complete_constructor),
      disable_xml_serialization_(disable_xml_serialization),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_stream_manipulators_(requires_stream_manipulators) { }

void aspect_settings::swap(aspect_settings& other) noexcept {
    using std::swap;
    swap(disable_complete_constructor_, other.disable_complete_constructor_);
    swap(disable_xml_serialization_, other.disable_xml_serialization_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
}

bool aspect_settings::operator==(const aspect_settings& rhs) const {
    return disable_complete_constructor_ == rhs.disable_complete_constructor_ &&
        disable_xml_serialization_ == rhs.disable_xml_serialization_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_;
}

aspect_settings& aspect_settings::operator=(aspect_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool aspect_settings::disable_complete_constructor() const {
    return disable_complete_constructor_;
}

void aspect_settings::disable_complete_constructor(const bool v) {
    disable_complete_constructor_ = v;
}

bool aspect_settings::disable_xml_serialization() const {
    return disable_xml_serialization_;
}

void aspect_settings::disable_xml_serialization(const bool v) {
    disable_xml_serialization_ = v;
}

bool aspect_settings::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void aspect_settings::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

bool aspect_settings::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void aspect_settings::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool aspect_settings::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void aspect_settings::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

} } } }
