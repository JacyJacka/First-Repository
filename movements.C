#include "movements.h"


//movements function: its core is a switch function that call cyclically every case through a "for" cycle.



void shift( vector<machine> &machines, vector<sf::CircleShape> &circles, vector<sf::RectangleShape> &energies) {


																									//first i need to save the "old" impulse in order to implement the solution with euler's 
	for( int u=0; u<3; u++){												//method. Acceleration is modulated exponentially in order to avoid extremely high speed.
																									//it's verified that hig speedare not so good for both the hitted and hitting particle and
		if (machines[u].giveLife() > 0){							//makes the game not so good. By this modulation every machine's speed will saturate to a
																									//maximum value due to the presence of the friction.
			float previousPx = machines[u].givePx();
			float previousPy = machines[u].givePy();
			float tau = 3;
			float acceleration = 0.25*exp(-sqrt(pow(machines[u].givePx()/machines[u].giveMass(),2) + pow(machines[u].givePx()/machines[u].giveMass(),2))/tau );
																																	//Every case has a specify set of comands, proper of the machine. Both 
			switch (u){																									//machine considered and command vary with the index of the "for cycle"
																																	//and so every machine has different controls. Then, every case has the 																																	//same structure: control if any of the keys are pressed and vary the 
				case 0:																										//impulse or the energy of the particle. Then exit from the swich 
																																	//structure and move the character. Then change the index in the for 
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){		//for cycle and reiterate the procedure with an other machine.

							machines[u].addImpulse(-acceleration,0);					//if "left" is pressed, change the impulse with the acceleration
																																// of the first machine
	
						}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

						machines[u].addImpulse(acceleration,0);						//if "right" is pressed, change the impulse with the acceleration
																															// of the first machine
					
						}
				
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

						machines[u].addImpulse(0,-acceleration);					//if "up" is pressed, change the impulse with the acceleration
																															// of the first machine

						}

				
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

						machines[u].addImpulse(0,acceleration);						//if "down" is pressed, change the impulse with the acceleration
																															// of the first machine


	
						}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && machines[u].giveCharge() < 30)
				{
	
						machines[u].addCharge(0.15);											//if "RShift" is pressed, increase the energy of the first machine,
																															// show the outline and inrease the lenght of the energy bar

						circles[u].setOutlineThickness(4);

						float lenght = 70 * machines[u].giveCharge()/30;

						energies[u].setSize(sf::Vector2f( lenght, 5));
					}

					else
						circles[u].setOutlineThickness(0);								//if "RShift" is not pressed, then don't show the outline


					break;


			case 1:

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

						machines[u].addImpulse(-acceleration,0);					//if "A" is pressed, change the impulse with the acceleration
																															// of the first machine

	

					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

						machines[u].addImpulse(acceleration,0);						//if "D" is pressed, change the impulse with the acceleration
																															// of the first machine
	
						}
				
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

						machines[u].addImpulse(0,-acceleration);					//if "W" is pressed, change the impulse with the acceleration
																															// of the first machine

						}
				
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

						machines[u].addImpulse(0,acceleration);					//if "S" is pressed, change the impulse with the acceleration
																														// of the first machine

						}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && machines[u].giveCharge() < 30)
				{
	
						machines[u].addCharge(0.15);											//if "Q" is pressed, increase the energy of the first machine,
																															// show the outline and inrease the lenght of the energy bar

						circles[u].setOutlineThickness(4);

						float lenght = 70 * machines[u].giveCharge()/30;

						energies[u].setSize(sf::Vector2f( lenght, 5));

					}

					else
						circles[u].setOutlineThickness(0);								//if "Q" is not pressed, then don't show the outline

					break;


				case 2:

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){

						machines[u].addImpulse(-acceleration,0);						//if "H" is pressed, change the impulse with the acceleration
																																// of the first machine

						}

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){

							machines[u].addImpulse(acceleration,0);						//if "K" is pressed, change the impulse with the acceleration
																																// of the first machine
							}
				
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)){

							machines[u].addImpulse(0,-acceleration);					//if "U" is pressed, change the impulse with the acceleration
																																// of the first machine
							}
				
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){

							machines[u].addImpulse(0,acceleration);					//if "J" is pressed, change the impulse with the acceleration
																															// of the first machine
							}


						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && machines[u].giveCharge() < 30)
					{
	
							machines[u].addCharge(0.15);										//if "Y" is pressed, increase the energy of the first machine,
																															// show the outline and inrease the lenght of the energy bar

							circles[u].setOutlineThickness(4);

							float lenght = 70 * machines[u].giveCharge()/30;

							energies[u].setSize(sf::Vector2f( lenght, 5));	

						}

						else
							circles[u].setOutlineThickness(0);							//if "Y" is not pressed, then don't show the outline

						break;


				}
				machines[u].Friction();

				circles[u].move((previousPx/ machines[u].giveMass()), (previousPy/ machines[u].giveMass()));

				machines[u].addXY((previousPx/ machines[u].giveMass()), (previousPy/ machines[u].giveMass()));
	
		}

	}

}


