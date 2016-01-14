#include <iostream>
#include <string>
using namespace std;

class Expression {
public:
  virtual int value() const = 0;
  virtual string toString() const = 0;
};

class Number : public Expression {
  int _value;
public:
  Number(int value) : _value(value) {}
  int value() const {
    return _value;
  }
  string toString() const {
    return to_string(_value);
  }
};

class LBinary : public Expression {
  Expression &_left, &_right;
protected:
   virtual int calculate(int v1, int v2) const = 0;
public:
  LBinary(Expression &left, Expression &right) : _left(left), _right(right) {}
  Expression &left() const {
    return _left;
  }
  Expression &right() const {
    return _right;
  }
  virtual const char *symbol() const = 0;
  virtual int value() const {
    int left_value = _left.value();
    int right_value = _right.value();
    int result = calculate(left_value, right_value);
    return result;
    // one-line version: return calculate(_left.value(), _right.value());
  }
  string toString() const {
    string _left =  "(" + left().toString() + ")";
    string _op = symbol();
    string _right = "(" + right().toString() + ")";
    return _left + _op + _right;
  }
};

class Addition : public LBinary {
protected:
  virtual int calculate(int v1, int v2) const {
    return v1 + v2;
  }
public:
  Addition(Expression &left, Expression &right) : LBinary(left, right) {}
  virtual const char *symbol() const {
    return "+";
  }
};

class Multiplication : public LBinary {
protected:
  virtual int calculate(int v1, int v2) const {
    return v1 * v2;
  }
public:
  Multiplication(Expression &l, Expression &r) : LBinary(l, r) {}
  virtual const char *symbol() const {
    return "*";
  }
};

ostream &operator <<(ostream &o, const Expression &e) {

  o << e.toString() << "=" << e.value();
  return o;
  
}

int main() {
  Number n2(2), n3(3), n_1(-1); cout << n_1 << endl;
// SIMPLE OUTPUT : -1 = -1
// MINIMUM OUTPUT: -1 = -1
Addition a1(n2, n_1);
cout << a1 << endl;
// SIMPLE OUTPUT : (2)+(-1) = 1 // MINIMUM OUTPUT: 2+(-1) = 1
Addition a2(n_1, n3);
cout << a2 << endl;
// SIMPLE OUTPUT : (-1)+(3) = 2 // MINIMUM OUTPUT: -1+3 = 2
Multiplication m1(n3, a1);
cout << m1 << endl;
// SIMPLE OUTPUT : (3)*((2)+(-1)) = 3 // MINIMUM OUTPUT: 3*(2+(-1)) = 3
Addition a3(m1, a1);
cout << a3 << endl;
// SIMPLE OUTPUT : ((3)*(2+(-1)))+(2+(-1)) = 4 // MINIMUM OUTPUT: 3*(2+(-1))+(2+(-1)) = 4
Addition a4(a1, m1);
cout << a4 << endl;
// SIMPLE OUTPUT : ((2)+(-1))+((3)*(2+(-1))) = 4 // MINIMUM OUTPUT: 2+(-1)+3*(2+(-1)) = 4
}
