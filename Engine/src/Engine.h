#pragma once

#define OpenGL 1
#define DirectX11 0

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "Core/Log.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Input/Input.h"
#include "Input/KeyCodes.h"

#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"

#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/UniformElement.h"

#include "DX11/DX11RenderingApi.h"
#include "DX11/DX11Shader.h"
#include "DX11/DX11VertexBuffer.h"
#include "DX11/DX11IndexBuffer.h"

#include "OpenGL/OpenGLShader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLTexture.h"

#include "Window/Window.h"
#include "Window/GlfwWindow.h"
#include "Window/Win32Window.h"

#include "Core/App.h"
#include "Core/OrthographicCamera.h"
#include "Core/Camera.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Mesh.h"

