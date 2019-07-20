#include "machine.h"

//collisions are implemented by three functions. The main one, "Collisions" cecks what kind of collision is happening, if it's happening, then recalls one of the other two, passing them the machines involved and theyr health bar.
/*Both "Two body collision" and "Three body collision" uses a tranformation of the impulses due to passig from the "pc reference system"
to the mass-centre one proper of the two or three bodie that are hitting. In ths system, two bodies see each other coming with impulse 
equal to the relative one. Then an elatical hit happens and the two machines go back with the same impulse but in the opposite direction.
Using this transformation and recombining relative and total impulse after the collision energy and total impulse are preserved.
Last, "collision" updates the particles position resetting them to the ones immediately before the hit, avoiding mutual penetration.
*/


/* the "two body collision" starts calculating the total impulse and the relative one separating the mass-centre problem and the relative one
then resets and recombinates the impulses as described above. The transformation used is:

P = p1 +p2
p = m2*p1/(m1+m2) - m1*p2/(m1+m2)

where: P is the mass-centre impulse, p the relative one and p1 and p2 are the one proper onf the first and second machine

*/


/* "three body collision" does the same thing by using the sequent transformation:

P = p1 + p2 + p3
p21 = -m2*p1/M + (m1+m3)*p2/M  - m2*p3/M
p31 = -m3*p1/M - m3*p2/M + (m1+m2)*p3/M
p32 = (m1+m2)*p1/M - m3*p2/M - m3*p3/M

where a similar legend has to apply in this equations.
It' important to specify that "two body collision" and "three body collision" have the only effect to redistribute the impulses
any evolution is left to the "shift" function in file movements.C
*/



void Collisions(vector<machine> &machines, vector<sf::CircleShape> &circles,  vector<sf::RectangleShape> &lives, float *positionParticlesX, float *positionParticlesY);



void Two_Body_Collision(vector<machine> &machines,  vector<sf::RectangleShape> &lives, int firstParticleIndex, int secondParticleIndex);


void Three_Body_Collision(vector<machine> &machines, vector<sf::RectangleShape> &lives);


