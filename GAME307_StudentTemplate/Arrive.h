#ifndef ARRIVE_H
#define ARRIVE_H
#include "SteeringBehaviour.h"
class Arrive :

	public SteeringBehaviour
{
protected:
	Body* target;
	float slowRadius;
	float timetotarget = 0.1;
	float targetRadius;

public:

	Arrive(Body* character_, Body* target_, float targetRadius_, float slowRadius_, float timetotarget_);
	virtual ~Arrive();
	SteeringOutput* getSteering();
};
#endif

