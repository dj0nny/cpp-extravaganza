
#include <cctype>
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

// Clean the input stream
void clean_input(std::istream& is);

// Handle menu's action
bool handle_menu_action(int menu_action, Account& account, const std::string& file_name);

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
    exit = handle_menu_action(menu_action, current_account.value(), file_name);

    std::cout << "\n\n";
  }

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
  while (true) {
    std::cout << "Choose an option: ";

    std::string input{};
    std::getline(std::cin >> std::ws, input);

    std::stringstream ss{input};
    int menu_action{};
    char extra{};

    if (!(ss >> menu_action) || (ss >> extra)) {
      std::cout << "Invalid input. Please choose an option from 1 to 5." << '\n';
      continue;
    }

    if (menu_action < 1 || menu_action > 5) {
      std::cout << "Invalid choice. Please choose an option from 1 to 5." << '\n';
      continue;
    }

    return menu_action;
  }
}

void clean_input(std::istream& is) {
  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool handle_menu_action(int menu_action, Account& account, const std::string& file_name) {
  switch (static_cast<MenuActions>(menu_action)) {
    // TODO: For deposits and withdrawals, read the amount as text and convert
    //       it to cents yourself. Reject non-numbers, negative amounts, zero,
    //       and anything with more than two decimal places.
    case MenuActions::Deposit: {
      std::optional<long long> deposit_amount{read_amount("Amount to deposit: ")};

      if (deposit_amount) {
        deposit(account, *deposit_amount);

        std::cout << "Deposited " << format_cents(*deposit_amount) << "." << '\n';
        std::cout << "New balance: " << format_cents(account.balance) << ".";
      } else {
        std::cout << "That is not a valid amount. Enter something like 25 or 12.50, up to $1000000.00.";
      }

      break;
    }

    // TODO: Refuse any withdrawal larger than the balance. The balance must
    //       never drop below zero. Record every accepted transaction.
    case MenuActions::Withdraw: {
      std::optional<long long> withdrawal_amount{read_amount("Amount to withdraw: ")};

      if (!withdrawal_amount) {
        std::cout << "That is not a valid amount. Enter something like 25 or 12.50, up to $1000000.00.";
        break;
      }

      if (withdraw(account, *withdrawal_amount)) {
        std::cout << "Withdrew " << format_cents(*withdrawal_amount) << "." << '\n';
        std::cout << "New balance: " << format_cents(account.balance) << ".";
      } else {
        std::cout << "Withdrawal refused. You cannot withdraw more than your current balance." << '\n';
        std::cout << "Current balance: " << format_cents(account.balance) << ".";
      }

      break;
    }

    // TODO: Print money as dollars and cents with <iomanip>, padding the cents
    //       to two digits so 5 cents prints as $0.05, not $0.5.
    case MenuActions::ShowBalance:
      std::cout << "Current balance: " << format_cents(account.balance) << ".";
      break;

    case MenuActions::ShowStatement:
      print_statement(account);
      break;

    // TODO: On save and exit, write the owner, the balance, and the history to
    //       account.txt with a std::ofstream, report whether it worked, and
    //       return 0.
    case MenuActions::SaveAndExit:
      if (save_account(account, file_name)) {
        std::cout << "Saved to account.txt. Goodbye.";
        return true;
      }

      std::cout << "Failed to save the account.";
      break;

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

std::optional<long long> read_amount(std::string_view prompt) {
  std::cout << prompt;

  std::string amount{};

  if (std::getline(std::cin >> std::ws, amount)) {
    return parse_amount(amount);
  }

  return std::nullopt;
}

std::optional<long long> parse_amount(std::string_view text) {
  if (text.empty()) {
    return std::nullopt;
  }

  constexpr long long max_cents{100000000};

  std::size_t decimal_position{text.find('.')};

  if (decimal_position != std::string_view::npos && text.find('.', decimal_position + 1) != std::string_view::npos) {
    return std::nullopt;
  }

  std::string_view whole_part{};
  std::string_view decimal_part{};

  if (decimal_position == std::string_view::npos) {
    whole_part = text;
  } else {
    whole_part = text.substr(0, decimal_position);
    decimal_part = text.substr(decimal_position + 1);

    if (decimal_part.empty() || decimal_part.size() > 2) {
      return std::nullopt;
    }
  }

  if (whole_part.empty()) {
    return std::nullopt;
  }

  long long whole_amount{};

  for (char ch : whole_part) {
    if (!std::isdigit(static_cast<unsigned char>(ch))) {
      return std::nullopt;
    }

    int digit{ch - '0'};

    if (whole_amount > 1000000LL) {
      return std::nullopt;
    }

    whole_amount = whole_amount * 10 + digit;

    if (whole_amount > 1000000LL) {
      return std::nullopt;
    }
  }

  long long cents{whole_amount * 100};

  if (!decimal_part.empty()) {
    int decimal_cents{decimal_part[0] - '0'};

    if (decimal_part.size() == 2) {
      decimal_cents = decimal_cents * 10 + (decimal_part[1] - '0');
    } else {
      decimal_cents *= 10;
    }

    cents += decimal_cents;
  }

  if (cents <= 0 || cents > max_cents) {
    return std::nullopt;
  }

  return cents;
}

void deposit(Account& account, long long cents) {
  account.balance += cents;

  account.transactions.push_back(Transaction{TransactionType::Deposit, cents, account.balance});
}

bool withdraw(Account& account, long long cents) {
  if (cents <= 0 || cents > account.balance) {
    return false;
  }

  account.balance -= cents;

  account.transactions.push_back(Transaction{TransactionType::Withdrawal, cents, account.balance});

  return true;
}

void print_statement(const Account& account) {
  std::cout << "Statement for " << account.owner << '\n';

  std::cout << std::left << std::setw(18) << "Type" << std::right << std::setw(12) << "Amount" << std::setw(13) << "Balance" << '\n';

  for (const Transaction& transaction : account.transactions) {
    std::string type;

    if (transaction.type == TransactionType::Deposit) {
      type = "Deposit";
    } else {
      type = "Withdrawal";
    }

    std::cout << std::left << std::setw(18) << type << std::right << std::setw(12) << format_cents(transaction.cents_amount) << std::setw(13) << format_cents(transaction.balance_after_cents) << '\n';
  }

  std::cout << "Current balance: " << format_cents(account.balance) << '\n';
}

bool save_account(const Account& account, const std::string& file_name) {
  std::ofstream file{file_name};

  if (!file) {
    return false;
  }

  file << account.owner << '\n';
  file << account.balance << '\n';

  for (const Transaction& transaction : account.transactions) {
    char type{};

    if (transaction.type == TransactionType::Deposit) {
      type = 'D';
    } else {
      type = 'W';
    }

    file << type << ' ' << transaction.cents_amount << ' ' << transaction.balance_after_cents << '\n';
  }

  return file.good();
}

std::optional<Account> load_account(const std::string& file_name) {
  std::ifstream file{file_name};

  if (!file) {
    return std::nullopt;
  }

  Account account{};

  if (!std::getline(file, account.owner)) {
    return std::nullopt;
  }

  if (!(file >> account.balance)) {
    return std::nullopt;
  }

  char type{};
  long long amount{};
  long long balance_after{};

  while (file >> type >> amount >> balance_after) {
    TransactionType transaction_type{};

    if (type == 'D') {
      transaction_type = TransactionType::Deposit;
    } else if (type == 'W') {
      transaction_type = TransactionType::Withdrawal;
    } else {
      return std::nullopt;
    }

    account.transactions.push_back(Transaction{transaction_type, amount, balance_after});
  }

  return account;
}