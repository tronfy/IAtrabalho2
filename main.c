#include "swarm.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592684

double rastrigin(double *x) {
  double out = 2;
  out += x[0] * x[0] - cos(2 * PI * x[0]);
  out += x[1] * x[1] - cos(2 * PI * x[1]);
  return out;
}

void writeArray(char *fname, double *out, int n) {
  FILE *fp = fopen(fname, "w");
  for (int i = 0; i < n; i++) {
    fprintf(fp, "%.17g \n", out[i]);
  }
  fclose(fp);
}

int main() {

  double c1[2] = {0.05, 0.05}; // Constante alfa no modelo predator-prey
  double c2[2] = {0.01, 0.01}; // Constante A no modelo predator-prey
  double c3[2] = {0.00, 0.00}; // Constante lambda no modelo predator-prey

  int Nprey = 10;
  int Npred = 10;
  swarm S;
  initSwarm(&S, Nprey, Npred, 2, c1, c2, c3);

  int tmax = 1000;
  double out[tmax];
  for (int t = 0; t < tmax; t++) {
    updateSwarm(&S, rastrigin);
    out[t] = rastrigin(S.x_opt);
  }

  char *fname = (char *)malloc(21 * sizeof(char));
  sprintf(fname, "resultados_N=%04d.dat", Nprey);
  writeArray(fname, out, tmax);

  return 0;
}
