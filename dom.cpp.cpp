#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, k;
    std::cin >> n;
    std::cin >> k;
    std::vector<std::vector<int>> matrix(k, std::vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
    int maxState = 1 << k;
    std::vector<std::vector<int>> dp(n, std::vector<int>(maxState, -1));
    for (int i = 0; i < n; i++) {
        for (int j = maxState - 1; j >= 0; j--) {
            if (dp[i][j] > -1)
                continue;
            std::vector<std::vector<int>> currDp(k, std::vector<int>(2, 0)); // do obliczenia dp[i][j], pierwsza to maks wynik dotychczas a druga jego ciag
            if (i > 0) {
                currDp[0][0] = dp[i - 1][maxState - 1];
                currDp[0][1] = maxState - 1;
                if (j & (1 << 0) && currDp[0][0] < matrix[0][i] + matrix[0][i - 1] + dp[i - 1][(maxState - 1) & ~(1 << 0)]) { 
                    currDp[0][0] = matrix[0][i] + matrix[0][i - 1] + dp[i - 1][(maxState - 1) & ~(1 << 0)];
                    currDp[0][1] = (maxState - 1) & ~(1 << 0);
                }
                if (k > 1) {
                    currDp[1] = currDp[0];
                    if (j & (1 << 1) && j & (1 << 0) && currDp[1][0] < matrix[1][i] + matrix[0][i] + dp[i - 1][maxState - 1]) {
                        currDp[1][0] = matrix[1][i] + matrix[0][i] + dp[i - 1][maxState - 1];
                        currDp[1][1] = maxState - 1;
                    }
                    if (j & (1 << 1) && currDp[1][0] < matrix[1][i] + matrix[1][i - 1] + currDp[0][0] - dp[i - 1][currDp[0][1]] + dp[i - 1][currDp[0][1] & ~(1 << 1)]) {
                        currDp[1][0] = matrix[1][i] + matrix[1][i - 1] + currDp[0][0] - dp[i - 1][currDp[0][1]] + dp[i - 1][currDp[0][1] & ~(1 << 1)];
                        currDp[1][1] = currDp[0][1] & ~(1 << 1);
                    }
                }
            }
            else if (k > 1 && j & (1 << 1) && j & (1 << 0)) {
                currDp[1][0] = std::max(currDp[1][0], matrix[0][0] + matrix[1][0]);
            }
            for (int l = 2; l < k; l++) {
                currDp[l] = currDp[l - 1];
                if (j & (1 << l) && j & (1 << (l - 1)) && currDp[l][0] < matrix[l][i] + matrix[l - 1][i] + currDp[l - 2][0]) {
                    currDp[l][0] = matrix[l][i] + matrix[l - 1][i] + currDp[l - 2][0];
                    currDp[l][1] = currDp[l - 2][1];
                }
                if (i > 0 && j & (1 << l) && currDp[l][0] < matrix[l][i] + matrix[l][i - 1] + currDp[l - 1][0] - dp[i - 1][currDp[l - 1][1]] + dp[i - 1][currDp[l - 1][1] & ~(1 << l)]) {
                    currDp[l][0] = matrix[l][i] + matrix[l][i - 1] + currDp[l - 1][0] - dp[i - 1][currDp[l - 1][1]] + dp[i - 1][currDp[l - 1][1] & ~(1 << l)];
                    currDp[l][1] = currDp[l - 1][1] & ~(1 << l);
                }
                dp[i][j & ((1 << (l + 1)) - 1)] = currDp[l][0];

            }
            dp[i][j] = currDp[k - 1][0];
        }
    }
    std::cout << dp[n - 1][maxState - 1] << "\n";

    return 0;
}
