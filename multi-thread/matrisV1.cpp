#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#define MAX_THREADS 4

pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t creating_threads_mutex = PTHREAD_MUTEX_INITIALIZER;
int creating_threads = 0;

std::vector<int> sharedMatrisA;
std::vector<int> sharedMatrisB;
std::vector<int> sharedMatrisC;
int m;
int n;
int k;

void *matrisHesapla(void *arg) {
    int satirno = *(int *)arg;

    if (creating_threads > 0) {
        pthread_mutex_lock(&condition_mutex);
        pthread_cond_wait(&condition_cond, &condition_mutex);
        pthread_mutex_unlock(&condition_mutex);
    } else {
        pthread_mutex_unlock(&creating_threads_mutex);
    }

    int ic1, ic2;
    for (ic1 = 0; ic1 < k; ic1++) {
        for (ic2 = 0; ic2 < n; ic2++) {
            sharedMatrisC[(satirno * k) + ic1] += sharedMatrisA[(satirno * n) + ic2] * sharedMatrisB[(ic2 * k) + ic1];
        }
    }
    pthread_exit(NULL);
}

void dosyayaYaz(const std::string& dosyaAdi, const std::vector<int>& matris, int satirSayisi, int sutunSayisi) {
    std::ofstream dosya(dosyaAdi);
    if (!dosya) {
        std::cout << "Dosya açılamadı." << std::endl;
        return;
    }

    for (int i = 0; i < satirSayisi; i++) {
        for (int j = 0; j < sutunSayisi; j++) {
            dosya << matris[i * sutunSayisi + j] << "\t";
        }
        dosya << std::endl;
    }

    dosya.close();
}

void dosyayaRastgeleSayilarYaz(const std::string& dosyaAdi, int satirSayisi, int sutunSayisi) {
    std::ofstream dosya(dosyaAdi);
    if (!dosya) {
        std::cout << "Dosya açılamadı." << std::endl;
        return;
    }

    srand(time(0));
    for (int i = 0; i < satirSayisi; i++) {
        for (int j = 0; j < sutunSayisi; j++) {
            int sayi = rand() % 10; // 0 ile 9 arasında rastgele bir sayı üret
            dosya << sayi << "\t";
        }
        dosya << std::endl;
    }

    dosya.close();
}

int main() {
    // Generate random numbers within a range
    srand(time(0));

    std::cout << "Matris boyutlarını girin:" << std::endl;
    std::cout << "m: ";
    std::cin >> m;
    std::cout << "n: ";
    std::cin >> n;
    std::cout << "k: ";
    std::cin >> k;

    std::vector<int> matrisA(m * n);
    std::vector<int> matrisB(n * k);
    std::vector<int> matrisC(m * k);

    for (int i = 0; i < m * n; i++) {
        matrisA[i] = rand() % 10; // Generate a random number between 0 and 9
    }

    for (int i = 0; i < n * k; i++) {
        matrisB[i] = rand() % 10; // Generate a random number between 0 and 9
    }

    sharedMatrisA = matrisA;
    sharedMatrisB = matrisB;
    sharedMatrisC.resize(m * k);

    for (int i = 0; i < m * k; i++) {
        sharedMatrisC[i] = 0;
    }

    pthread_t threads[MAX_THREADS];

    creating_threads = MAX_THREADS;

    for (int i = 0; i < MAX_THREADS; i++) {
        int *arg = new int(i);
        pthread_create(&threads[i], NULL, matrisHesapla, (void *)arg);
    }

    pthread_mutex_lock(&creating_threads_mutex);
    creating_threads = 0;
    pthread_mutex_unlock(&creating_threads_mutex);

    pthread_mutex_lock(&condition_mutex);
    pthread_cond_broadcast(&condition_cond);
    pthread_mutex_unlock(&condition_mutex);

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisA.txt", matrisA, m, n);
    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisB.txt", matrisB, n, k);
    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisC.txt", sharedMatrisC, m, k);
    dosyayaRastgeleSayilarYaz("/mnt/c/Users/suden/Desktop/rastgeleSayilar.txt", m, n);

    return 0;
}