#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#define CHANCES 6

std::string getPhrase(std::string filename) {
    std::vector<std::string> phrases;
    std::ifstream file;
    file.open(filename);
    while (file) {
        char str[255];
        file.getline(str, 255);
        phrases.push_back(str);
    }
    int nPhrases = phrases.size() - 1;
    srand(time(NULL));
    int rnum = rand() % nPhrases;
    std::string phrase = phrases[rnum];
    for (int i = 0; i < phrase.length(); i++) {
        phrase[i] = std::tolower(phrase[i]);
    }
    return phrase;
}

char getCharInput() {
    /* Function to take one and only one input character.
     * Outer loop to prevent empty input.
     * Inner loop to get rid of additional/invalid chars and newline.
     * The returned value is lowercased.
     */
    bool isValidChar = false;
    char guess;
    while (!isValidChar) {
        printf("Pick a letter: ");
        char next = std::cin.get();
        while (next != 10) {
            isValidChar = true;
            guess = std::tolower(next);
            if (guess < 'a' || guess > 'z') {
                isValidChar = false;
            }
            next = std::cin.get();
        }
    }
    return guess;
}

bool charIsInPhrase(char c, std::string phrase) {
    for (int i = 0; i < phrase.length(); i++) {
        if (c == phrase[i]) {
            return true;
        }
    }
    return false;
}

std::string updatePhraseGuessed(char guess, std::string phraseGuessed, std::string phrase) {
    for (int i = 0; i < phraseGuessed.length(); i++) {
        if (phrase[i] == guess) {
            phraseGuessed[i] = guess;
        }
    }
    return phraseGuessed;
}

void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void drawHangman(int mistakes) {
    std::string hangman;
    switch (mistakes) {
    case 0:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 1:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 2:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |    |  "  "\n"
            "   |    |  "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 3:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |   /|  "  "\n"
            "   |    |  "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 4:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |   /|\\"  "\n"
            "   |    |  "  "\n"
            "   |       "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 5:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |   /|\\"  "\n"
            "   |    |  "  "\n"
            "   |   /   "  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    case 6:
        hangman =
            "   +----+  "  "\n"
            "   |    |  "  "\n"
            "   |    O  "  "\n"
            "   |   /|\\"  "\n"
            "   |    |  "  "\n"
            "   |   / \\"  "\n"
            "   |       "  "\n"
            "---+----   "  "\n";
        break;
    }
    std::cout << hangman;
}

void displayWrongChars(char wrongChars[]) {
    std::cout << "Wrong guesses: ";
    std::cout << wrongChars[0];
    int i = 1;
    while (i < CHANCES && wrongChars[i] != ' ') {
        std::cout << ", ";
        std::cout << wrongChars[i];
        i++;
    }
    printf("\n");
}

int main() {
    const std::string PHRASE = getPhrase(".\\word_list.txt");
    std::string phraseGuessed = PHRASE;
    for (int i = 0; i < phraseGuessed.length(); i++) {
        if (PHRASE[i] == ' ') {
            phraseGuessed[i] = ' ';
        } else {
            phraseGuessed[i] = '_';
        }
    }

    char wrongChars[CHANCES];
    for (int i = 0; i < CHANCES; i++) {
        wrongChars[i] = ' ';
    }

    int mistakes = 0;
    clearScreen();
    drawHangman(mistakes);
    std::cout << "Guess: " << phraseGuessed << std::endl;
    displayWrongChars(wrongChars);
    while (true) {
        char guess = getCharInput();
        if (charIsInPhrase(guess, PHRASE)) {
            phraseGuessed = updatePhraseGuessed(guess, phraseGuessed, PHRASE);
        } else if (!charIsInPhrase(guess, wrongChars)) {
            wrongChars[mistakes] = guess;
            mistakes++;
        }

        clearScreen();
        drawHangman(mistakes);
        std::cout << "Guess: " << phraseGuessed << std::endl;
        displayWrongChars(wrongChars);

        if (PHRASE.compare(phraseGuessed) == 0) {
            printf("You win!\n");
            break;
        }
        if (mistakes == CHANCES) {
            printf("You lose! The answer is: ");
            std::cout << PHRASE << std::endl;
            break;
        }
    }
}
