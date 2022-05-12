
#include "LinkedList.h"
#include "Board.h"
#include "Person.h"
#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#define EXIT_SUCCESS    0

// The main menu for the program
void mainMenu(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<std::string> moveHistory);
void checkQuit(std::string input);
// Initialises a new game
bool newGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag);
// Loads in a saved game from the users files
bool loadGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer);
// Reads in the information from a save game
bool readGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::string& fileName, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer);
// Starts the main game loop
void play(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, bool isNewGame, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer);
// Input used for taking in user input and actions
void moveDecide(std::shared_ptr<Person> player, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<Person> player1, std::shared_ptr<Person> player2, std::shared_ptr<std::string> moveHistory);
// Displays the credits for the game
void credits();
//method to determine if the winners score is in the top 3 highest scores (to date)
void highScore(int score);
//method to display the current high scores
void displayHighScores();

// Misc methods that assists in user input and loading in games
void printPlay(std::shared_ptr<Person> player1, std::shared_ptr<Person> player2, std::shared_ptr<Board> board, std::shared_ptr<Person> turn);
std::string readLine(std::string& fileName, int line);
std::shared_ptr<LinkedList> stringToList(std::string hand);
void tileToBoard(std::string tiles, std::shared_ptr<Board> board);
void makeCapital(std::string& s);
bool isLetters(std::string input);
// determines whether the colour option is on or off (default off)
bool colourOn = false;

int main(void) {

   std::shared_ptr<Person> player1(new Person("", std::shared_ptr<LinkedList>(new LinkedList()), 0));
   std::shared_ptr<Person> player2(new Person("", std::shared_ptr<LinkedList>(new LinkedList()), 0));

   std::shared_ptr<LinkedList> tileBag(new LinkedList());
   
   std::shared_ptr<Board> board(new Board());

   std::shared_ptr<std::string> moveHistory(new std::string(""));

   mainMenu(player1, player2, tileBag, board, moveHistory);

   return EXIT_SUCCESS;
}

void mainMenu(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<std::string> moveHistory) {
   // print out Qwirkle logo (just for fun) inspired by: http://www.network-science.de/ascii/
   std::cout << "  ___           _      _    _      " << std::endl;
   std::cout << " / _ \\__      _(_)_ __| | _| | ___ " << std::endl;
   std::cout << "| | | \\ \\ /\\ / / | '__| |/ / |/ _ \\" << std::endl;
   std::cout << "| |_| |\\ V  V /| | |  |   <| |  __/" << std::endl;
   std::cout << " \\__\\_\\ \\_/\\_/ |_|_|  |_|\\_\\_|\\___|" << std::endl;
   
   // display welcome message
   std::cout << "\nWelcome to Quirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << "*** NOTE: If at any stage you get stuck, type 'help'. Enjoy! ***" << std::endl;

   // display main menu
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game\n2. Load Game\n3. Credits\n4. Quit" << std::endl;
   std::cout << "5. Toggle " << ESC << RED_TXT << "m" << "C" << RESET << ESC << ORANGE_TXT << "m" << "O" << RESET << ESC << YELLOW_TXT << "m" << "L" << RESET << 
    ESC << GREEN_TXT << "m" << "O" << RESET << ESC << BLUE_TXT << "m" << "U" << RESET << ESC << PURPLE_TXT << "m" << "R" << RESET << " on (off by default)" << std::endl;
   std::cout << "6. Display High Scores" << std::endl;

   // user selects from different options using input
   std::string selection;

   std::cin >> selection;

   checkQuit(selection);
   
   // Redirects user based on their input to the desired function 
   if (selection == "1") {
      if (newGame(playerA, playerB, bag)){
         std::shared_ptr<std::string> currentPlayer(new std::string(playerA->getName()));
         play(playerA, playerB, bag, board, true, moveHistory, currentPlayer);
      }
   }

   else if (selection == "2") {
      std::shared_ptr<std::string> currentPlayer(new std::string(""));
      if (loadGame(playerA, playerB, bag, board, moveHistory, currentPlayer)){
         play(playerA, playerB, bag, board, false, moveHistory, currentPlayer);
      }
   }

   else if (selection == "3") {
      credits();
      mainMenu(playerA, playerB, bag, board, moveHistory);
   }

   else if (selection == "4") {
      std::cout << "Goodbye" << std::endl;
      exit(EXIT_SUCCESS);
   }

   else if (selection == "5"){
      if (colourOn == true){
         colourOn = false;
         std::cout << "Colour turned off!" << std::endl;
      }
      else if (colourOn == false){
         colourOn = true;
         std::cout << "Colour turned on!" << std::endl;
      }
      mainMenu(playerA, playerB, bag, board, moveHistory);
   }

   else if (selection == "6"){
      displayHighScores();
      mainMenu(playerA, playerB, bag, board, moveHistory);
   }

   // TODO: 
   else if (selection == "help"){
      std::cout << "Select a number as displayed...\nType 1 and press enter if you wish to start a new game\nType 2 and press enter if you wish to load a previously saved game" << std::endl;
      std::cout << "Type 3 and press enter if you wish to view the credits\nType 4 and press enter if you wish to quit the game\nType 5 and press enter if you wish to turn Colour on for tiles" << std::endl;
      std::cout << "Type 6 and press enter if you want to view the current highscores\n" << std::endl;
      mainMenu(playerA, playerB, bag, board, moveHistory);
   }

   else {
      std::cout << "\nInvalid input. Please try again.\n" << std::endl;
      mainMenu(playerA, playerB, bag, board, moveHistory);
   }

}

