"""
Um Número Faltante — Problema Original (Solução Ótima)
========================================================

Dado um vetor com n inteiros distintos, onde o conjunto original era os
inteiros de 1 a n+1 e exatamente UM número foi removido, encontre-o.

O programa aguarda as entradas do usuário pelo terminal.

Complexidade: O(n) de tempo, O(1) de espaço.
"""


def encontrar_faltante(vetor: list[int]) -> int:
    """Encontra o número faltante em uma sequência de 1 a len(vetor) + 1.

    O vetor deve conter inteiros distintos, sem UM valor removido.

    Ideia: a soma dos inteiros de 1 a k é k(k+1)/2 (fórmula da
    progressão aritmética). A diferença entre a soma esperada do
    universo completo e a soma real do vetor é exatamente o faltante.
    """
    k = len(vetor) + 1                    # universo completo: 1..k
    soma_esperada = k * (k + 1) // 2
    return soma_esperada - sum(vetor)


def ler_vetor_do_usuario() -> list[int]:
    """Lê n e os n valores do terminal.

    Os valores podem ser digitados um por linha ou todos na mesma
    linha, separados por espaço (igual ao comportamento do scanf).
    """
    n = int(input("Quantos números o vetor tem? "))
    print(f"Digite os {n} valores:")

    vetor: list[int] = []
    while len(vetor) < n:
        linha = input()
        vetor.extend(int(token) for token in linha.split())
    return vetor[:n]


def main() -> None:
    vetor = ler_vetor_do_usuario()
    faltante = encontrar_faltante(vetor)
    print(f"O número faltante é: {faltante}")


if __name__ == "__main__":
    main()
