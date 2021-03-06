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
#ifndef DOGEN_YARN_TYPES_ALL_HPP
#define DOGEN_YARN_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/node.hpp"
#include "dogen/yarn/types/yarn.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/mapper.hpp"
#include "dogen/yarn/types/merger.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/builtin.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/indexer.hpp"
#include "dogen/yarn/types/indices.hpp"
#include "dogen/yarn/types/mapping.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/workflow.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/persister.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/decomposer.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/yarn/types/enumerator.hpp"
#include "dogen/yarn/types/separators.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/mapping_set.hpp"
#include "dogen/yarn/types/transformer.hpp"
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/object_types.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/mapping_error.hpp"
#include "dogen/yarn/types/mapping_value.hpp"
#include "dogen/yarn/types/merging_error.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/frontend_error.hpp"
#include "dogen/yarn/types/indexing_error.hpp"
#include "dogen/yarn/types/name_flattener.hpp"
#include "dogen/yarn/types/pretty_printer.hpp"
#include "dogen/yarn/types/printing_error.hpp"
#include "dogen/yarn/types/workflow_error.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/hydration_error.hpp"
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/yarn/types/mapping_actions.hpp"
#include "dogen/yarn/types/mapping_context.hpp"
#include "dogen/yarn/types/origin_expander.hpp"
#include "dogen/yarn/types/persister_error.hpp"
#include "dogen/yarn/types/registrar_error.hpp"
#include "dogen/yarn/types/type_parameters.hpp"
#include "dogen/yarn/types/concept_expander.hpp"
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/parsing_expander.hpp"
#include "dogen/yarn/types/resolution_error.hpp"
#include "dogen/yarn/types/string_processor.hpp"
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/types/language_expander.hpp"
#include "dogen/yarn/types/mappings_hydrator.hpp"
#include "dogen/yarn/types/name_tree_builder.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/frontend_interface.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/injection_expander.hpp"
#include "dogen/yarn/types/injector_interface.hpp"
#include "dogen/yarn/types/injector_registrar.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/mappings_validator.hpp"
#include "dogen/yarn/types/primitive_expander.hpp"
#include "dogen/yarn/types/attributes_expander.hpp"
#include "dogen/yarn/types/annotations_expander.hpp"
#include "dogen/yarn/types/association_expander.hpp"
#include "dogen/yarn/types/containment_expander.hpp"
#include "dogen/yarn/types/decomposition_result.hpp"
#include "dogen/yarn/types/enumeration_expander.hpp"
#include "dogen/yarn/types/first_stage_expander.hpp"
#include "dogen/yarn/types/new_name_tree_parser.hpp"
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/yarn/types/orm_model_properties.hpp"
#include "dogen/yarn/types/stereotypes_expander.hpp"
#include "dogen/yarn/types/transformation_error.hpp"
#include "dogen/yarn/types/first_stage_validator.hpp"
#include "dogen/yarn/types/orm_module_properties.hpp"
#include "dogen/yarn/types/orm_object_properties.hpp"
#include "dogen/yarn/types/second_stage_expander.hpp"
#include "dogen/yarn/types/mapping_set_repository.hpp"
#include "dogen/yarn/types/second_stage_validator.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"
#include "dogen/yarn/types/legacy_name_tree_parser.hpp"
#include "dogen/yarn/types/orm_properties_expander.hpp"
#include "dogen/yarn/types/orm_attribute_properties.hpp"
#include "dogen/yarn/types/orm_primitive_properties.hpp"
#include "dogen/yarn/types/type_parameters_expander.hpp"
#include "dogen/yarn/types/intermediate_model_repository.hpp"
#include "dogen/yarn/types/mapping_set_repository_factory.hpp"
#include "dogen/yarn/types/identifiable_and_qualified_builder.hpp"
#include "dogen/yarn/types/intermediate_model_repository_factory.hpp"

#endif
