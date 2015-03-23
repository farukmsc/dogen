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
#include "dogen/dynamic/schema/types/repository.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

repository::repository(
    const std::list<dogen::dynamic::schema::field_definition>& all_field_definitions,
    const std::unordered_map<std::string, std::list<std::string> >& facet_names_by_model_name,
    const std::unordered_map<std::string, std::list<std::string> >& formatter_names_by_model_name,
    const std::unordered_map<std::string, dogen::dynamic::schema::field_definition>& field_definitions_by_name,
    const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& field_definitions_by_facet_name,
    const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& field_definitions_by_formatter_name)
    : all_field_definitions_(all_field_definitions),
      facet_names_by_model_name_(facet_names_by_model_name),
      formatter_names_by_model_name_(formatter_names_by_model_name),
      field_definitions_by_name_(field_definitions_by_name),
      field_definitions_by_facet_name_(field_definitions_by_facet_name),
      field_definitions_by_formatter_name_(field_definitions_by_formatter_name) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(all_field_definitions_, other.all_field_definitions_);
    swap(facet_names_by_model_name_, other.facet_names_by_model_name_);
    swap(formatter_names_by_model_name_, other.formatter_names_by_model_name_);
    swap(field_definitions_by_name_, other.field_definitions_by_name_);
    swap(field_definitions_by_facet_name_, other.field_definitions_by_facet_name_);
    swap(field_definitions_by_formatter_name_, other.field_definitions_by_formatter_name_);
}

bool repository::operator==(const repository& rhs) const {
    return all_field_definitions_ == rhs.all_field_definitions_ &&
        facet_names_by_model_name_ == rhs.facet_names_by_model_name_ &&
        formatter_names_by_model_name_ == rhs.formatter_names_by_model_name_ &&
        field_definitions_by_name_ == rhs.field_definitions_by_name_ &&
        field_definitions_by_facet_name_ == rhs.field_definitions_by_facet_name_ &&
        field_definitions_by_formatter_name_ == rhs.field_definitions_by_formatter_name_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::dynamic::schema::field_definition>& repository::all_field_definitions() const {
    return all_field_definitions_;
}

std::list<dogen::dynamic::schema::field_definition>& repository::all_field_definitions() {
    return all_field_definitions_;
}

void repository::all_field_definitions(const std::list<dogen::dynamic::schema::field_definition>& v) {
    all_field_definitions_ = v;
}

void repository::all_field_definitions(const std::list<dogen::dynamic::schema::field_definition>&& v) {
    all_field_definitions_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& repository::facet_names_by_model_name() const {
    return facet_names_by_model_name_;
}

std::unordered_map<std::string, std::list<std::string> >& repository::facet_names_by_model_name() {
    return facet_names_by_model_name_;
}

void repository::facet_names_by_model_name(const std::unordered_map<std::string, std::list<std::string> >& v) {
    facet_names_by_model_name_ = v;
}

void repository::facet_names_by_model_name(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    facet_names_by_model_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& repository::formatter_names_by_model_name() const {
    return formatter_names_by_model_name_;
}

std::unordered_map<std::string, std::list<std::string> >& repository::formatter_names_by_model_name() {
    return formatter_names_by_model_name_;
}

void repository::formatter_names_by_model_name(const std::unordered_map<std::string, std::list<std::string> >& v) {
    formatter_names_by_model_name_ = v;
}

void repository::formatter_names_by_model_name(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    formatter_names_by_model_name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::dynamic::schema::field_definition>& repository::field_definitions_by_name() const {
    return field_definitions_by_name_;
}

std::unordered_map<std::string, dogen::dynamic::schema::field_definition>& repository::field_definitions_by_name() {
    return field_definitions_by_name_;
}

void repository::field_definitions_by_name(const std::unordered_map<std::string, dogen::dynamic::schema::field_definition>& v) {
    field_definitions_by_name_ = v;
}

void repository::field_definitions_by_name(const std::unordered_map<std::string, dogen::dynamic::schema::field_definition>&& v) {
    field_definitions_by_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& repository::field_definitions_by_facet_name() const {
    return field_definitions_by_facet_name_;
}

std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& repository::field_definitions_by_facet_name() {
    return field_definitions_by_facet_name_;
}

void repository::field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& v) {
    field_definitions_by_facet_name_ = v;
}

void repository::field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >&& v) {
    field_definitions_by_facet_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& repository::field_definitions_by_formatter_name() const {
    return field_definitions_by_formatter_name_;
}

std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& repository::field_definitions_by_formatter_name() {
    return field_definitions_by_formatter_name_;
}

void repository::field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >& v) {
    field_definitions_by_formatter_name_ = v;
}

void repository::field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::dynamic::schema::field_definition> >&& v) {
    field_definitions_by_formatter_name_ = std::move(v);
}

} } }