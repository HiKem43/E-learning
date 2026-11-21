#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
using namespace std;

const int MAXN = 1005;

int n, k;
// a luu gia tri tung o; dp[i][j] la tong hinh chu nhat tu (1, 1) den (i, j).
// Mang danh chi so tu 1 de hang 0 va cot 0 cua dp mac dinh bang 0.
long long a[MAXN][MAXN];
long long dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hai file duoc tim trong thu muc chay chuong trinh.
    ifstream fin("input_B1.txt");
    if (!fin) {
        cerr << "Khong the mo file input_B1.txt\n";
        return 1;
    }

    // input_B1.txt gom n, k, sau do la ma tran n x n.
    if (!(fin >> n >> k)) {
        cerr << "Du lieu trong input_B1.txt khong hop le\n";
        return 1;
    }

    if (n <= 0 || n >= MAXN || k <= 0 || k > n) {
        cerr << "Gia tri n hoac k trong input_B1.txt khong hop le\n";
        return 1;
    }

    // Doc luong vang tai tung o.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!(fin >> a[i][j])) {
                cerr << "Du lieu trong input_B1.txt khong hop le\n";
                return 1;
            }
        }
    }

    ofstream fout("output_B1.txt");
    if (!fout) {
        cerr << "Khong the mo file output_B1.txt\n";
        return 1;
    }

    // Tong tien to 2 chieu: cong them hang tren va cot trai,
    // roi tru phan giao bi tinh hai lan.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = a[i][j]
                     + dp[i-1][j]
                     + dp[i][j-1]
                     - dp[i-1][j-1];
        }
    }

    // Duyet moi o (i, j) co the lam goc tren-trai cua hinh vuong k x k.
    // LLONG_MIN dam bao van chon dung neu tat ca tong deu am.
    long long ans = LLONG_MIN;
    int bestI = 1, bestJ = 1;

    for (int i = 1; i <= n-k+1; i++) {
        for (int j = 1; j <= n-k+1; j++) {

            // Tinh tong hinh chu nhat (i, j) den (i+k-1, j+k-1)
            // bang tong tien to va nguyen ly bao gom - loai tru.
            long long sum =
                dp[i+k-1][j+k-1]
                - dp[i-1][j+k-1]
                - dp[i+k-1][j-1]
                + dp[i-1][j-1];

            if (sum > ans) {
                ans = sum;
                // Chi cap nhat khi lon hon, nen neu hoa thi giu vi tri gap truoc.
                bestI = i;
                bestJ = j;
            }
        }
    }

    // File output chi ghi tong lon nhat; vi tri duoc thong bao tren man hinh.
    fout << ans << '\n';
    fout.close();

    cout << "Da ghi ket qua vao output_B1.txt: " << ans << '\n';
    cout << "Hinh vuong duoc chon: tu hang " << bestI << ", cot " << bestJ
         << " den hang " << bestI + k - 1 << ", cot " << bestJ + k - 1 << '\n';

    return 0;
}
