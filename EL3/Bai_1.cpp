
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, k;
long long a[MAXN][MAXN];
long long dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Nhap kich thuoc ma tran va kich thuoc hinh vuong
    cin >> n >> k;

    // Nhap luong vang tai tung o
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
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
    long long ans = 0;

    for (int i = 1; i <= n-k+1; i++) {
        for (int j = 1; j <= n-k+1; j++) {

            long long sum =
                dp[i+k-1][j+k-1]
                - dp[i-1][j+k-1]
                - dp[i+k-1][j-1]
                + dp[i-1][j-1];

            ans = max(ans, sum);
        }
    }

    // Xuat ket qua
    cout << ans << '\n';

    return 0;
}
