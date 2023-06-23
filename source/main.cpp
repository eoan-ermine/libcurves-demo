#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include <libcurves/libcurves.hpp>

constexpr auto MIN_OBJECTS = 1, MAX_OBJECTS = 10;
constexpr auto MIN_RADIUS = 1, MAX_RADIUS = 1000;
constexpr auto MIN_STEP = -1000, MAX_STEP = 1000;

auto main() -> int
{
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_int_distribution<int> objects_distribution(MIN_OBJECTS,
                                                          MAX_OBJECTS);

  std::vector<std::shared_ptr<curve<double>>> curves;

  // Populate a container (e.g. vector or list) of objects of these types
  // created in random manner with random parameters
  {
    // Insert circles
    for (auto count = objects_distribution(gen); count != 0; --count) {
      std::uniform_int_distribution<int> radius_distribution(MIN_RADIUS,
                                                             MAX_RADIUS);
      curves.push_back(std::shared_ptr<curve<double>>(
          new circle<double>(radius_distribution(gen))));
    }

    // Insert ellipses
    for (auto count = objects_distribution(gen); count != 0; --count) {
      std::uniform_int_distribution<int> radii_distribution(MIN_RADIUS,
                                                            MAX_RADIUS);
      curves.push_back(std::shared_ptr<curve<double>>(new ellipse<double>(
          radii_distribution(gen), radii_distribution(gen))));
    }

    // Insert helixes
    for (auto count = objects_distribution(gen); count != 0; --count) {
      std::uniform_int_distribution<int> radius_distribution(MIN_RADIUS,
                                                             MAX_RADIUS);
      std::uniform_int_distribution<int> step_distribution(MIN_STEP, MAX_STEP);
      curves.push_back(std::shared_ptr<curve<double>>(
          new helix<double>(radius_distribution(gen), step_distribution(gen))));
    }
  }

  // Print coordinates of points and derivatives of all curves in the
  // container at t = pi/4
  {
    const double parameter = std::numbers::pi / 4;
    for (const auto& obj : curves) {
      const auto& point = obj->get_point(parameter);
      const auto& derivative = obj->get_derivative(parameter);
      std::cout << "Point: (" << point.x() << ", " << point.y() << ", "
                << point.z() << ") "
                << "derivative: {" << derivative(0) << ", " << derivative(1)
                << ", " << derivative(2) << '}' << std::endl;
    }
  }

  // Populate a second container that would contain only circles from the
  // first container. Make sure the second container shares (i.e. not clones)
  // circles of the first one, e.g. via pointers

  std::vector<std::shared_ptr<curve<double>>> circles;
  {
    for (const auto& obj : curves) {
      if (obj->get_type() == curve<double>::type::circle) {
        circles.push_back(obj->shared_from_this());
      }
    }
  }

  // Sort the second container in the ascending order of circles' radii
  // That is, the first element has the smallest radius, the last — the greatest
  {
    std::sort(circles.begin(),
              circles.end(),
              [](const auto& lhs, const auto& rhs)
              { return lhs->get_radii_sum() < rhs->get_radii_sum(); });
  }

  // Compute the total sum of radii of all curves in the second container
  double sum_of_radii = 0;
  {
    for (const auto& obj : circles) {
      sum_of_radii += obj->get_radii_sum();
    }
    std::cout << "The sum of the radii of all circles: " << sum_of_radii
              << std::endl;
  }

  return 0;
}
