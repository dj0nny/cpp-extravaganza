#include <iostream>

int main() {
  std::cout << "Personal Stats" << '\n';
  std::cout << "==============" << '\n';

  // TODO: Change variables above to use default initialization (empty braces)
  int age{};
  double height{};

  // TODO: Prompt user for age and read input
  std::cout << "Enter your age: ";
  std::cin >> age;

  // TODO: Prompt user for height and read input
  std::cout << "Enter your height (in feet): ";
  std::cin >> height;

  // TODO: Update the output section below to have a "Your Stats:" header
  std::cout << "\nYour Stats:" << '\n';
  std::cout << "Age: " << age << " years" << '\n';
  std::cout << "Height: " << height << " feet" << '\n';

  return 0;
}
