#pragma once

#include "glm/glm.hpp"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

namespace Engine {

	class Mesh
	{
	public:

		struct Vertex
		{
			glm::vec3 Position;
		};

		struct Index
		{
			unsigned int Vertex1, Vertex2, Vertex3;
		};

		Mesh(const std::string& path);
		~Mesh();

		void Render();
	private:

		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}