void play(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, bool isNewGame, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer){

   // Draws 6 tiles for each player if it is a new game
   if (isNewGame == true) {
      for (int i = 0; i < 12; i++){
         // Sets the users initial hand
         if (i < 6) {
            playerA -> getHand() -> addBack(bag -> getTile(0));
            bag -> deleteFront();
         } else {
            playerB -> getHand() -> addBack(bag -> getTile(0));
            bag -> deleteFront();
         }
      }
   }
   
   // Decides the current turn based on the save file or if it is a new game
   int turn = 1;
   if (*currentPlayer == playerB->getName()){
      turn++;
   }

   // Ignores the first input because no endline character from previous cin
   std::cin.ignore();

   // Next move as long as the bag and one player's hand isn't empty
   while ((playerA -> getHand() -> getLength() != 0) && (playerB -> getHand() -> getLength() != 0)){
      
      if (turn % 2 == 1) {
         printPlay(playerA, playerB, board, playerA);
         moveDecide(playerA, bag, board, playerA, playerB, moveHistory);
      } else {
         printPlay(playerA, playerB, board, playerB);
         moveDecide(playerB, bag, board, playerA, playerB, moveHistory);
      }
      
      turn++;
   }
   std::shared_ptr<Person> winningPlayer = playerA;
   std::cout << "Game over" << std::endl;
   std::cout << "Score for " << playerA -> getName() << ": " << playerA -> getPoints() << std::endl;
   std::cout << "Score for " << playerB -> getName() << ": " << playerB -> getPoints() << std::endl;
   // Gives the player who finished their hand first an extra 6 points
   if (playerA->getHand()->getLength() == 0){
      playerA->setPoints(6);
   }
   else {
      playerB->setPoints(6);
   }
   // Declares the player with the most points the winner
   if (playerA->getPoints() == playerB->getPoints()){
      std::cout << "Tie!" << std::endl;
      // if tie, see if player score is a high score (doesnt matter which player as both are equal points)
      highScore(playerA->getPoints());
      displayHighScores();
   }
   else {
      if (playerB->getPoints() > playerA->getPoints()){
         winningPlayer = playerB;
      }
      std::cout << winningPlayer->getName() << " wins!" << std::endl;
      //checks if the winning players score is a high score
      highScore(winningPlayer->getPoints());
      displayHighScores();
   }
}

