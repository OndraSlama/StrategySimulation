class Game;
#pragma once
#include "Base.h"

class Field{
public:
	b2Body* body;
	Game* game;
	b2World* world;

	Field(Game* _game, b2World* _world);
	Field();
	~Field();
};

