#include <loop_device.hxx>
#include <vect.hxx>

#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>

namespace ErrorEstimator {
using namespace Loop;

enum class shape_t { sphere, cube, boxes };

template <typename T> constexpr T radius_sphere(const vect<T, dim> &X) {
  using std::sqrt;
  return sqrt(sum(pow2(X)));
}

template <typename T> constexpr T radius_cube(const vect<T, dim> &X) {
  using std::abs;
  return maximum(abs(X));
}

template <typename T> constexpr T radius_boxes(const vect<T, dim> &X) {
  using std::abs;
  using std::fmin;
  const vect<T, dim> p1{1, 0, 1};
  const vect<T, dim> p2{-1, 0, 1};
  return fmin(maximum(abs(X - p1)), maximum(abs(X - p2)));
}

template <typename T, int CI, int CJ, int CK>
T lap(const GF3D<const T, CI, CJ, CK> &var, const vect<int, dim> &I) {
  const auto DI = vect<int, dim>::unit(0);
  const auto DJ = vect<int, dim>::unit(1);
  const auto DK = vect<int, dim>::unit(2);
  using std::fabs;
  return fabs(var(I - DI) - 2 * var(I) + var(I + DI)) +
         fabs(var(I - DJ) - 2 * var(I) + var(I + DJ)) +
         fabs(var(I - DK) - 2 * var(I) + var(I + DK));
}

extern "C" void ErrorEstimator_Estimate(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_ErrorEstimator_Estimate;
  DECLARE_CCTK_PARAMETERS;

  const vect<int, dim> ones{1, 1, 1};
  const vect<int, dim> levfac{cctk_levfac[0], cctk_levfac[1], cctk_levfac[2]};
  const vect<int, dim> scalefactors = scale_by_resolution ? levfac : ones;

  const std::array<int, dim> indextype = {1, 1, 1};
  const GF3D2layout layout(cctkGH, indextype);
  const GF3D2<CCTK_REAL> regrid_error_(layout, regrid_error);

  const shape_t shape = [&]() {
    if (CCTK_EQUALS(region_shape, "sphere"))
      return shape_t::sphere;
    if (CCTK_EQUALS(region_shape, "cube"))
      return shape_t::cube;
    if (CCTK_EQUALS(region_shape, "boxes"))
      return shape_t::boxes;
    std::abort();
  }();

  const GridDescBaseDevice grid(cctkGH);
  grid.loop_int_device<1, 1, 1>(
      grid.nghostzones,
      [=] CCTK_DEVICE(const PointDesc &p) CCTK_ATTRIBUTE_ALWAYS_INLINE {
        const CCTK_REAL r = [&]() {
          switch (shape) {
          case shape_t::sphere:
            return radius_sphere(scalefactors * p.X);
          case shape_t::cube:
            return radius_cube(scalefactors * p.X);
          case shape_t::boxes:
            return radius_boxes(scalefactors * p.X);
          default:
            assert(0);
          };
        }();
        using std::max;
        const CCTK_REAL err = 1 / max(r, epsilon);
        regrid_error_(p.I) = err;
      });
}

} // namespace ErrorEstimator
