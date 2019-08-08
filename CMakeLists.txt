cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 1)
endif()

project(ip_filter VERSION 0.0.${VERSION})

add_executable(ip_filter ip_filter.cpp)
add_library(lib lib.cpp)
target_link_libraries(ip_filter lib)
target_include_directories(lib
        PRIVATE "${CMAKE_BINARY_PATH}")

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

### gtest ###
find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(test_ip_filter test_ip_filter.cpp)
target_link_libraries(test_ip_filter
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        lib)

target_include_directories(test_ip_filter PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

enable_testing()
add_test(test_ip_filter test_ip_filter)
### ###

set_target_properties(ip_filter test_ip_filter PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
            /W4
            )
    target_compile_options(test_ip_filter PRIVATE
            /W4
            )
else ()
    target_compile_options(ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()