/*
  Implementation of classic "Knapsack" problem solution.

  Problem: Given knapsack with capacity S and N items.
  Each item have it's weight. We must put to knapsack 
  as much weight as possible.
*/

#include <iostream>
#include <vector>

class DP {
public:
  DP(int capacity, const std::vector<int>& weights)
    : capacity(capacity), weights(weights), n(weights.size()) {};

  ~DP() = default;

  long long getAnswer();
  void print();
  
private:
  int capacity;
  int n;
  const std::vector<int>& weights;
  std::vector<std::vector<long long>> dp;

  DP(const DP& other);
  
  void setupBase();
  void update(int i, int w);
};

void DP::setupBase() {
  n = weights.size();
  dp.assign(n, std::vector<long long> (capacity + 1, 0));

  for (int w = 0; w <= capacity; ++w) {
    if (w >= weights[0]) {
      dp[0][w] = std::max(0ll, weights[0]);
    }
  }
}

void DP::update(int i, int w) {
  long long valueIfSkip = dp[i - 1][w];
  long long valueIfTake = 0;
  if (w >= weights[i])
    valueIfTake = dp[i - 1][w - weights[i]] + weights[i];

  dp[i][w] = std::max(valueIfSkip, valueIfTake);
}

long long DP::getAnswer() {
  setupBase();

  for (int i = 1; i < n; ++i) {
    for (int w = 0; w <= capacity; ++w) {
      update(i, w);
    }
  }

  long long answer = 0;
  for (int w = 0; w <= capacity; ++w) {
    answer = std::max(answer, dp.back()[w]);
  }

  return answer;
}

void DP::print() {
  std::cout << "DP table [" << n << "x" << capacity + 1 << "]\n";
  for (int i = 0; i < n; ++i) {
    for (int w = 0; w <= capacity; ++w) {
      std::cout << dp[i][w] << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
 
  #ifdef local
    freopen("io/in.txt", "r", stdin);
    freopen("io/out.txt", "w", stdout);
  #endif

  int capacity, n;
  std::cin >> capacity >> n;
  std::vector<int> weights(n);
  for (auto &item : weights) {
    std::cin >> item;
  }

  DP dp(capacity, weights);
  std::cout << dp.getAnswer();
}
