#include "pch.h"


#include "Mesh.h"

#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"

#include "glad/glad.h"
#include "Renderer/Renderer2D.h"


const unsigned int ImportFlags =
aiProcess_CalcTangentSpace |
aiProcess_Triangulate |
aiProcess_SortByPType |
aiProcess_PreTransformVertices |
aiProcess_GenNormals |
aiProcess_GenUVCoords |
aiProcess_OptimizeMeshes |
aiProcess_Debone |
aiProcess_ValidateDataStructure;

namespace Engine {

	Mesh::Mesh(const std::string& path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, ImportFlags);
		aiMesh* mesh = scene->mMeshes[0];

		m_Vertices.reserve(mesh->mNumVertices);

		for (unsigned int i = 0; i < m_Vertices.capacity(); i++)
		{
			Vertex vertex;
			vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			m_Vertices.push_back(vertex);
		}

		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices.data(), sizeof(Vertex) * m_Vertices.size()));

		m_Indices.reserve(mesh->mNumFaces);

		for (unsigned int i = 0; i < m_Indices.capacity(); i++)
		{
			Index index;
			index.Vertex1 = mesh->mFaces[i].mIndices[0];
			index.Vertex2 = mesh->mFaces[i].mIndices[1];
			index.Vertex3 = mesh->mFaces[i].mIndices[2];

			m_Indices.push_back(index);
		}

		m_IndexBuffer.reset(IndexBuffer::Create(m_Indices.data(), sizeof(Index) * m_Indices.size()));
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::Render()
	{
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		glDrawElements(GL_TRIANGLES, m_Indices.size() * 3, GL_UNSIGNED_INT, nullptr);
	}

}