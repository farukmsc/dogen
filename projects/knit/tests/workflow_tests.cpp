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
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/test/macros.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/yarn_dia.hpp"
#include "dogen/utility/test_data/yarn_json.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/options/test/mock_options_factory.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/knit/types/workflow.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/yarn/serialization/model_ser.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"
#include "dogen/yarn/test/yarn_file_asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

/*
 * Comment these out as required if testing only one frontend.
 */
#define ENABLE_DIA_TESTS
#define ENABLE_JSON_TESTS
#define ENABLE_CSHARP_TESTS
#define ENABLE_UPSILON_TESTS

using dogen::utility::test_data::yarn_dia;
using dogen::utility::test_data::yarn_json;
using dogen::utility::test_data::yarn_upsilon;

namespace  {

const std::string empty;
const std::string empty_module_path;
const std::string test_module("knit");
const std::string test_suite("workflow_tests");

const std::string expected("/expected");
const std::string actual_dia_dir("/actual.dia");
const std::string actual_json_dir("/actual.json");
const std::string actual_upsilon_dir("/actual.upsilon");

const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string dia_invalid_name("Dia object name is empty");

struct test_configuration {
    boost::filesystem::path expected;
    boost::filesystem::path actual;
    dogen::options::knitting_options options;
};

test_configuration make_test_configuration(const std::string& model_name,
    const boost::filesystem::path& target,
    const std::string& actual_dir) {
    test_configuration r;

    using dogen::utility::test_data::validating_resolver;
    r.expected = validating_resolver::resolve(model_name + ::expected);
    r.actual = validating_resolver::resolve(model_name + actual_dir);

    using dogen::options::test::mock_options_factory;
    r.options = mock_options_factory::make_knitting_options(target, r.actual);

    return r;
}

test_configuration make_split_project_configuration(const bool json = false) {
    const auto target(json ?
        yarn_json::input_split_project_json() :
        yarn_dia::input_split_project_dia());
    const auto model_name(target.stem().string());
    const auto actual_dir(json ? actual_json_dir : actual_dia_dir);
    auto r(make_test_configuration(model_name, target, actual_dir));
    auto& o(r.options);

    /*
     * Note that we create a top-level directory with the project name
     * just to make the life easier for the rebaselining
     * scripts.
     */
    o.output_directory_path() /= "split_project";

    /*
     * Its important that the output directory is _not_ a parent of
     * the header directory, or else we will not test housekeeping
     * properly.
     */
    o.cpp_headers_output_directory_path(o.output_directory_path());
    const boost::filesystem::path p("dir/inc/another");
    o.cpp_headers_output_directory_path() /= p;
    o.output_directory_path() /= "some_dir";
    return r;
}

bool execute_test(const test_configuration& tc) {
    /*
     * Ensure the actual directory is empty before we run the
     * tests. Note that the actual directory is guaranteed to exist as
     * it is created by the scripts. This is a very roundabout way of
     * doing things, but works for now.
     */
    // boost::filesystem::remove_all(tc.actual);
    // boost::filesystem::create_directory(tc.actual);

    dogen::knit::workflow w(tc.options);
    w.execute();

    using dogen::utility::test::asserter;
    return asserter::assert_directory(tc.expected, tc.actual);
}

bool test_knit_workflow(const std::string& model_name,
    const boost::filesystem::path& target,
    const std::string& actual_dir) {
    const auto tc(make_test_configuration(model_name, target, actual_dir));
    return execute_test(tc);
}

bool test_knit_workflow(const boost::filesystem::path& target,
    const std::string& actual_dir) {
    const auto name(target.stem().string());
    return test_knit_workflow(name, target, actual_dir);
}

}

using dogen::utility::test::contains_checker;
using dogen::knit::workflow_error;

BOOST_AUTO_TEST_SUITE(workflow_tests)

#ifdef ENABLE_DIA_TESTS

