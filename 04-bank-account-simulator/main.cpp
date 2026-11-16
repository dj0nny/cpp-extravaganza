#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class MenuActions { Deposit = 1, Withdraw, ShowBalance, ShowStatement, SaveAndExit };

enum class TransactionType { Deposit, Withdrawal };

// TODO: Define a Transaction struct that records the kind of transaction
//       (deposit or withdrawal), the amount, and the balance straight after it.
//       Store every amount as a whole number of cents, never as a double.
struct Transaction {
  TransactionType type{};
  long long cents_amount;
  long long balance_after_cents{};
};

// TODO: Define an Account struct holding the owner's name, the balance in
//       cents, and a std::vector of Transaction for the history.
struct Account {
  std::string owner{};
  long long balance{};
  std::vector<Transaction> transactions{};
};

// Return a new account if not exist a previous one
Account create_new_account();

// Print application's menu
void print_menu();

// Read user's menu action
int read_menu_action();

// Handle menu's action
bool handle_menu_action(int menu_action);

// Turns a whole number of cents into text such as "$1234.05".
std::string format_cents(long long cents);

// Converts text such as "25" or "12.50" into cents, or nothing if invalid.
std::optional<long long> parse_amount(std::string_view text);

// Prompts for an amount, prints why it was rejected if it was.
std::optional<long long> read_amount(std::string_view prompt);

void deposit(Account& account, long long cents);
bool withdraw(Account& account, long long cents);
void print_statement(const Account& account);

bool save_account(const Account& account, const std::string& file_name);
std::optional<Account> load_account(const std::string& file_name);

int main() {
  // TODO: Try to load a saved account from account.txt with a std::ifstream.
  //       If there is no file, or it cannot be read, ask for the account
  //       holder's name and open a new account with a balance of zero.
  std::cout << "=== Bank Account Simulator ===" << "\n\n";

  const std::string file_name{"account.txt"};
  std::optional<Account> current_account{load_account(file_name)};

  if (current_account == std::nullopt) {
    std::cout << "No saved account found. Let's open a new one." << '\n';
    current_account = create_new_account();
  } else {
    std::cout << "Account loaded." << '\n';
  }

  std::cout << '\n';

  bool exit{};

  // TODO: Show a menu in a loop: deposit, withdraw, show balance, show
  //       statement, save and exit. Read the choice with std::getline and
  //       reject anything that is not one of the listed options.
  while (!exit) {
    print_menu();

    int menu_action{read_menu_action()};
    exit = handle_menu_action(menu_action);

    std::cout << "\n\n";
  }

  // TODO: For deposits and withdrawals, read the amount as text and convert
  //       it to cents yourself. Reject non-numbers, negative amounts, zero,
  //       and anything with more than two decimal places.

  // TODO: Refuse any withdrawal larger than the balance. The balance must
  //       never drop below zero. Record every accepted transaction.

  // TODO: Print money as dollars and cents with <iomanip>, padding the cents
  //       to two digits so 5 cents prints as $0.05, not $0.5.

  // TODO: On save and exit, write the owner, the balance, and the history to
  //       account.txt with a std::ofstream, report whether it worked, and
  //       return 0.

  return 0;
}

Account create_new_account() {
  Account new_account{};

  std::cout << "Account holder name: ";
  std::getline(std::cin >> std::ws, new_account.owner);

  std::cout << "Account opened for " << new_account.owner << " with a balance of " << format_cents(new_account.balance) << "." << '\n';

  return new_account;
}

void print_menu() {
  std::cout << "1) Deposit" << '\n';
  std::cout << "2) Withdraw" << '\n';
  std::cout << "3) Show balance" << '\n';
  std::cout << "4) Show statement" << '\n';
  std::cout << "5) Save and exit" << '\n';
}

int read_menu_action() {
  int t_menu_action{};

  while (true) {
    std::cout << "Choose an option: ";

    if (!(std::cin >> t_menu_action)) {
      std::cout << "Invalid input. Please provide a valid number.";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    return t_menu_action;
  }
}

bool handle_menu_action(int menu_action) {
  switch (static_cast<MenuActions>(menu_action)) {
    case MenuActions::Deposit:
      std::cout << "Deposit";
      break;
    case MenuActions::Withdraw:
      std::cout << "Withdraw";
      break;
    case MenuActions::ShowBalance:
      std::cout << "Show balance";
      break;
    case MenuActions::ShowStatement:
      std::cout << "Show Statement";
      break;
    case MenuActions::SaveAndExit:
      std::cout << "Save and exit";
      return true;
    default:
      std::cout << "Invalid choice";
  }

  return false;
}

std::string format_cents(long long cents) {
  std::ostringstream os_stream{};

  os_stream << '$' << (cents / 100) << '.' << std::setfill('0') << std::setw(2) << cents % 100;

  return os_stream.str();
}

std::optional<Account> load_account(const std::string& file_name) { return std::nullopt; }