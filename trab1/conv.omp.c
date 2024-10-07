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
    int metade_filtro = M / 2;
    float soma = 0.0;
    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            for (int p = 0; p < N; p += 4) {
                int end = (p + 4 > N) ? N : p + 4;
                #pragma omp task firstprivate(p, end) shared(imagem, filtro, resultado, N, M)
                {
                    #pragma omp parallel for collapse(2)
                    for (int i = p+metade_filtro; i < end+metade_filtro; i++) {
                        for (int j = metade_filtro; j < N+metade_filtro; j++) {

                            // collapse no for externo e simd no interno
                            // for simd colapsado reduction
                            #pragma omp simd reduction(+:soma)
                            for (int k = -metade_filtro; k <= metade_filtro; k++) {
                                for (int l = -metade_filtro; l <= metade_filtro; l++) {
                                    int x = i + k;
                                    int y = j + l;

                                    // simd com if pode dar pau
                                    soma += imagem[x][y] * filtro[k + metade_filtro][l + metade_filtro];
                                    // if (x >= 0 && x < N && y >= 0 && y < N) {
                                    // }
                                }
                            }

                            if (soma > 255)
                                resultado[i][j] = 255;
                            else
                                resultado[i][j] = (int)soma;

                            soma = 0.0;
                        }
                    }
                }
            }
        }
    }
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

int main()
{
    int N, M;
    int **imagem = NULL;
    int **resultado = NULL;
    int S;
    float **filtro = NULL;

    scanf("%d %d %d", &N, &M, &S);
    srand(S);

    imagem = (int **)calloc(N+M, sizeof(int *));
    resultado = (int **)calloc(N, sizeof(int *));
    filtro = (float **)calloc(M, sizeof(float *));

    for (int i = 0; i < N; i++) {
        resultado[i] = (int *)calloc(N, sizeof(int));
    }

    for (int i = 0; i < N+M; i++) {
        imagem[i] = (int *)calloc(N+M, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        filtro[i] = (float *)calloc(M, sizeof(float));
    }

    gerar_imagem(imagem, N, M);
    gerar_filtro(filtro, M);
    // aplicar_filtro(imagem, filtro, resultado, N, M);

    for (int i = 0; i < N+M; i++) {
        for (int j = 0; j < N+M; j++) {
            printf("%d ", imagem[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%.2f ", filtro[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", resultado[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < N; i++) {
        free(imagem[i]);
        free(resultado[i]);
    }

    for (int i = 0; i < M; i++) {
        free(filtro[i]);
    }

    free(imagem);
    free(resultado);
    free(filtro);

    return 0;
}