// Prints the game state
void printPlay(std::shared_ptr<Person> player1, std::shared_ptr<Person> player2, std::shared_ptr<Board> board, std::shared_ptr<Person> turn){
   std::cout << turn -> getName() << ", it's your turn" << std::endl;
   std::cout << "Score for " << player1 -> getName() << ": " << player1 -> getPoints() << std::endl;
   std::cout << "Score for " << player2 -> getName() << ": " << player2 -> getPoints() << std::endl;

   if (colourOn == false){
      board -> printBoard();
   }
   else if (colourOn == true){
      board -> printBoardColoured();
   }

   std::cout << "\nYour hand is" << std::endl;
   std::cout << turn -> getHand() -> toString() << std::endl;
} 

void moveDecide(std::shared_ptr<Person> player, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<Person> player1, std::shared_ptr<Person> player2, std::shared_ptr<std::string> moveHistory){
   std::string move;
   std::getline(std::cin, move);
   int moveLength = move.length();

   checkQuit(move);

   // Replaces the selected tile with the first tile in the tilebag and sends the selected tile to back of the bag
   if (move.std::string::find("replace") != std::string::npos && moveLength == 10){
      if (bag->getLength() != 0){
         std::shared_ptr<Tile> temp(new Tile(move.at(8), (int)move.at(9) - '0'));
         // Checks first if the tile is actually in the users hand
         if (player -> getHand() -> compareTile(temp)){
            // Replaces the tile and adds it back to bag
            bag -> addBack(temp);
            player -> getHand() -> replaceTile(temp, bag -> getTile(0));
            bag -> deleteFront();
         } else {
            std::cout << "Invalid Replacement. Please try again." << std::endl;
            moveDecide(player, bag, board, player1, player2, moveHistory);
         }
      }
      else {
         std::cout << "Tile Bag is empty!" << std::endl;
         moveDecide(player, bag, board, player1, player2, moveHistory);
      }
   } 
   else if (move.std::string::find("place") != std::string::npos && (moveLength == 14 || moveLength == 15)){
      std::shared_ptr<Tile> temp(new Tile(move.at(6), (int)move.at(7) - '0'));
      int row = (int)move.at(12) - 65;
      int col;
      // Checks if the col contains a two or single digit number
      if (moveLength == 14){
         col = (int)move.at(13) - '0';
      }
      else {
         col = ((int)move.at(13) - '0') * 10 + (int)move.at(14) - '0';
      }

      bool hasTile = player->getHand()->compareTile(temp);
      bool validMove = false;
      bool validSpace = (row >=0 && 26 >= row && col >=0 && 26 >= col);
      if (validSpace){
         validMove = (*moveHistory == "" || board->validMove(row, col, temp));
      }
      
      // Checks if it is a valid move and if the tile exists in the player's hand
      if (hasTile && validMove && validSpace){
         board->addTile(row, col, temp);
         
         player -> getHand() -> removeTile(temp);
         if (bag -> getLength() > 0) {
            player -> getHand() -> addBack(bag -> getTile(0));
            bag -> deleteFront();
         }
         player -> setPoints(board -> calculatePoints(row, col));
         if (*moveHistory == ""){
            *moveHistory = *moveHistory + temp -> toString() + '@' + move.at(12) + move.at(13);
         } else {
            *moveHistory = *moveHistory + ", " + temp -> toString() + '@' + move.at(12) + move.at(13);
         }
      } else {
         std::cout << "Invalid Placement. Please try again." << std::endl;
         moveDecide(player, bag, board, player1, player2, moveHistory);
      }
   } else if (move.std::string::find("save") != std::string::npos){
      std::vector<std::string> inputWords;
      std::stringstream ss(move);
      std::string word;

      while (std::getline(ss, word, ' ')){
         inputWords.push_back(word);
      }

      if (inputWords.size() == 2 && inputWords.at(0) == "save"){
         std::ofstream output(inputWords.at(1));

         output << player1 -> getName() << std::endl;
         output << player1 -> getPoints() << std::endl;
         output << player1 -> getHand() -> toString() << std::endl;
         output << player2 -> getName() << std::endl;
         output << player2 -> getPoints() << std::endl;
         output << player2 -> getHand() -> toString() << std::endl;
         output << "26,26" << std::endl;
         output << *moveHistory << std::endl;
         output << bag -> toString() << std::endl;
         output << player -> getName() << std::endl;

         std::cout << "Game saved successfully" << std::endl;

      }
      else {
         std::cout << "Please input a valid save game name\n";
      }
      

   } else if (move.std::string::find("quit") != std::string::npos) {
      std::cout << "Goodbye" << std::endl;
      exit(EXIT_SUCCESS);
   } else if (move.std::string::find("help") != std::string::npos) {
      std::cout << "These are the possible moves/commands:" << std::endl;
      std::cout << "Replace: Type replace and type one of the tiles from your hand which you wish to replace with a random tile from the bag! Eg. 'Replace R4'" << std::endl;
      std::cout << "Place: Type place and type one of the tiles from your hand which you want to place somewhere, then type 'at' followed with a valid place on the board. Eg. 'Place R4 at Z1'" << std::endl;
      std::cout << "Save: Save your current game" << std::endl;
      std::cout << "Quit: Quit your current game (if you wish to save your game, do that first)" << std::endl;

      moveDecide(player, bag, board, player1, player2, moveHistory);
   } else {
      std::cout << "Invalid Choice. Please try again." << std::endl;
      moveDecide(player, bag, board, player1, player2, moveHistory);
   }
}

