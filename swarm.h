
#include "particles.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SWARM_H
#define SWARM_H

typedef struct {
  int Nprey;      // número de presas
  particle *prey; // conjunto de presas

  int Npred;      // número de predadores
  particle *pred; // conjunto de predadores

  int dim;       // dimensão
  double *x_opt; // posição ótima das presas

  // Vetores-coeficientes
  double *c1;
  double *c2;
  double *c3;
} swarm;

void initSwarm(swarm *S, int Nprey, int Npred, int dim, double *c1, double *c2,
               double *c3);
void freeSwarm(swarm *S);
void updateSwarm(swarm *S, double (*cost)(double *));

#endif
