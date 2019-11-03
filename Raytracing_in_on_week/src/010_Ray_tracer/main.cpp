#include "vec3.h"

#include <iostream>
#include <fstream>

auto main() -> int {
  std::ofstream fd("image2.ppm", std::ofstream::out);
  constexpr int nx = 200,
                ny = 100;

  fd << "P3\n" << nx << ' ' << ny << "\n255\n";
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col{ static_cast<double>(i) / static_cast<double>(nx),
                static_cast<double>(j) / static_cast<double>(ny),
                0.2 };

      int ir = static_cast<int>(255.99 * col[0]);
      int ig = static_cast<int>(255.99 * col[1]);
      int ib = static_cast<int>(255.99 * col[2]);
      fd << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  fd.close();
  return 0;
}
