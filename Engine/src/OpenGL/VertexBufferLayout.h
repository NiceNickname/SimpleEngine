#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class DATATYPE
{
	FLOAT1 = 0, FLOAT2, FLOAT3, INT1, MAT4
};
struct LayoutElement
{
	std::string name;
	DATATYPE type;
	unsigned int offset;
	bool normalized;

	LayoutElement(const std::string& name, DATATYPE type, bool normalized = false)
		: name(name), type(type), normalized(normalized), offset(0)
	{
	}

	unsigned int GetCount()
	{
		switch (type)
		{
			case DATATYPE::INT1:
			case DATATYPE::FLOAT1:
				return 1;
			case DATATYPE::FLOAT2: return 2;
			case DATATYPE::FLOAT3: return 3;
			case DATATYPE::MAT4:   return 16;
		}

		return 0;
	}

	unsigned int GetSize()
	{
		switch (type)
		{
			case DATATYPE::INT1:   return 1 * sizeof(int);
			case DATATYPE::FLOAT1: return 1 * sizeof(float);
			case DATATYPE::FLOAT2: return 2 * sizeof(float);
			case DATATYPE::FLOAT3: return 3 * sizeof(float);
			case DATATYPE::MAT4:   return 16 * sizeof(float);
		}

		return 0;
	}

	unsigned int GetType()
	{
		switch (type)
		{
			case DATATYPE::INT1:		return GL_INT;
			case DATATYPE::FLOAT1:		return GL_FLOAT;
			case DATATYPE::FLOAT2:		return GL_FLOAT;
			case DATATYPE::FLOAT3:		return GL_FLOAT;
			case DATATYPE::MAT4:		return GL_FLOAT;
		}

		return 0;
	}

};

struct VertexBufferLayout
{
	VertexBufferLayout(const std::initializer_list<LayoutElement>& elements)
	{
		unsigned int offset = 0;
		for (LayoutElement el : elements)
		{
			el.offset = offset;
			offset += el.GetSize();
			Elements.push_back(el);
		}
		Stride = offset;
	}


	std::vector<LayoutElement> Elements;
	unsigned int Stride;
};