#pragma once
#include "System/GameObject.h"
#include <vector>
#include <map>
#include "System/Renderer.h"
#include "System/SphereRenderer.h";
#include "System/ObjLoader.h"
using namespace std;

class Dino : public GameObject {
public:
	Dino();
	void Rotate(float angle, glm::vec3 direction);
	void Draw(Renderer*);
private:
	ObjLoader* objLoader;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
};