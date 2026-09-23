#include <iostream>
#include <vector>

using namespace std;

void dfs(vector <string>& malha, int linha, int coluna) {
    int num_linhas = malha.size();
    int num_colunas = malha[0].size();
    // Condição de parada: fora dos limites da matriz ou se não for um '0'
    if (linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas 
    || malha[linha][coluna] != '0') {
        return;
    }
    malha[linha][coluna] = '1';
    dfs(malha, linha - 1, coluna); // Cima
    dfs(malha, linha + 1, coluna); // Baixo
    dfs(malha, linha, coluna - 1); // Esquerda
    dfs(malha, linha, coluna + 1); // Direita
}

int contarBuracos(vector<string>& malha) {
    if (malha.empty()) return 0;
    int buracos = 0;
    int num_linhas = malha.size();
    int num_colunas = malha[0].size();
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            // Se encontrar um '0', é um novo buraco
            if (malha[i][j] == '0') {
                buracos++;
                // Inicia a varredura para marcar todos os zeros deste mesmo buraco
                dfs(malha, i, j);
            }
        }
    }
    return buracos;
}

int main() {
    int n;    
    if (!(cin >> n)) return 0;
    vector<string> malha(n);
    for (int i = 0; i < n; i++) {
        cin >> malha[i];
    }
    int total_buracos = contarBuracos(malha);    
    cout << total_buracos << endl;

    return 0;
}