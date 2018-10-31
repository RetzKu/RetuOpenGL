#include "renderable2d.h"

void Engine::Graphics::Renderable2D::AddMovement(Maths::vec3 Towards)
{
	position.x += Towards.x;
	position.y += Towards.y;
	position.z += Towards.z;
}

void Engine::Graphics::Renderable2D::UpdateSize()
{
	if (startsize.x > 1)
	{
		float tmp = size.x / 7;
		size.x = (startsize.x + 8) - _distancemoved;
		position.x = startposition.x + 2 - size.x / 2;
	}
	else if (startsize.y > 1)
	{
		float tmp = size.y / 7;
		size.y = (startsize.y + 8) - _distancemoved;
		position.y = startposition.y+2 - size.y / 2;
	}
}
