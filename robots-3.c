#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	_Bool hasRobot; // 1 (true) a robot is here; 0 (false) the space is clear
	int robHeading; // 0 (west), 1 (north), 2 (east), 3 (south)
	_Bool robAlive; // 1 (true) for running robot; (false) when crashed
} gridSquare;

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	// The 10 by 10 grid
	gridSquare grid[10][10];

	// TODO: initialize the grid using a nested loop so there are no robots
	for (int j=0; j < 10; j++){
		for (int k=0; k<10; k++){
			grid[j][k].hasRobot = 0;
		}
	}
	int i;
	int row, column;

	// Add 10 robots to the grid
	for (i = 0; i < 10; i++) {

		// This makes sure that the grid space is currently empty
		do {
			row = rand() % 10;
			column = rand() % 10;
		} while (grid[row][column].hasRobot);

		// TODO:  Randomly set the heading at (column,row),
		//        and make the robot alive
		grid[row][column].robHeading=rand()%3;
		grid[row][column].hasRobot=1;
		grid[row][column].robAlive=1;	
	}

	// Counts the number of live robots
	int liveCount = 10;

	// main loop of the game
	do {

		// TODO: Output the grid
		for(row=0; row<10; row++){
			for(column=0; column<10; column++){
				if(grid[row][column].hasRobot && grid[row][column].robAlive){
					print("R");
				}
				else if(grid[row][column].hasRobot && !grid[row][column].robAlive){
					print("@");
				}
				else{
					print(".");
				}
			}
		}
		char cmd;

		// Obtain user input (move or rotate command)
		printf("\n input action and coordinates, please: ");
		scanf(" %c %i %i", &cmd, &row, &column);

		// Process user command
		if (grid[row][column].hasRobot && grid[row][column].robAlive) {

			if (cmd == 'L') {

				// TODO: Update the heading accordingly
				grid[row][column].robHeading = (grid[row][column].robHeading - 1)%3;
			} else if (cmd == 'R') {

				// TODO: Update the heading accordingly
				grid[row][column].robHeading = (grid[row][column].robHeading + 1)%3;
			} else if (cmd == 'F') {

				// This attempts to move the robot forward, depending on the
				// direction it is currently pointing
				switch (grid[row][column].robHeading) {

					case 0: // Pointing west
						if (column > 0) {
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row][column-1].hasRobot){
								if(grid[row][column-1].robAlive){
									grid[row][column-1].robAlive = 0;
									liveCount -= 1;
								}
								grid[row][column].robAlive = 0;
								liveCount -= 1;
							}
							else{
								grid[row][column-1].hasRobot=1;
								grid[row][column-1].robAlive=1;
								grid[row][column-1].robHeading=grid[row][column].robHeading;
								grid[row][column].hasRobot=0;
								grid[row][column].robAlive=0;
							}
						}
						break;

					case 1: // Pointing north
						if (row > 0) {
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row-1][column].hasRobot){
								if(grid[row-1][column].robAlive){
									grid[row-1][column].robAlive = 0;
									liveCount -= 1;
								}
								grid[row-1][column].robAlive = 0;
								liveCount -= 1;
							}
							else{
								grid[row-1][column].hasRobot=1;
								grid[row-1][column].robAlive=1;
								grid[row-1][column].robHeading=grid[row][column].robHeading;
								grid[row][column].hasRobot=0;
								grid[row][column].robAlive=0;
							}
						}
						break;

					case 2: // Pointing east
						if (column < 9) {
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row][column+1].hasRobot){
								if(grid[row][column+1].robAlive){
									grid[row][column+1].robAlive = 0;
									liveCount -= 1;
								}
								grid[row][column].robAlive = 0;
								liveCount -= 1;
							}
							else{
								grid[row][column+1].hasRobot=1;
								grid[row][column+1].robAlive=1;
								grid[row][column+1].robHeading=grid[row][column].robHeading;
								grid[row][column].hasRobot=0;
								grid[row][column].robAlive=0;
							}
						}
						break;

					case 3: // Pointing south
						if (row < 9) {
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row+1][column].hasRobot){
								if(grid[row+1][column].robAlive){
									grid[row+1][column].robAlive = 0;
									liveCount -= 1;
								}
								grid[row][column].robAlive = 0;
								liveCount -= 1;
							}
							else{
								grid[row+1][column].hasRobot=1;
								grid[row+1][column].robAlive=1;
								grid[row+1][column].robHeading=grid[row][column].robHeading;
								grid[row][column].hasRobot=0;
								grid[row][column].robAlive=0;
							}
						}
						break;

					default: // Shouldn't happen
						print("Error happened");
						break;
				}

			}

		}

	} while (liveCount > 0);

	return 0;
}
