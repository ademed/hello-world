#include <iostream>
#include <vector>
#include <deque>
#include "sequence_algorithms.hpp"

struct Animal {};

class MyArray {
 public:
  double operator[](std::size_t) { return 0.0; }
};

class custom_iterator {
 public:
  using difference_type = std::size_t;
  using value_type = double;
  using pointer = double *;
  using reference = double &;
  using iterator_category = std::random_access_iterator_tag;
  /*
   double operator[](std::size_t i) { return 0.0; }
   custom_iterator &operator++() { return *this; }
   custom_iterator &operator--() { return *this; }
   std::size_t operator-(custom_iterator) { return 0; }
   double &operator*() { return data; }
   double *operator->() { return &data; }
   double data;
   */
};
template<class T>
void print_vector(const T &v) {
  std::cout << "v = [ ";
  for (auto &element : v) std::cout << element << " ";
  std::cout << " ]" << std::endl; 
}

int main(int, char **) {
  std::size_t N = 5ul;
  std::vector<double> stdvA(N, 0.0), stdvB(N, 0.0), stdvC(N, 0.0),
      stdvD(N, 0.0), stdvE(N,10.0);
  double zero = 0.0, one = 1.0, two = 2.0, three = 3.0, four = 4.0, five = 5.0;

  std::cout << "============================================================="
            << std::endl;

  print_vector(stdvA);

  std::cout << "Pass a vector lvalue and an rvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA, 1.0);
  print_vector(stdvA);

  std::cout << "Pass a iterator rvalue and an rvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA.begin(), 2.0);
  print_vector(stdvA);

  {
    std::cout << "Pass a iterator lvalue and an rvalue" << std::endl;
    auto my_it = stdvA.begin();
    mxcpl::utilities::copy_n<>::apply(N, my_it, 3.0);
    print_vector(stdvA);
  }
  {
    std::cout << "Pass a pointer lvalue and an rvalue" << std::endl;
    double *my_ptr = stdvA.data();
    mxcpl::utilities::copy_n<>::apply(N, my_ptr, 4.0);
    print_vector(stdvA);
  }

  std::cout << "Pass a pointer rvalue and an rvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA.data(), 5.0);
  print_vector(stdvA);

  std::cout << "Pass a vector lvalue and an lvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA, one);
  print_vector(stdvA);

  std::cout << "Pass a iterator rvalue and an lvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA.begin(), two);
  print_vector(stdvA);

  std::cout << "Pass a iterator lvalue and an lvalue" << std::endl;
  auto my_it = stdvA.begin();
  mxcpl::utilities::copy_n<>::apply(N, my_it, three);
  print_vector(stdvA);

  std::cout << "Pass a pointer lvalue and an lvalue" << std::endl;
  double *my_ptr = stdvA.data();
  mxcpl::utilities::copy_n<>::apply(N, my_ptr, four);
  print_vector(stdvA);

  std::cout << "Pass a pointer rvalue and an lvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA.data(), five);
  print_vector(stdvA);

  std::cout << "Pass a pointer rvalue and a pointer rvalue" << std::endl;
  mxcpl::utilities::copy_n<>::apply(N, stdvA.data(), stdvE.data());
  print_vector(stdvA);

  std::cout << "============================================================="
            << std::endl;

  return 0;
}