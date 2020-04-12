<img src="https://proxy.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.UpYpMIfsXsORJXAR4do7KgAAAA%26pid%3DApi&f=1" alt="Book Cover" height="62px" width="42px" align="left"><br><br>

# Design Patterns in Modern C++
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
This repository contains my notes and source files of the book `Design Patterns in Modern C++` by Dmitri Nesteruk. I created this repository in order to have a centralized space for my code. My notes are not complete by any means, they only consist of content which I thought is helpful.

## Tipps
<b>How to add `cpplint` to Visual Studio</b>
1. Install the [tool](https://github.com/google/styleguide):
```
$ python -m pip install cpplint
```
2. Add external tools to Visual Studio:
  ```
  Tools - External tools - Add - Title：cpplint
  command：cpplint -–output=vs7 $(ItemPath)
  Initial Directory：$(ItemDir)
  Use Output Window: checked
  ```
3. Add shortcut:
  ```
  Tools - Options - Environment - Keyboard
  Show commands containing：external
  Tools.ExternalCommand1
  Press shortcut keys
  ```

## Chapter 1: Introduction
The introduction contains a lot of compressed knowledge which at some point get described in detail in section 9, hence I am not covering those elements, only if I think it makes sense. Nevertheless the SOLID Design Principles is interesting and important.

### The SOLID Design Principles
SOLID is an acronym which stands for the following design principles (and their abbreviations):
- Single Responsibility Principle (SRP)
- Open-Closed Principle (OCP)
- Liskov Substitution Principle (LSP)
- Interface Segregation Principle (ISP)
- Dependency Inversion Principle (DIP)

**Single Responsibility Principle (SRP)**
A class should only have one purpose, this helps to remove coupling as well as create better abstractions, which are easier to understand. This helps to eliminate the need of changing classes since the class has only one purpose. As general antipattern is the `God object`, meaning objects which are trying to implement as many concerns as possible.

**Open-Closed Principle (OCP)**
The open closed principle describes the fact that a class should be open for extensions but closed for changes, this means in order to add functionality, the class should be easily extendable without recompiling everything. Only by adding the behavior which should extend the class.

**Liskov Substitution Principle LSP**
If an interface takes an object of its base class, it should equally take an object
of its sub class without anything breaking, or unexpected behavior.

**The Interface Segregation Principle (ISP)**
Interface should also follow the rule of SRP, meaning it's not recommended to create interface classes which contain a lot of methods unless the grouping makes sense in the bigger picture. It is often beneficial to split the interfaces this helps the user, in case he does not want to implement all methods, only the one he needs.

**Dependency Inversion Principle (DIP)**
"High-level modules should not depend on low-level modules. Both
should depend on abstractions."[Robert C. Martin](https://www.goodreads.com/author/show/45372.Robert_C_Martin).

## Part 1: Creational Patterns
Creational patterns are answering the question about how a complex object should be created. This makes sense when a creation of the object is not trivial, meaning the construction process is complicated. This is where the creational patterns come in play.

### Chapter 2: Builder
#### Simple Builder
The builder pattern is one way of taking care of the creation of a object in a separate class. The builder pattern in the following code snipped shows how the building of the `HtmlElement` is done by the `HtmlBuilder`, which shows that the interface is easier to use, and there is no need to know the internal implementation of the `HtmlELement`.
``` c++
TEST(BuilderPatternIntro, Before) {
   std::string words[] = { "Hello", "world" };
   HtmlElement list("ul", "");
   for (auto w : words)
     list.elements_.emplace_back(HtmlElement{ "li", w });
   std::cout << list.str();
 }

 TEST(BuilderPatternSimpleBuilder, After) {
   HtmlBuilder builder{ "ul" };
   builder.add_child("li", "hello");
   builder.add_child("li", "world");
   std::cout << builder.str();
 }
```

#### Fluent Builder
The fluent builder basically adds a little bit of functionality to the builder class, allowing e.g. chaining and a more wider scope of adding elements, see code snippet below.
```c++
TEST(BuilderPatternFluentBuilder, MoreAdvancedExample) {
  auto builder = HtmlElemenUpdated::build("ul");

  builder->add_child("li", "hello").add_child("li", "world");
  std::cout << builder->str();
}
```

#### Groovy-Style Builder
A groovy style builder is just a way of creating a syntactic way of constructing an object that mimics the syntax of the programming language groovy. The snippet below uses initializer lists to do so.
```c++
struct P : Tag {
  explicit P(const std::string& text) : Tag{ "P", text } {}
  P(std::initializer_list<Tag> children) : Tag{ "p", children } {}
};

struct IMG : Tag {
  explicit IMG(const std::string& url) : Tag{ "img", "" } {
    attributes_.emplace_back(std::make_pair( "src", url));
  }
};

TEST(BuilderPatternGrovyStyleBuilder, Example) {
   std::cout << P{
     IMG{ "http://awdawd.png" },
     IMG{ "http://awdawd.png" }
   };
 }
```

#### Composite Builder
The composite builder is simply just a aggregation of different builders.
```c++
class PersonBuilderBase {
protected:
  Person& person_;
  explicit PersonBuilderBase(Person& person) : person_{ person } {}

public:
  operator Person() {
    return std::move(person_);
  }

  PersonAddressBuilder lives(void) {
    return PersonAddressBuilder{ person_ };
  };
  PersonJobBuilder works(void) {
    return PersonJobBuilder{ person_ };
  }
};
```

### Chapter 3: Factories
#### Factory Method
The Factory Method design pattern is used instead of the regular class constructor for keeping within the SOLID principle of programming, decoupling the construction of objects from the objects themselves [Wikipedia](https://en.wikipedia.org/wiki/Factory_method_pattern).

#### Inner Factory
Is basically the same as a factory class besides the fact that it resides within the class of the object it creates. Here is a code snipped:
```c++
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

TEST(InnerFactoryClass, BasicIntro) {
    auto p = InnerPoint::Factory::NewPolar(5, 2.14 / 2);
  }
```

#### Abstract Factory
The abstract factory is an extension of a classical factory class but with the usage of inheritance, meaning a abstract factory class is defined for the creation of a concrete factory:
```c++
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
```

#### Functional Factory
If someone passes in a `std::function` that returns a type T into some function, this is typically referred to as a Factory, not a Factory Method [Dmitri Nesteruk](https://www.pluralsight.com/authors/dmitri-nesteruk).

**Note**<br>
A factory is simply a wrapper function around a constructor (possibly one in a different class). The key difference is that a factory method pattern requires the entire object to be built in a single method call, with all the parameters pass in on a single line. The final object will be returned.

A builder pattern, on the other hand, is in essence a wrapper object around all the possible parameters you might want to pass into a constructor invocation. This allows you to use setter methods to slowly build up your parameter list. One additional method on a builder class is a build() method, which simply passes the builder object into the desired constructor, and returns the result. [Stackoverflow](https://stackoverflow.com/questions/757743/what-is-the-difference-between-builder-design-pattern-and-factory-design-pattern).

### Chapter 4: Prototype
#### Ordinary Duplication
The general idea is to create an object and copy is's attributes with the help of e.g. an `operator=`.
```c++
SomeWeirdClass prototype{"An attribute", 5};
SomeWeirdClass different_obj;
// here we are using a prototype for initialization of the values of different_obj
different_obj = prototype;

// customizing it
different_obj.a_value = 7;

```

#### Duplication via Copy Constructor
Duplication can also occur via the copy constructor.
```c++
SomeWeirdClass prototype{"An attribute", 5};
SomeWeirdClass different_obj = prototype;

// customizing it
different_obj.a_value = 7;
```

#### Prototype Factory
Is creating an object via a factory pattern with the help of an instantiated object which is used as a blue print.

### Chapter 5: Singelton
#### Ordinary Duplication


## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
