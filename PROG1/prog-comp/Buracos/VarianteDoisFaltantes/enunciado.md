# Dois Números Faltantes — Análise Completa

## Enunciado

Dado um vetor com `n` inteiros distintos pertencentes à sequência `1, 2, ..., N` (onde `N = n + 2`), **dois** números estão faltando. Encontre-os.

**Exemplo:** `v = {1, 2, 5, 6, 7}` → faltantes: `3` e `4`

---

## A Solução XOR é Divisão e Conquista?

**Não no sentido estrito**, mas compartilha a *estrutura* de D&C. Compare:

| Critério de D&C clássico | Solução XOR |
|---|---|
| Divide em subproblemas **do mesmo tipo** | Divide em dois grupos por bit — cada grupo é um problema de "achar 1 faltante via XOR", **não** um problema de "achar 2 faltantes" |
| Resolve **recursivamente** | Resolve **iterativamente** (um único `for` por grupo) |
| Combina resultados dos subproblemas | "Combina" = simplesmente reporta os dois valores (não há combinação) |

**Classificação correta:** é uma estratégia de **particionamento por bit** (*bit-partitioning*). O nome "divide and conquer" aparece em relatos de Stack Overflow porque a *intuição* é a mesma (separar para simplificar), mas formalmente:

- **D&C:** `T(n) = a·T(n/b) + f(n)` → recursão
- **XOR Partition:** `T(n) = 2·O(n)` → iteração linear, sem recursão

> **Resumo:** a lógica é *análoga* a D&C (separar → resolver → juntar), mas a implementação é **iterativa e não recursiva**, com subproblemas de complexidade menor (1 faltante em vez de 2).

---

## Solução 1 — Sistema de Equações (Soma + Soma de Quadrados)

### Funções fechadas

| Grandeza | Fórmula | Derivação |
|---|---|---|
| Soma | $S(N) = \dfrac{N(N+1)}{2}$ | PA: $\sum_{i=1}^{N} i = \frac{N(a_1 + a_N)}{2}$ |
| Soma de quadrados | $Q(N) = \dfrac{N(N+1)(2N+1)}{6}$ | Indução / Faulhaber |

### Lógica

Sejam `a` e `b` os faltantes. Montamos:

$$
\begin{cases}
a + b = S(N) - S_{\text{real}} \; \equiv \; s \\[6pt]
a^2 + b^2 = Q(N) - Q_{\text{real}} \; \equiv \; q
\end{cases}
$$

Pela identidade $(a+b)^2 = a^2 + 2ab + b^2$:

$$
ab = \frac{s^2 - q}{2} \; \equiv \; p
$$

Então `a` e `b` são raízes de:

$$
x^2 - sx + p = 0 \;\;\Longrightarrow\;\; x = \frac{s \pm \sqrt{s^2 - 4p}}{2}
$$

### Implementação

```c
#include <stdio.h>
#include <math.h>

void encontrarDoisFaltantes(int v[], int n, int *a, int *b) {
    long N = n + 2;

    // Funções fechadas
    long somaEsperada = N * (N + 1) / 2;
    long quadEsperado = N * (N + 1) * (2 * N + 1) / 6;

    long somaReal = 0, quadReal = 0;
    for (int i = 0; i < n; i++) {
        somaReal += v[i];
        quadReal += (long)v[i] * v[i];
    }

    long s = somaEsperada - somaReal;   // a + b
    long q = quadEsperado - quadReal;   // a² + b²
    long p = (s * s - q) / 2;           // a * b

    // Raízes de x² - sx + p = 0
    double delta = (double)s * s - 4.0 * p;
    *a = (int)round((s - sqrt(delta)) / 2.0);
    *b = (int)round((s + sqrt(delta)) / 2.0);
}
```

### Análise de Complexidade

| Aspecto | Detalhe |
|---|---|
| **Tempo** | `O(n)` — um único laço de `n` iterações. As operações por iteração: 1 soma + 1 multiplicação + 1 acúmulo. **Constante ≈ 3 ops/elemento.** |
| **Espaço** | `O(1)` — variáveis: `somaReal`, `quadReal`, `s`, `q`, `p` (5 registros). |
| **Overflow** | $Q(N) = O(N^3)$. Com `int` (32-bit, máx ≈ $2.1 \times 10^9$): overflow para $N \gtrsim 15{,}949$. Com `long` (64-bit, máx ≈ $9.2 \times 10^{18}$): overflow para $N \gtrsim 2.3 \times 10^6$. |
| **Precisão** | `sqrt` retorna `double` (53 bits de mantissa). Para $s^2 - 4p > 2^{53}$, há perda de precisão → usar `long double` ou a solução XOR. |

---

## Solução 2 — XOR com Particionamento por Bit

