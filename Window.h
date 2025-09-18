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
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacionZ() { return articulacionZ; }
	GLfloat getarticulacionX() { return articulacionX; }
	GLfloat getarticulacionC() { return articulacionC; }
	GLfloat getarticulacionV() { return articulacionV; }
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

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacionZ, articulacionX, articulacionC, articulacionV, articulaciong1, articulaciong2, articulaciong3, articulaciong4, articulaciong5, articulaciong6, articulaciong7, articulaciong8, articulaciong9, articulaciong0;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

