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

#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <execution>

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
  constexpr int nx = 200,
                ny = 100,
                ns = 1;
  std::ofstream fd("image ns_"s+ std::to_string(ns) +".ppm"s, std::ofstream::out);
  fd << "P3\n" << nx << ' ' << ny << "\n255\n";
 
  camera cam( vec3(-2.0, 2.0, 1.0),
              vec3(0.0, 0.0, -1.0),
              vec3(0.0, 1.0, 0.0),
              60.0, static_cast<double>(nx /ny));

  std::chrono::high_resolution_clock::time_point t1, t0;

  hittable<double>* world = random_scene(); // new hittable_list(list, 5);

  t0 = std::chrono::high_resolution_clock::now();

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);
      
      /*
      vec3<double> a[ns];
      std::for_each(std::begin(a), std::end(a), [&] (vec3<double>& in) {
        double u = static_cast<double>(i + random<double>()) / static_cast<double>(nx),
               v = static_cast<double>(j + random<double>()) / static_cast<double>(ny);
        ray r = cam.get_ray(u, v);
        in = color(r, world, 0);});
      
      col = std::accumulate(std::begin(a), std::end(a), vec3<double>{0.0, 0.0, 0.0});

      col /= ns;
      */
          
      for (int s = 0; s < ns; s++) {
        double u = static_cast<double>(i + random<double>()) / static_cast<double>(nx),
               v = static_cast<double>(j + random<double>()) / static_cast<double>(ny);
        col += color(cam.get_ray(u, v), world,0);
      }
      col /= ns;
      
      fd << static_cast<int>(255.99 * sqrt(col[0])) << ' '
         << static_cast<int>(255.99 * sqrt(col[1])) << ' '
         << static_cast<int>(255.99 * sqrt(col[2])) << '\n';
    }
  }
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Elapsed time for random_scene: " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << " s \n";

  fd.close();
  return 0;
}
