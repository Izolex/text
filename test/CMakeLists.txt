project(text_search_test)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GTest::GTest)
