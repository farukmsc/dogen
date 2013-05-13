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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_DOMAIN_IMPLEMENTATION_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_DOMAIN_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class domain_implementation : public file_formatter {
public:
    domain_implementation() = delete;
    domain_implementation(const domain_implementation&) = default;
    domain_implementation(domain_implementation&&) = default;
    domain_implementation& operator=(const domain_implementation&) = default;

public:
    domain_implementation(std::ostream& stream,
        bool disable_complete_constructor,
        bool use_integrated_io, bool disable_io);

    virtual ~domain_implementation() noexcept {}

private:
    void smart_pointer_helper(const nested_type_info& nti);
    void recursive_helper_method_creator(const nested_type_info& nti,
        std::unordered_set<std::string>& types_done);

    void io_helper_methods(const class_info& ci);
    void inserter_operator(const class_info& ci);
    void class_implementation(const aspect_types at,
        const sml::category_types ct, const class_info& ci);

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        bool disable_complete_constructor, bool use_integrated_io,
        bool disable_io);

private:
    void format_class(const file_info& fi);
    void format_enumeration(const file_info& fi);

public:
    virtual void format(const file_info& fi) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
    const bool disable_complete_constructor_;
    const bool use_integrated_io_;
    const bool disable_io_;
};

} } }

#endif
