#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getprendida() { return luzprendida; }
	GLfloat getprendidaOb() { return luzprendidaOb; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getarticulaciong1() { return articulaciong1; }
	GLfloat getarticulaciong2() { return articulaciong2; }
	GLfloat getarticulaciong3() { return articulaciong3; }
	GLfloat getarticulaciong4() { return articulaciong4; }
	GLfloat getarticulaciong5() { return articulaciong5; }
	GLfloat getarticulaciong6() { return articulaciong6; }
	GLfloat getarticulaciong7() { return articulaciong7; }
	GLfloat getarticulaciong8() { return articulaciong8; }
	GLfloat getarticulaciong9() { return articulaciong9; }
	GLfloat getarticulaciong0() { return articulaciong0; }
	GLfloat getcarrozaPosZ() { return carrozaPosZ; }
	GLfloat gethelicopPosX() { return helicopPosX; }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat luzprendida, luzprendidaOb;
	bool mouseFirstMoved;
	GLfloat articulaciong1, articulaciong2, articulaciong3, articulaciong4, articulaciong5, articulaciong6, articulaciong7, articulaciong8, articulaciong9, articulaciong0;
	GLfloat carrozaPosZ, helicopPosX;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};