/* Team 10 
Muhammad Hussain Baqar 27100127 
Umar Iftikhar 27100128 
*/


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int CARD_COUNT = 13;
const int INITIAL_MONEY = 1000;

void clearScreen() { 
//this function is written to clear screen after every round of blackjack 
#ifdef _WIN32
    system("cls"); //for windows
#else
    system("clear");//for mac 
#endif
}


int dealCard() {
    // Setting values of the cards in a deck
    int cards[CARD_COUNT] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    return cards[rand() % CARD_COUNT];
}

int calculateScore(vector<int>& cards) {
    int sum = 0;
    int ace = 0;

    // Loop through cards
    for (int card : cards) {
        // If Ace is found, ace count is incremented.
        // Sum is calculated by adding card.
        if (card == 11) {
            ace++;
        }
        sum += card;
    }

    // If Ace is present, and the sum of cards is greater than 21,
    // the ace is counted as 1. This is done by subtracting 10 from the sum.
    while (sum > 21 && ace > 0) {
        sum -= 10;
        ace--;
    }

    return sum;
}

string compare(int user_score, int computer_score) {
    // Compare scores and determine the winner
    if (user_score == 21) {
        return "Blackjack! You win!!! Woohoo! ";
    } else if (computer_score == 21) {
        return "Computer got Blackjack! You lose :(";
    } else if (user_score > 21) {
        return "You went over! You lose :(";
    } else if (computer_score > 21) {
        return "Computer went over! You win!!! Woohoo! ";
    } else if (user_score > computer_score) {
        return "You win!!! Woohoo! ";
    } else if (user_score == computer_score) {
        return "It's a Draw! Phew. It was a close one.";
    } else {
        return "You lose :(";
    }
}

int compareMoney(int user_score, int computer_score) {
    // Compare scores for money handling
    // Return 1 if user wins, return 2 if computer wins. Return any other value if draw.
    if (user_score == 21) {
        return 1;
    } else if (computer_score == 21) {
        return 2;
    } else if (user_score > 21) {
        return 2;
    } else if (computer_score > 21) {
        return 1;
    } else if (user_score > computer_score) {
        return 1;
    } else if (user_score == computer_score) {
        return 0;
    } else {
        return 2;
    }
}

void playGame(int &player_money, int &computer_money, int bet) {
    int user_score = 0;
    int computer_score = 0;
    char user_deal;

    vector<int> user_cards;
    vector<int> computer_cards;

    // Deal initial two cards for user and computer
    for (int i = 0; i < 2; i++) {
        user_cards.push_back(dealCard());
        computer_cards.push_back(dealCard());
    }

    bool game_over = false;

    // Game loop
    while (!game_over) {
        // Calculate scores
        user_score = calculateScore(user_cards);
        computer_score = calculateScore(computer_cards);

        // Display user's current hand and score
        cout << "Your cards: [";
        for (int card : user_cards) {
            cout << card << " ";
        }
        cout << "] , current score: " << user_score << endl;

        cout << "Computer's first card: [" << computer_cards[0] << "] " << endl;

        // Check if the game is over
        if (user_score == 21 || computer_score == 21 || user_score > 21) {
            game_over = true;
        } else {
            // Ask user for the next move
            cout << "Type 'y' to get another card, type 'n' to pass: ";
            cin >> user_deal;

            // Validate user input
            while (cin.fail() || (user_deal != 'y' && user_deal != 'n')) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please type 'y' or 'n': ";
                cin >> user_deal;
            }

            // Deal another card or end the game based on user input
            if (user_deal == 'y') {
                user_cards.push_back(dealCard());
            } else {
                game_over = true;
            }
        }
    }

    // Computer's turn: Hit until the score is at least 17
    while (computer_score != 0 && computer_score < 17) {
        computer_cards.push_back(dealCard());
        computer_score = calculateScore(computer_cards);
    }

    // Display final hands and scores
    cout << "Your final hand: [";
    for (int card : user_cards) {
        cout << card << " ";
    }
    cout << "] , final score: " << user_score << endl;

    cout << "Computer's final hand: [";
    for (int card : computer_cards) {
        cout << card << " ";
    }
    cout << "] , final score: " << computer_score << endl;

    // Compare scores and determine the winner, then update money accordingly
    cout << compare(user_score, computer_score) << endl;

    if (compareMoney(user_score, computer_score) == 1) {
        player_money += bet;
        computer_money -= bet;
    } else if (compareMoney(user_score, computer_score) == 2) {
        computer_money += bet;
        player_money -= bet;
    }
}

