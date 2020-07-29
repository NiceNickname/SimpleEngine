#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Input/Input.h"

#include "Renderer/VertexBufferLayout.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLTexture.h"

#include "Window/Window.h"
#include "Core/App.h"
#include "Core/OrthographicCamera.h"
#include "Renderer/Renderer.h"

