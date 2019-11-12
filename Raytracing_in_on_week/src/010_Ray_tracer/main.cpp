#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include "camera.h"
#include "rand.h"

#include <iostream>
#include <fstream>
#include <string>

using std::string_literals::operator""s;

auto main() -> int {
  constexpr int nx = 400,
                ny = 200,
                ns = 100;
  std::ofstream fd("image ns_"s+ std::to_string(ns) +".ppm"s, std::ofstream::out);
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
  camera cam;

  hittable<double>* list[2];
  list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
  list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);

  hittable<double>* world = new hittable_list(list, 2);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);
      for (int s = 0; s < ns; s++) {
        double u = static_cast<double>(i + random<double>()) / static_cast<double>(nx),
               v = static_cast<double>(j + random<double>()) / static_cast<double>(ny);
        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }
      col /= ns;

      int ir = static_cast<int>(255.99 * col[0]);
      int ig = static_cast<int>(255.99 * col[1]);
      int ib = static_cast<int>(255.99 * col[2]);
      fd << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  fd.close();
  return 0;
}
