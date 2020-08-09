#pragma once


namespace Engine {


	class Window
	{

	public:

		enum class Type { WIN32WINDOW = 0, GLFW };

		virtual ~Window() = default;
		static Window* Create(const std::string& name, int width, int height, Type type);

		virtual void Update() = 0;
		virtual bool ShouldClose() = 0;
		virtual void GetFrameBufferSize(int* width, int* height) = 0;

		virtual const std::string& GetName() const { return m_Name; }
		virtual int GetWidth() const { return m_Width; }
		virtual int GetHeight() const { return m_Height; }

	protected:
		std::string m_Name;
		int m_Width;
		int m_Height;
	};

}