#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	articulaciong1 = 0.0f;
	articulaciong2 = 0.0f;
	articulaciong3 = 0.0f;
	articulaciong4 = 0.0f;
	articulaciong5 = 0.0f;
	articulaciong6 = 0.0f;
	articulaciong7 = 0.0f;
	articulaciong8 = 0.0f;
	articulaciong9 = 0.0f;
	articulaciong0 = 0.0f;
	carrozaPosZ = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la práctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_1)
	{
		if (theWindow->articulaciong1 + 10.0f <= 45.0f)
		{
			theWindow->articulaciong1 += 10.0f;
		}
		else
		{
			theWindow->articulaciong1 = 45.0f;
		}
	}
	if (key == GLFW_KEY_2)
	{
		if (theWindow->articulaciong1 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong1 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong1 = -45.0f;
		}
	}
	if (key == GLFW_KEY_3)
	{
		if (theWindow->articulaciong2 + 10.0f <= 45.0f)
		{
			theWindow->articulaciong2 += 10.0f;
		}
		else
		{
			theWindow->articulaciong2 = 45.0f;
		}
	}
	if (key == GLFW_KEY_4)
	{
		if (theWindow->articulaciong2 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong2 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong2 = -45.0f;
		}
	}
	if (key == GLFW_KEY_5)
	{
		if (theWindow->articulaciong3 + 10.0f <= 45.0f)
		{
			theWindow->articulaciong3 += 10.0f;
		}
		else
		{
			theWindow->articulaciong3 = 45.0f;
		}
	}
	if (key == GLFW_KEY_6)
	{
		if (theWindow->articulaciong3 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong3 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong3 = -45.0f;
		}
	}
	if (key == GLFW_KEY_7)
	{
		if (theWindow->articulaciong4 + 10.0f <= 45.0f)
		{
			theWindow->articulaciong4 += 10.0f;
		}
		else
		{
			theWindow->articulaciong4 = 45.0f;
		}
	}
	if (key == GLFW_KEY_8)
	{
		if (theWindow->articulaciong4 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong4 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong4 = -45.0f;
		}
	}
	if (key == GLFW_KEY_9)
	{
		if (theWindow->articulaciong5 + 10.0f <= 0.0f)
		{
			theWindow->articulaciong5 += 10.0f;
		}
		else
		{
			theWindow->articulaciong5 = 0.0f;
		}
	}
	if (key == GLFW_KEY_0)
	{
		if (theWindow->articulaciong5 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong5 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong5 = -45.0f;
		}
	}

	if (key == GLFW_KEY_R)
	{
		if (theWindow->articulaciong6 + 10.0f <= 0.0f)
		{
			theWindow->articulaciong6 += 10.0f;
		}
		else
		{
			theWindow->articulaciong6 = 0.0f;
		}
	}
	if (key == GLFW_KEY_T)
	{
		if (theWindow->articulaciong6 - 10.0f >= -45.0f)
		{
			theWindow->articulaciong6 -= 10.0f;
		}
		else
		{
			theWindow->articulaciong6 = -45.0f;
		}
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->articulaciong7 += 10.0f;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow->articulaciong7 -= 10.0f;
	}
	if (key == GLFW_KEY_I)
	{
		theWindow->articulaciong7 += 10.0f;
		theWindow->carrozaPosZ += 0.4f; // Avanza
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->articulaciong7 -= 10.0f;
		theWindow->carrozaPosZ -= 0.4f; // Retrocede
	}



	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
