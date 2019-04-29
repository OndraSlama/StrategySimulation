#pragma once
#include "Base.h"
#include "Field.h"
#include "Ball.h"
class Game{
public:	

	b2World world = b2World(b2Vec2(0.0f, 0.0f));
	b2Body* groundBody;
	Field field;
	Ball ball;
	

	//world.SetContactListener(new MyListener);

	/*redPlayer = new Player(this, "red");
	bluePlayer = new Player(this, "blue");
	ball = new Ball(this);
	field = new Field(this);
	camera = new Camera(this, fps);
	redPlayer.setStrategy();
	bluePlayer.setStrategy();*/

	Game(b2Vec2 gravity = b2Vec2(0.0f, 0.0f));
	~Game();

	void Update();
	void CheckGoal();
	void UpdateStrategyData();
};

