#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Task {
  std::string description{};
  bool is_done{false};
};

enum class MenuChoices { EarlyExit = -1, ListTasks = 1, AddTask = 2, ToggleTaskStatus = 3, DeleteTask = 4, EditTask = 5, DeleteCompletedTasks = 6, SaveToFile = 7, ReloadFromFile = 8, Quit = 9 };

// Show the application menu
void show_menu();

// Prompts until the user enters a whole number, then returns it.
int read_int(const std::string& prompt);

// Handle the user
bool handle_user_choice(int menu_choice, std::vector<Task>& tasks, const std::string& file_name);

// Clear the buffer
void clear_buffer(std::istream& is);

// Prompts once and returns the whole line the user typed.
std::string read_line(const std::string& prompt);

// Turns a task into the one-line form used on screen and in the file.
std::string format_task(const Task& task);

// Rebuilds a task from a saved line. Returns false if the line is malformed.
bool parse_task(std::string line, Task& task);

// Check if the task's index is in range
bool check_task_id(int task_id, std::size_t vector_size);

void list_tasks(const std::vector<Task>& tasks);
void add_task(std::vector<Task>& tasks);
void toggle_task(std::vector<Task>& tasks);
void delete_task(std::vector<Task>& tasks);
void edit_task(std::vector<Task>& tasks);
void delete_completed_task(std::vector<Task>& tasks);

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
    std::cout << "Tasks loaded from todo.txt";
  } else {
    std::cout << "No saved list found. Starting with an empty list.";
  }

  std::cout << "\n\n";

  // TODO: Show a numbered menu: list, add, complete, delete, save, reload,
  //       and quit. Read the choice as a whole number. If the user types
  //       something that is not a number, call std::cin.clear(), discard the
  //       rest of the line with std::cin.ignore(...), and ask again.
  show_menu();

  while (!exit) {
    int choice{read_int("Choose an option: ")};

    exit = handle_user_choice(choice, tasks, file_name);

    std::cout << '\n';
  }

  return 0;
}

void show_menu() {
  std::cout << "1. List tasks" << '\n';
  std::cout << "2. Add a task" << '\n';
  std::cout << "3. Toggle task status" << '\n';
  std::cout << "4. Delete a task" << '\n';
  std::cout << "5. Edit a task" << '\n';
  std::cout << "6. Delete completed tasks" << '\n';
  std::cout << "7. Save to file" << '\n';
  std::cout << "8. Reload from file" << '\n';
  std::cout << "9. Quit" << '\n';
}

void clear_buffer(std::istream& is) {
  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string read_line(const std::string& prompt) {
  std::string t_description{};

  clear_buffer(std::cin);

  std::cout << prompt;
  std::getline(std::cin >> std::ws, t_description);

  return t_description;
}

std::string format_task(const Task& task) {
  std::string formatted_task{"[ ] "};

  if (task.is_done) {
    formatted_task[1] = 'x';
  }

  formatted_task.append(task.description);

  return formatted_task;
}

bool parse_task(std::string line, Task& task) {
  if (line[1] == 'x') {
    task.is_done = true;
  } else if (line[1] == ' ') {
    task.is_done = false;
  } else {
    return false;
  }

  constexpr std::size_t start_description_index{4};

  task.description = line.substr(start_description_index, std::string::npos);

  return true;
}

int read_int(const std::string& prompt) {
  int prompt_choice{};

  while (true) {
    std::cout << prompt;

    if (!(std::cin >> prompt_choice)) {
      if (std::cin.eof()) {
        return -1;
      }

      std::cout << "That is not a whole number. Please try again." << '\n';
      clear_buffer(std::cin);
      continue;
    }

    return prompt_choice;
  }
}

bool handle_user_choice(int menu_choice, std::vector<Task>& tasks, const std::string& file_name) {
  // TODO: Dispatch on the choice with a switch statement, one case per menu
  //       option, and a default case for numbers that are not on the menu.
  switch (static_cast<MenuChoices>(menu_choice)) {
    case MenuChoices::ListTasks:
      list_tasks(tasks);
      return false;
    // TODO: Add a task. Read the whole description line, reject it if it is
    //       blank, and append a new task to the end of the vector.
    case MenuChoices::AddTask:
      add_task(tasks);
      break;
    // TODO: Complete, delete or edit a task. Ask for the task number the user sees
    //       in the list, check it is between 1 and the number of tasks, then
    //       convert it to a zero-based index before touching the vector.
    case MenuChoices::ToggleTaskStatus:
      toggle_task(tasks);
      return false;
    case MenuChoices::DeleteTask:
      delete_task(tasks);
      return false;
    case MenuChoices::EditTask:
      edit_task(tasks);
      return false;
    case MenuChoices::DeleteCompletedTasks:
      delete_completed_task(tasks);
      return false;
    // TODO: Save the list. Open the save file with std::ofstream and write one
    //       task per line in a format you can parse again later.
    case MenuChoices::SaveToFile:
      if (save_tasks(tasks, file_name)) {
        std::cout << "Saved " << tasks.size() << " task(s) to todos.txt.";
      } else {
        std::cout << "Error during the saving of the tasks in the file.";
      }
      return false;
    // TODO: Reload the list from the file, replacing whatever is in memory.
    case MenuChoices::ReloadFromFile:
      if (load_tasks(tasks, file_name)) {
        std::cout << "Reloaded " << tasks.size() << " task(s) to todos.txt.";
      } else {
        std::cout << "Error during the reload of the tasks froms the file.";
      }
      break;
    // TODO: Keep showing the menu until the user chooses quit.
    case MenuChoices::Quit:
      std::cout << "Goodbye.";
      return true;
    case MenuChoices::EarlyExit:
      if (save_tasks(tasks, file_name)) {
        std::cout << "Early exit, autosave...";
      }
      return true;
    default:
      std::cout << "Invalid menu choice";
  }

  return false;
}

bool check_task_id(int task_id, std::size_t vector_size) { return (task_id < 1 || static_cast<std::size_t>(task_id) > vector_size) ? false : true; }

void list_tasks(const std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks to show.";
    return;
  }

  std::cout << "Your tasks:";
  for (std::size_t idx{0}; idx < tasks.size(); ++idx) {
    std::cout << '\n';
    std::cout << "  " << (idx + 1) << ". " << format_task(tasks[idx]);
  }
}

