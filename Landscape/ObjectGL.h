#pragma once

#include "Lib.h"
#include <math.h>

#ifndef OBJECTGL_H
#define OBJECTGL_H

#define  PI   3.14159265358979323846

typedef struct 
{
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	int nTriangles;
	// Vertici
	vector<vec3> vertici;
	vector<vec4> colors;
	// Numero vertici
	int nv;
	//Matrice di Modellazione: Traslazione*Rotazione*Scala
	mat4 Model;
	float step;
} ObjectGL;


void build_triangle(ObjectGL* fig) {
	fig->vertici.push_back(vec3(-0.5f, -0.5f, 0.0));
	fig->vertici.push_back(vec3(0.5f, -0.5f, 0.0));
	fig->vertici.push_back(vec3(0.0f, 0.5f, 0.0));

	fig->colors.push_back(vec4(1.0, 0.9, 0.0, 1.0));
	fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));

	fig->nv = fig->vertici.size();
}

void build_star(ObjectGL* fig, int nTriangles) {
	float t;
	fig->nTriangles = nTriangles;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(0.0, 0.0, 0.0));
	fig->colors.push_back(vec4(1.0, 0.8627, 0.0, 1.0000));

	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;

		if (i % 2 == 0)
			fig->vertici.push_back(vec3(cos(t), sin(t), 0.0));
		else
			fig->vertici.push_back(vec3(0.5 * cos(t), 0.5 * sin(t), 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 0.9, 0.9, 0.8));
	}
	fig->nv = fig->vertici.size();
}

void build_butterfly(ObjectGL* fig, int nTriangles, float cx, float cy, float raggiox, float raggioy) {
	float t;
	fig->nTriangles = nTriangles;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3((sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, 0.0));
		fig->colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));
	}
	fig->nv = fig->vertici.size();
}

void build_circle(ObjectGL* fig, float cx, float cy, float raggiox, float raggioy) {
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(vec4(237 / 255.0f, 1.0, 033 / 255.0f, 1.0));
	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3(cx + (cos(t) * raggiox), cy + (sin(t) * raggioy), 0.0));
		//Colore 
		fig->colors.push_back(vec4(237 / 255.0f, 1.0, 033 / 255.0f, 1.0));
	}
	fig->nv = fig->vertici.size();
}

void build_circle(ObjectGL* fig, float cx, float cy, float r, vec4 color) {
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(vec4(1.0, 0, 0, 1.0));
	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3(cx + (cos(t) * r), cy + (sin(t) * r), 0.0));
		//Colore 
		fig->colors.push_back(color);
	}
	fig->nv = fig->vertici.size();
}


void build_square(ObjectGL* fig, vec4 p1, vec4 p2, vec4 p3, vec4 p4) {
	fig->nTriangles = 2;

	fig->vertici.push_back(vec3(0.0, 0.0, 0.0));
	fig->vertici.push_back(vec3(1.0, 0.0, 0.0));
	fig->vertici.push_back(vec3(0.0, 1.0, 0.0));
	fig->vertici.push_back(vec3(1.0, 1.0, 0.0));

	fig->colors.push_back(p1);
	fig->colors.push_back(p2);
	fig->colors.push_back(p3);
	fig->colors.push_back(p4);

	fig->nv = fig->vertici.size();
}

void build_mountains(ObjectGL* fig, int nTriangles, float cx, float cy) {
	fig->nTriangles = nTriangles;
	fig->step = 1.0f / float(fig->nTriangles);
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3(cx + sin(2 * PI * t), cy + abs(sin(2 * PI * t)), 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));
	}
	fig->nv = fig->vertici.size();
}

void crea_VAO_Vector(ObjectGL* fig)
{
	glGenVertexArrays(1, &fig->VAO);
	glBindVertexArray(fig->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &fig->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, fig->vertici.size() * sizeof(vec3), fig->vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &fig->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}
#endif 
