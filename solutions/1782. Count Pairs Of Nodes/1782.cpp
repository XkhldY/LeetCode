class Solution {
 public:
  vector<int> countPairs(int n, vector<vector<int>>& edges,
                         vector<int>& queries) {
    vector<int> ans(queries.size());

    // count[i] := # of edges of node i
    vector<int> count(n + 1);

    // shared[i][j] := # of edges incident to i or j, where i < j
    vector<unordered_map<int, int>> shared(n + 1);

    for (const auto& edge : edges) {
      ++count[edge[0]];
      ++count[edge[1]];
      ++shared[min(edge[0], edge[1])][max(edge[0], edge[1])];
    }

    vector<int> sorted(count);
    sort(begin(sorted), end(sorted));

    int k = 0;
    for (const auto& q : queries) {
      for (int i = 1, j = n; i < j;)
        if (sorted[i] + sorted[j] > q)
          ans[k] += (j--) - i;
        else
          ++i;
      for (int i = 1; i <= n; ++i)
        for (const auto& [j, sh] : shared[i])
          if (count[i] + count[j] > q && count[i] + count[j] - sh <= q)
            --ans[k];
      ++k;
    }

    return ans;
  }
};
