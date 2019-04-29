#include "Game.h"


Game::Game(b2Vec2 gravity){
	world.SetGravity(gravity);
	b2BodyDef bodyDef;
	groundBody = world.CreateBody(&bodyDef);
	field = Field(this, &world);
	ball = Ball(this, &world);
}




Game::~Game(){
}

void Game::Update(){
	world.Step(b2.timeStep, b2.velocityIterations, b2.positionIterations);
	world.ClearForces();

	ball.Update();
	//camera.Update();
	UpdateStrategyData();
	//redPlayer.Update();
	//bluePlayer.Update();

	CheckGoal();
	
}

void Game::CheckGoal(){
}

void Game::UpdateStrategyData(){
}
