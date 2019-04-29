#pragma once
#include <Box2D/Box2D.h>
#include "SimulationStructs.h"
#include "Constants.h"

class B2{
public:
	B2();
	~B2();

	// Transformation functions
	void setPosition(Vector pos, b2Body* body);
	void setVelocity(Vector vel, b2Body* body);

	void setPosition(b2Vec2 pos, b2Body* body);
	void setVelocity(b2Vec2 vel, b2Body* body);

	b2Vec2 p2w(Vector pos);
	float p2w(float arg);
	//b2Vec2 p2w(float x, float y);

	Vector w2p(b2Vec2 pos);
	float w2p(float arg);
	//Vector w2p(float x, float y);
	
	b2Vec2 u2w(Vector pos);
	b2Vec2 u2wScale(Vector pos);
	float u2wScale(float arg);

	//float u2w(float arg)

	Vector w2u(b2Vec2 pos);
	Vector w2uScale(b2Vec2 pos);
	float w2uScale(float pos);

	Vector u2p(Vector pos);
	Vector u2pScale(Vector pos);
	float u2pScale(float arg);
		

	float pixelScale = 100;
	float unitsScaleX = 1000;
	float unitsScaleY = -1000;
	float unitsOffsetX = 0;
	float unitsOffsetY = 0;

	float32 timeStep = 1.0f / (float)simulationFPS;
	int32 velocityIterations = 3;
	int32 positionIterations = 2;
};

