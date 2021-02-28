#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

namespace gmJJ { namespace graphics {
	
#define MAX_KEYS 1024
#define MAX_BUTTONS 34
	
	class Window 
	{
	private:
		int _height;
		int _width;
		const char *_name;
		GLFWwindow *_window;
		bool _closed;

		bool _keys[MAX_KEYS];
		bool _mouseButtons[MAX_BUTTONS];
		/*For the movements coordinates*/
		double _Mx, _My;

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	public:

		Window(int height, int width, const char* name);
		~Window();
		void clear() const;
		void update();
		bool close() const;

		inline int getWidth() const { return _width; }
		inline int getHeight() const  { return _height; }

		bool isKeypressed(unsigned int keycode) const;	
		bool isButtonPressed(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;
	};
}}