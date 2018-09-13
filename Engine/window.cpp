#include "window.h"
#include <iostream>

namespace Engine 
{
	namespace Graphics
	{
		//array johon voi laittaa nappeja
		bool Window::_keys[MAX_KEYS];
		bool Window::_keystate[MAX_KEYS];
		bool Window::_keytyped[MAX_KEYS];
		//array johon tulee hiiren napit &/ joystick
		bool Window::_buttons[MAX_BUTTONS];
		bool Window::_mouseclicked[MAX_BUTTONS];
		bool Window::_mousestate[MAX_BUTTONS];
		//mouse pos
		double Window::_mouseX;
		double Window::_mouseY;

		void WindowResize(GLFWwindow *window, int width, int height);

		//ikkunan konstruktori
		Window::Window(const char *title, int width, int height)
		{
			_title = title;
			_width = width;
			_height = height;
			if (!init())
			{
				glfwTerminate(); // tuhoaa ikkunan / dekonstruktori
			}
			for (int i = 0; i < MAX_KEYS; i++)
			{
				_keys[i] = false;
				_keystate[i] = false;
				_keytyped[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				_buttons[i] = false;
				_mousestate[i] = false;
				_mouseclicked[i] = false;
			}
		}
		// -||- dekonstruktori
		Window::~Window()
		{
			glfwTerminate();
		}		//Näppäimistö -> openGL:n callback funktio (osa inputtia)
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->_keys[key] = action != GLFW_RELEASE;

		}	
		//Hiirennapit -> openGL:n callback funktio (osa inputtia)
		void button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_buttons[button] = action != GLFW_RELEASE;
		}
		//Cursor position -> openGL:n callback funktio (osa inputtia)
		void cursor_callback(GLFWwindow* window, double MouseX, double MouseY)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_mouseX = MouseX;
			win->_mouseY = MouseY;
		}
		// varsinainen ikkunan teko
		bool Window::init()
		{
			if (!glfwInit()) // GLFW init check
			{
				std::cout << "GLFW Init Error!" << std::endl;
				return false;
			}
			//kutsutaan ikkunaa
			_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
			//ikkuna check,
			if (!_window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			//
			glfwMakeContextCurrent(_window);
			glfwSetWindowUserPointer(_window, this);
			glfwSetFramebufferSizeCallback(_window, WindowResize);
			//input hommia
			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, button_callback);
			glfwSetCursorPosCallback(_window, cursor_callback);
			// Otetaan Vsync pois päältä
			glfwSwapInterval(0);
			
			//glew (OpenGL Extension Wrangler Library) init check
			//GLEW on libi joka mahdollistaa cross-platform extensionit CPP filuihin
				if (glewInit() != GLEW_OK)
				{
						std::cout << "Could not initialize GLEW!" << std::endl;
						return false;
				}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//tulostaa openGL version, pitäisi tulla "4.5.0" jos on GLEW init onnistui
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;

		}
		//näppäimet
		bool Window::isKeyTyped(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
			{
				return false;
				std::cout << "Keycode is out of range!" << std::endl;
			}
			return _keytyped[keycode];
		}

		bool Window::isMouseButtonClicked(unsigned int button)
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
				std::cout << "Keycode is out of range!" << std::endl;
			}
			return _mouseclicked[button];
		}
		
		bool Window::isKeyPressed(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
			{
				return false;
				std::cout << "Keycode is out of range!" << std::endl;
			}
			return _keys[keycode];
		}
		//napit -> hiiri/joystick
		bool Window::isButtonPressed(unsigned int button)
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
				std::cout << "Buttons are out of range!" << std::endl;
			}
			return _buttons[button];
		}

		//mouse pos
		void Window::GetMousePosition(double& x, double& y)
		{
			x = _mouseX;
			y = _mouseY;
		}

		// clear metodi
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		//update metodi
		void Window::update()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				_keytyped[i] = _keys[i] && !_keystate[i];


			for (int i = 0; i < MAX_KEYS; i++)
				_keystate[i] = _keys[i];

			for (int i = 0; i < MAX_BUTTONS; i++)
				_mouseclicked[i] = _buttons[i] && !_mousestate[i];

			for (int i = 0; i < MAX_BUTTONS; i++)
				_keystate[i] = _buttons[i];
			// Error check
			GLenum error = glGetError();
			if(error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			//glfwGetFramebufferSize(_Window, &_Width, &_Height);
			glfwSwapBuffers(_window);
		}
		//window up check
		bool Window::closed() const
		{
			return glfwWindowShouldClose(_window);
		}
		//keskittää objektit ja skaalaa niitä (tässä tapauksessa neliö)
		void WindowResize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height); // (resize function) ** kokeile kommentoida rivi ja resize ikkunaa **
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_width = width;
			win->_height = height;
		}

	}
}