/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *  public:
 *   bool canMove(char direction);
 *   void move(char direction);
 *   boolean isTarget();
 * };
 */

enum Grid { UNVISITED, START, TARGET, BLOCKED, EMPTY };

class Solution {
 public:
  int findShortestPath(GridMaster& master) {
    constexpr int m = 500;
    constexpr int startX = m;
    constexpr int startY = m;

    vector<vector<Grid>> grid(m * 2, vector<Grid>(m * 2, UNVISITED));

    // build the grid information by dfs
    dfs(master, grid, startX, startY);

    int ans = 0;
    queue<pair<int, int>> q{{{startX, startY}}};
    grid[startX][startY] = BLOCKED;

    // find the steps by bfs
    while (!q.empty()) {
      ++ans;
      for (int size = q.size(); size > 0; --size) {
        const auto [i, j] = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k) {
          const int x = i + dirs[k];
          const int y = j + dirs[k + 1];
          if (grid[x][y] == TARGET)
            return ans;
          if (grid[x][y] == BLOCKED)
            continue;
          grid[x][y] = BLOCKED;
          q.push({x, y});
        }
      }
    }

    return -1;
  }

 private:
  const vector<int> dirs{0, 1, 0, -1, 0};
  const vector<char> charTable{'R', 'D', 'L', 'U'};

  void dfs(GridMaster& master, vector<vector<Grid>>& grid, int i, int j) {
    if (grid[i][j] != UNVISITED)
      return;
    if (master.isTarget())
      grid[i][j] = TARGET;
    else
      grid[i][j] = EMPTY;

    for (int k = 0; k < 4; ++k) {
      const int x = i + dirs[k];
      const int y = j + dirs[k + 1];
      const char d = charTable[k];
      const char undoD = charTable[(k + 2) % 4];
      if (master.canMove(d)) {
        master.move(d);
        dfs(master, grid, x, y);
        master.move(undoD);
      } else {
        grid[x][y] = BLOCKED;
      }
    }
  }
};
