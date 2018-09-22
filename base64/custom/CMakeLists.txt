set(LIBNAME custom)

add_library("${LIBNAME}"
     base64.cpp
)

if(BUILD_TEST)
     set(TESTNAME "ut-${LIBNAME}")
     add_executable("${TESTNAME}" test/base64_test.cpp)
     target_link_libraries("${TESTNAME}" "${LIBNAME}" gtest_main)
     add_test(NAME "${LIBNAME}" COMMAND "${TESTNAME}")
endif()