#include <celero/Celero.h>

#ifndef WIN32
#include <cmath>
#include <cstdlib>
#endif

#include <vector>
#include <algorithm>
#include <execution>


#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include "camera.h"
#include "rand.h"
#include "lambertian.h"




#include <corecrt_math_defines.h>
///
/// This is the main(int argc, char** argv) for the entire celero program.
/// You can write your own, or use this macro to insert the standard one into the project.
///
CELERO_MAIN


hittable<double>* create_hittable(int nx , int ny, int ns) {
  double R = cos(M_PI / 4);  

  hittable<double>** list = new hittable<double>* [2];

  list[0] = new sphere(vec3(-R, 0.0, -1.0), R, new lambertian(vec3(0.0, 0.0, 1.0)));
  list[1] = new sphere(vec3(R, 0.0, -1.0), R, new lambertian(vec3(1.0, 0.0, 0.0)));

  return new hittable_list(list, 2);
}

BASELINE(InnerLoopNx, Baseline, 300, 1000)
{
  constexpr int nx = 200,
                ny = 100,
                ns = 10;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
            v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;
  
}

BENCHMARK(InnerLoopNx, Ns20, 300, 1000)
{
  constexpr int nx = 100,
    ny = 200,
    ns = 20;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;

}

BENCHMARK(InnerLoopNx, Nx200, 300, 1000)
{
  constexpr int nx = 200,
    ny = 200,
    ns = 20;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;

}

BENCHMARK(InnerLoopNx, Nx400, 300, 1000)
{
  constexpr int nx = 400,
    ny = 200,
    ns = 20;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;

}

BENCHMARK(InnerLoopNx, Ns40, 300, 1000)
{
  constexpr int nx = 200,
    ny = 200,
    ns = 40;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;

}

BASELINE(ColorLoop, Baseline, 300, 2000)
{
  constexpr int nx = 200,
    ny = 200,
    ns = 100;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  for (int s = 0; s < ns; s++) {
    double  u = static_cast<double>(s + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(s + random<double>()) / static_cast<double>(ny);
    col += color(cam.get_ray(u, v), world, 0);
  }
  col /= ns;

}


BENCHMARK(ColorLoop, StdAlgorithm, 300, 2000)
{
  constexpr int nx = 200,
    ny = 200,
    ns = 100;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);

  vec3<double> a[ns];
  std::for_each(std::begin(a), std::end(a), [&](vec3<double>& in) {
    double u = static_cast<double>(1 + random<double>()) / static_cast<double>(nx),
           v = static_cast<double>(1 + random<double>()) / static_cast<double>(ny);
    ray r = cam.get_ray(u, v);
    in = color(r, world, 0); });

  col = std::accumulate(std::begin(a), std::end(a), vec3<double>{0.0, 0.0, 0.0});

  col /= ns;
}

BENCHMARK(ColorLoop, StdAlgorithmParalel, 300, 2000)
{
  constexpr int nx = 200,
    ny = 200,
    ns = 100;
  hittable<double>* world = create_hittable(nx, ny, ns);

  camera cam(vec3(-2.0, 2.0, 1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(0.0, 1.0, 0.0),
    60.0, static_cast<double>(nx / ny));

  vec3 col(0.0, 0.0, 0.0);
  
  vec3<double> a[ns];
  std::for_each(std::execution::par, std::begin(a), std::end(a), [&](vec3<double>& in) {
    double u = static_cast<double>(1 + random<double>()) / static_cast<double>(nx),
      v = static_cast<double>(1 + random<double>()) / static_cast<double>(ny);
    ray r = cam.get_ray(u, v);
    in = color(r, world, 0); });

  col = std::accumulate(std::begin(a), std::end(a), vec3<double>{0.0, 0.0, 0.0});

  col /= ns;
}
