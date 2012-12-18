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
#ifndef DOGEN_SML_TYPES_ENUMERATION_HPP
#define DOGEN_SML_TYPES_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <vector>
#include "dogen/sml/serialization/enumeration_fwd_ser.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/*
 * @brief An enumeration type provides an efficient way to define
 * a set of named integral constants that may be assigned to a variable.
 */
class enumeration final {
public:
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;
    ~enumeration() = default;

public:
    enumeration();

public:
    enumeration(
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const std::string& documentation,
        const std::vector<dogen::sml::enumerator>& enumerators);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enumeration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enumeration& v, unsigned int version);

public:
    /*
     * @brief Qualified name for the type.
     */
    /**@{*/
    const dogen::sml::qname& name() const {
        return name_;
    }

    dogen::sml::qname& name() {
        return name_;
    }

    void name(const dogen::sml::qname& v) {
        name_ = v;
    }

    void name(const dogen::sml::qname&& v) {
        name_ = std::move(v);
    }
    /**@}*/

    /*
     * @brief What to do with this enumeration in terms of code generation.
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const {
        return generation_type_;
    }

    void generation_type(const dogen::sml::generation_types& v) {
        generation_type_ = v;
    }
    /**@}*/

    /*
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    const std::string& documentation() const {
        return documentation_;
    }

    std::string& documentation() {
        return documentation_;
    }

    void documentation(const std::string& v) {
        documentation_ = v;
    }

    void documentation(const std::string&& v) {
        documentation_ = std::move(v);
    }
    /**@}*/

    /*
     * @brief Enumerators for this enumeration.
     */
    /**@{*/
    const std::vector<dogen::sml::enumerator>& enumerators() const {
        return enumerators_;
    }

    std::vector<dogen::sml::enumerator>& enumerators() {
        return enumerators_;
    }

    void enumerators(const std::vector<dogen::sml::enumerator>& v) {
        enumerators_ = v;
    }

    void enumerators(const std::vector<dogen::sml::enumerator>&& v) {
        enumerators_ = std::move(v);
    }
    /**@}*/

public:
    bool operator==(const enumeration& rhs) const;
    bool operator!=(const enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    dogen::sml::qname name_;
    dogen::sml::generation_types generation_type_;
    std::string documentation_;
    std::vector<dogen::sml::enumerator> enumerators_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::enumeration& lhs,
    dogen::sml::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif
