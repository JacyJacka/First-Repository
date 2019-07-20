#include "collision.h"

/* this function takes as argument the machines vector, the life bar one and the indexes of the machine that are hitting.  

*/


void Two_Body_Collision(vector<machine> &machines, vector<sf::RectangleShape> &lives, int firstParticleIndex, int secondParticleIndex){

	
	
		float x = machines[firstParticleIndex].givePositionX() - machines[secondParticleIndex].givePositionX();
		float y = machines[firstParticleIndex].givePositionY() - machines[secondParticleIndex].givePositionY();

		float theta;
		if ( x >= 0)

			theta = atan(y/x);
		else
			theta = atan(y/x) + M_PI;
	

		float firstParticleImpulse = sqrt(pow(machines[firstParticleIndex].givePx() , 2) + pow(machines[firstParticleIndex].givePy() , 2));
		float secondParticleImpulse = sqrt(pow(machines[secondParticleIndex].givePx() , 2) + pow(machines[secondParticleIndex].givePy() , 2));


																													/* first of all passes in the relative coordinates, calculating the 																														position of the second machine respect to the first one and by this 																														also the direction of the relative impulse. Then takes memory of 																															the "old" impulse modulus of both the two machines. 

																													*/

	
		float totalMass = machines[secondParticleIndex].giveMass() + machines[firstParticleIndex].giveMass();

		float reductedMass = (machines[secondParticleIndex].giveMass() * machines[firstParticleIndex].giveMass())/totalMass;

		float totalImpulsex = machines[firstParticleIndex].givePx() + machines[secondParticleIndex].givePx();

		float totalImpulsey = machines[firstParticleIndex].givePy() + machines[secondParticleIndex].givePy();

		float relativeImpulsex = machines[firstParticleIndex].givePx() * ((machines[secondParticleIndex].giveMass())/totalMass) - machines[secondParticleIndex].givePx() * ((machines[firstParticleIndex].giveMass())/totalMass);

		float relativeImpulsey = machines[firstParticleIndex].givePy() * ((machines[secondParticleIndex].giveMass())/totalMass) - machines[secondParticleIndex].givePy() * ((machines[firstParticleIndex].giveMass())/totalMass);

		float relativeImpulseModulus =  sqrt(pow(relativeImpulsex,2) + pow(relativeImpulsey,2));

		relativeImpulsex = relativeImpulseModulus * cos(theta);
		relativeImpulsey = relativeImpulseModulus * sin(theta);

																																//here the function has just calculated the total and reduced mass and the 																																		total and relative impulses along the x and y coordinates. 


		machines[firstParticleIndex].setImpulse((relativeImpulsex + totalImpulsex * (machines[firstParticleIndex].giveMass()/totalMass) ), (totalImpulsey * (machines[firstParticleIndex].giveMass()/totalMass) + relativeImpulsey ));

		machines[secondParticleIndex].setImpulse((totalImpulsex * (machines[secondParticleIndex].giveMass()/totalMass) - relativeImpulsex ), (totalImpulsey * (machines[secondParticleIndex].giveMass()/totalMass) - relativeImpulsey ));




																															// 	Lastly, here it has just recombinated the new impulses, inverting the 																																transformation previous applicated using the "reflected" relative impulses. 																																The function ends by calculating and assigning the damages based on the 																																speed of the machines (the slower you go, more is damage you take) and 																																	updating to this the character's lifebars.




		float deltaLife = (pow(relativeImpulsex,2) + pow(relativeImpulsey,2))/(2*10*reductedMass); //here's the total damage that has to be 																																																distributed to both the machines

		machines[firstParticleIndex].addLife( deltaLife * 2 * secondParticleImpulse/(secondParticleImpulse + firstParticleImpulse) ); 																																																			//assigning the damage

		lives[firstParticleIndex].setSize(sf::Vector2f( 70 * machines[firstParticleIndex].giveLife()/150, 5)); //updating the lifebar


		machines[secondParticleIndex].addLife( deltaLife*2*(1 - secondParticleImpulse/(firstParticleImpulse+secondParticleImpulse)) );																																																			//assigning the remaining damage

		lives[secondParticleIndex].setSize(sf::Vector2f( 70 * machines[secondParticleIndex].giveLife()/150, 5)); 			//updating the lifebar


};







/*
This function recives as arguments only the machine's and lifebar's vectors, since it has to treat with all of the three of the characters.
*/

