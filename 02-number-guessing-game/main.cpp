#include <iostream>
#include <limits>
#include <random>

const int g_max_attempts{10};
const int g_closest_diff{5};

enum class Difficulty { Easy = 1, Medium = 2, Hard = 3 };

// Draws a fresh secret number in the inclusive range [low, high].
int generate_secret_number(std::mt19937& generator, int low, int high);

// Choose the difficulty level
int choose_difficulty();

// Prompts until the player enters a whole number, then returns it.
int read_guess(int low, int high);

// Prints whether the guess was too low or too high.
void print_hint(int guess, int secret_number);

// Asks whether the player wants another round.
bool wants_another_round();

// Handle wrong input
void handle_wrong_input(std::istream& is);

int main() {
  std::cout << "=== Number Guessing Game ===" << "\n\n";

  // TODO: Set up the random number machinery once, before any round begins.
  //       You need a std::random_device to produce a seed, a std::mt19937
  //       generator seeded from it, and a std::uniform_int_distribution
  //       covering the range the player has to guess.
  std::random_device random_device{};
  std::mt19937 generator{random_device()};

  int secret_number{};
  int guesses{};
  int best_guesses_score{};

  constexpr int min_value{1};
  int max_value{};

  // TODO: Start a round. Draw a fresh secret number from the distribution,
  //       reset the attempt counter, and tell the player what range to aim at.
  while (true) {
    max_value = choose_difficulty();
    secret_number = generate_secret_number(generator, min_value, max_value);
    guesses = 0;

    std::cout << '\n';
    std::cout << "I am thinking of a number between 1 and " << max_value << "." << "\n\n";

    int guess{};

    while (g_max_attempts > guesses) {
      // TODO: Read a guess. If the player types something that is not a whole
      //       number, call std::cin.clear(), discard the rest of the line with
      //       std::cin.ignore(...), say what went wrong, and ask again.
      guess = read_guess(min_value, max_value);
      ++guesses;

      // TODO: Compare the guess to the secret number, print a too low or too high
      //       hint, count the attempt, and keep looping until the guess is right.
      if (guess == secret_number) {
        // TODO: When the guess is correct, congratulate the player and report the
        //       secret number and how many attempts it took.
        std::cout << "Correct! The number was " << secret_number << ". It took you " << guesses << " guesses." << "\n\n";
        break;
      } else {
        print_hint(guess, secret_number);
      }
    }

    if (g_max_attempts == guesses) {
      std::cout << "\nYou could not guess the number within the " << g_max_attempts << " attempts. The secret number was: " << secret_number << ".\n\n";
    }

    if (guesses < best_guesses_score || best_guesses_score == 0) {
      best_guesses_score = guesses;
    }

    std::cout << "The best guesses score is: " << best_guesses_score << "\n\n";

    // TODO: Ask whether the player wants another round. If so, go back and draw
    //       a new secret number with the attempt counter back at zero.
    if (!wants_another_round()) {
      std::cout << "\nThanks for playing." << '\n';
      break;
    }

    std::cout << '\n';
  }

  return 0;
}

int generate_secret_number(std::mt19937& generator, int low, int high) {
  std::uniform_int_distribution<int> distribution{low, high};

  return distribution(generator);
}

int choose_difficulty() {
  std::cout << "Choose the difficulty" << '\n';
  std::cout << ' ' << "1. Easy (1 - 50)" << '\n';
  std::cout << ' ' << "2. Medium (1 - 100)" << '\n';
  std::cout << ' ' << "3. Hard (1 - 1000)" << "\n\n";

  int difficulty_code{};

  while (true) {
    std::cout << "Enter the difficulty code: ";

    if (!(std::cin >> difficulty_code)) {
      std::cout << "Invalid value" << '\n';
      handle_wrong_input(std::cin);
      continue;
    }

    switch (static_cast<Difficulty>(difficulty_code)) {
      case Difficulty::Easy:
        return 50;
      case Difficulty::Medium:
        return 100;
      case Difficulty::Hard:
        return 1000;
      default:
        std::cout << "Invalid value" << '\n';
    }
  }
}

int read_guess(int low, int high) {
  int user_guess{};

  while (true) {
    std::cout << "Your guess: ";

    if (!(std::cin >> user_guess)) {
      std::cout << "Invalid input" << '\n';
      handle_wrong_input(std::cin);
      continue;
    }

    if (user_guess < low || user_guess > high) {
      std::cout << "The guess is not between " << low << " and " << high << ". No attempt will be consumed." << '\n';
      continue;
    }

    return user_guess;
  }
}

void print_hint(int guess, int secret_number) {
  if (abs(guess - secret_number) <= g_closest_diff) {
    std::cout << "You are very close." << '\n';
  } else {
    guess > secret_number ? std::cout << "Too high. Try again." << '\n' : std::cout << "Too low. Try again." << '\n';
  }
}

bool wants_another_round() {
  char flag;

  while (true) {
    std::cout << "Play again? (y/n): ";

    if (!(std::cin >> flag)) {
      std::cout << "Invalid input" << '\n';
      handle_wrong_input(std::cin);
      continue;
    }

    switch (tolower(static_cast<unsigned char>(flag))) {
      case 'y':
        return true;
      case 'n':
        return false;
      default:
        std::cout << "Invalid choice" << '\n';
    }
  }
}

void handle_wrong_input(std::istream& is) {
  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
