#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/gl.h>

static const char* s_VertexSource = R"---(
#version 330 core
layout (location = 0) in vec2 vert_Position;

void main(void)
{
	gl_Position = vec4(vert_Position,0.0 ,1.0 );
}
)---";

static const char* s_FragmentSource = R"---(
#version 330 core
layout (location = 0) out vec4 out_Color;

void main(void)
{
	out_Color = vec4(1.0,0.5,0.0,1.0);
}
)---";
int main() {
	std::cout << "master~" << std::endl;
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 800, "master~", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(&glfwGetProcAddress);

	float vert[] = {-.5, -.5f, .5f, -.5f, 0, .5f};
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//OwO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLuint vertShader, fragShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertShader, 1, &s_VertexSource, nullptr);
	glShaderSource(fragShader, 1, &s_FragmentSource, nullptr);
	
	glCompileShader(vertShader);
	glCompileShader(fragShader);//happy fox noises
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);

	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glUseProgram(program);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			glClearColor(((float)rand() / (float)RAND_MAX), .8f, .8f, 1.0f);
		}
		else {
			glClearColor(((float)rand() / (float)RAND_MAX), .0f, .0f, 1.0f);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);
	glfwTerminate();
}