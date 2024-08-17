#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int binomialCoefficient(int n, int k) {
    std::vector<std::vector<int>> C(n + 1, std::vector<int>(k + 1, 0));
    if (n == k)
    {
        return 1;
    }
    else if (n < k)
    {
        return -1;
    }
    else {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= std::min(i, k); ++j)
            {
                if (j == 0 || j == i) {
                    C[i][j] = 1;
                }
                else {
                    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
                }
            }
        }

        return C[n][k];
    }

}
//Link test to hop https://quayso.vn/Cong-cu-tinh-to-hop-online.aspx

int main() {
    /*
    int n, k;
    do{
        printf("Nhap to hop n chap k voi n >= k (n va k deu lon hon 0)\n");
        printf("Nhap n: \n");
        scanf_s("%d", &n);
        printf("Nhap k: \n");
        scanf_s("%d", &k);

    } while (n < k||n<0||k<0);


    std::cout << "To hop chap " << k << " cua " << n << " la: " << binomialCoefficient(n, k) << std::endl;
    */
    cout << "Neu n<k thi ket qua mac dinh la -1!!!" << endl;
    ifstream inputFile("input_bai1.txt");
    ofstream outputFile("output_bai1.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Khong the mo file dau vao!" << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file dau ra!" << std::endl;
        return 1;
    }

    int n, k;
    while (inputFile >> n >> k) {
        int result = binomialCoefficient(n, k);
        cout << "To hop chap " << k << " cua " << n << " la: " << result << std::endl;
        outputFile << "To hop chap " << k << " cua " << n << " la: " << result << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Xong! Ket qua da duoc ghi vao file output_bai1.txt" << std::endl;

    return 0;
}