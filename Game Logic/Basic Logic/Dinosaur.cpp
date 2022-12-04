#include "Dinosaur.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Dino::Dino() {
    objLoader = new ObjLoader();

    bool res = objLoader->loadObj("Dino.obj", vertices, uvs, normals);
	if(res)
		renderer->ChangeVertex(vertices, objLoader->vertexIndices);
	Normalize();
}
void Dino::Rotate(float angle, glm::vec3 direction) {
	transform->Rotate(angle * direction.x, angle * direction.y, angle * direction.z);
}
void Dino::Draw(Renderer* renderer) {
	//renderer->Render(transform->GetGlobalPosition(), transform->GetGlobalRotation(), transform->GetGlobalScale(), glm::vec3(1, 1, 1), objLoader->vertexIndices.size());
	this->Render(renderer);
}
void Dino::Normalize()
{
	int max = glm::length(vertices[1] - vertices[0]);
	for (int i = 1; i < vertices.size(); i++)
	{
		int next = glm::length(vertices[i] - vertices[i - 1]);
		if (max < next)
			max = next;
	}
	float scaler = (float)1 / max;
	cout << scaler;
	transform->SetScale(glm::vec3(scaler, scaler, scaler));
} 