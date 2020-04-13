// Copyright 2019, Nawin

#include "Workspace.h"
#include <algorithm>

#include <boost/container_hash/hash.hpp>

std::size_t hash_value(const Point& obj) {
  std::size_t seed = 0x725c686f;
  boost::hash_combine(seed, obj.x_);
  boost::hash_combine(seed, obj.y_);
  return seed;
}

std::size_t hash_value(const Line& obj) {
  std::size_t seed = 0x719e6b16;
  boost::hash_combine(seed, obj.begin_);
  boost::hash_combine(seed, obj.end_);
  return seed;
}

VectorRectangle::VectorRectangle(Point p, int width, int height) {
  lines_.emplace_back(Line{ p,
      { p.x_ + width, p.y_ } });
  lines_.emplace_back(Line{ { p.x_ + width, p.y_ },
      { p.x_ + width, p.y_ + height } });
  lines_.emplace_back(Line{ { p.x_ + width, p.y_ + height },
      { p.x_, p.y_ + height } });
  lines_.emplace_back(Line{ { p.x_, p.y_ + height },
      { p.x_, p.y_ } });
}

std::vector<Line>::iterator VectorRectangle::begin() {
  return lines_.begin();
}

std::vector<Line>::iterator VectorRectangle::end() {
  return lines_.end();
}

void CPaintDC::SetPixel(int x, int y) {
  std::cout << '(' << x << '/' << y << ") ";
}
void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
  for (auto i = start; i != end; ++i) {
    dc.SetPixel(i->x_, i->y_);
  }
}

LineToPointAdapter::LineToPointAdapter(Line& line) {
  int left = std::min(line.begin_.x_, line.end_.x_);
  int right = std::max(line.begin_.x_, line.end_.x_);
  int top = std::min(line.begin_.y_, line.end_.y_);
  int bottom = std::max(line.begin_.y_, line.end_.y_);
  int dx = right - left;
  int dy = bottom - top;

  //only vertical
  if (!dx) {
    for (int y = top; y <= bottom; ++y)
      points_.emplace_back(Point{ left, y });
  }
  else if (!dy) {
    for (int x = left; x <= right; ++x)
      points_.emplace_back(Point{ x, top });
  }
}

std::map<size_t, LineToPointAdapter::Points> LineToPointAdapter::cache{};
size_t LineToPointAdapter::line_hash{};

LineToPointAdapter::Points::iterator LineToPointAdapter::begin() {
  return cache[line_hash].begin();
}
LineToPointAdapter::Points::iterator LineToPointAdapter::end() {
  return cache[line_hash].end();
}
void LineToPointAdapter::LineToPointCachingAdapter(Line& line) {
  static boost::hash<Line> hash;
  line_hash = hash(line);
  if (cache.find(line_hash) != cache.end())
    return;

  //.. TL;DR
}
