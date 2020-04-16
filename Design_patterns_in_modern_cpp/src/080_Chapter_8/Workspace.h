// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <array>
#include <string>
#include <memory>
#include <vector>
class Creature {
  enum Abilities { str,
    agl,
    intl,
    count };
  std::array<int, count> abilities_;

public:
  int get_strength() const;
  void set_strength(int);
  double average() const;

  int sum() const;
};

struct GraphicObject {
  virtual void draw() = 0;
};

struct Circle : GraphicObject {
  void draw() override;
};

struct Group : GraphicObject {
  std::string name_;
  std::vector<std::shared_ptr<GraphicObject>> objects_;

  explicit Group(const std::string& name) : name_{ name } {}
  void draw() override;
};


struct Neuron {
  std::vector<Neuron*> in_, out_;
  unsigned int id_;

  Neuron() {
    static int id = 1;
    id_ = id++;
  }

  void connect_to(Neuron& other);
};


struct NeuronLayer : std::vector<Neuron> {
  NeuronLayer(int);
};

template <typename Self>
struct SomeNeurons {
  template <typename T>
  void connect_to(T& other) {
    for (Neuron& from : *static_cast<Self*>(this)) {
      for (Neuron& to : other) {
        from.out_.push_back(&to);
        to.in_.push_back(&from);
      }
    }
  }
};
#endif // _HEADER_WORKSPACE
