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

  void solve()
  {
    visited = true;
    
    Directions directions[4];
    directions[0] = N;
    directions[1] = S;
    directions[2] = E;
    directions[3] = W;
    
    int swaps = 4;
    
    while(swaps > 1)
    {
      int k = rand()%4;
      --swaps;
      std::swap(directions[swaps], directions[k]);
    }
    
    for(int i = 0; i < 4; i++)
    {
      if(getNeighbor(directions[i]) && getNeighbor(directions[i])->visited == false)
      {
        breakDown(directions[i]);
        getNeighbor(directions[i])->solve();
      }
    }
    
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