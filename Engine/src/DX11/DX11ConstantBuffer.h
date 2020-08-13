#pragma once

#include "DX11/DX11RenderingApi.h"

namespace Engine {

	class DX11ConstantBuffer
	{
	public:
		DX11ConstantBuffer(const std::string& name, unsigned int bytewidth);
		~DX11ConstantBuffer();

		void Update(const void* data);

		void Bind(unsigned int slot);
		inline const std::string& GetName() { return m_Name;  }

	private:
		std::string m_Name;
		ID3D11Buffer* m_Buffer;
	};

}
