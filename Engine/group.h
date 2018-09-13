#pragma once


#include "renderable2d.h"


namespace Engine { namespace Graphics {
	

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> _renderables;
		Maths::mat4 _transformationMatrix;
		float DistanceCalculator = 0;
	public:
		Group(const Maths::mat4& tranform);
		~Group();
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer) const override;
		void AddFromOrigin(Renderable2D* renderable, Maths::vec3 Towards)
		{
			renderable->AddMovement(Towards);
			_renderables.push_back(renderable);
		}
		void SetMatrix(Maths::mat4 NewMatrix) 
		{
			float AddedX = NewMatrix.columns[3].x - _transformationMatrix.columns[3].x;
			float AddedY = NewMatrix.columns[3].y - _transformationMatrix.columns[3].y;
			DistanceCalculator += abs(AddedX) + abs(AddedY);
			if (_renderables.size() > 0)
			{
				for (Renderable2D* renderable : _renderables)
				{
					float DistanceMoved = renderable->AddDistance(abs(AddedX) + abs(AddedY));
					renderable->UpdateSize();
					if (DistanceMoved >= 10 || DistanceMoved <= -10)
					{
						ClearRenderable(renderable);
						break;
					}
				}
			}
			else
			{
				DistanceCalculator = 0;
			}
			_transformationMatrix = NewMatrix;
		}
		void Rotate(float Degrees, Maths::vec3 Axis);
		void RotateAt(Maths::vec2 Point, float Degrees, Maths::vec2 Center);
		Maths::vec2 GetCenter(Maths::vec3 Position,Maths::vec2 Size);
		Maths::mat4* GetMatrix() { return &_transformationMatrix; }
		bool CheckCollisionWithPoint(Maths::vec2 Point);
		bool AABBCollisionCheck(Maths::mat4 TargetMatrix, Maths::vec3 TargetPos, Maths::vec2 TargetSize);
		void ClearRenderable(Renderable2D* renderable);
	};
	
}}