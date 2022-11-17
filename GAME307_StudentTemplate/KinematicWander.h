#ifndef KINEMATIC_WANDER_H
#define KINEMATIC_WANDER_H

#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicWander
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	float randomBinomial();
public:
	KinematicWander(Body* character_);
	~KinematicWander();
	KinematicSteeringOutput* getSteering();

	Vec3 getCharacterOrientation();

};
#endif

