#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GLTypes/RenderObject.h>
#include <GLTypes/Mesh.h>
#include <GLTypes/Texture.h>
class AssimpModel
{
public:
	std::vector<Mesh *> meshes;
	std::vector<Material *> materials;
	std::vector<Texture2D *> texturesLoaded;
	RenderObjectData data;
	std::string directory;
	const Material &material;

	AssimpModel(const char *path, const Material &defMaterial, RenderObjectData data);

private:
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
	void processMaterials(const aiScene *scene);
	void loadMaterialProperties(aiMaterial *aiMat, Material *genMat);
	Texture2D *loadMaterialTextureType(aiMaterial *aiMat, Material *genMat, aiTextureType type, const char *materialName);
};