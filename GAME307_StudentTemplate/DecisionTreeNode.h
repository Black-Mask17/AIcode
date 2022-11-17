#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

//#include "Character.h"

class Character;

class DecisionTreeNode {

private:

protected:
	Character* owner;

public:
	virtual void makeDecision() = 0;

};

#endif