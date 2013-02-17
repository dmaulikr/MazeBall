#include "MazeBallMain.h"
#include "PlayView.h"

// Declare our game instance
MazeBallMain game;

MazeBallMain::MazeBallMain()
  : _scene(NULL), 
  mMainMenu(NULL),
  mOverlay(NULL)
{

}

void MazeBallMain::initialize()
{
  mMainMenu = MainMenu::create(this);
  mOverlay = LeapOverlay::create();
  mRootNode = GameNode::create("RootNode");
  mRootNode->addChild(mOverlay);
  mRootNode->addChild(mMainMenu);

}

void MazeBallMain::finalize()
{
  SAFE_RELEASE(mRootNode);
}

void MazeBallMain::update(float elapsedTime)
{
  leap.update();

  mRootNode->update(elapsedTime);

  if(mOverlay)
  {
    mOverlay->update(elapsedTime);
  }
}

void MazeBallMain::render(float elapsedTime)
{
  // Clear the color and depth buffers
  clear(CLEAR_COLOR_DEPTH, Vector4(100.0f/255.0f, 149.0f/255.0f, 237.0f/255.0f, 1), 1.0f, 0);
  mRootNode->draw();
}

void MazeBallMain::keyEvent(Keyboard::KeyEvent evt, int key)
{
  if (evt == Keyboard::KEY_PRESS)
  {
    switch (key)
    {
    case Keyboard::KEY_ESCAPE:
      exit();
      break;
    }
  }

  if(evt == Keyboard::KEY_RELEASE)
  {
    switch(key)
    {
    case Keyboard::KEY_F5:
      mRootNode->reload();
      break;
    }

  }
}

void MazeBallMain::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
  switch (evt)
  {
  case Touch::TOUCH_PRESS:
    break;
  case Touch::TOUCH_RELEASE:
    break;
  case Touch::TOUCH_MOVE:
    break;
  };
}

void MazeBallMain::MainMenuExit()
{
  exit();
}

void MazeBallMain::MainMenuPlay()
{
  if(mMainMenu) // Shouldn't be a problem, but we'll check just in case.
  {
    mRootNode->removeChild(mMainMenu);
    mMainMenu = NULL;
  }
  PlayView* playView = PlayView::create();
  if(playView)
  {
    mRootNode->addChild(playView);
  }
}