void Three_Body_Collision(vector<machine> &machines, vector<sf::RectangleShape> &lives){

																																						//here i define the parameters of the tranformation from the 																																								"pc" coordinates system to the center-mass one.

	
	float totalImpulsex = 0 , relativeImpulse10x, relativeImpulse20x, totalImpulsey = 0, relativeImpulse10y, relativeImpulse20y, relativeImpulse21x, relativeImpulse21y, totalMass = 0, m0, m1, m2;

	float newImpulse0x, newImpulse1x, newImpulse2x, newImpulse0y, newImpulse1y, newImpulse2y;

																																									//here i calculate the fraction masses m0, m1 and m2 and 																																											the total mass "totalMass"

	for (int i=0; i<3; i++)
		totalMass += machines[i].giveMass();


	m0 = machines[0].giveMass()/totalMass;
		
	m1 = machines[1].giveMass()/totalMass;
	
	m2 = machines[2].giveMass()/totalMass;
	

	


																																		//here i start to apply the transformation, calculating the mass-centre 																																			impulse

	for (int i=0; i<3; i++){

		totalImpulsex += machines[i].givePx();
		totalImpulsey += machines[i].givePy();

		}

																																	//here i finish to apply the tranformation, calculating the relative 																																			impulses, using the transformation written in "collision.h"

	relativeImpulse10x = (-1)*m1*machines[0].givePx() + (m0 + m2)*machines[1].givePx() - m1*machines[2].givePx();
	relativeImpulse10y = (-1)*m1*machines[0].givePy() + (m0 + m2)*machines[1].givePy() - m1*machines[2].givePy();
	
	relativeImpulse20x = (-1)*m2*machines[0].givePx() - m2*machines[1].givePx() + (m0+m1)*machines[2].givePx();
	relativeImpulse20y = (-1)*m2*machines[0].givePy() - m2*machines[1].givePy() + (m0+m1)*machines[2].givePy();
	
	relativeImpulse21x = (m0+m1)*machines[0].givePx() - m2*machines[1].givePx() - m2*machines[2].givePx();
	relativeImpulse21y = (m0+m1)*machines[0].givePy() - m2*machines[1].givePy() - m2*machines[2].givePy();
	
																																								//i excange the relative impulses of the machines

	relativeImpulse10x = relativeImpulse10x*(-1);
	relativeImpulse10y = relativeImpulse10y*(-1);

	relativeImpulse20x = relativeImpulse20x*(-1);
	relativeImpulse20y = relativeImpulse20y*(-1);

																																								//and finally recombine the impulses.



	newImpulse0x = m0*totalImpulsex - relativeImpulse10x - relativeImpulse20x;
	newImpulse0y = m0*totalImpulsey - relativeImpulse10y - relativeImpulse20y;

	newImpulse1x = m1*totalImpulsex + relativeImpulse10x;
	newImpulse1y = m1*totalImpulsey + relativeImpulse10y;

	newImpulse2x = m2*totalImpulsex + relativeImpulse20x;
	newImpulse2y = m2*totalImpulsey + relativeImpulse20y;


																																				//now i assigne the new impulses to the machines

	machines[0].setImpulse(newImpulse0x, newImpulse0y);
	machines[1].setImpulse(newImpulse1x, newImpulse1y);
	machines[2].setImpulse(newImpulse2x, newImpulse2y);

																																				//	finally i calculate the damage due to all the three 																																						interactions between the particles and the weights with wich it 																																						has to be assigned



	float deltaLife10 = (pow(relativeImpulse10x,2) + pow(relativeImpulse10y,2))/(2*30*(m0*m1/(m0+m1)));
	float deltaLife20 = (pow(relativeImpulse20x,2) + pow(relativeImpulse20y,2))/(2*30*(m0*m2/(m0+m2)));
	float deltaLife21 = (pow(relativeImpulse21x,2) + pow(relativeImpulse21y,2))/(2*30*(m2*m1/(m2+m1)));


	float K0 = sqrt(pow(machines[0].givePx(),2) + pow(machines[0].givePy(),2));
	float K1 = sqrt(pow(machines[1].givePx(),2) + pow(machines[1].givePy(),2));
	float K2 = sqrt(pow(machines[2].givePx(),2) + pow(machines[2].givePy(),2));

																																			 //In conclusion, i assign the damages treating the interactions as 																																				two-body collisions and summing on the same machine.
	machines[0].addLife(deltaLife10 * K0/(K0+K1));
	machines[0].addLife(deltaLife20 * K0/(K0+K2));

	machines[1].addLife(deltaLife10 * K1/(K0+K1));
	machines[1].addLife(deltaLife21 * K2/(K1+K2));

	machines[2].addLife(deltaLife20 * K2/(K0+K2));
	machines[2].addLife(deltaLife21 * K2/(K1+K2));

																																			//here i update also the characther's lifebars.

	for (int i=0; i<3; i++)
		lives[i].setSize(sf::Vector2f( 70 * machines[i].giveLife()/150, 5));
	

	

};







/*
this function serves only to ceck if a collision is really happening and, if so, calling the "two body collision" or
"three body collision" functions. After that it recordes the position of all the three machines in the two position vector defined 
at the beginning of the main program "alpha_version.C" : "positionParticlesX" and "PositionParticlesY"
*/




