#include "App.h"

#include <stdexcept>

void App::run()
{

	euclideEngine.setWindowSize(1200, 800);
	euclideEngine.setWindowName("Euclide");
	euclideEngine.createWindow();

	/*while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}

	glfwTerminate();*/

}

