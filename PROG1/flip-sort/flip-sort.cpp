/*
 * Resolução feita por Giovane Godoi Oliveira, 2026/2
 * Flip Sort — número mínimo de operações de Flip (troca de adjacentes)
 * para ordenar um vetor, calculado por divisão e conquista (Merge Sort).
 *
 * Ideia central: o mínimo de trocas adjacentes para ordenar A[1..n] é
 * igual ao número de INVERSÕES do vetor (pares i < j com A[i] > A[j]).
 *
 *   - Cada Flip corrige no máximo uma inversão   -> limite inferior.
 *   - O bubble sort corrige exatamente uma por vez -> limite atingido.
 *
 * O merge conta as inversões "cruzadas": ao copiar um elemento da
 * metade DIREITA antes dos que restam na ESQUERDA, ele forma inversão
 * com TODOS eles de uma só vez (mid - i inversões).
 *
 * Complexidade: O(N log N) por caso de teste.
 */


#include <stdio.h>
#include <vector>

using namespace std;

// Intercala a[lo..mid) com a[mid..hi) e conta as inversoes cruzadas.
long long countAndMerge(vector<int>& a, vector<int>& buf, int lo, int mid, int hi) {
    long long inv = 0;
    int i = lo, j = mid, k = lo;

    while (i < mid && j < hi) {
        if (a[i] <= a[j]) {
            buf[k++] = a[i++];
        } else {
            inv += mid - i;          // a[j] "pula" todo o resto da esquerda
            buf[k++] = a[j++];
        }
    }
    while (i < mid) buf[k++] = a[i++];
    while (j < hi)  buf[k++] = a[j++];

    for (k = lo; k < hi; ++k) a[k] = buf[k];
    return inv;
}

// Ordena a[lo..hi) por divisao e conquista e retorna o total de inversoes.
long long contaInversao(vector<int>& a, vector<int>& buf, int lo, int hi) {
    if (hi - lo <= 1) return 0;      // 0 ou 1 elemento: ja ordenado

    int mid = lo + (hi - lo) / 2;
    return contaInversao(a, buf, lo, mid)
         + contaInversao(a, buf, mid, hi)
         + countAndMerge(a, buf, lo, mid, hi);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        vector<int> a(n), buf(n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

        printf("Minimum exchange operations : %lld\n", contaInversao(a, buf, 0, n));
    }
    return 0;
}