// LIFE CHECK:
 #include <iostream>

//int main() {
//	std::cout << "Hello" << std::endl;
//	std::cin.get();
//}

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
	// Sample code from GLFW --->
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello OpenGl", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Print out version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// This needs to happen after we have a valid context, see more in http://glew.sourceforge.net/basic.html
	if (glewInit() != GLEW_OK)
		std::cout << "Error on glewInit()" << std::endl;
	
	// Define three vertice positions
	float positions[6] = {
		-0.5f, -0.5f, // Each line represents a vertex position (x and y values)
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	// Pass in the memory address of an unsigned int (this will be the return value)
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//// Legacy GL to test all is up and running
		//glBegin(GL_TRIANGLES);
		//glVertex2d(-0.5f, -0.5f);
		//glVertex2d(0.0f, 0.5f);
		//glVertex2d(0.5f, -0.5f);
		//glEnd();

		// Draws from the glBindBuffer!
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 3, ) This is with index buffers


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}