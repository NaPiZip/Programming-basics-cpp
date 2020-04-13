// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <iostream>
#include <vector>
#include <map>

struct Point {
  int x_, y_;
  friend std::size_t hash_value(const Point& obj);
};

struct Line {
  Point begin_, end_;
  friend std::size_t hash_value(const Line& obj);
};

struct VectorObject {
  virtual std::vector<Line>::iterator begin() = 0;
  virtual std::vector<Line>::iterator end() = 0;
};


struct VectorRectangle : public VectorObject {
private:
  std::vector<Line> lines_;

public:
  VectorRectangle(Point p, int width, int height);
  std::vector<Line>::iterator begin() override;
  std::vector<Line>::iterator end() override;
};

// Drawing dummy struct
struct CPaintDC {
  void SetPixel(int x, int y);
};

void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end);

struct LineToPointAdapter {
  using Points = std::vector<Point>;
  LineToPointAdapter(Line& line);
  void LineToPointCachingAdapter(Line& line);
  virtual Points::iterator begin();
  virtual Points::iterator end();

private:
  static std::map<size_t, Points> cache;
  static size_t line_hash;
  Points points_;
};
#endif // _HEADER_WORKSPACE
