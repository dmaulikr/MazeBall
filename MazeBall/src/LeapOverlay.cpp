#include "LeapOverlay.h"
#include "LeapManager.h"
#include <iostream>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}

LeapOverlay* LeapOverlay::create()
{
  LeapOverlay* overlay = new LeapOverlay();
  do
  {
    BREAK_IF(!overlay->setup());
    overlay->initialize();
    return overlay;
  } while (false);
  SAFE_DELETE(overlay);
  return NULL;
}

LeapOverlay::LeapOverlay() : GameNode("LeapOverlay")
{
}

bool LeapOverlay::setup()
{
  do 
  {
    mForm = Form::create("res/scenes/Common/LeapOverlay.form");
    BREAK_IF(!mForm); // If the form doesn't load we're in for trouble.

    mFingerBatch = SpriteBatch::create("res/themes/editor.png", NULL, 10);
    BREAK_IF(!mFingerBatch);
    return true;
  } while (false);
  return false;
}

LeapOverlay::~LeapOverlay()
{

}

void LeapOverlay::update(float delta)
{
  mForm->update(delta);
  GameNode::update(delta);
}

void LeapOverlay::draw()
{
  LeapManager& leap = *LeapManager::instance();
  Vector2 screen;
  screen.x = Game::getInstance()->getWidth();
  screen.y = Game::getInstance()->getHeight();
  Vector2 tex;
  tex.x = tex.y = 256.0f;

  float ua, ub, va, vb;

  ua = 127.0f;
  va = 1.0f;
  ub = 46.0f+ua;
  vb = 46.0f+va;

  ua /= tex.x;
  va /= tex.y;
  ub /= tex.x;
  vb /= tex.y;
  
  float sensativity = 1.5f;

  Leap::Frame frame = leap.frame(0);

  if(frame.fingers().count() || frame.tools().count())
  {
    mFingerBatch->start();
  
  
  Vector4 handColors[] =
  {
    Vector4(0, 1, 0, 0.8f),
    Vector4(0, 0, 1, 0.8f),
    Vector4(1, 0, 0, 0.8f),
    Vector4(1, 0, 1, 0.8f),
    Vector4(0, 1, 1, 0.8f),
    Vector4(1, 1, 0, 0.8f),
  };

  for(int i = 0; i < frame.hands().count(); ++i)
  {
    for(int j = 0; j < frame.hands()[i].fingers().count(); ++j)
    {
      Leap::Finger finger = frame.hands()[i].fingers()[j];
      mFingerBatch->draw(
                         (screen.x * 0.5f) + finger.tipPosition().x*sensativity,
                         screen.y - finger.tipPosition().y*sensativity,
                         (ub-ua)*tex.x * (finger.length() / 75.0f),
                         (vb-va)*tex.y * (finger.length() / 75.0f),
                         ua,
                         1.0f-va, 
                         ub, 
                         1.0f-vb, 
                         handColors[i]);
    }
  }
  
  
  ua = 78.0f;
  va = 1.0f;
  ub = 46.0f+ua;
  vb = 46.0f+va;
  
  ua /= tex.x;
  va /= tex.y;
  ub /= tex.x;
  vb /= tex.y;
  
  for(int i = 0; i < frame.tools().count(); i++)
  {
    Leap::Tool tool = frame.tools()[i];
    
    mFingerBatch->draw(
      (screen.x * 0.5f) + tool.tipPosition().x*sensativity,
      screen.y - tool.tipPosition().y*sensativity,
      (ub-ua)*tex.x * (tool.length() / 75.0f), 
      (vb-va)*tex.y * (tool.length() / 75.0f), 
      ua, 
      1.0f-va, 
      ub, 
      1.0f-vb,
      Vector4(0.8, 0.2, 0.9, 0.8f));
  }

    mFingerBatch->finish();
  }

  mForm->draw();
  GameNode::draw();
}


void LeapOverlay::initialize()
{

}

void LeapOverlay::finalize()
{
  SAFE_RELEASE(mForm);
}