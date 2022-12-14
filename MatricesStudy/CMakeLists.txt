#SOURCE
include_directories(${CMAKE_CURRENT_LIST_DIR}/public)

file(
        GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        ${CMAKE_CURRENT_LIST_DIR}/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/*.tpp
        ${CMAKE_CURRENT_LIST_DIR}/*.hpp
        ${CMAKE_CURRENT_LIST_DIR}/*.h
)

#TARGETS
add_library(
        ${CMAKE_PROJECT_NAME}_lib
        STATIC
        ${SOURCES}
)
#add_executable(
#        ${CMAKE_PROJECT_NAME}_exec
#        ${SOURCES}
#)