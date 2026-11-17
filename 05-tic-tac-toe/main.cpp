#include <array>
#include <cctype>
#include <iostream>
#include <limits>

constexpr std::size_t board_size{9};
using Board = std::array<char, board_size>;

// Get cell label from array index
char cell_label_from_index(std::size_t index);

// Prints the board, showing numbers in the empty cells.
void print_board(const Board& board);

// Prompts until the player picks a legal cell, then returns its index.
std::size_t read_move(const Board& board, char player);

// Returns true if player has three marks on any win line.
bool has_won(const Board& board, char player);

// Returns true if no empty cells are left.
bool is_full(const Board& board);

// Plays one game from an empty board until a win or a draw.
void play_one_game();

// Asks whether the players want another game.
bool wants_another_game();

int main() {
  std::cout << "=== Tic-Tac-Toe ===" << "\n\n";

  // TODO: Create the board as a std::array of 9 chars, one per cell, and fill
  //       every cell with the same "empty" marker. Cell 1 is index 0, cell 9
  //       is index 8, counting left to right and top to bottom.
  Board game_board{};
  game_board.fill(' ');

  // TODO: Print the board as three rows separated by lines. Show X or O in
  //       a taken cell and the cell's number in an empty one, so the players
  //       can see which numbers are still available.
  print_board(game_board);

  // TODO: Read a move for the current player. Reject anything that is not a
  //       number (call std::cin.clear(), then std::cin.ignore(...)), any
  //       number outside 1 to 9, and any cell that is already taken. Keep
  //       asking the same player until the move is legal.

  // TODO: Place the current player's mark, then check all eight win lines:
  //       three rows, three columns, and two diagonals. If one of them holds
  //       three of the current player's marks, announce the winner.

  // TODO: If nobody has won and no empty cells are left, announce a draw.
  //       Otherwise switch the current player between X and O and loop.

  // TODO: When the game ends, ask whether the players want another game. If
  //       so, clear the board, give X the first move again, and start over.
  do {
    play_one_game();
  } while (wants_another_game());

  return 0;
}

char cell_label_from_index(std::size_t index) { return static_cast<char>('1' + index); }

void print_board(const Board& board) {
  for (std::size_t row{}; row < 3; ++row) {
    for (std::size_t col{}; col < 3; ++col) {
      std::size_t index{row * 3 + col};

      if (board[index] == ' ') {
        std::cout << ' ' << cell_label_from_index(index) << ' ';
      } else {
        std::cout << ' ' << board[index] << ' ';
      }

      if (col < 2) {
        std::cout << '|';
      }
    }

    std::cout << '\n';

    if (row < 2) {
      std::cout << "---+---+---" << '\n';
    }
  }

  std::cout << '\n';
}

std::size_t read_move(const Board& board, char player) {
  while (true) {
    std::cout << "Player " << player << ", choose a cell (1-9): ";

    int choice{};

    if (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number." << '\n';

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      continue;
    }

    if (choice < 1 || choice > 9) {
      std::cout << "Invalid choice. Please choose a number from 1 to 9." << '\n';
      continue;
    }

    std::size_t index{static_cast<std::size_t>(choice - 1)};

    if (board[index] != ' ') {
      std::cout << "That cell is already taken. Choose another one." << '\n';
      continue;
    }

    return index;
  }
}

bool has_won(const Board& board, char player) {
  constexpr std::array<std::array<std::size_t, 3>, 8> win_lines{{{{0, 1, 2}}, {{3, 4, 5}}, {{6, 7, 8}}, {{0, 3, 6}}, {{1, 4, 7}}, {{2, 5, 8}}, {{0, 4, 8}}, {{2, 4, 6}}}};

  for (const auto& line : win_lines) {
    if (board[line[0]] == player && board[line[1]] == player && board[line[2]] == player) {
      return true;
    }
  }

  return false;
}

bool is_full(const Board& board) {
  for (char cell : board) {
    if (cell == ' ') {
      return false;
    }
  }

  return true;
}

void play_one_game() {
  Board game_board{};
  game_board.fill(' ');

  char current_player{'X'};
  bool game_over{};

  while (!game_over) {
    print_board(game_board);

    std::size_t move{read_move(game_board, current_player)};

    game_board[move] = current_player;

    if (has_won(game_board, current_player)) {
      print_board(game_board);

      std::cout << "Player " << current_player << " wins!" << '\n';

      game_over = true;
    } else if (is_full(game_board)) {
      print_board(game_board);

      std::cout << "It's a draw!" << '\n';

      game_over = true;
    } else {
      current_player = (current_player == 'X') ? 'O' : 'X';
    }
  }
}

bool wants_another_game() {
  while (true) {
    std::cout << "\nDo you want to play another game? (y/n): ";

    char answer{};

    if (!(std::cin >> answer)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::tolower(static_cast<unsigned char>(answer)) == 'y') {
      return true;
    }

    if (std::tolower(static_cast<unsigned char>(answer)) == 'n') {
      return false;
    }

    std::cout << "Please enter y or n." << '\n';
  }
}