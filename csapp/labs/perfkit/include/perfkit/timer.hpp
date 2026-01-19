#ifndef PERFKIT_TIMER_HPP
#define PERFKIT_TIMER_HPP

#include <chrono>

namespace perfkit {
static std::chrono::time_point<std::chrono::steady_clock> started_at;

/*
 * Starts the timer
 */
inline void start_timer() { started_at = std::chrono::steady_clock::now(); }

/*
 * Stops the timer and returns a `long long` which is the count of tick elapsed
 */
inline long long stop_timer() {
  auto now = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now - started_at)
      .count();
}
} // namespace perfkit

#endif // PERFKIT_TIMER_HPP
