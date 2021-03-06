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
#ifndef DOGEN_YARN_TYPES_PARSING_EXPANDER_HPP
#define DOGEN_YARN_TYPES_PARSING_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Expands all encoded representations that require parsing
 * into their yarn form.
 *
 * As an example, all local attributes have unparsed types - strings
 * following a well defined notation - that need to be parsed into
 * name trees. All such forms of encoding are processed by this
 * expander.
 *
 * It is also responsible for reading all meta-data that requires
 * parsing such as parent names, enumeration underlying types and so
 * forth.
 */
class parsing_expander {
private:
    struct type_group {
        annotations::type parent;
        annotations::type enumeration_underlying_element;
        annotations::type primitive_underlying_element;
    };

    type_group make_type_group(const annotations::type_repository& atrp) const;

    std::string make_parent(const type_group& tg,
        const annotations::annotation& a) const;

    std::string make_enumeration_underlying_element(const type_group& tg,
        const annotations::annotation& a) const;

    std::string make_primitive_underlying_element(const type_group& tg,
        const annotations::annotation& a) const;

private:
    std::string obtain_value_attribute_simple_name(const languages l) const;

private:
    /**
     * @brief Returns all of the top-level modules in the supplied
     * model.
     */
    std::unordered_set<std::string>
    obtain_top_level_modules(const intermediate_model& m) const;

private:
    /**
     * @brief Parses all attributes in the supplied attribute list..
     */
    void parse_attributes(const location& model_location,
        const std::unordered_set<std::string>& top_level_modules,
        const languages language, std::list<attribute>& attrs) const;

    /**
     * @brief Parses parent name in the supplied object.
     */
    void parse_parent(const type_group& tg, const location& model_location,
        const std::unordered_set<std::string>& top_level_modules,
        object& o) const;

    /**
     * @brief Parses the underlying element in the supplied
     * enumeration.
     */
    void parse_underlying_element(const type_group& tg,
        const location& model_location,
        const std::unordered_set<std::string>& top_level_modules,
        enumeration& e) const;

    /**
     * @brief Parses underlying element in the supplied primitive.
     */
    void parse_underlying_element(const type_group& tg,
        const location& model_location, const languages l,
        const std::unordered_set<std::string>& top_level_modules,
        primitive& p) const;

public:
    /**
     * Execute the property expansion against the model.
     */
    void expand(const annotations::type_repository& atrp,
        intermediate_model& m) const;
};

} }

#endif
