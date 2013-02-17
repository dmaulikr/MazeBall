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
  Cell(int x, int y)
  {
    memset(this, 0, sizeof(Cell));
    this->x = x;
    this->y = y;
    northWall = true;
    eastWall = true;
    visited = false;
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
  
  enum Directions
  {
    N = 0,
    S,
    E,
    W
  };
  Cell* north;
  Cell* south;
  Cell* east;
  Cell* west;

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

  
  struct CellDirPair
  {
    Cell* c;
    Cell::Directions dir;
  };
  
  void solve()
  {
    visited = true;
    
    CellDirPair n[4];
    n[0].dir = Cell::N;
    n[0].c = north;
    n[1].dir = Cell::S;
    n[1].c = south;
    n[2].dir = Cell::E;
    n[2].c = east;
    n[3].dir = Cell::W;
    n[3].c = west;
    
    int swaps = 4;
    
    while(swaps > 1)
    {
      int k = rand()%4;
      --swaps;
      CellDirPair t;
      t.dir = n[swaps].dir;
      t.c = n[swaps].c;
      n[swaps].dir = n[k].dir;
      n[swaps].c = n[k].c;
      n[k].dir = t.dir;
      n[k].c = t.c;
    }
    
    for(int i = 0; i < 4; i++)
    {
      if(n[i].c && n[i].c->visited == false)
      {
        breakDown(n[i].dir);
        n[i].c->solve();
      }
    }
    
  }
  
  // Let's only be responsible for two walls, our neighbours can take responsibility for our other two.
  bool northWall;
  bool eastWall;
  int x;
  int y;
  bool visited;
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