### Propriedades de XOR utilizadas

| Propriedade | Fórmula |
|---|---|
| Elemento neutro | $x \oplus 0 = x$ |
| Auto-inversão | $x \oplus x = 0$ |
| Comutatividade | $x \oplus y = y \oplus x$ |
| Associatividade | $(x \oplus y) \oplus z = x \oplus (y \oplus z)$ |

### Lógica passo a passo

**Passo 1 — XOR global:**

$$
X = \left(\bigoplus_{i=1}^{N} i\right) \oplus \left(\bigoplus_{i=0}^{n-1} v[i]\right)
$$

Cada número presente no vetor aparece **duas vezes** (uma no range, outra no array) → cancela. Restam apenas `a` e `b`:

$$
X = a \oplus b
$$

**Passo 2 — Escolher um bit para particionar:**

Como `a ≠ b`, `X ≠ 0`, logo existe ao menos um bit setado em `X`. Escolhemos o **bit menos significativo setado**:

$$
\text{setBit} = X \;\&\; (-X) \quad \text{(isolar o LSB setado)}
$$

**Por que esse bit separa `a` e `b`?** Se `a` e `b` tivessem o **mesmo** valor nesse bit, o XOR nesse bit seria 0 — contradizendo que o bit está setado em `X`. Portanto, `a` e `b` **differem** nesse bit.

**Passo 3 — Particionar e XOR por grupo:**

```
Grupo 1: todos os números (do range 1..N e do vetor) com bit setado
Grupo 2: todos os números sem bit setado
```

No Grupo 1, todos os números presentes cancelam → resta `a` (ou `b`).
No Grupo 2, resta o outro.

### Implementação

```c
#include <stdio.h>

void encontrarDoisFaltantesXOR(int v[], int n, int *a, int *b) {
    int N = n + 2;
    int xor = 0;

    // Passo 1: XOR global = a ^ b
    for (int i = 1; i <= N; i++)
        xor ^= i;
    for (int i = 0; i < n; i++)
        xor ^= v[i];

    // Passo 2: isolar LSB setado
    int setBit = xor & (-xor);

    // Passo 3: particionar
    int g1 = 0, g2 = 0;
    for (int i = 1; i <= N; i++) {
        if (i & setBit)  g1 ^= i;
        else             g2 ^= i;
    }
    for (int i = 0; i < n; i++) {
        if (v[i] & setBit)  g1 ^= v[i];
        else                g2 ^= v[i];
    }

    *a = g1;
    *b = g2;
}
```

### Análise de Complexidade

| Aspecto | Detalhe |
|---|---|
| **Tempo** | `O(n)` — 4 laços lineares (2 no range, 2 no vetor). **Constante ≈ 4 ops/elemento** (1 XOR + 1 teste de bit). |
| **Espaço** | `O(1)` — variáveis: `xor`, `setBit`, `g1`, `g2` (4 registros). |
| **Overflow** | **Nenhum** — XOR é operação bitwise, não aritmética. Funciona para qualquer `N` que caiba no tipo inteiro. |
| **Precisão** | **Exata** — sem ponto flutuante, sem divisão, sem raiz. |

---

## Comparação Final

| Critério | Soma + Quadrados | XOR Partition |
|---|---|---|
| Tempo (assintótico) | O(n) | O(n) |
| Constante de tempo | ~3 ops/elem | ~4 ops/elem |
| Espaço | O(1) | O(1) |
| Overflow | **Sim** ($O(N^3)$) | **Não** |
| Ponto flutuante | Sim (`sqrt`) | Não |
| Escalabilidade | Limitada (~$10^6$ em 64-bit) | Ilimitada (até o tipo) |
| Legibilidade | Alta (álgebra elementar) | Média (bitwise) |
| Classificação algorítmica | Álgebra / funções fechadas | **Particionamento por bit** (estrutura análoga a D&C, mas iterativo) |

**Conclusão:** para entrevistas, a solução **XOR** é a preferida — elimina overflow, não depende de `math.h`, e demonstra domínio de operações bitwise. A solução algébrica é útil como *fallback* quando o entrevistador pede "sem operações bitwise".

---

## Empresas onde esse exercício apareceu

| Empresa | Variante |
|---|---|
| **Amazon** | 1 faltante |
| **Microsoft** | 1 faltante |
| **Google** | 1 faltante |
| **Qualcomm** | 1 faltante |
| **IBM** | 1 faltante |
| **Adobe** | 1 faltante |
| **Cisco** | 1 faltante |
| **Goldman Sachs** | **2 faltantes** |
| **Flipkart** | 1 faltante |
| **Morgan Stanley** | 1 faltante |
| **Visa** | 1 faltante |
| **Accolite** | 1 faltante |


