#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Task {
  std::string description{};
  bool is_done{false};
};

enum class MenuChoices { ListTasks = 1, AddTask = 2, MarkAsComplete = 3, DeleteTask = 4, SaveToFile = 5, ReloadFromFile = 6, Quit = 7 };

// Show the application menu
void show_menu();

// Prompts until the user enters a whole number, then returns it.
int read_int(const std::string& prompt);

// Clear the buffer
void clear_buffer(std::istream& is);

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
  std::vector<Task> tasks{};
  const std::string file_name{"tasks.txt"};
  bool exit{false};

  std::cout << "=== To-Do List Manager ===" << '\n';

  // TODO: Load the saved list. Open the save file with std::ifstream. If it
  //       opened, read it one line at a time with std::getline, turn each
  //       line back into a task, and add it to the vector. If it did not
  //       open, tell the user they are starting with an empty list.
  if (load_tasks(tasks, file_name)) {
  } else {
    std::cout << "No saved list found. Starting with an empty list." << "\n\n";
  }

  // TODO: Show a numbered menu: list, add, complete, delete, save, reload,
  //       and quit. Read the choice as a whole number. If the user types
  //       something that is not a number, call std::cin.clear(), discard the
  //       rest of the line with std::cin.ignore(...), and ask again.
  show_menu();

  while (!exit) {
    int choice{read_int("Choose an option: ")};

    // TODO: Dispatch on the choice with a switch statement, one case per menu
    //       option, and a default case for numbers that are not on the menu.
    switch (static_cast<MenuChoices>(choice)) {
      case MenuChoices::ListTasks:
        list_tasks(tasks);
        break;
      case MenuChoices::AddTask:
        // TODO: Add a task. Read the whole description line, reject it if it is
        //       blank, and append a new task to the end of the vector.
        add_task(tasks);
        break;
      case MenuChoices::MarkAsComplete:
        std::cout << "Mark a task complete" << '\n';
        break;
      case MenuChoices::DeleteTask:
        std::cout << "Delete a task" << '\n';
        break;
      case MenuChoices::SaveToFile:
        std::cout << "Save to file" << '\n';
        break;
      case MenuChoices::ReloadFromFile:
        std::cout << "Reload from file" << '\n';
        break;
      case MenuChoices::Quit:
        std::cout << "Goodbye." << '\n';
        exit = true;
        break;
      default:
        std::cout << "Invalid menu choice" << '\n';
    }

    std::cout << '\n';
  }
  // TODO: Complete or delete a task. Ask for the task number the user sees
  //       in the list, check it is between 1 and the number of tasks, then
  //       convert it to a zero-based index before touching the vector.

  // TODO: Save the list. Open the save file with std::ofstream and write one
  //       task per line in a format you can parse again later.

  // TODO: Reload the list from the file, replacing whatever is in memory.

  // TODO: Keep showing the menu until the user chooses quit.

  return 0;
}

void show_menu() {
  std::cout << "1. List tasks" << '\n';
  std::cout << "2. Add a task" << '\n';
  std::cout << "3. Mark a task complete" << '\n';
  std::cout << "4. Delete a task" << '\n';
  std::cout << "5. Save to file" << '\n';
  std::cout << "6. Reload from file" << '\n';
  std::cout << "7. Quit" << '\n';
}

void clear_buffer(std::istream& is) {
  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void list_tasks(const std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks to show.";
    return;
  }
}

int read_int(const std::string& prompt) {
  int prompt_choice{};

  while (true) {
    std::cout << prompt;

    if (!(std::cin >> prompt_choice)) {
      std::cout << "That is not a whole number. Please try again." << '\n';
      clear_buffer(std::cin);
      continue;
    }

    return prompt_choice;
  }
}

void add_task(std::vector<Task>& tasks) {
  std::string new_task_description{};

  clear_buffer(std::cin);

  std::cout << "Task description: ";
  std::getline(std::cin >> std::ws, new_task_description);

  if (new_task_description.empty()) {
    std::cout << "The task description is blank.";
    return;
  }

  tasks.emplace_back(new_task_description);
  std::cout << "Added task " << (tasks.size()) << ".";
}

bool load_tasks(std::vector<Task>& tasks, const std::string& fileName) { return false; }