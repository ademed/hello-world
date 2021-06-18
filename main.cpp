#include <iostream>
#include <omp.h>
#include <chrono>


typedef int Type;
#pragma omp declare simd uniform(x,y) linear(i:1)\
aligned(x,y:32) 
void saxpy(Type* x, Type* y, int i, Type a) {
    y[i] = a * x[i] + y[i];
}
int main1()
{
     std::size_t size = 10000000, alignment = 32; Type a = 10;
    auto x = (Type*) operator new[](sizeof(Type)* size, (std::align_val_t)(alignment));
    auto y = (Type*) operator new[](sizeof(Type)* size, (std::align_val_t)(alignment));
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (size_t j = 0; j < 1000; j++)
    {
        for (int i = 0; i < size; ++i)
        {
            saxpy(x, y, i, a);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << time/1e6 << " seconds" << std::endl;
    ::operator delete(x, std::align_val_t{ alignment });
    ::operator delete(y, std::align_val_t{ alignment });
  
    int m = 10; 
}