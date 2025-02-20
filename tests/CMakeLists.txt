add_executable(
        test_File
        test_FIle.cpp
)

target_include_directories(test_File PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        test_File
        gtest_main
        gtest
        pthread
)

include(GoogleTest)

gtest_discover_tests(test_File)