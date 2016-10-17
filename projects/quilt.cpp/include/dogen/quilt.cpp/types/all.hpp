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
#ifndef DOGEN_QUILT_CPP_TYPES_ALL_HPP
#define DOGEN_QUILT_CPP_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/types/cpp.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/workflow.hpp"
#include "dogen/quilt.cpp/types/initializer.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/types/fabric/injector.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/initializer.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/reducer.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/building_error.hpp"
#include "dogen/quilt.cpp/types/formatters/io/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_error.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/model_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/types/initializer.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/resolution_error.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_descriptor.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formattables/element_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/initializer.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/transformation_error.hpp"
#include "dogen/quilt.cpp/types/formattables/locator_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_support_types.hpp"
#include "dogen/quilt.cpp/types/formatters/master_header_formatter.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/initializer.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_directory_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/locator_facet_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/io/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_resolver.hpp"
#include "dogen/quilt.cpp/types/formattables/file_path_and_guard_expander.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder.hpp"
#include "dogen/quilt.cpp/types/formattables/local_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/exception_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/namespace_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/global_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/locator_formatter_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/forward_declarations_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/forward_declarations_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"

#endif
