/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file spline_2d_constraint.h
 **/

#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_

#include <vector>
#include "Eigen/Core"

#include "modules/common/math/vec2d.h"
#include "modules/planning/math/smoothing_spline/affine_constraint.h"
#include "modules/planning/math/smoothing_spline/spline_2d.h"

namespace apollo {
namespace planning {

class Spline2dConstraint {
 public:
  Spline2dConstraint(const std::vector<double>& t_knots,
                     const std::uint32_t order);

  // direct method
  bool AddInequalityConstraint(const Eigen::MatrixXd& constraint_matrix,
                               const Eigen::MatrixXd& constraint_boundary);
  bool AddEqualityConstraint(const Eigen::MatrixXd& constraint_matrix,
                             const Eigen::MatrixXd& constraint_boundary);

  // preset method
  /**
  *   @brief: inequality boundary constraints
  *   if no boundary, do specify either by std::infinity or let vector.size() =
  *0
  **/
  bool Add2dBoundary(const std::vector<double>& t_coord,
                     const std::vector<double>& angle,
                     const std::vector<apollo::common::math::Vec2d>& ref_point,
                     const std::vector<double>& longitidinal_bound,
                     const std::vector<double>& lateral_bound);

  // ref point refer to derivative reference point
  bool Add2dDerivativeBoundary(
      const std::vector<double>& t_coord, const std::vector<double>& angle,
      const std::vector<apollo::common::math::Vec2d>& ref_point,
      const std::vector<double>& longitidinal_bound,
      const std::vector<double>& lateral_bound);

  // ref point refer to second derivative ref point
  bool Add2dSecondDerivativeBoundary(
      const std::vector<double>& t_coord, const std::vector<double>& angle,
      const std::vector<apollo::common::math::Vec2d>& ref_point,
      const std::vector<double>& longitidinal_bound,
      const std::vector<double>& lateral_bound);

  // ref point refer to third derivative ref point
  bool Add2dThirdDerivativeBoundary(
      const std::vector<double>& t_coord, const std::vector<double>& angle,
      const std::vector<apollo::common::math::Vec2d>& ref_point,
      const std::vector<double>& longitidinal_bound,
      const std::vector<double>& lateral_bound);

  bool AddPointConstraint(const double t, const double x, const double y);
  bool AddPointAngleConstraint(const double t, const double angle);

  // guarantee upto values are joint
  bool AddSmoothConstraint();

  // guarantee upto derivative are joint
  bool AddDerivativeSmoothConstraint();

  // guarantee upto second order derivative are joint
  bool AddSecondDerivativeSmoothConstraint();

  // guarantee upto third order derivative are joint
  bool AddThirdDerivativeSmoothConstraint();

  /**
  *   @brief: output interface inequality constraint
  **/
  const AffineConstraint& inequality_constraint() const;
  const AffineConstraint& equality_constraint() const;

 private:
  std::uint32_t FindIndex(const double t) const;
  std::vector<double> AffineCoef(const double angle, const double t) const;
  std::vector<double> AffineDerivativeCoef(const double angle,
                                           const double t) const;
  std::vector<double> AffineSecondDerivativeCoef(const double angle,
                                                 const double t) const;
  std::vector<double> AffineThirdDerivativeCoef(const double angle,
                                                const double t) const;
  std::vector<double> PolyCoef(const double t) const;
  std::vector<double> DerivativeCoef(const double t) const;
  std::vector<double> SecondDerivativeCoef(const double t) const;
  std::vector<double> ThirdDerivativeCoef(const double t) const;
  double SignDistance(const apollo::common::math::Vec2d& xy_point,
                      const double angle) const;

 private:
  AffineConstraint inequality_constraint_;
  AffineConstraint equality_constraint_;
  std::vector<double> t_knots_;
  std::uint32_t spline_order_;
  std::uint32_t total_param_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_
