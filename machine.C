#include "machine.h"


																															//constructor of the machine class: it istantiates the contructor parameters 																																	of the machine and sets the initial impulses and the charge to zero.

machine::machine(float Radius, float Mass, float Life){

	

	radius = Radius;

	mass = Mass;

	life = Life;

	charge = 0;


	Px=0;
	Py=0;

	
}


																	//destructor function of the "machine" class

machine::~machine(){


};


																							//"output" functions: as explained in "machine.h", they simply return 																								in output the value of the attribute they refers.


float machine::giveRadius() const{

	return radius;


};

float machine::giveMass() const{

	return mass;


};
		
float machine::giveLife() const{

	return life;


};

float machine::givePx() const{

	return Px;


};

float machine::givePy() const{

	return Py;


};

float machine::givePositionX() const{

	return x;


};

float machine::givePositionY() const{

	return y;


};




int machine::giveIndex() const{

	return Index;

};


float machine::giveCharge() const{

	return charge;


};

void machine::setCharge(float newCharge){

	charge = newCharge;

};


																												//"input" functions: "add" functions adds/subtracts the value to the previous one, 																														"set" functions overvwrites on it



	//get damage


void machine::setLife(float lifeValue){

	life = lifeValue;

};


void machine::addLife(float Damage){

	life -= Damage;

};



	//get impulse

void machine::setImpulse(float ImpulseX, float ImpulseY){

	Px = ImpulseX;
	Py = ImpulseY;

};


void machine::addImpulse(float hitX, float hitY){

	Px += hitX;
	Py += hitY;

};



	//change position

void machine::setXY(float newPositionX, float newPositionY){

	x = newPositionX;
	y = newPositionY;

	

};


void machine::addXY(float moveX, float moveY){

	x += moveX;
	y += moveY;



};


void machine::setIndex (int positionInVector){

	Index = positionInVector;

};


																																//this is the function that allow the machine to charge theyr energy and so 																																	use the superpower. Energy stacks to a maximum up to 30.

void machine::addCharge( float chargeAmount){

	charge += chargeAmount;

};



																																//friction function: a deceleration that constantly reduces the impulse in 																																		both of the coordinates, opposing to the motion of the machine, wether 																																		direction it is. It doesn't afflict the istantaneous position, simply 																																	reduces the impulses along the two coordinates.


void machine::Friction(){

	float theta, frictionX, frictionY;



	if (Px != 0 || Py !=0){

		if (Px >= 0)

			theta = atan(Py/Px);

		else
			theta = atan(Py/Px) + M_PI;


		frictionX = 0.071*cos(theta);
		frictionY = 0.071*sin(theta);

		Px -= frictionX;
		Py -= frictionY;

		}
};








//this is the roundhose kick. Every character possesses a special key to acrtivate it ad a special one to charge it. When a machine is charging, a ring appears around it and the energy bar grows on the right panel. When a machine uses the move the energy abruptly decreases and the bars are updated.


//this function needs in input the vectors of the machines and the ones of the bars. Then istantiate an sf::Keyboard::Key array of the keys that allows the characters to use the powers.




void machine::RoundhouseKick(vector<machine> &machines, vector<sf::RectangleShape> &energies, vector<sf::RectangleShape> &lives){

	sf::Keyboard::Key superButtons[3] = {sf::Keyboard::Numpad0, sf::Keyboard::E, sf::Keyboard::I};//vector of the "use the kick" key.
	


//start the controls: superpowers is used if the charge is at least 20, if you are alive and if you are pushing the key.
//"Index" attribute in this situation is important because assigns a specific key to every machine and allows them to control if they're going to kick themselves or someone other.


	if(charge >= 20 && sf::Keyboard::isKeyPressed(superButtons[Index]) && giveLife() > 0){

	

		for(int i=0; i<3; i++){

			
			float deltax = x-machines[i].givePositionX(); // here is calculating "theta", that gives the directionin wich the machine will push 																											 away the target 
			float deltay = y-machines[i].givePositionY();

			float theta;

			if ( deltax >= 0)
				theta = atan(deltay/deltax) + M_PI;

			else
				theta = atan(deltay/deltax);


			//now here's the check if the machine is hitting someone other or itself. Kick will work only in the first case

			if(( i != Index) && sqrt(pow(deltax,2) + pow(deltay,2)) <= 160 && machines[i].giveLife() > 0){

				float P = 70;

				machines[i].addImpulse( P*cos(theta), P*sin(theta) );  //the machine posh away the other one
				machines[i].addLife(10);				//the machine gives damage to the others
			


				addCharge(-20);  //using the superpowers costs 20 of energy.

				if (charge < 0)   //a control that sets to zero every possible negative energies
					setCharge(0);

				energies[Index].setSize(sf::Vector2f(70 * charge/30, 5)); //updating the energy bars.

			}
			lives[i].setSize(sf::Vector2f(70 * machines[i].giveLife()/150, 5)); //updating the life bars

		}

	}



};



