// Copyright 2019, Nawin

#include "Workspace.h"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <numeric>
#include <iostream>

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
    mcond.wait(lock, []() {return !mqueue.empty(); });
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
  }
}
