//1806ICT - Programming Principles
// Assignment Milestone Part 2
//Brendon Rauch
//S5266588

#include <stdbool.h>
#include <math.h>   //used got math equations
#include <stdlib.h>
#include <string.h>
#include <time.h>   //used in srand as seed time
#include <stdio.h>  //standard input / output library

#define _USE_MATH_DEFINES //tells to use math defines
#define PLUS '+'
#define MINUS '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define MOD '%'
#define ZERO 0

int size = 0;      //number of digits in the equation
int MIN_VALUE = 0; //minimum number
int MAX_VALUE = 0; //maximum number

struct Login
{
  char fname[15];
  char username[15];
  char password[15];

};
enum 
{
  LOGGED_OUT,
  LOGGED_IN,
  EXIT
};

void random(int **board, int bgsize);     // prototype matrix for random numbers;
void cal_solution(int **board, int bgsize); //prototype for calculating the equation
void cal_user(int **board, int bgsize); //prototype for calculating the equation
void printgame (int **game, int bgsize);
void inputEntry ( int **game, int *add, int *delete, int *hint, int **board, int inputval );
void copyboard(int **board, int **game, int bgsize);
void startgame(int **game, int **board, int bgsize, int *hint);
void time_taken(int start_time, int *tt);
void end_game(int **game, int bgsize, int *end);
void rhint(int **game, int ** board, int bgsize, int *ri, int *rj);
int login();
void registration();
void convert_menu(int **board, int bgsize);
int convert(int number, int base);
int menu ();
void finalscore(int *score, int *tt, int *count, int *hint, int *delete,int *ctt);
void printscore();
int playgame(int *base);
void convert_board(int **board, int bgsize, int base);
void savegame(int **game, int bgsize, int **board, int *score, int *tt, int *count, int *hint, int *delete, int *MAX_VALUE, int *MIN_VALUE, int *size, int *add);
void loadgame();
int loginmenu();
int continuegame(int **game, int bgsize, int **board, int score, int tt, int count, int hint, int MAX_VALUE, int MIN_VALUE, int size, int delete, int add);

int main(void)
{
int user_state = LOGGED_OUT;
  while ( user_state != EXIT )
  {
    if ( user_state == LOGGED_OUT)
    {// user is NOT logged in, handle main menu 
      user_state = loginmenu();
    }
    else
    {// user is logged in, handle sub menu
      user_state = menu();
    }
  }
  return 0;
}

