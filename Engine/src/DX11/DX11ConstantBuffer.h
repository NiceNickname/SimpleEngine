#pragma once

#include "DX11/DX11RenderingApi.h"

namespace Engine {

	class DX11ConstantBuffer
	{
	public:
		DX11ConstantBuffer(unsigned int bytewidth);
		~DX11ConstantBuffer();

		void Update(const void* data);

		void Bind();


	private:
		ID3D11Buffer* m_Buffer;
	};

}
