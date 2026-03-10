#include <iostream>
#include <omp.h>
#include <random>

#define N 1000
#define chnk 100
#define show 10

void imprimeArreglo(float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!!\n";
    // Creating random generator
    unsigned int seed = 44u;
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);
    // init arrays and loop counter
    float a[N], b[N], c[N];
    int i;
    

    for (i = 0; i < N; i++)
    {
        a[i] = dist(rng);
        b[i] = dist(rng);
        c[i] = 0.0f;
    }
    int chunk = chnk;

    #pragma omp parallel for \
    shared(a, b, c, chunk) private(i) \
    schedule(static, chunk)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float *d)
{
    for (int x = 0; x < show; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}