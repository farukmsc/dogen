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
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/variant/get.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/types/object_types.hpp"
#include "dogen/dia/types/stereotypes.hpp"
#include "dogen/dia/io/object_types_io.hpp"
#include "dogen/dia/io/stereotypes_io.hpp"
#include "dogen/dia/types/enum_parser.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/transformation_error.hpp"
#include "dogen/generator/modeling/dia_object_to_sml_enumeration.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml"));

using dogen::generator::modeling::transformation_error;

const std::string empty;
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_attributes("attributes");
const std::string dia_uml_attribute("umlattribute");
const std::string dia_string("string");
const std::string dia_composite("composite");
const std::string dia_stereotype("stereotype");
const std::string dia_documentation("comment");

const std::string hash_character("#");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string relationship_target_not_found(
    "Relationship points to object with non-existent ID: ");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string name_attribute_expected("Could not find name attribute");
const std::string type_attribute_expected("Could not find type attribute");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string missing_package_for_id("Missing package for dia object ID: ");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string error_parsing_stereotype("Fail to parse stereotype: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string root_vertex_id("root");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");
const std::string unexpected_child_node(
    "Non UML package object has a child node: ");

/**
 * @brief Parses a string representing an object type into its enum.
 *
 * @param s string with an object type
 */
dogen::dia::object_types parse_object_type(const std::string s) {
    dogen::dia::object_types r;
    try {
        using dogen::dia::enum_parser;
        r = enum_parser::parse_object_type(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(transformation_error(stream.str()));
    }
    return r;
}

/**
 * @brief Parses a string representing a stereotype into its enum
 *
 * @param s string with a stereotype
 */
dogen::dia::stereotypes parse_stereotype(const std::string s) {
    dogen::dia::stereotypes r;
    try {
        using dogen::dia::enum_parser;
        r = enum_parser::parse_stereotype(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_stereotype << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(transformation_error(stream.str()));
    }
    return r;
}

template<typename AttributeValue, typename Variant>
AttributeValue
attribute_value(const Variant& v, const std::string& description) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type
                                 << description;
        BOOST_THROW_EXCEPTION(transformation_error(unexpected_attribute_value_type +
            description));
    }
    return r;
}

}

namespace dogen {
namespace generator {
namespace modeling {

dogen::sml::qname dia_object_to_sml_enumeration::
transform_qname(const dogen::dia::attribute& a,
    dogen::sml::meta_types meta_type, const std::string& pkg_id) const {
    if (a.name() != dia_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected;
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    dogen::sml::qname name;
    name.model_name(model_name_);
    name.meta_type(meta_type);
    name.external_package_path(external_package_path_);

    if (!pkg_id.empty()) {
        const auto i(packages_.find(pkg_id));
        if (i == packages_.end()) {
            BOOST_LOG_SEV(lg, error) << missing_package_for_id << pkg_id;
            BOOST_THROW_EXCEPTION(transformation_error(missing_package_for_id + pkg_id));
        }
        auto pp(i->second.name().package_path());
        pp.push_back(i->second.name().type_name());
        name.package_path(pp);
    }

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return name;
}

std::string dia_object_to_sml_enumeration::
transform_string_attribute(const dogen::dia::attribute& a) const {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        BOOST_THROW_EXCEPTION(transformation_error(unexpected_attribute_value_size +
            boost::lexical_cast<std::string>(values.size())));
    }

    using dogen::dia::string;
    const auto v(attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_all(name, hash_character);
    boost::trim(name);
    return name;
}

dia_object_to_sml_enumeration::
dia_object_to_sml_enumeration(const std::string& model_name,
    const std::list<std::string>& external_package_path,
    bool is_target, bool verbose)
    : model_name_(model_name), external_package_path_(external_package_path),
      is_target_(is_target), verbose_(verbose) { }

bool dia_object_to_sml_enumeration::is_processable(const dia::object& o) const {
    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    if (ot != object_types::uml_class)
        return false;

    for (auto a : o.attributes()) {
        if (a.name() != dia_stereotype)
            continue;

        using dogen::dia::stereotypes;
        const std::string v(transform_string_attribute(a));
        if (v.empty())
            return false;

        const auto st(parse_stereotype(v));
        if (st == stereotypes::enumeration)
            return true;
    }
    return false;
}

void dia_object_to_sml_enumeration::add_object(const dia::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Adding enumeration object: " << o.id();

    if (!is_processable(o)) {
        BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                 << " to be " << dia_uml_attribute
                                 << "but was " << o.type();
        BOOST_THROW_EXCEPTION(transformation_error(uml_attribute_expected));

    }

    objects_.push_back(o);
}

dogen::sml::enumerator dia_object_to_sml_enumeration::
transform_enumerator(const dogen::dia::composite& uml_attribute,
    const unsigned int position) const {
    dogen::sml::enumerator r;
    for (const auto a : uml_attribute.value()) {
        if (a->name() == dia_name) {
            r.name(transform_string_attribute(*a));
        } else if (a->name() == dia_documentation) {
            const std::string doc(transform_string_attribute(*a));
            r.documentation(doc);
        } else {
            BOOST_LOG_SEV(lg, warn) << "Ignoring unexpected attribute: "
                                    << a->name();
        }
    }
    r.value(boost::lexical_cast<std::string>(position));
    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a name attribute.";
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    return r;
}

sml::enumeration dia_object_to_sml_enumeration::
transform_enumeration(const dia::object& o) const {
    sml::enumeration r;

    r.generation_type(is_target_ ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);
    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();
        if (a.name() == dia_name) {
            const std::string pkg_id(o.child_node() ?
                o.child_node()->parent() : empty);
            using sml::meta_types;
            r.name(transform_qname(a, meta_types::enumeration,
                    pkg_id));
        } else if (a.name() == dia_documentation) {
            const std::string doc(transform_string_attribute(a));
            r.documentation(doc);
        } if (a.name() == dia_attributes) {
            const auto values(a.values());

            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            dogen::sml::enumerator invalid;
            invalid.name("invalid");
            invalid.documentation("Represents an uninitialised enum");
            invalid.value("0");

            std::vector<dogen::sml::enumerator> enumerators;
            enumerators.push_back(invalid);

            unsigned int pos(1);
            for (auto v : values) {
                using dogen::dia::composite;
                const auto c(attribute_value<composite>(v, dia_composite));

                if (c.type() != dia_uml_attribute) {
                    BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                             << " to be "
                                             << dia_uml_attribute
                                             << "but was " << c.type();
                    BOOST_THROW_EXCEPTION(transformation_error(uml_attribute_expected));
                }
                BOOST_LOG_SEV(lg, debug) << "Found composite of type "
                                         << c.type();
                enumerators.push_back(transform_enumerator(c, pos++));
            }
            r.enumerators(enumerators);
        }

    }
    return r;
}

std::unordered_map<sml::qname, sml::enumeration>
dia_object_to_sml_enumeration::
transform(std::unordered_map<std::string, sml::package> packages) {
    packages_ = packages;
    std::unordered_map<sml::qname, sml::enumeration> r;
    for (const auto o : objects_) {
        auto e(transform_enumeration(o));
        r.insert(std::make_pair(e.name(), e));
    }
    return r;
}

} } }
