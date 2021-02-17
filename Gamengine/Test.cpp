#include"x64/Debug/src/graphics/window.h"

int main()
{
	gmJJ::graphics::Window window(800, 600, "GameEngineWindow");
	/*Combination for a blue screen that is about to run in the while-loop*/
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION); 

	while (!window.close())
	{
		std::cout << window.getHeight() << "," << window.getWidth() << "\n";
		window.clear();
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	return 0;
}