// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <memory>
#include <string>
#include <map>
#include <functional>

class PointFactory;

struct Point {
protected:
  float x_, y_;
  friend class PointFactory;

private:
  Point(float x, float y) : x_{ x }, y_{ y } {}
};

struct PointFactory {
  static Point NewCartesian(float, float);
  static Point NewPolar(float, float);
};


struct InnerPoint {
protected:
  float x_, y_;

private:
  InnerPoint(float x, float y) : x_{ x }, y_{ y } {}

public:
  using Factory = PointFactory;
  struct PointFactory {
    static InnerPoint NewCartesian(float, float);
    static InnerPoint NewPolar(float, float);
  };
};

struct HotDrink {
  virtual void prepare(int) = 0;
};

struct Tea : public HotDrink {
  void prepare(int) override;
};

struct Coffee : public HotDrink {
  void prepare(int) override;
};


std::unique_ptr<HotDrink> make_drink(std::string type);

struct HotDrinkFactory {
  virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : public HotDrinkFactory {
  std::unique_ptr<HotDrink> make() const override;
};

struct TeaFactory : public HotDrinkFactory {
  std::unique_ptr<HotDrink> make() const override;
};

class DrinkFactory {
  std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
  DrinkFactory();
  std::unique_ptr<HotDrink> make_drink(const std::string& name);
};

class DrinkWithVolumeFactory {
  std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public:
  DrinkWithVolumeFactory();
  inline std::unique_ptr<HotDrink> make_drink(const std::string& name) {
    return factories[name]();
  }
};
#endif // _HEADER_WORKSPACE
