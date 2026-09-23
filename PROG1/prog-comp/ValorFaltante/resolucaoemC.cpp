#include <stdio.h>

int encontrarFaltante(int v[], int n) {
    // O vetor original deveria ter n+1 elementos (de 1 a n+1)
    // A soma de 1 a k é k * (k + 1) / 2
    int k = n + 1;
    int somaEsperada = k * (k + 1) / 2;
    
    int somaReal = 0;
    for (int i = 0; i < n; i++) {
        somaReal += v[i];
    }
    
    return somaEsperada - somaReal;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int vetor[n];

    for (int i=0; i<n; i++) {
        scanf("%d", &vetor[i]);
    }

    
    int faltante = encontrarFaltante(vetor, n);
    printf("O número faltante é: %d\n", faltante); // Saída: 3
    
    return 0;
}   