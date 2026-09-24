# Dois Números Faltantes — Variante Goldman Sachs

## Enunciado

Dado um vetor com `n` inteiros **distintos**, onde o conjunto original era os inteiros de `1` a `n+2` e exatamente **dois** números foram removidos, encontre os dois faltantes.

**Exemplo:** `v = {1, 2, 4, 5, 7}` (universo `1..7`) → faltam `3` e `6`.

Essa variante é mais difícil que a de um faltante porque, com uma única equação (a soma), obtemos apenas `a + b` — um grau de liberdade a menos. São necessárias **duas equações independentes** para resolver o sistema.

---

## Solução 1 — Básica (força bruta)

### Lógica

Para cada candidato `c` de `1` a `n+2`, varra o vetor inteiro procurando `c`. Se `c` não for encontrado, ele é um dos faltantes. Repita até coletar os dois.

```cpp
pair<int,int> doisFaltantesBruta(const vector<int>& v) {
    int n = (int)v.size();
    int limite = n + 2;
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
```

### Complexidade

| | Valor |
|---|---|
| Tempo | **O(n²)** — para cada um dos ~n+2 candidatos, uma varredura de O(n) |
| Espaço | **O(1)** — apenas variáveis escalares |

**Vantagem:** trivial de entender e implementar; não depende de ordenação nem de fórmulas.
**Desvantagem:** quadratico — impraticável para `n` na ordem de 10⁵ ou mais.

> **Variante intermediária:** ordenar o vetor e varrer procurando os "buracos" nos valores custa O(n log n) tempo e O(1) espaço extra (se a ordenação for in-place). Melhor que a força bruta, mas ainda pior que a ótima.

---

## Solução 2 — Ótima: soma + soma de quadrados

### Lógica

Sejam `a` e `b` os faltantes (`a < b`). A ideia é montar um **sistema de duas equações** com dados obtidos em uma única varredura do vetor:

**Equação 1 (soma):** usando a fórmula da progressão aritmética,

$$s = a + b = \frac{k(k+1)}{2} - \sum_{i} v_i, \quad k = n+2$$

**Equação 2 (soma de quadrados):** usando a fórmula da soma dos quadrados,

$$q = a^2 + b^2 = \frac{k(k+1)(2k+1)}{6} - \sum_{i} v_i^2$$

Com `s` e `q` em mãos, resolvemos o sistema algebricamente:

1. **Produto:** pela identidade `(a+b)² = a² + 2ab + b²`:
   $$ab = \frac{s^2 - q}{2}$$
2. **Diferença:** pela relação de Bhaskara (raízes de `x² - sx + ab = 0`), o discriminante é:
   $$(a - b)^2 = s^2 - 4ab \;\;\Rightarrow\;\; d = |a - b| = \sqrt{s^2 - 4ab}$$
3. **Resposta:**
   $$a = \frac{s - d}{2}, \qquad b = \frac{s + d}{2}$$

Como `a` e `b` são inteiros, o discriminante é sempre um **quadrado perfeito** e as divisões por 2 são exatas.

```cpp
pair<long long,long long> doisFaltantesOtimos(const vector<int>& v) {
    long long n = (long long)v.size();
    long long k = n + 2;
    long long s = k * (k + 1) / 2;               // soma esperada
    long long q = k * (k + 1) * (2*k + 1) / 6;   // soma de quadrados esperada

    for (int x : v) {
        s -= x;
        q -= (long long)x * x;
    }

    long long prod = (s * s - q) / 2;            // a * b
    long long disc = s * s - 4 * prod;           // (a - b)^2

    long long d = (long long)sqrt((double)disc); // raiz com correção
    while (d * d > disc) d--;
    while ((d + 1) * (d + 1) <= disc) d++;

    long long a = (s - d) / 2;
    long long b = (s + d) / 2;
    return {a, b};
}
```

### Exemplo numérico

`v = {1, 2, 4, 5, 7}`, `n = 5`, `k = 7`:

- Soma esperada: `7·8/2 = 28`; soma real: `19` → `s = 9`
- Soma de quadrados esperada: `7·8·15/6 = 140`; real: `1+4+16+25+49 = 95` → `q = 45`
- `ab = (81 − 45)/2 = 18`; `d = √(81 − 72) = 3`
- `a = (9 − 3)/2 = 3`, `b = (9 + 3)/2 = 6` ✓

### Complexidade

| | Valor |
|---|---|
| Tempo | **O(n)** — uma única varredura do vetor |
| Espaço | **O(1)** — apenas variáveis escalares |

**Vantagem:** linear, uma passada, sem ordenação e sem estruturas auxiliares.
**Desvantagem:** risco de **overflow** — a soma de quadrados cresce como `k³/3`. Para `k ≈ 2·10⁶`, `q ≈ 2,7·10¹⁸`, próximo do limite do `long long` (≈ 9,2·10¹⁸). Use `long long` (obrigatório) e, para universos maiores, prefira a variante XOR.

---

## Solução 2b — Alternativa ótima via XOR

Útil quando o overflow é uma preocupação real (a XOR nunca "cresce": o resultado tem no máximo os bits do maior valor).

### Lógica

1. Calcule `x` = XOR de todos os elementos do vetor **e** de todos os valores de `1` a `n+2`. Tudo que aparece dos dois lados se cancela, restando `x = a ⊕ b`.
2. Como `a ≠ b`, `x ≠ 0`, então `x` tem pelo menos um bit setado. Pegue o bit mais à direita: `bit = x & (−x)`. Esse bit **diferencia** `a` de `b` (um o tem, o outro não).
3. Particione todos os valores (do vetor e do universo `1..n+2`) em dois grupos — os com o bit setado e os sem. Dentro do grupo de `a`, todos os valores se cancelam por pares exceto `a`; o mesmo para `b`.

```cpp
pair<long long,long long> doisFaltantesXOR(const vector<int>& v) {
    long long n = (long long)v.size();
    long long x = 0;
    for (int val : v) x ^= val;
    for (long long i = 1; i <= n + 2; i++) x ^= i;   // x = a XOR b

    long long bit = x & (-x);
    long long a = 0, b = 0;
    for (int val : v)        (val & bit) ? a ^= val : b ^= val;
    for (long long i = 1; i <= n + 2; i++) (i & bit) ? a ^= i : b ^= i;

    if (a > b) swap(a, b);
    return {a, b};
}
```

### Complexidade

| | Valor |
|---|---|
| Tempo | **O(n)** — duas varreduras lineares |
| Espaço | **O(1)** |

---

## Comparação geral

| Critério | Força bruta | Ordenar + varrer | Soma + quadrados | XOR |
|---|---|---|---|---|
| Tempo | O(n²) | O(n log n) | O(n) | O(n) |
| Espaço | O(1) | O(1) ou O(n) | O(1) | O(1) |
| Requer ordenação? | Não | Sim | Não | Não |
| Nº de varreduras | ~2n | 1 (+ sort) | 1 | 2 |
| Risco de overflow | Não | Não | Sim (use `long long`) | Não |
| Carga cognitiva | Baixa | Baixa | Média | Média/alta |

## Conclusão

- A solução por **soma + soma de quadrados** é a resposta clássica esperada: transforma o problema algébrico em um sistema 2×2 resolvido em O(n) e O(1) de espaço.
- A variante **XOR** tem a mesma complexidade e elimina o risco de overflow — em uma entrevista, mencioná-la como alternativa demonstra domínio da família de técnicas.
- A força bruta serve apenas como linha de base para validar as soluções ótimas em testes (foi exatamente o papel dela na bateria de testes do código).

