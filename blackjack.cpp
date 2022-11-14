#include <iostream>
#include <windows.h> //cmd commands
#include <cstdlib> //rand(), srand()
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
string P2hand1[5] = {};
int P2hand2[5] = {};
string Dhand1[5] = {};
int Dhand2[5] = {};
int Ccount = 0;
int Pcount = 0;
int P2count = 1;
int Dcount = 0;
int balance = 100;
int bet = 0;
int bet2 = 0;
bool pb1 = FALSE;
bool pb2 = FALSE;
string input;


// Function definition
// Gives player a card
void addPcard() {
    Phand1[Pcount] = cards[Ccount];
    Phand2[Pcount] = values[Ccount];
    Ccount++;
    Pcount++;
}
// Gives player's second hand a card
void addP2card() {
    P2hand1[P2count] = cards[Ccount];
    P2hand2[P2count] = values[Ccount];
    Ccount++;
    P2count++;
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
// Sum of player's second hand
int P2handsum() {
    int sum = 0;
    for (int i = 0; i < P2count; i++) {
        sum+= P2hand2[i];
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
void aceCheck(string x, string y = " ") {
    if (x == "p" || y == "p") {
        if (Phandsum() > 21) {
            for (int i = 0; i < Pcount; i++) {
                if (Phand2[i] == 11) {
                    Phand2[i] = 1;
                    break;
                }
            }
        }
    }
    if (x == "p2" || y == "p2") {
        if (P2handsum() > 21) {
            for (int i = 0; i < P2count; i++) {
                if (P2hand2[i] == 11) {
                    P2hand2[i] = 1;
                    break;
                }
            }
        }
    }
    if (x == "d" || y == "d") {
        if (Dhandsum() > 21) {
            for (int i = 0; i < Dcount; i++) {
                if (Dhand2[i] == 11) {
                    Dhand2[i] = 1;
                    break;
                }
            }
        }
    }
}
// Prints both hands on screen
void showHands(bool x = FALSE, bool y = FALSE) {
    system("cls");
    if (y == TRUE) {
        cout << "Balance: " << balance << "\n" << "First bet: " << bet << "\n" << "Second bet: " << bet2 << "\n" << "\n";
    }
    else {
        cout << "Balance: " << balance << "\n" << "Bet: " << bet << "\n" << "\n";
    }
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
    if (y == TRUE) {
        cout << "\n";
        cout << "Your first hand (" << Phandsum() << "):\n";
        for (int i = 0; i < Pcount; i++) {
            cout << "- " << Phand1[i] << "\n";
        }
        cout << "\n";
        cout << "Your second hand (" << P2handsum() << "):\n";
        for (int i = 0; i < P2count; i++) {
            cout << "- " << P2hand1[i] << "\n";
        }
        cout << "\n";
    }
    else {
        cout << "\n";
        cout << "Your hand (" << Phandsum() << "):\n";
        for (int i = 0; i < Pcount; i++) {
            cout << "- " << Phand1[i] << "\n";
        }
        cout << "\n";
    }
}


// Main game loop
void game() {
    // Bet placing
    do {
        system("cls");
        cout << "Balance: " << balance << "\n" << "\n";
        cout << "Please place your bet:\n";
        cin >> bet;
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (bet <= 0);
    balance -= bet;

    // Deck shuffle
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int r = i + (rand() % (52 - i));
        swap(cards[i], cards[r]);
        swap(values[i], values[r]);
    }

    // First card dealing
    for (int i = 0; i < 2; i++) {
        addPcard();
        addDcard();
    }
    aceCheck("p", "d");
    if (Dhand2[1] == 10 || Dhand2[1] == 11) {
        showHands();
        system("pause");
    }

    // Blackjack checks
    if (Dhandsum() == 21) {
        showHands(TRUE);
        if (Phandsum() == 21) {
            cout << "You and the dealer both have blackjack! It's a draw!\n";
            balance += bet;
        } else {
            cout << "Dealer has blackjack! Dealer wins!\n";
        }
    } else if (Phandsum() == 21) {
        showHands(TRUE);
        cout << "You have blackjack! You win!\n";
        balance += bet + bet * 1.5;
    }

        // Player input
    else {
        while (Pcount < 5 && Phandsum() < 21) {
            showHands();
            if (Pcount == 2) {
                if (Phand1[0][0] == Phand1[1][0]) {
                    cout << "Input H to hit, DD to double down, SP to split or S to stand:\n";
                } else {
                    cout << "Input H to hit, DD to double down or S to stand:\n";
                }
            } else {
                cout << "Input H to hit or S to stand:\n";
            }
            cin >> input;
            cout << "\n";
            if (input == "H" || input == "h") {
                addPcard();
                aceCheck("p");
                showHands();
            }
            if (Pcount == 2) {
                if (input == "DD" || input == "dd" || input == "Dd" || input == "dD") {
                    if (balance >= bet) {
                        balance -= bet;
                        bet = bet * 2;
                        addPcard();
                        aceCheck("p");
                        break;
                    } else {
                        showHands();
                        cout << "You don't have enough money to double down!\n";
                        system("pause");
                        system("cls");
                        showHands();
                    }
                }
                if (Phand1[0][0] == Phand1[1][0]) {
                    if (input == "SP" || input == "sp" || input == "Sp" || input == "sP") {
                        if (balance >= bet) {
                            balance -= bet;
                            bet2 = bet;
                            P2hand1[0] = Phand1[1];
                            P2hand2[0] = Phand2[1];
                            Phand1[1] = "";
                            Phand2[1] = 0;
                            Pcount--;
                            addPcard();
                            addP2card();
                            aceCheck("p", "p2");
                            while (Pcount < 5 && Phandsum() < 21) {
                                showHands(FALSE, TRUE);
                                cout << "Input H to hit or S to stand:\n";
                                cin >> input;
                                cout << "\n";
                                if (input == "H" || input == "h") {
                                    addPcard();
                                    aceCheck("p");
                                }
                                if (input == "S" || input == "s") {
                                    break;
                                }
                            }
                            if (Phandsum() > 21) {
                                showHands(FALSE,TRUE);
                                cout << "Your first hand has bust!\n";
                                pb1 = TRUE;
                                system("pause");
                            }
                            while (P2count < 5 && P2handsum() < 21) {
                                showHands(FALSE, TRUE);
                                cout << "Input H to hit or S to stand:\n";
                                cin >> input;
                                cout << "\n";
                                if (input == "H" || input == "h") {
                                    addP2card();
                                    aceCheck("p2");
                                }
                                if (input == "S" || input == "s") {
                                    break;
                                }
                            }
                            if (P2handsum() > 21) {
                                showHands(FALSE,TRUE);
                                cout << "Your second hand has bust!\n";
                                pb2 = TRUE;
                                system("pause");
                            }
                        }
                        else {
                            showHands();
                            cout << "You don't have enough money to split!\n";
                            system("pause");
                            system("cls");
                            showHands();
                        }
                    }
                }
                if (input == "S" || input == "s") {
                    break;
                }
            }
            if (P2count > 1) {
                if (pb1 == TRUE || pb2 == TRUE) {

                }

            }
            else {
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
                        aceCheck("d");
                        showHands(TRUE);
                    }

                    // Result check
                    if (Dhandsum() > 21) {
                        cout << "The dealer has bust! You win!\n";
                        balance += bet * 2;
                    }
                    else if (Phandsum() > Dhandsum()) {
                        cout << "You Won!\n";
                        balance += bet * 2;
                    }
                    else if (Phandsum() == Dhandsum()) {
                        cout << "Draw!\n";
                        balance += bet;
                    }
                    else {
                        cout << "You lose!\n";
                    }
                }
            }
        }
    }
}

// Main loop
int main() {
    string input2 = "Y";
    system("MODE 55,20");
    SetConsoleOutputCP(65001);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 18;
    cfi.dwFontSize.Y = 36;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    do {
        game();
        if (balance > 0) {
            cout << "Do you want to play again?[Y/N]:\n";
            cin >> input2;
            for (int i = 0; i < 5; i++) {
                Phand1[i] = "";
                Phand2[i] = 0;
                P2hand1[i] = "";
                P2hand2[i] = 0;
                Dhand1[i] = "";
                Dhand2[i] = 0;
            }
            Ccount = 0;
            Pcount = 0;
            P2count = 0;
            Dcount = 0;
        }
        else {
            cout << "You don't have any more money left!\n";
            system("pause");
            input2 = "";
        }
    }
    while (input2 == "Y" || input2 == "y");
}
