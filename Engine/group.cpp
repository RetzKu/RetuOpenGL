#include "group.h"


namespace Engine { namespace Graphics {


	Group::Group(const Maths::mat4& transform)
		: _transformationMatrix(transform)
	{		
	}
	
	Group::~Group()
	{
		for (int i = 0; i < _renderables.size(); i++)
		{
			delete _renderables[i];
		}
	}

	void Group::add(Renderable2D* renderable)
	{
		_renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const
	{
		renderer->push(_transformationMatrix);
		for(const Renderable2D* renderable : _renderables)
		{
			renderable->submit(renderer);
		}
		renderer->pop();
	}
	void Group::Rotate(float Degrees, Maths::vec3 Axis)
	{
		_transformationMatrix = _transformationMatrix.rotation(Degrees, Axis);
	}
	void Group::RotateAt(Maths::vec2 Point, float Degrees, Maths::vec2 Center)
	{
		float x = _transformationMatrix.columns[3].x;
		float y = _transformationMatrix.columns[3].y;
		float s = sin(Degrees);
		float c = cos(Degrees);

		x -= Point.x - (Center.x /2);
		y -= Point.y - (Center.y /2); 

		float newx = x * c - y * s;
		float newy = x * s + y * c;
	
		_transformationMatrix.columns[3].x = newx + Point.x - (Center.x /2);
		_transformationMatrix.columns[3].y = newy + Point.y - (Center.y /2);

	}
	Maths::vec2 Group::GetCenter(Maths::vec3 Position, Maths::vec2 Size)
	{
		float x, y;
		x = Size.x / 2;
		y = Size.y / 2;
		x += Position.x + _transformationMatrix.columns[3].x;
		y += Position.y + _transformationMatrix.columns[3].y;
		return Maths::vec2(x, y);
	}
	bool Group::CheckCollisionWithPoint(Maths::vec2 Point)
	{
		for (const Renderable2D* renderable : _renderables)
		{
			if (renderable->IsCollider() == true)
			{

				Maths::vec2 A1;
				A1.x = renderable->getPosition().x + _transformationMatrix.columns[3].x;
				A1.y = renderable->getPosition().y + _transformationMatrix.columns[3].y;
				
				Maths::vec2 A2 = A1;
				A2.x += abs(renderable->getSize().x);
				A2.y += abs(renderable->getSize().y);
				
				if (A1.x <= Point.x && A2.x >= Point.x) 
				{
					if (A1.y <= Point.y && A2.y >= Point.y)
					{
						std::cout << "COLLIDERUU\n";
						return true;
					}
				}
			}
		}
		return false;
	}
	bool Group::AABBCollisionCheck(Maths::mat4 TargetMatrix, Maths::vec3 TargetPos, Maths::vec2 TargetSize)
	{
		for (const Renderable2D* renderable : _renderables)
		{
			if (renderable->IsCollider() == true)
			{
				Maths::vec2 A1; //A1 on Pelaajan boxin eka nurkka
				A1.x = TargetMatrix.columns[3].x + TargetPos.x;
				A1.y = TargetMatrix.columns[3].y + TargetPos.y;

				Maths::vec2 A2; //A2 on Pelaajan boxin toka nurkka
				A2.x = A1.x + TargetSize.x;
				A2.y = A1.y + TargetSize.y;

				Maths::vec2 B1;
				B1.x = _transformationMatrix.columns[3].x + renderable->getPosition().x;
				B1.y = _transformationMatrix.columns[3].y + renderable->getPosition().y;

				Maths::vec2 B2;
				B2.x = B1.x + renderable->getSize().x;
				B2.y = B1.y + renderable->getSize().y;

				if ((A2.x <= B1.x || B2.x <= A1.x) == false)
				{
					if ((A2.y <= B1.y || B2.y <= A1.y) == false)
					{
						return true;
						std::cout << "COLLIDERU";
					}
				}
			}
		}
		return false;
	}
	void Group::ClearRenderable(Renderable2D* Renderable)
	{
		int index = std::distance(_renderables.begin(),std::find(_renderables.begin(), _renderables.end(), Renderable));
		delete _renderables[index];
		_renderables.erase(_renderables.begin() + index);
	}
}}