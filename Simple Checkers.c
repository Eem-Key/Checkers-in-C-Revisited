/*
TODO:
1. must capture when possible on turn, so you have to choose th piece that can capture if possible  done partially
    1.1 need to force the longest multiple capture
2. end conditions   done
    2.1 draw 40 moves no cptures    done
    2.2 opponent can not move       done
    2.3 surrender  or draw option
3. game over screen     done for now
    3.1 winner
    3.2 draw
4. main menu            done
    4.1 start game      done
    4.2 score sheet   done
    4.3 how to play     done
    4.4 exit            done
5. fix comments
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPTURES 4
#define SIZE 8
#define PIECES_COUNT 12

void printTitle() {
    printf("=====================================\n");
    printf("  _____ _               _             \n");
    printf(" / ____| |             | |            \n");
    printf("| |    | |__   ___  ___| | _____ _ __ \n");
    printf("| |    | '_ \\ / _ \\/ __| |/ / _ \\ '__|\n");
    printf("| |____| | | |  __/ (__|   <  __/ |   \n");
    printf(" \\_____|_| |_|\\___|\\___|_|\\_\\___|_|   \n\n");
    printf("=====================================\n\n");
}

void printMainMenu() {
    system("cls");

    printTitle();
    printf("           MAIN MENU                 \n");
    printf("-------------------------------------\n");
    printf("  1. Start Game                     \n");
    printf("  2. Score Sheet                   \n");
    printf("  3. How to Play                   \n");
    printf("  4. Exit                         \n");
    printf("-------------------------------------\n");
    printf("Please enter your choice (1-4): ");
}

void printBoard(char board[SIZE][SIZE]) {
    system("cls");

    printTitle();

    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    printf("    1   2   3   4   5   6   7   8\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%c |", letters[i]);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
}

void printGameOver(char board[SIZE][SIZE], int winner){
    printBoard(board);
    
    switch(winner){
        case 1:
            printf("\n~*~*~*~*~*~*~*~ Black wins ~*~*~*~*~*~*~*~\n"); 
            break;
        case 2:
            printf("\n~*~*~*~*~*~*~*~  Red wins  ~*~*~*~*~*~*~*~\n"); 
            break;
        case 3:
            printf("\n~*~*~*~*~*~*~*~    Draw    ~*~*~*~*~*~*~*~\n"); 
            break;
        default:
            printf("Why did it end????"); 
    }
}

void initializeBoard(char board[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = ' ';
            } else {
                board[i][j] = '.';
                // if (i < 3)
                //     board[i][j] = 'b'; // black piece
                // else if (i > 4)
                //     board[i][j] = 'r'; // red piece
                // else
                //     board[i][j] = '.'; // empty dark square
            }
        }
    }

    board[1][0] = 'b';
    board[4][3] = 'b';
    board[5][4] = 'r';

    // board[3][2] = 'b';
    // board[4][3] = 'r';
    // board[6][5] = 'r';

    // board[6][5] = 'b';
    // board[1][2] = 'r';

    // board[6][5] = 'B';
    // board[1][2] = 'R';

    // board[4][1] = 'r';
    // board[6][3] = 'R';
    // board[6][5] = 'r';
    // board[4][5] = 'r';
    // board[3][0] = 'b';

    // board[2][5] = 'b';
    // board[1][4] = 'B';
    // board[1][2] = 'B';
    // board[3][2] = 'b';
    // board[4][7] = 'r';

    // board[4][1] = 'r';
    // board[6][3] = 'R';
    // board[6][5] = 'r';
    // board[4][5] = 'r';
    // board[3][0] = 'b';
    // board[3][4] = 'B';

    // board[4][1] = 'r';
    // board[6][3] = 'R';
    // board[6][5] = 'r';
    // board[4][5] = 'r';
    // board[3][0] = 'b';
    // board[3][4] = 'B';

    // board[7][0] = 'r';
    // board[6][1] = 'b';
    // board[4][3] = 'b';

    // board[6][1] = 'b';
    // board[7][2] = 'r';
    // board[5][2] = 'r';
}

int convertChartoDecimal(char row){
    char letters[SIZE*2] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    
    for(int i = 0; i < SIZE*2; i++){
        if(letters[i] == row) return (i%8)+1;
    }

    return -1;
}

bool isBlackPiece(char piece) {
    return piece == 'b' || piece == 'B';
}

bool isRedPiece(char piece) {
    return piece == 'r' || piece == 'R';
}

int checkCapturableBoard(char board[SIZE][SIZE], int capturables[PIECES_COUNT][2], char color, bool multCapture){
    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int count = 0;
    bool capturable = false;
    for(int i = 1; i <= SIZE; i++){
        for(int j = 1; j <= SIZE; j++){
            capturable = false;
            //  if black piece
            if(isBlackPiece(color) && isBlackPiece(board[i-1][j-1])){
                //  caputures check: capturable true
                if((board[i+1][j+1] == '.' && isRedPiece(board[i][j]))
                    || (board[i+1][j-3] == '.' && isRedPiece(board[i][j-2]))) capturable = true;
                //  if kinged
                else if(board[i-1][j-1] == 'B'){
                    //  caputures backwards check: capturable true
                    if((board[i-3][j+1] == '.' && isRedPiece(board[i-2][j]))
                        || (board[i-3][j-3] == '.' && isRedPiece(board[i-2][j-2]))) capturable = true;
                }
                //  if capturable: add to array
                if(capturable){
                    capturables[count][0] = i-1;
                    capturables[count][1] = j-1;
                    count++;
                }
            }
            //  if red piece
            else if(isRedPiece(color) && isRedPiece(board[i-1][j-1])){
                //  caputures check: capturable true
                if((board[i-3][j+1] == '.' && isBlackPiece(board[i-2][j]))
                    || (board[i-3][j-3] == '.' && isBlackPiece(board[i-2][j-2]))) capturable = true;
                //  if kinged
                if(board[i-1][j-1] == 'R'){
                    //  caputures backwards check:  capturable true    
                    if((board[i+1][j+1] == '.' && isBlackPiece(board[i][j]))
                        || (board[i+1][j-3] == '.' && isBlackPiece(board[i][j-2]))) capturable = true;
                }
                //  if capturable: add to array
                if(capturable){
                    capturables[count][0] = i-1;
                    capturables[count][1] = j-1;
                    count++;
                }
            }
        }
    }
    //  display capturable pieces when possible and not when multi capturing
    if(count && !multCapture){
        printf("You can capture using:");
        for(int i = 0; i < count; i++){
            if (capturables[i][0] > -1) printf(" %c%d", letters[capturables[i][0]], capturables[i][1]+1);
        }
        printf("\n");
    }
 
    return count;
}

void checkCapturablePiece(char board[SIZE][SIZE], int placeables[CAPTURES][2], int row, int col){
    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int count = 0;

    //  if black piece
    if(isBlackPiece(board[row-1][col-1])){
        //  caputures check: add to placeables
        if(board[row+1][col+1] == '.' && isRedPiece(board[row][col])){
            placeables[count][0] = row+1;
            placeables[count][1] = col+1;
            count++;
        }
        if(board[row+1][col-3] == '.' && isRedPiece(board[row][col-2])){
            placeables[count][0] = row+1;
            placeables[count][1] = col-3;
            count++;
        }
        //  if kinged
        if(board[row-1][col-1] == 'B'){
            //  caputures backwards check: add to placeables
            if(board[row-3][col+1] == '.' && isRedPiece(board[row-2][col])){
                placeables[count][0] = row-3;
                placeables[count][1] = col+1;
                count++;
            }
            if (board[row-3][col-3] == '.' && isRedPiece(board[row-2][col-2])){
                placeables[count][0] = row-3;
                placeables[count][1] = col-3;
                count++;
            }
        }
    }
    //  if red piece
    else if(isRedPiece(board[row-1][col-1])){
        //  caputures check: add to placeables
        if(board[row-3][col+1] == '.' && isBlackPiece(board[row-2][col])){
                placeables[count][0] = row-3;
                placeables[count][1] = col+1;
                count++;
        }
        if (board[row-3][col-3] == '.' && isBlackPiece(board[row-2][col-2])){
                placeables[count][0] = row-3;
                placeables[count][1] = col-3;
                count++;
        }
        //  if kinged
        if(board[row-1][col-1] == 'R'){
            //  caputures backwards check: add to placeables    
            if(board[row+1][col+1] == '.' && isBlackPiece(board[row][col])){
                placeables[count][0] = row+1;
                placeables[count][1] = col+1;
                count++;
            }
            if (board[row+1][col-3] == '.' && isBlackPiece(board[row][col-2])){
                placeables[count][0] = row+1;
                placeables[count][1] = col-3;
                count++;
            }
        }
    }
    //  display placable tiles when possible
    if(count){
        printf("You can capture on:");
        for(int i = 0; i < count; i++){
            if (placeables[i][0] > -1) printf(" %c%d", letters[placeables[i][0]], placeables[i][1]+1);
        }
        printf("\n");
    }
    //  when no captures set placeables to -1
    else{
        placeables[0][0] = -1;
        placeables[0][1] = -1;
    }
}

int checkEnd(char board[SIZE][SIZE]){
    int placeables[CAPTURES][2];
    int countBlack = 0, countRed = 0;
    bool movableBlack = false, movableRed = false;

    for (int i = 1; i <= SIZE; i++) {
        for (int j = 1; j <= SIZE; j++) {
            if(isBlackPiece(board[i-1][j-1])) {
                if(!movableBlack){
                    checkCapturablePiece(board, placeables, i, j);
                    if(placeables[0][0] != -1 && placeables[0][1] != -1) movableBlack = true;
                    //  normal move check: breaks if exists
                    if(board[i][j] == '.' || board[i][j-2] == '.') movableBlack = true;
                    //  if kinged
                    if(board[i-1][j-1] == 'B'){
                        //  normal move backwards check: breaks if exists
                        if(board[i-2][j] == '.' || board[i-2][j-2] == '.') movableBlack = true;
                    }
                }
                countBlack++;
            }
            if(isRedPiece(board[i-1][j-1])) {
                if(!movableRed){
                    checkCapturablePiece(board, placeables, i, j);
                    if(placeables[0][0] != -1 && placeables[0][1] != -1) movableRed = true;
                    //  normal move check: breaks if exists
                    if(board[i-2][j] == '.' || board[i-2][j-2] == '.') movableRed = true;
                    //  if kinged
                    if(board[i-1][j-1] == 'R'){
                        //  normal move backwards check: breaks if exists
                        if(board[i][j] == '.' || board[i][j-2] == '.') movableRed = true;
                    }
                }
                countRed++;
            }

            //  if opponent can no longer move
        }
    }

    if(countBlack == 0 || !movableRed) return 1;
    if(countRed == 0 || !movableBlack) return 2;
    return 0;
}

bool turnBlack(char board[SIZE][SIZE]){
    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int capturables[PIECES_COUNT][2];
    int placeables[CAPTURES][2];
    char tempChooseRow, tempPlaceRow;
    int chooseCol, placeCol, chooseRow, placeRow, countCapturables;
    bool validInput = false, multCapture = false, didAction = false;

    //  turn loops when you're multicapturing
    do{
        //  display for multi capturing and not multi capturing
        if(multCapture){
            printBoard(board);
            printf("Black Turn ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
            printf("Multi-Capturing with %c%d\n", letters[placeRow-1], placeCol);
            chooseRow = placeRow;
            chooseCol = placeCol;
        }
        else{
            printf("Black Turn ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
        }
        //  check to see if player can capture any enemy pieces
        countCapturables = checkCapturableBoard(board, capturables, 'B', multCapture);

        if(!multCapture){
            while(!validInput){
                printf("Choose a piece to move: ");
                scanf(" %c%d", &tempChooseRow, &chooseCol);
        
                chooseRow = convertChartoDecimal(tempChooseRow);
                //  remember that variables are not in 0-based!!!
                //  checking input: valid checks for available moves
                if(chooseRow != -1 && chooseCol >= 1 && chooseCol <= 8 && isBlackPiece(board[chooseRow-1][chooseCol-1])){
                    //  if theres a possible capture
                    if(countCapturables > 0){
                        bool chosenCapturable = false;
                        for(int i = 0; i < countCapturables; i++){
                            //  player has to choose a piece that can capture: break if chosen
                            if(chooseRow == capturables[i][0]+1 && chooseCol == capturables[i][1]+1) 
                                chosenCapturable = true;
                        }
                        if(chosenCapturable) break;
                    }
                    //  no possible capture so checks for moves
                    else{
                        //  normal move check: breaks if exists
                        if(board[chooseRow][chooseCol] == '.' || board[chooseRow][chooseCol-2] == '.') break;
                        //  if kinged
                        if(board[chooseRow-1][chooseCol-1] == 'B'){
                            //  normal move backwards check: breaks if exists
                            if(board[chooseRow-2][chooseCol] == '.' || board[chooseRow-2][chooseCol-2] == '.') break;
                        }
                    }
                }
                //  error message and loops if did not break
                printf("Invalid input please try again\n");
            }
        }
    
        multCapture = false;

        checkCapturablePiece(board, placeables, chooseRow, chooseCol);

        while(!validInput){
            printf("Choose a tile to place your piece: ");
            scanf(" %c%d", &tempPlaceRow, &placeCol);
    
            placeRow = convertChartoDecimal(tempPlaceRow);
            //  checking input: valid checks if its a legal move
            if(placeRow != -1 && placeCol >= 1 && placeCol <= 8 && board[placeRow-1][placeCol-1] == '.'){
                //  remember that variables are not in 0-based!!!
                //  possible capture check: breaks if possible captures and captured
                if(countCapturables > 0){
                    //  captured check: breaks if captures
                    if(placeRow - chooseRow == 2 && abs(placeCol - chooseCol) == 2 && isRedPiece(board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2])){
                        didAction = true;
                        break;
                    }
                    //  if kinged
                    else if(board[chooseRow-1][chooseCol-1] == 'B'){
                        //  captured backwards check: breaks if captures
                        if(chooseRow - placeRow == 2 && abs(placeCol - chooseCol) == 2 && isRedPiece(board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2])){
                            didAction = true;
                            break;
                        }
                    }
                }
                //  if theres no possible captures then normal moves are checked
                else{
                    //  normal move check: breaks if exists
                    if(placeRow - chooseRow == 1 && abs(placeCol - chooseCol) == 1){
                        if(board[chooseRow-1][chooseCol-1] == 'b') didAction = true;
                        break;
                    }
                    //  if theres no possible captures then normal backwards moves are checked
                    else if(board[chooseRow-1][chooseCol-1] == 'B'){
                        //  normal move backwards check: breaks if exists
                        if(chooseRow - placeRow == 1 && abs(placeCol - chooseCol) == 1) break;
                    }
                }
            }
            //  error message and loops if did not break
            printf("Invalid input please try again\n");
        }

        char piece = board[chooseRow-1][chooseCol-1];
        //  kinging if reaches the end
        if (piece == 'b' && placeRow == 8) piece = 'B';
        //  execute the move
        board[placeRow-1][placeCol-1] = piece;
        board[chooseRow-1][chooseCol-1] = '.';
        //  if captures take the opponent piece
        if(abs(placeRow - chooseRow) == 2) board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2] = '.';

        checkCapturablePiece(board, placeables, placeRow, placeCol);

        if(placeables[0][0] != -1 && placeables[0][1] != -1) multCapture = true;
        if(checkEnd(board)) multCapture = false;
    }while(multCapture);

    return didAction;
}

bool turnRed(char board[SIZE][SIZE]){
    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int capturables[PIECES_COUNT][2];
    int placeables[CAPTURES][2];
    char tempChooseRow, tempPlaceRow;
    int chooseCol, placeCol, chooseRow, placeRow, countCapturables;
    bool validInput = false, multCapture = false, didAction = false;

    do{
        if(multCapture){
            printBoard(board);
            printf("Red Turn   ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
            printf("Multi-Capturing with %c%d\n", letters[placeRow-1], placeCol);
            chooseRow = placeRow;
            chooseCol = placeCol;
        }
        else{
        printf("Red Turn   ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
        }

        countCapturables = checkCapturableBoard(board, capturables, 'R', multCapture);

        if(!multCapture){
            while(!validInput){
                printf("Choose a piece to move: ");
                scanf(" %c%d", &tempChooseRow, &chooseCol);

                chooseRow = convertChartoDecimal(tempChooseRow);
                //  remember that variables are not in 0-based!!!
                //  checking input: valid checks for available moves
                if(chooseRow != -1 && chooseCol >= 1 && chooseCol <= 8 && isRedPiece(board[chooseRow-1][chooseCol-1])){
                    //  if theres a possible capture
                    if(countCapturables > 0){
                        bool chosenCapturable = false;
                        for(int i = 0; i < countCapturables; i++){
                            //  player has to choose a piece that can capture: break if chosen
                            if(chooseRow == capturables[i][0]+1 && chooseCol == capturables[i][1]+1) 
                                chosenCapturable = true;
                        }
                        if(chosenCapturable) break;
                    }
                    //  no possible capture so checks for moves
                    else{
                        //  normal move check: breaks if exists
                        if(board[chooseRow-2][chooseCol] == '.' || board[chooseRow-2][chooseCol-2] == '.') break;
                        //  if kinged
                        if(board[chooseRow-1][chooseCol-1] == 'R'){
                            //  normal move backwards check: breaks if exists
                            if(board[chooseRow][chooseCol] == '.' || board[chooseRow][chooseCol-2] == '.') break;
                        }
                    }
                }       
                //  error message and loops if did not break
                printf("Invalid input please try again\n");
            }
        }

        multCapture = false;

        checkCapturablePiece(board, placeables, chooseRow, chooseCol);

        while(!validInput){
            printf("Choose a tile to place your piece: ");
            scanf(" %c%d", &tempPlaceRow, &placeCol);

            placeRow = convertChartoDecimal(tempPlaceRow);
            //  checking input: valid checks if its a legal move
            if(placeRow != -1 && placeCol >= 1 && placeCol <= 8 && board[placeRow-1][placeCol-1] == '.'){
                //  remember that variables are not in 0-based!!!
                //  possible capture check: breaks if possible captures and captured
                if(countCapturables > 0){
                    //  captured check: breaks if captures
                    if(chooseRow - placeRow == 2 && abs(placeCol - chooseCol) == 2 && isBlackPiece(board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2])){
                        didAction = true;
                        break;
                    }
                    //  if kinged
                    else if(board[chooseRow-1][chooseCol-1] == 'R'){
                        //  captured backwards check: breaks if captures
                        if(placeRow - chooseRow == 2 && abs(placeCol - chooseCol) == 2 && isBlackPiece(board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2])){
                            didAction = true;
                            break;
                        }
                    }
                }
                //  if theres no possible captures then normal moves are checked
                else{
                    //  normal move check: breaks if exists
                    if(chooseRow - placeRow == 1 && abs(placeCol - chooseCol) == 1){
                        if(board[chooseRow-1][chooseCol-1] == 'r') didAction = true;
                        break;
                    }
                    //  if theres no possible captures then normal backwards moves are checked
                    else if(board[chooseRow-1][chooseCol-1] == 'R'){
                        //  normal move backwards check: breaks if exists
                        if(placeRow - chooseRow == 1 && abs(placeCol - chooseCol) == 1) break;
                    }
                }
            }
            //  error message and loops if did not break
            printf("Invalid input please try again\n");
        }
        
        char piece = board[chooseRow-1][chooseCol-1];
        //  kinging if reaches the end
        if (piece == 'r' && placeRow == 1) piece = 'R';
        //  execute the move
        board[placeRow-1][placeCol-1] = piece;
        board[chooseRow-1][chooseCol-1] = '.';
        //  if captures take the opponent piece
        if(abs(placeRow - chooseRow) == 2) board[(placeRow+chooseRow-2)/2][(placeCol+chooseCol-2)/2] = '.';

        checkCapturablePiece(board, placeables, placeRow, placeCol);

        if(placeables[0][0] != -1 && placeables[0][1] != -1) multCapture = true;
        if(checkEnd(board)) multCapture = false;
    }while(multCapture);

    return didAction;
}

int main() { 
    int gameLogs[1000][2];
    int choice, redPoints = 0, blackPoints = 0, games = 0;

    do {
        printMainMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                char board[SIZE][SIZE];
                bool didAction = false;
                int turn = 0, lastAction = 0, winner = 0;
            
                initializeBoard(board);

                while(!winner){
                    turn++;
                    printBoard(board);
            
                    if(turn % 2 == 1){  // black or darker moves first
                        didAction = turnBlack(board);
                        winner = checkEnd(board);
                    }
                    else{   // red or white goes second
                        didAction = turnRed(board);
                        winner = checkEnd(board);
                    }
                    //  if move limit reached draw
                    lastAction++;
                    if(didAction) lastAction = 0;
                    if(lastAction == 40){
                        winner = 3;
                    }
                }
                //  log the points
                if(winner == 1) blackPoints++;
                else if (winner == 2) redPoints++;
                //  log the game logs
                gameLogs[games][0] = winner;
                gameLogs[games][1] = turn;
                games++;
                //print the final board and winner
                printGameOver(board, winner);
                break;
            case 2:
                char inputExitSS = 0;
                do{
                    system("cls");
                    printf("=====================================\n");
                    printf("Score Sheet");
                    printf("\n=====================================\n\n");
                    printf(" Black Points\t\tRed Points\n");
                    printf("      %d    \t\t    %d\n\n", blackPoints, redPoints);
                    printf("Game Logs:\n");
                    if(games){
                        for(int i = 0; i < games; i++){
                            printf("Game %d : ", i+1);
                            if(gameLogs[i][0] == 1) printf("Black Won in %d turns\n", gameLogs[i][1]);
                            else if (gameLogs[i][0] == 2) printf("Red Won in %d turns\n", gameLogs[i][1]);
                            else if (gameLogs[i][0] == 3) printf("Draw in %d turns\n", gameLogs[i][1]);
                            else printf("idk cuh\n");
                        }
                    }
                    else{
                        printf("Sorry no games have been played to display\n");
                    }
                    printf("\nEnter any key to exit: ");
                    scanf(" %c", &inputExitSS);
                }while(!inputExitSS);
                break;
            case 3:
                char inputExitHTP = 0;
                do{
                    system("cls");
                    printf("=====================================\n");
                    printf("\nHow to Play\n");
                    printf("\n=====================================\n");
    
                    printf(" - How to Move\n");
                    printf(" \t- Input the position of the piece in the board to select and move pieces.\n");
                    printf(" \t- Pieces can only move diagonally onto the '.' squares.\n");
                    printf(" \t- A piece can only move to an empty square.\n");
    
                    printf(" - King Pieces\n");
                    printf(" \t- When a piece reaches the opponent's back row (the farthest row), it is \"kinged\" ('B' or 'R').\n");
                    printf(" \t- Kings can move diagonally forward and backward by one square.\n");
                    printf(" \t- Kings can also capture forward and backward.\n");
    
    
                    printf(" - Capturing\n");
                    printf(" \t- If an opponent;s piece is diagonally adjacent and the square beyond it is empty, you must jump over it, capturing (removing) the opponent's piece..\n");
                    printf(" \t- Multiple jumps are possible in a single turn if each jump meets the capturing conditions.\n");
                    printf(" \t- Capturing is mandatory; if you can capture, you must.\n");
                    printf(" - Kings move backwards.\n\n");
                    
                    printf(" - How to Win\n");
                    printf(" \t- Capture opponent's pieces or make them unable to move to win.\n");
    
                    printf("\nEnter any key to exit: ");
                    scanf(" %c", &inputExitHTP);
                }while(!inputExitHTP);
                break;
            case 4:
                printf("\nExiting the game. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a number between 1 and 4.\n\n");
        }
    } while(choice != 4);


    return 0;
}