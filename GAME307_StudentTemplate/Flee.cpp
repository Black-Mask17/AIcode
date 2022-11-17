#include "Flee.h"

Flee::Flee(Body* character_, Body* target_)
{

	character = character_;
	target = target_;
}
Flee:: ~Flee() {

}

SteeringOutput* Flee::getSteering() {


	//Get direction to target
	result->linear = character->getPos() - target->getPos() ;

	// accelerate along this direction
	result->linear = VMath::normalize(result->linear) * character->getMaxAcceleration();

	result->angular = 0.0f;

	return result;
}