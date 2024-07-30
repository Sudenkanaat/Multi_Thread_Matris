#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

void dosyayaYaz(const std::string& dosyaAdi, const std::vector<std::vector<int>>& matris) {
    std::ofstream dosya(dosyaAdi);
    if (!dosya) {
        std::cout << "Dosya açılamadı." << std::endl;
        return;
    }

    for (const auto& row : matris) {
        for (int value : row) {
            dosya << value << "\t";
        }
        dosya << std::endl;
    }

    dosya.close();
}

int main() {
    int m, n, k;

    std::cout << "Matris boyutlarını girin:" << std::endl;
    std::cout << "m: ";
    std::cin >> m;
    std::cout << "n: ";
    std::cin >> n;
    std::cout << "k: ";
    std::cin >> k;

    std::vector<std::vector<int>> matrisA(m, std::vector<int>(n));
    std::vector<std::vector<int>> matrisB(n, std::vector<int>(k));
    std::vector<std::vector<int>> matrisC(m, std::vector<int>(k));

    // Rastgele sayı üretimi için seed ayarla
    srand(time(0));

    // Matris A'yı rastgele sayılarla doldur ve dosyaya yaz
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrisA[i][j] = rand() % 10; // 0 ile 9 arasında rastgele bir sayı üret
        }
    }
    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisA_v2.txt", matrisA);

    // Matris B'yi rastgele sayılarla doldur ve dosyaya yaz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            matrisB[i][j] = rand() % 10; // 0 ile 9 arasında rastgele bir sayı üret
        }
    }
    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisB_v2.txt", matrisB);

    // Matris C'yi hesapla
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            for (int ic = 0; ic < n; ic++) {
                matrisC[i][j] += matrisA[i][ic] * matrisB[ic][j];
            }
        }
    }

    // Matris C'yi dosyaya yaz
    dosyayaYaz("/mnt/c/Users/suden/Desktop/matrisC_v2.txt", matrisC);
    return 0;
}
