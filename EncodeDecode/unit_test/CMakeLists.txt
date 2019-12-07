#TESTING SHITE
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_color=yes --verbose)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER unit_test)
endmacro()

package_add_test(Encode_Test EncodeTests.cc)
