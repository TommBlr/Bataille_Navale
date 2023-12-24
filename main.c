#include "nb.h"

int main(){
	//Init random generator
	srand(time(NULL));

	//Locals
	Player player1;
	Player player2;
	int* sizeBoats;
	Game game;
	int endOfGame = 0;
	int round = 1;

	//Allocate
	sizeBoats = malloc(sizeof(int)*NBBOATS);

	//Generate random sizes for boats
	for (int i = 0; i < NBBOATS; i++){
		sizeBoats[i] = 2 + rand()%4;
	}

	//Main
	//Create Players
	player1 = initPlayer(sizeBoats);
	player2 = initPlayer(sizeBoats);

	//Create Board and setup the game
	game = initGame(player1, player2);
	printf("\nYour Board :\n\n");
	displayBoard(game.boatP1);
	printf("\n\n");

	//Play the game
	while (!endOfGame){
		printf("|---------------ROUND %d---------------|\n\n", round);
		game = gameRound(game);
		printf("\n\nYour board :\n\n");
		displayBoard(game.boatP1);
		printf("\n\nP2 Lane :\n\n");
		displayBoard(game.boardP1);
		printf("\n\n");
			
		player1 = testPlayerBoats(player1, game.boatP1);
		player2 = testPlayerBoats(player2, game.boatP2);

		switch (testGame(player1, player2)){
			case 1:
				printf("Player 1 won !\n");
				endOfGame = 1;
				break;
			case 2:
				printf("Player 2 won !\n");
				endOfGame = 1;
				break;
		}
		round++;
	}
	
	//Free allocated space
	//Players
	free(player1.boats);
	free(player2.boats);
	free(player1.stateBoats);
	free(player2.stateBoats);
	free(sizeBoats);

	//Boards
	for (int i = 0; i < BOARD_SIZE; i++){
		free(game.boardP1[i]);
		free(game.boardP2[i]);
		free(game.boatP1[i]);
		free(game.boatP2[i]);
	}
	free(game.boardP1);
	free(game.boardP2);
	free(game.boatP1);
	free(game.boatP2);

	return(0);	
}
