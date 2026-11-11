#include <iostream>

int main() {
  // TODO: Add a title and separator line for the calculator
  std::cout << "Rectangle Area Calculator" << '\n';
  std::cout << "========================" << '\n';

  // TODO: Declare variables for length, width, and area
  double length{};
  double width{};
  double area{};

  // TODO: Prompt and read length from user
  std::cout << "Enter the length of the rectangle: ";
  std::cin >> length;

  // TODO: Prompt and read width from user
  std::cout << "Enter the width of the rectangle: ";
  std::cin >> width;

  // TODO: Calculate the area (length times width)
  area = length * width;

  // TODO: Display the results with labels
  std::cout << '\n';
  std::cout << "Results:" << '\n';
  std::cout << "Length: " << length << '\n';
  std::cout << "Width:  " << width << '\n';
  std::cout << "Area:   " << area << '\n';

  return 0;
}
