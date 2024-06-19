#include "swarm.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <outdir> <idx>\n", argv[0]);
    return 1;
  }

  // Constantes c1, c2 do modelo inicial de enxame de partículas
  double c1[2] = {0.05, 0.05};
  double c2[2] = {0.01, 0.01};

  double alpha = 1;        // escala da atração dos predadores
  double lambda = 1;       // escala da distância dos predadores
  double A[2] = {1, 1}; // escala da influência dos predadores

  // numero de particulas
  int Nprey = 50;
  int Npred = 50;

  swarm S;
  initSwarm(&S, Nprey, Npred, 2, c1, c2, alpha, lambda, A);

  int tmax = 1000;
  double out[tmax];
  for (int t = 0; t < tmax; t++) {
    updateSwarm(&S, rastrigin);
    out[t] = rastrigin(S.x_opt);
  }

  char *fname = (char *)malloc(100 * sizeof(char));
  sprintf(fname, "%s/result_N=%02d_P=%02d_alpha=%.2f_lambda=%.2f_A={%.2f,%.2f}_%s.txt", argv[1], Nprey, Npred, alpha, lambda, A[0], A[1], argv[2]);
  writeArray(fname, out, tmax);

  return 0;
}
