#include "nb.h"

/**
 * @brief Initializes a boat with the given size.
 * 
 * @param size The size of the boat to be initialized.
 * @return A Boat structure representing the initialized boat.
 */
Boat initBoat(int size) {
    // Locals
    Boat currentBoat;

    // Check Params
    if (size <= 0) {
        exit(1);
    }

    // Init the boat structure
    currentBoat.size = size;
    currentBoat.x;
    currentBoat.y;
    currentBoat.dir = rand() % 2;

    return (currentBoat);
}

/**
 * @brief Initializes a player with the specified boat sizes.
 * 
 * @param sizeBoats An array representing the sizes of boats for the player.
 * @return A Player structure representing the initialized player.
 */
Player initPlayer(int* sizeBoats) {
    // Locals
    Player currentPlayer;

    // Allocate Structure
    currentPlayer.boats = malloc(sizeof(Boat) * NBBOATS);
    currentPlayer.stateBoats = malloc(sizeof(int) * NBBOATS);

    // Init the Player structure
    for (int i = 0; i < NBBOATS; i++) {
        currentPlayer.boats[i] = initBoat(sizeBoats[i]);
        currentPlayer.stateBoats[i] = 1;
    }

    return (currentPlayer);
}

/**
 * @brief Tests if a boat can be placed on the specified board.
 * 
 * @param boat The boat to be tested.
 * @param board The game board.
 * @return 1 if the boat can be placed, 0 otherwise.
 */
int testBoat(Boat boat, int** board) {
    // Local
    int currentX;
    int currentY;

    // Check state of the boat
    currentX = boat.x;
    currentY = boat.y;
    for (int i = 0; i < boat.size; i++) {
        if (board[currentY][currentX] != WRECK) {
            return (1);
        } else if (boat.dir == NORTH) {
            currentY++;
        } else {
            currentX++;
        }
    }
    return (0);
}

/**
 * @brief Tests if the size of a boat is valid for placement on the specified board.
 * 
 * @param boat The boat to be tested.
 * @param board The game board.
 * @return 1 if the size of the boat is valid, 0 otherwise.
 */
int testSizeBoat(Boat boat, int** board) {
    // Local
    int currentX;
    int currentY;

    // Check if there is enough for a boat to be set up
    currentX = boat.x;
    currentY = boat.y;

    for (int i = 0; i < boat.size; i++) {
        if (board[currentY][currentX] != WATER) {
            return (1);
        } else if (boat.dir == NORTH) {
            currentY++;
        } else {
            currentX++;
        }
    }
    return (0);
}

/**
 * @brief Initializes the game with the specified players.
 * 
 * @param p1 Player 1.
 * @param p2 Player 2.
 * @return A Game structure representing the initialized game.
 */
Game initGame(Player p1, Player p2) {
    // Local
    Game currentGame;
    int x;
    int y;

    // Init boards
    currentGame.boardP1 = malloc(sizeof(enum Direction*) * BOARD_SIZE);
    currentGame.boardP2 = malloc(sizeof(enum Direction*) * BOARD_SIZE);
    currentGame.boatP1 = malloc(sizeof(enum Direction*) * BOARD_SIZE);
    currentGame.boatP2 = malloc(sizeof(enum Direction*) * BOARD_SIZE);

    for (int i = 0; i < BOARD_SIZE; i++) {
        currentGame.boardP1[i] = malloc(sizeof(enum Direction) * BOARD_SIZE);
        currentGame.boardP2[i] = malloc(sizeof(enum Direction) * BOARD_SIZE);
        currentGame.boatP1[i] = malloc(sizeof(enum Direction) * BOARD_SIZE);
        currentGame.boatP2[i] = malloc(sizeof(enum Direction) * BOARD_SIZE);
    }
    printf("Boards created\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            currentGame.boardP1[i][j] = WATER;
            currentGame.boardP2[i][j] = WATER;
            currentGame.boatP1[i][j] = WATER;
            currentGame.boatP2[i][j] = WATER;
        }
    }

    printf("Board ignited\n");

    // Init boats for player 1
    for (int i = 0; i < NBBOATS; i++) {
        p1.boats[i].x = 10;
        p1.boats[i].y = 8;
        do {
            p1.boats[i].x = rand() % 10;
            p1.boats[i].y = rand() % 10;

            if (p1.boats[i].dir == 0 && p1.boats[i].size > BOARD_SIZE - p1.boats[i].y) {
                p1.boats[i].y -= p1.boats[i].size;
            } else if (p1.boats[i].dir == 1 && p1.boats[i].size > BOARD_SIZE - p1.boats[i].x) {
                p1.boats[i].x -= p1.boats[i].size;
            }

        } while (testSizeBoat(p1.boats[i], currentGame.boatP1));

        for (int k = 0; k < p1.boats[i].size; k++) {
            if (p1.boats[i].dir == NORTH) {
                currentGame.boatP1[k + p1.boats[i].y][p1.boats[i].x] = BOAT;
            } else {
                currentGame.boatP1[p1.boats[i].y][k + p1.boats[i].x] = BOAT;
            }
        }
    }

    // Init boats for player 2
    for (int i = 0; i < NBBOATS; i++) {
        p2.boats[i].x = 10;
        p2.boats[i].y = 8;
        do {
            p2.boats[i].x = rand() % 10;
            p2.boats[i].y = rand() % 10;

            if (p2.boats[i].dir == 0 && p2.boats[i].size > BOARD_SIZE - p2.boats[i].y) {
                p2.boats[i].y -= p2.boats[i].size;
            } else if (p2.boats[i].dir == 1 && p2.boats[i].size > BOARD_SIZE - p2.boats[i].x) {
                p2.boats[i].x -= p2.boats[i].size;
            }

        } while (testSizeBoat(p2.boats[i], currentGame.boatP2));

        for (int k = 0; k < p2.boats[i].size; k++) {
            if (p2.boats[i].dir == NORTH) {
                currentGame.boatP2[k + p2.boats[i].y][p2.boats[i].x] = BOAT;
            } else {
                currentGame.boatP2[p2.boats[i].y][k + p2.boats[i].x] = BOAT;
            }
        }
    }

    return (currentGame);
}

