/*
 * Dois Numeros Faltantes - Solucao 1: FORCA BRUTA
 * ------------------------------------------------
 * Dado um vetor com n inteiros distintos, onde os valores originais
 * eram os inteiros de 1 a n+2 e exatamente DOIS foram removidos,
 * encontre os dois faltantes.
 *
 * Estrategia: para cada candidato c em 1..n+2, varre o vetor
 * inteiro procurando c. Os dois nao encontrados sao a resposta.
 *
 * Tempo:  O(n^2)
 * Espaco: O(1)
 *
 * Compilar: g++ -O2 -std=c++17 dois_faltantes_forca_bruta.cpp -o bruta
 */

#include <bits/stdc++.h>
using namespace std;

pair<int, int> doisFaltantesBruta(const vector<int>& v) {
    int n = (int)v.size();
    int limite = n + 2;              // universo: 1 .. n+2
    int f1 = -1, f2 = -1;

    for (int cand = 1; cand <= limite; cand++) {
        bool achou = false;
        for (int x : v)
            if (x == cand) { achou = true; break; }
        if (!achou) {
            if (f1 == -1) f1 = cand;
            else          f2 = cand;
        }
    }
    return {f1, f2};
}

int main() {
    struct Teste { vector<int> v; int e1, e2; };
    vector<Teste> testes = {
        {{1, 2, 4, 5, 6, 7},  3,  8},
        {{3, 1, 5, 4},         2,  6},
        {{1},                  2,  3},
        {{2, 3},               1,  4},
        {{2, 3, 4, 5, 6, 7, 8}, 1, 9},
        {{1, 2, 3, 4, 5, 6, 8, 9}, 7, 10},
    };

    bool ok = true;
    for (const auto& t : testes) {
        auto r = doisFaltantesBruta(t.v);
        bool p = (min(r.first, r.second) == t.e1 && max(r.first, r.second) == t.e2);
        if (!p) ok = false;
        printf("n=%2d | faltantes(%d,%d) | %s\n",
               (int)t.v.size(), r.first, r.second, p ? "OK" : "ERRO");
    }
    printf(ok ? "\nTODOS OS TESTES PASSARAM\n" : "\nHOUVE FALHAS\n");
    return 0;
}