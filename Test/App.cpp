#include <iostream>
#include <vector>

#include <Tools/Timer.h>
using namespace std;
template<typename T, unsigned B>
struct Base
{
    //other function
    //....
    template<unsigned N>
    void FuncImpl()
    {
        cout<<"primary function"<<endl;
    }
    template<>
    void FuncImpl<16>()
    {
        cout<<"specialization function"<<endl;
    }
    void Func()
    {
        FuncImpl<B>();
    }
};

int main() {
  Just::Timer timer;
}