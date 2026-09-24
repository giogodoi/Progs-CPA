"""
Dois Números Faltantes — Variante Goldman Sachs (Solução Ótima)
================================================================

Dado um vetor com n inteiros distintos, onde o conjunto original era os
inteiros de 1 a n+2 e exatamente DOIS números foram removidos, encontre
os dois faltantes.

Complexidade: O(n) de tempo, O(1) de espaço.
"""

from math import isqrt


def encontrar_dois_faltantes(vetor: list[int]) -> tuple[int, int]:
    """Encontra os dois números faltantes em uma sequência de 1 a len(vetor) + 2.

    O vetor deve conter inteiros distintos, sem os dois valores removidos.

    Ideia: montar um sistema de duas equações, resolvível em uma única varredura:

      1) soma            ->  a + b
      2) soma quadrada  ->  a² + b²

    Com isso, usa-se a identidade (a + b)² = a² + 2ab + b² para achar o
    produto, e a fórmula de Bhaskara para separar as duas raízes.
    """
    # O universo completo vai de 1 até k; o vetor tem k - 2 elementos.
    k = len(vetor) + 2

    # Somas esperadas caso NENHUM número tivesse sido removido.
    soma_esperada = k * (k + 1) // 2
    soma_quadrados_esperada = k * (k + 1) * (2 * k + 1) // 6

    # Subtraímos o que de fato está presente.
    soma_do_par = soma_esperada - sum(vetor)                                    # a + b
    soma_dos_quadrados_do_par = soma_quadrados_esperada - sum(x * x for x in vetor)  # a² + b²

    # De (a + b)² = a² + 2ab + b², isolamos o produto:
    produto_do_par = (soma_do_par**2 - soma_dos_quadrados_do_par) // 2          # a * b

    # Bhaskara: x² - (a+b)x + ab = 0 tem raízes a e b.
    # O discriminante é (a - b)², sempre um quadrado perfeito.
    discriminante = soma_do_par**2 - 4 * produto_do_par                         # (a - b)²
    diferenca = isqrt(discriminante)                                            # |a - b|

    menor = (soma_do_par - diferenca) // 2
    maior = (soma_do_par + diferenca) // 2
    return menor, maior


# ---------------------------------------------------------------------------
# Testes
# ---------------------------------------------------------------------------

def _executar_testes() -> None:
    import random

    casos_fixos = [
        ([1, 2, 4, 5, 6, 7], (3, 8)),
        ([3, 1, 5, 4], (2, 6)),
        ([1], (2, 3)),
        ([2, 3], (1, 4)),
        ([2, 3, 4, 5, 6, 7, 8], (1, 9)),
        ([1, 2, 3, 4, 5, 6, 8, 9], (7, 10)),
    ]
    for vetor, esperado in casos_fixos:
        resultado = encontrar_dois_faltantes(vetor)
        situacao = "OK" if resultado == esperado else f"ERRO (esperado {esperado})"
        print(f"n={len(vetor):2d} | faltantes {resultado} | {situacao}")

    # Testes aleatórios de larga escala.
    for _ in range(300):
        k = random.randint(3, 3000)
        universo = list(range(1, k + 1))
        faltantes = sorted(random.sample(universo, 2))
        presentes = [x for x in universo if x not in faltantes]
        assert encontrar_dois_faltantes(presentes) == tuple(faltantes)

    print("\nTODOS OS TESTES PASSARAM")


if __name__ == "__main__":
    _executar_testes()
