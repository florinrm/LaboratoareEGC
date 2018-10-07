#pragma once

#include <Component/SimpleScene.h>

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();
		bool isColorChanged = false;
		int changeObject = 0;
		bool canBeObjectMoved = false;
		float x = 1, y = 0.5, z = 0;
		Mesh *mesh;
		Mesh *someMesh;

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
};
