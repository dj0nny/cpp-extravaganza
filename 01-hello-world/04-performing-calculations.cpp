#include <iostream>

int main() {
  std::cout << "Personal Stats Calculator" << '\n';
  std::cout << "=========================" << '\n';

  // TODO: Update title to "Personal Stats Calculator" with matching separator

  int age{};
  double height{};

  std::cout << "Enter your age: ";
  std::cin >> age;

  std::cout << "Enter your height (in feet): ";
  std::cin >> height;

  std::cout << "\nYour Stats:" << '\n';
  std::cout << "Age: " << age << " years" << '\n';
  std::cout << "Height: " << height << " feet" << '\n';

  // TODO: Declare and calculate age in months (age * 12) in a single line
  int age_in_months{age * 12};

  // TODO: Display the age in months
  std::cout << "Age in months: " << age_in_months;

  return 0;
}
