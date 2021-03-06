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
#include "dogen/yarn/test_data/mapping_set_td.hpp"
#include "dogen/yarn/test_data/mapping_set_repository_td.hpp"

namespace {

dogen::yarn::mapping_set
create_dogen_yarn_mapping_set(const unsigned int position) {
    return dogen::yarn::mapping_set_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, dogen::yarn::mapping_set> create_std_unordered_map_std_string_dogen_yarn_mapping_set(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::mapping_set> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_mapping_set(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

mapping_set_repository_generator::mapping_set_repository_generator() : position_(0) { }

void mapping_set_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.default_mapping_set(create_dogen_yarn_mapping_set(position + 0));
    v.by_name(create_std_unordered_map_std_string_dogen_yarn_mapping_set(position + 1));
}

mapping_set_repository_generator::result_type
mapping_set_repository_generator::create(const unsigned int position) {
    mapping_set_repository r;
    mapping_set_repository_generator::populate(position, r);
    return r;
}

mapping_set_repository_generator::result_type*
mapping_set_repository_generator::create_ptr(const unsigned int position) {
    mapping_set_repository* p = new mapping_set_repository();
    mapping_set_repository_generator::populate(position, *p);
    return p;
}

mapping_set_repository_generator::result_type
mapping_set_repository_generator::operator()() {
    return create(position_++);
}

} }
