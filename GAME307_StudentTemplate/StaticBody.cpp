#include "StaticBody.h"

void StaticBody::Update(float deltatime, KinematicSteeringOutput* steering){
	Body::Update(deltatime);

	vel = steering->velocity;
	rotation = steering->rotation;

	if (VMath::mag(vel) > maxSpeed) {
		vel = VMath::normalize(vel) * maxSpeed;
	}

	if (rotation > maxRotation) {
		rotation = maxRotation;
	}

}

void StaticBody::newOrientation() {

	if (VMath::mag(vel) > 0.0f) {
		orientation = atan2(-vel.y, vel.x);
	}

}
