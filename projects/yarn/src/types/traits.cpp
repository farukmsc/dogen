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
#include "dogen/yarn/types/traits.hpp"

namespace dogen {
namespace yarn {

std::string traits::input_language() {
    static std::string r("yarn.input_language");
    return r;
}

std::string traits::output_language() {
    static std::string r("yarn.output_language");
    return r;
}

std::string traits::is_proxy_model() {
    static std::string r("yarn.is_proxy_model");
    return r;
}

std::string traits::reference() {
    static std::string r("yarn.reference");
    return r;
}

std::string traits::type_parameters::variable_number_of_parameters() {
    static std::string r("yarn.type_parameters.variable_number_of_parameters");
    return r;
}

std::string traits::type_parameters::type_parameters_count() {
    static std::string r("yarn.type_parameters.count");
    return r;
}

std::string traits::type_parameters::type_parameters_always_in_heap() {
    static std::string r("yarn.type_parameters.always_in_heap");
    return r;
}

std::string traits::generalization::is_final() {
    static std::string r("yarn.generalization.is_final");
    return r;
}

std::string traits::generalization::parent() {
    static std::string r("yarn.generalization.parent");
    return r;
}

std::string traits::enumeration::
use_implementation_defined_underlying_element() {
    static std::string r(
        "yarn.enumeration.use_implementation_defined_underlying_element");
    return r;
}

std::string traits::enumeration::underlying_element() {
    static std::string r("yarn.enumeration.underlying_element");
    return r;
}

std::string traits::enumeration::
use_implementation_defined_enumerator_values() {
    static std::string r(
        "yarn.enumeration.use_implementation_defined_enumerator_values");
    return r;
}

std::string traits::enumeration::add_invalid_enumerator() {
    static std::string r("yarn.enumeration.add_invalid_enumerator");
    return r;
}

std::string traits::enumerator::value() {
    static std::string r("yarn.enumerator.value");
    return r;
}

std::string traits::primitive::underlying_element() {
    static std::string r("yarn.primitive.underlying_element");
    return r;
}

std::string traits::primitive::is_nullable() {
    static std::string r("yarn.primitive.is_nullable");
    return r;
}

std::string traits::primitive::use_type_aliasing() {
    static std::string r("yarn.primitive.use_type_aliasing");
    return r;
}

std::string traits::orm::database_system() {
    static std::string r("yarn.orm.database_system");
    return r;
}

std::string traits::orm::table_name() {
    static std::string r("yarn.orm.table_name");
    return r;
}

std::string traits::orm::schema_name() {
    static std::string r("yarn.orm.schema_name");
    return r;
}

std::string traits::orm::is_primary_key() {
    static std::string r("yarn.orm.is_primary_key");
    return r;
}

std::string traits::orm::column_name() {
    static std::string r("yarn.orm.column_name");
    return r;
}

std::string traits::orm::is_nullable() {
    static std::string r("yarn.orm.is_nullable");
    return r;
}

std::string traits::orm::letter_case() {
    static std::string r("yarn.orm.letter_case");
    return r;
}

std::string traits::orm::type_override() {
    static std::string r("yarn.orm.type_override");
    return r;
}

std::string traits::orm::is_composite() {
    static std::string r("yarn.orm.is_composite");
    return r;
}

} }