//this function implements the elastic bounces on the walls of the arena. If a particle hits the the wall, its othogonal impulse component
//will be immediately changed in sign, alike an elastic collision with an unmovable and extremely big object.


void bounce ( vector<machine> &machines, vector<sf::CircleShape> &circles, int bordersupx, int borderinfx, int bordersupy, int borderinfy){

	float vectorImpulsesX[3], vectorImpulsesY[3], vectorPositionsX[3], vectorPositionsY[3];

	for(int i=0; i<3; i++){									//here i save the "old" impulses and positions: the first have the function to make the wall 
																					//reflect the particle, the second to refresh the machine position after the collision in order 																					//to avoid compenetrations. 

		vectorPositionsX[i] = machines[i].givePositionX();
		vectorPositionsY[i] = machines[i].givePositionY();

		vectorImpulsesX[i] = machines[i].givePx();
		vectorImpulsesY[i] = machines[i].givePy();

	}

	for (int i=0; i<3; i++){																				//This process is iterated for all the three machines by a "for" cycle


		if (machines[i].givePositionX() < borderinfx){ 		//	verify if whe i-th particle collides on the left border: if so invert the
																											//	relative value of the impulse

			vectorImpulsesX[i] = vectorImpulsesX[i]*(-1);		
		
			vectorPositionsX[i] = borderinfx;

			machines[i].Friction();												// then recalls friction for the next motion

		}





		if (machines[i].givePositionX() > bordersupx){		//	verify if whe i-th particle collides on the right border: if so invert the
																											//	relative value of the impulse

			vectorImpulsesX[i] = vectorImpulsesX[i]*(-1);

			vectorPositionsX[i] = bordersupx;

			machines[i].Friction();													// then recalls friction for the next motion

		}




		if (machines[i].givePositionY() < borderinfy){		//	verify if whe i-th particle collides on the top border: if so invert the
																											//	relative value of the impulse

			vectorImpulsesY[i] = vectorImpulsesY[i]*(-1);

			vectorPositionsY[i] = borderinfy ;

			machines[i].Friction();													// then recalls friction for the next motion

		}




		if (machines[i].givePositionY() > bordersupy){		//	verify if whe i-th particle collides on the top border: if so invert the
																											//	relative value of the impulse
			vectorImpulsesY[i] = vectorImpulsesY[i]*(-1);

			vectorPositionsY[i] = bordersupy ;

			machines[i].Friction();													// then recalls friction for the next motion

		}


		machines[i].setImpulse( vectorImpulsesX[i], vectorImpulsesY[i] );		// now reset the machines impulses: if somene has bounced, 																																					//something will be inverted, otherwise no changing will be    																																					//happen in the values possessed by the machines.

		machines[i].setXY( vectorPositionsX[i], vectorPositionsY[i] );			//reset the positions of the particle for avoid compenetrations
		circles[i].setPosition( vectorPositionsX[i], vectorPositionsY[i] ); //do the same thing in the graphic representations.
	}
	

}

