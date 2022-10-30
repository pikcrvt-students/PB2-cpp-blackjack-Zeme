#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


// Variable deifinition
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
void addPcard() {
  Phand1[Pcount] = cards[Ccount];
  Phand2[Pcount] = values[Ccount];
  Ccount++;
  Pcount++;
}
void addDcard() {
  Dhand1[Dcount] = cards[Ccount];
  Dhand2[Dcount] = values[Ccount];
  Ccount++;
  Dcount++;
}
int Phandsum() {
  int sum = 0;
  for (int i = 0; i < Pcount; i++) {
    sum+= Phand2[i];
  }
  return sum;
}
int Dhandsum() {
  int sum = 0;
  for (int i = 0; i < Dcount; i++) {
    sum+= Dhand2[i];
  }
  return sum;
}
void showPhand() {
  cout << "Your hand (" << Phandsum() << "):\n";
  for (int i = 0; i < Pcount; i++) {
    cout << "- " << Phand1[i] << "\n";
  }
  cout << "\n";
}
void showDhand(string x) {
  system("CLS");
  if (x == "show") {
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
}


// Main game loop
int main() {
  SetConsoleOutputCP(65001);

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
  showDhand("");
  showPhand();
  if (Dhand2[1] == 10 || Dhand2[1] == 11) {
    system("pause");
  }
  
  // The rest of the game
  if (Dhandsum() == 21) {
    showDhand("show");
    showPhand();
    if (Phandsum() == 21) {
      cout << "You and the dealer both have blackjack! It's a tie!\n";
      system("pause");
    }
    else {
      cout << "Dealer has blackjack! Dealer wins!\n";
      system("pause");
    }
  }
  else if (Phandsum() == 21) {
    showDhand("show");
    showPhand();
    cout << "You have blackjack! You win!\n";
    system("pause");
  }
  else {
    showDhand("");
    showPhand();
    while (Pcount < 5 && Phandsum() < 21) {
      cout << "Input H to hit or S to stand:\n";
      cin >> input;
      cout << "\n";
      if (input == "H" || input == "h") {
        addPcard();
        if (Phandsum() > 21) {
          for (int i = 0; i < 5; i++) {
            if (Phand2[i] == 11) {
              Phand2[i] = 1;
              if (Phandsum() < 21) {
                break;
              }
            }
          }
        }
        showDhand("");
        showPhand();
      }
      if (input == "S" || input == "s") {
        break;
      }
    }
    if (Phandsum() > 21) {
      showDhand("show");
      showPhand();
      cout << "Bust! You lose!\n";
      system("pause");
    }
    else {
      showDhand("show");
      showPhand();
      while (Dhandsum() < 17 && Dcount < 5) {
        system("pause");
        addDcard();
        if (Dhandsum() > 21) {
          for (int i = 0; i < 5; i++) {
            if (Dhand2[i] == 11) {
              Dhand2[i] = 1;
              if (Dhandsum() < 21) {
                break;
              }
            }
          }
        }
        showDhand("show");
        showPhand();
      }
      if (Dhandsum() > 21) {
        cout << "The dealer has bust! You win!\n";
        system("pause");
      }
      else if (Phandsum() > Dhandsum()) {
        cout << "You Won!\n";
        system("pause");
      }
      else if (Phandsum() == Dhandsum()) {
        cout << "Draw!\n";
        system("pause");
      }
      else {
        cout << "You lose!\n";
        system("pause");
      }
    }
  }
}