void checkQuit(std::string input) {
   if (input == "^D") {
      std::cout << "Goodbye" << std::endl;
      exit(EXIT_SUCCESS);
   }
}

bool newGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag) {
   std::cout << "\nStarting a New Game\n" << std::endl;

   //get players names
   std::string name1 = "";
   std::string name2 = "";

   //check if player names are valid (only letters)
   bool conditionsMet = false;
   while (conditionsMet == false) {
      std::cout << "Enter a name for Player 1:" << std::endl;
      std::cin >> name1;
      
      checkQuit(name1);

      if (isLetters(name1) == true) {
         std::cout << "Player1: " << name1 << std::endl;
         // creating player1 object
         playerA -> setName(name1);
         playerA -> setHand(std::shared_ptr<LinkedList>(new LinkedList));
         playerA -> setPoints(0);
         conditionsMet = true;
      }
   
      else {
         std::cout << "Invalid input: only letters permitted, please try again!" << std::endl;
      }
   }

   conditionsMet = false;
   while (conditionsMet == false) {
      std::cout << "Enter a name for Player 2:" << std::endl;
      std::cin >> name2;

      checkQuit(name2);

      if (isLetters(name2) == true) {
         std::cout << "Player2: " << name2 << std::endl;
         // creating player2 object
         playerB -> setName(name2);
         playerB -> setHand(std::shared_ptr<LinkedList>(new LinkedList));
         playerB -> setPoints(0);
         conditionsMet = true;
      }
   
      else {
         std::cout << "Invalid input: only letters permitted, please try again!" << std::endl;
      }
   }

   bag -> fillBag();
   bag -> shuffle();
      
   std::cout << "Let's Play!\n" << std::endl;
   return true;
}

