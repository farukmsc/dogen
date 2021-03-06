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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/yarn/test_data/enumerator_td.hpp"
#include "dogen/yarn/test_data/enumeration_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

dogen::yarn::enumerator
create_dogen_yarn_enumerator(const unsigned int position) {
    return dogen::yarn::enumerator_generator::create(position);
}

std::vector<dogen::yarn::enumerator> create_std_vector_dogen_yarn_enumerator(unsigned int position) {
    std::vector<dogen::yarn::enumerator> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_enumerator(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen {
namespace yarn {

enumeration_generator::enumeration_generator() : position_(0) { }

void enumeration_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::element_generator::populate(position, v);
    v.underlying_element(create_dogen_yarn_name(position + 0));
    v.enumerators(create_std_vector_dogen_yarn_enumerator(position + 1));
    v.use_implementation_defined_underlying_element(create_bool(position + 2));
    v.use_implementation_defined_enumerator_values(create_bool(position + 3));
    v.add_invalid_enumerator(create_bool(position + 4));
}

enumeration_generator::result_type
enumeration_generator::create(const unsigned int position) {
    enumeration r;
    enumeration_generator::populate(position, r);
    return r;
}

enumeration_generator::result_type*
enumeration_generator::create_ptr(const unsigned int position) {
    enumeration* p = new enumeration();
    enumeration_generator::populate(position, *p);
    return p;
}

enumeration_generator::result_type
enumeration_generator::operator()() {
    return create(position_++);
}

} }