BOOST_AUTO_TEST_CASE(cpp_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("cpp_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_cpp_model_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code_dia) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code_dia");
    const auto dia(yarn_dia::input_disable_facet_folders_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code_dia) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code_dia");
    const auto dia(yarn_dia::input_disable_cmakelists_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_types_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_types_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_types_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_cod_diae");
    const auto dia(yarn_dia::input_enable_facet_hash_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_serialization_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_io_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_model_does_not_generate_code_dia) {
    SETUP_TEST_LOG("two_empty_layers_model_does_not_generate_code_dia");
    const auto dia(yarn_dia::input_two_empty_layers_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(class_without_name_model_throws) {
    SETUP_TEST_LOG("class_without_name_model_throws");
    const auto target(yarn_dia::input_class_without_name_dia());
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(test_knit_workflow(target, actual_dia_dir),
        std::exception, c);
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("empty_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_empty_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_compressed_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_two_layers_with_objects_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("std_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_std_model_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("boost_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_boost_model_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(package_without_name_model_throws) {
    SETUP_TEST_LOG("package_without_name_model_throws");
    const auto dia(yarn_dia::input_package_without_name_dia());
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(test_knit_workflow(dia, actual_dia_dir),
        std::exception, c);
}

BOOST_AUTO_TEST_CASE(all_path_and_directory_settings_generates_expected_code_dia) {
    SETUP_TEST_LOG("all_path_and_directory_settings_generates_expected_code_dia");
    const auto dia(yarn_dia::input_all_path_and_directory_settings_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(split_project_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("split_project_model_generates_expected_code_dia");
    const auto tc(make_split_project_configuration());
    BOOST_CHECK(execute_test(tc));
}

BOOST_AUTO_TEST_CASE(cpp_98_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("cpp_98_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_cpp_98_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(lam_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("lam_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_lam_model_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

#ifdef ENABLE_CSHARP_TESTS

BOOST_AUTO_TEST_CASE(csharp_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("csharp_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_csharp_model_dia());
    BOOST_CHECK(test_knit_workflow(dia, actual_dia_dir));
}

#endif // ENABLE_CSHARP_TESTS

#endif // ENABLE_DIA_TESTS

#ifdef ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(cpp_model_generates_expected_code_json) {
    SETUP_TEST_LOG("cpp_model_generates_expected_code_json");
    const auto json(yarn_json::input_cpp_model_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code_json) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code_json");
    const auto json(yarn_json::input_disable_facet_folders_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code_json) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code_json");
    const auto json(yarn_json::input_disable_cmakelists_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_types_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_types_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_types_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_hash_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_serialization_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_io_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code_json) {
    SETUP_TEST_LOG("empty_model_generates_expected_code_json");
    const auto json(yarn_json::input_empty_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code_json) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code_json");
    const auto json(yarn_json::input_compressed_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code_json) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code_json");
    const auto json(yarn_json::input_two_layers_with_objects_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code_json) {
    SETUP_TEST_LOG("std_model_generates_expected_code_json");
    const auto json(yarn_json::input_std_model_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code_json) {
    SETUP_TEST_LOG("boost_model_generates_expected_code_json");
    const auto json(yarn_json::input_boost_model_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(all_path_and_directory_settings_generates_expected_code_json) {
    SETUP_TEST_LOG("all_path_and_directory_settings_generates_expected_code_json");
    const auto json(yarn_json::input_all_path_and_directory_settings_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(split_project_model_generates_expected_code_json) {
    SETUP_TEST_LOG("split_project_model_generates_expected_code_json");
    const auto tc(make_split_project_configuration(true/*json*/));
    BOOST_CHECK(execute_test(tc));
}

BOOST_AUTO_TEST_CASE(cpp_98_model_generates_expected_code_json) {
    SETUP_TEST_LOG("cpp_98_model_generates_expected_code_json");
    const auto json(yarn_json::input_cpp_98_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(lam_model_generates_expected_code_json) {
    SETUP_TEST_LOG("lam_model_generates_expected_code_json");
    const auto json(yarn_json::input_lam_model_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

#ifdef ENABLE_CSHARP_TESTS

BOOST_AUTO_TEST_CASE(csharp_model_generates_expected_code_json) {
    SETUP_TEST_LOG("csharp_model_generates_expected_code_json");
    const auto json(yarn_json::input_csharp_model_json());
    BOOST_CHECK(test_knit_workflow(json, actual_json_dir));
}

#endif // ENABLE_CSHARP_TESTS

#endif // ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(upsilon_model_generates_expected_code) {
    SETUP_TEST_LOG("upsilon_model_generates_expected_code");
    const auto upsilon(yarn_upsilon::input_zeta_model_configuration_xml());
    BOOST_CHECK(test_knit_workflow("Zeta", upsilon, actual_upsilon_dir));
}

BOOST_AUTO_TEST_SUITE_END()