int loginmenu()
{
  int choice;
  while ( 1 )
  {
    printf("Welcome the Mathematical Crossword Login Screen!!!\n");
    printf("\n");
    printf("\n1 : register!!!\n");
    printf("2 : login!!!\n");
	printf("3 : quit\n");
    printf("Enter your choice : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        registration();
        break;
      case 2:
        if ( login())
          return LOGGED_IN;
        break;
	  case 3:
        printf("Thank you for playing!! \n");
        return EXIT;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
} 
int playgame(int *base)
{ int count=0, add=0, delete=0, score=0, hint = 0, difficulty, inputval, tt=0, end=0, ctt=0;
		srand((unsigned)time(NULL)); //sets the seed for the random function to increase randomness
    	printf("Welcome to the Mathematical Crossword Game.\nPlease Enter the amount of numbers in the equation: ");
    	scanf("%d", &size); //sets the number of digits in the equation
    	printf("Please enter minimum number (Above 2): ");
		scanf("%d", &MIN_VALUE); //sets the minimum value
		while (MIN_VALUE <=1)//sets the minimum value
			{
			printf("Invalid Number. Please try again\n");
			printf("Please enter minimum number (Above 2): ");
			scanf("%d", &MIN_VALUE);
			} 
    printf("Please enter maximum number: ");
    scanf("%d", &MAX_VALUE); //sets the maximum value
		while (MAX_VALUE < MIN_VALUE)
			{
			printf("Invalid Number. Please try again\n");
			printf("Please enter maximum number: ");
    		scanf("%d", &MAX_VALUE);
			}

	int bgsize = 2 * size + 1; // Allow for operators and totals
 	int **board; // The solution board
// Allocate memory
 	board = (int **) malloc(sizeof(int *) * bgsize);
 		for (int i = 0; i < bgsize; i++) // Allocate rows
  			board[i] = (int *) malloc(sizeof(int) * bgsize);
	int **game; // The game board
// Allocate memory
	game = (int **) malloc(sizeof(int *) * bgsize);	
		for (int i = 0; i < bgsize; i++) // Allocate rows
    		game[i] = (int *) malloc(sizeof(int) * bgsize);
	
	time_t start_time = time(0); // starts the timer for time taken
    random(board, bgsize); // generates random numbers and operators
	
	cal_solution(board, bgsize); // calculates the solution board
	
//	convert_base(board, bgsize, base);
	convert_board(board,bgsize, base);
	copyboard(board, game, bgsize); // copies solution board to game board
	difficulty= (MAX_VALUE-MIN_VALUE)*size; // calculated the difficulty level
	printf("Difficulty = %d\n",difficulty); //prints the difficutly to screen
	//convert_base(board, bgsize, base);
	startgame(game, board, bgsize, &hint); 
	printgame(game, bgsize); //prints gameboard// sets game board user cells to 1 and starts game
while (end != 1) // runs loop until game is complete or user quits
{
	printf("Press 1 to add or delete entry\nPress 2 for a HINT\nPress 3 to SAVE game\nPress 0 to Quit\nSelection: "); //user inputs the selection
	scanf("%d", &inputval);
	if (inputval ==0)
		{printf("Sorry your leaving\n");
		break;
		}
	 else if (inputval ==1)
	inputEntry(game, &add, &delete, &hint, board, inputval);
	else if (inputval ==2)
	inputEntry(game, &add, &delete, &hint, board, inputval);
		else if (inputval == 3)
		savegame(game, bgsize, board, score, tt, count, hint, delete, MAX_VALUE, MIN_VALUE, size, add);
	else
	printf("Invalid entry location. No change.\n");

		cal_user(game, bgsize); //updates user total calculations
		printgame(game, bgsize); // prints updated board
		time_taken(start_time, &tt); // updates the time taken
		count++; //adds 1 to move counter
		printf("Move Counter = %d\n", count); // prints move counter
		score = (add-delete-hint+difficulty)*100; // calculates running score
		printf("Score = %d\n", score); // prints running score
		end_game(game, bgsize, &end); 

}
	finalscore(score, tt, count, hint, delete, difficulty);
	for (int i = 0; i < bgsize; i++) 
    	free(board[i]);
 		free(board);
// Free Game rows	
	for (int i = 0; i < bgsize; i++)
   	free(game[i]);
	free(game);
}
	
int continuegame(int **game, int bgsize, int **board, int score, int tt, int count, int hint, int MAX_VALUE, int MIN_VALUE, int size, int delete, int add)
{
	
	int difficulty, end=0, inputval, ctt;

	time_t start_time = time(0);
	difficulty= (MAX_VALUE-MIN_VALUE)*size;
	printf("Difficulty = %d\n",difficulty);
	printgame(game, bgsize); //prints gameboard
	while (end != 1) // runs loop until game is complete or user quits
{
	printf("Press 1 to add or delete entry\nPress 2 for a HINT\nPress 3 to SAVE game\nPress 0 to Quit\nSelection: "); //user inputs the selection
	scanf("%d", &inputval);
	if (inputval ==0)
		{printf("Sorry your leaving\n");
		break;
		}
	 else if (inputval ==1)
	inputEntry(game, &add, &delete, &hint, board, inputval);
	else if (inputval ==2)
	inputEntry(game, &add, &delete, &hint, board, inputval);
		else if (inputval == 3)
		savegame(game, bgsize, board, score, tt, count, hint, delete, MAX_VALUE, MIN_VALUE, size, add);
	else
	printf("Invalid entry location. No change.\n");

		cal_user(game, bgsize); //updates user total calculations
		printgame(game, bgsize); // prints updated board
		time_taken(start_time, &tt); // updates the time taken
		count++; //adds 1 to move counter
		printf("Move Counter = %d\n", count); // prints move counter
		score = (add-delete-hint+difficulty)*100; // calculates running score
		printf("Score = %d\n", score); // prints running score
		end_game(game, bgsize, &end); 

}
	finalscore(score, tt, count, hint, delete, difficulty);
	
// Free Game rows	
	for (int i = 0; i < bgsize; i++)
   	free(game[i]);
	free(game);
	menu();
}
void loadgame()
{
	  FILE *log;    
int val, i=0, j=0, bgsize, score, ctt, count, hint, delete, MAX_VALUE, MIN_VALUE, size, add;
     log=fopen("save.txt","r");
     fscanf(log, "%d", &bgsize);
		//printf("%d\n", bgsize);
	int **game; // The game board
// Allocate memory
 	game = (int **) malloc(sizeof(int *) * bgsize);
 		for (int i = 0; i < bgsize; i++) // Allocate rows
  			game[i] = (int *) malloc(sizeof(int) * bgsize);
   {
		for (i=0; i<bgsize; i++)
		{
			for (j=0; j<bgsize; j++)
			{
				fscanf(log, "%d", &val);
				game[i][j]=	val;
				//printf("%d ", game[i][j]);
			}
			printf("\n");
	 	}
	}
	int **board; // The game board
// Allocate memory
 	board = (int **) malloc(sizeof(int *) * bgsize);
 		for (int i = 0; i < bgsize; i++) // Allocate rows
  			board[i] = (int *) malloc(sizeof(int) * bgsize);
   {
		for (i=0; i<bgsize; i++)
		{
			for (j=0; j<bgsize; j++)
			{
				fscanf(log, "%d", &val);
				board[i][j]=	val;
			//	printf("%d ", board[i][j]);
			}
			printf("\n");
	 	}
	}

	fscanf(log, "%d", &score);
	fscanf(log, "%d", &ctt);
	fscanf(log, "%d", &count);
	fscanf(log, "%d", &hint);
	fscanf(log, "%d", &delete );
	fscanf(log, "%d", &MAX_VALUE);
	fscanf(log, "%d", &MIN_VALUE);
	fscanf(log, "%d", &size);
	fscanf(log, "%d", &add);
	
 	fclose(log);
	
	
	printgame(game, bgsize);
	continuegame(game, bgsize, score, ctt, count, hint, delete, MAX_VALUE, MIN_VALUE, size, add);	

	}

void savegame(int **game, int bgsize, int **board, int score, int tt, int count, int hint, int delete, int MAX_VALUE, int MIN_VALUE, int size, int add)
{
	  FILE *log;    

     log=fopen("save.txt","wb+");
     fprintf(log, "%d\n", bgsize);
   for (int i=0; i<bgsize; i++)
	{
	for (int j=0; j<bgsize; j++)
		{
		fprintf(log, "%d ", game[i][j]);
		}
	fprintf(log, "\n");
	 }

	  for (int i=0; i<bgsize; i++)
		{
		for (int j=0; j<bgsize; j++)
			{
			fprintf(log, "%d ", board[i][j]);
			}
		fprintf(log, "\n");
		 }
	
	fprintf(log, "%d\n", score);
	fprintf(log, "%d\n", tt);
	fprintf(log, "%d\n", count);
	fprintf(log, "%d\n", hint);
	fprintf(log, "%d\n", delete);
	fprintf(log, "%d\n", MAX_VALUE);
	fprintf(log, "%d\n", MIN_VALUE);
	fprintf(log, "%d\n", size);
	fprintf(log, "%d\n", add);
 	fclose(log);
	}

void printscore()
{
	int read =0;
	char buffer[500];
	FILE *log = fopen("scores.txt", "rb");
	 if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
   
  }printf("Difficulty   Score	     Name\n");
	while (fgets(buffer, 500, log) !=NULL)
	{read = strlen(buffer);
	buffer[read-1]=buffer[read-1] == '\n' ? '\0' : buffer[read-1];
	printf("%s\n", buffer);
}
	fclose(log);
	}

void finalscore(int *score, int *tt, int *count, int *hint, int *delete, int *difficulty, int *ctt)
{
	int buffer[50], finalscore, diff, ftt, continuetime, fscore;
	char name[15];
	
	FILE *log = fopen("scores.txt", "a+");
	 if (log == NULL)
  {sprintf("Difficulty %10 Score %15 Name");
   }
	printf("Please enter your name: ");
	scanf("%15s", name);
	continuetime= ctt;
	fscore = score;
	ftt = tt+ continuetime;	
	finalscore = fscore * ftt; 
	diff=difficulty;
	//calculates final score
	sprintf(buffer, "%d %10d %15s\n", difficulty, finalscore, name, ); 
	fwrite(buffer, 1, strlen(buffer), log);
	
	printf("Congratulations %s!! \n_______________\nYour Final Score = %d\nMoves Taken = %d\nMoves Deleted = %d\nHints Used = %d\n", name, finalscore, count, delete, hint);
	fclose(log);
	}
int menu()
{ 
	int menuoption;
	{//while (1)
	printf("Welcome to the Mathematical Crossword Game.\n"
			"\nPlease Select an option.\n"
			"1. Play Game \n"
			"2. Load a Saved Game\n"
			"3. Display Scores\n"
			"4. Exit to Login\n"
			"Selection: ");
	if (scanf("%d", &menuoption)==1);
	{
		switch (menuoption)
		{
			case 1:
				convert_menu();
				break;
			case 2:
				loadgame();
				continuegame();
				break;
				
			case 3:
				printf("\nCurrent Scores are: \n");
				printscore();
				printf("\n\n");
				break;
			case 4:
        		return LOGGED_OUT;
      		default:
      			  printf("Please enter a valid choice!!\n");
      			  break;
		}
	}
}
	return LOGGED_IN;
	}
void registration()
{
  FILE *log = fopen("login.txt", "a+");
  struct Login l;
  printf("\nEnter first name : ");
  scanf("%s", (l.fname));
  printf("\nEnter your Username : ");
  scanf("%s", l.username);
  printf("\nEnter your password : ");
  scanf("%s", l.password);
  fwrite(&l, sizeof(struct Login), 1, log);
  fclose(log);
  printf("\nYou are successfully registered!!");
  printf("\nYour UserId is %s", l.username);
  printf("\nNow login with your username and password!!\n\n");
}

int login()
{
  FILE *log = fopen("login.txt", "rb");
  struct Login linput, lfile;
 
  if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
    return 0; // login failed
  }
  printf("\nUserID : ");
  scanf("%s", linput.username);
  printf("\nPassword : ");
  scanf("%s", linput.password);
  while ( fread(&lfile, sizeof(struct Login), 1, log)  )
  {
    if (strcmp(linput.username, lfile.username) == 0 && strcmp(linput.password, lfile.password)==0)
    {
      printf("\nYou are successfully logged in !!\n");
      fclose(log);
      return 1; // login succeeded
    }
  }
  printf("\nYour UserID or password is incorrect !!\n");
  registration();
  fclose(log);
  return 0; // login failed
}

