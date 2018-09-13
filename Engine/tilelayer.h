#pragma once

#include "layer.h"
#include "BatchRenderer2D.h"

namespace Engine {
	namespace Graphics {
	
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};
	
}}