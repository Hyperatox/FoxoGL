#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#if defined(_MSC_VER)
#	include <Windows.h>
#endif

static const char* s_VertexSource = R"---(
#version 330 core
layout (location = 0) in vec2 vert_Position;
layout (location = 1) in vec3 vert_Color;

out vec3 frag_Color;

void main(void)
{
	gl_Position = vec4(vert_Position, 0.0, 1.0);
	frag_Color = vert_Color;
}
)---";

static const char* s_FragmentSource = R"---(
#version 330 core
layout (location = 0) out vec4 out_Color;

in vec3 frag_Color;

uniform vec3 u_Color;

void main(void)
{
	out_Color = vec4(frag_Color, 1.0);
}
)---";

void CheckShaderError(GLuint shader) noexcept {
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &status);

		GLchar* message = new GLchar[status];
		glGetShaderInfoLog(shader, status , &status, message);
		std::cerr << message << std::endl;
#if defined(_MSC_VER)
		if (IsDebuggerPresent())
			__debugbreak();
#endif
		delete[] message;
	}
}
void CheckProgramError(GLuint program) noexcept {
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &status);

		GLchar* message = new GLchar[status];
		glGetProgramInfoLog(program, status , &status, message);
		std::cerr << message << std::endl;
#if defined(_MSC_VER)
		if(IsDebuggerPresent())
			__debugbreak();
#endif

		delete[] message;
	}
}


int main() {
	std::cout << "master~" << std::endl;
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 800, "master~", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(&glfwGetProcAddress);

	//layout (position xy) (color rgb)
	int vertcount = 6;
	float vert[] = {
	-.5f, +.5f, .0f, .0f, 1.0f,
	-.5f, -.5f, .0f, 1.0f, .0f,
	+.5f, +.5f, 1.0f, .0f, .0f,
	+.5f, +.5f, 1.0f, 0.0f, .0f,
	-.5f, -.5f, 0.0f, 1.0f, .0f,
	+.5f, -.5f, 1.0f, 0.5f, .0f,
	};
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//happy fox noises
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , (const void*)( 2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	GLuint vertShader, fragShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertShader, 1, &s_VertexSource, nullptr);
	glShaderSource(fragShader, 1, &s_FragmentSource, nullptr);
	
	glCompileShader(vertShader);
	glCompileShader(fragShader);//happy fox noises

	CheckShaderError(vertShader);
	CheckShaderError(fragShader);


	

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);

	CheckProgramError(program);

	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glUseProgram(program);

	GLint location =  glGetUniformLocation(program, "u_Color");
	glUniform3f(location, 0.6f, 0.2f, 0.2f);



	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			glClearColor(((float)rand() / (float)RAND_MAX), .8f, .8f, 1.0f);
		}
		else {
			glClearColor(((float)rand() / (float)RAND_MAX), .0f, .0f, 1.0f);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, vertcount);


		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);
	glfwTerminate();
}