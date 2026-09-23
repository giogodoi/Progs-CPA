def dfs(grid, linha, coluna, num_linhas, num_colunas):
    # Condição de parada: fora dos limites da matriz ou se não for '0'
    if (linha < 0 or linha >= num_linhas or 
        coluna < 0 or coluna >= num_colunas or 
        grid[linha][coluna] != '0'):
        return

    # Marca a posição atual como '1' para evitar nova visita
    grid[linha][coluna] = '1'

    # Chama a DFS para os 4 vizinhos
    dfs(grid, linha - 1, coluna, num_linhas, num_colunas)  # Cima
    dfs(grid, linha + 1, coluna, num_linhas, num_colunas)  # Baixo
    dfs(grid, linha, coluna - 1, num_linhas, num_colunas)  # Esquerda
    dfs(grid, linha, coluna + 1, num_linhas, num_colunas)  # Direita

def contar_buracos(malha):
    if not malha:
        return 0

    # Converte as strings para listas de caracteres para permitir mutação
    grid = [list(linha) for linha in malha]
    num_linhas = len(grid)
    num_colunas = len(grid[0])
    buracos = 0

    # Varredura da matriz
    for i in range(num_linhas):
        for j in range(num_colunas):
            if grid[i][j] == '0':
                buracos += 1
                dfs(grid, i, j, num_linhas, num_colunas)

    return buracos

if __name__ == "__main__":
    n = int(input())
    malha = [input().strip() for _ in range(n)]

    resultado = contar_buracos(malha)
    print(resultado)