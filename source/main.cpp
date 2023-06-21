#include <libcurves/libcurves.hpp>

#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <memory>

auto main() -> int
{
  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_real_distribution<int> objects_distribution(1, 10);

  std::vector<std::shared_ptr<curve<double>>> curves;

  // Populate a container (e.g. vector or list) of objects of these types
  // created in random manner with random parameters
  {
    // Insert circles
    {
      for (auto count = objects_distribution(); count != 0; --count) {
        std::uniform_real_distribution<int> radius_distribution(1, 1000);
        curves.push_back(std::shared_ptr<curve>(new circle<double>(radius_distribution())));
      }
    }

    // Insert ellipses
    {
      for (auto count = objects_distribution(); count != 0; --count) {
        std::uniform_real_distribution<int> radii_distribution(1, 1000);
        curves.push_back(std::shared_ptr<curve>(
          new ellipse<double>(radii_distribution(), radii_distribution())
        ));
      }
    }

    // Insert helixes
    {
      for (auto count = objects_distribution(); count != 0; --count) {
        std::uniform_real_distribution<int> radius_distribution(1, 1000);
        std::uniform_real_distribution<int> step_distribution(-1000, 1000);
        curves.push_back(std::shared_ptr<curve>(
          new helix<double>(radius_distribution(), step_distribution())
        ));
      }
    }
  }

  // Print coordinates of points and derivatives of all curves in the
  // container at t = pi/4
  {
    double t = std::numbers::pi;
    for (const auto& curve: curves) {
      std::cout << "Point: " << curve.get_point(t) << ", derivative: " << curve.get_derivative(t) << std::endl;
    }
  }

  // Populate a second container that would contain only circles from the
  // first container. Make sure the second container shares (i.e. not clones)
  // circles of the first one, e.g. via pointers

  std::vector<std::shared_ptr<curve<double>>> circles;
  {
    for (const auto& curve: curves) {
      if (curve.get_type() == curve<double>::type::circle) {
       circles.push_back(curve.get()->shared_from_this()); 
      }
    }
  }

  // Sort the second container in the ascending order of circles' radii
  // That is, the first element has the smallest radius, the last — the greatest
  {
    std::sort(circles.begin(), circles.end(), [](const auto& lhs, const auto& rhs) {
      return lhs.radius < rhs.radius;
    });
  }

  // Compute the total sum of radii of all curves in the second container
  {
    for (const auto& curve: curves) {
      double sum_of_radii = 0;
      if (curve.get_type() == curve<double>::type::circle) {
        // TODO
      }
      else if (curve.get_type() == curve<double>::type::ellipse) {
        // TODO
      }
      else if (curve.get_type() == curve<double>::type::helix) {
        // TODO
      }
    }
  }

  return 0;
}
