
#ifndef PARTICLES_H
#define PARTICLES_H

#define V_MAX 10

typedef struct {
  double *x;     // posição atual
  double *x_opt; // posição ótima
  double *v;     // velocidade
  int dim;       // dimensão
} particle;

void initParticle(particle *p, int dim, double *x_0);
void freeParticle(particle *p);

void updatePreyVelocity(particle *p, double *c1, double *c2, double *swarm_opt,
                        double *A, double lambda, double *Xpred);
void updatePredVelocity(particle *p, double alpha, double *swarm_opt);
void updatePreyPosition(particle *p, double (*cost)(double *));
void updatePredPosition(particle *p);

#endif
