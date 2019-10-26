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
"Some operations, such as initialization, assignment, copy, and move, are fundamental in the sense that language rules make assumptions about them. Other operations, such as == and <<, have conventional meanings that are perilous to ignore", Bjarne Stroustrup.


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
A move constructor does not take a `const` argument: after all, a move constructor is supposed to remove the value from its argument. A move assignment is defined similarly.

## Chapter 6: Templates
A template is a class or a function that we parameterize with a set of types or values. A good general FAQ, which explains the bits an parts of templates can be found [here](https://isocpp.org/wiki/faq/templates#template-specialization-piecemeal). An explanation to the question: `Why can’t I separate the definition of my templates class from its declaration and put it inside a .cpp file` can also be found there.

<b>Template Argument Deduction</b><br>
"In order to instantiate a function template, every template argument must be known, but not every template argument has to be specified. When possible, the compiler will deduce the missing template arguments from the function arguments", see reference [here](https://en.cppreference.com/w/cpp/language/template_argument_deduction).
```
template<typename To, typename From> To convert(From f);

void g(double d)
{
    int i = convert<int>(d);    // calls convert<int, double>(double)
    char c = convert<char>(d);  // calls convert<char, double>(double)
    int(*ptr)(float) = convert; // instantiates convert<int, float>(float)
}
```
<b>Function Objects</b><br>
Functors (Function Objects or Functionals) are simply put `object + ()`. In other words, a functor is any object that can be used with () in the manner of a function.
```
template<typename C, typename P>
     // requires Sequence<C> && Callable<P,Value_type<P>>
int count(const C& c, P pred)
{
     int cnt = 0;
     for (const auto& x : c)
           if (pred(x))
                 ++cnt;
     return cnt;
}

vector<int> vec{ 1,1,1,10,10};
count(vec, Less_than{10});
```
<b>Lambda Expressions</b><br>
"C++11 introduces lambdas allow you to write an inline, anonymous functor to replace the struct f. For small simple examples this can be cleaner to read (it keeps everything in one place) and potentially simpler to maintain", see [here](https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11#7627218).
```
vector<int> vec{ 1,1,1,10,10};
count(vec, [] (int a) -> bool { return a < 10;});
```
<b>Aliases</b><br>
It is very common for a parameterized type to provide an alias for types related to their template arguments.
```
template<typename Key, typename Value>
class Map {
     // ...
};

template<typename Value>
using String_map = Map<string,Value>;

String_map<int> m;  
```

## Chapter 7: Concepts and Generic Programming
Templates provide a powerful mechanism for compile-time computation and type manipulation that can lead to very compact and efficient code.

"Concepts are named Boolean predicates on template parameters, evaluated at compile time. A concept may be associated with a template (class template, function template, or member function of a class template), in which case it serves as a constraint: it limits the set of arguments that are accepted as template parameters", source can be found [here](https://en.wikipedia.org/wiki/Concepts_(C%2B%2B)).

<b>I am skipping concepts for now, due to the fact that MSVC does only add limited functionality</b><br>
The following code does currently not compile, even with ` /std:c++latest ` .
```
template<Sequence Seq, Number Num>
Num sum(Seq s, Num v) {
  for (const auto& x : s)
    v += x

    return x;
}
```
<b>Generic Programming</b><br>
"The form of generic programming supported by C++ centers around the idea of abstracting from concrete, efficient algorithms to obtain generic algorithms that can be combined with different data representations to produce a wide variety of useful software", Stepanov.

<b>Abstraction Using Templates</b><br>
"It is not a good idea to try to “abstract” by trying to prepare for every conceivable need and technique; start with one concrete examples from real use and try to eliminate inessential details", Bjarne Stroustrup.
```
void use(const vector<int>& vec, const list<double>& lst)
{
     auto sum = accumulate(begin(vec),end(vec),0.0); // accumulate in a double
     auto sum2 = accumulate(begin(lst),end(lst),sum);
     //
}
```
<b>Variadic template</b><br>
In computer programming, variadic templates are templates that take a variable number of arguments. MSVc is a little bit diffrent in the usage of varidic templates, ther always needs to be a base case, see [here](https://docs.microsoft.com/en-us/cpp/cpp/ellipses-and-variadic-templates?view=vs-2019).
```
template<typename T>
void print(T& val) {
  std::cout << val << '\n';
}

template<typename T, typename ... Tail>
void print(T head, Tail... tail) {
  std::cout << head << ' ';
  print(tail...);
}
...
print("asd"s, 1, '3', 3, 4.0f);
```
"Variadic recursion involves calling a variadic function template by using differing (almost always decreasing) numbers of arguments, and thereby stamping out a different signature every time. <u>A "base case" is still required</u>, but the nature of the recursion is different."

<b>Fold Expressions</b><br>
Fold expressions are a new way to unpack variadic parameters with operators.
```
template<Number ... T>
int sum2(T... v)
{
  return ( ... + v); // add all elements of v to 0
}
```
"Duck typing (“If it walks like a duck and it quacks like a duck, it’s a duck”)."

## Chapter 8: Library Overview
"The C++ Standard Library provides several generic containers, functions to utilize and manipulate these containers, function objects, generic strings and streams, support for some language features, and functions for everyday tasks such as finding the square root of a number", see [here](http://www.cplusplus.com/reference/).

## Chapter 9: Strings and Regular Expressions
"The standard string class provides support for such objects with an interface similar to that of a standard container of bytes, but adding features specifically designed to operate with strings of single-byte characters", definition can be found [here](http://www.cplusplus.com/reference/string/string/).

Regular expressions are a standardized way to express patterns to be matched against sequences of characters", for details see [here](http://www.cplusplus.com/reference/regex/).

<b>Strings</b><br>
Small String Optimization (SSO), short strings will not call the allocate function and instead being created in the `string` object it self. When a `string`’s value changes from a short to a long string (and vice versa) its representation adjusts appropriately. An example can be found [here](https://blogs.msmvps.com/gdicanio/2016/11/17/the-small-string-optimization/).

<b>String Views</b><br>
A `string_view` is a way to wrap an existing string in a non-owning way.
The idea is always to store a pair of pointer-to-first-element and size of some existing data array or string.

Such a view-handle class could be passed around cheaply by value and would offer cheap substringing operations (which can be implemented as simple pointer increments and size adjustments).

<b>Regular Expressions</b><br>
"A regular expression, regex or regexp is, in theoretical computer science and formal language theory, a sequence of characters that define a search pattern. Usually this pattern is then used by string searching algorithms for "find" or "find and replace" operations on strings, or for input validation", see definition [here](https://en.wikipedia.org/wiki/Regular_expression).
```
Ax*            // A, Ax, Axxxx
Ax+            // Ax, Axxx     Not A
\d−?\d         // 1-2, 12      Not 1--2
\w{2}−\d{4,5}  // Ab-1234, XX-54321, 22-5432      Digits are in \w
(\d*:)?(\d+)   // 12:3, 1:23, 123, :123  Not 123:
(bs|BS)        // bs, BS       Not bS
[aeiouy]       // a, o, u      An English vowel, not x
[^aeiouy]      // x, k         Not an English vowel, not e
[a^eiouy]      // a, ^, o, u   An English vowel or ^
```
A more detailed description of `regex` can be found [here](http://www.informit.com/articles/article.aspx?p=2079020).

## Chapter 10: Input and Output
As already mentioned, at lowest levels, files are implemented as streams of bytes. A Stream is simply a sequence of bytes. Input and Output operations are supported by the `istream` (input stream) and `ostream` (output stream) classes.

The ostream output operation, referred to as insertion is performed by the insertion operator "<<". The istream input operation, referred to as extraction, is performed by the extraction operator ">>", se details [here](https://codescracker.com/cpp/cpp-input-output.htm). I am skipping here some content since basic I/O operations are pretty straight forward.

<b>I/O State</b><br>
"In general, the I/O state holds all the information needed to read or write, such as formatting information (§10.6), error state (e.g., has end-of-input been reached?), and what kind of buffering is used", Bjarne Stroustrup.
The following  table shows the `std::ios::fail` function information, [link](http://www.cplusplus.com/reference/ios/ios/fail/).
<table>
<tbody><tr><th rowspan="2"><samp><a href="/ios_base::iostate">iostate</a></samp> value<br>
(member constants)</th><th rowspan="2">indicates</th><th colspan="5"><samp></samp>functions to check state flags</th></tr>
<tr><th><samp><a href="/ios::good">good()</a></samp></th><th><samp><a href="/ios::eof">eof()</a></samp></th><th><samp><a href="/ios::fail">fail()</a></samp></th><th><samp><a href="/ios::bad">bad()</a></samp></th><th><samp><a href="/ios::rdstate">rdstate()</a></samp></th></tr>
<tr><th><samp>goodbit</samp></th><td>No errors (zero value <samp><a href="/ios_base::iostate">iostate</a></samp>)</td><td class="yes"><code>true</code></td><td class="no"><code>false</code></td><td class="no"><code>false</code></td><td class="no"><code>false</code></td><td><samp>goodbit</samp></td></tr>
<tr><th><samp>eofbit</samp></th><td>End-of-File reached on input operation</td><td class="no"><code>false</code></td><td class="yes"><code>true</code></td><td class="no"><code>false</code></td><td class="no"><code>false</code></td><td><samp>eofbit</samp></td></tr>
<tr><th><samp>failbit</samp></th><td>Logical error on i/o operation</td><td class="no"><code>false</code></td><td class="no"><code>false</code></td><td class="yes"><code>true</code></td><td class="no"><code>false</code></td><td><samp>failbit</samp></td></tr>
<tr><th><samp>badbit</samp></th><td>Read/writing error on i/o operation</td><td class="no"><code>false</code></td><td class="no"><code>false</code></td><td class="yes"><code>true</code></td><td class="yes"><code>true</code></td><td><samp>badbit</samp></td></tr>
</tbody></table>

<b>File System</b><br>
"The Filesystem library, ISO/IEC TS 18822:2015, provides facilities for performing operations on file systems and their components, such as paths, regular files, and directories", see [here](https://en.cppreference.com/w/cpp/experimental/fs).
```
#inlcude <filesystem>
using std::filesystem::path;
using std::filesystem::current_path;
using std::filesystem::exists;

path cwd = current_path(),
     rel{"../../../a_test_file.txt"};

    exists(cwd / rel);
```

## Chapter 11: Containers
A class with the main purpose of holding objects is commonly called a container. Containers are used to manage collections of objects of a certain kind. There are several different types of containers like deque, list, vector, map etc.

<b>Vector</b><br>
"A typical implementation of vector (§4.2.2, §5.2) will consist of a handle holding pointers to the first element, one-past-the-last element, and one-past-the-last allocated space", Bjarne Stroustrup.
```
template<typename T>
class Vector {
     T* elem;     // pointer to first element
     T* space;    // pointer to first unused (and uninitialized) slot
     T* last;     // pointer to last slot
public:
     // ...
     int size();                     // number of elements (space-elem)
     int capacity();                 // number of slots available for elements (last-elem)
     // ...
     void reserve(int newsz);        // increase capacity() to newsz
     // ...
     void push_back(const T& t);     // copy t into Vector
     void push_back(T&& t);          // move t into Vector
};
```
<b>List</b><br>
"Lists are sequence containers that allow non-contiguous memory allocation. As compared to vector, list has slow traversal, but once a position has been found, insertion and deletion are quick. Normally, when we say a List, we talk about doubly linked list. For implementing a singly linked list, we use forward list", see [here](https://www.geeksforgeeks.org/list-cpp-stl/).

<b>Map</b><br>
"Map is dictionary like data structure. It is a sequence of (key, value) pair, where only single value is associated with each unique key. It is often referred as associative array," see [here](https://www.tutorialspoint.com/cpp_standard_library/map.htm). The standard library offers a balanced binary search tree (usually, a red-black tree) called map.

<b>Unordered map</b><br>
"Unordered maps are associative containers that store elements formed by the combination of a key value and a mapped value, and which allows for fast retrieval of individual elements based on their keys.
Internally, the elements in the unordered_map are not sorted in any particular order with respect to either their key or mapped values, but organized into buckets depending on their hash values to allow for fast access to individual elements directly by their key values (with a constant average time complexity on average)," reference is provided [here](http://www.cplusplus.com/reference/unordered_map/unordered_map/).

## Chapter 12: Algorithms
"We rarely just store objects in a container. We sort them, print them, extract subsets, remove elements, search for objects, etc. Consequently, the standard library provides the most common algorithms for containers in addition to providing the most common container types", Bjarne Stroustrup.

<b>Iterators</b><br>
"An iterator is an object (like a pointer) that points to an element inside the container. We can use iterators to move through the contents of the container. They can be visualized as something similar to a pointer pointing to some location and we can access content at that particular location using them.

Iterators play a critical role in connecting algorithm with containers along with the manipulation of data stored inside the containers. The most obvious form of iterator is a pointer. A pointer can point to elements in an array, and can iterate through them using the increment operator (++). But, all iterators do not have similar functionality as that of pointers", see reference [here] (https://www.geeksforgeeks.org/introduction-iterators-c/).
```
void f(vector<Entry>& vec, list<Entry>& lst){     sort(vec.begin(),vec.end());                      // use < for order     unique_copy(vec.begin(),vec.end(),lst.begin());   // don't copy adjacent equal elements}
```

<b>Iterator Streams</b><br>
If an iterator can be used to access elements of a data container, then what about streams? In keeping with the design, Streams too are data containers and so C++ provides us with iterators to iterate over the elements present in any stream. These iterators are called Stream Iterators. To use these iterators the iterator header file must be included. Link of an example can be found [here](https://www.geeksforgeeks.org/stdistream_iterator-stdostream_iterator-c-stl/).

<b>Predicates</b><br>
The Predicate parameter is used whenever an algorithm expects a function object that when applied to the result of dereferencing the corresponding iterator returns a value testable as true. In other words, if an algorithm takes Predicate pred as its argument and first as its iterator argument, it should work correctly in the construct `if (pred(*first)){...}`. The function object pred shall not apply any non-constant function through the dereferenced iterator. This function object may be a pointer to function, or an object of a type with an appropriate function call operator, from the C++ standard.
```
std::map<std::string, int> m{ {"Nawin", 1}, {"Belen", 4}, {"JD", 7} };
auto p2 = find_if(m.begin(), m.end(), [](const std::pair<std::string, int>& r) { return r.second > 4; });
```

## Chapter 13: Utilities
The standard function has several utility functions for number of conversions, variable-length, argument processing, sorting and searching, and random number generation. To use these function the header <cstdlib> is required.

<b>Resource Management</b><br>
A resource is something that must be acquired and later (explicitly or implicitly) released. Examples are memory, locks, sockets, thread handles, and file handles.

<b>unique_ptr and shared_ptr</b><br>
Smart pointer is an abstract data type by using which we can make a normal pointer in such way that it can be used as memory management like file handling, network sockets etc., also it can do many things like automatic destruction, reference counting etc.
```
std::unique_ptr<T> ptr { new T(value) };

//OR

std::unique_ptr<T> ptr = make_unique<T>(value);
```
Where do we use “smart pointers” (such as `unique_ptr`) rather than resource handles with operations designed specifically for the resource (such as `vector` or `thread`)? Unsurprisingly, the answer is “when we need pointer semantics.”

- When we share an object.
- When we refer to a polymorphic object , we need a pointer (or a reference) because we don’t know the exact type of the object referred to.
- A shared polymorphic object typically requires `shared_ptr`.

<b>array</b><br>
An `array` is a fixed-size sequence of elements of a given type where the number of elements is specified at compile time.
```
void f(int* p, int sz);    // C-style interface

void g()
{
     array<int,10> a;

     f(a,a.size());             // error: no conversion
     f(&a[0],a.size());         // C-style use
     f(a.data(),a.size());      // C-style use

     auto p = find(a.begin(),a.end(),777);    // C++/STL-style use
     // ...
}
```

<b>bitset</b><br>
A set of flags indicating binary conditions such as good/bad, true/false, and on/off is a prefect use case for a `bitset`.
```
    std::bitset<5> bs1{"10010"};
    std::bitset<5> not_bs1= ~bs1;
```

<b>pair and tuple</b><br>
`std::pair` is a data type for grouping two values of any desired user or build in type together as a single object. A `std::tuple` is an object that can hold a number of elements. The elements can be of different data types. The elements of tuples are initialized as arguments in order in which they will be accessed.
```
template <class T1, class T2> struct pair;
tuple<string,int,double> t1 {"Shark",123,3.14};    // the type is explicitly specified
```

<b>variant</b><br>
A variant is basally a more safer option of a union.
```
std::variant<int, float> v, w;
    v = 12; // v contains int
    int i = std::get<int>(v);
    w = std::get<int>(v);
    w = std::get<0>(v); // same effect as the previous line
    w = v; // same effect as the previous line

//  std::get<double>(v); // error: no double in [int, float]
//  std::get<3>(v);      // error: valid index values are 0 and 1
```
<b>optional</b><br>
"An `optional` can be seen as a special kind of variant (like a `variant<A,nothing>`) or as a generalization of the idea of an `A*` either pointing to an object or being `nullptr`", Bjarne Stroustrup. The usage is the same as for a genral pointer type.

<b>any</b><br>
An `any` is basically a generalization of an variant for build in types or user types, it also could be empty.
```
std::any a = 1;

try {
  std::cout << std::any_cast<float>(a) << '\n';
} catch (const std::bad_any_cast& e) {
  std::cout << e.what() << '\n';
}
```
<b>Allocators</b><br>
"Allocators are used by the C++ Standard Library to handle the allocation and deallocation of elements stored in containers. All C++ Standard Library containers except std::array have a template parameter of type allocator<Type>, where Type represents the type of the container element", see [here](https://docs.microsoft.com/en-us/cpp/standard-library/allocators?view=vs-2019).

"At the most conceptual level, an allocator is an object that supplies raw memory for use by other objects, especially containers", Pablo Halpern.

A implementation based on the requirements for an allocator defined by the C++ standard can be found [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2271.html#std_allocator).

<b>Time</b><br>
The `chrono` library provides support for time measuring as well as a high res helper functions.

```
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  auto time_span = duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "It took me " << time_span.count() << " seconds.";
```
<b>iterator_traits</b><br>
Generic code that uses iterators, such as the STL algorithms which use them intensely, needs information about them. For example, it needs the type of the object that the iterators refer to. To obtain this information, the STL requires that the iterator it operates on must define a type called `value_type`, see reference [here](https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/).

```
class MyIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;

    // ...
```
## Topics to dive in deeper in the future
Here is a list of topics I would investigate a bit more in detail:
- Error handling architectures
- Contracts
- Modules
- Concepts
- Concurrency
- Performance measuring
- Filesystem standard library
- Template metaprogramming
- Analyzing the standard library coding style
- ROOT a modular scientific software toolkit found [here](https://root.cern.ch//).

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
