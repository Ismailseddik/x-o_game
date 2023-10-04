#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#pragma warning(disable : 4996)
typedef unsigned char uint8_t;

uint8_t GameBoard[9] = { '1','2','3','4','5','6','7','8','9' };
uint8_t SymbolArray[2]={'X','O'};
uint8_t playerSymbol;
uint8_t configArray[2];
int flag = 0;

void drawBoard(uint8_t* board) {

	printf(" %c | %c | %c ", board[0], board[1], board[2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[3], board[4], board[5]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[6], board[7], board[8]);
	printf("\n");

}
void updateBoard(uint8_t* board,uint8_t position, uint8_t Value)
{
	board[position - 1] = Value;
}
uint8_t getPlayerSymbol(uint8_t PlayerNumber, uint8_t* symbol)
{

	if (playerSymbol == symbol[0] || playerSymbol == symbol[1])
	{
		return 0;
	}
	else if (configArray[0] == configArray[1])
	{
		printf("wrong symbol please choose the other symbol\n");
		return 1;

	}

	return -1;
}
void setPlayerConfig(uint8_t* configArray)
{
	int counter = 0;
	char playersymbol = 0;
	printf("welcome to the game player 1 please choose your symbol for X press x for O press o\n" );
	scanf("%c", &playersymbol);
	if (playersymbol == 'x') {
		configArray[0] = 'X';
		configArray[1] = 'O';
	}
	else if(playersymbol == 'o') {
		configArray[0] = 'O';
		configArray[1] = 'X';
	}
	else {
		printf("wrong character please enter X or O");
		exit(1);
	}
	int result = getPlayerSymbol(configArray, &SymbolArray);
	if (result == 1) {
		printf("error\n");
		exit(1);
	}

}


void loadAndUpdate(uint8_t PlayerNumber)
{
	int pos = 1;
	printf("player number %d please enter a position with symbol %c\n", PlayerNumber,configArray[PlayerNumber-1]);
	scanf("%d", &pos);
	char symbol = configArray[PlayerNumber - 1];
	if (pos < 1 || pos>9) {
		printf("invalid input\n");
	}
	if (GameBoard[pos - 1] == 'X' || GameBoard[pos - 1] == 'O') {
		printf("invalid input\n");
	}
	else {
		updateBoard(&GameBoard,pos, symbol);
	}
	updateBoard(&GameBoard,pos, configArray[PlayerNumber - 1]);

}
void getGameState(uint8_t* board, uint8_t* gameState)
{
	//checking rows

	if (board[0] == board[1] && board[1] == board[2]) {
		*gameState = 0;
	}
	if (board[3] == board[4] && board[4] == board[5]) {
		*gameState = 0;
	}
	if (board[6] == board[7] && board[7] == board[8]) {
		*gameState = 0;
	}

	//chech coloumns

	if (board[0] == board[3] && board[3] == board[6]) {
		*gameState = 0;
	}
	if (board[1] == board[4] && board[4] == board[7]) {
		*gameState = 0;
	}
	if (board[2] == board[5] && board[5] == board[8]) {
		*gameState = 0;
	}

	//chech diagonals

	if (board[0] == board[4] && board[4] == board[8]) {
		*gameState = 0;
	}


	if (board[6] == board[4] && board[4] == board[2]) {
		*gameState = 0;
	}
	//check draw
	int counter = 0;
	for (int i = 0; i < 9; i++) {
		if (board[i] == 'X' || board[i] == 'O')
		{
			counter++;
		}
		if (counter == 9) {
			*gameState = 1;
		}
	}


}
int main()
{
	int player = 1;
	int loop = -1;
	char status = ' ';
	setPlayerConfig(configArray);
	if (flag == -1) {
		setPlayerConfig(configArray);
		
	}
	drawBoard(GameBoard);
	while (loop == -1) {
		if (player % 2 == 0) {
			player = 2;
		}
		else {
			player = 1;
		}
		loadAndUpdate(player);
		drawBoard(GameBoard);

	    getGameState(GameBoard,&status);
		if (status == 0) {
			printf("winner is player number %d\n", player);
			break;
		}
		else if (status == 1) {
			printf("draw\n");
			break;
		}
		player++;
	}



}
