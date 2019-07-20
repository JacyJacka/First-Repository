#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


//here's the header of the principal element in this program: the machine class.
//Every machine is represented by a circle and possesses mass, radius, life, an index and a charge: those are the intrinsic parameters of every character. 
//Plus, every machine possesses an impulse and a position that allows them to "know" where they are, theyr speed and let the "collision" functions to predict theyr behavour after the hit.

class machine{

	private:

		float radius; // radius of the circle

		float mass; // mass of the machine

		float life;//	life of the machine

		int Index;// index that allows the machine to know its position in the vector "machines"

	
		float Px; //coordinate x of the Impulse
		float Py; //coordinate y of the impulse
		
		float x, y; // coordinates x and y of the position

		float charge; // charge that allows the machine to use the superpowers

	
	public:

																												//constructor of the machines: it need all the contruction parameters to 																														instantiate a new one and it will start with null speed.

		machine(float Radius, float Mass, float Life);

		~machine();													 							//here's the destructor of the "machine" class



																											//those are the "output" functions: every attribute has a dedicated one, because the 																													machine needs to comunicate with the surrounding enviroment. Output functions 																												doesn't change the value of the attribute, simply returnes it, so are declared 																													constant.

		float giveRadius() const;

		float giveMass() const;
		
		float giveLife() const;

		float givePx() const;

		float givePy() const;

		float givePositionX() const;

		float givePositionY() const;

		int giveIndex() const;

		float giveCharge() const;


																												//those are the "input" functions: "set" prefix indicates that the function 																													overwrites the new value on the previous one, "add" indicates that the function 																													will add or subtract the value taken as input to the preexiistent one. those are 																														all void, but requires a float value as input.

		void setLife(float lifeValue);

		void addLife(float Damage);

		void setImpulse(float ImpulseX, float ImpulseY);
	
		void addImpulse(float hitX, float hitY);

		void setXY(float newPositionX, float newPositionY);

		void addXY(float moveX, float moveY);


		void addCharge(float chargeAmount);

		void setCharge(float newCharge);

		void setIndex (int positionInVector);

																												//	"friction" function: it add to the motion a costant friction that eventually 																													stops the machine if the accelerator isn't being held. this has been introduced 																												principally for the necessity to make the machines easier to be controlled and 																													because every machine has a friction: due to the engine brake, due to the 																												intrinsic friction in the engine, due to the total friction that the car feels 																													when it moves.
		
		void Friction();



																												//this is the only superpower i managed to introduce: inspired by Chuck Norris, a 																													roundhouse kick that istantly hits everything that is in a certain radius around 																														the character. It adds a certain impulse and gives a certain damage to the hit 																														ones, pushing them away.

		void RoundhouseKick(vector<machine> &machines, vector<sf::RectangleShape> &energies, vector<sf::RectangleShape> &lives);


};



