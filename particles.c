#include "particles.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initParticle(particle *p, int dim, double *x_0) {
  /*
      Inicializa uma partícula.
      p: partícular a ser inicializada
      dim: dimensão do espaço de busca
      x_0: posição inicial
  */
  // Posição inicial
  p->x = malloc(dim * sizeof(double));
  assert(p->x);
  copyArray(p->x, x_0, dim);
  // Posição ótima
  p->x_opt = malloc(dim * sizeof(double));
  assert(p->x_opt);
  copyArray(p->x_opt, x_0, dim);
  // Velocidade inicial é zero
  p->v = malloc(dim * sizeof(double));
  assert(p->v);
  for (int i = 0; i < dim; i++)
    p->v[i] = 0;
  // Dimensão
  p->dim = dim;
}

void freeParticle(particle *p) {
  if (p != NULL) {
    if (p->x != NULL)
      free(p->x);
    if (p->x_opt != NULL)
      free(p->x_opt);
    if (p->v != NULL)
      free(p->v);
  }
}

/*
void updateVelocity(particle *p, double *c1, double *c2, double *swarm_opt) {

  //    Função para atualizar a velocidade de uma partícula.
  //    p: partícula a ser atualizada
  //    c1 e c2: vetores de coeficientes
  //    swarm_opt: vetor ótimo do enxame
  
  // Termo individual da velocidade
  double *aux_sub1 = arraySub(p->x_opt, p->x, p->dim);
  double *aux_mul1 = arrayMul(c1, aux_sub1, p->dim);
  // Termo coletivo da velocidade
  double *aux_sub2 = arraySub(swarm_opt, p->x, p->dim);
  double *aux_mul2 = arrayMul(c2, aux_sub2, p->dim);
  // Ponteiro para velocidade anterior
  double *aux_v = p->v;
  // Atualiza velocidade
  double *aux_sum = arraySum(aux_mul1, aux_mul2, p->dim);
  p->v = arraySum(aux_v, aux_sum, p->dim);

  // Libera memória
  free(aux_sub1);
  free(aux_sub2);
  free(aux_mul1);
  free(aux_mul2);
  free(aux_v);
  free(aux_sum);
}


*/

void updatePreyVelocity(particle *p, double *c1, double *c2, double *swarm_opt, double *A, double lambda, double *Xpred) {
  //    Função para atualizar a velocidade de uma partícula.
  //    p:         ponteiro da partícula a ser atualizada
  //    c1 e c2:   vetores de coeficientes
  //    swarm_opt: vetor ótimo do enxame

  //    A:         vetor influência do predator
  //    lambda:    fator de escala para a distância predador-presa
  //    Xpred:     a posição média (t+1) do grupo de PREDADORES (supõe que está executando após updatePredPosition)
  
  // Termo individual da velocidade
  double *aux_sub1 = arraySub(p->x_opt, p->x, p->dim);
  double *aux_mul1 = arrayMul(c1, aux_sub1, p->dim);
  // Termo coletivo da velocidade
  double *aux_sub2 = arraySub(swarm_opt, p->x, p->dim);
  double *aux_mul2 = arrayMul(c2, aux_sub2, p->dim);
  // Ponteiro para velocidade anterior
  double *aux_v = p->v;
  // Atualiza velocidade
  double *aux_sum = arraySum(aux_mul1, aux_mul2, p->dim);
  p->v = arraySum(aux_v, aux_sum, p->dim);

  // Libera memória
  free(aux_sub1);
  free(aux_sub2);
  free(aux_mul1);
  free(aux_mul2);
  free(aux_v);
  free(aux_sum);

  // AQUI, P->v GUARDA O TERMO Vi(t+1) da eq (7). Falta somar A*exp{etc,etc...}
  // Calculo de A*exp(etc,etc)
  aux_sub1 = arraySub(p->x, Xpred, p->dim);                          // Xprey - Xpred
  double exponencial = exp((-lambda) * arrayNorm(aux_sub1, p->dim)); // exp(etc)
  double *aux_scale = arrayScale(A, exponencial, p->dim);            // A*exp(etc)
  aux_v = p->v;
  p->v = arraySum(p->v, aux_scale, p->dim);                          // Vi(t+1) + A*exp(etc)

  // Controle de velocidade
  if (arrayNorm(p->v, p->dim) >= V_MAX) {
    double* aux_v2 = p->v;
    p->v = arrayScale(p->v, V_MAX/arrayNorm(p->v, p->dim), p->dim);
    free(aux_v2);
  }

  free(aux_sub1);
  free(aux_scale);
  free(aux_v);

  return;
}

void updatePredVelocity(particle *p, double alpha, double *swarm_opt) {
  double *aux_sub = arraySub(swarm_opt, p->x, p->dim);
  double *aux_v = p->v;
  p->v = arrayScale(aux_sub, alpha, p->dim);

  free(aux_sub);
  free(aux_v);

  return;
}

void updatePreyPosition(particle *p, double (*cost)(double *)) {
  /*
      Função para atualizar a posição e posição ótima de uma PRESA.
      p: partícula a ser atualizada
      cost: função custo
  */
  // Ponteiro para posição anterior
  double *aux_x = p->x;
  // Atualiza posição atual
  p->x = arraySum(aux_x, p->v, p->dim);
  // Checa se x_opt deve ser atualizada
  double cost_prev = cost(p->x_opt);
  double cost_new = cost(p->x);
  if (cost_prev > cost_new) {
    copyArray(p->x_opt, p->x, p->dim);
  }
  // Libera memória
  free(aux_x);
}

void updatePredPosition(particle *p) {
  /*
      Função para atualizar a posição de um PREDADOR.
      p: partícula a ser atualizada
  */
  
  double *aux_x = p->x;
  p->x = arraySum(aux_x, p->v, p->dim);
  free(aux_x);
}
