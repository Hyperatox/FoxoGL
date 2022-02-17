#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include "amazing-fox-photo-182.h"
#include "evensmaller.c"

#if defined(_MSC_VER)
#	include <Windows.h>
#endif

static const char* s_VertexSource = R"---(
#version 330 core
layout (location = 0) in vec2 vert_Position;
layout (location = 1) in vec3 vert_Color;
layout (location = 2) in vec2 aTexCoord;

out vec3 frag_Color;
out vec2 TexCoord;

void main(void)
{
	gl_Position = vec4(vert_Position, 0.0, 1.0);
	frag_Color = vert_Color;
	TexCoord = aTexCoord;
}
)---";

static const char* s_FragmentSource = R"---(
#version 330 core
layout (location = 0) out vec4 out_Color;
layout (location = 1) out vec4 FragColor;
//out vec4 FragColor;

in vec3 frag_Color;
in vec2 TexCoord;

uniform bool ShowIMG;
uniform vec3 u_Color;
uniform sampler2D ourTexture;

void main(void)
{
	//FragColor = texture(ourTexture, TexCoord);
	out_Color = vec4(frag_Color, 1.0);
	if(ShowIMG){
		out_Color = texture(ourTexture, TexCoord);
	}
	
	

}
)---";
GLuint textureInt;
bool ImageWoW();
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

	//layout (position xy) (color rgb) (Texture coords)
	int vertcount = 6;
	float vert[] = {
	//positions         //colors               //texture coords
	//0
	-.5f, +.5f,        .0f, .0f, 1.0f,          0.0f, 1.0f,//top left 
	-.5f, -.5f,        .0f, 1.0f, .0f,          0.0f, 0.0f,//bottom left
	+.5f, +.5f,        1.0f, .0f, .0f,          1.0f, 1.0f,//top right
	//1
	+.5f, +.5f,        1.0f, .0f, .0f,          1.0f, 1.0f,//top right
	-.5f, -.5f,        .0f, 1.0f, .0f,          0.0f, 0.0f,//bottom left
	+.5f, -.5f,        1.0f, .5f, .0f,          1.0f, 0.0f,//bottom right
	};
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//happy fox noises
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	/* org
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , (const void*)( 2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/

	//mod  
	//(type of change, floats total in row for type ,normal , floats total in row?, offset  )
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//mod
	

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

	GLint location0 =  glGetUniformLocation(program, "u_Color");
	glUniform3f(location0, 0.6f, 0.2f, 0.2f);
	
	GLint location1 =  glGetUniformLocation(program, "ShowIMG");
	glUniform1i(location1, 0);


	//mod
	ImageWoW();
	//mod

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			glClearColor(((float)rand() / (float)RAND_MAX), .8f, .8f, 1.0f);

			glUniform1i(location1, 1);
		}
		else {
			glClearColor(((float)rand() / (float)RAND_MAX), .0f, .0f, 1.0f);
			glUniform1i(location1, 0);
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










































/*
		-^^,--,~

  __
 / _|
| |_ _____  __
|  _/ _ \ \/ /
| || (_) >  <
|_| \___/_/\_\

  _,-=._              /|_/|
  `-.}   `=._,.-=-._.,  @ @._,
	 `._ _,-.   )      _,.-'
		`    G.m-"^m`m'

*/



bool ImageWoW() {

	char* pImg = (char*)header_data;
	char pRGB[3];
	char image[height * width * 3];

	
	for (int j = 0; j < height * width *3; j+=3) {//FUCK THIS almost 4 am and i got it right
		HEADER_PIXEL(pImg, pRGB)

			image[j] = pRGB[0];
			image[j+1] = pRGB[1];
			image[j+2] = pRGB[2];

	}

	/*
	for (int j = height * width * 3; j >= 3; j -= 3) {//normal orientation but with a cool error that does not do anything
		HEADER_PIXEL(pImg, pRGB)

		image[j]     = pRGB[0];
		image[j - 2] = pRGB[1];
		image[j - 1] = pRGB[2];

		//std::cout << image[j] << " " << j << std::endl;

	}*/



	// Create one OpenGL texture
	glGenTextures(1, &textureInt);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureInt);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


	return true;
}