#include "Workspace.hpp"
#include "gtest/gtest.h"

#include <climits>

using ::testing::AtLeast;

/*
  Casting in general
    https://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Variables/Type_Casting
*/

TEST(static_cast_test, something){
  /*
  static_cast:
    Relies on compiltime information (static type information). You ma use it to:
    1) convert arithmetic conversations
    2) int to enum
    3) size conversations
    4) diffrent types
    5) convert reference of type a object &x to type b object &y with relation ship
    6) same goes with objects and pointer to member within the same
    class hirarcy.

    http://www.cpp-home.com/tutorials/2_2.htm
  */

// 1) arithmetic conversations
int middleOfArray = static_cast<int>(19/2);
std::cout<<"The result is an int: " << middleOfArray << std::endl;

//2) int to enum
enum class symbol:int {A = 1, B = 2};
int value = static_cast<int>(symbol::A);
std::cout << "This is the converted enum value: " << value << std::endl;
// this would be illegal
//value = symbol::A;

//3) size conversations
unsigned long int lValue = ULONG_MAX;
unsigned short sValue  = static_cast<unsigned short>(lValue);
std::cout <<"iValue: "<< sValue <<"\t\t sizeof():" << sizeof(unsigned short) <<std::endl;
std::cout <<"lValue: "<< lValue <<"\t sizeof():" << sizeof(unsigned long int)<< std::endl;

//4) diffrent types
int iValue = 1;
float fValue = static_cast<float>(iValue);
std::cout << "This is the converted float value: " << fValue << std::endl;

//5) convert reference of type a object &x to type b object &y with relation ship
struct A {
  int first = 1;
  float second = 2;
}objA;
struct B:A{
  double third = 3;
}objB;

objB.first = 5;
objA = static_cast<A>(objB);
std::cout << "This is the converted objA first: " << objA.first << std::endl;
std::cout << "This is the converted objA second: " << objA.second << std::endl;

//6) same goes with objects and pointer to member within the same
//class hirarcy.

class classA {
public:
  int first = 1;
  float second = 2;
};
class classB:public classA{
  double third = 3;
};
classB *cobjB = new classB();
classA *cobjA = static_cast<classA*>(cobjB);
/*
   Note that static cast relies on compiltime information, this is only possible
   for non-polymorphic classes. A polymorphic class is a class containing a virtual
   function which is also concidered as dynamic polymorphism, the counter part is
   Curiously Recurring Template Pattern (CRTP).
   see http://www.cplusplus.com/forum/general/169991/
*/
std::cout << "This is the converted cobjA first: " << cobjA->first << std::endl;
std::cout << "This is the converted cobjA second: " << cobjA->second << std::endl;

//6) same goes with objects and pointer to member within the same
//class hirarcy.
class cBase
{
  int member = 0;
public:
  virtual void do_something(){ std::cout<< "Hello Base" << std::endl; };
};

class cDerived : public cBase{
public:
  void do_something() override { std::cout << "Hello Derived" << std::endl; }
  void something_else(){ std::cout << "This is an exclusive function" << std::endl; }
};
class cDiffrent{
  int member = 0;
public:
  virtual void something_diffrent(){ std::cout<< "Hello what" << std::endl; };
};

cBase baseObj;
cDerived derivedObj;
cDiffrent diffrentObj;

cBase *pBase = static_cast<cBase*>(&derivedObj);
cDerived *pDerived = static_cast<cDerived*>(&baseObj); // shuld not be used
// https://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast#1255015
pBase->do_something(); // calls derived func
pDerived->do_something(); // calls base func

//pBase = static_cast<cBase*>(&diffrentObj); // invalid

}

TEST(dynamic_cast_test, something){
  /*
    dynamic_cast:
      - only for pointer and references
      1) derived class pointer to base class
      2) base class pointer to derived class
  */
  class cBase{
    int member = 0;
  public:
    virtual void do_something(){ std::cout<< "Hello Base" << std::endl; };
  };

  class cDerived : public cBase{
  public:
    void do_something() override { std::cout << "Hello Derived" << std::endl; }
    void something_special_in_derived(){ std::cout << "This is an exclusive derived function" << std::endl; }
  };

  class cSibling : public cBase{
  public:
    void do_something() override { std::cout << "Hello Sibling" << std::endl; }
      void something_special_in_sibling(){ std::cout << "This is an exclusive sibling function" << std::endl; }
  };

  //  1) derived class pointer to base class
  cBase baseObj;
  cDerived derivedObj;
  cSibling siblingObj;

  cBase *pBase = dynamic_cast<cBase*>(&derivedObj);

  if(pBase)
    pBase->do_something();

  //2) derived class pointer to sibling
  cDerived *pDerived = dynamic_cast<cDerived*>(&baseObj);

  if(pDerived) //does never succeed
    pDerived->do_something();

  std::function<void(cBase &)> f = [](cBase &ref){
    cDerived *pD = dynamic_cast<cDerived*>(&ref);
    cSibling *pS = dynamic_cast<cSibling*>(&ref);
    if(pD)
     pD->something_special_in_derived();
    if(pS)
     pS->something_special_in_sibling();
  };
 std::cout << "--->" << std::endl;
 f(baseObj);
 f(derivedObj);
 f(siblingObj);
}

TEST(reinterpret_cast_test, something){

const uintptr_t SYSCFG = 0x03FF0000;
uint32_t *const IOPMOD = reinterpret_cast<uint32_t*>(SYSCFG + 0x5000);
//IOPMOD  = reinterpret_cast<uint32_t*>(0x03FF0000 + 0x5000);

uint32_t &refIOPMOD  = reinterpret_cast<uint32_t&>(*IOPMOD);
uint32_t &refIOPMOD2  = *reinterpret_cast<uint32_t*>(0x03FF0000 + 0x5000);

std::cout << "Adress of what IOPMOD points to: " <<std::hex<< IOPMOD << std::endl;
std::cout << "Adress of refIOPMOD: " << &refIOPMOD << std::endl;
std::cout << "Adress of refIOPMOD2: " << &refIOPMOD2 << std::endl;

int *intPutter = nullptr;
float *floatPutter = reinterpret_cast<float*>(intPutter);
std::cout <<"Address of intPutter:   "<< &intPutter << std::endl;
std::cout <<"Address of floatPutter: "<< &floatPutter << std::endl;
}
