#include "window.h"
#include <windows.h>
#include <iostream>
#include "Maths.h"
#include "fileutils.h"
#include "Shader.h"
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "renderer2d.h"
#include "renderable2d.h"
#include "simple2drenderer.h"
#include "static_sprite.h"
#include <chrono>
#include "BatchRenderer2D.h"
#include "sprite.h"
#include <time.h>
#include "timer.h"
#include <thread>
#include "MikaTestijuttuja.h"
#include "tilelayer.h"
#include "group.h"
#include "Label.h"
#include "texture.h"
#include <stdio.h>

#include "PhysicsObject.h"

// Jos haluat printit p‰‰lle, t‰ss‰ 1, jos et valitse 0
#define DEBUG 1
#if DEBUG
	#define CONSOLE(x) std::cout << x
	#define CONSOLEND(x) std::cout << x << std::endl
#else
	#define CONSOLE(x)
	#define CONSOLEND(x)
#endif

//Constructs GLFW Window publicly
Window* window = new Window("Engine", SCREENWIDTH, SCREENHEIGHT);

class Game
{
public:
	Game() {}
	~Game()
	{
		if (Layers.size() > 0)
		{
			for (TileLayer* LayerObject : Layers)
			{
				delete LayerObject;
			}
			Layers.clear();
		}
		if (Groups.size() > 0)
		{
			for (Group* GroupObject : Groups)
			{
				delete GroupObject;
			}
			Groups.clear();
		}
		delete shader;
		delete ControlFunktionality;
	}

	/*USED CLASSES FOR GAMEOBJECT*/
	Shader* shader;
	TestClass* ControlFunktionality;
	std::vector<TileLayer*> Layers;
	std::vector<Group*> Groups;
	FileUtils utils;


	/*FUNCTIONS THAT CONTROL UPDATES*/
	void RenderLayers()
	{
		if (Layers.size() > 0)
		{
			for (Layer* RenderableLayers : Layers)
			{
				RenderableLayers->render();
			}
		}
	}
};

/*GAME LOOP FUNKTIONS*/
void InitScene();
int SceneLoop(Game* GameObject);

#if 1
#endif
int main()
{
#define SCREENWIDTH 960
#define SCREENHEIGHT 540

	using namespace Engine;
	using namespace Graphics;
	using namespace Maths;

	FileUtils utils;
	// Asetetaan ikkunan parametrit

	std::cout << "Window Width: " << window->getWidth() << +" Height: " << window->getHeight() << std::endl;
	InitScene();
	return 0;
}

void InitScene()
{
	Game* GameStruct = new Game();
	GameStruct->shader = new Shader("basic.vert", "basic.frag");
	GameStruct->shader->enable();
	// Heitet‰‰n shadereill‰ valotusta
	GameStruct->shader->setUniformMat2f("light_pos", vec2(4.0f, 1.5f));
	// Tehd‰‰n layeri
	GameStruct->Layers.push_back(new TileLayer(GameStruct->shader));
	GameStruct->ControlFunktionality = new TestClass(window, GameStruct->shader);
	GameStruct->ControlFunktionality->GetCameraMovement();
	SceneLoop(GameStruct);
}
int SceneLoop(Game* GameObject)
{
	bool Running = true;

	/*Updatable Variables*/
	Maths::vec2 MousePos;

	/*Background color*/
	glClearColor(0,0,0, 1);

	/*given translation is groups point of origin*/
	//Group* LeftColliders = new Group(Maths::mat4::translation(Maths::vec3(10.0f, 0.0f, 0.0f)));

	/*Adding player to layer within main Gameobject class*/

	std::chrono::time_point<std::chrono::system_clock> DeltaTime = std::chrono::system_clock::now();//start point for deltatime;
	float TimeInteval = (int)((1.0f / 82.0f) * 1000);//giving deltatime tickrate; this is good until hitting under 60fps; ;

	GameObject->Layers[0]->add(new PhysicsObject(0, 10, 1, 1, new Texture("Pekka2.bmp"), 100));
	while (!window->closed())
	{
		/*Main Loop*/
		window->clear();


		GameObject->RenderLayers(); //Renderoi kaikki layerit jotka on annettu Gameobject classille
		window->update(); //ikkunan swap
		//}

	}
	return 0;
}
