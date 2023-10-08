#include "llgl/Llgl.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/ObjectBase.hpp"
#include "llgl/Uniform.hpp"
#include <algorithm>
#include <chrono>

namespace llgl
{

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
using Duration = std::chrono::duration<float, std::ratio<1, 1>>;

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
	TimePoint runTimePoint = Clock::now();
	TimePoint lastFrameTimePoint = runTimePoint;

	while (!glfwWindowShouldClose(Window::getWindow()))
    {

		const Color &color = this->Window::getBackgroundColor();
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		for(auto &object : this->objects){
			auto objectLock = object.lock();
			if(objectLock == nullptr) continue;
			objectLock->draw();
		}

        glfwSwapBuffers(Window::getWindow());
        glfwPollEvents();


		TimePoint currentTime = Clock::now();
		float runDuration = std::chrono::duration_cast<Duration>(currentTime - runTimePoint).count();
		float frameDuration = std::chrono::duration_cast<Duration>(currentTime - lastFrameTimePoint).count();
		lastFrameTimePoint = currentTime;
		updateTickFuncs(runDuration, frameDuration);
    }
}

void Llgl::addObject(std::shared_ptr<ObjectBase> object)
{
	if(object == nullptr) return;
	this->objects.push_back(object);
}

void Llgl::addTickUpdateFunc(TickUpdateFunc func)
{
	this->tickUpdateFunctions.push_back(std::move(func));
}

void Llgl::updateTickFuncs(float runTime, float deltaTime)
{
	TickInfo tickInfo{
		runTime,
		deltaTime
	};
	for(auto &func : this->tickUpdateFunctions){
		func(tickInfo);
	}
}




} // namespace llgl
