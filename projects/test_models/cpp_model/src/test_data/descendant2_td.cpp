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
#include "dogen/test_models/cpp_model/test_data/base_td.hpp"
#include "dogen/test_models/cpp_model/test_data/descendant2_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

descendant2_generator::descendant2_generator() : position_(0) { }

void descendant2_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::cpp_model::base_generator::populate(position, v);
    v.prop_0(create_bool(position + 0));
}

descendant2_generator::result_type
descendant2_generator::create(const unsigned int position) {
    descendant2 r;
    descendant2_generator::populate(position, r);
    return r;
}

descendant2_generator::result_type*
descendant2_generator::create_ptr(const unsigned int position) {
    descendant2* p = new descendant2();
    descendant2_generator::populate(position, *p);
    return p;
}

descendant2_generator::result_type
descendant2_generator::operator()() {
    return create(position_++);
}

} } }
