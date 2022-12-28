#include <iostream>
#include "Polinom.h"
int main()
{
  int x, y, z;
  TPolinom* p;
  TPolinom* p2;
  p = new TPolinom();
  p2 = new TPolinom();

  std::cout << "Enter polynom 1: " << std::endl;
  std::cin >> *p;
  std::cout << "Enter polynom 2: " << std::endl;
  std::cin >> *p2;

  std::cout << "polynom 1: " << std::endl << *p << std::endl;
  std::cout << "polynom 2: " << std::endl << *p2 << std::endl;

  std::cout << "Sum of polynoms = " << *p + *p2 << std::endl;

  std::cout << "Calculating of polynoms: " << std::endl;
  std::cout << "Enter x" << std::endl;
  std::cin >> x;
  std::cout << "Enter y" << std::endl;
  std::cin >> y;
  std::cout << "Enter z" << std::endl;
  std::cin >> z;
  std::cout << "Polynom 1 = " << p->CalculatePolinom(x, y, z) << std::endl;
  std::cout << "Polynom 2 = " << p2->CalculatePolinom(x, y, z) << std::endl;
  return 0;
}