# Encontrar o Número Faltante em um Vetor

## Enunciado

Dado um vetor com `n` inteiros consecutivos de `1` a `n+1`, onde **um** número está faltando, encontre-o.

**Exemplo:** `v = {1, 2, 4, 5, 6}` → faltante: `3`

---

## Solução 1 — Força Bruta (comparação linear)

Percorre o vetor e verifica se cada número esperado está presente.

```c
int encontrarFaltante(int v[], int n) {
    int esperado = 1;
    for (int i = 0; i < n; i++) {
        if (v[i] == esperado)
            esperado++;
        else if (v[i] < esperado)
            continue; // já foi visto
    }
    return esperado;
}
```

> **Nota:** Essa versão funciona apenas se o vetor estiver **ordenado**. Sem ordenação, o custo extra de sortar domina.

### Complexidade

| | Valor |
|---|---|
| Tempo | **O(n)** (vetor ordenado) / **O(n log n)** (se precisar ordenar) |
| Espaço | **O(1)** |

---

## Solução 2 — Progressão Aritmética (fórmula da soma)

A soma dos inteiros de `1` a `k` é:

$$S = \frac{k(k+1)}{2}$$

Se o vetor deveria ter `n+1` elementos (de `1` a `n+1`), basta:

```
faltante = S(1..n+1) − soma(vetor)
```

```c
int encontrarFaltante(int v[], int n) {
    int k = n + 1;
    long somaEsperada = (long)k * (k + 1) / 2;
    long somaReal = 0;

    for (int i = 0; i < n; i++)
        somaReal += v[i];

    return (int)(somaEsperada - somaReal);
}
```

> **Atenção:** use `long` para evitar *overflow* quando `n` for grande.

### Complexidade

| | Valor |
|---|---|
| Tempo | **O(n)** |
| Espaço | **O(1)** |

---

## Comparação

| Critério | Força Bruta (ordenado) | Progressão Aritmética |
|---|---|---|
| Tempo | O(n) | O(n) |
| Espaço | O(1) | O(1) |
| Requer vetor ordenado? | Sim | Não |
| Risco de overflow | Não | Sim (mitigável com `long`) |
| Legibilidade | Direta | Exige conhecimento da fórmula |

**Conclusão:** a solução por progressão aritmética é **superior** porque não depende da ordenação e tem a mesma complexidade assintótica.

---

## Empresas onde esse exercício apareceu em processos seletivos

- **Amazon**
- **Microsoft**
- **Google**
- **Qualcomm**
- **IBM**
- **Adobe**
- **Cisco**
- **Goldman Sachs** (variante com dois números faltantes)
- **Flipkart**
- **Morgan Stanley**
- **Visa**
- **Accolite**
```

