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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/annotations/opaque_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class opaque_annotations {
public:
    opaque_annotations() = default;
    opaque_annotations(const opaque_annotations&) = default;
    opaque_annotations(opaque_annotations&&) = default;
    opaque_annotations& operator=(const opaque_annotations&) = default;

    virtual ~opaque_annotations() noexcept = 0;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::opaque_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::opaque_annotations& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const opaque_annotations& rhs) const;
public:
    virtual bool equals(const opaque_annotations& other) const = 0;

protected:
    void swap(opaque_annotations& other) noexcept;

};

inline opaque_annotations::~opaque_annotations() noexcept { }

inline bool operator==(const opaque_annotations& lhs, const opaque_annotations& rhs) {
    return lhs.equals(rhs);
}

} } } }

#endif