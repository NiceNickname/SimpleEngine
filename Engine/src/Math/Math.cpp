#include "Math.h"
#include <cmath>
#define PI 3.141592653

namespace Engine
{
	Mat4f::Mat4f()
	{
		for (int i = 0; i < 4 * 4; i++)
		{
			m_Elements[i] = 0.0f;
		}
	}

	Mat4f Mat4f::Identity()
	{
		Mat4f result;

		result.m_Elements[0 + 0 * 4] = 1.0f;
		result.m_Elements[1 + 1 * 4] = 1.0f;
		result.m_Elements[2 + 2 * 4] = 1.0f;
		result.m_Elements[3 + 3 * 4] = 1.0f;

		return result;
	}

	Mat4f Mat4f::Ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4f result = Identity();

		result.m_Elements[0 + 0 * 4] = 2.0f / (right - left);
		result.m_Elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.m_Elements[2 + 2 * 4] = 2.0f / (near - far);

		result.m_Elements[0 + 3 * 4] = (left + right) / (left - right);
		result.m_Elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.m_Elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Mat4f Mat4f::Translate(const Vector3f& position)
	{
		Mat4f result = Identity();

		result.m_Elements[0 + 3 * 4] = position.x;
		result.m_Elements[1 + 3 * 4] = position.y;
		result.m_Elements[2 + 3 * 4] = position.z;

		return result;
	}

	Mat4f Mat4f::Rotate(float angle)
	{
		Mat4f result = Identity();
		float r = (float)PI * angle / 180.0f;
		float Cos = cos(r);
		float Sin = sin(r);

		result.m_Elements[0 + 0 * 4] = Cos;
		result.m_Elements[1 + 0 * 4] = Sin;
		result.m_Elements[0 + 1 * 4] = -Sin;
		result.m_Elements[1 + 1 * 4] = Cos;

		return result;
	}

	Mat4f Mat4f::Product(const Mat4f& another)
	{
		Mat4f result;

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += m_Elements[x + e * 4] * another.m_Elements[e + y * 4];
				}
				result.m_Elements[x + y * 4] = sum;
			}
		}

		return result;
	}
}
