add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(
    DIRECTORY ../../dir/inc/another/
    DESTINATION ../../dir/inc/another/
    COMPONENT headers
    FILES_MATCHING PATTERN "*.hpp")

set(include_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../dir/inc/another/dogen/test_models/split_project/odb")
set(all_odb_files "")
file(GLOB_RECURSE all_odb_files RELATIVE
    "${include_odb_dir}/"
    "${include_odb_dir}/*_pragmas.hpp")

set(src_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/odb/")
if(NOT EXISTS "${src_odb_dir}")
    file(MAKE_DIRECTORY "${src_odb_dir}")
endif()

add_custom_target(odb_split_project
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND mv ${include_odb_dir}/*.cpp ${src_odb_dir})

set(ignore_file false)
set(include_types_dir "${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/test_models/split_project/types")
foreach(odb_file ${all_odb_files})
    if (odb_file MATCHES "all_pragmas.hpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(type_name "")
        string(REPLACE "_pragmas.hpp" "" type_name ${odb_file})
        string(REPLACE "\\" "_" type_name ${type_name})
        string(REPLACE "/" "_" type_name ${type_name})

        set(target_name "odb_split_project_${type_name}")
        add_custom_target(${target_name}
            COMMENT "ODB ${type_name}"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/options.odb
            --output-dir ${include_odb_dir}/
            --odb-epilogue '\#include \"dogen/test_models/split_project/odb/${odb_file}\"'
            -I ${ODB_INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR}/../../dir/inc/another
            ${include_types_dir}/${type_name}.hpp)

        add_dependencies(odb_split_project ${target_name})
    endif()
    set(ignore_file false)
endforeach()
