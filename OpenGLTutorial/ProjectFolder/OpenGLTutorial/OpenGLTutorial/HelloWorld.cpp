
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *FragmentShaderOrangeSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char *FragmentShaderYellowSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//screen settings.
const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;
// two triangle vertices
float Triangle1Vertices[] =
{
	-0.8f, -0.5f, 0.0f,  // left 
	-0.1f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f  // top 
};

float Triangle2Vertices[] =
{
	0.1f, -0.5f, 0.0f,  // left
	0.8f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f //top
};
//used for both triangles.
unsigned int indicesTriangle[] = {
0,1,2
};

 int main()
{
	//GLFW : initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version 0.3
	// together the last two lines tell openGl that we are using version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// glad: load all OpenGL functions pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // 800 and 600 correspond to the size used to create the window.

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//unsigned int VAOTriangle1, VAOTriangle2;// vertex array object;
	unsigned int VAOTriangles[2];
	glGenVertexArrays(2, VAOTriangles);
	//unsigned int VBOTriangle1; // vertex buffer object 
	unsigned int VBOTriangles[2];
	glGenBuffers(2, VBOTriangles); // generate a buffer id and assign it to the VBO.
	
	unsigned int EBOTriangles[2];
	glGenBuffers(2, EBOTriangles);

	glBindVertexArray(VAOTriangles[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTriangles[0]); // assign buffer type to VBO. The type here is GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1Vertices), Triangle1Vertices, GL_STATIC_DRAW); //here we load buffer data into the GL_ARRAY_BUFFER which is bound to VBO that is to say
																			   //that when we load the GL_ARRAY_BUFFER the information is found in a buffer named VBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOTriangles[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(VAOTriangles[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTriangles[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2Vertices), Triangle2Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOTriangles[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);




	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //create vertex shader store (reference) in vertexShader Variable
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach some source code to the shader 
	glCompileShader(vertexShader); // compile the shader

	unsigned int fragmentShaderOrange;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &FragmentShaderOrangeSource, NULL);
	glCompileShader(fragmentShaderOrange);

	unsigned int fragmentShaderYellow;
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &FragmentShaderYellowSource, NULL);
	glCompileShader(fragmentShaderYellow);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // check if compilation of the shader was successful and write the result in sucess variable

	//if the compilation is not successful then write the ouput on the screen.
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success); // check if compilation of the shader was successful and write the result in sucess variable
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success); // check if compilation of the shader was successful and write the result in sucess variable
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgramOrange;
	shaderProgramOrange = glCreateProgram(); // create a program (shader program)
	glAttachShader(shaderProgramOrange, vertexShader); // attach the vertex shader to the program
	glAttachShader(shaderProgramOrange, fragmentShaderOrange); // attach the fragment shader to the program
	glLinkProgram(shaderProgramOrange); // linking the shaders in the program to each other. This is where the in and out variables of each need to line up
	
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success); // checking for compilation errors
	if (!success) // if not compiled then
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
	}

	unsigned int shaderProgramYellow;
	shaderProgramYellow = glCreateProgram(); // create a program (shader program)
	glAttachShader(shaderProgramYellow, vertexShader); // attach the vertex shader to the program
	glAttachShader(shaderProgramYellow, fragmentShaderYellow); // attach the fragment shader to the program
	glLinkProgram(shaderProgramYellow); // linking the shaders in the program to each other. This is where the in and out variables of each need to line up

	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success); // checking for compilation errors
	if (!success) // if not compiled then
	{
		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
	}

	//glUseProgram(shaderProgramOrange);// use the shaderprogram that was made earlier in the code. this will be used for every shader and rendering call for now.

	glDeleteShader(vertexShader); // deleting the shaders once they are no longer needed.
	glDeleteShader(fragmentShaderOrange);
	// First parameter is which vertex attribute we want to configure it is 0 because in the code for vertex shader we set location = 0
	// Second parameter is size of the vertex attribute. Since each vertex is a vec3 (3 values) we have a size of 3.
	// Third parameter is the tyoe of data in the vertex, here it is a GL_FLOAT.
	// Fourth is wether or not we want the data tp by normalized. Since it is already normalized we put this to GL_false.
	//Fifth is the "stride" that is to say how much space between consecutive vertex attributes. Here each attribute is 3 floats so we set the stride 
	//to be 3* size of a float. 
	//Sixth is the offset of where the positon data begins in the buffer. The position data begins at 0 here so we set it to (void*)0 (basicly just 0)


	
	// Render loop
	while (!glfwWindowShouldClose(window)) 
	{
		//input 
		processInput(window);
		//rendering commands here

		//Clear the buffer window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shaderProgramYellow);
			glBindVertexArray(VAOTriangles[0]);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			glUseProgram(shaderProgramOrange);
			glBindVertexArray(VAOTriangles[1]);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//dealocate resources
	glDeleteVertexArrays(1, VAOTriangles);
	glDeleteBuffers(1, VBOTriangles);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);
	glfwTerminate();
	return 0;
}

// Whenever the window size changes (by OS or user resize) this callback function is executed
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// Process all input : query GLFW whether releveant keys are pressed/released this frame and react accordingly.
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
