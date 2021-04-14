struct TrieNode {
  TrieNode() : next(2) {}
  vector<TrieNode*> next;
  int count = 0;
};

class Solution {
 public:
  int countPairs(vector<int>& nums, int low, int high) {
    int ans = 0;

    for (const int num : nums) {
      ans += getCount(num, high + 1) - getCount(num, low);
      insert(num);
    }

    return ans;
  }

 private:
  const int kHeight = 14;
  TrieNode root;

  void insert(int num) {
    TrieNode* node = &root;
    for (int h = kHeight; h >= 0; --h) {
      const int index = ((num >> h) & 1);
      if (!node->next[index])
        node->next[index] = new TrieNode();
      node = node->next[index];
      ++node->count;
    }
  }

  // # of nums < limit
  int getCount(int num, int limit) {
    TrieNode* node = &root;
    int count = 0;

    for (int h = kHeight; h >= 0; --h) {
      const int bitNum = ((num >> h) & 1);
      const int bitLimit = ((limit >> h) & 1);
      if (bitLimit == 1) {
        if (node->next[bitNum])
          count += node->next[bitNum]->count;
        node = node->next[1 - bitNum];
      } else {
        node = node->next[bitNum];
      }
      if (!node)
        break;
    }

    return count;
  }
};
