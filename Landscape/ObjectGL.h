#pragma once
#include "Lib.h"
#include <math.h>

#ifndef OBJECTGL_H
#define OBJECTGL_H

#define  PI   3.14159265358979323846
#define VEC3ZERO vec3(0.0f, 0.0f, 0.0f)
#define WIDTH 1280.0f
#define HEIGHT 720.0f
#define RGB 255.0f

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
	float dx, dy;
	float scalex, scaley;
	float angle;
} ObjectGL;

float f_RGB(int value) {
	return value / RGB;
}

vec4 vec_RGBA(int r, int g, int b, int a) {
	return vec4(f_RGB(r), f_RGB(g), f_RGB(b), f_RGB(a));
}

vec4 vec_RGBA(int r, int g, int b) {
	return vec4(f_RGB(r), f_RGB(g), f_RGB(b), f_RGB(255));
}

vec4 vec_RGBA(float r, float g, float b, float a) {
	return vec4(r, g, b, a);
}
vec4 vec_RGBA(float r, float g, float b) {
	return vec4(r, g, b, 1.0f);
}

void build_triangle(ObjectGL* fig, vec4 color1, vec4 color2, vec4 color3) {
	fig->vertici.push_back(vec3(-0.5f, -0.5f, 0.0));
	fig->vertici.push_back(vec3(0.5f, -0.5f, 0.0));
	fig->vertici.push_back(vec3(0.0f, 0.5f, 0.0));
	fig->nv = fig->vertici.size();
	fig->nTriangles = fig->nv%3;

	fig->colors.push_back(color1);
	fig->colors.push_back(color2);
	fig->colors.push_back(color3);
}

void build_star(ObjectGL* fig, int nTriangles, float cx, float cy, vec4 colorIntern, vec4 colorExtern) {
	fig->nTriangles = nTriangles;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0f));
	fig->colors.push_back(colorIntern);

	float t;
	for (int i = 0; i <= fig->nTriangles; i++) {
		t = (float)i * fig->step;

		if (i % 2 == 0)
			fig->vertici.push_back(vec3(cos(t), sin(t), 0.0));
		else
			fig->vertici.push_back(vec3(0.5 * cos(t), 0.5 * sin(t), 0.0));
		fig->colors.push_back(colorExtern);
	}
	fig->nv = fig->vertici.size();
}

void build_star(ObjectGL* fig, int nTriangles, vec4 colorIntern, vec4 colorExtern) {
	build_star(fig, nTriangles, 0.0f, 0.0f, colorIntern, colorExtern);
}

void build_butterfly(ObjectGL* fig, int nTriangles, float cx, float cy, float rx, float ry, vec4 colorIntern, vec4 colorExtern) {
	fig->nTriangles = nTriangles;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0f));
	fig->colors.push_back(colorIntern);

	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3((sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4,
			(cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, 0.0));
		fig->colors.push_back(colorExtern);
	}
	fig->nv = fig->vertici.size();
}

void build_butterfly(ObjectGL* fig, int nTriangles, float rx, float ry, vec4 colorIntern, vec4 colorExtern) {
	build_butterfly(fig, nTriangles, 0.0f, 0.0f, rx, ry, colorIntern, colorExtern);
}

void build_oval(ObjectGL* fig, int nTriangles, float cx, float cy, float rx, float ry, vec4 colorInter, vec4 colorExtern) {
	fig->nTriangles = nTriangles;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(colorInter);

	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * fig->step;
		fig->vertici.push_back(vec3(cx + (cos(t) * rx), cy + (sin(t) * ry), 0.0));
		fig->colors.push_back(colorExtern);
	}
	fig->nv = fig->vertici.size();
}

void build_oval(ObjectGL* fig, int nTriangles, float rx, float ry, vec4 colorInter, vec4 colorExtern) {
	build_oval(fig, nTriangles, 0.0f, 0.0f, rx, ry, colorInter, colorExtern);
}

