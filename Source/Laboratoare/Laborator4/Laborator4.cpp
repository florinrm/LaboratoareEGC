#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f,-1.5f);
	modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// solar system
	sunAngle += deltaTimeSeconds;
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 2, 2);
	modelMatrix *= Transform3D::RotateOZ(sunAngle);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// planet
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 2, 2);
	modelMatrix *= Transform3D::Scale(1, 1, 1);
	modelMatrix *= Transform3D::RotateOZ(sunAngle * 2);
	modelMatrix *= Transform3D::Translate(0, -2, -2);
	modelMatrix *= Transform3D::Translate(0, 8, 2);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// moon
	modelMatrix *= Transform3D::RotateOZ(sunAngle * 3);
	modelMatrix *= Transform3D::Translate(0, 4, 0);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// TODO
	if (window->KeyHold(GLFW_KEY_W) && moveScreen)
		translateZ -= deltaTime;
	if (window->KeyHold(GLFW_KEY_D) && moveScreen)
		translateX += deltaTime;
	if (window->KeyHold(GLFW_KEY_A) && moveScreen)
		translateX -= deltaTime;
	if (window->KeyHold(GLFW_KEY_S) && moveScreen)
		translateZ += deltaTime;
	if (window->KeyHold(GLFW_KEY_R) && moveScreen)
		translateY += deltaTime;
	if (window->KeyHold(GLFW_KEY_F) && moveScreen)
		translateY -= deltaTime;
	if (window->KeyHold(GLFW_KEY_1)) {
		scaleX += deltaTime;
		scaleY += deltaTime;
		scaleZ += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_2)) {
		scaleX -= deltaTime;
		scaleY -= deltaTime;
		scaleZ -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_3)) {
		angularStepOX += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_4)) {
		angularStepOX -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_5)) {
		angularStepOY += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_6)) {
		angularStepOY -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_7)) {
		angularStepOZ += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_8)) {
		angularStepOZ -= deltaTime;
	}
}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}

	if (key == GLFW_KEY_P) {
		if (moveScreen)
			moveScreen = false;
		else
			moveScreen = true;
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
