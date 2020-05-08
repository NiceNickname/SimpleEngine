#pragma once

namespace Engine
{
	class Vector3f
	{
	public:
		Vector3f()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vector3f(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		float x, y, z;
	};

	class Mat4f
	{
	public:

		Mat4f();
		static Mat4f Identity();
		static Mat4f Ortho(float left, float right, float bottom, float top, float near, float far);
		static Mat4f Translate(const Vector3f& position);
		Mat4f Rotate(float Rotation);

		Mat4f Product(const Mat4f& another);
		inline float* GetElements() { return m_Elements; }


		float m_Elements[4 * 4];
	};
}
