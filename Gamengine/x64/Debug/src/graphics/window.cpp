#include "window.h"


namespace gmJJ { namespace graphics {

	/*If the Method, members or variables are static. They should be declared in the namespace as a part of the class window*/


	/*Callbacks functions for the namespace graphics*/
	void windowResize(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(int height, int width, const char* name)
	{
		_name = name;
		_height = height;
		_width = width;
		if (!init())
			glfwTerminate();

		/*Initialization of the two Arrays*/
		for (size_t i = 0; i < MAX_KEYS; i++)
		{
			_keys[i] = false;
		}

		for (size_t i = 0; i < MAX_BUTTONS; i++)
		{
			_mouseButtons[i] = false;
		}
	}	
	
	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to intialize GLFW \n";
			return false;
		}

		_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
		if (!_window)
		{ 
			glfwTerminate();	
			std::cerr << "Failed to create the window \n";
			return false;
		}

		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, this);

		/*Calling back the windowResize method of the class*/
		glfwSetWindowSizeCallback(_window, windowResize);

		glfwSetKeyCallback(_window, key_callback);
		glfwSetMouseButtonCallback(_window, mouse_button_callback);
		glfwSetCursorPosCallback(_window, cursor_position_callback);

		/*Initializing GlEW framework after calling the contextcurrent function, otherwise is going to throw an error*/
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW \n";
			return false;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";

		return true; 
	}
	
	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	bool Window::isKeypressed(unsigned int keycode) const
	{
		 /*Check if the pressed key is in range*/
		if (keycode >= MAX_KEYS)
		{
			std::cerr << "The pressed key is not in range \n";
			return false;
		}

		return _keys[keycode];
	} 

	bool Window::isButtonPressed(unsigned int button) const
	{
		/*Check if the pressed key is in range*/
		if (button >= MAX_BUTTONS)
		{
			std::cerr << "The pressed button is not in range \n";
			return false;
		}

		return _mouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = _Mx;
		y = _My;
	}


	void Window::update() 
	{
		glfwPollEvents();
	//	glfwGetFramebufferSize(_window, &_width, &_height);
		glfwSwapBuffers(_window);
	}

	bool Window::close() const
	{
		return glfwWindowShouldClose(_window);
	}

	/*This is a callback function, it does not have to be define the class WINDOW to be called*/
	void windowResize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		/*I have to cast this window, because the function returns a void pointer */
		Window* window_key = (Window*) glfwGetWindowUserPointer(window);
		window_key->_keys[key] = (action != GLFW_RELEASE);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* window_button = (Window*) glfwGetWindowUserPointer(window);
		window_button->_mouseButtons[button] = (action != GLFW_RELEASE);
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* window_cursorpos = (Window*)glfwGetWindowUserPointer(window);
		window_cursorpos->_Mx = xpos;
		window_cursorpos->_My = ypos;
	}
}} 