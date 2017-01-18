
#pragma once

#include "common.hpp"
#include "glfw/glfw_manager.hpp"
#include "gl/gl.hpp"
#include "logger/log.hpp"
#include "cam/cam.hpp"

class game_state {
public:
	game_state();
	~game_state();

	void init();
	void kill();
	void run();

private:
    glfw_manager glfw;
	gl_manager gl;
	cam_3d cam;
	bool running;
	bool initialized;

	GLuint VAO, VBO;
};