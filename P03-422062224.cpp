//práctica 3: Modelado Geométrico y Cámara Sintética.
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<MeshColor*> meshColorList;
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks




void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Pirámide triangular equilatera
void CrearPiramideTriangular()
{
	unsigned int indices_piramide_triangular[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
	};
	GLfloat vertices_piramide_triangular[] = {
	-0.5f, -0.5f, -0.2887f, // V0
	 0.5f, -0.5f, -0.2887f, // V1
	 0.0f, -0.5f,  0.5774f, // V2
	 0.0f,  0.5f,  0.0f     // V3 (ápice)
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_piramide_triangular, indices_piramide_triangular, 12, 12);
	meshList.push_back(obj1);

}
/*
Crear cilindro, cono y esferas con arreglos dinámicos vector creados en el Semestre 2023 - 1 : por Sánchez Pérez Omar Alejandro
*/
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los vértices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el círculo
		else {
			x = R * cos((0)*dt);
			z = R * sin((0)*dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los vértices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh *cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//función para crear un cono
void CrearCono(int res,float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);
	
	//ciclo for para crear los vértices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res+2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh *cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}

void CrearT()
{
	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.2887f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f,  0.5774f, 0.0f, 0.0f, 0.0f
	};
	MeshColor* piramideT = new MeshColor();
	piramideT->CreateMeshColor(vertices, 18);
	meshColorList.push_back(piramideT);
}

//función para crear pirámide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	vector<unsigned int> piramidecuadrangular_indices = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	vector<GLfloat> piramidecuadrangular_vertices = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh *piramide = new Mesh();
	piramide->CreateMeshGeometry(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramide);
}

