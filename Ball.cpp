#include "Ball.h"
#include "Game.h"


Ball::Ball(Game * _game, b2World * _world){
	game = _game;
	world = _world;

	// Create body
	b2BodyDef ballBodyDef;
	b2Vec2 ballPos = b2.u2w(Vector(boardWidth / 2, 0));
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(ballPos.x, ballPos.y);
	ballBodyDef.linearDamping = 0.15;
	body = world->CreateBody(&ballBodyDef);

	b2CircleShape shape;

	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &shape;
	ballFixtureDef.density = .011f;
	ballFixtureDef.friction = 0.1f;
	ballFixtureDef.restitution = 0.1;
	ballFixtureDef.filter.maskBits = 65535;
	ballFixtureDef.filter.categoryBits = 1;

	shape.m_radius = b2.u2wScale(ballRadius);
	body->CreateFixture(&ballFixtureDef);

	// Mouse joint definition
	mouseJointDef.bodyA = game->groundBody;
	mouseJointDef.bodyB = body;
	mouseJointDef.target = body->GetPosition();
	mouseJointDef.maxForce = 1000.0f;
	mouseJointDef.dampingRatio = 0.5;
	body->SetAwake(true);

	mouseJointActive = false;

	b2.setPosition(Vector(boardWidth/2, -boardHeight/2 + ballRadius), body);
	b2.setVelocity(Vector(randInterval(-2, 2), 10), body);
}

Ball::Ball(){
}

void Ball::Update(){
	position = b2.w2u(body->GetPosition());
	velocity = b2.w2uScale(body->GetLinearVelocity());
	velocity = velocity.Mult(0.001);

	angle = body->GetAngle();
	angularVelocity = body->GetAngularVelocity();

	mass = body->GetMass();
	//body->SetAwake(1);

	if (mouseJointActive){
		mouseJoint->SetTarget(b2.p2w(*mousePos));
	}
	ApplyForces();
}

void Ball::ApplyForces(){

	// Friction
	float magnitude = 1;
	float max = .2;
	float velMag = velocity.Length();
	Vector force = velocity.Normalize();
	force = force.Mult(velMag * -magnitude).LimitMag(max);
	b2Vec2 finalForce = b2.u2wScale(force);
	body->ApplyForce(finalForce, body->GetPosition(), true);

	//// Random stuff
	//let softness = 3000
	//	magnitude = 1
	//	force.set(map(noise(this.pos.x / softness, this.pos.y / softness), 0, 1, -magnitude, magnitude),
	//		map(noise(this.pos.x / softness + 1000, this.pos.y / softness + 1000), 0, 1, -magnitude, magnitude));
	//if (velMag < 300) force.limit(0.1);
	//this.body.ApplyForce(b2.u2w(force, "SCALE"), b2.u2w(position));
	

	// Blow
	if (velMag < 0.1){
		timer += b2.timeStep;
	} else{
		timer = 0;
	}
	if (timer > 3){
		timer = 0;
		Vector blowSpeed = Vector(-sgn(position.x - boardWidth / 2) * randInterval(0, 1), -sgn(position.y) * randInterval(0, 1));
		b2.setVelocity(blowSpeed, body);
	}

	// Edge slopes
	Vector edgeForce;
	float edgeForceMag = 40;
	if (abs(position.y) > (boardHeight / 2 - slopeSize)){
		edgeForce = Vector(0, -sgn(position.y) * edgeForceMag);
		body->ApplyForce(b2.u2wScale(edgeForce), b2.u2w(position), true);
	}

	// Corner slopes
	float dy = boardHeight / 2 - goalSize / 2;
	float dx = cornerSlopeReach;
	float offset = goalSize / 2;
	float xSide = sgn(position.x - boardWidth / 2);
	float ySide = sgn(position.y);
	float xSlopeForce = 9;
	float ySlopeForce = 5;

		// Left 
	if (position.y > (dy / dx) * position.x + offset){
		edgeForce = Vector(-xSide * xSlopeForce, -ySide * ySlopeForce);
		body->ApplyForce(b2.u2wScale(edgeForce), b2.u2w(position), true);
	}
	if (position.y < -(dy / dx) * position.x - offset){
		edgeForce = Vector(-xSide * xSlopeForce, -ySide * ySlopeForce);
		body->ApplyForce(b2.u2wScale(edgeForce), b2.u2w(position), true);
	}

		// Right
	if (position.y > -(dy / dx) * (position.x - boardWidth) + offset){
		edgeForce = Vector(-xSide * xSlopeForce, -ySide * ySlopeForce);
		body->ApplyForce(b2.u2wScale(edgeForce), b2.u2w(position), true);
	}
	if (position.y < (dy / dx) * (position.x - boardWidth) - offset){
		edgeForce = Vector(-xSide * xSlopeForce, -ySide * ySlopeForce);
		body->ApplyForce(b2.u2wScale(edgeForce), b2.u2w(position), true);
	}
}



void Ball::BindToTarget(){
	if (!mouseJointActive){
		mouseJointDef.target = body->GetPosition();
		mouseJoint = (b2MouseJoint*)world->CreateJoint(&mouseJointDef);
		mouseJointActive = true;
	}
}

void Ball::Unbind(){
	if (mouseJointActive){
		game->world.DestroyJoint(mouseJoint);
		mouseJointActive = false;
	}
}


Ball::~Ball(){

}


