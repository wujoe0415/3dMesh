#include "Renderer.h"
#include "Window.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

vector<glm::vec3> Renderer::DEFAULT_VECTOR = {};
Renderer::Renderer(const char* textureName,const char* shaderName, vector<glm::vec3>& vertices) {
	texture = ResourceManager::GetTexture(textureName);
	shader = ResourceManager::GetShader(shaderName);
	InitRenderData(vertices);
}
void Renderer::ChangeShader(char* shaderName) {
	shader = ResourceManager::GetShader(shaderName);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);
	//InitRenderData();
}
void Renderer::ChangeTexture(char* textureName) {
	texture = ResourceManager::GetTexture(textureName);
}
void Renderer::InitRenderData(vector<glm::vec3>& vertix) {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	vertexsize = 36;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if(vertix == DEFAULT_VECTOR)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, vertix.size() * sizeof(glm::vec3), &vertix[0], GL_STATIC_DRAW);
	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void Renderer::ChangeVertex(vector<glm::vec3>& vertices, vector<unsigned int>& indices) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// EBO
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	vertexsize = vertices.size();
}
void Renderer::Render(glm::mat4 pmodel, glm::vec3 color) {
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->shader.Use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.SetMatrix4("view", view);

	glm::mat4 model = pmodel;
	//std::cout << glm::to_string(model) << std::endl;
	shader.SetMatrix4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Renderer::Render(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 color) {
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->shader.Use();
	glm::vec3 pointLightPositions[] = {
		glm::vec3(2.0f,  3.0f,  -3.0f),
		glm::vec3(1.0f + sin(glfwGetTime()) * 2.0f, sin(glfwGetTime() / 2.0f) * 2.0f, 3.0f),
		glm::vec3(-3.0f,  3.0f, -4.0f),
		glm::vec3(3.0f,  -5.0f, -3.0f)
	};
	// point light 1
	shader.SetVector3f("pointLights[0].position", pointLightPositions[0]);
	shader.SetVector3f("pointLights[0].color", 0.996f, 0.7968f, 0.5976f);
	shader.SetVector3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("pointLights[0].diffuse", 0.3f, 0.3f, 0.3f);
	shader.SetVector3f("pointLights[0].specular", 0.1f, 0.1f, 0.1f);
	shader.SetFloat("pointLights[0].constant", 0.0f);
	shader.SetFloat("pointLights[0].linear", 0.09f);
	shader.SetFloat("pointLights[0].quadratic", 0.032f);
	// point light 2
	shader.SetVector3f("pointLights[1].position", pointLightPositions[1]);
	shader.SetVector3f("pointLights[1].color", 0.996f, 0.8945f, 0.7968f);
	shader.SetVector3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("pointLights[1].diffuse", 0.2f, 0.2f, 0.2f);
	shader.SetVector3f("pointLights[1].specular", 0.1f, 0.2f, 0.1f);
	shader.SetFloat("pointLights[1].constant", 0.0f);
	shader.SetFloat("pointLights[1].linear", 0.09f);
	shader.SetFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	shader.SetVector3f("pointLights[2].position", pointLightPositions[2]);
	shader.SetVector3f("pointLights[2].color", 0.7968f, 0.5f, 0.996f);
	shader.SetVector3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("pointLights[2].diffuse", 0.4f, 0.4f, 0.4f);
	shader.SetVector3f("pointLights[2].specular", 0.3f, 0.3f, 0.2f);
	shader.SetFloat("pointLights[2].constant", 0.01f);
	shader.SetFloat("pointLights[2].linear", 0.09f);
	shader.SetFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	shader.SetVector3f("pointLights[3].position", pointLightPositions[3]);
	shader.SetVector3f("pointLights[3].color", 0.398f, 0.695f, 0.996f);
	shader.SetVector3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("pointLights[3].diffuse", 0.8f, 0.7f, 0.8f);
	shader.SetVector3f("pointLights[3].specular", 0.2f, 0.2f, 0.3f);
	shader.SetFloat("pointLights[3].constant", 0.5f);
	shader.SetFloat("pointLights[3].linear", 0.09f);
	shader.SetFloat("pointLights[3].quadratic", 0.032f);
	//glm::vec2 lightPosition;
	//lightPosition.x = 1.0f + sin(glfwGetTime()) * 2.0f;
	//lightPosition.y = sin(glfwGetTime() / 2.0f) * 1.0f;
	//shader.SetVector3f("light.position", lightPosition.x, lightPosition.y, 1.0f);
	//shader.SetVector3f("viewPos", 0.0f, 0.0f, 3.0f);
	//// light properties
	//shader.SetVector3f("light.ambient", 1.0f, 1.0f, 1.0f); // note that all light colors are set at full intensity
	//shader.SetVector3f("light.diffuse", 1.0f, 1.0f, 1.0f);
	//shader.SetVector3f("light.specular", 1.0f, 1.0f, 1.0f);

	//// material properties
	shader.SetVector3f("material.ambient", 0.2f, 0.2f, 0.2f);
	shader.SetVector3f("material.diffuse", 1.0f, 0.5f, 1.0f);
	shader.SetVector3f("material.specular", 0.2f, 0.2f, 0.2f);
	shader.SetFloat("material.shininess", 32.0f);
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	shader.SetMatrix4("view", view);

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);

	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotateMatrix = transformX * transformY *  transformZ;

	model *= rotateMatrix;

	model = glm::scale(model, size); // last scale

	//std::cout << glm::to_string(model) << std::endl;
	
	shader.SetMatrix4("model", model);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexsize);
}
void Renderer::Render(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 color, unsigned int indices_size) {
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->shader.Use();
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	shader.SetMatrix4("view", view);

	glm::mat4 model = glm::mat4(1.0f);

	//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::translate(model, position);

	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotateMatrix = transformX * transformY * transformZ;

	model *= rotateMatrix;

	model = glm::scale(model, size); // last scale

	//std::cout << glm::to_string(model) << std::endl;

	shader.SetMatrix4("model", model);

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, (void*)0);
}