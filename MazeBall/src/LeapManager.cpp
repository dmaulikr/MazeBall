//
//  LeapManager.cpp
//  MazeBall
//
//  Created by Jared Thomson on 2013-01-29.
//
//

#include "LeapManager.h"

using namespace Leap;
using namespace std;

LeapManager* LeapManager::stackInstance = NULL;

LeapManager::~LeapManager()
{
  
}

const Frame LeapManager::frame(int history) const
{
  return mController.frame(history);
}

Leap::Vector LeapManager::translation() const
{
  return frame().translation(frame(1));
}

float LeapManager::translationX() const
{
  return translation().x;
}

float LeapManager::translationY() const
{
  return translation().y;
}

float LeapManager::translationZ() const
{
  return translation().z;
}

void LeapManager::update()
{
//  for(int i = 1; i < sizeof(frameIDs); ++i)
  //{
    //frameIDs[i] = frameIDs[i-1];
//  }
  //frameIDs[0] = frame(0).id();
}

void LeapManager::onInit(const Controller& controller)
{
  cout << "Leap: onInit\n";
}

void LeapManager::onConnect(const Controller& controller)
{
  cout << "Leap: onConnect\n";
}

void LeapManager::onDisconnect(const Controller& controller)
{
   cout << "Leap: onDisconnect\n";
}

void LeapManager::onExit(const Controller& controller)
{
   cout << "Leap: onExit\n"; 
}

void LeapManager::onFrame(const Controller& controller)
{

}