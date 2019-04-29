#include "SimulationStructs.h"

float Vector::Length(){
	return sqrt(x*x + y * y);
}

Vector Vector::Normalize(){
	float vecLength = Length();
	if (vecLength != 0){
		return Div(Length());
	} else{
		return Vector(0, 0);
	}
}

Vector Vector::Sub(Vector vec){
	return Vector(x - vec.x, y - vec.y);
}

Vector Vector::Add(Vector vec){
	return Vector(x + vec.x, y + vec.y);
}

Vector Vector::Mult(float num){
	return Vector(x * num, y * num);
}

Vector Vector::Mult(Vector vec){
	return Vector(x * vec.x, y * vec.y);
}

Vector Vector::Div(float num){
	if (num != 0){
		return Vector(x / num, y / num);
	} else{
		return Vector(0, 0);
	}
}

Vector Vector::Div(Vector vec){
	return Vector(x / vec.x, y / vec.y);
}

Vector Vector::Limit(float arg){
	return Vector(std::min(x, arg), std::min(y, arg));
}

Vector Vector::LimitMag(float arg){
	if (this->Length() > arg){
		return this->Normalize().Mult(arg);
	} else{
		return *this;
	}
}

float Vector::Dist(Vector vec){
	return Sub(vec).Length();
}

float Vector::DotProduct(Vector vec){
	return x * vec.x + y * vec.y;
}

float Vector::AngleBetween(Vector vec){
	return acos(DotProduct(vec) / (Length() * vec.Length()));
}

bool Vector::IsEqual(Vector vec){
	if (x == vec.x & y == vec.y) return true;
	return false;
}

void Vector::Set(Vector vec){
	x = vec.x;
	y = vec.y;
}

void Vector::Set(float x, float y){
	x = x;
	y = y;
}


