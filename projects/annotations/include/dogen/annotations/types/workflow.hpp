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
#ifndef DOGEN_ANNOTATIONS_TYPES_WORKFLOW_HPP
#define DOGEN_ANNOTATIONS_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/annotations/types/object.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/scope_types.hpp"
#include "dogen/annotations/types/object_aggregate.hpp"
#include "dogen/annotations/types/raw_aggregate.hpp"
#include "dogen/annotations/types/field_definition.hpp"


namespace dogen {
namespace annotations {

/**
 * @brief Produces an annotation object from raw data.
 */
class workflow {
public:
    /**
     * @brief Initialise the annotations object factory.
     *
     *
     * @param repository All field definitions.
     * @param throw_on_missing_field_definition If true, any
     * annotations extensions for which a field definition does not
     * exist will result in an exception. If false, they will be
     * ignored.
     */
    explicit workflow(
        const repository& rp,
        const bool throw_on_missing_field_definition = true);

private:
    /**
     * @brief Returns the field definition for the qualified name, if
     * one exists.
     */
    boost::optional<field_definition>
    obtain_field_definition(const std::string& n) const;

    /**
     * @brief Ensures the field definition is valid for the current
     * scope.
     */
    void validate_scope(const field_definition& fd,
        const scope_types current_scope) const;

private:
    /**
     * @brief Aggregate raw data by key.
     */
    std::unordered_map<std::string, std::list<std::string> >
    aggregate_raw_data_activity(
        const std::list<std::pair<std::string, std::string> >&
        raw_data) const;

    /**
     * @brief Converts the raw data into a set of field instances.
     */
    std::unordered_map<std::string, field_instance> create_fields_activity(
        const std::unordered_map<std::string, std::list<std::string> >&
        aggregated_data, const scope_types current_scope) const;

public:
    /**
     * @brief Produce the annotations object.
     */
    object execute(const scope_types scope,
        const std::list<std::pair<std::string, std::string>>&
        raw_data) const;

    std::unordered_map<std::string, object_aggregate>
    execute(const std::string& root_object_id, const std::unordered_map<
        std::string, raw_aggregate>& raw_aggregates) const;

private:
    const repository& repository_;
    const bool throw_on_missing_field_definition_;
};

} }

#endif