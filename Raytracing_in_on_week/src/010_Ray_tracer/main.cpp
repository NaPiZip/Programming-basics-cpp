#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include "camera.h"
#include "rand.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#include <iostream>
#include <fstream>
#include <string>

using std::string_literals::operator""s;

auto main() -> int {
  constexpr int nx = 400,
                ny = 200,
                ns = 30;
  std::ofstream fd("image ns_"s+ std::to_string(ns) +".ppm"s, std::ofstream::out);
  fd << "P3\n" << nx << ' ' << ny << "\n255\n";
 
  camera cam( vec3(-2.0, 2.0, 1.0),
              vec3(0.0, 0.0, -1.0),
              vec3(0.0, 1.0, 0.0),
              20.0, static_cast<double>(nx /ny));


  hittable<double>* list[5];
  /*double R = cos(M_PI / 4);
  list[0] = new sphere(vec3(-R, 0.0, -1.0), R, new lambertian(vec3(0.0, 0.0, 1.0)));
  list[1] = new sphere(vec3(R, 0.0, -1.0), R, new lambertian(vec3(1.0, 0.0, 0.0)));
  */
  list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5, new lambertian(vec3{ 0.1, 0.2, 0.5 }));
  list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0, new lambertian(vec3{ 0.8, 0.8, 0.0 }));
  list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5, new metal(vec3{ 0.8, 0.6, 0.2 }, 0.3));
  list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5, new dielectric(1.35));
  list[4] = new sphere(vec3(-1.0, 0.0, -1.0), -0.45, new dielectric(1.35));
  
  hittable<double>* world = new hittable_list(list, 5);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);
      for (int s = 0; s < ns; s++) {
        double u = static_cast<double>(i + random<double>()) / static_cast<double>(nx),
               v = static_cast<double>(j + random<double>()) / static_cast<double>(ny);
        ray r = cam.get_ray(u, v);
        col += color(r, world,0);
      }
      col /= ns;
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

      int ir = static_cast<int>(255.99 * col[0]);
      int ig = static_cast<int>(255.99 * col[1]);
      int ib = static_cast<int>(255.99 * col[2]);
      fd << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  fd.close();
  return 0;
}