void CrearPiramideColoreada()
{
	GLfloat vertices[] = {
		// Cara 1 (magenta)
		0.0f, 0.5f, 0.0f,      1.0f, 0.0f, 1.0f,
	   -0.5f, -0.5f, -0.2887f, 1.0f, 0.0f, 1.0f, 
		0.5f, -0.5f, -0.2887f, 1.0f, 0.0f, 1.0f, 

		// Cara 2 (verde)
		0.0f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 
		0.5f, -0.5f, -0.2887f, 0.0f, 1.0f, 0.0f, 
		0.0f, -0.5f,  0.5774f, 0.0f, 1.0f, 0.0f, 

		// Cara 3 (cyan)
		0.0f, 0.5f, 0.0f,      0.0f, 1.0f, 1.0f, 
		0.0f, -0.5f,  0.5774f, 0.0f, 1.0f, 1.0f, 
	   -0.5f, -0.5f, -0.2887f, 0.0f, 1.0f, 1.0f, 

	   // Base (amarillo)
	  -0.5f, -0.5f, -0.2887f, 1.0f, 1.0f, 0.0f,
	   0.5f, -0.5f, -0.2887f, 1.0f, 1.0f, 0.0f,
	   0.0f, -0.5f,  0.5774f, 1.0f, 1.0f, 0.0f 
	};
	MeshColor* piramide = new MeshColor();
	piramide->CreateMeshColor(vertices, 72);
	meshColorList.push_back(piramide);
}



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(1200, 800);
	mainWindow.Initialise();
	//Cilindro y cono reciben resolución (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//índice 0 en MeshList
	CrearPiramideTriangular();//índice 1 en MeshList
	CrearCilindro(5, 1.0f);//índice 2 en MeshList
	CrearCono(25, 2.0f);//índice 3 en MeshList
	CrearPiramideCuadrangular();//índice 4 en MeshList
	CreateShaders();
	CrearPiramideColoreada();// 0 en MeshColorList

	/*Cámara se usa el comando: glm::lookAt(vector de posición, vector de orientación, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posición,
	glm::vec3 vector up,
	GlFloat yaw rotación para girar hacia la derecha e izquierda
	GlFloat pitch rotación para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posición inicial está en 0,0,1 y ve hacia 0,0,-1.
	*/
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);

	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	CrearT();
	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f,0.0f,0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{
		
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//Cámara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		model = glm::mat4(1.0);
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));		
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh(); //dibuja cubo y pirámide triangular
		//meshList[3]->RenderMeshGeometry(); //dibuja las figuras geométricas cilindro, cono, pirámide base cuadrangular
		//sp.render(); //dibuja esfera
		

		glClearColor(1.0F,1.0F,1.0F, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		// PIRAMIDE
		// BASE
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(shaderList[0].getColorLocation(), 1, glm::value_ptr(color));
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMeshGeometry();

		float escala = 0.31f; // escala de todas las pirámides de aristas
		// SUPERIOR
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		uniformView = shaderList[1].getViewLocation();

		float y_apice = 0.5f;
		float y_offset = y_apice - (0.5f * escala);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, y_offset+0.01, 0.0f));
		model = glm::scale(model, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[1]->RenderMeshColor();

		// ESQUINAS INFERIORES
		glm::vec3 esquinasBase[3] = {
			glm::vec3(-0.5f, -0.5f, -0.2887f),
			glm::vec3( 0.5f, -0.5f, -0.2887f),
			glm::vec3( 0.0f, -0.5f,  0.5774f)
		};

		glm::vec3 esquinaLocal[3] = {
			glm::vec3(-0.5f, -0.5f, -0.2887f),
			glm::vec3(0.5f, -0.5f, -0.2887f),
			glm::vec3(0.0f, -0.5f,  0.5774f),
		};

		glm::mat4 modelEsquina = glm::mat4(1.0f);
		modelEsquina = glm::translate(modelEsquina, esquinasBase[0] - (escala * esquinaLocal[0]));
		modelEsquina = glm::translate(modelEsquina, glm::vec3(-0.01f,-0.01f,-0.01f));
		modelEsquina = glm::scale(modelEsquina, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelEsquina));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelEsquina = glm::mat4(1.0f);
		modelEsquina = glm::translate(modelEsquina, esquinasBase[1] - (escala * esquinaLocal[1]));
		modelEsquina = glm::translate(modelEsquina, glm::vec3(0.01f, -0.01f, -0.01f));
		modelEsquina = glm::scale(modelEsquina, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelEsquina));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelEsquina = glm::mat4(1.0f);
		modelEsquina = glm::translate(modelEsquina, esquinasBase[2] - (escala * esquinaLocal[2]));
		modelEsquina = glm::translate(modelEsquina, glm::vec3(0.0f, -0.01f, 0.01f));
		modelEsquina = glm::scale(modelEsquina, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelEsquina));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// MEDIAS INFERIORES
		glm::vec3 mediosBase[3] = {
			(glm::vec3(-0.5f, -0.5f, -0.2887f) + glm::vec3(0.5f, -0.5f, -0.2887f)) * 0.5f,
			(glm::vec3(0.5f, -0.5f, -0.2887f) + glm::vec3(0.0f, -0.5f, 0.5774f)) * 0.5f,
			(glm::vec3(0.0f, -0.5f, 0.5774f) + glm::vec3(-0.5f, -0.5f, -0.2887f)) * 0.5f
		};
		glm::vec3 medioLocal[3] = {
			(glm::vec3(-0.5f, -0.5f, -0.2887f) + glm::vec3(0.5f, -0.5f, -0.2887f)) * 0.5f,
			(glm::vec3(0.5f, -0.5f, -0.2887f) + glm::vec3(0.0f, -0.5f, 0.5774f)) * 0.5f,
			(glm::vec3(0.0f, -0.5f, 0.5774f) + glm::vec3(-0.5f, -0.5f, -0.2887f)) * 0.5f
		};

		glm::mat4 modelMedio = glm::mat4(1.0f);
		modelMedio = glm::translate(modelMedio, mediosBase[0] - (escala * medioLocal[0]));
		modelMedio = glm::translate(modelMedio, glm::vec3(0.0f, -0.01f, -0.01f));
		modelMedio = glm::scale(modelMedio, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMedio));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelMedio = glm::mat4(1.0f);
		modelMedio = glm::translate(modelMedio, mediosBase[1] - (escala * medioLocal[1]));
		modelMedio = glm::translate(modelMedio, glm::vec3(0.0f, -0.01f, 0.01f));
		modelMedio = glm::scale(modelMedio, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMedio));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelMedio = glm::mat4(1.0f);
		modelMedio = glm::translate(modelMedio, mediosBase[2] - (escala * medioLocal[2]));
		modelMedio = glm::translate(modelMedio, glm::vec3(-0.01f, -0.01f, 0.01f));
		modelMedio = glm::scale(modelMedio, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMedio));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// MEDIAS MEDIAS
		// Como referencia local tomamos el ápice de la pirámide coloreada (0,0.5,0)
		glm::vec3 top(0.0f, 0.5f, 0.0f);

		glm::vec3 base1(-0.5f, -0.5f, -0.2887f);
		glm::vec3 base2(0.5f, -0.5f, -0.2887f);
		glm::vec3 base3(0.0f, -0.5f, 0.5774f);

		glm::vec3 mediosLaterales[3] = {
			(top + base1) / 2.8f,// calculados a mano
			(top + base2) / 2.8f,
			(top + base3) / 2.8f
		};

		for (int i = 0; i < 3; i++) {
			shaderList[1].useShader();
			uniformModel = shaderList[1].getModelLocation();
			uniformProjection = shaderList[1].getProjectLocation();
			uniformView = shaderList[1].getViewLocation();

			glm::mat4 modelMedioMedio = glm::mat4(1.0f);
			modelMedioMedio = glm::translate(modelMedioMedio, mediosLaterales[i]);
			modelMedioMedio = glm::translate(modelMedioMedio, glm::vec3(0.0f, 0.0f, 0.0f));
			modelMedioMedio = glm::scale(modelMedioMedio, glm::vec3(escala, escala, escala));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMedioMedio));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			meshColorList[0]->RenderMeshColor();
		}


		// PIRÁMIDES INVERTIDAS EN EL CENTRO

		escala = 0.25f; // escala de todas las pirámides del centro

		// Obtenemos los ejes de rotación para darle ángulo a las caras
		glm::vec3 apexNegra(0.0f, 0.5f, 0.0f);
		glm::vec3 mitadLado = (base2 + base3) * 0.5f;
		mitadLado.y = apexNegra.y;
		glm::vec3 ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		glm::vec3 aux(0.0f, 1.0f, 0.0f);
		glm::vec3 ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular

		glm::mat4 modelInvertida = glm::mat4(1.0f);
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.11f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base1 + base2) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular

		modelInvertida = glm::mat4(1.0f);
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.11f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base3 + base1) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular

		modelInvertida = glm::mat4(1.0f);
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.11f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();




		// PIRAMIDES INVERTIDAS INFERIORES

		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base3 + base1) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base3 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base1;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f,0.5f,0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base3 + base1) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base1 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base3;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f, 0.5f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base1 + base2) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base1 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base2;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f, 0.5f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base1 + base2) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base2 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base1;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f, 0.5f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base2 + base3) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base2 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base3;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f, 0.5f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// Obtenemos los ejes de rotación para darle ángulo a las caras
		mitadLado = (base2 + base3) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - apexNegra;  // vector desde punta hasta mitad del lado
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::mat4(1.0f);

		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 0.04f);
		modelInvertida = glm::rotate(modelInvertida, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelInvertida = glm::rotate(modelInvertida, glm::radians(-32.0f), ejePerpendicular);
		modelInvertida = glm::scale(modelInvertida, glm::vec3(escala, escala, escala));

		mitadLado = (base3 + apexNegra) * 0.5f;
		mitadLado.y = apexNegra.y;
		ejeRotacion = mitadLado - base2;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelInvertida = glm::translate(modelInvertida, ejeRotacion * 1.2f);
		modelInvertida = glm::translate(modelInvertida, glm::vec3(0.0f, 0.5f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelInvertida));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// PIRAMIDES DE ABAJO

		glm::mat4 modelAbajo = glm::mat4(1.0f);
		modelAbajo = glm::translate(modelAbajo, glm::vec3(0.0f, -0.38f, 0.0f));
		modelAbajo = glm::scale(modelAbajo, glm::vec3(escala, escala, escala));
		modelAbajo = glm::rotate(modelAbajo, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mitadLado = (base1 + base2) * 0.5f;
		ejeRotacion = mitadLado - base3;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelAbajo = glm::translate(modelAbajo, ejeRotacion * 0.8f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelAbajo));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelAbajo = glm::mat4(1.0f);
		modelAbajo = glm::translate(modelAbajo, glm::vec3(0.0f, -0.38f, 0.0f));
		modelAbajo = glm::scale(modelAbajo, glm::vec3(escala, escala, escala));
		modelAbajo = glm::rotate(modelAbajo, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mitadLado = (base2 + base3) * 0.5f;
		ejeRotacion = mitadLado - base1;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelAbajo = glm::translate(modelAbajo, ejeRotacion * 0.8f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelAbajo));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();

		modelAbajo = glm::mat4(1.0f);
		modelAbajo = glm::translate(modelAbajo, glm::vec3(0.0f, -0.38f, 0.0f));
		modelAbajo = glm::scale(modelAbajo, glm::vec3(escala, escala, escala));
		modelAbajo = glm::rotate(modelAbajo, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mitadLado = (base3 + base1) * 0.5f;
		ejeRotacion = mitadLado - base2;  // vector desde mitad de lado hasta vertice de base
		ejeRotacion = glm::normalize(ejeRotacion); // normalizar
		ejePerpendicular = glm::normalize(glm::cross(ejeRotacion, aux)); // perpendicular
		modelAbajo = glm::translate(modelAbajo, ejeRotacion * 0.8f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelAbajo));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshColorList[0]->RenderMeshColor();


		// LINEAS DE ARISTAS

		GLfloat piramide_aristas[] = {
		0.0f,  0.5f,  0.0f,     // V3 (ápice)
		-0.5f, -0.5f, -0.2887f, // V0
		0.0f,  0.5f,  0.0f,     // V3 (ápice)
		0.5f, -0.5f, -0.2887f,  // V1
		0.0f,  0.5f,  0.0f,     // V3 (ápice)
		0.0f, -0.5f,  0.5774f,  // V2
		-0.5f, -0.5f, -0.2887f, // V0
		0.5f, -0.5f, -0.2887f,  // V1
		0.5f, -0.5f, -0.2887f,  // V1
		0.0f, -0.5f,  0.5774f,  // V2
		0.0f, -0.5f,  0.5774f,  // V2
		-0.5f, -0.5f, -0.2887f  // V0
		};

		int numAristas = sizeof(piramide_aristas) / (sizeof(GLfloat) * 6); // 6 aristas

		for (int i = 0; i < numAristas * 6; i += 6) {
			glm::vec3 puntoA = glm::vec3(
				piramide_aristas[i],
				piramide_aristas[i + 1],
				piramide_aristas[i + 2]
			);

			glm::vec3 puntoB = glm::vec3(
				piramide_aristas[i + 3],
				piramide_aristas[i + 4],
				piramide_aristas[i + 5]
			);

			glm::vec3 puntoMedio = (puntoA + puntoB) * 0.5f;
			float longitud = glm::distance(puntoA, puntoB);
			glm::vec3 direccion = glm::normalize(puntoB - puntoA);
			glm::vec3 ejeUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 ejeRotacion = glm::cross(ejeUp, direccion);
			float angulo = acos(glm::dot(ejeUp, direccion));

			CrearCilindro(16, 0.025f);
			shaderList[0].useShader();
			uniformModel = shaderList[0].getModelLocation();
			color = glm::vec3(0.0f, 0.0f, 0.0f);
			glUniform3fv(shaderList[0].getColorLocation(), 1, glm::value_ptr(color));

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, puntoMedio);
			model = glm::rotate(model, angulo, ejeRotacion);
			model = glm::scale(model, glm::vec3(1.0f, longitud, 1.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			meshList.back()->RenderMeshGeometry();
		}





		/*
		//ejercicio: Instanciar primitivas geométricas para recrear el dibujo de la práctica pasada en 3D,
		//se requiere que exista piso y la casa tiene una ventana azul circular justo en medio de la pared trasera y solo 1 puerta frontal.
		model = glm::mat4(1.0f);
		color=glm::vec3(0.0f,1.0f,0.0f);
		//Opcional duplicar esta traslación inicial para posicionar en -Z a los objetos en el mismo punto
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.75f, -2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMeshGeometry();
		*/

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}

	
		