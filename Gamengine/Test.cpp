#include"x64/Debug/src/graphics/window.h"

int main()
{
	gmJJ::graphics::Window window(800, 600, "GameEngineWindow");
	/*Combination for a blue screen that is about to run in the while-loop*/
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint var;
	glGenVertexArrays(1, &var);
	glBindVertexArray(var);


	while (!window.close())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		std::cout << x<<", " << y << std::endl;
#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
	return 0;
}