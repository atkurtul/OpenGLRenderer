#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>

#include <GLTypes/RenderObject.h>
#include <GLTypes/Camera.h>
#include <GLTypes/ElementBuffer.h>
#include <GLTypes/VertexBuffer.h>
#include <GLTypes/VertexArray.h>
#include <GLTypes/LightManager.h>
#include <GLTypes/Mesh.h>
#include <GLTypes/AssimpModel.h>


struct RendererData
{
	bool clearColor = true, depthTest = true, clearDepth = true;
	float resetCol[4] = {0.2f, 0.3f, 0.8f, 1.0f};
	uint32_t getClearMask();
};

class Renderer
{
private:
	uint32_t itemCount = 0;

	std::unordered_map<uint32_t, RenderObject *> renderObjects;
	RendererData data;

	std::vector<const VertexBuffer *> vertexBuffers;
	std::vector<const VertexArray *> vertexArrays;
	std::vector<const ElementBuffer *> elementBuffers;

public:
	static Renderer *renderer;
	FreeCamera *camera;
	LightManager *lightManager;

	Renderer(RendererData data);

	void init();

	SimpleRenderObject *addOddObject(RenderObjectData data, Material *material, const std::vector<float> &vertices, const std::vector<uint32_t> &attributeSizes);

	SimpleRenderObject *addSimpleObject(RenderObjectData data, Material *material, const std::vector<float> &vertices, const std::vector<uint32_t> &attributeSizes, const std::vector<uint32_t> &indices);

	AssimpModel *addModel(RenderObjectData data, const Material &baseMaterial, const char *path);

	Mesh *addMesh(RenderObjectData data, Material *material, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);

	template<typename Type>
	Type *cloneObject(const Type &from)
	{
		uint32_t id = itemCount++;
		Type *renderObject = new Type(id, from);
		renderObjects.insert({id, renderObject});
		return renderObject;
	}

	void draw();

	~Renderer();
private:
	void addRenderObject(RenderObject *renderObject);
};