#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>  // For tolower()
// Function to clear the console
// I am the only one writting this code.
// they are useless a burden.
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to draw the hangman figure with more detail
void drawHangman(int lives) {
    printf(" +---+\n");
    printf(" |   |\n");
    
    if (lives < 6)
        printf(" O   |\n");  // Head
    else
        printf("     |\n");
    
    if (lives < 5) {
        if (lives < 4)
            printf("/|\\  |\n");  // Full body
        else if (lives < 3)
            printf("/|   |\n");  // Partial body
        else
            printf(" |   |\n");  // Just the torso
    } else {
        printf("     |\n");  // No body
    }

    if (lives < 2) {
        if (lives < 1)
            printf("/ \\  |\n");  // Both legs
        else
            printf("/    |\n");  // One leg
    } else {
        printf("     |\n");  // No legs
    }
    
    printf("     |\n");
    printf("=======\n");
}

int main() {
    // Movie titles with hints
    char movieTitles[][50] = {
        "The last of us", "The Godfather", "The Dark Knight", "12 Angry Men", 
        "Schindler's List", "Inception", "Forrest Gump", "The Matrix", 
        "Interstellar", "Gladiator"
    };
    
    // Mobile games with hints
    char mobileGames[][50] = {
        "Clash of Clans", "PUBG Mobile", "Candy Crush", "Genshin Impact", 
        "Call of Duty Mobile", "Among Us", "Pokémon Go", "Brawl Stars", 
        "Subway Surfers", "Minecraft Pocket Edition"
    };
    
    // Sports games with hints
    char sportsGames[][50] = {
        "FIFA 21", "NBA 2K21", "Madden NFL 21", "Rocket League", 
        "PES 2021", "WWE 2K Battlegrounds", "NHL 21", "Tennis World Tour", 
        "EA Sports UFC 4", "MLB The Show 21"
    };

    // Hints for each category
    char movieHints[10][3][100] = {
        {"Based on a video game", "Post-apocalyptic setting", "Released in 2023"},
        {"Mafia family", "Directed by Francis Ford Coppola", "Starring Marlon Brando"},
        {"Superhero movie", "Directed by Christopher Nolan", "Features Joker"},
        {"Classic court drama", "12 jurors", "Released in 1957"},
        {"World War II", "Holocaust", "Directed by Steven Spielberg"},
        {"Dream invasion", "Directed by Christopher Nolan", "Starring Leonardo DiCaprio"},
        {"Run, Forrest, Run!", "Starring Tom Hanks", "Released in 1994"},
        {"Red pill or blue pill?", "Sci-fi classic", "Directed by the Wachowskis"},
        {"Space exploration", "Directed by Christopher Nolan", "Released in 2014"},
        {"Ancient Rome", "Starring Russell Crowe", "Released in 2000"}
    };
    
    char mobileHints[10][3][100] = {
        {"Strategy game", "Clans fighting", "Built on villages"},
        {"Battle royale", "Multiplayer", "100 players in one match"},
        {"Match 3 puzzle", "Colorful candies", "Extremely addictive"},
        {"Open-world", "Anime style", "Elemental powers"},
        {"First-person shooter", "Warzone", "Based on the Call of Duty franchise"},
        {"Deception game", "Space setting", "Impostors and crewmates"},
        {"Augmented reality", "Catching creatures", "Worldwide popularity"},
        {"Multiplayer action", "Supercell's creation", "Characters with unique abilities"},
        {"Endless runner", "Escape from a policeman", "Popular mobile arcade game"},
        {"Sandbox game", "Block-building", "Creative mode or survival"}
    };
    
    char sportsHints[10][3][100] = {
        {"Soccer simulation", "Developed by EA Sports", "Has Ultimate Team mode"},
        {"Basketball simulation", "Features MyCareer", "Part of NBA 2K series"},
        {"American football", "NFL teams and players", "By EA Sports"},
        {"Car soccer", "Hybrid of racing and soccer", "Played with vehicles"},
        {"Soccer game", "Competitor to FIFA", "Developed by Konami"},
        {"Wrestling game", "Exaggerated arcade style", "Part of WWE 2K series"},
        {"Ice hockey", "Developed by EA Sports", "NHL players and teams"},
        {"Tennis simulation", "Features ATP and WTA players", "Realistic tennis experience"},
        {"Mixed martial arts", "By EA Sports", "Realistic UFC experience"},
        {"Baseball game", "MLB teams and players", "Developed by San Diego Studio"}
    };

    char guess[50];
    int lives = 6;
    int score = 0;
    int hintIndex = 0;
    char incorrectGuesses[26];  // To store incorrect guesses
    int incorrectGuessCount = 0;

    srand(time(NULL));

    // Ask user to select category
    int categoryChoice;
    printf("Choose a category:\n");
    printf("1. Movies\n");
    printf("2. Mobile Games\n");
    printf("3. Sports Games\n");
    scanf("%d", &categoryChoice);

    char (*selectedCategory)[50];
    char (*selectedHints)[3][100];
    int randomIndex;

    // Based on category selection, assign category and hints
    if (categoryChoice == 1) {
        selectedCategory = movieTitles;
        selectedHints = movieHints;
        randomIndex = rand() % 10;
    } else if (categoryChoice == 2) {
        selectedCategory = mobileGames;
        selectedHints = mobileHints;
        randomIndex = rand() % 10;
    } else {
        selectedCategory = sportsGames;
        selectedHints = sportsHints;
        randomIndex = rand() % 10;
    }

    int wordLength = strlen(selectedCategory[randomIndex]);
    char displayedWord[50];

    // Initialize the displayedWord with underscores and spaces
    for (int i = 0; i < wordLength; i++) {
        if (selectedCategory[randomIndex][i] == ' ') {
            displayedWord[i] = ' ';
        } else {
            displayedWord[i] = '_';
        }
    }
    displayedWord[wordLength] = '\0';  // Null-terminate the string

    printf("Start guessing!\n");

    while (lives > 0) {
        drawHangman(lives);
        printf("\nWord: ");
        for (int i = 0; i < wordLength; i++) {
            printf("%c ", displayedWord[i]);  // Show the current state of the word
        }

        // Display incorrect guesses
        if (incorrectGuessCount > 0) {
            printf("\nIncorrect guesses: ");
            for (int i = 0; i < incorrectGuessCount; i++) {
                printf("%c ", incorrectGuesses[i]);
            }
        }

        // Show hint if the user has made a wrong guess
        if (hintIndex < 3 && lives < 6) {
            printf("\nHint: %s", selectedHints[randomIndex][hintIndex]);
            hintIndex++;
        }

        printf("\nGuess a letter: ");
        scanf("%s", guess);

        // Convert guess to lowercase
        guess[0] = tolower(guess[0]);

        int correctGuess = 0;
        for (int i = 0; i < wordLength; i++) {
            // Convert both the character in the word and the guess to lowercase for case-insensitive comparison
            if (tolower(selectedCategory[randomIndex][i]) == guess[0]) {
                displayedWord[i] = selectedCategory[randomIndex][i];  // Update the displayedWord with the correct guess
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            // Add the wrong guess to the incorrect guesses list
            incorrectGuesses[incorrectGuessCount++] = guess[0];
            lives--;
            printf("Incorrect guess! Lives remaining: %d\n", lives);
        } else {
            score++;
            printf("Correct guess! Score: %d\n", score);
        }

        // Check if the word is fully guessed
        if (strcmp(displayedWord, selectedCategory[randomIndex]) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", selectedCategory[randomIndex]);
            break;
        }
    }

    if (lives == 0) {
        drawHangman(lives);
        printf("\nGame Over! The word was: %s\n", selectedCategory[randomIndex]);
    }

    return 0;
}