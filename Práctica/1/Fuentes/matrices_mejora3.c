#include<stdio.h>

#include<stdlib.h>

#include <sys/time.h>

#define ORDENXFILAS 0
#define ORDENXCOLUMNAS 1

//Dimension por defecto de las matrices
int N = 100;

//Para calcular tiempo
double dwalltime() {
  double sec;
  struct timeval tv;

  gettimeofday( & tv, NULL);
  sec = tv.tv_sec + tv.tv_usec / 1000000.0;
  return sec;
}

int main(int argc, char * argv[]) {
  double * A, * B, * C;
  int i, j, k;
  int check = 1;
  double timetick;

  //Controla los argumentos al programa
  if ((argc != 2) || ((N = atoi(argv[1])) <= 0)) {
    printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
    exit(1);
  }

  //Aloca memoria para las matrices
  A = (double * ) malloc(sizeof(double) * N * N);
  B = (double * ) malloc(sizeof(double) * N * N);
  C = (double * ) malloc(sizeof(double) * N * N);

  //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
  if (ORDENXFILAS == 1) {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i * N + j] = 1;
        B[i * N + j] = 1;
        C[i * N + j] = 0;
      }
    }

    //Realiza la multiplicacion
    timetick = dwalltime();

    for (i = 0; i < N; i++) {
      for (k = 0; k < N; k++) {
        double valorA = A[i * N + k];
        for (j = 0; j < N; j++) {
          C[i * N + j] += valorA * B[k * N + j];
        }
      }
    }

    printf("Multiplicacion de matrices de %dx%d. Tiempo en segundos %f\n", N, N, dwalltime() - timetick);
    //Verifica el resultado
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        check = check && (C[i * N + j] == N);
      }
    }
  }
  else {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i + j * N] = 1;
        B[i + j * N] = 1;
        C[i + j * N] = 0;
      }
    }

    //Realiza la multiplicacion
    timetick = dwalltime();

    for (i = 0; i < N; i++) {
      for (k = 0; k < N; k++) {
        double valorA = A[i + k * N];
        for (j = 0; j < N; j++) {
          C[i + j * N] += valorA * B[k + j * N];
        }
      }
    }

    printf("Multiplicacion de matrices de %dx%d. Tiempo en segundos %f\n", N, N, dwalltime() - timetick);
    //Verifica el resultado
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        check = check && (C[i + j * N] == N);
      }
    }
  }

  if (check) {
    printf("Multiplicacion de matrices resultado correcto\n");
  } else {
    printf("Multiplicacion de matrices resultado erroneo\n");
  }

  free(A);
  free(B);
  free(C);
  return (0);
}