void convert_menu(int **board, int bgsize)
{
    int num, choice, base;
    {
        printf("Select conversion: \n\n"
        "1. Decimal.\n" 
		"2. Binary. \n"
        "3. Octal. \n"
        "4. Hexadecimal. \n"              
		"5. Return to Main Menu.\n"
        "\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
			case 1:
				break;
            case 2:
                base = 2;
                break;
            case 3:
                base = 8;
                break;              
            case 4:
                base = 16;
                break;
			case 5:
				menu();
				break;
            default:
                printf("Invalid choice.\n\n");
               
        }

        playgame(base);

        printf("\n\n");
    }
}
void convert_board(int **board, int bgsize,int base)
{
	int number, converted;
	for (int i=0; i<bgsize; i++)
	for (int j=0; j<bgsize; j++)
	{i=number;
	convert(number, base);
		board[i][j] = number;}
		
}
int convert(int number, int base)
{ 
	if(number == 0 || base==10)
        return number;
    return (number % base) + 10*convert(number / base, base);
}
	
void rhint(int **game,int **board, int bgsize, int *ri, int *rj)// generates random hint
{
	int m= bgsize-3;
	*ri=0;
	*rj=0;
	*ri= 2*( rand() % m);
	*rj= 2*( rand() % m);
	while (*ri>m || *rj>m)
		{
		*ri= 2*( rand() % m);
		*rj= 2*( rand() % m);
		}
}

