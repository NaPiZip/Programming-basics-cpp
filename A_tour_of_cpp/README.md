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

<b>Initialization</b><br>
The preferred way for initialization is to use the curly braces as seen below:
```
int i1 = 7.8;        // i1 becomes 7 (surprise?)
int i2 {7.8};        // error: floating-point to integer conversion

complex<double> z2 {d1,d2};
complex<double> z3 = {d1,d2};    // the = is optional with { ... }
vector<int> v {1,2,3,4,5,6};     // a vector of ints
```
This helps to prevent implicit conversation.

<b>Constexpr</b><br>
`constexpr` is as a guarantee that the function will be computable at compile-time, which opens a lot of possibilities to outsource tasks to the compiler.
```
constexpr double square(double x) { return x*x; }

constexpr double max1 = 1.4*square(17);       // OK 1.4*square(17) is a constant expression
constexpr double max2 = 1.4*square(var);      // error: var is not a constant expression
const double max3 = 1.4*square(var);          // OK, may be evaluated at run time
```
A `constexpr` function is not allowed to have side effects!

<b>Pointers and stuff</b><br>
When we don’t want to modify an argument but still don’t want the cost of copying, we use a `const` reference to it.
```
double sum(const vector<double>&)
```
## Chapter 2: User-Defined Types
This section contains of typical user defined types such as structures, classes, unions and enums.

<b>Variant</b><br>
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

<b>Exception handling</b><br>
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

<b>Structured binding </b><br>
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

## Chapter 4: Classes
A class is a user-defined type provided to represent a concept in the code of a program. This section covers mainly tree parts:<br>
- Concrete classes
- Abstract classes
- Class hierarchies

<b>Concrete classes</b><br>
The idea of concrete classes is to mimic the behavior of built-in types, code can be found under `src/040_Chapter_4`, since this is pretty straight forward so far.

<b>Abstract classes</b><br>
"Abstract classes act as expressions of general concepts from which more specific classes can be derived. You cannot create an object of an abstract class type; however, you can use pointers and references to abstract class types", link can be found [here](https://docs.microsoft.com/en-us/cpp/cpp/abstract-classes-cpp?view=vs-2019).

```
class Container {
 public:
  virtual double& operator[](int) = 0;
  virtual int size() const = 0;
  virtual ~Container() {}
};
```

<b>Class hierarchies</b><br>
A class hierarchy is a set of classes ordered in a lattice created by derivation (e.g., : public). Benefits:
- Interface inheritance<br>
An object of a derived class can be used with the a base class pointer.<br>
- Implementation inheritance<br>
A base class provides functions or data that simplifies the implementation of derived classes.

<b>Run-time Type Identification RTTI</b><br>
RTTI is to provide a standard way for a program to determine the type of object during runtime, and is often used in context with polymorphism.

```
class Base {virtual void use(){}};

class Derived : public Base { };

int main()
{
	Base base;
	Derived derived;

	Base *pb = dynamic_cast<Base*>(&derived);		  // #1
	Derived *pd = dynamic_cast<Derived*>(&base); 	// #2 fails

  // check pointer after casting!!
  if(pd)
    pd->use();

	return 0;
}
```

## Chapter 5: Essential Operations

<b>Assignment, copy and initialization</b><br>
There are multiple ways a user defined type gets created:
```
class X {
public:
     X(Sometype);            // "ordinary constructor": create an object
     X();                    // default constructor
     X(const X&);            // copy constructor
     X(X&&);                 // move constructor
     X& operator=(const X&); // copy assignment: clean up target and copy
     X& operator=(X&&);      // move assignment: clean up target and move
     ~X();                   // destructor: clean up
     // ...
};
```
<b>Default operations and deleted ones</b><br>
The keywords `delete` and `default` in a context of a user defined class can be used in order to prevent operations and or to use default compiler implementations. As a rule of thumb when a class has a pointer member, it is usually a good idea to be explicit about copy and move operations. The reason is that a pointer may point to something that the class needs to delete, in which case the default memberwise copy would be wrong.
```
class Shape {
public:
     Shape() =default;
     Shape(const Shape&) =delete;            // no copy operations
     Shape& operator=(const Shape&) =delete;
     // ...
};

void copy(Shape& s1, const Shape& s2)
{
     s1 = s2;  // error: Shape copy is deleted
}
```
<b>Copying Containers</b><br>
The default memberwise copy for a container is typically a disaster, due to the fact that the class is responsible for an object accessed through a pointer. We don't want a shallow copy, but a deep one.

```
class Vector {
  //...
 private:
  int sz_;
  double* element_;
};
     Vector v2 = v1;    // copy v1's representation into v2     
     v1[0] = 2;         // v2[0] is now also 2!     
     v2[1] = 3;         // v1[1] is now also 3!
```
Note here the element pointer of v2 just gets set to same address as v1, aka shallow copy.

<b>Moving Containers</b><br>
"C++11 defines two new functions in service of move semantics: a move constructor, and a move assignment operator. Whereas the goal of the copy constructor and copy assignment is to make a copy of one object to another, the goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is much less expensive than making a copy)", definition form [here](https://www.learncpp.com/cpp-tutorial/15-3-move-constructors-and-move-assignment/).
```
class Vector {     // ...     
  Vector(const Vector& a);               // copy constructor     
  Vector& operator=(const Vector& a);    // copy assignment     
  Vector(Vector&& a);                    // move constructor     
  Vector& operator=(Vector&& a);         // move assignment};
```
A move constructor does not take a const argument: after all, a move constructor is supposed to remove the value from its argument. A move assignment is defined similarly.

## Topics to dive in deeper in the future
Here is a list of topics I would investigate a bit more in detail:
- Error handling architectures
- Contracts
- Modules
- Analyzing the standard library
- ROOT a modular scientific software toolkit found [here](https://root.cern.ch//).

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
