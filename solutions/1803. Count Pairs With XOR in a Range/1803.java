class TrieNode {
  public TrieNode[] next = new TrieNode[2];
  public int count = 0;
}

class Solution {
  public int countPairs(int[] nums, int low, int high) {
    int ans = 0;

    for (final int num : nums) {
      ans += getCount(num, high + 1) - getCount(num, low);
      insert(num);
    }

    return ans;
  }

  private final int kHeight = 14;
  private TrieNode root = new TrieNode();

  private void insert(int num) {
    TrieNode node = root;
    for (int h = kHeight; h >= 0; --h) {
      final int index = ((num >> h) & 1);
      if (node.next[index] == null)
        node.next[index] = new TrieNode();
      node = node.next[index];
      ++node.count;
    }
  }

  // # of nums < limit
  private int getCount(int num, int limit) {
    TrieNode node = root;
    int count = 0;

    for (int h = kHeight; h >= 0; --h) {
      final int bitNum = ((num >> h) & 1);
      final int bitLimit = ((limit >> h) & 1);
      if (bitLimit == 1) {
        if (node.next[bitNum] != null)
          count += node.next[bitNum].count;
        node = node.next[1 - bitNum];
      } else {
        node = node.next[bitNum];
      }
      if (node == null)
        break;
    }

    return count;
  }
}
