#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

// Variable definition
string cards[52] = {"2♦", "2♣", "2♥", "2♠",
                    "3♦", "3♣", "3♥", "3♠",
                    "4♦", "4♣", "4♥", "4♠",
                    "5♦", "5♣", "5♥", "5♠",
                    "6♦", "6♣", "6♥", "6♠",
                    "7♦", "7♣", "7♥", "7♠",
                    "8♦", "8♣", "8♥", "8♠",
                    "9♦", "9♣", "9♥", "9♠",
                    "10♦", "10♣", "10♥", "10♠",
                    "jack♦", "jack♣", "jack♥", "jack♠",
                    "queen♦", "queen♣", "queen♥", "queen♠",
                    "king♦", "king♣", "king♥", "king♠",
                    "ace♦", "ace♣", "ace♥", "ace♠"};
int values[52] = {2, 2, 2, 2,
                  3, 3, 3, 3,
                  4, 4, 4, 4,
                  5, 5, 5, 5,
                  6, 6, 6, 6,
                  7, 7, 7, 7,
                  8, 8, 8, 8,
                  9, 9, 9, 9,
                  10, 10, 10, 10,
                  10, 10, 10, 10,
                  10, 10, 10, 10,
                  10, 10, 10, 10,
                  11, 11, 11, 11};
string Phand1[5] = {};
int Phand2[5] = {};
string Dhand1[5] = {};
int Dhand2[5] = {};
int Ccount = 0;
int Pcount = 0;
int Dcount = 0;
string input;


// Function definition
// Gives player a card
void addPcard() {
  Phand1[Pcount] = cards[Ccount];
  Phand2[Pcount] = values[Ccount];
  Ccount++;
  Pcount++;
}
// Gives dealer a card
void addDcard() {
  Dhand1[Dcount] = cards[Ccount];
  Dhand2[Dcount] = values[Ccount];
  Ccount++;
  Dcount++;
}
// Sum of player hand
int Phandsum() {
  int sum = 0;
  for (int i = 0; i < Pcount; i++) {
    sum+= Phand2[i];
  }
  return sum;
}
// Sum of dealer hand
int Dhandsum() {
  int sum = 0;
  for (int i = 0; i < Dcount; i++) {
    sum+= Dhand2[i];
  }
  return sum;
}
// Changes ace value from 11 to 1 if needed
void aceCheck(char x, char y = ' ') {
    if (x == 'p' || y == 'p') {
        if (Phandsum() > 21) {
            for (int i = 0; i < 2; i++) {
                if (Phand2[i] == 11) {
                    Phand2[i] = 1;
                    break;
                }
            }
        }
    }
    if (y == 'd' || y == 'd') {
        if (Dhandsum() > 21) {
            for (int i = 0; i < 2; i++) {
                if (Dhand2[i] == 11) {
                    Dhand2[i] = 1;
                    break;
                }
            }
        }
    }
}
// Prints both hands on screen
void showHands(bool x = FALSE) {
  system("cls");
  if (x == TRUE) {
    cout << "Dealer's hand (" << Dhandsum() << "):\n";
    for (int i = 0; i < Dcount; i++) {
      cout << "- " << Dhand1[i] << "\n";
    }
  }
  else {
    cout << "Dealer's hand (" << Dhandsum() - Dhand2[0] << "):\n";
    cout << "- hidden card\n";
    for (int i = 1; i < Dcount; i++) {
      cout << "- " << Dhand1[i] << "\n";
    }
  }
  cout << "\n";
  cout << "Your hand (" << Phandsum() << "):\n";
  for (int i = 0; i < Pcount; i++) {
    cout << "- " << Phand1[i] << "\n";
  }
  cout << "\n";
}


// Main game loop
void game() {
  // Deck shuffle
  srand(time(0));
  for (int i = 0; i < 52 ; i++) {
    int r = i + (rand() % (52 - i));
    swap(cards[i], cards[r]);
    swap(values[i], values[r]);
  }

  // First card dealing
  for (int i = 0; i < 2; i++) {
    addPcard();
    addDcard();
  }
  aceCheck('p', 'd');
  showHands();
  if (Dhand2[1] == 10 || Dhand2[1] == 11) {
    system("pause");
  }

  // Blackjack checks
  if (Dhandsum() == 21) {
    showHands(TRUE);
    if (Phandsum() == 21) {
      cout << "You and the dealer both have blackjack! It's a draw!\n";
    }
    else {
      cout << "Dealer has blackjack! Dealer wins!\n";
    }
  }
  else if (Phandsum() == 21) {
    showHands(TRUE);
    cout << "You have blackjack! You win!\n";
  }

  // Player input
  else {
    showHands();
    while (Pcount < 5 && Phandsum() < 21) {
      cout << "Input H to hit or S to stand:\n";
      cin >> input;
      cout << "\n";
      if (input == "H" || input == "h") {
        addPcard();
        aceCheck('p');
        showHands();
      }
      if (input == "S" || input == "s") {
        break;
      }
    }
    if (Phandsum() > 21) {
      showHands(TRUE);
      cout << "Bust! You lose!\n";
    }

    // Dealer dealing himself cards
    else {
      showHands(TRUE);
      while (Dhandsum() < 17 && Dcount < 5) {
        system("pause");
        addDcard();
        aceCheck('d');
        showHands(TRUE);
      }

      // Result check
      if (Dhandsum() > 21) {
        cout << "The dealer has bust! You win!\n";
      }
      else if (Phandsum() > Dhandsum()) {
        cout << "You Won!\n";
      }
      else if (Phandsum() == Dhandsum()) {
        cout << "Draw!\n";
      }
      else {
        cout << "You lose!\n";
      }
    }
  }
}

// Main loop
int main() {
  string input2 = "Y";
  system("MODE 55,18");
  SetConsoleOutputCP(65001);
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof(cfi);
  cfi.nFont = 0;
  cfi.dwFontSize.X = 18;
  cfi.dwFontSize.Y = 36;
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;
  std::wcscpy(cfi.FaceName, L"Consolas");
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
  do {
    game();
    cout << "Do you want to play again?[Y/N]:\n";
    cin >> input2;
    for (int i = 0; i < 5; i++) {
        Phand1[i] = "";
    }
    for (int i = 0; i < 5; i++) {
        Phand2[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        Dhand1[i] = "";
    }
    for (int i = 0; i < 5; i++) {
        Dhand2[i] = 0;
    }
    Ccount = 0;
    Pcount = 0;
    Dcount = 0;
  }
  while (input2 == "Y" || input2 == "y");
}