int main() {
    srand(time(0));

    // Game start prompt
    cout << "Do you want to play a game of Blackjack? Type 'y' or 'n': ";
    char startGame;
    cin >> startGame;

    int player_money = INITIAL_MONEY, computer_money = INITIAL_MONEY, bet;
    int count = 0;

    // Validate user input for starting the game
    while (cin.fail() || (startGame != 'y' && startGame != 'n')) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please type 'y' or 'n': ";
        cin >> startGame;
    }

    // Main game loop
    while (startGame == 'y' && player_money > 0 && computer_money > 0) {
        // Display game rules and information
        cout << "Welcome to Blackjack!" << endl;
        cout<<endl; 
        cout<<endl; 
        cout<<endl; 
        cout<<endl; 
        cout << "888     888                888       d8b                888      \n";
        cout << "888     888                888       Y8P                888      \n";
        cout << "888     888                888                          888      \n";
        cout << "88888b. 888 8888b.  .d8888b888  888 8888 8888b.  .d8888b888  888 \n";
        cout << "888 \"88b888    \"88bd88P\"   888 .88P \"888    \"88bd88P\"   888 .88P \n";
        cout << "888  888888.d888888888     888888K   888.d888888888     888888K  \n";
        cout << "888 d88P888888  888Y88b.   888 \"88b  888888  888Y88b.   888 \"88b \n";
        cout << "88888P\" 888\"Y888888 \"Y8888P888  888  888\"Y888888 \"Y8888P888  888 \n";
        cout << "                                     888                         \n";
        cout << "                                    d88P                         \n";
        cout << "                                  888P\"                         \n";
        cout<<endl; 
        cout<<endl; 
        cout<<endl; 
        cout<<endl;
        if (count == 0){
            cout << "Rules:\n"
                << "1. Card Values:\n"
                << "   - Number cards (2-10) have face value.\n"
                << "   - Face cards (Jack, Queen, King) are worth 10 points.\n"
                << "   - Ace is initially worth 11 points, but can be reduced to 1 if sum exceeds 21.\n\n"
                << "2. Game Setup:\n"
                << "   - Start with two cards for yourself and the computer.\n\n"
                << "3. Your Turn:\n"
                << "   - Choose to 'hit' (get another card) or 'pass' (keep your current hand).\n"
                << "   - If your total exceeds 21, you lose.\n"
                << "   - If you pass, it's the computer's turn.\n\n"
                << "4. Computer's Turn:\n"
                << "   - The computer hits until its total is at least 17.\n"
                << "   - If the computer's total exceeds 21, you win.\n\n"
                << "5. Scoring:\n"
                << "   - You win if:\n"
                << "     - You get a Blackjack (initial two cards sum to 21).\n"
                << "     - The computer goes over 21.\n"
                << "     - Your total is higher than the computer's total.\n"
                << "   - You lose if:\n"
                << "     - The computer gets a Blackjack.\n"
                << "     - You go over 21.\n"
                << "     - The computer's total is higher than yours.\n"
                << "   - It's a draw if both have the same total.\n\n"
                << "6. Money Handling:\n"
                << "   - You start with initial money.\n"
                << "   - Place bets before each round.\n"
                << "   - The outcome affects your money based on the rules (see code).\n\n"
                << "7. Game Loop:\n"
                << "   - Continue playing as long as you want to play and have money.\n\n"
                << "8. End of Game:\n"
                << "   - The game ends when you or the computer runs out of money.\n"
                << "   - Display a message indicating the winner or a tie.\n\n";
        }
        count++;

        // Display current money and ask for the bet
        cout << "Your money: " << player_money << "\n"
             << "Computer money: " << computer_money << endl;
        cout << "How much do you want to bet? ";

        // Get and validate the bet input
        cin >> bet;
        while (cin.fail() || bet < 1 || bet > player_money) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please enter a valid bet : ";
                cin >> bet;
            } else if (bet < 1) {
                cout << "You must bet $1 or more " << endl;
                cout << "Enter your bet : ";
                cin >> bet;
            } else if (bet > player_money) {
                cout << "Bet placed is greater than your money. Please enter a valid bet." << endl;
                cout << "Enter your bet : ";
                cin >> bet;
            }
        }

        // Play a round of the game
        playGame(player_money, computer_money, bet);

        // Display remaining money and ask if the user wants to play again
        cout << "You have $" << player_money << endl;
        cout << "Computer has $" << computer_money << endl;

        cout << "Do you want to play again? Type 'y' or 'n': ";
        cin >> startGame;
        clearScreen(); //clears the screen after every round
        

        // Validate user input for playing again
        while (cin.fail() || (startGame != 'y' && startGame != 'n')) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please type 'y' or 'n': ";
            cin >> startGame;
        }
    }

    // Display the result of the game
    if (computer_money <= 0) {
        cout << "You win!!!! Computer ran out of money. ";
    } else if (player_money <= 0) {
        cout << "You lost :( You ran out of money.";
    }

    return 0;
}