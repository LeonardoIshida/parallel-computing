#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void aplicar_filtro(int **imagem, float **filtro, int **resultado, int N, int M) {
    int raio_de_deslocamento = M / 2;
    // omp_set_nested(1);

    #pragma omp parallel for collapse(2) schedule(dynamic) num_threads(8)
    for (int i = M/2; i < N+M/2; i++) {
        for (int j = M/2; j < N+M/2; j++) {
            float soma = 0.0;

            #pragma omp simd reduction(+:soma)
            for (int fi = 0; fi < M; fi++) {
                for (int fj = 0; fj < M; fj++) {
                    int oi = i - raio_de_deslocamento + fi;
                    int oj = j - raio_de_deslocamento + fj;

                    soma += imagem[oi][oj] * filtro[fi][fj];
                }
            }

            resultado[i-M/2][j-M/2] = min(255, (int)soma);
        }
    }
}

int calcula_max(int** conv, int N, int M) {
    int maximo = -1;
    #pragma omp parallel for schedule(dynamic) collapse(2) reduction(max: maximo) num_threads(4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maximo = max(maximo, conv[i][j]);
        }
    }

    return maximo;
}

int calcula_min(int** conv, int N, int M) {
    int minimo = 256;
    #pragma omp parallel for schedule(dynamic) collapse(2) reduction(min: minimo) num_threads(4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            minimo = min(minimo, conv[i][j]);
        }
    }

    return minimo;
}

void gerar_filtro(float **filtro, int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            filtro[i][j] = (rand() % 10) / 10.0;
        }
    }
}

void gerar_imagem(int **imagem, int N, int M) {
    for (int i = M/2; i < N+M/2; i++) {
        for (int j = M/2; j < N+M/2; j++) {
            imagem[i][j] = rand() % 256;
        }
    }
}

int main() {
    int N, M, S;
    scanf("%d %d %d", &N, &M, &S);
    srand(S);

    int **imagem = (int **)calloc(N+M, sizeof(int *));
    int **resultado = (int **)calloc(N, sizeof(int *));
    float **filtro = (float **)calloc(M, sizeof(float *));

    for (int i = 0; i < N; i++) {
        resultado[i] = (int *)calloc(N, sizeof(int));
    }
    for (int i = 0; i < N+M-1; i++) {
        imagem[i] = (int *)calloc(N+M, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        filtro[i] = (float *)calloc(M, sizeof(float));
    }

    gerar_imagem(imagem, N, M);
    gerar_filtro(filtro, M);
    aplicar_filtro(imagem, filtro, resultado, N, M);
    int max, min;

    #pragma omp parallel num_threads(2)
    {
        #pragma omp single
        {
            #pragma omp task
            {
                max = calcula_max(resultado, N, M);
            }
            #pragma omp task
            {
                min = calcula_min(resultado, N, M);
            }
        }
    }
    printf("%d %d", max, min);


    // Liberar memória
    // for (int i = 0; i < N; i++) {
    //     free(imagem[i]);
    //     free(resultado[i]);
    // }
    // for (int i = 0; i < M; i++) {
    //     free(filtro[i]);
    // }

    // free(imagem);
    // free(resultado);
    // free(filtro);

    return 0;
}