#include "llgl/Llgl.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

Llgl::Llgl(std::string name, Size size)
:Window{std::move(name), size}
{
}

Llgl::Llgl()
:Window{}
{
}

Llgl::~Llgl()
{
	glfwTerminate();
}

bool Llgl::init()
{
	if(this->glfwInit() == false) return false;
	bool ret = true;
	if(this->Window::init() == false) ret = false;
	return ret && this->loadGlad();
}

bool Llgl::glfwInit()
{
	::glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	return true;
}

bool Llgl::loadGlad()
{
	gladLoadGL();
	return true;
}

void Llgl::run()
{
	if(Window::getWindow() == nullptr) return;
	while (!glfwWindowShouldClose(Window::getWindow()))
    {
		const Color &color = this->Window::getBackgroundColor();
        glClearColor(color.r, color.g, color.b, color.alpha);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(Window::getWindow());
        glfwPollEvents();
    }
}


} // namespace llgl
