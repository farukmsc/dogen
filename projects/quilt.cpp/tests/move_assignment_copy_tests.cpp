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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/quilt.cpp/types/all.hpp"
#include "dogen/quilt.cpp/io/all_io.hpp"
#include "dogen/quilt.cpp/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("quilt.cpp");
const std::string test_suite("move_assignment_copy_tests");

}

using namespace dogen::quilt::cpp;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(move_assignment_copy_tests)

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");

    test_move_assignment_copy<fabric::registrar_generator>();
    test_move_assignment_copy<formattables::model_generator>();
    test_move_assignment_copy<formattables::formattable_generator>();
    test_move_assignment_copy<formattables::odb_properties_generator>();
    test_move_assignment_copy<formattables::element_properties_generator>();
    test_move_assignment_copy<formattables::global_enablement_configuration_generator>();
    test_move_assignment_copy<formattables::artefact_properties_generator>();
    test_move_assignment_copy<formattables::helper_properties_generator>();
    test_move_assignment_copy<formattables::aspect_properties_generator>();
    test_move_assignment_copy<formattables::facet_properties_generator>();
    test_move_assignment_copy<formattables::helper_descriptor_generator>();
    test_move_assignment_copy<formattables::streaming_properties_generator>();
    test_move_assignment_copy<formattables::locator_configuration_generator>();
    test_move_assignment_copy<formattables::locator_facet_configuration_generator>();
    test_move_assignment_copy<formattables::locator_archetype_configuration_generator>();
    test_move_assignment_copy<fabric::registrar_generator>();
    test_move_assignment_copy<fabric::cmakelists_generator>();
    test_move_assignment_copy<fabric::odb_options_generator>();
    test_move_assignment_copy<fabric::master_header_generator>();
    test_move_assignment_copy<fabric::forward_declarations_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
