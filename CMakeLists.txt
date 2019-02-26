cmake_minimum_required(VERSION 3.8)

# Vertex-Oriented Triangle Progragation Geodesic
project(VTPGeodesic LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Setup the list of source files
set( VTP_APP_SOURCES 
    main.cpp
)

add_executable( ${PROJECT_NAME} ${VTP_APP_SOURCES})

include(CTest) #adds option BUILD_TESTING (default ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()