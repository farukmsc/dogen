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
#ifndef DOGEN_YARN_TYPES_MODEL_VALIDATOR_HPP
#define DOGEN_YARN_TYPES_MODEL_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/languages.hpp"

namespace dogen {
namespace yarn {

class model_validator final {
private:
    bool allow_spaces_in_built_in_types(const languages l) const;
    void sanity_check_string(const std::string& s,
        bool check_not_builtin = true) const;
    void sanity_check_strings(const std::list<std::string>& strings) const;
    std::list<name> decompose_model_into_element_names(const model& m) const;
    void sanity_check_name(const name& n,
        const bool allow_spaces_in_built_in_types) const;
    void sanity_check_all_names(const model& m) const;

public:
    void validate(const model& m) const;
};

} }

#endif
