#pragma once
#include "Renderer/IndexBuffer.h"
#include "DX11RenderingApi.h"

namespace Engine {

	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(void* data, unsigned int size);
		~DX11IndexBuffer();
		virtual void SetData(void* data, unsigned int size) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual int GetCount() const override;

	private:
		ID3D11Buffer* m_IndexBuffer;
	};

}
