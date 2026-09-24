using namespace std;

/* ---- Otimizada: soma + soma de quadrados ---- */
pair<long long, long long> doisFaltantesOtimos(const vector<int>& v) {
    long long n = (long long)v.size();
    long long k = n + 2;                         // universo: 1..k
    long long s = k * (k + 1) / 2;               // soma esperada
    long long q = k * (k + 1) * (2 * k + 1) / 6; // soma de quadrados esperada

    for (int x : v) {
        s -= x;
        q -= (long long)x * x;
    }

    long long prod = (s * s - q) / 2;            // a * b
    long long disc = s * s - 4 * prod;           // (a - b)^2

    long long d = (long long)sqrt((double)disc); // raiz com correcao de precisao
    while (d * d > disc) d--;
    while ((d + 1) * (d + 1) <= disc) d++;

    long long a = (s - d) / 2;
    long long b = (s + d) / 2;
    return {a, b};
}

/* ---- Alternativa otimizada: XOR ---- */
pair<long long, long long> doisFaltantesXOR(const vector<int>& v) {
    long long n = (long long)v.size();

    long long x = 0;
    for (int val : v) x ^= val;
    for (long long i = 1; i <= n + 2; i++) x ^= i;   // x = a XOR b

    long long bit = x & (-x);                         // bit mais a direita de x
    long long a = 0, b = 0;
    for (int val : v)  (val & bit) ? a ^= val : b ^= val;
    for (long long i = 1; i <= n + 2; i++) (i & bit) ? a ^= i : b ^= i;

    if (a > b) swap(a, b);
    return {a, b};
}

int main() {
    struct Teste { vector<int> v; int e1, e2; };
    vector<Teste> testes = {
        {{1, 2, 4, 5, 6, 7},  3,  8},
        {{3, 1, 5, 4},         2,  6},
        {{1},                  2,  3},
        {{2, 3},               1,  4},
        {{2, 3, 4, 5, 6, 7, 8}, 1, 9},
        {{1, 2, 3, 4, 5, 6, 8, 9}, 7, 10},
    };

    bool ok = true;
    for (const auto& t : testes) {
        auto r2 = doisFaltantesOtimos(t.v);
        auto r3 = doisFaltantesXOR(t.v);
        bool p2 = (r2.first == t.e1 && r2.second == t.e2);
        bool p3 = (r3.first == t.e1 && r3.second == t.e2);
        if (!(p2 && p3)) ok = false;
        printf("n=%2d | soma+quad(%lld,%lld)=%s | xor(%lld,%lld)=%s\n",
               (int)t.v.size(),
               r2.first, r2.second, p2 ? "OK" : "ERRO",
               r3.first, r3.second, p3 ? "OK" : "ERRO");
    }

    // Teste aleatorio de larga escala (prova que a solucao escala)
    random_device rd; mt19937 gen(rd());
    for (int iter = 0; iter < 200; iter++) {
        int k = 2 + (int)(gen() % 2000);
        vector<int> todos(k);
        iota(todos.begin(), todos.end(), 1);
        shuffle(todos.begin(), todos.end(), gen);
        int fA = todos[k - 1], fB = todos[k - 2];
        todos.resize(k - 2);
        if (fA > fB) swap(fA, fB);

        auto r2 = doisFaltantesOtimos(todos);
        auto r3 = doisFaltantesXOR(todos);
        if (!(r2.first == fA && r2.second == fB && r3.first == fA && r3.second == fB)) {
            printf("FALHOU: universo=%d, faltantes %d,%d\n", k, fA, fB);
            ok = false;
            break;
        }
    }
    printf(ok ? "\nTODOS OS TESTES PASSARAM\n" : "\nHOUVE FALHAS\n");
    return 0;
}