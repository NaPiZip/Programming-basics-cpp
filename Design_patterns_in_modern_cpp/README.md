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

### Chapter 5: Singleton
#### Classic Implementation
A singleton is a type which only can be instantiate once.
```c++
class Singleton
{
   public:
       static S& getInstance()
        {
            static S    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
     S(S const&)               = delete;
      void operator=(S const&)  = delete;
};
```

#### Monostate
A monostate is a singleton class which looks like an ordinary class but is under the hood only instantiate once.
```c++
class Printer
{
  static int id;
  public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
};
```

## Part 2: Structural Patterns
Structural pattern describe how to design objects and classes. It gives guidelines on how the internal arrangement should be and how it should be organized. We commonly use tree types:
- Inheritance
An object automatically acquires the nonprivate fields and functions of its base class.
or classes.
- Composition
It describes a class that references one or more objects of other classes in instance variables (it consists of).
- Aggregation
Is very similar as composition, with the difference that we do not own, pointer to an object, meaning we are not responsible for live time handling (it uses).

### Chapter 6: Adapters
#### Adapters
The adapter design pattern consists of having a fixed interface which is given, but we want to use it with our own object types. The example shows the `DrawPoints` function which is based on `std::vector<Point>::iterator`, but we want to use `Line` objects.
```c++

struct Point {
  int x_, y_;
};

struct Line {
  Point begin_, end_;
};

void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end);
```

We can accieve this by using a adapter:
```c++
struct LineToPointAdapter {
  using Points = std::vector<Point>;
  LineToPointAdapter(Line& line);
  virtual Points::iterator begin();
  virtual Points::iterator end();

  private:
  Points points_;
};
```

