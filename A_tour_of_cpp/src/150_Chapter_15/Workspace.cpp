// Copyright 2019, Nawin

#include "Workspace.h"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <thread>

void section_15_2::f() {
  constexpr int RUNS_OF_LOOP = 20;
  for (auto i = 0; i < RUNS_OF_LOOP; ++i)
    std::cout << "This is Thread 1 running ..." << '\n';
}

void section_15_2::F::operator()() {
  constexpr int RUNS_OF_LOOP = 20;
  for (auto i = 0; i < RUNS_OF_LOOP; ++i)
    std::cout << "This is Thread 2 running ..." << '\n';
}


void section_15_3::f(std::vector<double>& v) {
  std::iota(v.begin(), v.end(), 5);
  std::cout << "Task 1 is done sum is: "<< std::accumulate(v.begin(), v.end(), 0.f) << '\n';
}

void section_15_3::F::operator()() {
  std::transform_reduce(data.begin(), data.end(), data.begin(), 2);
  std::cout << "Task 2 is done sum is: " << std::accumulate(data.begin(), data.end(), 0.f) << '\n';
}

void section_15_4::f(const std::vector<double>& v, double* p) {
  *p = std::accumulate(v.begin(), v.end(), 0.f);
}

void section_15_4::F::operator()() {
  *res = std::accumulate(v.begin(), v.end(), 0.f);
}
double section_15_4::g(const std::vector<double>& v) {
  return std::accumulate(v.begin(), v.end(), 0.f);
}

std::mutex m;

void section_15_5::mutext_f(std::vector<double>& v) {
  std::scoped_lock lck{ m };
  section_15_3::f(v);
}

void section_15_5::Mutext_F::operator()() {
  std::scoped_lock lck{ m };
  F::operator()();
}

std::queue<section_15_6::Message> mqueue;
std::condition_variable mcond;
std::mutex mtex;

void section_15_6::consumer() {
  std::chrono::time_point < std::chrono::steady_clock> t0,t1;
  int size = 0;
  while (true) {
    t0 = std::chrono::steady_clock::now();
    std::unique_lock lock{ mtex };
    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
    if (mqueue.empty())
      break;
    auto msg = mqueue.front();
    size = mqueue.size();
    mqueue.pop();
    lock.unlock();
    t1 = std::chrono::steady_clock::now();
    std::cout << msg.get_tag() << msg.get_data() << " of " << size;
    std::cout << " time diff: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << '\n';    
  }
}

void section_15_6::producer() {
  int count{};
  while (true) {    
    std::scoped_lock lock{ mtex };
    mqueue.emplace(Message(std::string("Something: "), count++));
    mcond.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds{ 100});
    if (count >= 10)
      break;
  }
}

void section_15_7::f(std::promise<std::string>& px) {
  try {
    std::string result{ "A string to promise" };
    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
    px.set_value(result);
  }
  catch (...) {
    px.set_exception(std::current_exception());
  }
}

void section_15_7::g(std::future<std::string>& fx) {
  try {
    std::string v = fx.get();
    std::cout << v << '\n';
  } catch (...)
  {
   //
  }
}


double section_15_7::accumu(double* beg, double* end, double init) {
  return std::accumulate(beg, end, init);
}

double section_15_7::comp2(std::vector<double>& v) {
  using Task_type = double(double*, double*, double);
  std::packaged_task<Task_type> pt0{ accumu };
  std::packaged_task<Task_type> pt1{ accumu };

  std::future<double> f0{ pt0.get_future() };
  std::future<double> f1{ pt1.get_future() };

  double* first = &v[0];
  std::thread t1{ std::move(pt0), first, first + v.size() / 2, 0 };
  std::thread t2{ std::move(pt1), first + v.size() / 2, first + v.size(),0 };

  t1.join();
  t2.join();
   
  return f0.get() + f1.get();
}


double section_15_7::comp4(std::vector<double>& v) {
  if (v.size() < 1000)
    return std::accumulate(v.begin(), v.end(), 0.0);

  auto v0 = &v[0];
  auto sz = v.size();

  auto f0 = std::async(accumu, v0, v0 + sz / 4, 0.0);          // first quarter
  auto f1 = std::async(accumu, v0 + sz / 4, v0 + sz / 2, 0.0);     // second quarter
  auto f2 = std::async(accumu, v0 + sz / 2, v0 + sz * 3 / 4, 0.0);   // third quarter
  auto f3 = std::async(accumu, v0 + sz * 3 / 4, v0 + sz, 0.0);     // fourth quarter

  return f0.get() + f1.get() + f2.get() + f3.get();
}