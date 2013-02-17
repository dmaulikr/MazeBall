//
//  PlayView.h
//  MazeBall
//
//  Created by Jared Thomson on 2013-02-16.
//
//
#pragma once

#include "GameNode.h"
#include "Gameplay.h"
using namespace gameplay;

struct Cell
{
  enum Directions
  {
    N, S, E, W
  };
  
  Cell(int x, int y)
  {
    this->x = x;
    this->y = y;
    northWall = true;
    eastWall = true;
    visited = false;
    north = south = east = west = NULL;
  }
  
  void link(std::vector< std::vector<Cell*> >& cells)
  {
    if(x > 0)
    {
      west = cells[x-1][y];
    }
    if(x < cells.size()-1)
    {
      east = cells[x+1][y];
    }
    if(y > 0)
    {
      south = cells[x][y-1];
    }
    if(y < cells.size()-1)
    {
      north = cells[x][y+1];
    }
  }

  bool hasWall(Directions dir)
  {
    if(dir == N)
      return northWall;
    if(dir == E)
      return eastWall;
    if(dir == S)
      return south ? south->northWall : true;
    if(dir == W)
      return west ? west->eastWall : true;
    return false;
  }
  
  void breakDown(Directions dir)
  {
    if(dir == N)
      northWall = false;
    else if(dir == E)
      eastWall = false;
    else if(dir == S && south)
      south->northWall = false;
    else if(dir == W && west)
      west->eastWall = false;
  }
  
  Cell* getNeighbor(Directions dir)
  {
    switch (dir) {
      case N: return north;
      case S: return south;
      case E: return east;
      case W: return west;
      default: return NULL;
    }
  }
  
  struct Compass // Used because arrays inside of std pairs suck.
  {
    Directions directions[4];
  };
  
  // Super unsafe. Oh well.
  void shuffleDirections(Compass &compass)
  {
    compass.directions[0] = N;
    compass.directions[1] = S;
    compass.directions[2] = E;
    compass.directions[3] = W;
    int swaps = 4;
    while(swaps > 1)
    {
      int k = rand()%4;
      --swaps;
      std::swap(compass.directions[swaps], compass.directions[k]);
    }
  }

  
  //
  // So here's how we're solving mazes.
  // Basically we start with a node and a shuffled set of directions adding them to a stack (to replace the recursive solution)
  // We take the first element on the stack and say that we've checked it so we don't come back. We then go through
  // all of it's neighbors and if they exist, and they haven't been visited yet then we knock down the wall between us.
  // Once the wall is knocked down we shuffle up some directions and add them (and the neighbor) to the stack.
  // If no neighbors were looked at we can just get rid of the current node.
  // Once there are no nodes left in the stack we return, the maze is now generated.
  //
  void solve()
  {
    std::stack< std::pair<Cell*, Compass> > stack;
    Compass directions;
    shuffleDirections(directions);
    stack.push(std::pair<Cell*, Compass>(this, directions)); // Let's volunteer to be the first node on the stack.
    do {
      std::pair<Cell*, Compass >& current = stack.top(); // peak
      current.first->visited = true;

      bool isDone = true; // If we don't have any valid non visited neighbours we can just pop this node and never check it again.
      for(int i = 0; i < 4; ++i)
      {
        
        if(current.first->getNeighbor(current.second.directions[i]) && !current.first->getNeighbor(current.second.directions[i])->visited)
        {
          isDone = false; // Don't pop out when we're done here.
          current.first->breakDown(current.second.directions[i]);
          shuffleDirections(directions);
          stack.push(std::pair<Cell*, Compass>(current.first->getNeighbor(current.second.directions[i]), directions));
          break;
        }
      }
      
      if(isDone)
      {
        stack.pop();
      }
    } while (stack.size() > 0);
  }
  
  bool northWall, eastWall;
  int x, y; // Used in linking neighbours.
  bool visited; // Used in DFS generation.
  Cell* north, *south, *east, *west; // Neighbours
};

class PlayView : public GameNode
{
public:
  static PlayView* create();
  virtual bool setup();
  virtual void initialize();
  virtual void finalize();
  
  virtual void draw();
  virtual void update(float delta);

protected:
  bool drawScene(Node* node);
  
  Scene* mScene;
  Model* mCube;
  Light* mLight;
  Node* mCamera;
  
  
  std::vector< std::vector<Cell*> > mMaze;
  
  PlayView();
  ~PlayView();
};