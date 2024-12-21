#include <iostream>
#include <fstream>  // Required for file handling
#include <string>
using namespace std;

struct Player {
    string nickname;
    int age;
    int score1;
    int score2;
    float average; 
};

void displayMenu() {
    cout << "\n--- Player Menu---\n";
    cout << "1. Add Player Record\n";
    cout << "2. View Player Records\n";
    cout << "3. Compute for the average\n";
    cout << "4. Show the player(s) who gets the max average\n";
    cout << "5. Show the player(s) who gets the min average\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

void addPlayer(Player &player) {
    cout << "Enter player's nickname: ";
    cin >> player.nickname;
    cout << "Enter player's age: ";
    cin >> player.age;
    cout << "Enter first best score: ";
    cin >> player.score1;
    cout << "Enter second best score: ";
    cin >> player.score2;
    player.average = (player.score1 + player.score2) / 2.0; // Calculating the average
}

void displayPlayers(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Player " << i + 1 << ":\n";
        cout << "Nickname: " << players[i].nickname << "\n";
        cout << "Age: " << players[i].age << "\n";
        cout << "Best Score 1: " << players[i].score1 << "\n";
        cout << "Best Score 2: " << players[i].score2 << "\n";
        cout << "Average: " << players[i].average << "\n"; // Displaying the average
        cout << "------------------------\n";
    }
}

void calculateBestScores(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        int bestScore = (players[i].score1 > players[i].score2) ? players[i].score1 : players[i].score2;
        cout << "Player " << players[i].nickname << "'s best score: " << bestScore << "\n";
    }
}

void showMaxAveragePlayer(Player players[], int numPlayers) {
    float maxAvg = players[0].average;
    for (int i = 1; i < numPlayers; ++i) {
        if (players[i].average > maxAvg) {
            maxAvg = players[i].average;
        }
    }

    cout << "Player(s) with the max average score:\n";
    for (int i = 0; i < numPlayers; ++i) {
        if (players[i].average == maxAvg) {
            cout << "Nickname: " << players[i].nickname << ", Average: " << players[i].average << "\n";
        }
    }
}

void showMinAveragePlayer(Player players[], int numPlayers) {
    float minAvg = players[0].average;
    for (int i = 1; i < numPlayers; ++i) {
        if (players[i].average < minAvg) {
            minAvg = players[i].average;
        }
    }

    cout << "Player(s) with the min average score:\n";
    for (int i = 0; i < numPlayers; ++i) {
        if (players[i].average == minAvg) {
            cout << "Nickname: " << players[i].nickname << ", Average: " << players[i].average << "\n";
        }
    }
}

void savePlayerToFile(Player players[], int numPlayers) {
    ofstream file("pla.txt", ios::out);  // Open the file in overwrite mode (clear existing content)
    if (file.is_open()) {
        for (int i = 0; i < numPlayers; ++i) {
            file << players[i].nickname << " "
                 << players[i].age << " "
                 << players[i].score1 << " "
                 << players[i].score2 << " "
                 << players[i].average << "\n";  // Write each player's data to the file
        }
        cout << "Player data saved to pla.txt.\n";
        file.close();
    } else {
        cout << "Failed to open the file for writing.\n";
    }
}

void loadPlayersFromFile(Player players[], int &numPlayers) {
    ifstream file("pla.txt", ios::in);  // Open the file for reading
    if (file.is_open()) {
        while (file >> players[numPlayers].nickname >> players[numPlayers].age
                     >> players[numPlayers].score1 >> players[numPlayers].score2) {
            players[numPlayers].average = (players[numPlayers].score1 + players[numPlayers].score2) / 2.0; // Compute average
            numPlayers++;
            if (numPlayers >= 5) break; // Stop when 5 players are loaded
        }
        file.close();
    } else {
        cout << "No existing player data found, starting fresh.\n";
    }
}

int main() {
    const int NUM_PLAYERS = 5;
    Player players[NUM_PLAYERS]; 
    int choice;
    int playerIndex = 0;

    // Try to load existing player records from the file
    loadPlayersFromFile(players, playerIndex);

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                // Allow user to add 5 players
                while (playerIndex < NUM_PLAYERS) {
                    cout << "\n--- Add Player " << playerIndex + 1 << " ---\n";
                    addPlayer(players[playerIndex]);
                    playerIndex++;
                }
                // Save all players data to file once all players are added
                if (playerIndex == NUM_PLAYERS) {
                    savePlayerToFile(players, NUM_PLAYERS);
                }
                break;
            case 2:
                if (playerIndex < NUM_PLAYERS) {
                    cout << "You must add 5 players first before viewing player records.\n";
                } else {
                    displayPlayers(players, NUM_PLAYERS); // Show player records only after 5 players are added
                }
                break;
            case 3:
                if (playerIndex == NUM_PLAYERS) { // Ensure 5 players are added before calculating
                    calculateBestScores(players, NUM_PLAYERS); // Compute the best scores
                } else {
                    cout << "You must add 5 players first before computing averages.\n";
                }
                break;
            case 4:
                if (playerIndex == NUM_PLAYERS) { // Ensure 5 players are added before showing max average
                    showMaxAveragePlayer(players, NUM_PLAYERS); // Show max average player(s)
                } else {
                    cout << "You must add 5 players first before showing the max average.\n";
                }
                break;
            case 5:
                if (playerIndex == NUM_PLAYERS) { // Ensure 5 players are added before showing min average
                    showMinAveragePlayer(players, NUM_PLAYERS); // Show min average player(s)
                } else {
                    cout << "You must add 5 players first before showing the min average.\n";
                }
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }

    } while (choice != 6); 

    return 0;
}

