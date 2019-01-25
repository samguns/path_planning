#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

/* Define a Map class
   Inside the map class, define the mapWidth, mapHeight and grid as a 2D vector
*/
class Map {
 public:
  const static int mapWidth = 6;
  const static int mapHeight = 5;
  vector<vector<int>> grid = {
      {0, 1, 0, 0, 0, 0},
      { 0, 1, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0 },
      { 0, 0, 0, 1, 1, 0 }
  };
};

/* Define a Planner class
   Inside the Planner class, define the start, goal, cost, movements, and movements_arrows
   Note: The goal should be defined it terms of the mapWidth and mapHeight
*/
class Planner : Map {
 public:
  int start[2] = {0, 0};
  int goal[2] = {mapHeight-1, mapWidth-1};
  int cost = 1;
  vector<vector<int>> movements = {
      {-1, 0},
      {0, -1},
      {1, 0},
      {0, 1}
  };
  vector<char> movements_arrows = {'^', '<', 'v', '>'};
};

/* Define a print2DVector function which will print 2D vectors of any data type
   Example

   Input:
   vector<vector<int> > a{{ 1, 0 },{ 0, 1 }};
   print2DVector(a);
   vector<vector<string> > b{{ "a", "b" },{ "c", "d" }};
   print2DVector(b);

   Output:
   1 0
   0 1
   a b
   c d
   Hint: You need to use templates
*/
template <typename T>
void print2DVector(vector<vector<T>> input) {
  for (const auto &row : input) {
    for (const T &val : row) {
      cout << val << " ";
    }
    cout << endl;
  }
}

/*#### Code the search function which will generate the expansion list ####*/
// You are only required to print the final triplet values
void search(Map map, Planner planner)
{
  // Create a closed 2 array filled with 0s and first element 1
  vector<vector<int> > closed(map.mapHeight, vector<int>(map.mapWidth));
  closed[planner.start[0]][planner.start[1]] = 1;

  vector<vector<int>> expand(map.mapHeight, vector<int>(map.mapWidth, -1));

  // Defined the triplet values
  int x = planner.start[0];
  int y = planner.start[1];
  int g = 0;

  // Store the expansions
  vector<vector<int> > open;
  open.push_back({ g, x, y });

  // Flags
  bool found = false;
  bool resign = false;
  int count = 0;

  int x2;
  int y2;

  // While I am still searching for the goal and the problem is solvable
  while (!found && !resign) {
    // Resign if no values in the open list and you can't expand anymore
    if (open.size() == 0) {
      resign = true;
      cout << "Failed to reach a goal" << endl;
    }
      // Keep expanding
    else {
      // Remove triplets from the open list
      sort(open.begin(), open.end());
      reverse(open.begin(), open.end());
      vector<int> next;
      // Stored the poped value into next
      next = open.back();
      open.pop_back();

      x = next[1];
      y = next[2];
      g = next[0];

      expand[x][y] = count;
      count++;

      // Check if we reached the goal:
      if (x == planner.goal[0] && y == planner.goal[1]) {
        found = true;
        cout << "[" << g << ", " << x << ", " << y << "]" << endl;
      }

        //else expand new elements
      else {
        for (int i = 0; i < planner.movements.size(); i++) {
          x2 = x + planner.movements[i][0];
          y2 = y + planner.movements[i][1];
          if (x2 >= 0 && x2 < map.grid.size() && y2 >= 0 && y2 < map.grid[0].size()) {
            if (closed[x2][y2] == 0 and map.grid[x2][y2] == 0) {
              int g2 = g + planner.cost;
              open.push_back({ g2, x2, y2 });
              closed[x2][y2] = 1;
            }
          }
        }
      }
    }
  }

  print2DVector(expand);
}

/*############ Don't modify the main function############*/
int main()
{
  // Instantiate map and planner objects
  Map map;
  Planner planner;

  // Print classes variables
  cout << "Map:" << endl;
  print2DVector(map.grid);
  cout << "Start: " << planner.start[0] << " , " << planner.start[1] << endl;
  cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << endl;
  cout << "Cost: " << planner.cost << endl;
  cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << endl;
  cout << "Delta:" << endl;
  print2DVector(planner.movements);

  search(map, planner);

  return 0;
}
