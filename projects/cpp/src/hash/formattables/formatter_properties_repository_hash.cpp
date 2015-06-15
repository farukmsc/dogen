/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/cpp/hash/formattables/formatter_properties_hash.hpp"
#include "dogen/cpp/hash/formattables/formatter_properties_repository_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_dogen_cpp_formattables_formatter_properties(const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_std_unordered_map_std_string_dogen_cpp_formattables_formatter_properties_(const std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_unordered_map_std_string_dogen_cpp_formattables_formatter_properties(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

std::size_t formatter_properties_repository_hasher::hash(const formatter_properties_repository& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_dogen_sml_qname_std_unordered_map_std_string_dogen_cpp_formattables_formatter_properties_(v.formatter_properties_by_qname()));
    return seed;
}

} } }
