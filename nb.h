#ifndef NB_H
	#define NB_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	
	#define NBBOATS 5
	#define BOARD_SIZE 10
	
	/**
	 * @brief Represents the possible states of a square on the game board.
	 */
	enum Square {
	    WATER,      ///< Represents a water square on the game board.
	    WATER_SHOT, ///< Represents a water square that has been shot at.
	    BOAT,       ///< Represents a square occupied by a boat.
	    WRECK,      ///< Represents a square that was part of a boat but is now a wreck.
	};
	
	/**
	 * @brief Represents the possible directions a boat can be placed on the game board.
	 */
	enum Direction {
	    NORTH,  ///< Boat is oriented to the north on the game board.
	    EAST,   ///< Boat is oriented to the east on the game board.
	};
	
	/**
	 * @brief Represents a boat in the game.
	 */
	typedef struct {
	    int size;           ///< Size of the boat.
	    int x;              ///< X-coordinate of the boat's starting position.
	    int y;              ///< Y-coordinate of the boat's starting position.
	    enum Direction dir; ///< Direction in which the boat is oriented.
	} Boat;
	
	/**
	 * @brief Represents the game board.
	 */
	typedef struct {
	    int** board; ///< 2D array representing the game board.
	    int size;    ///< Size of the game board.
	} Board;
	
	/**
	 * @brief Represents the state of the game, including the boards and boats for both 	players.
	 */
	typedef struct {
	    int** boardP1; ///< Player 1's game board.
	    int** boardP2; ///< Player 2's game board.
	    int** boatP1;  ///< Player 1's boat positions.
	    int** boatP2;  ///< Player 2's boat positions.
	} Game;
	
	/**
	 * @brief Represents a player in the game, including their boats and the state of those 	boats.
	 */
	typedef struct {
	    Boat* boats;      ///< Array of boats for the player.
	    int* stateBoats;  ///< Array representing the state of each boat (e.g., sunk or 	afloat).
	} Player;
	
	Boat initBoat(int size);
	Player initPlayer(int* sizeBoats);
	int testBoat(Boat boat, int** board);
	int testSizeBoat(Boat boat, int** board);
	Game initGame(Player p1, Player p2);
	Game gameRound(Game game);
	void displayBoard(int** board);
	Player testPlayerBoats(Player player, int** board);
	int testGame(Player p1, Player p2);
	
#endif		
