
#ifndef PARTICLES_H
#define PARTICLES_H

typedef struct {
  double *x;     // posição atual
  double *x_opt; // posição ótima
  double *v;     // velocidade
  int dim;       // dimensão
} particle;

void initParticle(particle *p, int dim, double *x_0);
void freeParticle(particle *p);
void updateVelocity(particle *p, double *c1, double *c2, double *swarm_opt);
void updatePosition(particle *p, double (*cost)(double *));

// TODO: adaptar updateVelocity para updatePreyVelocity, recebendo também o
// parâmetro λ. v_i(t+1) já está sendo calculado, só falta somar com o termo ->
// A * exp(−λ||x_prey(t) − x_pred(t+1)||).
// A é a influencia dos preds (distancia media)

// TODO: adaptar updateVelocity para updatePredVelocity, recebendo também os
// parâmetros α e x_opt (das presas). v_pred(t + 1) = α[x_opt(t) − x_pred(t)]

#endif