bool loadGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer){
   bool loadSuccess;
   std::string fileName;
   std::cout << "\nEnter the filename from which load a game\n" << std::endl;
   std::cin >> fileName;

   checkQuit(fileName);
   
   int count = 0;
   std::string line;
   std::ifstream file(fileName);
   // Checks if file exists
   if (file.good()){
      while (std::getline(file, line)){
         count++;
      }
   }
   else {
      std::cout << "File doesn't exist" << std::endl;
   }
   // Checks if the format is correct
   if (count == 10 && readGame(playerA, playerB, bag, board, fileName, moveHistory, currentPlayer)){
      std::cout << "Qwirkle game successfully loaded" << std::endl;
      loadSuccess = true;
   } 
   else {
      std::cout << "Please enter a valid file" << std::endl;
      loadGame(playerA, playerB, bag, board, moveHistory, currentPlayer);
   }
   return loadSuccess;
}

bool readGame(std::shared_ptr<Person> playerA, std::shared_ptr<Person> playerB, std::shared_ptr<LinkedList> bag, std::shared_ptr<Board> board, std::string& fileName, std::shared_ptr<std::string> moveHistory, std::shared_ptr<std::string> currentPlayer){
    try {
      // Strips any unnecessary characters at the end 
      std::string playerAName = readLine(fileName, 1);
      if (playerAName.back() == '\n' || playerAName.back() == '\r'){
         playerAName.erase(playerAName.length() - 1);
      }
      std::string playerBName = readLine(fileName, 4);
      if (playerBName.back() == '\n' || playerBName.back() == '\r'){
         playerBName.erase(playerBName.length() - 1);
      }
      // Sets the inititalised variable to the details in the save game
      playerA -> setName(playerAName);
      playerA -> setHand(stringToList(readLine(fileName, 3)));
      playerA -> setPoints(stoi(readLine(fileName, 2)));
      playerB -> setName(playerBName);
      playerB -> setHand(stringToList(readLine(fileName, 6)));
      playerB -> setPoints(stoi(readLine(fileName, 5)));
      *moveHistory = readLine(fileName, 8);
      tileToBoard(readLine(fileName, 8), board);
      bag -> copyList(stringToList(readLine(fileName, 9)));
      std::string temp = readLine(fileName,10);
      if (temp.back() == '\n' || temp.back() == '\r'){
         temp.erase(temp.length() - 1);
      }
      *currentPlayer = temp;
      return true;
    } catch (std::invalid_argument const&) {
      std::cout << fileName << " is an invalid file. Please try again." << std::endl;
      return false;
    }

}

void highScore(int score){
   // assign text file inputs
    std::ifstream highScoreIN1("Highscores/highscore1.txt");
    std::ifstream highScoreIN2("Highscores/highscore2.txt");
    std::ifstream highScoreIN3("Highscores/highscore3.txt");

    int highScore1;
    int highScore2;
    int highScore3;

    // assign text file inputs to int variables
    highScoreIN1 >> highScore1;
    highScoreIN2 >> highScore2;
    highScoreIN3 >> highScore3;

    // assign text file outputs
    std::ofstream highScoreOUT1("Highscores/highscore1.txt");
    std::ofstream highScoreOUT2("Highscores/highscore2.txt");
    std::ofstream highScoreOUT3("Highscores/highscore3.txt");
    
    if (score == highScore1){
        highScoreOUT1 << highScore1;
        highScoreOUT2 << highScore2;
        highScoreOUT3 << highScore3;
        std::cout << "Matched the HIGHEST Score! Amazing Effort!!!" << std::endl;
    }
    else if (score > highScore1){
        highScoreOUT1 << score;
        highScoreOUT2 << highScore1;
        highScoreOUT3 << highScore2;
        std::cout << "New HIGHEST Score achieved! Congratulations!!!" << std::endl;
    }
    else {
        highScoreOUT1 << highScore1;
        if (score == highScore2){
            highScoreOUT2 << highScore2;
            highScoreOUT3 << highScore3;
            std::cout << "Matched the SECOND HIGHEST Score! Great Effort!!!" << std::endl;
        }
        else if (score > highScore2){
            highScoreOUT2 << score;
            highScoreOUT3 << highScore2;
            std::cout << "New SECOND HIGHEST Score achieved! Amazing!!!" << std::endl;
        }
        else {
            highScoreOUT2 << highScore2;
            if (score == highScore3){
                highScoreOUT3 << highScore3;
                std::cout << "Matched the THIRD HIGHEST Score! Good Effort!!!" << std::endl;
            }
            else if (score > highScore3){
                highScoreOUT3 << score;
                std::cout << "New THIRD HIGHEST Score achieved! Well done!!!" << std::endl;
            }
            else {
                highScoreOUT3 << highScore3;
                std::cout << "No High Score achieved, maybe next time!" << std::endl;
            }
        }
    }
}

