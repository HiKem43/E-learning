#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int MAXN = 1005;

int n, k;
long long a[MAXN][MAXN];
long long dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input_B1.txt");
    if (!fin) {
        cerr << "Khong the mo file input_B1.txt\n";
        return 1;
    }

    ofstream fout("output_B1.txt");
    if (!fout) {
        cerr << "Khong the mo file output_B1.txt\n";
        return 1;
    }

    // Nhap kich thuoc ma tran va kich thuoc hinh vuong
    if (!(fin >> n >> k)) {
        cerr << "Du lieu trong input_B1.txt khong hop le\n";
        return 1;
    }

    // Nhap luong vang tai tung o
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!(fin >> a[i][j])) {
                cerr << "Du lieu trong input_B1.txt khong hop le\n";
                return 1;
            }
        }
    }

    // Xay dung bang tong tien to 2 chieu
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = a[i][j]
                     + dp[i-1][j]
                     + dp[i][j-1]
                     - dp[i-1][j-1];
        }
    }

    // Tim hinh vuong k x k co tong vang lon nhat
    long long ans = LLONG_MIN;
    int bestI = 1, bestJ = 1;

    for (int i = 1; i <= n-k+1; i++) {
        for (int j = 1; j <= n-k+1; j++) {

            long long sum =
                dp[i+k-1][j+k-1]
                - dp[i-1][j+k-1]
                - dp[i+k-1][j-1]
                + dp[i-1][j-1];

            if (sum > ans) {
                ans = sum;
                bestI = i;
                bestJ = j;
            }
        }
    }

    // Xuat ket qua
    fout << ans << '\n';
    fout.close();

    cout << "Da ghi ket qua vao output_B1.txt: " << ans << '\n';
    cout << "Hinh vuong duoc chon: tu hang " << bestI << ", cot " << bestJ
         << " den hang " << bestI + k - 1 << ", cot " << bestJ + k - 1 << '\n';

    return 0;
}