void end_game(int **game, int bgsize, int *end)
{
	int comp_row, comp_col;
	bool col_total = false;
	bool row_total = false;

	for (int i=0; i<bgsize-2; i+=2)
		for (int j=bgsize-2; j<bgsize; j++)
			{
			if (comp_row == game[i][j])
				row_total= true;
			else row_total=false;
			comp_row=game[i][j];
			}
	for (int j=0; j<bgsize-1; j+=2)
		{
		for (int i=bgsize-2; i<bgsize; i++)
			{
			if (comp_col == game[i][j])
			col_total= true;
			else col_total=false;
			comp_col=game[i][j];
			}
		}
	if (col_total && row_total == true)
		*end=1;
}

void time_taken(int start_time, int *tt)
{
	int sec_taken, h,m,s;
	time_t end_time = time(0);
	sec_taken =end_time-start_time;
	h=(sec_taken/3600);
	m=(sec_taken-(3600*h))/60;
	s=(sec_taken-(3600*h)-(m*60));
	printf("Time Taken = %d:%d:%d\n", h,m,s );
	*tt +=sec_taken;
}

void random(int **board, int bgsize)
{
    int  row, col, op, rnumb,sum = 0;
    for (row = 0; row < bgsize; row++)
    	{
        for (col = 0; col < bgsize; col++)
			{
            if (row % 2 == 0 && col % 2 == 0)
            	{
                rnumb = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE; //generates random number within the range given
                board[row][col] = rnumb;
                }
            else if ((row % 2 == 1 && col % 2 == 1))
                   board[row][col] = 0;
			else
            {
                op = rand() % 5 + 1; //generates a random number between 1 and 4
                switch (op)          //switched number in op with math operator
                {
                case 1:
                    op = '+';
                    break;
                case 2:
                    op = '-';
                    break;
                case 3:
                    op = '*';
                    break;
                case 4:
                    op = '/';
                    break;
				case 5:
                    op = '%';
                    break;
                }
                board[row][col] = op;
            }
		}
    }
}
void cal_solution(int **board, int bgsize)
{
		int row,col,sum = 0;
		// finding the row sum
		for (row = 0; row < bgsize-2; row+=2) 
			{
			for (col = 0; col < bgsize-2; col+=2) 
				{
			// Add the element
				if (col == 0)
					sum= sum + board[row][col];
				else if (board[row][col-1] == MINUS)
					sum = sum - board[row][col];
				else if(board[row][col-1] == DIVIDE)
					sum = sum / board[row][col];
				else if (board[row][col-1] == MULTIPLY)
					sum = sum * board[row][col];
				else if (board[row][col-1] == MOD)
					sum = sum % board[row][col];
				else
					sum= sum + board[row][col];
				}
			board[row][bgsize-1]=sum;

		// Reset the sum
			sum = 0;
			}
    // finding the col sum
    for (col= 0; col < bgsize-2; col+=2) 
		{
		sum=board[0][col];
        for (row = 2; row < bgsize-2; row+=2) 
			{
            // Add the element
            if (board[row-1][col] == MINUS)
                sum = sum - board[row][col];
            else if(board[row-1][col] == DIVIDE)
                sum = sum / board[row][col];
            else if (board[row-1][col] == MULTIPLY)
                sum = sum * board[row][col];
			else if (board[row-1][col] == MOD)
					sum = sum % board[row][col];
            else
                sum= sum + board[row][col];
        	}

        board[bgsize-1][col]=sum;

        // Reset the sum
        sum = 0;
    	}
}

