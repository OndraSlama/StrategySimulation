#include "B2.h"



B2::B2(){
	// determine field dimensions
	float fieldWidthPxl = windowWidth * fillRatio;
	float fieldHeightPxl = windowHeight * fillRatio;
	if (fieldWidthPxl * fieldWidthPxl * (boardHeight / boardWidth) < (fieldHeightPxl * fieldHeightPxl * (boardWidth / boardHeight))){
		fieldHeightPxl = fieldWidthPxl * (boardHeight / boardWidth);
	} else{
		fieldWidthPxl = fieldHeightPxl * (boardWidth / boardHeight);
	}

	pixelScale = fieldWidthPxl / u2wScale(boardWidth);
	b2Vec2 temp = p2w(Vector(windowWidth / 2 - fieldWidthPxl / 2, windowHeight / 2));
	unitsOffsetX = temp.x;
	unitsOffsetY = temp.y;
}


B2::~B2(){
}

void B2::setPosition(Vector pos, b2Body * body){
	b2Vec2 worldPos = u2w(pos);
	body->SetTransform(worldPos, body->GetAngle());
}

void B2::setPosition(b2Vec2 pos, b2Body * body){
	body->SetTransform(pos, body->GetAngle());
}

void B2::setVelocity(Vector vel, b2Body * body){
	b2Vec2 worldVel = u2wScale(vel.Mult(1000));

	b2Vec2 impulse = (worldVel - body->GetLinearVelocity());
	impulse *= body->GetMass();
	body->ApplyLinearImpulse(impulse, body->GetPosition(), true);
}

void B2::setVelocity(b2Vec2 vel, b2Body * body){
	b2Vec2 impulse = (vel - body->GetLinearVelocity());
	impulse *= body->GetMass();
	body->ApplyLinearImpulse(impulse, body->GetPosition(), true);
}


b2Vec2 B2::p2w(Vector pos){
	return b2Vec2(pos.x / pixelScale, pos.y / pixelScale);
}

float B2::p2w(float arg){
	return arg / pixelScale;
}

Vector B2::w2p(b2Vec2 pos){
	return Vector(pos.x * pixelScale, pos.y * pixelScale);
}

float B2::w2p(float arg){
	return arg * pixelScale;
}


b2Vec2 B2::u2w(Vector pos){
	return b2Vec2(pos.x / unitsScaleX + unitsOffsetX, pos.y / unitsScaleY + unitsOffsetY);
}

b2Vec2 B2::u2wScale(Vector pos){
	return b2Vec2(pos.x / unitsScaleX, pos.y / unitsScaleY);
}

float B2::u2wScale(float arg){
	return arg / unitsScaleX;
}

Vector B2::w2u(b2Vec2 pos){
	return Vector((pos.x - unitsOffsetX) * unitsScaleX, (pos.y - unitsOffsetY) * unitsScaleY);
}

Vector B2::w2uScale(b2Vec2 pos){
	return Vector(pos.x * unitsScaleX, pos.y * unitsScaleY);
}

float B2::w2uScale(float pos){
	return pos * abs(unitsScaleX);
}

Vector B2::u2p(Vector pos){
	return w2p(u2w(pos));
}

Vector B2::u2pScale(Vector pos){
	return w2p(u2wScale(pos));
}

float B2::u2pScale(float arg){
	return w2p(u2wScale(arg));
}
