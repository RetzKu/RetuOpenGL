#include "renderable2d.h"

void Engine::Graphics::Renderable2D::AddMovement(Maths::vec3 Towards)
{
	_position.x += Towards.x;
	_position.y += Towards.y;
	_position.z += Towards.z;
}

void Engine::Graphics::Renderable2D::UpdateSize()
{
	if (startsize.x > 1)
	{
		float tmp = _size.x / 7;
		_size.x = (startsize.x + 8) - _distancemoved;
		_position.x = startposition.x + 2 - _size.x / 2;
	}
	else if (startsize.y > 1)
	{
		float tmp = _size.y / 7;
		_size.y = (startsize.y + 8) - _distancemoved;
		_position.y = startposition.y+2 - _size.y / 2;
	}
}