/**
 * @brief Displays the contents of a game board.
 * 
 * @param board The game board to be displayed.
 */
void displayBoard(int** board) {
    for (int k = 0; k < BOARD_SIZE; k++) {
        printf("  %d ", k);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            printf("----");
        }
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (board[i][j]) {
                case 0:
                    printf("|   ");
                    break;
                case 1:
                    printf("| X ");
                    break;
                case 2:
                    printf("| O ");
                    break;
                case 3:
                    printf("| H ");
                    break;
            }
        }
        printf("| %d\n", i);
    }
    for (int k = 0; k < BOARD_SIZE; k++) {
        printf("----");
    }
    printf("\n");
}

/**
 * @brief Executes a round of the game.
 * 
 * @param game The current state of the game.
 * @return The updated state of the game after the round.
 */
Game gameRound(Game game) {
    // Locals
    int x;
    int y;
    int testx;
    int testy;
    int test = 1;

    // Scan and tests
    do {
        printf("Entrez valeures de x et de y :\n");
        testx = scanf("%d", &x);
        testy = scanf("%d", &y);
        if (testx != 1 || testy != 1 || x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            test = 1;
            printf("Error coordinates range\n");
        } else {
            test = 0;
        }
    } while (test);

    switch (game.boatP2[y][x]) {
        case WATER:
            game.boatP2[y][x] = WATER_SHOT;
            game.boardP1[y][x] = WATER_SHOT;
            printf("Target missed ...\n");
            break;
        case BOAT:
            game.boatP2[y][x] = WRECK;
            game.boardP1[y][x] = WRECK;
            printf("Target touched !\n");
            break;
        default:
            printf("Target already blown ...\n");
    }

    // Bot's turn
    do {
        x = rand() % 10;
        y = rand() % 10;
        if (game.boardP2[y][x] != WATER) {
            test = 1;
        } else {
            test = 0;
        }
    } while (test);

    switch (game.boatP1[y][x]) {
        case WATER:
            game.boatP1[y][x] = WATER_SHOT;
            game.boardP2[y][x] = WATER_SHOT;
            break;
        case BOAT:
            game.boatP1[y][x] = WRECK;
            game.boardP2[y][x] = WRECK;
            break;
    }
    return (game);
}

/**
 * @brief Tests the placement of boats for a player on the game board.
 * 
 * @param player The player to be tested.
 * @param board The game board.
 * @return The updated player structure after testing and updating boat positions.
 */
Player testPlayerBoats(Player player, int** board) {
    // Locals
    int test;

    for (int i = 0; i < NBBOATS; i++) {
        if (player.stateBoats[i]) {
            for (int j = 0; j < player.boats[i].size; j++) {
                if (player.boats[i].dir == 0 && BOAT == board[j + player.boats[i].y][player.boats[i].x]) {
                    test = 0;
                    break;
                } else if (player.boats[i].dir == 1 && BOAT == board[player.boats[i].y][j + player.boats[i].x]) {
                    test = 0;
                    break;
                }
                test = 1;
            }
            if (test) {
                player.stateBoats[i] = 0;
            }
        }
    }

    return (player);
}

/**
 * @brief Tests the overall state of the game.
 * 
 * @param p1 Player 1.
 * @param p2 Player 2.
 * @return 2 if player 1 wins, 1 if player 2 wins, 0 if the game is not over.
 */
int testGame(Player p1, Player p2) {
    // Locals
    int testP1 = 1;
    int testP2 = 1;

    for (int i = 0; i < NBBOATS; i++) {
        if (p1.stateBoats[i]) {
            testP1 = 0;
        }
        if (p2.stateBoats[i]) {
            testP2 = 0;
        }
    }
    if (testP1) {
        printf("%d\n", testP1);
        return (2);
    } else if (testP2) {
        return (1);
    } else {
        return (0);
    }
}
