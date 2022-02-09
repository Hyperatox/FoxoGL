#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/gl.h>

int main() {
	std::cout << "master~" << std::endl;
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 800, "master~", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(&glfwGetProcAddress);

	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//glfwSetWindowIcon(window, );
		glClearColor(((float)rand() / (float)RAND_MAX), .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
	}


	glfwTerminate();
}