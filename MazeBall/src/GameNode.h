//
//  GameNode.h
//  MazeBall
//
//  Created by Jared Thomson on 2013-02-09.
//
//
#pragma once

#include "gameplay.h"
using namespace gameplay;

class GameNode: public Node
{
public:
  static GameNode* create(const char* id);
  virtual void addChild(Node* node);
  virtual void removeChild(Node* node);
  
  virtual void update(float delta);
  virtual void draw();
  virtual void reload();

protected:
  virtual void finalize();
  virtual void initialize();
  virtual bool setup();
  
  int mDrawDepth;

protected:
  GameNode() : Node("GameNode"), mDrawDepth(0)
  {
  }
  GameNode(const char* id) : Node(id), mDrawDepth(0)
  {
  }
  virtual ~GameNode()
  {
    finalize();
  }
};