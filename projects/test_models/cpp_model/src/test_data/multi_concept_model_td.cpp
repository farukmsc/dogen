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
#include <sstream>
#include "dogen/test_models/cpp_model/test_data/multi_concept_model_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

multi_concept_model_generator::multi_concept_model_generator() : position_(0) { }

void multi_concept_model_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_1(create_int(position + 0));
    v.prop_0(create_std_string(position + 1));
    v.prop_2(create_int(position + 2));
    v.prop_10(create_int(position + 3));
}

multi_concept_model_generator::result_type
multi_concept_model_generator::create(const unsigned int position) {
    multi_concept_model r;
    multi_concept_model_generator::populate(position, r);
    return r;
}

multi_concept_model_generator::result_type*
multi_concept_model_generator::create_ptr(const unsigned int position) {
    multi_concept_model* p = new multi_concept_model();
    multi_concept_model_generator::populate(position, *p);
    return p;
}

multi_concept_model_generator::result_type
multi_concept_model_generator::operator()() {
    return create(position_++);
}

} } }
