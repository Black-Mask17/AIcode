#include "Arrive.h"

Arrive::Arrive(Body* character_, Body* target_, float targetRadius_, float slowRadius_, float timetotarget_)
{

	character = character_;
	target = target_;
	targetRadius = targetRadius_;
	slowRadius = slowRadius_;
	timetotarget = timetotarget_;
}
Arrive:: ~Arrive() {

}

SteeringOutput* Arrive::getSteering() {
	float distance = 1.0f ;
	Vec3 direction;
	Vec3 targetVelocity;

	direction = target->getPos() - character->getPos();
	distance = VMath::mag(direction);

	if (distance < targetRadius) {
		return NULL;
	}

	float targetspeed = VMath::mag(target->getVel());

	if (distance > slowRadius) {
		targetspeed = character->getMaxSpeed();
	}
	else {
		targetspeed = character->getMaxSpeed() * distance / slowRadius;
	}

	targetVelocity = direction;
	targetVelocity = VMath::normalize(targetVelocity);
	targetVelocity *= targetspeed;

	result->linear = targetVelocity - character->getVel();
	result->linear /= timetotarget;

	if (VMath::mag(result->linear) > target->getMaxAcceleration()) {
		VMath::normalize(result->linear);
		result->linear *= target->getMaxAcceleration();

	}

	result->angular = 0.0;

	return result;
}