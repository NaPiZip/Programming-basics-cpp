<img src="http://img.linuxfr.org/img/68747470733a2f2f69736f6370702e6f72672f66696c65732f696d672f746f75722e6a7067/tour.jpg" alt="Book Cover" height="62px" width="42px" align="left"><br><br>

# A tour of C++
<div>
    <a href="https://github.com/NaPiZip/Tipps-and-tricks">
        <img src="https://img.shields.io/badge/Document%20Version-0.0.1-green.svg"/>
    </a>
    <a href="https://www.microsoft.com">
        <img src="https://img.shields.io/badge/Windows%2010%20x64-10.0.17134%20Build%2017134-blue.svg"/>
    </a>
    <a href="https://cmake.org/">
        <img src="https://img.shields.io/badge/CMake-3.15.3-blue"/>
    </a>
    <a href="https://visualstudio.microsoft.com/vs/">
        <img src="https://img.shields.io/badge/Microsoft%20Visual%20Studio-16.3.1-blue"/>
    </a>
</div>

## Introduction
This repository contains brief notes and source files of the book `A Tour of C++` by Bjarne Stroustrup. I created this repository in order to have a centralized space for my code. My notes are not complete by any means, they only consist of content which I thought is helpful.

## Chapter 1: The Basics
The introduction pretty much just contains of basics about types, arithmetic, lifetime and a lot more. Here are some elements worth highlighting.

<b>Initialization</b>
The preferred way for initialization is to use the curly braces as seen below:
```
int i1 = 7.8;        // i1 becomes 7 (surprise?)
int i2 {7.8};        // error: floating-point to integer conversion

complex<double> z2 {d1,d2};
complex<double> z3 = {d1,d2};    // the = is optional with { ... }
vector<int> v {1,2,3,4,5,6};     // a vector of ints
```
This helps to prevent implicit conversation.

<b>Constexpr</b>
`constexpr` is as a guarantee that the function will be computable at compile-time, which opens a lot of possibilities to outsource tasks to the compiler.
```
constexpr double square(double x) { return x*x; }

constexpr double max1 = 1.4*square(17);       // OK 1.4*square(17) is a constant expression
constexpr double max2 = 1.4*square(var);      // error: var is not a constant expression
const double max3 = 1.4*square(var);          // OK, may be evaluated at run time
```
A `constexpr` function is not allowed to have side effects!

<b>Pointers and stuff</b>
When we don’t want to modify an argument but still don’t want the cost of copying, we use a `const` reference to it.
```
double sum(const vector<double>&)
```
## Chapter 2: User-Defined Types
This section contains of typical user defined types such as structures, classes, unions and enums.

<b>Variant</b>
A variant is basically a type save union.
```
#include <variant>
#include <iostream>

auto main() ->int {
  std::variant<int, float> v {3};

  if(std::holds_alternative<int>(v)) {
    std::cout << "Variant is int: " << std::get<int>(v) << "\n";
  }else if (std::holds_alternative<float>(v)) {
    std::cout << "Variant is float: " << std::get<float>(v) << "\n";
  } else {
    std::cout << "Opps something went wrong" << "\n";
  }
}
```

## Chapter 3: Modularity
Covers the separation of declaration and implementation into translation units. `C++20` takes the concept further by introducing modules. The language feature, called modules is not yet ISO C++, but it is an ISO Technical Specification [ModulesTS]. The section also covers exception handling as well as invariants.

<b>Exception handling</b>
An exception is a problem that arises during the execution of a program. A C++ exception is a response to an exceptional circumstance that arises while a program is running,  the issue should be recoverable otherwise we cannot continue the operation of our program. A pretty straight forward example can be seen here:

```
void test()
{
     try{
          Vector v(−27);
     }
     catch (std::length_error&) {   // do something and rethrow
          cerr << "test failed: length error\n";
          throw;   // rethrow
     }
     catch (std::bad_alloc&) {      // Ouch! this program is not designed to handle memory exhaustion
          std::terminate();   // terminate the program
     }
}
```

<b>Structured binding </b>
Like a reference, a structured binding is an alias to an existing object. Unlike a reference, the type of a structured binding does not have to be a reference type.

```
...
std::unordered_map<std::string, float> hash_map;
    hash_map.emplace("Nawin", 12.3f);
    hash_map.emplace("Belen", 23.4f);

    for (auto [name, money] : hash_map) {
      std::cout << name << ' ' << money << "$\n";
    }
...

$ struct_binding.exe
Nawin 12.3$
Belen 23.4$
```

## Tipps

## Topics to dive in deeper
Here is a list of topics I would investigate a bit more in detail:
- Error handling architectures
- Contracts
- Modules

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
