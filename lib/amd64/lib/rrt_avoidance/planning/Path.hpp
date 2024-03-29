#pragma once

#include "lib/rrt_avoidance/StateSpace.hpp"
#include <vector>

namespace lib {
namespace rrt_avoidance {

/**
 * @brief Reduce the vector to @maxSize length
 * @details We do this by sampling to evenly distribute deletions
 *
 * @param states     The vector of T values to sample
 * @param maxSize Max length of the resulting vector
 */
template <typename T>
void DownSampleVector(std::vector<T>& states, size_t maxSize) {
  if (states.size() > maxSize) {
    int toDelete = states.size() - maxSize;
    double spacing = (double)states.size() / (double)toDelete;
    double i = 0.0;
    while (toDelete) {
      toDelete--;
      states.erase(states.begin() + (int)(i + 0.5));
      i += spacing - 1.0;
    }
  }
}

/**
 * @brief Deletes waypoints from @pts
 *
 * @param pts A vector of states that constitutes the path
 * @param transitionValidator A function that returns a boolean indicating
 *        whether or not a straight connection exists between the two given
 * states
 */
template <typename T>
void SmoothPath(std::vector<T>& pts, const StateSpace<T>& stateSpace) {
  size_t span = 2;
  while (span < pts.size()) {
    bool changed = false;
    for (size_t i = 0; i + span < pts.size(); i++) {
      if (stateSpace.transitionValid(pts[i], pts[i + span])) {
        for (size_t x = 1; x < span; x++) {
          pts.erase(pts.begin() + i + 1);
        }
        changed = true;
      }
    }

    if (!changed) span++;
  }
}

}  // namespace rrt_avoidance
}  // namespace lib