void Collisions(vector<machine> &machines, vector<sf::CircleShape> &circles,  vector<sf::RectangleShape> &lives, float* x, float* y){

	
	int whoCollides = 0;																			 //this variable has the function to establish who is interacting with who, 																															through the next two controls:

	for (int i=0; i < 3; i++){
		for (int j= (i+1); j < 3; j++){

	if (machines[i].giveLife() > 0 && machines[j].giveLife() > 0){

		if (sqrt(pow(machines[i].givePositionX() - machines[j].givePositionX(),2) + pow(machines[i].givePositionY() - machines[j].givePositionY(),2)) <= (machines[i].giveRadius() + machines[j].giveRadius()))
		{
			whoCollides = i+j;	
	
	
				}
			}
		}
	}	

																																		/*this cycle checks if the distance between the i-th particle and the 																																		j-th particle is less than the sum of theyr radius.
																																		In affermative case, whoCollides takes the value "i+j", so this means:

																																		whoCollides = 1 -> particle 0 on particle 1
																																		whoCollides = 2 -> particle 0 on particle 2
																																		whoCollides = 3 -> particle 1 on particle 2
																																		*/




																																			/*
																																			next control in an extremely enormous "if" selection that 																																			controls if at least two particle are hitting at the same time the 																																				third.
																																			If so, whoCollides takes the value 4.
																																			*/

if (machines[0].giveLife() > 0 && machines[1].giveLife() > 0 && machines[2].giveLife() > 0){

		if 
		(
	 (sqrt(pow(machines[0].givePositionX() - machines[1].givePositionX(),2) + pow(machines[0].givePositionY() - machines[1].givePositionY(),2)) <= (machines[1].giveRadius() + machines[0].giveRadius()) && 
		sqrt(pow(machines[0].givePositionX() - machines[2].givePositionX(),2) + pow(machines[0].givePositionY() - machines[2].givePositionY(),2)) <= (machines[2].giveRadius() + machines[0].giveRadius())) 

	||

		(sqrt(pow(machines[2].givePositionX() - machines[1].givePositionX(),2) + pow(machines[2].givePositionY() - machines[1].givePositionY(),2)) <= (machines[2].giveRadius() + machines[1].giveRadius()) && 
		sqrt(pow(machines[0].givePositionX() - machines[2].givePositionX(),2) + pow(machines[0].givePositionY() - machines[2].givePositionY(),2)) <= (machines[2].giveRadius() + machines[2].giveRadius()))

	||

		(sqrt(pow(machines[0].givePositionX() - machines[1].givePositionX(),2) + pow(machines[0].givePositionY() - machines[1].givePositionY(),2)) <= (machines[1].giveRadius() + machines[0].giveRadius()) && 
		sqrt(pow(machines[1].givePositionX() - machines[2].givePositionX(),2) + pow(machines[2].givePositionY() - machines[3].givePositionY(),2)) <= (machines[3].giveRadius() + machines[2].giveRadius()))

	){

	
			whoCollides = 4;
	}
}

																															//here's a switch selection dictated by "whoCollides". It calls back the 																																	appropriate function, then saves the position of the particle that are not 																																	hitting and reset the others avoiding compenetration after collision. 

		switch(whoCollides){

			case 1:

				Two_Body_Collision(machines, lives, 0, 1); 					//calling the two body collision

				for ( int i=0; i<2; i++)
				{
				machines[i].setXY( x[i], y[i]);											//resetting the interacting particle's positions
				circles[i].setPosition( x[i], y[i]);

				}
		
				x[2] = machines[2].givePositionX();									//updating the position of non-interacting particle
				y[2] = machines[2].givePositionY();


				break;

			case 3:

				Two_Body_Collision(machines, lives, 2, 1); 					//calling the two body collision

				for ( int i=1; i<3; i++ ){

					machines[i].setXY( x[i], y[i] );									//resetting the interacting particle's positions
					circles[i].setPosition( x[i], y[i] );
			
				}

				x[0] = machines[0].givePositionX();									//updating the position of non-interacting particle
				y[0] = machines[0].givePositionY();

				break;

			case 2:

				Two_Body_Collision(machines, lives, 2, 0);					//calling the two body collision

		
				machines[0].setXY( x[0], y[0] );										//resetting the interacting particle's positions
				circles[0].setPosition( x[0], y[0] );


				machines[2].setXY( x[2], y[2] );										//resetting the interacting particle's positions
				circles[2].setPosition( x[2], y[2] );

				x[1] = machines[1].givePositionX();									//updating the position of non-interacting particle
				y[1] = machines[1].givePositionY();

				break;

			case 4:

				Three_Body_Collision(machines, lives);							//calling the three body interaction

				for (int i=0; i<3; i++){

				machines[i].setXY( x[i], y[i] );										//resetting all the positions
				circles[i].setPosition( x[i], y[i]);

				}

				break;

			default:

				for ( int i=0; i<3; i++ ){

				x[i] = machines[i].givePositionX();								//here nobody's interacting, so it's only saving the particle's positions
				y[i] = machines[i].givePositionY();
				
				}

				break;

		}


};

	
