// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <vector>
#include <string_view>
#include <chrono>
#include <future>


namespace section_15_2 {
void f();
struct F {
  void operator()();
};  
}  //  namespace section_15_2 

namespace section_15_3 {
void f(std::vector<double>& v);

struct F {
  std::vector<double> data;
  F(std::vector<double>& vv) : data{ vv } {}
  void operator()();
};
}  //  namespace section_15_3


namespace section_15_4 {
void f(const std::vector<double>& v, double* res);
double g(const std::vector<double>& v);
class F {
public:
  F(const std::vector<double>& vv, double* p) : v{ vv }, res{ p } {}
  void operator()();

private:
  const std::vector<double>& v;
  double* res;
};
}  //  namespace section_15_4 

namespace section_15_5 {
  void mutext_f(std::vector<double>& v);
  struct Mutext_F: public section_15_3::F {
    Mutext_F(std::vector<double>& vv): F(vv) {}
    void operator()();
  };
}  //  namespace section_15_5 

namespace section_15_6 {
class Message {
public:
  Message(std::string& str, int val) : tag{ str }, data{ val } {}
  const std::string_view get_tag() { return tag; }
  int get_data() { return data; }
private:
  std::string tag;
  int data;
};

void producer();
void consumer();


}  //  namespace section_15_6

namespace section_15_7 {
  void f(std::promise<std::string>& px);
  void g(std::future<std::string>& fx);

  double accumu(double* beg, double* end, double init);
  double comp2(std::vector<double>& v);
  double comp4(std::vector<double>& v);
}  //  namespace section_15_7

#endif  // _HEADER_WORKSPACE
