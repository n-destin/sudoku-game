#include <stdio.h>
void printsample();
void readGame();
void printGrid();
int stopSave(int grid[], int mistakes);
void displayBoard(int grid[]);
void getNumbers(int grid[]);
int legalMove(int grid[], int position);
int correctMove(int grid[], int number, int postion);
void writeGame(int grid[], int mistakes);
int puzzleSolved(int grid[], int mistakes);
void red();
void blue();
void green();
void reset();

int main(void) {
  int mistakes = 0;
  int grid[81];
  printGrid();
  readGame(grid);
  displayBoard(grid);
  // stopSave(grid);
  // if(!stopSave(grid)){
    getNumbers(grid);
  
  // }

  return 0;
}

void printGrid() {
  int i, j;
  int k = 1;
  blue();
  printf(" \n\nHere is the sample grid indicating the positions you can play:  "
         "\n\n");
  reset();

  for (i = 1; i <= 9; i++) { // for each of nine lines in the grid
    for (j = 0; j < 46; j++) {
      printf("-"); // print the separating lines
    }
    printf("\n|");
    for (j = k; j <= i * 9; j++) { // print the numberrs starting from k = 1
      printf(" %-2d |", j);
      k = j + 1; //  increment k to start from 1 + the final j value
    }
    printf("\n");
  }
  for (j = 0; j < 46; j++) {
    printf("-");
  }
}

void displayBoard(int grid[]) {
  int j, l, position;
  blue();
  printf("\n\n \nYour current Sudoku game game grid:\n\n \n\n");
  reset();
  for (l = 1; l <= 81; l++) {
    if (l % 9 == 0) {
      if (grid[l - 1] == 0) {
        printf("\t\n");
      } else {
        printf("\t%d\n", grid[l - 1]);
      }
    } else if (l % 3 == 0) {
      printf("");
      if (grid[l - 1] == 0) {
        printf("\t  |");
      } else {
        printf("\t%d |", grid[l - 1]);
      }
    } else if (l == 28 || l == 55) {
      for (j = 0; j < 40; j++) {
        printf("-");
      }
      printf("\n");
      if (grid[l - 1] == 0) {
        printf("\t");
      } else {
        printf("\t%d", grid[l - 1]);
      }

    } else {
      if (grid[l - 1] == 0) {
        printf("\t ");
      } else if (l == position) {
        green();
        printf("%d", grid[position - 1]);
      } else {
        printf("\t%d", grid[l - 1]);
      }
    }
  }
}
// legal move function;
int legalMove(int grid[], int position) { // checking whether the area doesnot
                                          // have a number filled with it
  if (grid[position - 1] == 0) {
    return 1;
  }
  return 0;
}

int correctMove(int grid[], int number, int position) {
  int i, j, k, l;
  // checking column
  for (i = 0; i < 9; i++) {
    int newlocation = ((position - 1) % 9) + (9 * i);
    if (grid[newlocation] == number) {
      return 0;
    }
  }

  // checking row

  for (i = ((position - 1) / 9) * 9; i < (((position - 1) / 9) + 1) * 9; i++) {
    if (grid[i] == number) {
      return 0;
    }
  }

  int squarelocation = 0;
  int newsquarelocation =
      (((position - 1) / 27) * 3) + (((position - 1) % 27) % 9) / 3;

  for (i = 0; i < 9; i++) {
    squarelocation = (27 * (newsquarelocation / 3)) +
                     ((newsquarelocation % 3) * 3) + ((i / 3) * 6) + i;
    if (grid[squarelocation] == number) {
      return 0;
    }
  }
  return 1;
}

void getNumbers(int grid[]) {
  int mistakes= 0;
  int position, number, i;
  int attemps = 4;
  green();
  printf("\nValid Postions are 1-81\n\nAt what position do wanna play:  ");
  reset();
  scanf("%d", &position);
  green();
  printf("\nThe numbers to be played are between 1 and 9\n \nWhat number do "
         "you wanna play:   ");
  reset();
  scanf("%d", &number);
  if(position>81){
    green();
  printf("Please enter a valid postion");
    reset();
    getNumbers(grid);
  } else{
  if (legalMove(grid, position)) {
    if (correctMove(grid, number, position)) {
      // printf("%d", grid);
      grid[position - 1] = number;
      displayBoard(grid);
      writeGame(grid, mistakes);
      printf("\nThat was a nice Move!!!\n");
      if(!stopSave(grid, mistakes)){
        getNumbers(grid);
      }
    } else {
      red();
      printf("\n\nThe number you selected is in either the row, colum, or "
             "square in the grid Please try again\n");
      reset();
      mistakes++;
      printf("\nYou have made %d mistakes so far. You are remaining with only "
             "%d wrong attemps\n \n Let's play again! \n",
             mistakes, --attemps);
      getNumbers(grid);
    }
  } else {
    red();
    printf(
        "The position selected has another number in it. Please try again \n");
    reset();
    mistakes++;
    printf("\nYou have made %d mistakes so far. You are remaining with only %d "
           "wrong attemps\n",
           mistakes, --attemps);
    getNumbers(grid);
  }
}
  }

void writeGame(int grid[], int mistakes) {
  int i;
  FILE *savefile;
  savefile = fopen("SudokuSave.txt", "w");
  for (i = 0; i < 81; i++) {
    fprintf(savefile, "%d", grid[i]);
  }
  fprintf(savefile, "%d", mistakes);
  fclose(savefile);
}

int puzzleSolved(int grid[], int mistakes) {
  int i;
  for (i = 0; i <= 81; i++) {
    if (grid[i] == 0) {
      return 0;
    } else if(mistakes>3){
      return 0;
    }
  }
  return 1;
}

void readGame(int grid[]) {
  int i;
  FILE *ifile;
  ifile = fopen("sudoku.txt", "r");
  if (ifile != NULL) {
    while(fscanf(ifile, "%d", &grid[i - 1]) != EOF){
    for (i = 1; i <= 81; i++) {
      fscanf(ifile, "%d", &grid[i]);
    }
      }
  } else {
    printf("Invalid file!");
  }
  fclose(ifile);
}

void red() { printf("\033[1;31m"); }

void blue() { printf("\033[0;34m"); }

void green() { printf("\033[0;32m"); }

void reset() { printf("\033[0m"); }


int stopSave(int grid[], int mistakes) {
  int check;
  printf("Do you want to suspend a game, and save it? if so, press -1 else, press another number..    ");
  scanf("%d", &check);
  if (check == -1) {
    writeGame(grid, mistakes);
    return 1;
  }
  return 0;
}
