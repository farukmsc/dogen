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
#include "dogen/quilt.cpp/types/formatters/serialization/primitive_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>
#include "dogen/formatters/types/sequence_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

std::string primitive_implementation_formatter::static_artefact() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
primitive_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(),  cpp::traits::kernel(),
          traits::facet(),
          primitive_implementation_formatter::static_artefact());
    return r;
}

std::type_index primitive_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> primitive_implementation_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto& o(assistant::as<yarn::object>(static_artefact(), e));
    auto builder(f.make());

    const auto ch_fn(traits::class_header_archetype());
    builder.add(o.name(), ch_fn);

    using ic = inclusion_constants;
    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    // XML serialisation
    builder.add(ic::boost::serialization::nvp());
    builder.add(ic::boost::archive::xml_iarchive());
    builder.add(ic::boost::archive::xml_oarchive());

    const auto si(builder.make_special_includes(o));
    if (si.has_date)
        builder.add(ic::boost::date_time::gregorian::identity());

    if (si.has_ptime)
        builder.add(ic::boost::date_time::posix_time::identity());

    return builder.build();
}

dogen::formatters::artefact primitive_implementation_formatter::
format(const context& /*ctx*/, const yarn::element& /*e*/) const {
    dogen::formatters::artefact r;
    return r;
}

} } } } }