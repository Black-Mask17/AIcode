#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "KinematicBody.h"

#include "Decision.h"
#include "PlayerInRangeDecision.h"
#include "Action.h"

class DecisionTreeNode;

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

	DecisionTreeNode* decider;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};
	// TODO add constructor that takes parameters for the body
	~Character() 
	{
		if (body) delete body;
	};
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	
	void setTexture(SDL_Texture* texture_) 
	{
		body->setTexture(texture_); 
	}

	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);
	void steerToSeekPlayer(SteeringOutput* steering);

	void setPos(Vec3 pos) {	body->setPos(pos);}

	Vec3 getPos() { return body->getPos(); }
	Vec3 getPlayerPos() { return scene->game->getPlayer()->getPos(); }
};

#endif

