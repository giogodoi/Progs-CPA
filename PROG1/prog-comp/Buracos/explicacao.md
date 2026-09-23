# Análise do Algoritmo: Contagem de Agrupamentos em Matriz

Este documento explica o funcionamento lógico e a complexidade do algoritmo utilizado para contar agrupamentos de caracteres (buracos formados por zeros) em uma matriz bidimensional. O método aplicado é conhecido como Busca em Profundidade, ou DFS (Depth First Search).

## 1. Funcionamento Base

O algoritmo opera com base em três passos fundamentais: Varredura, Detecção e Marcação.

*   **Varredura:** O código principal utiliza dois laços de repetição tradicionais para percorrer a matriz de forma sequencial, lendo célula por célula (da esquerda para a direita, de cima para baixo).
*   **Detecção:** Quando o laço de repetição encontra o caractere `'0'`, ele identifica o início de um novo agrupamento. Imediatamente, o contador total de buracos é acrescido em 1.
*   **Marcação (Contágio):** Para evitar que as outras partes deste mesmo agrupamento sejam contadas novamente, o algoritmo pausa a varredura principal e chama uma função recursiva. Essa função visita a célula atual, transforma o `'0'` em `'1'` e, em seguida, olha para os quatro vizinhos adjacentes (cima, baixo, esquerda e direita). Se algum vizinho também for `'0'`, a função se repete a partir dele. Esse processo continua até que todos os zeros conectados àquele agrupamento original tenham sido substituídos por `'1'`.

Após a marcação completa do buraco, a varredura principal retorna de onde parou. Como os zeros daquele agrupamento específico foram transformados em `'1'`, eles serão ignorados, garantindo a contagem correta.

## 2. Complexidade de Tempo

A complexidade de tempo descreve quanto tempo o algoritmo leva para rodar à medida que a entrada cresce. 

Neste caso, a complexidade de tempo é **$O(L \times C)$**, onde $L$ representa o número de linhas e $C$ representa o número de colunas da matriz.

**Explicação simplificada:**
Apesar de termos laços de repetição e uma função recursiva rodando em conjunto, cada célula da matriz é processada um número estritamente limitado de vezes.
1. O laço principal passa por cada célula exatamente uma vez.
2. A função de marcação só visita uma célula se ela for um `'0'`. Assim que visita, ela a transforma em `'1'`. Isso garante que a função de marcação jamais visitará a mesma célula duas vezes.

Portanto, o tempo de execução cresce de forma linear e proporcional à quantidade total de células na matriz.

## 3. Complexidade de Espaço

A complexidade de espaço descreve a quantidade de memória extra que o algoritmo exige para funcionar.

Neste caso, a complexidade de espaço é de **$O(L \times C)$** no pior cenário possível.

**Explicação simplificada:**
O consumo de memória adicional vem da Pilha de Chamadas (Call Stack) do sistema operacional, utilizada pelas chamadas recursivas da função de marcação. 

*   **Pior caso:** Se a matriz for inteiramente composta por caracteres `'0'`, a função chamará a si mesma repetidamente, navegando por todas as células da matriz antes de começar a finalizar as chamadas. Isso criará um acúmulo de dados na memória proporcional ao tamanho total da matriz.
*   **Melhor caso:** Se a matriz for composta inteiramente por `'1'`s, a função recursiva nunca será chamada, e a complexidade de espaço extra será $O(1)$ (constante), consumindo apenas o espaço das variáveis básicas.