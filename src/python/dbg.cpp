#include <iostream>

template <class T1>
class Foo {

  template <class T2>
  Foo(T1 x, T2 y) {
    std::cout << x << " " << y << std::endl;
  }

};

int main(int argc, char **argv) {
  //Foo<int> foo = Foo<int>(1, 2);
}
