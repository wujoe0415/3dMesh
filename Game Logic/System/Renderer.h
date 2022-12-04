#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Texture.h"
#include "Shader.h"
#include <System/Sprite_Renderer.h>
#include "System/Resource_Manager.h"
#include <vector>
using namespace std;

class Renderer {
public:
	Renderer(const char* textureName, const char* shaderName, vector<glm::vec3>& vertices = DEFAULT_VECTOR);
	void ChangeTexture(char* newTexture);
	void ChangeShader(char* newShader);
	void ChangeVertex(vector<glm::vec3>& vertices);
	void Render(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 color);
	void Render(glm::mat4 model, glm::vec3 color);
	void InitRenderData(vector<glm::vec3>& vertices = DEFAULT_VECTOR);
	Texture2D texture;
	Shader shader;
private:
	unsigned int VAO;
	static vector<glm::vec3> DEFAULT_VECTOR;
};