// Function to calculate sum of user total
void cal_user(int **board, int bgsize)
{
	int row,col,sum = 0;
		// finding the row sum
	for (row = 0; row < bgsize-2; row+=2) 
		{
		for (col = 0; col < bgsize-2; col+=2) 
			{
			// Add the element
			if (col == 0)
				sum= sum + board[row][col];
			else if (board[row][col-1] == MINUS)
				sum = sum - board[row][col];
			else if(board[row][col-1] == DIVIDE)
				sum = sum / board[row][col];
			else if (board[row][col-1] == MULTIPLY)
				sum = sum * board[row][col];
			else if (board[row][col-1] == MOD)
					sum = sum % board[row][col];
			else
				sum= sum + board[row][col];
			}
		board[row][bgsize-2]=sum;
		// Reset the sum
		sum = 0;
		}
    // finding the col sum
    for (col= 0; col < bgsize-2; col+=2) 
		{
		sum=board[0][col];
        for (row = 2; row < bgsize-2; row+=2) 
			{
            // Add the element
            if (board[row-1][col] == MINUS)
                sum = sum - board[row][col];
            else if(board[row-1][col] == DIVIDE)
                sum = sum / board[row][col];
            else if (board[row-1][col] == MULTIPLY)
                sum = sum * board[row][col];
			else if (board[row-1][col] == MOD)
					sum = sum % board[row][col];
            else
                sum= sum + board[row][col];
        	}
        board[bgsize-2][col]=sum;
        // Reset the sum
        sum = 0;
    	}	
}

