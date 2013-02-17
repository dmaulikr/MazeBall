//
//  GameNode.cpp
//  MazeBall
//
//  Created by Jared Thomson on 2013-02-09.
//
//

#include "GameNode.h"
#include <iostream.h>
using namespace std;


GameNode* GameNode::create(const char* id)
{
  GameNode* gameNode = new GameNode(id);
  
  if(gameNode->setup())
  {
    gameNode->initialize();
    return gameNode;
  }
  cerr << "GameNode(" << __LINE__ << "): Could note create node with id '" << id << "'\n";
  return NULL;
}

void GameNode::addChild(Node* child)
{
  Node::addChild(child);
//  GP_ASSERT(child);
//  
//  if (child->getParent() == this)
//  {
//    return;
//  }
//  
//  child->addRef();
//  
//  int childDepth = 0;
//
//  if(GameNode* g = reinterpret_cast<GameNode*>(child))
//  {
//    childDepth = g->mDrawDepth;
//  }
//  
//  // If the item belongs to another hierarchy, remove it first.
//  if (child->getParent())
//  {
//    child->getParent()->removeChild(child);
//  }
//  else if (child->getScene())
//  {
//    child->getScene()->removeNode(child);
//  }
//
//  Node* current = _firstChild;
//  Node* previous = NULL;
//  
//  while (current != NULL)
//  {
//    int nodeDepth = 0;
//    if(GameNode* g = reinterpret_cast<GameNode*>(current))
//    {
//      nodeDepth = g->mDrawDepth;
//    }
//    
//    if(childDepth >= nodeDepth)
//    {
//      break;
//    }
//    
//    previous = current;
//    current = current->getNextSibling();
//  }
//
//  if(!previous)
//  {
//    previous->setNextSibling(_firstChild);
//    _firstChild = previous;
//  }
//  else
//  {
//    previous->setNextSibling(child);
//    child->setNextSibling(current);
//  }
//  
//  child->setParent(this);
//  ++_childCount;
//  
//  if (_notifyHierarchyChanged)
//  {
//    hierarchyChanged();
//  }
}

void GameNode::removeChild(Node* node)
{
  Node::removeChild(node);
}

void GameNode::update(float delta)
{
  Node* child = _firstChild;
  while(child)
  {
    if(GameNode* g = reinterpret_cast<GameNode*>(child))
    {
      g->update(delta);
    }
    child = child->getNextSibling();
  }
}

void GameNode::draw()
{
  Node* child = _firstChild;
  while(child)
  {
    if(GameNode* g = reinterpret_cast<GameNode*>(child))
    {
      g->draw();
    }
    child = child->getNextSibling();
  }
}

void GameNode::reload()
{
  finalize();
  if(setup())
  {
    initialize();
  }
  Node* child = _firstChild;
  while(child)
  {
    if(GameNode* g = reinterpret_cast<GameNode*>(child))
    {
      g->reload();
    }
    child = child->getNextSibling();
  }
}

void GameNode::initialize()
{
}

void GameNode::finalize()
{
}

bool GameNode::setup()
{
  return true;
}