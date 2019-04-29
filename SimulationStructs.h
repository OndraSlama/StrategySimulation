#pragma once
#include <vector>
#include <algorithm> 


struct Vector{
	float x;
	float y;

	Vector(){
		x = 0;
		y = 0;
	}
	Vector(float _x, float _y){
		x = _x;
		y = _y;
	}

	float Length();
	Vector Normalize();
	Vector Sub(Vector vec);
	Vector Add(Vector vec);
	Vector Mult(float num);
	Vector Mult(Vector vec);
	Vector Div(float num);
	Vector Div(Vector vec);
	Vector Limit(float arg);
	Vector LimitMag(float arg);
	float Dist(Vector vec);
	float DotProduct(Vector vec);
	float AngleBetween(Vector vec);
	bool IsEqual(Vector vec);
	void Set(Vector vec);
	void Set(float x, float y);
};

