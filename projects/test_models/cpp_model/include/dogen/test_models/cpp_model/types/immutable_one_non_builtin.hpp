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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_ONE_NON_BUILTIN_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_ONE_NON_BUILTIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/immutable_one_non_builtin_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Immutable class with one pod property
 */
class immutable_one_non_builtin final {
public:
    immutable_one_non_builtin() = default;
    immutable_one_non_builtin(const immutable_one_non_builtin&) = default;
    immutable_one_non_builtin(immutable_one_non_builtin&&) = default;
    ~immutable_one_non_builtin() = default;
    immutable_one_non_builtin& operator=(const immutable_one_non_builtin&) = delete;

public:
    explicit immutable_one_non_builtin(const std::string& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::immutable_one_non_builtin& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::immutable_one_non_builtin& v, unsigned int version);

public:
    const std::string& prop_0() const;

public:
    bool operator==(const immutable_one_non_builtin& rhs) const;
    bool operator!=(const immutable_one_non_builtin& rhs) const {
        return !this->operator==(rhs);
    }

private:
    std::string prop_0_;
};

} } }

#endif