void build_circle(ObjectGL* fig, int nTriangles, float cx, float cy, float r, vec4 colorInter, vec4 colorExtern) {
	build_oval(fig, nTriangles, cx, cy, r, r, colorInter, colorExtern);
}

void build_circle(ObjectGL* fig, int nTriangles, float r, vec4 colorInter, vec4 colorExtern) {
	build_oval(fig, nTriangles, 0.0f, 0.0f, r, r, colorInter, colorExtern);
}

void build_palaEolica(ObjectGL* fig, int nTriangles, float cx, float cy, float r, vec4 colorInter, vec4 colorExtern) {
	fig->nTriangles = nTriangles * 2;
	fig->step = (2 * PI) / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(colorInter);
	float t;
	for (int i = 0; i <= fig->nTriangles; i++)
	{
		t = (float) (i+1) * (PI / nTriangles);
		fig->vertici.push_back(vec3(cx + (cos(t) * r), cy + (sin(t) * r), 0.0));
		fig->colors.push_back(colorExtern);

		if (i % 2 == 0) {
			fig->vertici.push_back(vec3(cx, cy, 0.0));
			fig->colors.push_back(colorExtern);
		}
	}
	fig->nv = fig->vertici.size();
}

void build_palaEolica(ObjectGL* fig, int nTriangles, float r, vec4 colorInter, vec4 colorExtern) {
	build_palaEolica(fig, nTriangles, 0.0f, 0.0f, r, colorInter, colorExtern);
}

void build_square(ObjectGL* fig, vec4 p1, vec4 p2, vec4 p3, vec4 p4) {
	fig->vertici.push_back(vec3(0.0, 0.0, 0.0));
	fig->vertici.push_back(vec3(1.0, 0.0, 0.0));
	fig->vertici.push_back(vec3(0.0, 1.0, 0.0));
	fig->vertici.push_back(vec3(1.0, 1.0, 0.0));
	fig->nv = fig->vertici.size();
	fig->nTriangles = fig->nv % 2;

	fig->colors.push_back(p1);
	fig->colors.push_back(p2);
	fig->colors.push_back(p3);
	fig->colors.push_back(p4);
}

void build_square(ObjectGL* fig, vec4 color) {
	build_square(fig, color, color, color, color);
}

void build_mountain(ObjectGL* fig, int nTriangles, float cx, float cy, vec4 colorIntern, vec4 colorExtern) {
	fig->nTriangles = nTriangles;
	fig->step = 1.0f / fig->nTriangles;
	fig->vertici.push_back(vec3(cx, cy, 0.0));
	fig->colors.push_back(colorIntern);

	float t;
	for (int i = 0; i <= (fig->nTriangles / 2); i++)
	{
		t = (float)i * fig->step;

		fig->vertici.push_back(vec3(t, 0.0, 0.0));
		fig->vertici.push_back(vec3(t, abs(sin(2 * PI * t)), 0.0));

		fig->colors.push_back(colorIntern);
		fig->colors.push_back(colorExtern);
	}
	fig->nv = fig->vertici.size();
	fig->nTriangles = fig->nv - 3;
}

void build_mountain(ObjectGL* fig, int nTriangles, vec4 colorIntern, vec4 colorExtern) {
	build_mountain(fig, nTriangles, 0.0f, 0.0f, colorIntern, colorExtern);
}

void create_VAO_VBO_vertex(ObjectGL* fig)
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

void set_value_transfom_2D(ObjectGL* fig, float dx, float dy, float scalex, float scaley, float angle) {
	fig->dx = dx;
	fig->dy = dy;
	fig->scalex = scalex;
	fig->scaley = scaley;
	fig->angle = angle;
}

void transform(ObjectGL* fig, GLuint matModel) {
	fig->Model = mat4(1.0);
	fig->Model = translate(fig->Model, vec3(fig->dx, fig->dy, 1.0f));
	fig->Model = scale(fig->Model, vec3(fig->scalex, fig->scaley, 1.0f));
	fig->Model = rotate(fig->Model, radians(fig->angle), vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(matModel, 1, GL_FALSE, value_ptr(fig->Model));
}
#endif 
