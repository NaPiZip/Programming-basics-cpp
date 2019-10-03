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

## Chapter 1: Introduction
The introduction pretty much just contains of basics about types, arithmetic, lifetime and a lot more. Here are some elements worth highlighting.

<b>Initialization:</b>
The preferred way for initialization is to use the curly braces as seen below:
```
int i1 = 7.8;        // i1 becomes 7 (surprise?)
int i2 {7.8};        // error: floating-point to integer conversion

complex<double> z2 {d1,d2};
complex<double> z3 = {d1,d2};    // the = is optional with { ... }
vector<int> v {1,2,3,4,5,6};     // a vector of ints
```
This helps to prevent implicit conversation.

<b>Constexpr:</b>
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

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
