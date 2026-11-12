#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Task {
  std::string description{};
  bool is_done{};
};

// Prompts until the user enters a whole number, then returns it.
int read_int(const std::string& prompt);

// Prompts once and returns the whole line the user typed.
std::string read_line(const std::string& prompt);

// Turns a task into the one-line form used on screen and in the file.
std::string format_task(const Task& task);

// Rebuilds a task from a saved line. Returns false if the line is malformed.
bool parse_task(std::string line, Task& task);

void list_tasks(const std::vector<Task>& tasks);
void add_task(std::vector<Task>& tasks);
void complete_task(std::vector<Task>& tasks);
void delete_task(std::vector<Task>& tasks);

// Return false if the file could not be opened.
bool save_tasks(const std::vector<Task>& tasks, const std::string& fileName);
bool load_tasks(std::vector<Task>& tasks, const std::string& fileName);

int main() {
  // TODO: Describe a single task. Define a struct that holds the task's
  //       description as a std::string and whether it is done as a bool.
  //       Then create an empty std::vector of that struct to hold the list.

  // TODO: Load the saved list. Open the save file with std::ifstream. If it
  //       opened, read it one line at a time with std::getline, turn each
  //       line back into a task, and add it to the vector. If it did not
  //       open, tell the user they are starting with an empty list.

  // TODO: Show a numbered menu: list, add, complete, delete, save, reload,
  //       and quit. Read the choice as a whole number. If the user types
  //       something that is not a number, call std::cin.clear(), discard the
  //       rest of the line with std::cin.ignore(...), and ask again.

  // TODO: Dispatch on the choice with a switch statement, one case per menu
  //       option, and a default case for numbers that are not on the menu.

  // TODO: Add a task. Read the whole description line, reject it if it is
  //       blank, and append a new task to the end of the vector.

  // TODO: Complete or delete a task. Ask for the task number the user sees
  //       in the list, check it is between 1 and the number of tasks, then
  //       convert it to a zero-based index before touching the vector.

  // TODO: Save the list. Open the save file with std::ofstream and write one
  //       task per line in a format you can parse again later.

  // TODO: Reload the list from the file, replacing whatever is in memory.

  // TODO: Keep showing the menu until the user chooses quit.

  return 0;
}
