#include <iostream>
#include <vector>
#include <stack>
#include <deque>

#include "mxcpl_type_traits.hpp"

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

int main(int argc, char *argv[]) {
  std::cout << "============================================================="
            << std::endl;
  std::cout
      << "Is std::vector<double> iterable? "
      << mxcpl::type_traits::is_iterable_v<std::vector<double> > << std::endl;
  std::cout << "Is double iterable? "
            << mxcpl::type_traits::is_iterable_v<double> << std::endl;
  std::cout << "Is Animal iterable? "
            << mxcpl::type_traits::is_iterable_v<Animal> << std::endl;
  std::cout << "Is MyArray iterable? "
            << mxcpl::type_traits::is_iterable_v<MyArray> << std::endl;
  std::cout << "Is double* iterable? "
            << mxcpl::type_traits::is_iterable_v<double *> << std::endl;
  std::cout << "Is Animal* iterable? "
            << mxcpl::type_traits::is_iterable_v<Animal *> << std::endl;
  std::cout << "Is std::vector<double>::const_iterator iterable? "
            << mxcpl::type_traits::is_iterable_v<
                   std::vector<double>::const_iterator> << std::endl;
  std::cout << "Is std::vector<double>::iterator iterable? "
            << mxcpl::type_traits::is_iterable_v<
                   std::vector<double>::iterator> << std::endl;
  std::cout << "Is std::vector<Animal>::reverse_iterator iterable? "
            << mxcpl::type_traits::is_iterable_v<
                   std::vector<double>::reverse_iterator> << std::endl;
  std::cout << "Is custom_iterator iterable? "
            << mxcpl::type_traits::is_iterable_v<custom_iterator> << std::endl;
  std::cout << "============================================================="
            << std::endl;
  std::cout << "Is double * indexable_object? "
            << mxcpl::type_traits::is_indexable_object_v<double *> << std::endl;
  std::cout << "Is double indexable_object? "
            << mxcpl::type_traits::is_indexable_object_v<double> << std::endl;
  std::cout << "Is Animal indexable_object? "
            << mxcpl::type_traits::is_indexable_object_v<Animal> << std::endl;
  std::cout << "Is std::vector<double>::iterator indexable_object with index "
               "of type int? "
            << mxcpl::type_traits::is_indexable_object_v<std::vector<double>,
                                                         int> << std::endl;
  std::cout
      << "Is std::vector<double> indexable_object with index of type int? "
      << mxcpl::type_traits::is_indexable_object_v<std::vector<double>,
                                                   int> << std::endl;
  std::cout
      << "Is std::vector<double> indexable_object with index of type size_t? "
      << mxcpl::type_traits::is_indexable_object_v<std::vector<double>,
                                                   std::size_t> << std::endl;
  std::cout << "Is std::vector<double> indexable_object with index of type "
               "std::vector<double>? "
            << mxcpl::type_traits::is_indexable_object_v<
                   std::vector<double>, std::vector<double> > << std::endl;
  std::cout << "Is MyArray indexable_object with index std::size_t? "
            << mxcpl::type_traits::is_indexable_object_v<
                   MyArray, std::size_t> << std::endl;
  std::cout << "Is MyArray indexable_object with index int? "
            << mxcpl::type_traits::is_indexable_object_v<MyArray> << std::endl;
  std::cout << "Is MyArray indexable_object with index Animal? "
            << mxcpl::type_traits::is_indexable_object_v<MyArray,
                                                         Animal> << std::endl;
  std::cout << "============================================================="
            << std::endl;
  std::cout << "Is double * indexable? "
            << mxcpl::type_traits::is_indexable_v<double *> << std::endl;
  std::cout << "Is double indexable? "
            << mxcpl::type_traits::is_indexable_v<double> << std::endl;
  std::cout << "Is Animal indexable? "
            << mxcpl::type_traits::is_indexable_v<Animal> << std::endl;
  std::cout
      << "Is std::vector<double>::iterator indexable with index of type int? "
      << mxcpl::type_traits::is_indexable_v<std::vector<double>,
                                            int> << std::endl;
  std::cout << "Is std::vector<double> indexable with index of type int? "
            << mxcpl::type_traits::is_indexable_v<std::vector<double>,
                                                  int> << std::endl;
  std::cout << "Is std::vector<double> indexable with index of type size_t? "
            << mxcpl::type_traits::is_indexable_v<std::vector<double>,
                                                  std::size_t> << std::endl;
  std::cout << "Is std::vector<double> indexable with index of type "
               "std::vector<double>? "
            << mxcpl::type_traits::is_indexable_v<
                   std::vector<double>, std::vector<double> > << std::endl;
  std::cout
      << "Is MyArray indexable with index std::size_t? "
      << mxcpl::type_traits::is_indexable_v<MyArray, std::size_t> << std::endl;
  std::cout << "Is MyArray indexable with index int? "
            << mxcpl::type_traits::is_indexable_v<MyArray> << std::endl;
  std::cout << "Is MyArray indexable with index Animal? "
            << mxcpl::type_traits::is_indexable_v<MyArray, Animal> << std::endl;
  std::cout << "============================================================="
            << std::endl;

  std::cout
      << "Is Stack indexable with index std::size_t? "
      << mxcpl::type_traits::is_indexable_v<std::stack<double>, std::size_t> << std::endl;
  std::cout << "Is Stack indexable with index int? "
      << mxcpl::type_traits::is_indexable_v<std::stack<double>> << std::endl;
  std::cout << "Is Stack iterable "
      << mxcpl::type_traits::is_indexable_v<std::stack<double>> << std::endl;
  std::cout << "============================================================="
      << std::endl;


  std::cout
      << "Is Deque indexable with index std::size_t? "
      << mxcpl::type_traits::is_indexable_v<std::deque<double>, std::size_t> << std::endl;
  std::cout << "Is Deque indexable with index int? "
      << mxcpl::type_traits::is_indexable_v<std::deque<double>> << std::endl;
  std::cout << "Is Deque iterable "
      << mxcpl::type_traits::is_indexable_v<std::deque<double>> << std::endl;
  std::cout << "============================================================="
      << std::endl;
  return 0;
}