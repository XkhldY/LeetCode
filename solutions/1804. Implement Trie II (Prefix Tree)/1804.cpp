struct TrieNode {
  TrieNode() : children(26, nullptr) {}
  vector<TrieNode*> children;
  int prefixCount = 0;
  int wordCount = 0;
};

class Trie {
 public:
  void insert(string word) {
    TrieNode* node = &root;
    for (const char c : word) {
      const int i = c - 'a';
      if (node->children[i] == nullptr)
        node->children[i] = new TrieNode();
      node = node->children[i];
      ++node->prefixCount;
    }
    ++node->wordCount;
  }

  int countWordsEqualTo(string word) {
    TrieNode* node = find(word);
    return node ? node->wordCount : 0;
  }

  int countWordsStartingWith(string prefix) {
    TrieNode* node = find(prefix);
    return node ? node->prefixCount : 0;
  }

  void erase(string word) {
    TrieNode* node = &root;
    for (const char c : word) {
      const int i = c - 'a';
      node = node->children[i];
      --node->prefixCount;
    }
    --node->wordCount;
  }

 private:
  TrieNode root;

  TrieNode* find(const string& s) {
    TrieNode* node = &root;
    for (const char c : s) {
      const int i = c - 'a';
      if (!node->children[i])
        return nullptr;
      node = node->children[i];
    }
    return node;
  }
};
