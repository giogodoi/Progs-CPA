/*
 * Resolução feita por Giovane Godoi Oliveira, 2026/2
 * Premiação dos Gnomos — classificar M pontuações em N faixas
 * usando divisão e conquista (busca binária).
 *
 * Ideia central: os N-1 limites G estão em ordem estritamente
 * crescente, logo a faixa de uma pontuação p é o índice do
 * PRIMEIRO limite maior que p (faixa i = pontuações em [G[i-1], G[i]),
 * com G[-1] = -infinito e a última faixa aberta).
 *
 * A cada passo a busca descarta metade do espaço:
 *   - se G[meio] <= p, todo limite à esquerda (inclusive) é <= p
 *     e pode ser descartado: a resposta está à direita;
 *   - senão, G[meio] é candidato, mas pode existir um limite menor
 *     (e ainda maior que p) à esquerda: buscamos lá.
 * Quando os ponteiros se cruzam, 'esq' é exatamente o índice do
 * primeiro limite maior que p — que já coincide com o índice da
 * premiação correspondente em F.
 *
 * Complexidade: O(M log N) por caso de teste.
 */

#include <cstdio>
#include <vector>

using namespace std;

// Divisão e conquista recursiva: índice do primeiro G[i] > p em [esq..dir].
int faixa(const vector<int>& G, int esq, int dir, int p) {
    if (esq > dir) return esq;               // espaço reduzido a zero: convergiu

    int meio = esq + (dir - esq) / 2;        // evita overflow de (esq+dir)/2
    if (G[meio] <= p)
        return faixa(G, meio + 1, dir, p);  // descarta a metade esquerda
    return faixa(G, esq, meio - 1, p);       // descarta a metade direita
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    vector<int> G(N - 1), F(N);              // limites das faixas e premiações
    for (int i = 0; i < N - 1; ++i) scanf("%d", &G[i]);
    for (int i = 0; i < N; ++i)     scanf("%d", &F[i]);

    for (int i = 0; i < M; ++i) {
        int p;                                // pontuação do aluno atual
        scanf("%d", &p);

        printf("%d", F[faixa(G, 0, N - 2, p)]);
        printf(i < M - 1 ? " " : "\n");      // M inteiros em uma única linha
    }
    return 0;
}