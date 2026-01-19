#include <cassert>
#include <iostream>
#include <thread>

#include <perfkit/timer.hpp>

void test_timer_basic() {
  perfkit::start_timer();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  auto elapsed = perfkit::stop_timer();

  std::cout << "Time: " << elapsed << std::endl;

  assert(elapsed >= 0 && "Time should be positive");
  assert(elapsed >= 100 && "Should have elapsed at least 100ms");
  assert(elapsed < 200 && "Should not take more than 200ms");

  std::cout << "test_timer_basic: PASSED" << std::endl;
}

void test_timer_zero_time() {
  perfkit::start_timer();
  auto elapsed = perfkit::stop_timer();

  assert(elapsed >= 0 && "Time should be positive even for immediate stop");
  assert(elapsed < 10 && "Immediate stop should be under 10ms");

  std::cout << "test_timer_zero_time: PASSED" << std::endl;
}

void test_timer_multiple_runs() {
  for (int i = 0; i < 3; i++) {
    perfkit::start_timer();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto elapsed = perfkit::stop_timer();

    assert(elapsed >= 0 && "Time should be positive in each iteration");
    assert(elapsed >= 50 && "Each run should take at least 50ms");
  }

  std::cout << "test_timer_multiple_runs: PASSED" << std::endl;
}

void test_timer_longer_duration() {
  perfkit::start_timer();
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  auto elapsed = perfkit::stop_timer();

  assert(elapsed >= 250 && "Should handle longer durations");
  assert(elapsed < 350 && "Should be reasonably accurate");

  std::cout << "test_timer_longer_duration: PASSED" << std::endl;
}