### Chapter 7: Bridge
#### The Pimpl Idiom
The PIMPL Idiom (Pointer to IMPLementation) is a technique for implementation hiding in which a public class wraps a structure or class that cannot be seen outside the library the public class is part of [Stackoverflow](https://stackoverflow.com/questions/60570/why-should-the-pimpl-idiom-be-used).
```c++
struct Person {
  void greet();

  Person(std::string);
  ~Person();

  struct PersonImpl;
  PersonImpl* pimpl_;
};

void Person::greet() {
  pimpl_->greet(this);
};
```

The implementation is now hidden for the user.
#### Bridge
The bridge pattern is meant to decouple an abstraction form its implementation, similar to the `pimpl` idiom. The following example shows how we can pass a `VectorRenderer` or a `RasterRenderer` to the `Circle` constructor.
```c++
TEST(Bridge, ABasicBridge) {
  std::shared_ptr<VectorRenderer> v_renderer = std::make_shared<VectorRenderer>();
  std::shared_ptr<RasterRenderer> r_renderer = std::make_shared<RasterRenderer>();

  std::unique_ptr<Circle> v_shape = std::make_unique<Circle>(*v_renderer, 1, 1, 1);
  std::unique_ptr<Circle> r_shape = std::make_unique<Circle>(*v_renderer, 1, 1, 1);
  v_shape->draw();
  r_shape->draw();
}
```

### Chapter 8: Composite
#### The Composite Pattern
A composition pattern tries to give single objects and groups of objects an identical interface. The follow example shows the nesting of an element type `Group` into another group.
```c++
Group root("root");
Circle c1, c2;
root.objects.push_back(&c1);

Group subgroup("sub");
subgroup.objects.push_back(&c2);

root.objects.push_back(&subgroup);

root.draw();
```

### Chapter 9: Decorator
#### The Dynamic Decorator
The decorator pattern allows to enhance feature with out breaking the single responsible pattern.
```c++
struct Shape {
  virtual std::string str() const = 0;
};

struct ColoredShape : public Shape {
  Shape& shape_;
  std::string color_;

  ColoredShape(Shape& shape, const std::string& color) : shape_{ shape }, color_{ color } {}
  std::string str() const override;
};

struct TransparentShape : public Shape {
  Shape& shape_;
  uint8_t transparency_;

  TransparentShape(Shape& shape, uint8_t transparency) : shape_{ shape }, transparency_{ transparency } {}
  std::string str() const override;
};

TEST(DecoratorPattern, DynamicDecoratorEnhancment) {
   std::unique_ptr<TransparentShape> demi_square = std::make_unique<TransparentShape>(Square(5), 85);

   std::cout << demi_square->str() << '\n';

   std::unique_ptr<ColoredShape> red_circle = std::make_unique<ColoredShape>(Circle(3.0f), "red");
   std::unique_ptr<TransparentShape> custom_circle = std::make_unique<TransparentShape>(*red_circle, 200);

   std::cout << custom_circle->str() << '\n';
 }
```

#### The Static Decorator
Static decorator follow the same idea, but with using template meta programming technique. See here how the ctor is forwarded:
```c++
template <typename T>
struct NewTransparentShape2 : T {
  static_assert(std::is_base_of<Shape, T>::value,
      "Template argument needs to be a type of shape");

  uint8_t transparency_;
  template <typename... Args>
  NewTransparentShape2(uint8_t transparency, Args... args) : T(std::forward<Args>(args)...), transparency_{ transparency } {}
  std::string str() const override {
    float transparency_in_percent = static_cast<float>(transparency_) / 255.f * 100.f;
    return T::str() + " has " + std::to_string(transparency_in_percent) + "% transparency";
  }
};
```

#### Functional Decorator
Is the application of the decorator pattern for functions instead of classes.
```c++
template <typename>
struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)> {
  std::function<R(Args...)> func_;
  std::string name_;

  Logger3(std::function<R(Args...)> func, const std::string& name) : func_{ func }, name_{ name } {}

  R operator()(Args... args) {
    std::cout << "Entering " << name_ << '\n';
    R result = func_(args...);
    std::cout << "Exiting " << name_ << '\n';
    return result;
  }
};
```

### Chapter 10: Facade
#### General Description
A facade is a simple concept of hiding for example the initialization of a class with a vast number of arguments. It helps keeping the creation easy by removing the need of explicit initialization of all arguments. The following example shows how the arguments of the constructor gets replaced by a additional method which only takes a struct object to get initialized.
```c++
Console::Console(bool fullscreen, int char_width, int char_height, int width, int height, optional<Size> client_size)

struct ConsoleCreationParameters
{
  optional<Size> client_size;
  int character_width{10};
  int character_height{14};
  int width{20};
  int height{30};
  bool fullscreen{false};
  bool create_default_view_and_buffer{true};
};

Console::Console(const ConsoleCreationParameters& ccp);
```

### Chapter 11: Flyweight
#### General Description
The flyweight is a pattern which is used to save space or to reduce the overhead of content. The example below shows how to save names in a hash map like structure, an name only gets inserted if it does not exists yet otherwise the reference to the existing object is used.
```c++
struct User {
  User(const std::string& first_name, const std::string& last_name) : first_name_{ add(first_name) }, last_name_{ add(last_name) } {}
  const std::string& get_first_name() const;
  const std::string& get_last_name() const;

protected:
  key first_name_, last_name_;
  static key seed_;
  static boost::bimap<key, std::string> names_;
  static key add(const std::string& s);

private:
  friend std::ostream& operator<<(std::ostream& os, const User& obj);
};

key User::seed_ = 0;
boost::bimap<key, std::string> User::names_ = {};

key User::add(const std::string& s) {
  auto it = names_.right.find(s);
  if (it == names_.right.end()) {
    names_.insert({ ++seed_, s });
    return seed_;
  }
  return it->second;
}

```

### Chapter 12: Proxy
#### General Description
A proxy pattern basically provides a interface to an API. This can be used to either customize, adapt or extend an existing API. There are various different kind of proxy depending on their functionality:
- Property Proxies, replace fields and perform additional behavior.
- Virtual Proxies, provide additional functionality by maintaining the interface combability.
- Communication Proxies, keeps the same API by changing the underling invoked object.

```c++

struct Bitmap : Image {
  Bitmap(const std::string& filename);
  void draw() override;
};

struct LazyBitmap : Image {
  LazyBitmap(const std::string& filename) : Image{ filename } {};
  ~LazyBitmap() { delete bmp_; }
  void draw() override {
  if (!bmp_)
    bmp_ = new Bitmap(filename_);
  bmp_->draw();
};

private:
  Bitmap* bmp_{ nullptr };
};
```

## Part 3: Behavioral Patterns
Behavioral pattern address the topic of the deal with the way the program flow is executed, depending on the developer defined environmental constrains. It basically covers all general cases which are left.

### Chapter 13: Chain of Responsibility
#### General Description
The chain of Responsibility is the consecutive invocation of methods, this can either be implemented via:
- Pointer Chain, it is basic just traversing a linked list or a vector.
- Broker Chain , is a managed approach with the usage of a central service which keeps track  of what happend.

```c++
struct Query {
  std::string creature_name_;
  enum Argument { attack,
    defense } argument;
  int result;
};

class Creature2 {
  Game& game_;
  int attack_, defense_;  

public:  
  std::string name_;
  Creature2(Game& game, const std::string& name, int attack, int defense) : game_{ game }, name_{ name }, attack_{ attack }, defense_{defense} {};
  int get_attack() const {
    Query q{ name_, Query::Argument::attack, attack_ };
    game_.queries(q);
    return q.result;
  }
};

```

### Chapter 14: Command
#### General Description
With the help of the command pattern can objects modify and query state information with the help of using special objects aka. the command. This is helpful e.g. if you want to maintain a history of actions.
```c++
struct BankAccount {
  int balance_ = 0;
  int overdraft_limit_ = -500;

  void deposit(int amount);
  bool withdraw(int amount);
};


struct Command {
  virtual void call() = 0;
  virtual void undo() = 0;
};


struct BankAccountCommand : Command {
  BankAccount& account_;
  enum Action { deposit,
    withdraw } action_;
  int amount_;
  bool withdrawal_succeeded_{ false };

  BankAccountCommand(BankAccount& account, const Action action, const int amount) : account_{ account }, action_{ action }, amount_{ amount } {  }
  void call() override;
  void undo() override;
};

void BankAccountCommand::call() {
  switch (action_) {
  case BankAccountCommand::deposit:
    account_.deposit(amount_);
    break;
  case BankAccountCommand::withdraw:
    withdrawal_succeeded_ = account_.withdraw(amount_);
    break;
  default:
    break;
  }
}
```

### Chapter 15: Interpreter
#### General Description
The interpreter pattern is mostly used to parse text input. Interpreter are usually divided in tow parts the lexer and the parser:
- lexer: Tokenizes  the given input.
- parser: Transforms the tokens into AST (Abstract Syntax Tree) form.

```c++
struct Token {
  enum class Type { integer,
    plus,
    minus,
    lparen,
    rparen } type_;
  std::string text_;

  explicit Token(Type type, const std::string& text) : type_{ type }, text_{ text } {}
};

std::vector<Token> lex(const std::string& input);


struct Element {
  virtual int eval() const = 0;
};

struct Integer : Element {
  int value_;
  explicit Integer(int value) : value_{ value } {}
  int eval() const override;
};

struct BinaryOperation : Element {
  enum class Type {addition, subtraction} type_;
  std::shared_ptr<Element> lhs_, rhs_;
  int eval() const override;
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens);
```

### Chapter 16: Iterator
#### General Description
An iterator is a helper which defines a fixed set of assumptions, depending on its type. The following snippet show a `std::iterator` base class:

```c++
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };
```

### Chapter 17: Mediator
#### General Description
The Mediator is a mechanism for facilitating communication between the components. It removes the direct communication and adds a layer of indirection, similar to the saying need to know principle.
```c++
struct ChatRoom;

struct Person {
  std::string name_;
  ChatRoom* room_ = nullptr;
  std::vector<std::string> chat_log_;

  Person(const std::string& name) : name_{ name } {}

  void receive(const std::string& origin, const std::string& message);
  void say(const std::string& message) const;
  void pm(const std::string& who, const std::string& message) const;
};

struct ChatRoom {
  std::vector<Person*> people_;

  void join(Person* p);
  void broadcast(const std::string& orign, const std::string& message);
  void message(const std::string& origin, const std::string& who, const std::string& message);
};
```

### Chapter 18: Memento
#### General Description
The memento pattern is about creating tokens which makes it possible to restore the state of an object, very similar to the command pattern with a history function.
```c++

class Memento {
  int balance_;
public:
  Memento(int balance) : balance_{ balance } {}
  friend class BankAccount;
  friend class BankAccount2;
};

class BankAccount2 {
  int balance_ = 0;
  std::vector<std::shared_ptr<Memento>> changes_;
  int current_;

public:
  explicit BankAccount2(int balance) : balance_{ balance } {
    changes_.emplace_back(std::make_shared<Memento>(balance));
    current_ = 0;
  }
  std::shared_ptr<Memento> deposit(int amount);
  void restore(const std::shared_ptr<Memento>& m);
  std::shared_ptr<Memento> undo();
  std::shared_ptr<Memento> redo();

   private:
  friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj);
};

std::shared_ptr<Memento> BankAccount2::undo() {
  if (current_ > 0) {
    --current_;
    auto m = changes_[current_];
    balance_ = m->balance_;
    return m;
  }
  return {};
}
```

### Chapter 19: Null Object
#### General Description
A null object is basically just a mock of an object with no functionality.
```c++
struct Logger {
  virtual ~Logger() = default;
  virtual void info(const std::string& s) = 0;
  virtual void warn(const std::string& s) = 0;
};

struct NullLogger : Logger {
  void info(const std::string& s) override {}
  void warn(const std::string& s) override {}
};
```

### Chapter 20: Observer
#### General Description
The observer pattern consists of mainly tow parts, an observable and the observer. The observable is the target which we want to observer, also the event source, and the observer is the sink of the event or consumer. The main purpose is to keep track of important events and perform actions if they occur.
```c++
template <typename T>
struct ObservableWithSignal {
  boost::signals2::signal<void(T&, const std::string&)> property_changed_;
};

struct PersonWithSignal : ObservableWithSignal<PersonWithSignal> {
private:
  int age_;

public:
  PersonWithSignal(int age) : age_{ age } {}
  void set_age(int age);
};

void PersonWithSignal::set_age(int age) {

  if (this->age_ == age)
    return;
  this->age_ = age;
  property_changed_(*this, "age");
};

TEST(DynamicProcessor, Positive) {
  TextProcessor tp;
  tp.set_output_format(OutputFormat::markdown);
  tp.append_list({ "foo", "bar", "baz" });
  std::cout << tp.str() << std::endl;

  tp.clear();
  tp.set_output_format(OutputFormat::html);
  tp.append_list({ "foo", "bar", "baz" });
  std::cout << tp.str() << std::endl;
}
```

### Chapter 21: State
#### General Description
The state pattern just describes a finite state machine, an example can be seen below.:
```c++
class MyDevice
{
    int m_nCurrentState;

public:
    MyDevice()
    {
        m_nCurrentState= STATE_OFF;
    }
    // Function handling the state changes
    void HandleState();
};

void MyDevice::HandleState()
{
    /* changing state depends on the current state */
   if(STATE_OFF == m_nCurrentState)
   {
       m_nCurrentState = STATE_ON;
   }
   else if(STATE_ON == m_nCurrentState)
   {
       m_nCurrentState = STATE_ACQUIRING;
   }
   else if(STATE_ACQUIRING == m_nCurrentState)
   {
       m_nCurrentState = STATE_SAVE;
   }
  ....
  ....
  // We can add more states here
}
```

### Chapter 22: Strategy
#### General Description
The Strategy design pattern allows you to define a skeleton of an algorithm and then use composition to supply the missing implementation details related to a particular strategy.
```c++
enum class OutputFormat {
  markdown,
  html
};

struct ListStrategy {
  virtual void start(std::ostringstream& oss) {}
  virtual void add_list_item(std::ostringstream& oss, const std::string& item) {}
  virtual void end(std::ostringstream& oss) {}
};

struct TextProcessor {
  void append_list(const std::vector<std::string>& items);
  void clear();
  void set_output_format(const OutputFormat format);

  std::string str() const;

private:
  std::ostringstream oss_;
  std::unique_ptr<ListStrategy> list_strategy_;
};

struct HtmlListStrategy : ListStrategy {
  void start(std::ostringstream&) override;
  void add_list_item(std::ostringstream&, const std::string&) override;
  void end(std::ostringstream&) override;
};

struct MarkdownListStrategy : ListStrategy {
  void add_list_item(std::ostringstream&, const std::string&) override;
};

TEST(DynamicProcessor, Positive) {
  TextProcessor tp;
  tp.set_output_format(OutputFormat::markdown);
  tp.append_list({ "foo", "bar", "baz" });
  std::cout << tp.str() << std::endl;

  tp.clear();
  tp.set_output_format(OutputFormat::html);
  tp.append_list({ "foo", "bar", "baz" });
  std::cout << tp.str() << std::endl;
}
```

### Chapter 23: Template Method
#### General Description
The template method pattern is very similar to the strategy pattern, but instead of using composition the template pattern uses inheritance. This can be seen in the following snippet.
```c++
class Game {
public:
  explicit Game(int number_of_players) : number_of_players_{ number_of_players } {}
  void run();
protected:
  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;

  int number_of_players_;
  int current_player_{ 0 };
};

class Chess : public Game {
public:
  explicit Chess() : Game{ 2 } {}

protected:
  void start() override {}
  bool have_winner() override { return turns_ == max_turns_; }
  void take_turn() override {
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }
  int get_winner() override {
    return current_player_;
  }

private:
  int turns_{ 0 }, max_turns_{ 10 };
};
```
## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).
