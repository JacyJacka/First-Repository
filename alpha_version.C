#include "movements.h"
#include <vector>

int main(){
	
																									// initialization vectors of the particles' positions
		float positionParticlesX[3];
		float positionParticlesY[3];

																									//defining the boundaries of the virtual arena, giving the coordinates of the corners in 																											pixels
	
		int limsupx = 754;
		int liminfx = 21;
		int limsupy = 554;
		int liminfy = 21;

																									//here i istantiate a counter of how many characters are still alive. Since the game has 																											to start yet, it equals its maximum value.
		int stillStanding = 3;

																									// loading font of all the character's data
		sf::Font font; 
		font.loadFromFile("Prototype.ttf");

																											//defining the limits of the arena's image on the screen

		sf::RectangleShape arena(sf::Vector2f(760,560));

																											//istantiating the bar of the character's energy ad life

		vector<sf::RectangleShape> lives(3,sf::RectangleShape(sf::Vector2f(70, 5)));
		vector<sf::RectangleShape> energies(3, sf::RectangleShape(sf::Vector2f(0, 5)));

																											//setting arena's position ad colors

		arena.setPosition(20,20);
		arena.setFillColor(sf::Color::Black);
		arena.setOutlineThickness(3);
		arena.setOutlineColor(sf::Color::Green);

																											//istantiating a vector of the images of the charachter's names

		vector<sf::Text> Names(3);

																											//istantiating the caracter's machines
		
		vector <machine> machines( 3, machine(13,50,150) );

																											//creating an array that takes memory when a character is just dead

		bool notAlreadyDead[3] ={true,true,true};



																											// here's a loop to: 1) make the characters to "learn" theyr position in the array 																													"machines"; 2)position and regulate the text about the characters, 3) color the 																												energy and lives bars.
 
		for (int i=0; i<3; i++){

			machines[i].setIndex(i);

			Names[i].setFont(font);
			Names[i].setCharacterSize(20);
			Names[i].setStyle(sf::Text::Regular);

			lives[i].setFillColor(sf::Color::Green);

			energies[i].setFillColor(sf::Color::Cyan);

		}

																											//here i effectively write and positionate the names of the characters and theyr 																													bars	

		Names[0].setString("Red");
		Names[0].setPosition( 900, 70);

		lives[0].setPosition(900, 95);
		energies[0].setPosition(900, 103);

		Names[1].setString("Blue");
		Names[1].setPosition( 900, 270);

		lives[1].setPosition(900, 295);
		energies[1].setPosition(900, 303);


		Names[2].setString("Yellow");
		Names[2].setPosition( 900, 470);

		lives[2].setPosition(900, 495);
		energies[2].setPosition(900, 503);

																												//here i positionate the machines on the virtual arena

		machines[0].setXY(400,200);

		machines[1].setXY(573,500);

		machines[2].setXY(227,500);
	
																												//here i create an array of the images of the machines: three dots of different 																													colours

		vector <sf::CircleShape> circles( 3, sf::CircleShape(13,30) );

																												//i give to the images the same position of theyr relative machine in the virtual 																													map and give a "border" that will show when they charge theyr superpower

		for ( int i=0; i<3; i++ ){
			circles[i].setPosition(machines[i].givePositionX(), machines[i].givePositionY());
			circles[i].setOutlineColor( sf::Color(30,120,0) );
			}

																											//here i color the dots

		circles[0].setFillColor( sf::Color::Red );
		circles[1].setFillColor( sf::Color::Blue );
		circles[2].setFillColor( sf::Color::Yellow );

																											//finally, i create a window that will draw all the stuff precedently created.


		sf::RenderWindow window( sf::VideoMode(1100,600), "Last Man Standing!");


																										//begin game loop: it will continue as soon as the window is opened

		while (window.isOpen()){

		
			sf::Event event;

																									//here's the check if the window "close" button is clicked: if so, then close the window 																										and exit from the loop
			while (window.pollEvent(event)){

				if (event.type == sf::Event::Closed)


					window.close();


			};

																									//check of any collision


			Collisions(machines, circles, lives, positionParticlesX, positionParticlesY);
			

																									//ceck if someone able to use the roundhouse kick is effectively using it on someone

			for (int i=0; i<3; i++)	
				machines[i].RoundhouseKick(machines, energies, lives);


																									//	checking if someone is hitting on the borders of the arena

			bounce (machines, circles, limsupx, liminfx, limsupy, liminfy);
	
																									//making the particles move, shifting them a little following theyr motions equations
		
			shift(machines, circles, energies);

																									//clearing the window from its "image"

			window.clear(sf::Color::Black);

																									//drawing the arena and the other images precedently updated

			window.draw(arena);				
				
			
			
			for (int i = 0; i<3; i++){
	
				if (machines[i].giveLife() < 0){
						machines[i].setLife(0);

						lives[i].setSize(sf::Vector2f(0,5));

				}


				if (machines[i].giveLife() > 0)
					window.draw(circles[i]);

				window.draw(Names[i]);
				
				window.draw(lives[i]);
		
				window.draw(energies[i]);

				}

																																// here the window displays the whole image


			window.display();
																																//	check if someone is now died: if so, stillstanding is decreased 																																	by one and if it's equal to one or zero exit from the game loop

			for (int i=0; i<3; i++){
				if (machines[i].giveLife() == 0 && notAlreadyDead[i]){

					stillStanding--;
					notAlreadyDead[i] = false;

				}
			}

			

			if (stillStanding <= 1)
				break;


		};

																															//	last loop is for controlling who's left alive: then a succession of if 																																		delcares the winner or a draw between the last two characters

		int who = 3;

		for(int i=0; i < 3; i++){
			
			if (machines[i].giveLife() < 0)
						machines[i].setLife(0);

			if (machines[i].giveLife() != 0)
					who = i;		
		}

	if (who == 0)
		cout << endl << endl << endl << endl << "and the winner is Red!"<< endl << endl << endl << endl << endl << endl;

	if (who == 1)
		cout << endl << endl << endl << endl << "and the winner is Blue!"<< endl << endl << endl << endl << endl << endl;

	if (who == 2)
		cout << endl << endl << endl << endl << "and the winner is Yellow!"<< endl << endl << endl << endl << endl << endl;

	if (who == 3)
		cout << endl << endl << endl << endl << "DRAW!"<< endl << endl << endl << endl << endl << endl;

	return 0;

}


//end of the game
