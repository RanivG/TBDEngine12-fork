#pragma once

#include "Program.h"
#include "core/camera.h"
#include "core/game_engine.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define NUM_LIGHTS 2
#define NUM_MATERIALS 3
#define NUM_SHADERS 3

class RenderEngine
{
	GLFWwindow* window;
	std::string resource_path = "../resources";

	std::string verts[NUM_SHADERS] = {
	    "/vert.glsl",
	    "/phong_vert.glsl",
	    "/silhouette_vert.glsl"
	};

	std::string frags[NUM_SHADERS] = {
	    "/frag.glsl",
	    "/phong_frag.glsl",
	    "/silhouette_frag.glsl"
	};

	Program program;
	std::unordered_map<std::string, std::vector<float>> posBuffMap;
	std::unordered_map<std::string, std::vector<float>> texBuffMap;
	std::unordered_map<std::string, std::vector<float>> norBuffMap;
	std::vector<float> posBuff;
	std::vector<float> norBuff;
	std::vector<float> texBuff;

	glm::vec3 eye = {0.0f, 0.0f, 4.0f};

	struct materialStruct {
		glm::vec3 ka, kd, ks;
		float s;
	} materials[NUM_MATERIALS];

	struct lightStruct {
		glm::vec3 position;
		glm::vec3 color;
	} lights[NUM_LIGHTS];

	int mat_idx = 0;
	int shader_idx = 0;

	Camera* camera;
	GameEngine* gameEngine;

public:
	RenderEngine()
	{
		Init();
	}
	RenderEngine(GLFWwindow* _window)
	{
		window = _window;
		Init();
	}

	RenderEngine(GLFWwindow* _window, Camera* _camera)
	{
		window = _window;
		camera = _camera;
		Init();
	}

	RenderEngine(GLFWwindow* _window, Camera* _camera, GameEngine* _gameEngine)
	{
		window = _window;
		camera = _camera;
		gameEngine = _gameEngine;

		Init();
	}

	void Init();

	void ShadersInit();
	void Display();
	void CharacterCallback(GLFWwindow* window, unsigned int key);
	void FrameBufferSizeCallback(GLFWwindow* lWindow, int width, int height);

	void LoadModel(const std::string &name);

};
