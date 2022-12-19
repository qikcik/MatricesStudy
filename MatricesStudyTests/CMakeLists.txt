#IMPORT
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

enable_testing()

#SOURCE

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/../MatricesStudy/public
)

file(
        GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        ${CMAKE_CURRENT_LIST_DIR}/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/public/*.hpp
        ${CMAKE_CURRENT_LIST_DIR}/public/*.h
)

enable_testing()

#TARGET
add_executable(
        ${CMAKE_PROJECT_NAME}_tests
        ${SOURCES}
        private/MatricesUtils.cpp)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}_tests
        ${CMAKE_PROJECT_NAME}_lib
        GTest::gtest_main
        GTest::gmock_main
)

#DISCOVER
include(
        GoogleTest
)

gtest_discover_tests(
        ${CMAKE_PROJECT_NAME}_tests
)