// OpenGLSession0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n" 
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y,aPos.z,1.0f);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 triangleColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(triangleColor, 1.0f);\n"
"}\n\0";


int main()
{
    GLFWwindow* window;
	




	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 580, "Test Window ", NULL, NULL);
    std::cout << "Hello World!\n";
	
	GLfloat vertices[] = {

		-0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
		0.0,0.5f * float(sqrt(3)) * 2 / 3, 0.0f,

		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	    1.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	    0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to get process address " << std::endl;
		glfwTerminate();
		return -1;
	}
	else {
		std::cout << " process is great ";
	}
	gladLoadGL();

	glViewport(0, 0, 640, 580);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	float translationX1 = 0.0f;
	float translationY1 = 0.0f;

	float translationX2 = 0.0f;
	float translationY2 = 0.0f;
	float translationSpeed = 0.01f;

	GLint translationLocation = glGetUniformLocation(shaderProgram, "translation");
	GLint triangleColorLocation = glGetUniformLocation(shaderProgram, "triangleColor");
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			std::cout << "Exit the window ..." << std::endl;
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			vertices[0] -= translationSpeed;
			vertices[3] -= translationSpeed;
			vertices[6] -= translationSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			vertices[0] += translationSpeed;
			vertices[3] += translationSpeed;
			vertices[6] += translationSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			vertices[1] += translationSpeed;
			vertices[4] += translationSpeed;
			vertices[7] += translationSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			vertices[1] -= translationSpeed;
			vertices[4] -= translationSpeed;
			vertices[7] -= translationSpeed;
		}
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

		glUniform2f(translationLocation, translationX1, translationY1);
		glUniform3f(triangleColorLocation, 0.8f, 0.0f, 0.8f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUniform2f(translationLocation, translationX2, translationY2);
		glUniform3f(triangleColorLocation, 0.01f, 0.02f, 0.5f);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		
		
		// Swap front and back buffers 
		glfwSwapBuffers(window);
		
		// Poll for and process events 
		
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
