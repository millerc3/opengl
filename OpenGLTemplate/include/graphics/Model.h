#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <graphics/Shader.h>
#include <graphics/Mesh.h>

class Model {
public:
	Model(const char* path);
	void Draw(Shader& shader);

private:
	// model data
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> loaded_textures;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};