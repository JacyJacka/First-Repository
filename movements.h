#include "collision.h"

//those are the function related to the movements of the characters. These functions are divided in two moments: the first one in which it changes the impulses and the second one in which it moves the particle, both virtually and graphically.
//The motions statisfy the Hamilton's uniformly accelerated motions equations and are implemented by using the Euler's algorythm because the dynamics of the game, the continuous changes in the accelerations and the restricted space in which the machine are forced to stay make the error in the solution not so influent to the events during the match. Every cycle of the game loop inreases the game time of one "time unit", so the increment of the impulse is equal to the acceleration and the one of the position to the "old" speed.


																														//this funtion takes in input the machines vector, the cirlces ones and the 																														energies ones. It controls which key is pressed and varies the impulse or the 																														energy consequently.

void shift( vector<machine> &machines, vector<sf::CircleShape> &circles,  vector<sf::RectangleShape> &energies);


																														//this function verifies if a machine is hitting the border of the arena and if 																														so resets the impuses in order to make it elastically bounce on the "wall" This 																														kind of collision doesn't affect the character's life.
																														//this function takes in input the machines and vircles vector and the 4 borders 																															of the arena.

void bounce ( vector<machine> &machines, vector<sf::CircleShape> &circles, int limsupx, int liminfx, int limsupy, int liminfy);