void displayHighScores() {
   // assign text file inputs
    std::ifstream highScoreIN1("Highscores/highscore1.txt");
    std::ifstream highScoreIN2("Highscores/highscore2.txt");
    std::ifstream highScoreIN3("Highscores/highscore3.txt");

    int highScore1;
    int highScore2;
    int highScore3;

    // assign text file inputs to int variables
    highScoreIN1 >> highScore1;
    highScoreIN2 >> highScore2;
    highScoreIN3 >> highScore3;

    std::cout << "Highest Score: " << highScore1 << std::endl;
    std::cout << "Second Highest Score: " << highScore2 << std::endl;
    std::cout << "Third Highest Score: " << highScore3 << std::endl;
}

std::string readLine(std::string& fileName, int line){
   std::ifstream file(fileName);
   std::string out;
   for (int i = 0; i < line; i++){
      std::getline(file, out);
   }
   return out;
}

std::shared_ptr<LinkedList> stringToList(std::string hand){
   std::shared_ptr<LinkedList> list(new LinkedList());
   std::string out;
   std::stringstream ss(hand);
   std::shared_ptr<Tile> temp;
   while(std::getline(ss, out, ',')) {
      temp = std::shared_ptr<Tile>(new Tile(out.at(0), (int)out.at(1) - '0'));
      list -> addBack(temp);
   }
   return list;
}

void tileToBoard(std::string tiles, std::shared_ptr<Board> board){
   std::string out;
   std::stringstream ss(tiles);
   std::shared_ptr<Tile> temp;
   while(std::getline(ss, out, ',')){
      int firstIndex = out.find_first_not_of(' ');
      int lastIndex = out.find_last_not_of(' ');
      out = out.substr(firstIndex, lastIndex - firstIndex + 1);
      temp = std::shared_ptr<Tile>(new Tile(out.at(0), (int)out.at(1) - '0'));
      board -> addTile ((int)out.at(3) - 65, (int)out.at(4) - '0', temp);
   }
}

// function to make string capital
void makeCapital(std::string& s) {
    for(unsigned int i=0;i<s.length();i++){
        s[i] = toupper(s[i]);
    }
}

// function to check if string only contains letters
bool isLetters(std::string input) {
    for (unsigned int i = 0; i < input.size(); i++)
    {
        int uppercaseChar = toupper(input[i]);
        if ((uppercaseChar < 'A' || uppercaseChar > 'Z') && uppercaseChar != ' ') 
        {
            return false;
        }
    }

    return true;
}

void credits() {
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: Matthew Pike" << std::endl;
    std::cout << "Student Number: s3865305" << std::endl;
    std::cout << "Email Address: s3865305@student.rmit.edu.au" << std::endl;

    std::cout << "\nName: Rohan Poorun" << std::endl;
    std::cout << "Student Number: s3843078" << std::endl;
    std::cout << "Email Address: s3843078@student.rmit.edu.au" << std::endl;

    std::cout << "\nName: Antigony Haikalis" << std::endl;
    std::cout << "Student Number: s3840637" << std::endl;
    std::cout << "Email Address: s3840637@student.rmit.edu.au" << std::endl;

    std::cout << "\nName: Andy Ho Ming Moy" << std::endl;
    std::cout << "Student Number: s3842349" << std::endl;
    std::cout << "Email Address: s3842349@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;

}


