#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

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

// Turns a whole number of cents into text such as "$1234.05".
std::string format_cents(long long cents);

// Converts text such as "25" or "12.50" into cents, or nothing if invalid.
std::optional<long long> parse_amount(std::string_view text);

// Prompts for an amount, prints why it was rejected if it was.
std::optional<long long> read_amount(std::string_view prompt);

void deposit(Account& account, long long cents);
bool withdraw(Account& account, long long cents);
void printStatement(const Account& account);

bool save_account(const Account& account, const std::string& file_name);
std::optional<Account> load_account(const std::string& file_mame);

int main() {
  // TODO: Try to load a saved account from account.txt with a std::ifstream.
  //       If there is no file, or it cannot be read, ask for the account
  //       holder's name and open a new account with a balance of zero.

  // TODO: Show a menu in a loop: deposit, withdraw, show balance, show
  //       statement, save and exit. Read the choice with std::getline and
  //       reject anything that is not one of the listed options.

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
