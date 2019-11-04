#include "vec3.h"
#include "ray.h"
#include "utils.h"

#include <iostream>
#include <fstream>


auto main() -> int {
  std::ofstream fd("image2.ppm", std::ofstream::out);
  constexpr int nx = 200,
                ny = 100;

  fd << "P3\n" << nx << ' ' << ny << "\n255\n";

  /*
      ( -2, 1,-1 )-----------------------( 2, 1,-1 )
                 |                      | 
                 |                      | y
                 |         (0,0,0)      | ^
                 |                      | |
                 |                      | |--> x
                 |                      |                
      ( -2,-1,-1 )-----------------------( 2,-1,-1 )
  
  */
  vec3  lower_left_corner(-2., -1., -1.),
        horizontal(4., 0., 0.),
        vertical(0., 2., 0.),
        origin(0., 0., 0.);

  
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      double u = static_cast<double>(i) / static_cast<double>(nx),
             v = static_cast<double>(j) / static_cast<double>(ny);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 col = color(r);
      int ir = static_cast<int>(255.99 * col[0]);
      int ig = static_cast<int>(255.99 * col[1]);
      int ib = static_cast<int>(255.99 * col[2]);
      fd << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  fd.close();
  return 0;
}
