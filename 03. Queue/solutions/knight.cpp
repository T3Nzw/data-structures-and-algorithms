#include <iostream>
#include <algorithm>
#include <queue>

struct Position {
  int x, y, dist;
};

bool operator==(Position const &p1, Position const &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool validStep(int n, Position const &p) {
  return p.x >= 0 && p.x < n && p.y >= 0 && p.y < n;
}

// bfs traversal
int minSteps(int n, Position const &start, Position const &end) {
  std::queue<Position> pos;
  std::vector<std::vector<bool> > visited(n);
  std::fill(visited.begin(), visited.end(), std::vector<bool>(n, false));

  pos.push({start.x, start.y, 0});

  while (!pos.empty()) {

    Position cur = pos.front();
    pos.pop();

    if (cur == end)
      return cur.dist;

    if (visited[cur.x][cur.y])
      continue;

    visited[cur.x][cur.y] = true;

    // друг вариант е да запишем изместванията в два масива

    /*
    static int const dx[]{1, 1, -1, -1, 2, 2, -2, -2};
    static int const dy[]{2, -2, 2, -2, 1, -1, 1, -1};
    */

    for (int i = -2; i <= 2; ++i) {
      for (int j = -2; j <=2; ++j) {
        if (i != 0 && j != 0 && abs(i) != abs(j)) {
          Position p{cur.x + i, cur.y + j, cur.dist + 1};
          if (validStep(n, p)) 
            pos.push(std::move(p));
        }
      }
    }
  }

  return -1;
}

int main() {

  int n = 3;
  Position start{0,0};
  Position end{1,0};
  std::cout << minSteps(n, start, end) << std::endl;

  return 0;
}
