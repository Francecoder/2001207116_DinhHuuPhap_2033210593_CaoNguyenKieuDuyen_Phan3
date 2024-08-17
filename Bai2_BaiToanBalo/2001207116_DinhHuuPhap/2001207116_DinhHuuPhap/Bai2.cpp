/*
Bài 2. Cài đặt chương trình giải bài toán ba lô theo phương pháp quy hoạch động.
Cho một cái ba lô có thể đựng một trọng lượng W và n loại đồ vật, mỗi đồ vật i có một
trọng lượng gi và một giá trị vi. Tất cả các loại đồ vật đều có số lượng không hạn chế. Tìm
một cách lựa chọn các đồ vật đựng vào ba lô, chọn các loại đồ vật nào, mỗi loại lấy bao nhiêu
sao cho tổng trọng lượng không vượt quá W và tổng giá trị là lớn nhất
Tạo file txt chứa dữ liệu test là trọng lượng balo, danh sách các vật cùng trọng lượng,
giá trị của chúng. Đọc dữ liệu và xử lý, sau đó xuất kết quả ra màn hình và ghi vào file txt.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 10;

struct Do_vat {
    char Ten[20];
    int Trong_luong;
    int Gia_tri;
    int Phuong_an;
};

typedef Do_vat Danh_sach_vat[MAX]; // Định nghĩa mảng 1 chiều kiểu Do_vat bằng tên
typedef int Bang[MAX][100]; // Định nghĩa mảng 2 chiều kiểu int bằng tên Bang

void Tao_Bang(Danh_sach_vat ds_vat, int n, int W, Bang F, Bang X) {
    int xk, yk, k;
    int FMax, XMax, v;

    for (v = 0; v <= W; v++) {
        X[1][v] = v / ds_vat[1].Trong_luong;
        F[1][v] = X[1][v] * ds_vat[1].Gia_tri;
    }

    for (k = 2; k <= n; k++) {
        X[k][0] = 0;
        F[k][0] = 0;
        for (v = 1; v <= W; v++) {
            FMax = F[k - 1][v];
            XMax = 0;
            yk = v / ds_vat[k].Trong_luong;
            for (xk = 1; xk <= yk; xk++) {
                if (F[k - 1][v - xk * ds_vat[k].Trong_luong] + xk * ds_vat[k].Gia_tri > FMax) {
                    FMax = F[k - 1][v - xk * ds_vat[k].Trong_luong] + xk * ds_vat[k].Gia_tri;
                    XMax = xk;
                }
            }
            F[k][v] = FMax;
            X[k][v] = XMax;
        }
    }
}

void Tra_Bang(Danh_sach_vat ds_vat, int n, int W, Bang F, Bang X) {
    int k, v;
    v = W;
    for (k = n; k >= 1; k--) {
        if (X[k][v] > 0) {
            ds_vat[k].Phuong_an = X[k][v];
            v = v - X[k][v] * ds_vat[k].Trong_luong;
        }
    }
}

int main() {
    Danh_sach_vat ds_vat;
    int n, W;
    Bang F, X;

    ifstream infile("input_bai2.txt");
    if (!infile) {
        cerr << "Unable to open file input.txt";
        exit(1); // terminate with error
    }

    infile >> W >> n;
    for (int i = 1; i <= n; i++) {
        infile >> ds_vat[i].Ten >> ds_vat[i].Trong_luong >> ds_vat[i].Gia_tri;
        ds_vat[i].Phuong_an = 0;
    }
    infile.close();
    printf("Trong luong toi da cua balo: %d\n", W);
    printf("Danh sach do vat ban dau :\n");
    for (int i = 1; i <= n; i++) {
        printf("Ten:%s ,Trong luong : %d, Gia tri: %d \n", ds_vat[i].Ten, ds_vat[i].Trong_luong, ds_vat[i].Gia_tri);
    }
    Tao_Bang(ds_vat, n, W, F, X);
    Tra_Bang(ds_vat, n, W, F, X);
    int trongluongtoida = 0, giatritoida = 0;
    cout << "Cac do vat chon de dua vao balo:\n";
    for (int i = 1; i <= n; i++) {
        if (ds_vat[i].Phuong_an > 0) {
            cout << "Do vat: " << ds_vat[i].Ten << " Trong luong: " << ds_vat[i].Trong_luong << ", So luong : " << ds_vat[i].Phuong_an << endl;
            trongluongtoida = trongluongtoida + ds_vat[i].Trong_luong * ds_vat[i].Phuong_an;
            giatritoida = giatritoida + ds_vat[i].Gia_tri * ds_vat[i].Phuong_an;
        }
    }
    printf("Trong luong toi da dua vao balo: %d\n", trongluongtoida);
    printf("Gia tri toi da dua vao balo: %d\n", giatritoida);

    ofstream outfile("output_bai2.txt");
    if (!outfile) {
        cerr << "Unable to open file output.txt";
        exit(1);
    }

    outfile << "Cac do vat chon de dua vao balo:\n";
    for (int i = 1; i <= n; i++) {
        if (ds_vat[i].Phuong_an > 0) {
            outfile << "Do vat: " << ds_vat[i].Ten << " Trong luong: " << ds_vat[i].Trong_luong << ", So luong : " << ds_vat[i].Phuong_an << endl;

        }
    }
    outfile << "Trong luong toi da dua vao balo : " << trongluongtoida;
    outfile << "Gia tri toi da dua vao balo : " << giatritoida;

    outfile.close();

    return 0;
}