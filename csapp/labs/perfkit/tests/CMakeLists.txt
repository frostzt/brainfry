add_executable(test_runner
  test_runner.cpp
  test_timer.cpp
)

target_link_libraries(test_runner PRIVATE perfkit)

add_test(NAME perfkit_test COMMAND test_runner)
