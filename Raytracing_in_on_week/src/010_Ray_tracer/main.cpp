#include "vec3.h"

#include <iostream>
#include <fstream>

auto main() -> int {
  std::ofstream fd("image.ppm", std::ofstream::out);
  constexpr int nx = 200,
                ny = 100;

  fd << "P3\n" << nx << ' ' << ny << "\n255\n";
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float r = static_cast<float>(i) / static_cast<float>(nx);
      float g = static_cast<float>(j) / static_cast<float>(ny);
      float b = 0.2;

      int ir = static_cast<int>(255.99 * r);
      int ig = static_cast<int>(255.99 * g);
      int ib = static_cast<int>(255.99 * b);
      fd << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  fd.close();
  return 0;
}
