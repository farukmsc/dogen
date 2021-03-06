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
#ifndef DOGEN_UPSILON_TYPES_TAG_HPP
#define DOGEN_UPSILON_TYPES_TAG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/upsilon/serialization/tag_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class tag final {
public:
    tag() = default;
    tag(const tag&) = default;
    tag(tag&&) = default;
    ~tag() = default;

public:
    tag(
        const std::string& name,
        const std::string& comment);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::tag& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::tag& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& comment() const;
    std::string& comment();
    void comment(const std::string& v);
    void comment(const std::string&& v);

public:
    bool operator==(const tag& rhs) const;
    bool operator!=(const tag& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(tag& other) noexcept;
    tag& operator=(tag other);

private:
    std::string name_;
    std::string comment_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::tag& lhs,
    dogen::upsilon::tag& rhs) {
    lhs.swap(rhs);
}

}

#endif
