#include <iostream>
#include <vector>
#include <algorithm>

void bt(int i, int j, int nextj, int curr, std::vector<std::vector<int64_t>> &dp, int &k, std::vector<std::vector<int>> &matrix){
    dp[i + 1][nextj] = std::max(dp[i + 1][nextj], dp[i][j]);
    if (curr == k) return;
    bt(i, j, nextj, curr + 1, dp, k, matrix);
    if (!((j) & (1 << curr))){
        if (curr < k - 1 && (!(j & (1 << (curr + 1))))){
            dp[i][j] += matrix[curr][i] + matrix[curr + 1][i];
            bt(i, j, nextj, curr + 2, dp, k, matrix);
            dp[i][j] -= matrix[curr][i] + matrix[curr + 1][i];
        }
        dp[i][j] += matrix[curr][i] + matrix[curr][i + 1];
        bt(i, j, nextj | (1 << curr), curr + 1, dp, k, matrix);
        dp[i][j] -= matrix[curr][i] + matrix[curr][i + 1];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> matrix(k, std::vector<int>(n));
    int maxState = (1 << k);
    std::vector<std::vector<int64_t>> dp (n + 1, std::vector<int64_t>(maxState, -1000000000000));
    dp[0][0] = 0;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            std::cin >> matrix[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < maxState; j++)
            if (dp[i][j] > -1000000000000)
                bt(i, j, 0, 0, dp, k, matrix);
    std::cout << dp[n][0];
    return 0;
}


