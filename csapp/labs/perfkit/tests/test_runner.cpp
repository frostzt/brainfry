#include <exception>
#include <iostream>

// Test function declarations
void test_timer_basic();
void test_timer_zero_time();
void test_timer_multiple_runs();
void test_timer_longer_duration();

int main() {
  int passed = 0;
  int failed = 0;

  std::cout << "Running tests...\n" << std::endl;

  // Timer tests
  try {
    test_timer_basic();
    passed++;
  } catch (const std::exception &e) {
    std::cerr << "test_timer_basic: FAILED - " << e.what() << std::endl;
    failed++;
  }

  try {
    test_timer_zero_time();
    passed++;
  } catch (const std::exception &e) {
    std::cerr << "test_timer_zero_time: FAILED - " << e.what() << std::endl;
    failed++;
  }

  try {
    test_timer_multiple_runs();
    passed++;
  } catch (const std::exception &e) {
    std::cerr << "test_timer_multiple_runs: FAILED - " << e.what() << std::endl;
    failed++;
  }

  try {
    test_timer_longer_duration();
    passed++;
  } catch (const std::exception &e) {
    std::cerr << "test_timer_longer_duration: FAILED - " << e.what()
              << std::endl;
    failed++;
  }

  std::cout << "\n========================================" << std::endl;
  std::cout << "Tests passed: " << passed << std::endl;
  std::cout << "Tests failed: " << failed << std::endl;
  std::cout << "========================================" << std::endl;

  return failed > 0 ? 1 : 0;
}
