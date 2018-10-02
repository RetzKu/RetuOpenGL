#pragma once
#include "Maths.h"


using namespace Engine::Maths;

vec3 CalculateNormal(vec3 triangle[3])
{
	vec3 normal;

	normal = (triangle[1] - triangle[0]) * (triangle[2] - triangle[0]);

	return normal;
}

float CalculateDirectionVector(vec2 v1, vec2 v2)
{
	vec2 temp(0, 0);
	
	temp = v1 - v2;
	float dist = temp.x * temp.x + temp.y*temp.y;
	dist = sqrt(dist);

	return dist;
}
