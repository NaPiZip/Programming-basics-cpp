// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>

struct Person {
  void greet();

  Person(std::string);
  ~Person();

  struct PersonImpl;
  PersonImpl* pimpl_;
};


struct Renderer {
  virtual void render_circle(float, float, float) = 0;
};

struct VectorRenderer : public Renderer {
  void render_circle(float, float, float) override;
};

struct RasterRenderer : Renderer {
  void render_circle(float, float, float) override;
};

struct Shape {
protected:
  Renderer& renderer_;
  Shape(Renderer& renderer) : renderer_{ renderer } {}

public:
  virtual void draw() = 0;
  virtual void resize(float) = 0;
};

struct Circle : public Shape {
  float x_, y_, radius_;
  void draw() override;
  void resize(float) override;
  Circle(Renderer& renderer, float x, float y, float radius) : Shape{ renderer }, x_{ x }, y_{ y }, radius_{ radius } {}
};
#endif // _HEADER_WORKSPACE