void inputEntry ( int **game, int *add, int *delete, int *hint, int **board, int inputval )
{
	int row, column;
	if (inputval==1)
		{
		printf("Enter row and column number: ");
		scanf("%d %d", &row, &column);

			if (row % 2 == 0 && column % 2 == 0)
				{
				if (game[row][column] != 1)
					{
					(*delete)++;
					printf("Entry Deleted ");
					game[row][column]= 1;
					}	
				else
					{
					(*add)++;
					printf("Enter value: ");
					scanf("%d", &game[row][column]);
					}
				}
			else 
				{
				printf("Invalid entry location. No change.\n");
				}
		}
	else if (inputval==2)
		{
		(*hint)++;
		printf("Enter row and column number: ");
		scanf("%d %d", &row, &column);
		game[row][column]=board[row][column];
		}
	else
		printf("Invalid entry. No change.\n");
}

void copyboard(int **board, int **game, int bgsize)
{
	int i, j;
    for(int i=0;i<bgsize;i++)     //Print Matrix
	   {
        for(int j=0;j<bgsize;j++)
			game[i][j] = board[i][j];
	   }
}

void startgame (int **game, int **board, int bgsize, int *hint)
{
	int ri=0, rj=0, hintsize;

		printf("How many numbers would you like to start with: ");
		scanf("%d", &hintsize);
		*hint = hintsize;
		for(int i=0;i<bgsize;i++)     //Print Matrix
			for(int j=0;j<bgsize;j++)
				if ( i % 2 == 0 && j % 2 == 0 || i==bgsize-2 || j==bgsize-2)
            		{
					if (i==bgsize-1 || j==bgsize-1)
						game[i][j] = board[i][j];
					else
						game[i][j] = 1;
        			}
		for (int i=0; i<bgsize; i++)
			for (int j=0; j<bgsize; j++)
				while (hintsize >=0)
					{
					rhint(game, board, bgsize, &ri, &rj);
					if (game[ri][rj]!=1)
						rhint(game, board, bgsize, &ri, &rj);
					else
						game[ri][rj]=board[ri][rj];
						hintsize--;
					}

}

void printgame (int **game, int bgsize)
{
	int i, j,k,l;
	printf("\nElements in the matrix are \n");
	for(int i=0;i<bgsize;i++) 
		if (i==bgsize-1)
			printf("   T");
		else if (i==bgsize-2)
			printf("   U");
		else
					{
		if (i==0)
			printf("      %d", i);
		else if (i<=9)
			printf("   %d", i);
		else
			printf("  %d", i);
			}
		printf("\n");
	{
	for(int i=0;i<bgsize;i++) 
		{
		if (i==0)
			printf("  +---");
		else
     	 	 printf("----");
		}
		printf("\n");
	}
	for(int i=0;i<bgsize;i++)     //Print Matrix
	{
		if (i<bgsize-2)
		{
			if (i<=9)
				printf("%d |",i);
	    	else
				printf("%d|",i);
		}
		else if (i==bgsize-2)
			printf("U |");
		else printf("T |");for(int j=0;j<bgsize;j++)
		{
			{	
			if (i == bgsize-1 || j==bgsize-1)
				{
				if (i==bgsize-1 && j==bgsize-1)
					printf("   ");
				else if (i % 2 == 0 && j % 2 == 0)
           		 	printf("%4d",game[i][j]);
				else
					printf("    ");
			    }
			else if (i == bgsize-2 || j==bgsize-2)
				{
				if (i % 2 == 1 && j % 2 == 1)
           	 		printf("    ");
				else
					printf("%4d",game[i][j]);
				}
			else if (i % 2 == 0 && j % 2 == 0)
           			printf("%4d",game[i][j]);
			else if (i%2==1 && j%2==1)
					printf("    ");
			else
				printf ("%4c", game[i][j]);
               }
		}
        printf("\n");
 	}  
}