#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void aplicar_filtro(int *imagem, float *filtro, int *resultado, int N, int M) {
    int raio_de_deslocamento = M / 2;
    int mais_claro = 0;
    int mais_escuro = 255;

    #pragma omp parallel for schedule(dynamic) reduction(max: mais_claro) reduction(min: mais_escuro)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float soma = 0.0;

            for (int fi = 0; fi < M; fi++) {
                int oi = i - raio_de_deslocamento + fi;
                if (oi < 0 || oi >= N) continue;

                for (int fj = 0; fj < M; fj++) {
                    int oj = j - raio_de_deslocamento + fj;
                    if (oj < 0 || oj >= N) continue;

                    soma += imagem[oi * N + oj] * filtro[fi * M + fj];
                }
            }

            resultado[i * N + j] = (int)soma;
            mais_claro = max(mais_claro, resultado[i * N + j]);
            mais_escuro = min(mais_escuro, resultado[i * N + j]);
        }
    }

    mais_claro = mais_claro > 255 ? 255 : mais_claro;
    printf("%d %d\n", mais_claro, mais_escuro);
}

void gerar_filtro(float *filtro, int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            filtro[i * M + j] = (rand() % 10) / 10.0;
        }
    }
}

void gerar_imagem(int *imagem, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            imagem[i * N + j] = rand() % 256;
        }
    }
}

int main() {
    int N, M, S;
    int *imagem = NULL;
    int *resultado = NULL;
    float *filtro = NULL;

    scanf("%d %d %d", &N, &M, &S);
    srand(S);

    // Alocação de memória em formato linear
    imagem = (int *)calloc(N * N, sizeof(int));
    resultado = (int *)calloc(N * N, sizeof(int));
    filtro = (float *)calloc(M * M, sizeof(float));

    // Geração sequencial das matrizes
    gerar_imagem(imagem, N);
    gerar_filtro(filtro, M);
    
    // Aplicação do filtro de forma paralela
    aplicar_filtro(imagem, filtro, resultado, N, M);

    // Liberar memória
    free(imagem);
    free(resultado);
    free(filtro);

    return 0;
}
