#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
		mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
		someMesh = mesh;
		mesh = new Mesh("trevor_philips");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "trevor_philips.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	if (!isColorChanged)
		glClearColor(0, 0, 0, 1);
	else
		glClearColor(0.5, 0.3, 0.1, 1);
	/*
	if (isObjectChanged) {
		Mesh *copy = new Mesh("teapot");
		copy->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[someMesh->GetMeshID()] = copy;
	}
	else {
		meshes[someMesh->GetMeshID()] = someMesh;
	} */

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(4, 0.7f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes["sphere"], glm::vec3(2, 0.5f, 0), glm::vec3(0.7f));
	RenderMesh(meshes["trevor_philips"], glm::vec3(x, y, z), glm::vec3(0.015f));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (canBeObjectMoved) {
		//cout << deltaTime << endl;
		if (window->KeyHold(GLFW_KEY_W))
			z -= deltaTime * 2;
		if (window->KeyHold(GLFW_KEY_A))
			x -= deltaTime * 2;
		if (window->KeyHold(GLFW_KEY_S))
			z += deltaTime * 2;
		if (window->KeyHold(GLFW_KEY_D))
			x += deltaTime * 2;
		if (window->KeyHold(GLFW_KEY_Q))
			y += deltaTime * 2;
		if (window->KeyHold(GLFW_KEY_E))
			y -= deltaTime * 2;
	}

};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
		if (isColorChanged)
			isColorChanged = false;
		else
			isColorChanged = true;
	}
	if (key == GLFW_KEY_V) {
		if (changeObject == 1) {
			changeObject = 2;
			Mesh *copy = new Mesh("teapot");
			copy->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
			meshes[someMesh->GetMeshID()] = copy;
		} else if (changeObject == 2) {
			changeObject = 0;
			Mesh *copy = new Mesh("quad");
			copy->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
			meshes[someMesh->GetMeshID()] = copy;
		} else {
			changeObject = 1;
			meshes[someMesh->GetMeshID()] = someMesh;
		}
	}
	if (key == GLFW_KEY_P) {
		if (canBeObjectMoved)
			canBeObjectMoved = false;
		else
			canBeObjectMoved = true;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
	
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
