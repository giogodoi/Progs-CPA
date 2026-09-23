/*
 * Resolução feita por Giovane Godoi Oliveira, 2026/2
 * SBANK - ordenação de contas bancárias
 *
 * A aplicação do algoritmo Radix Sort ordena os números das contas bancárias
 * processando dígito por dígito. Como os números de conta possuem o mesmo
 * tamanho fixo, iteramos do dígito menos significativo (mais à direita) para o
 * mais significativo (mais à esquerda).
 *
 * Para ordenar os dígitos em cada posição, utiliza-se o Counting Sort, que é
 * um algoritmo estável. A estabilidade é essencial para garantir que a
 * ordenação baseada nos dígitos mais significativos preserve a ordem relativa
 * já estabelecida pelas posições anteriores.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string juntar_conta(const string& p1, const string& p2, const string& p3, const string& p4, const string& p5, const string& p6) {
    return p1 + p2 + p3 + p4 + p5 + p6;
}

string formatarConta(const string& conta) {
    return conta.substr(0, 2) + " " +
           conta.substr(2, 8) + " " +
           conta.substr(10, 4) + " " +
           conta.substr(14, 4) + " " +
           conta.substr(18, 4) + " " +
           conta.substr(22, 4);
}

// O Counting Sort mapeia a frequência de cada dígito (0 a 9) na posição atual,
// soma os índices para encontrar as posições finais e distribui os elementos.
void countingSort_porDigito(vector<string>& contas, int posicao) {
    vector<int> contagem(10, 0);
    vector<string> saida(contas.size());

    // Conta a ocorrência de cada caractere numérico
    for (size_t i = 0; i < contas.size(); i++) {
        int digito = contas[i][posicao] - '0';
        contagem[digito]++;
    }

    // Acumula as contagens para determinar a posição final no vetor ordenado
    for (int i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }

    // A iteração inversa distribui os elementos e garante a estabilidade do algoritmo
    for (int i = (int)contas.size() - 1; i >= 0; i--) {
        int digito = contas[i][posicao] - '0';
        saida[contagem[digito] - 1] = contas[i];
        contagem[digito]--;
    }

    // Sobrescreve o vetor original com a ordenação parcial deste dígito
    for (size_t i = 0; i < contas.size(); i++) {
        contas[i] = saida[i];
    }
}

// O Radix Sort itera sobre cada posição da string de conta, chamando o
// Counting Sort a partir do último caractere até o primeiro.
void radix_sort(vector<string>& contas) {
    if (contas.empty()) {
        return;
    }

    int tamanho = contas[0].size();

    for (int posicao = tamanho - 1; posicao >= 0; posicao--) {
        countingSort_porDigito(contas, posicao);
    }
}

void imprimecontasOrdenadas(const vector<string>& contas) {
    if (contas.empty()) {
        cout << "\n";
        return;
    }

    int repeticoes = 1;

    for (size_t i = 1; i < contas.size(); i++) {
        if (contas[i] == contas[i - 1]) {
            repeticoes++;
        } else {
            cout << formatarConta(contas[i - 1]) << " " << repeticoes << "\n";
            repeticoes = 1;
        }
    }

    cout << formatarConta(contas[contas.size() - 1]) << " " << repeticoes << "\n\n";
}

int main() {
    // Otimização das operações de entrada e saída para processar rapidamente
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    for (int caso = 0; caso < t; caso++) {
        int n;
        cin >> n;

        vector<string> contas;
        contas.reserve(n); // Reserva o espaço previamente para evitar gargalos de alocação de memória
        
        string p1, p2, p3, p4, p5, p6;

        for (int i = 0; i < n; i++) {
            cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
            contas.push_back(juntar_conta(p1, p2, p3, p4, p5, p6));
        }

        radix_sort(contas);
        imprimecontasOrdenadas(contas);
    }

    return 0;
}