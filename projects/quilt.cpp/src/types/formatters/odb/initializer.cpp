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
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/master_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/builtin_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/initializer.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

void initializer::initialize(registrar& rg) {
    register_formatter<master_header_formatter>(rg, traits::facet());
    register_formatter<builtin_header_formatter>(rg);
    register_formatter<primitive_header_formatter>(rg);
    register_formatter<class_header_formatter>(rg);
    register_formatter<enum_header_formatter>(rg);
    register_formatter<odb_options_formatter>(rg);
}

} } } } }
