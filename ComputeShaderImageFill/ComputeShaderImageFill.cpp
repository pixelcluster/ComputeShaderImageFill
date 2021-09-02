// ComputeShaderImageFill.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <limits>
#include <iostream>

using namespace std;

char* readFile(const char* name, int& destSize) {
	std::ifstream shaderStream = std::ifstream(name);
	if (!shaderStream.is_open())
		std::cout << ":(";
	shaderStream.ignore(std::numeric_limits<std::streamsize>::max());
	destSize = (int)shaderStream.gcount();
	shaderStream.seekg(std::ios::beg);
	shaderStream.clear();

	char* text = new char[destSize];
	shaderStream.read(text, destSize);
	return text;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Example", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	GLuint targetTexture;
	glGenTextures(1, &targetTexture);
	glBindTexture(GL_TEXTURE_2D, targetTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLuint nullShaderVert, nullShaderFrag;
	GLuint nullProgram;

	nullShaderVert = glCreateShader(GL_VERTEX_SHADER);
	nullShaderFrag = glCreateShader(GL_FRAGMENT_SHADER);

	int shaderFileSize;
	char* shaderSource = readFile("./null-vertex.glsl", shaderFileSize);

	glShaderSource(nullShaderVert, 1, &shaderSource, &shaderFileSize);
	glCompileShader(nullShaderVert);

	delete[] shaderSource;
	shaderSource = readFile("./null-fragment.glsl", shaderFileSize);

	glShaderSource(nullShaderFrag, 1, &shaderSource, &shaderFileSize);
	glCompileShader(nullShaderFrag);

	nullProgram = glCreateProgram();
	glAttachShader(nullProgram, nullShaderVert);
	glAttachShader(nullProgram, nullShaderFrag);
	glLinkProgram(nullProgram);

	GLuint computeProgram = glCreateProgram(), computeShader = glCreateShader(GL_COMPUTE_SHADER);

	delete[] shaderSource;
	shaderSource = readFile("./fill-compute.glsl", shaderFileSize);

	glShaderSource(computeShader, 1, &shaderSource, &shaderFileSize);
	delete[] shaderSource;

	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(computeProgram);
		glBindImageTexture(0, targetTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glDispatchCompute(800, 600, 1);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		glUseProgram(nullProgram);
		glBindTexture(GL_TEXTURE_2D, targetTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
