#include "Field.h"



Field::Field(){	
}


Field::Field(Game * _game, b2World * _world){
	game = _game;
	world = _world;

	// Define body.	
	b2BodyDef fieldBodyDef;
	b2Vec2 groundPos = b2.u2w(Vector(0, 0));
	fieldBodyDef.position.Set(groundPos.x, groundPos.y);
	body = world->CreateBody(&fieldBodyDef);

	b2EdgeShape shape;

	b2FixtureDef fieldFixtureDef;
	fieldFixtureDef.shape = &shape;
	fieldFixtureDef.density = 0.0f;
	fieldFixtureDef.restitution = 0.2;

	// Left vertical
	shape.Set(b2.u2wScale(Vector(0, boardHeight / 2)), b2.u2wScale(Vector(0, goalSize / 2)));
	body->CreateFixture(&fieldFixtureDef);

	shape.Set(b2.u2wScale(Vector(0, -goalSize / 2)), b2.u2wScale(Vector(0, -boardHeight / 2)));
	body->CreateFixture(&fieldFixtureDef);

	shape.Set(b2.u2wScale(Vector(0, -boardHeight / 2)), b2.u2wScale(Vector(boardWidth, -boardHeight / 2)));
	body->CreateFixture(&fieldFixtureDef);

	shape.Set(b2.u2wScale(Vector(boardWidth, -boardHeight / 2)), b2.u2wScale(Vector(boardWidth, -goalSize / 2)));
	body->CreateFixture(&fieldFixtureDef);

	shape.Set(b2.u2wScale(Vector(boardWidth, goalSize / 2)), b2.u2wScale(Vector(boardWidth, boardHeight / 2)));
	body->CreateFixture(&fieldFixtureDef);

	shape.Set(b2.u2wScale(Vector(boardWidth, boardHeight / 2)), b2.u2wScale(Vector(0, boardHeight / 2)));
	body->CreateFixture(&fieldFixtureDef);
}

Field::~Field(){
}
