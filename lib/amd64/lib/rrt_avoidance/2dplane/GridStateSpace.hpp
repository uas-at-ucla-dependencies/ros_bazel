#pragma once

#include <Eigen/Dense>
#include "lib/rrt_avoidance/2dplane/ObstacleGrid.hpp"
#include "lib/rrt_avoidance/2dplane/PlaneStateSpace.hpp"

namespace lib {
namespace rrt_avoidance {

/**
 * @brief A 2d plane with continuous states and discretized obstacles.
 * @details The state space is broken up into a grid with the given discrete
 * height and widths.
 */
class GridStateSpace : public PlaneStateSpace<Eigen::Vector2d> {
public:
    GridStateSpace(double width, double height, int discretizedWidth,
                   int discretizedHeight);

    /**
     * Returns a boolean indicating whether the given point is within bounds and
     * obstacle-free.
     */
    bool stateValid(const Eigen::Vector2d& pt) const;
    bool transitionValid(const Eigen::Vector2d& from,
                         const Eigen::Vector2d& to) const;

    using PlaneStateSpace<Eigen::Vector2d>::intermediateState;
    Eigen::Vector2d intermediateState(const Eigen::Vector2d& source,
                                      const Eigen::Vector2d& target,
                                      double minStepSize,
                                      double maxStepSize) const;

    const ObstacleGrid& obstacleGrid() const;
    ObstacleGrid& obstacleGrid();

private:
    ObstacleGrid _obstacleGrid;
};

}  // namespace rrt_avoidance
}  // namespace lib
