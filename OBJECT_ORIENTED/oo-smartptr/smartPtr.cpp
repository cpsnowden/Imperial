#include <iostream>
using namespace std;

template<class T>
class SmartPtr {
private:
    T* pObj;
    int* pRefCount;
// This private method decreases the reference count of the
// object, and deletes it if the reference count reaches zero.
// This functionality is needed by both the destructor and the
// overloaded assignment operator, so we place it in its own function
  void release() {
    if (!(pObj == 0)) {
      (*pRefCount)--;
      if (*pRefCount == 0) {
	delete pObj;
	delete pRefCount;
      }
    }
  }
  
  void copy(const SmartPtr<T>& src) {
    // Copy the pointers to the referenced object and its reference count
    pObj = src.pObj;
    pRefCount = src.pRefCount;
    // If we do not have a null pointer, increment the reference count
    if (!(pObj == 0)) {
      (*pRefCount)++;
    }
}

public:
// The default constructor
  SmartPtr() {
    pObj = 0; // a null pointer
    pRefCount = 0; // a null pointer
  }
  
  // Constructor from an existing (standard) pointer
  SmartPtr(T* obj) {
    pObj = obj;
    pRefCount = new int(1); // Initialise the reference count
  }
  
  // The copy constructor
  SmartPtr(const SmartPtr<T>& src) {
    copy(src);
  }
  
  // The Destructor calls the release method to decrement the reference count
  ~SmartPtr() {
    release();
}
  
  SmartPtr<T>& operator=(const SmartPtr<T>& src) {
    if (!(&src == this)){
      release(); // Remove the reference to the current object
      copy(src); // Copy the new reference
    }
    return *this;
  }
  
  T& operator*() {
    return *pObj;
}
  T* operator->() {
    return pObj;
  }
  
  int getRefCount() {
    if (!(pRefCount == 0)) {
      return *pRefCount;
    }
  return 0;
}
  
};

class TestClass1 {
public:
  virtual void print() {
    cout << "TestClass1 at address " << this << '\n';
  }
};

class DerivedClass: public TestClass1 {
public:
  void print() {cout << "DerivedClass at address " << this << '\n'; }
};

class TestClass2 {
  public:
  void print() {cout << "TestClass2 at address " << this << '\n'; }
};

class PtrLoop {
public:
  SmartPtr<PtrLoop> selfPtr;
  void print() { cout << "PtrLoop at address " << this << '\n'; }
};

int main() {
  // Smart Pointers work with primitive datatypes
  SmartPtr<int> spInt1(new int(5));
  SmartPtr<int> spInt2 = spInt1;

  cout << *spInt1 << '\n'; // Output: 5
  cout << *spInt2 << '\n'; // Output: 5

  *spInt1 = 3;

  cout << *spInt1 << '\n'; // Output: 3
  cout << *spInt2 << '\n'; // Output: 3
  cout << spInt1.getRefCount() << '\n'; // Output: 2
  cout << spInt2.getRefCount() << '\n'; // Output: 2

  // Check the assigning a smart pointer to itself does not increase the reference count
  
  spInt1 = spInt1;
  cout << spInt1.getRefCount() << '\n'; // Output: 2
  
  // Smart Pointers work with object (class) types too 
  SmartPtr<TestClass1> spTest1(new TestClass1());
  SmartPtr<TestClass1> spTest2(new TestClass1());

  spTest1->print(); // Output: TestClass1 at address 0x4d8590
  spTest2->print(); // Output: TestClass1 at address 0x4d85b0

  spTest1 = spTest2;

  // We can call methods on objects stored in smart pointers
  spTest1->print(); // Output: TestClass1 at address 0x4d85b0

  // We even have virtual functions behaving correctly!
  spTest1 = new DerivedClass();
  spTest1->print(); // Output DerivedClass at address 0x4d85d0

  // Our smart pointers are typesafe
  TestClass1* pTest3 = new TestClass1();
  TestClass2* pTest4 = new TestClass2();

  
  // pTest3 = pTest4
  // this gives a compiler error since TestClass1 and TestClass2
  // are NOT compatible types

  SmartPtr<TestClass1> spTest3(pTest3);
  SmartPtr<TestClass2> spTest4(pTest4);

  // spTest3 = spTest4;
  // This should also give a compiler error: no match for operator=
  // Now we test that memory is reclaimed
  {
    SmartPtr<TestClass2> spTest5(pTest4);
  } // 'last' reference to TestClass2 object goes out of scope here

  // *pTest4;
  // This should give a runtime error because the object
  // at this memory address has been deleted

  // A 'test' handle to a PtrLoop object
  PtrLoop* pLoop = new PtrLoop();
  // A new scope block: in here we will create a smart pointer reference to
  // the loop object and make it point to itself so that even when our last
  // reference to the object in the main body of the program is lost the
  // object is not deleted from memory
  cout << "Ploop address: " << pLoop << endl;
  {
    // Create the object and reference it by a smart pointer
    SmartPtr<PtrLoop> spLoop(pLoop);
    // Make it point to itself
    cout << "spLoop Address: " << &spLoop << endl;
    cout << spLoop.getRefCount() << '\n';
    spLoop->selfPtr = spLoop; //will invoke copy on spLoop thus increasing the
			      //ref count on pLoop so when destructor is called
			      //will not delete
    cout << spLoop.getRefCount() << '\n';
  }
  // This does NOT cause a runtime error as the object still exists in memory
  pLoop->print(); // Output: PtrLoop at address 0x4d8600


  {
    // Create the object and reference it by a smart pointer
    SmartPtr<PtrLoop> spLoop(new PtrLoop());
    // Make it point to itself
    cout << "spLoop Address: " << &spLoop << endl;
    cout << spLoop.getRefCount() << '\n';
    spLoop->selfPtr = spLoop; //will invoke copy on spLoop thus increasing the
			      //ref count on pLoop so when destructor is called
			      //will not delete
    cout << spLoop.getRefCount() << '\n';
  }
  
  return 0;

}
