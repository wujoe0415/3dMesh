#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

using namespace std;

class ObjLoader {
public:
	ObjLoader();
	bool loadObj(string path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals);
private:
	void PrecessData();
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
};