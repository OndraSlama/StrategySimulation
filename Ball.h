class Game;
#pragma once
#include "Base.h"
#include <math.h>

class Ball{
public:

	//Box2D
	b2Body* body;
	Game* game;
	b2World* world;
	b2MouseJoint* mouseJoint;
	b2MouseJointDef mouseJointDef;
	bool mouseJointActive;

	//Mouse
	Vector* mousePos;

	// States
	Vector position;
	Vector velocity;
	float angle;
	float angularVelocity;
	float mass;
	float timer = 0;


	Ball(Game* _game, b2World* _world);
	Ball();
	~Ball();

	void Update();
	void ApplyForces();
	void BindToTarget();
	void Unbind();
};

