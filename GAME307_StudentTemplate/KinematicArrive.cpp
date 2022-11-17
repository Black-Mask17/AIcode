#include "KinematicArrive.h"

KinematicArrive::KinematicArrive(Body* character_, Body* target_, float radius_, float timeTotarget_)
{
	character = character_;
	target = target_;
	radius = radius_;
	timeTotarget = timeTotarget_;
	result = new KinematicSteeringOutput();
}

KinematicArrive::~KinematicArrive()
{
	if (result) { delete result; }
}

KinematicSteeringOutput* KinematicArrive::getSteering()
{
	result->velocity = target->getPos() - character->getPos();

	if (VMath::mag(result->velocity) < radius) {
		return NULL;

	};

	result->velocity /= timeTotarget;

	if (VMath::mag(result->velocity) > character->getMaxSpeed()) {

		VMath::normalize(result->velocity);
		result->velocity *= character->getMaxSpeed();

	};

	result->rotation = 0.0f;

	return result;
}