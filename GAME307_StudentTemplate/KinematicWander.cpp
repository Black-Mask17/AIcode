#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_) {

	character = character_;

	result = new KinematicSteeringOutput();
}

KinematicWander::~KinematicWander()
{
	if (result) { delete result; }
}
float KinematicWander::randomBinomial() {
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	float d = ((float)rand() / (RAND_MAX)) ;
	
	return  d;
}
KinematicSteeringOutput* KinematicWander::getSteering()
{
	result->velocity = character->getMaxSpeed() * getCharacterOrientation();

	result->rotation = randomBinomial() * character->getMaxRotation();

	return result;
}

Vec3 KinematicWander::getCharacterOrientation()
{
	Vec3 Adj (1, 0, 0);

	return Adj / cos(character->getOrientation());
}
