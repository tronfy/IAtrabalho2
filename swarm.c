#include "swarm.h"
#include "particles.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void initSwarm(swarm *S, int Nprey, int Npred, int dim, double *c1, double *c2,
               double alpha, double lambda, double A) {
  /*
      Inicializa um enxame com posições aleatórias para as partículas.
      Nprey: número de presas
      Npred: número de predadores
      dim: dimensão do espaço de busca
  */

  // srand(time(NULL));
  srand(0);

  // == presas ==
  S->prey = malloc(Nprey * sizeof(particle));
  assert(S->prey);

  for (int i = 0; i < Nprey; i++) {
    double aux_x[dim];
    for (int s = 0; s < dim; s++) {
      aux_x[s] = ((double)rand()) / ((double)RAND_MAX);
      aux_x[s] = 2 * aux_x[s] - 1;
    }
    initParticle(&S->prey[i], dim, aux_x);
  }
  // Posição ótima inicial é também aleatória
  S->x_opt = malloc(dim * sizeof(double));
  assert(S->x_opt);
  for (int s = 0; s < dim; s++) {
    S->x_opt[s] = ((double)rand()) / ((double)(RAND_MAX));
    S->x_opt[s] = 2 * S->x_opt[s] - 1;
  }

  // == predadores ==
  S->pred = malloc(Npred * sizeof(particle));
  assert(S->pred);

  for (int i = 0; i < Npred; i++) {
    double aux_x[dim];
    for (int s = 0; s < dim; s++) {
      aux_x[s] = ((double)rand()) / ((double)RAND_MAX);
      aux_x[s] = 2 * aux_x[s] - 1;
    }
    initParticle(&S->prey[i], dim, aux_x);
  }

  // Dimensão
  S->dim = dim;
  // Vetores coeficientes
  S->c1 = c1;
  S->c2 = c2;
  // Parâmetros
  S->alpha = alpha;
  S->lambda = lambda;
  S->A = A;

  S->Nprey = Nprey;
  S->Npred = Npred;
}

void freeSwarm(swarm *S) {
  if (S != NULL) {
    for (int i = 0; i < S->Nprey; i++) {
      freeParticle(&S->prey[i]);
    }
    free(S->prey);
  }
}

void updateSwarm(swarm *S, double (*cost)(double *)) {
  // Valor ótimo atual
  double f_opt = cost(S->x_opt);
  // Índice inicial da melhor partícula é -1
  int id_opt = -1;

  // TODO: atualizar presas (updatePreyVelocity) e predadores
  // (updatePredVelocity) separadamente

  // Atualiza posições das partículas e busca novo valor ótimo
  for (int i = 0; i < S->Nprey; i++) {
    updateVelocity(&S->prey[i], S->c1, S->c2, S->x_opt);
    updatePosition(&S->prey[i], cost);
    double f_new = cost(S->prey[i].x_opt);
    if (f_opt > f_new) {
      f_opt = f_new;
      id_opt = i;
    }
  }

  // Se melhorou ótimo atual, atualiza
  if (id_opt > -1) {
    copyArray(S->x_opt, S->prey[id_opt].x_opt, S->dim);
  }
}
