#pragma once

#include "json.hpp"
#include "Mesh.hpp"

using json = nlohmann::json;


class Model
{
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);
	void Scale(glm::vec3 scale) {
		for (int i = 0; i < matricesMeshes.size(); i++) {
			matricesMeshes[i] = glm::scale(matricesMeshes[i], scale);
		}
	}
	void Translate(glm::vec3 translation) {
		for (int i = 0; i < matricesMeshes.size(); i++) {
			matricesMeshes[i] = glm::translate(matricesMeshes[i], translation);
		}
	}
	void Rotate(float angle, glm::vec3 axis) {
		for (int i = 0; i < matricesMeshes.size(); i++) {
			matricesMeshes[i] = glm::rotate(matricesMeshes[i], angle, axis);
		}
	}


private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	void loadMesh(unsigned int indMesh);

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

};