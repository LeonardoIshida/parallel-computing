// SSC0903 - COMPUTAÇÃO DE ALTO DESEMPENHO
// TRABALHO PRÁTICO 1

// Alunos:
// Enzo Yassuo Hirano Harada -
// Jõao Pedro Hamata -
// Leonardo Ishida - 12873424
// Miguel Bragante Henriques - 13671894
// Victor Hugo Trigolo Amaral -

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

    #pragma omp parallel for collapse(2) schedule(guided) num_threads(8)
    for (int i = raio_de_deslocamento; i < N+raio_de_deslocamento; i++) {
        for (int j = raio_de_deslocamento; j < N+raio_de_deslocamento; j++) {
            float soma = 0.0;

            #pragma omp simd reduction(+:soma)
            for (int fi = 0; fi < M; fi++) {
                for (int fj = 0; fj < M; fj++) {
                    soma += imagem[i-raio_de_deslocamento+fi][j-raio_de_deslocamento+fj] * filtro[fi][fj];
                }
            }

            resultado[i-M/2][j-M/2] = min(255, (int)soma);
        }
    }
}

void calcula_max_min(int** conv, int N, int *max_global, int *min_global) {
    int maximo = -1;
    int minimo = 256;

    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(guided) collapse(2) reduction(max: maximo) reduction(min: minimo) nowait
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                minimo = min(minimo, conv[i][j]);
                maximo = max(maximo, conv[i][j]);
            }
        }
    }

    *max_global = maximo;
    *min_global = minimo;
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
    int max, min;

    // alocacao de memoria para as matrizes
    for (int i = 0; i < N; i++) {
        resultado[i] = (int *)calloc(N, sizeof(int));
    }

    for (int i = 0; i < N+M-1; i++) {
        imagem[i] = (int *)calloc(N+M-1, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        filtro[i] = (float *)calloc(M, sizeof(float));
    }

    gerar_imagem(imagem, N, M);
    gerar_filtro(filtro, M);

    #pragma omp prallel num_threads(8)
    {
        // task para construir a matriz de convolucao
        #pragma omp task depend(out: resultado)
        {
            aplicar_filtro(imagem, filtro, resultado, N, M);
        }

        // task para encontrar o maior e menor valor da matriz de convolucao
        #pragma omp task shared(max, min) depend(in: resultado)
        {
            calcula_max_min(resultado, N, &max, &min);
        }

        // as proximas 3 tasks desalocam memoria
        #pragma omp task depend(out: max, min)
        {
            for (int i = 0; i < N; i++) {
                free(resultado[i]);
            }
            free(resultado);
        }
        #pragma omp task depend(out: max, min)
        {
            for (int i = 0; i < N+M-1; i++) {
                free(imagem[i]);
            }
            free(imagem);
        }
        #pragma omp task depend(out: max, min)
        {
            for (int i = 0; i < M; i++) {
                free(filtro[i]);
            }
            free(filtro);
        }

        // impressao do maior e menor valor da matriz de convolucao
        #pragma taskwait
        printf("%d %d", max, min);
    }

    return 0;
}