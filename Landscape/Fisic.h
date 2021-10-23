#pragma once
#include "Lib.h"
#include <math.h>

#ifndef FISIC_H
#define FISIC_H

typedef struct {
	float x, xo;
	float y, yo;
	float vo;
	float a;
	float t;
	float e;
} EqFisic;


float compute_eq_y(EqFisic* eq) {
	eq->y = eq->yo + (sin(radians(eq->e)) * (eq->t * eq->vo)) + ((eq->a * pow(eq->t, 2)) / 2);
	return eq->y;
}

float compute_eq_x(EqFisic* eq) {
	eq->x = eq->xo + (cos(radians(eq->e)) * (eq->t * eq->vo));
	return eq->x;
}

void compute_tocca(EqFisic* eq) {

}

void reset_time(EqFisic* eq) {
	eq->t = 0.0f;
}

void set_eq_init(EqFisic* eq, float xo, float yo, float vo, float t) {
	eq->xo = xo;
	eq->yo = yo;
	eq->vo = vo;
	eq->t = t;
}




#endif

