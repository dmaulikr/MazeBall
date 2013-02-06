#include "LeapOverlay.h"
#include "LeapManager.h"
#include <iostream>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}

LeapOverlay::LeapOverlay()
{
  do 
  {
    BREAK_IF(!setup());
  } while (false);
  cerr << "Could not create leap overlay.\n";
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
}

void LeapOverlay::draw()
{
  LeapManager& leap = *LeapManager::instance();
  Vector2 screen; // TODO: get properly
  screen.x = 1280.0f;
  screen.y = 720.0f;
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

  Leap::Frame frame = leap.frame(0);

  if(frame.fingers().count())
  {
    mFingerBatch->start();
  }
  
  for(int i = 0; i < frame.fingers().count(); i++)
  {
    Leap::Finger finger = frame.fingers()[i];
    
    mFingerBatch->draw(
      (screen.x * 0.5f) + finger.tipPosition().x*2.5f, 
      screen.y - finger.tipPosition().y*2.5f, 
      (ub-ua)*tex.x * (finger.length() / 75.0f), 
      (vb-va)*tex.y * (finger.length() / 75.0f), 
      ua, 
      1.0f-va, 
      ub, 
      1.0f-vb, 
      Vector4(0, 0, 1, 0.8f));
  }

  if(frame.fingers().count())
  {
    mFingerBatch->finish();
  }

  mForm->draw();
}

void LeapOverlay::reload()
{
  finalize();
  if(setup()) 
  {
    initialize();
  }
  else
  {
    cerr << "Could not reload LeapOverlay.\n";
  }
}

void LeapOverlay::initialize()
{

}

void LeapOverlay::finalize()
{
  SAFE_RELEASE(mForm);
}