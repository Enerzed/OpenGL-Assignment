#include <filesystem>
#include "Model.hpp"


const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 1000;

// Пол
Vertex vertices[] = {
	// Координаты							// Цвета					// Нормали					// Координаты текстур
	Vertex{glm::vec3(-50.0f, 0.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-50.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(50.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(50.0f, 0.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] = {
	0, 1, 2,
	2, 3, 0
};

// Стена
Vertex wall[] = {
	Vertex{glm::vec3(-50.0f, 0.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-50.0f, -25.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(50.0f, -25.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(50.0f, 0.0f,  50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};

GLuint indices_wall[] = {
	0, 1, 2,
	2, 3, 0
};


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LAB4", NULL, NULL);
	if (!window)
		throw std::runtime_error("Error creating GLFW window");

	glfwMakeContextCurrent(window);

	if (!gladLoaderLoadGL())
		throw std::runtime_error("Error initializing GLAD");
	
	// Пол
	Texture textures[]{
		Texture("Textures/floor.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Textures/floor_spec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	std::vector<Vertex> vertexVector(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> indicesVector(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> textureVector(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(vertexVector, indicesVector, textureVector);

	// Стена
	Texture texturesWall[]{
		Texture("Textures/city.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Textures/city_spec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	std::vector<Vertex> vertexVectorWall(wall, wall + sizeof(wall) / sizeof(Vertex));
	std::vector <GLuint> indicesVectorWall(indices_wall, indices_wall + sizeof(indices_wall) / sizeof(GLuint));
	std::vector <Texture> textureVectorWall(texturesWall, texturesWall + sizeof(texturesWall) / sizeof(Texture));

	Mesh wall(vertexVectorWall, indicesVectorWall, textureVectorWall);

	glViewport(0, 0, WIDTH, HEIGHT);
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.f, 300.f, 0.f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	// Статуя
	Model statue("Models/lowe-3d-model/scene.gltf");
	statue.Scale(glm::vec3(0.5, 0.5, 0.5));
	statue.Rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	statue.Translate(glm::vec3(-30, 0, 30));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		statue.Draw(shaderProgram, camera);
		floor.Draw(shaderProgram, camera);
		wall.Draw(shaderProgram, camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}