#include "Dinosaur.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Dino::Dino() {
    objLoader = new ObjLoader();

    bool res = objLoader->loadObj("Dino.obj", vertices, uvs, normals);
	if(res)
		renderer->ChangeVertex(vertices);
}
void Dino::Rotate(float angle, glm::vec3 direction) {
	transform->Rotate(angle * direction.x, angle * direction.y, angle * direction.z);
}
void Dino::Draw(Renderer* renderer) {
	this->Render(renderer);
}