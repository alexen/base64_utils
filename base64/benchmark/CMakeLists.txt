set(TESTNAME base64_benchmark_test)
add_executable(${TESTNAME}
     base64_benchmark_test.cpp
)
target_link_libraries(${TESTNAME}
     celero
)