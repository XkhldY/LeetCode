class Solution {
  public int[] countPairs(int n, int[][] edges, int[] queries) {
    int[] ans = new int[queries.length];

    // count[i] := # of edges of node i
    int[] count = new int[n + 1];

    // shared[i][j] := # of edges incident to i or j, where i < j
    Map<Integer, Integer>[] shared = new Map[n + 1];

    for (int i = 1; i <= n; ++i)
      shared[i] = new HashMap<>();

    for (int[] edge : edges) {
      ++count[edge[0]];
      ++count[edge[1]];
      final int a = Math.min(edge[0], edge[1]);
      final int b = Math.max(edge[0], edge[1]);
      shared[a].put(b, shared[a].getOrDefault(b, 0) + 1);
    }

    int[] sorted = count.clone();
    Arrays.sort(sorted);

    int k = 0;
    for (final int q : queries) {
      for (int i = 1, j = n; i < j;)
        if (sorted[i] + sorted[j] > q)
          ans[k] += (j--) - i;
        else
          ++i;
      for (int i = 1; i <= n; ++i)
        for (var p : shared[i].entrySet()) {
          final int j = p.getKey();
          final int sh = p.getValue();
          if (count[i] + count[j] > q && count[i] + count[j] - sh <= q)
            --ans[k];
        }
      ++k;
    }

    return ans;
  }
}
