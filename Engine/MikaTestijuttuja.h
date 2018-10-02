#include "window.h"
#include <windows.h>
#include <iostream>
#include "Maths.h"
#include <chrono>
#include "fileutils.h"
#include "Shader.h"
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "renderable2d.h"
#include "BatchRenderer2D.h"
#include "sprite.h"
#include <thread>
#include "group.h"

using namespace Engine;
using namespace Graphics;
using namespace Maths;

#define SCREENWIDTH 960
#define SCREENHEIGHT 540

class TestClass
{
public:
	TestClass(Window* WindowObject,Shader* ShaderObject)
	{
		this->ShaderObject = ShaderObject;
		this->WindowObject = WindowObject;
		this->CameraCoordinates = vec2(0.0f, 0.0f);
		DefineAspectRatio();
	}
	vec2 get_relativeMSCoord(double x, double y);
	double get_relative_width(double x);
	double get_relavive_height(double y);
	double get_correct_width(double x);
	double get_correct_height(double y);
	void GetCameraMovement();
	vec2 MouseWorldLocation();
	vec2 MouseUILocation();
	void SetUniforMat4(std::string UniformName, mat4 Ortho) { ShaderObject->setUniformMat4(UniformName.c_str(), Ortho); }
	void ButtonCooldownThread(bool* Cooldown);
	void ResetCooldown() { Cooldown = false; }
	void RotatePlayer(Group* PlayerGroup, vec2 At, vec2 Center);
	void RotatePlayerTimed(Group* PlayerGroup, vec2 At, vec2 Center);
	void DefineAspectRatio()
	{
		float ratio = (float)SCREENHEIGHT / (float)SCREENWIDTH;
		if (ratio == 0.5625f)
		{
			this->AspectRatio.x = 16;
			this->AspectRatio.y = 9;
		}
		std::cout << "\nAspectRatio is " << this->AspectRatio.x << ":" << this->AspectRatio.y << "\n";
	}
	vec2 AspectRatio;
private:
	Shader* ShaderObject;
	Window* WindowObject;
	vec2 CameraCoordinates;
	float scale = 1;
	bool Cooldown;
	float time;
};

//TestClassin funktiot määritelty alapuolella

vec2 TestClass::get_relativeMSCoord(double x, double y) //palauttaa vec2 objektin joka on -1/1 väliltä
{
	float relative_x = x - SCREENWIDTH / 2;
	relative_x = relative_x / (SCREENWIDTH / 2);
	float relative_y = y - SCREENHEIGHT / 2;
	relative_y = relative_y / (SCREENHEIGHT / 2);
	return vec2(relative_x, relative_y);
}
double TestClass::get_relative_width(double x) //osaatte varmaan päätellä
{
	float relative_x = x - SCREENWIDTH / 2;
	relative_x = relative_x / (SCREENWIDTH / 2);
	return relative_x;
}
double TestClass::get_relavive_height(double y)//osaatte varmaan päätellä x2
{
	float relative_y = y - SCREENHEIGHT / 2;
	relative_y = relative_y / (SCREENHEIGHT / 2);
	return -relative_y;
}
double TestClass::get_correct_width(double x)
{
	float tmp = SCREENWIDTH / 2;
	tmp = x / tmp;
	return tmp / 2;
}
double TestClass::get_correct_height(double y)
{
	float tmp = SCREENHEIGHT / 2;
	tmp = y / tmp;
	return tmp / 2;
}
void TestClass::ButtonCooldownThread(bool* Cooldown) //tämä on esimerkki siitä kuinka tehdään threadille sopiva funktio joka pystyy muuttamaan classin arvoa. Rakenna std::thread(&class::funktio, *this, parameters).detatch()
{ 
	*Cooldown = true;
	std::cout << "went to thread";
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10ms);
	*Cooldown = false;
}

vec2 TestClass::MouseUILocation()
{
	double x, y;
	WindowObject->GetMousePosition(x, y);
	//std::cout << "\nSCREENCOORDINATES: X: " << x << " Y: " << y;
	return vec2(x, y);
}

vec2 TestClass::MouseWorldLocation()
{
	double x, y;
	WindowObject->GetMousePosition(x, y);
	x += CameraCoordinates.x*30;
	y -= CameraCoordinates.y*30; //no idea why cameracoordinates are 30 times smaller than screencoordinates but over all this give correct world coordinates even when moving camera
	//std::cout << "\nWORLD COORDINATES: X: " << x << " Y: " << y;
	return vec2(x, y);
}

void TestClass::GetCameraMovement()
{
	time += 0.1f;
	for (int i = 60; i < 95; i++)
	{
		if (WindowObject->isKeyPressed(i))
		{
			switch (i)
			{
			case GLFW_KEY_A:
				CameraCoordinates.x -= 0.01f;
				break;
			case GLFW_KEY_W:
				CameraCoordinates.y += 0.01f;
				break;
			case GLFW_KEY_D:
				CameraCoordinates.x += 0.01f;
				break;
			case GLFW_KEY_S:
				CameraCoordinates.y -= 0.01f;
				break;
			case GLFW_KEY_Q:
				scale += 0.01f;
				break;
			case GLFW_KEY_E:
				if (scale > 0.01f)
				{
					scale -= 0.01f;
				}
				break;
			default:
				break;
			}
		}
	}

	Maths::mat4 ortho = Maths::mat4::identity();
	ortho = ortho.translation(vec3{CameraCoordinates.x,CameraCoordinates.y,0}) * ortho.scale(vec3{ 0.1f*scale,0.1f*scale,0.1f*scale });
	ShaderObject->enable();
	ShaderObject->setUniformMat4("vw_matrix", ortho);
	ShaderObject->disable();
}

void TestClass::RotatePlayer(Group* PlayerGroup, vec2 At, vec2 Center)
{
	for (int i = 60; i < 95; i++)
	{
		if (WindowObject->isKeyPressed(i))
		{
			switch (i)
			{
			case GLFW_KEY_A:
				PlayerGroup->RotateAt(At, 0.05f, Center);
				break;
			case GLFW_KEY_D:
				PlayerGroup->RotateAt(At, -0.05f, Center);
				break;
			default:
				break;
			}
		}
	}
	
}
void TestClass::RotatePlayerTimed(Group* PlayerGroup, vec2 At, vec2 Center)
{
	PlayerGroup->RotateAt(At, -0.00175f, Center);
}
