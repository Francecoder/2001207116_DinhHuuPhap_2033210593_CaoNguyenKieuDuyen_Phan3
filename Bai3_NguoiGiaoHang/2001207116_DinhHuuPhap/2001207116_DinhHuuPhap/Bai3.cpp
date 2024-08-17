#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

// Hàm tìm đường đi có tổng giá trị lớn nhất
int findMaxPath(vector<vector<int>>& A, int m, int n, vector<int>& path) {
    // Tạo bảng dp để lưu trữ giá trị lớn nhất tại mỗi nút lưới
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Khởi tạo cột đầu tiên của bảng dp
    for (int i = 0; i < m; ++i) {
        dp[i][0] = A[i][0];
    }

    // Tính giá trị lớn nhất tại mỗi nút lưới theo các quy tắc
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            int maxPrev = dp[i][j - 1];
            if (i > 0) maxPrev = max(maxPrev, dp[i - 1][j - 1]);
            if (i < m - 1) maxPrev = max(maxPrev, dp[i + 1][j - 1]);
            dp[i][j] = A[i][j] + maxPrev;
        }
    }

    // Tìm giá trị lớn nhất tại cột cuối cùng
    int maxPath = dp[0][n - 1];
    int maxIndex = 0;
    for (int i = 1; i < m; ++i) {
        if (dp[i][n - 1] > maxPath) {
            maxPath = dp[i][n - 1];
            maxIndex = i;
        }
    }

    // Truy vết lại đường đi
    int j = n - 1;
    path[j] = maxIndex;
    for (j = n - 1; j > 0; --j) {
        int i = path[j];
        if (i > 0 && dp[i][j] == dp[i - 1][j - 1] + A[i][j]) {
            path[j - 1] = i - 1;
        }
        else if (i < m - 1 && dp[i][j] == dp[i + 1][j - 1] + A[i][j]) {
            path[j - 1] = i + 1;
        }
        else {
            path[j - 1] = i;
        }
    }

    return maxPath;
}
// Hàm in lưới
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
}
// Hàm in bảng cửu chương từ 1 đến 9 theo hàng dọc
void printMultiplicationTable() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            cout << j << " x " << i << " = " << j * i << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Kích thước của lưới
    int m = 4, n = 4;
    // Khởi tạo lưới
    vector<vector<int>> A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    // Mảng lưu trữ đường đi
    vector<int> path(n);
    cout << "Grid:" << endl;
    printGrid(A);
    // Tìm tổng giá trị lớn nhất có thể đạt được
    int maxPathSum = findMaxPath(A, m, n, path);
    cout << "Max path sum: " << maxPathSum << endl;

    // In đường đi
    cout << "Path: ";
    for (int i = 0; i < n; ++i) {
        cout << "(" << path[i] << ", " << i << ") ";
    }
    cout << endl;

    // In bảng cửu chương
    //printMultiplicationTable();
     // Ghi lưới vào file
    ofstream outFile("output_bai3.txt");
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    outFile << "Grid:" << endl;
    for (const auto& row : A) {
        for (int value : row) {
            outFile << value << " ";
        }
        outFile << endl;
    }

    // Ghi tổng giá trị lớn nhất vào file
    outFile << "Max path sum: " << maxPathSum << endl;

    // Ghi đường đi vào file
    outFile << "Path: ";
    for (int i = 0; i < n; ++i) {
        outFile << "(" << path[i] << ", " << i << ") ";
    }
    outFile << endl;

    // Đóng file
    outFile.close();
    return 0;
}
