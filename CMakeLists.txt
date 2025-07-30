cmake_minimum_required(VERSION 3.21)
project(pb-cpp-data CXX)


add_library(pb-cpp-data STATIC 
    src/library.cpp
)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-fpermissive -Wno-write-strings")
endif()

if (WIN32)
    target_compile_definitions(pb-cpp-data PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set_target_properties(pb-cpp-data PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)


#Bring the headers, plugin include, algorithm include
target_include_directories(pb-cpp-data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

# only do the testing targets if we are doing this project.  this way
# other projects won't get this stuff.
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    include(CTest)
    include(FetchContent)

    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
    )
    FetchContent_MakeAvailable(googletest)
    add_library(GTest::GTest INTERFACE IMPORTED)
    target_link_libraries(GTest::GTest INTERFACE gtest_main)


    add_executable(pb-cpp-data-test 
        test/DummyTest.cpp
    )

    target_link_libraries(pb-cpp-data-test PRIVATE
        GTest::GTest
        pb-cpp-data)

    set_target_properties(pb-cpp-data-test PROPERTIES 
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE ON
    )

    add_test(pb-cpp-data-gtests pb-cpp-data-test)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test/resource/)

    file(TO_NATIVE_PATH ${PROJECT_SOURCE_DIR}/test/resource/ TEST_RESOURCES_SRC)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/test/resource/ TEST_RESOURCES_DEST)    
    #copy the resources used for tests into the build folder under test/resource.
    add_custom_command(
            TARGET pb-cpp-data-test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${TEST_RESOURCES_SRC}
                    ${TEST_RESOURCES_DEST})

endif()