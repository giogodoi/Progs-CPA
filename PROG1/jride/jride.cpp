/*
 * Resolução feita por Giovane Godoi Oliveira, 2026/2
 *
 * A aplicação do algoritmo de divisão e conquista divide o espaço
 * de busca em duas metades a cada chamada. O trecho com a maior 
 * soma de avaliações pode estar:
 *   1. Inteiramente contido na metade esquerda.
 *   2. Inteiramente contido na metade direita.
 *   3. Cruzando o ponto central (meio) que divide as duas metades.
 *
 * Usarei como referência um pseudocódigo usado em sala de aula, adaptando-o para C++.
 * 
 * O algoritmo resolve recursivamente as partes esquerda e direita
 * e calcula a melhor soma cruzada expandindo a partir do meio. 
 * O resultado final da etapa é o melhor entre essas três opções.
 */

#include <cstdio>
#include <vector>

using namespace std;

struct Resultado {
    int soma;
    int inicio;
    int fim;
    
    // Construtor explícito para garantir compatibilidade com compiladores C++98/03
    Resultado(int s, int i, int f) {
        soma = s;
        inicio = i;
        fim = f;
    }
};

// Compara duas possíveis respostas e retorna a melhor aplicando as regras do algoritmo
Resultado melhor_resultado(Resultado a, Resultado b) {
    if (a.soma != b.soma) {
        return (a.soma > b.soma) ? a : b;
    }
    
    int tamanho_a = a.fim - a.inicio;
    int tamanho_b = b.fim - b.inicio;
    
    if (tamanho_a != tamanho_b) {
        return (tamanho_a > tamanho_b) ? a : b;
    }
    
    return (a.inicio < b.inicio) ? a : b;
}

// Encontra o melhor trecho contíguo que obrigatoriamente passa pelo meio
Resultado encontrar_cruzamento(const vector<int>& avaliacoes, int esq, int meio, int dir) {
    // Usando -1000000000 explicitamente para evitar possíveis problemas de conversão de double em compiladores muito antigos com -1e9
    int melhor_soma_esq = -1000000000; 
    int melhor_inicio = meio;
    int soma_atual = 0;
    
    // Expande do meio para a esquerda
    for (int i = meio; i >= esq; --i) {
        soma_atual += avaliacoes[i];
        // O uso de '>=' assegura que o algoritmo escolha o índice mais à esquerda 
        // durante empates, priorizando sequências mais longas e de menor índice
        if (soma_atual >= melhor_soma_esq) {
            melhor_soma_esq = soma_atual;
            melhor_inicio = i;
        }
    }

    int melhor_soma_dir = -1000000000;
    int melhor_fim = meio + 1;
    soma_atual = 0;

    // Expande do meio para a direita
    for (int i = meio + 1; i <= dir; ++i) {
        soma_atual += avaliacoes[i];
        // O uso de '>=' assegura a escolha do índice mais à direita durante 
        // empates, priorizando sequências mais longas
        if (soma_atual >= melhor_soma_dir) {
            melhor_soma_dir = soma_atual;
            melhor_fim = i;
        }
    }

    // Retorna usando o construtor explicitamente
    return Resultado(melhor_soma_esq + melhor_soma_dir, melhor_inicio, melhor_fim + 1);
}

// Aplicação recursiva da Divisão e Conquista
Resultado divisao_e_conquista(const vector<int>& avaliacoes, int esq, int dir) {
    // Caso base: espaço reduzido a um único trecho
    if (esq == dir) {
        return Resultado(avaliacoes[esq], esq, esq + 1);
    }

    int meio = esq + (dir - esq) / 2;

    Resultado esquerda = divisao_e_conquista(avaliacoes, esq, meio);
    Resultado direita = divisao_e_conquista(avaliacoes, meio + 1, dir);
    Resultado cruzamento = encontrar_cruzamento(avaliacoes, esq, meio, dir);

    // Combina os subproblemas retornando o de melhor classificação
    return melhor_resultado(melhor_resultado(esquerda, direita), cruzamento);
}

int main() {
    int quantidade_rotas;
    if (scanf("%d", &quantidade_rotas) != 1) return 0;

    for (int rota = 1; rota <= quantidade_rotas; ++rota) {
        int quantidade_paradas;
        scanf("%d", &quantidade_paradas);

        int quantidade_trechos = quantidade_paradas - 1;
        vector<int> avaliacoes(quantidade_trechos + 1);

        for (int i = 1; i <= quantidade_trechos; ++i) {
            scanf("%d", &avaliacoes[i]);
        }

        Resultado melhor_rota = divisao_e_conquista(avaliacoes, 1, quantidade_trechos);

        if (melhor_rota.soma > 0) {
            printf("The nicest part of route %d is between stops %d and %d\n", rota, melhor_rota.inicio, melhor_rota.fim);
        } else {
            printf("Route %d has no nice parts\n", rota);
        }
    }
    return 0;
}