void add_task(std::vector<Task>& tasks) {
  std::string new_task_description{read_line("Task description: ")};

  if (new_task_description.empty()) {
    std::cout << "The task description is blank.";
    return;
  }

  tasks.emplace_back(Task{new_task_description});
  std::cout << "Added task " << (tasks.size()) << ".";
}

void toggle_task(std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks in the list.";
    return;
  }

  int task_number{read_int("Task number to complete: ")};
  if (!check_task_id(task_number, tasks.size())) {
    std::cout << "There is no task " << task_number;
    return;
  }

  std::size_t task_index{static_cast<std::size_t>(task_number - 1)};

  if (tasks[task_index].is_done) {
    std::cout << "Toggle task \"" << tasks[task_index].description << "\" as not done.";
  } else {
    std::cout << "Toggle task \"" << tasks[task_index].description << "\" as done.";
  }

  tasks[task_index].is_done = !tasks[task_index].is_done;
}

void delete_task(std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks in the list.";
    return;
  }

  int task_number{read_int("Task number to delete: ")};
  if (!check_task_id(task_number, tasks.size())) {
    std::cout << "There is no task " << task_number << ".";
    return;
  }

  std::cout << "Deleted \"" << tasks[static_cast<std::size_t>(task_number - 1)].description << "\".";

  tasks.erase(tasks.begin() + static_cast<std::ptrdiff_t>(task_number - 1));
}

void edit_task(std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks in the list.";
    return;
  }

  int task_number{read_int("Task number to edit: ")};
  if (!check_task_id(task_number, tasks.size())) {
    std::cout << "There is no task " << task_number << ".";
    return;
  }

  std::string edited_task_description{read_line("New task description: ")};

  tasks[task_number - 1].description = edited_task_description;

  std::cout << "Edited task " << task_number << ". description.";
}

void delete_completed_task(std::vector<Task>& tasks) {
  if (tasks.empty()) {
    std::cout << "There are no tasks in the list.";
    return;
  }

  auto it{std::remove_if(tasks.begin(), tasks.end(), [](const Task& current_task) { return current_task.is_done; })};

  tasks.erase(it, tasks.end());

  std::cout << "Completed tasks deleted";
}

bool save_tasks(const std::vector<Task>& tasks, const std::string& file_name) {
  std::ofstream file{file_name};

  if (!file.is_open()) {
    return false;
  }

  for (const auto& task : tasks) {
    file << format_task(task) << '\n';
  }

  return true;
}

bool load_tasks(std::vector<Task>& tasks, const std::string& file_name) {
  std::ifstream file{file_name};

  if (!file.is_open()) {
    return false;
  }

  std::string line{};

  while (std::getline(file, line)) {
    Task new_task{};
    if (parse_task(line, new_task)) {
      tasks.push_back(new_task);
      continue;
    }

    return false;
  }

  return true;
}