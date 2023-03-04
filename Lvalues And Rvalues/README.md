# Lvalues And Rvalues
<b>Lvalues</b>: Lvalues are values which can come to the left side or right side of an expression. Modifiable Lvalues can be assigned a new value.
```
int x = 5, Here x is a modifiable Lvalue.
x = 10, Here x can be assigned a new value
const int x = 5, Here x is a non modifiable Lvalue
int y = x, Here y and x both are Lvalues
```

<b>Rvalues</b>: Rvalues are those values which can come only in right side of expression. These values cannot be assigned to a new value. Rvalues are temporary data which exists only till the expression is over.
```
int x = 5, Here 5 is an Rvalue. The lifetime of the address which contains 5 is only till this expression. After the expression, the memory is freed.
int list[10];
list[5] = 20; list[5] is a Lvalue, 20 is an Rvalue.

int foo(){
  return 5;
}

foo() = 10; // Error because foo() is a Rvalue

int y;
int &bar(){
  return y;
}

bar() = 10; // Valid. Because bar() is a Lvalue in this case
```

## Lvalue References
As the name suggests, these are references to Lvalues.
```
int x = 5;
int &y = x; // y is a Lvalue reference

int &z = 5; // Error because 5 is not an Lvalue.

Constant lvalue references can be assigned rvalues. Since they're constant, the value can't be modified through the reference and hence there's no problem of modifying an rvalue.
const int &p = 5; // Valid. Because p cannot be assigned another value

```

## Rvalue References
These are references to Rvalues. Rvalue references cannot be assigned a Lvalue
```
int &&x = 5; // x is a Rvalue reference. Rvalue references are denoted by && (Two ampersands)

int x, y, z;
int &r = x; // valid
int &r2 = (x + y); // Invalid. Because (x + y) is a Rvalue
const int &r3 = (x + y); // valid. Because Rvalues can be assigned to constant Lvalue references.
int &&r4 = (x + y); // valid. r4 is an r value reference.

In the last two cases, the lifetime of the temporary location for (x + y) is extended till the lifetime of r3 or r4.
```

## Passing parameters in functions
```
  void foo(int x); // pass by value
  void foo2(int &x); // pass by reference. The reference value can be changed. 
  void foo3(const int &x); // pass by const reference. The reference value cannot be changed. Accepts Rvalues.
  void foo4(int &&x); // pass by r value reference. Will not accept Lvalues.
  
```

```
#include <iostream>

void foo(int &x){
    std::cout << "foo(int &x)" << std::endl;
}

void foo(const int &x){
    std::cout << "foo(const int &x)" << std::endl;
}

void foo(int &&x){
    std::cout << "foo(int &&x)" << std::endl;
}

int main(){

    foo(5); // foo(int &&x) function would be called. If foo(int &&x) was not there, then foo(const int &x) would be called.
    return 0;
}
```

## What is the use of Rvalues
Rvalues are
