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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_CLASS_FORMATTER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_CLASS_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/settings_bundle.hpp"
#include "dogen/cpp/types/class_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class class_formatter_interface {
public:
    class_formatter_interface() = default;
    class_formatter_interface(const class_formatter_interface&) = delete;
    class_formatter_interface(class_formatter_interface&&) = default;
    virtual ~class_formatter_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the facet.
     */
    virtual std::string facet_id() const = 0;

    /**
     * @brief Unique identifier for the formatter, for logging purposes.
     */
    virtual std::string formatter_id() const = 0;

    /**
     * @brief Generate a c++ representation for the type.
     */
    virtual dogen::formatters::file
    format(const class_info& c, const settings_bundle& sb) const = 0;
};

} } }

#endif
