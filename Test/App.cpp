#include <iostream>
#include <vector>

class Father {
 public:
  int i = 0;
  void fn1() const{
    std::cout<<this->i<<std::endl;
    fn2();
  }
  virtual void fn2() const =  0;
};

class Son1 : public Father {
 public:
  int i = 1;
  void fn2() const override {
    std::cout<<this->i<<std::endl;
  }
};

class Son2 : public Father {
 public:
  int i = 2;
  void fn2() const override {
    std::cout<<this->i<<std::endl;
  }
};

int main() {
  auto v = Son1();
  v.fn1();
  v.fn2();
}