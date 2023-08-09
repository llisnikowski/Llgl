#include "llgl/Llgl.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/ObjectBase.hpp"
#include "llgl/Uniform.hpp"

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
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		for(auto &uniform : this->updateTickUniforms){
			auto uniformLock = uniform.lock();
			if(uniformLock == nullptr) continue;
			uniformLock->update();
		}

		for(auto &object : this->objects){
			auto objectLock = object.lock();
			if(objectLock == nullptr) continue;
			objectLock->draw();
		}

        glfwSwapBuffers(Window::getWindow());
        glfwPollEvents();
    }
}

void Llgl::addObject(std::shared_ptr<ObjectBase> object)
{
	if(object == nullptr) return;
	this->objects.push_back(object);
}

void Llgl::addToTickUpdater(std::shared_ptr<UniformBase> uniform)
{
	this->updateTickUniforms.push_back(uniform);
}

} // namespace llgl
