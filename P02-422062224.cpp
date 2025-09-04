//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
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
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
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



void CrearLetrasyFiguras()
{
	GLfloat vertices_triangulorojo[] = { // 0
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);


	GLfloat vertices_cuadradoverde[] = { // 1
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


	GLfloat vertices_trianguloazul[] = { // 2
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f
	};
	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);


	GLfloat vertices_trianguloverde[] = { // 3
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
	};
	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);


	GLfloat vertices_cuadradocafe[] = { // 4
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,

	};
	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);


	GLfloat vertices_cuadradorojo[] = { // 5
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);


	GLfloat vertices_letras_colores[] = { // 6
		// J (rojo)
		-0.4f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.4f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,

		-0.4f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,

		-0.6f, -0.8f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f, -0.8f, 0.0f,   1.0f, 0.0f, 0.0f,

		-0.6f, -0.8f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.6f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,

		// H (verde)
		-0.1f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.1f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,

		-0.1f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,

		 0.3f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.3f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,

		 0.3f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f,  0.8f, 0.0f,   0.0f, 1.0f, 0.0f,

		-0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,

		-0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.4f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,

		 // C (azul)
		 0.6f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.6f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f,

		 0.6f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f,

		 0.6f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.6f, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,

		 0.6f, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.9f, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,

		 0.6f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.7f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.6f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,

		 0.6f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.7f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.7f,  0.8f, 0.0f,   0.0f, 0.0f, 1.0f,
	};
	MeshColor* letrasJHC = new MeshColor();
	letrasJHC->CreateMeshColor(vertices_letras_colores, sizeof(vertices_letras_colores) / sizeof(GLfloat));
	meshColorList.push_back(letrasJHC);
}


void Crear3D()
{
	GLfloat cuborojo_vertices[] = { // 7
				-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

				 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

				 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

				 -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f
	};
	MeshColor* cuboRojo = new MeshColor();
	cuboRojo->CreateMeshColor(cuborojo_vertices, 216);
	meshColorList.push_back(cuboRojo);


	
	// Cubo verde
	GLfloat cuboverde_vertices[] = { // 8
		// Cara frontal
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

		// Cara trasera
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

		// Cara izquierda
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

		// Cara derecha
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

		// Cara superior
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

		// Cara inferior
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f
	};
	MeshColor* cuboVerde = new MeshColor();
	cuboVerde->CreateMeshColor(cuboverde_vertices, 216);
	meshColorList.push_back(cuboVerde);

	// Cubo caf�
	GLfloat cubocafe_vertices[] = { // 9
		// Cara frontal
		-0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,

		// Cara trasera
		-0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,

		// Cara izquierda
		-0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,

		// Cara derecha
		 0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,

		// Cara superior
		-0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f,  0.5f,  0.5f, 0.478f, 0.255f, 0.067f,

		// Cara inferior
		-0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		 0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f, -0.5f, 0.478f, 0.255f, 0.067f,
		-0.5f, -0.5f,  0.5f, 0.478f, 0.255f, 0.067f
	};
	MeshColor* cuboCafe = new MeshColor();
	cuboCafe->CreateMeshColor(cubocafe_vertices, 216);
	meshColorList.push_back(cuboCafe);

	// Pir�mide azul
	GLfloat piramideazul_vertices[] = { // 10
		// Base
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		// Lado 1
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.0f, 1.0f,
		// Lado 2
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.0f, 1.0f,
		// Lado 3
		 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.0f, 1.0f
	};
	MeshColor* piramideAzul = new MeshColor();
	piramideAzul->CreateMeshColor(piramideazul_vertices, 18 * 2); // 6 tri�ngulos * 3 v�rtices * 6 valores
	meshColorList.push_back(piramideAzul);

	// Pir�mide verde
	GLfloat piramideverde_vertices[] = { // 11
		// Base
		-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f,
		// Lado 1
		-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.5f, 0.0f,
		// Lado 2
		 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.5f, 0.0f,
		// Lado 3
		 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		 0.0f,  0.5f, -0.25f, 0.0f, 0.5f, 0.0f
	};
	MeshColor* piramideVerde = new MeshColor();
	piramideVerde->CreateMeshColor(piramideverde_vertices, 18 * 2);
	meshColorList.push_back(piramideVerde);
}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	Crear3D();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(80.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();



		// LETRAS DE COLORES
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -49.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();



		// CASA 3D
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.01;

		// CUBO ROJO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();

		// TECHO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.0f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[10]->RenderMeshColor();

		// VENTANAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, -0.2f, -2.4f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[8]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, -0.2f, -2.4f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[8]->RenderMeshColor();

		// PUERTA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -2.4f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[8]->RenderMeshColor();

		// �RBOL IZQUIERDO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.2f, -0.7f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[9]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.2f, -0.3f, -2.8f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[11]->RenderMeshColor();

		// �RBOL DERECHO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.2f, -0.7f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[9]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.2f, -0.3f, -2.8f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[11]->RenderMeshColor();













		//Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}

// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/