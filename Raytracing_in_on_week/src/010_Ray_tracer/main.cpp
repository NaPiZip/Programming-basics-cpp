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

hittable<double>* random_scene() {
  const int n = 500;
  hittable<double>** list = new hittable<double>*[n + 1];
  list[0] = new sphere(vec3(0.0, -1000.0, 0.0), 1000.0, new lambertian(vec3(0.5, 0.5, 0.5)));
  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      double choose_mat = random<double>();
      vec3 center(a + 0.9 * random<double>(), 0.2, b + 0.9 * random<double>());
      if ((center - vec3(4.0, 0.2, 0.0)).length() > 0.9) {
        if (choose_mat < 0.8) {  // diffuse
          list[i++] = new sphere(center, 0.2,
            new lambertian(vec3(random<double>() * random<double>(),
              random<double>() * random<double>(),
              random<double>() * random<double>())
            )
          );
        }
        else if (choose_mat < 0.95) { // metal
          list[i++] = new sphere(center, 0.2,
            new metal(vec3(0.5 * (1 + random<double>()),
              0.5 * (1 + random<double>()),
              0.5 * (1 + random<double>())),
              0.5 * random<double>()));
        }
        else {  // glass
          list[i++] = new sphere(center, 0.2, new dielectric(1.5));
        }
      }
    }
  }

  list[i++] = new sphere(vec3(0.0, 1.0, 0.0), 1.0, new dielectric(1.5));
  list[i++] = new sphere(vec3(-4.0, 1.0, 0.0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
  list[i++] = new sphere(vec3(4.0, 1.0, 0.0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

  return new hittable_list(list, i);
}


auto main() -> int {
  constexpr int nx = 600,
                ny = 300,
                ns = 1;
  std::ofstream fd("image ns_"s+ std::to_string(ns) +".ppm"s, std::ofstream::out);
  fd << "P3\n" << nx << ' ' << ny << "\n255\n";
 
  camera cam( vec3(-2.0, 2.0, 1.0),
              vec3(0.0, 0.0, -1.0),
              vec3(0.0, 1.0, 0.0),
              60.0, static_cast<double>(nx /ny));


  hittable<double>* list[5];

  list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5, new lambertian(vec3{ 0.1, 0.2, 0.5 }));
  list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0, new lambertian(vec3{ 0.8, 0.8, 0.0 }));
  list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5, new metal(vec3{ 0.8, 0.6, 0.2 }, 0.3));
  list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5, new dielectric(1.35));
  list[4] = new sphere(vec3(-1.0, 0.0, -1.0), -0.45, new dielectric(1.35));
  
  hittable<double>* world = random_scene(); // new hittable_list(list, 5);

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
