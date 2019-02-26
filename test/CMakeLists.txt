#############################################################################
# one executable for each unit test 
#############################################################################

set(test_default_name "${PROJECT_NAME}_test")

set(TEST_ARGS )

file(GLOB test_input_files "data/*.obj")

message("${test_input_files}")

# file containing the geodesic distances from source to each vertex 
option(Export_Test_GeodesicDistanceFile "export file containing the geodesic distances from source to each vertex 
" OFF)

foreach(file ${test_input_files})
    set(TEST_ARGS 
        -m ${file} 
        -s 0
    )

    if(Export_Test_GeodesicDistanceFile)
        get_filename_component(FileName ${file} NAME_WE)
        get_filename_component(FilePath ${file} PATH)
        set(GEODESIC_OUTPUT_FILE "${FilePath}/${FileName}.txt")

        set(OUTPUT_ARG 
            -o ${GEODESIC_OUTPUT_FILE}
        )
        list(APPEND TEST_ARGS "${OUTPUT_ARG}")
        message(${TEST_ARGS})
    endif()

    add_test(NAME "${test_default_name}_default"
        COMMAND ${PROJECT_NAME} ${TEST_ARGS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endforeach()

