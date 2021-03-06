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
#ifndef DOGEN_FORMATTERS_TYPES_INFIX_CONFIGURATION_HPP
#define DOGEN_FORMATTERS_TYPES_INFIX_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/formatters/serialization/infix_configuration_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Configuration to use for a given infix in sequence formatter.
 */
class infix_configuration final {
public:
    infix_configuration() = default;
    infix_configuration(const infix_configuration&) = default;
    infix_configuration(infix_configuration&&) = default;
    ~infix_configuration() = default;

public:
    infix_configuration(
        const std::string& first,
        const std::string& not_first,
        const std::string& not_last,
        const std::string& last);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::infix_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::infix_configuration& v, unsigned int version);

public:
    /**
     * @brief Applicable only to the first element of a sequence, if the sequence has more
     * than one element.
     */
    /**@{*/
    const std::string& first() const;
    std::string& first();
    infix_configuration& first(const std::string& v);
    infix_configuration& first(const std::string&& v);
    /**@}*/

    /**
     * @brief Applicable to all elements other than the first.
     */
    /**@{*/
    const std::string& not_first() const;
    std::string& not_first();
    infix_configuration& not_first(const std::string& v);
    infix_configuration& not_first(const std::string&& v);
    /**@}*/

    const std::string& not_last() const;
    std::string& not_last();
    infix_configuration& not_last(const std::string& v);
    infix_configuration& not_last(const std::string&& v);

    /**
     * @brief Only applicable to the last element of a sequence.
     */
    /**@{*/
    const std::string& last() const;
    std::string& last();
    infix_configuration& last(const std::string& v);
    infix_configuration& last(const std::string&& v);
    /**@}*/

public:
    bool operator==(const infix_configuration& rhs) const;
    bool operator!=(const infix_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(infix_configuration& other) noexcept;
    infix_configuration& operator=(infix_configuration other);

private:
    std::string first_;
    std::string not_first_;
    std::string not_last_;
    std::string last_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::infix_configuration& lhs,
    dogen::formatters::infix_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
