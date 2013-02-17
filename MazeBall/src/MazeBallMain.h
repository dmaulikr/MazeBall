#ifndef TEMPLATEGAME_H_
#define TEMPLATEGAME_H_

#include "gameplay.h"
#include "LeapManager.h"
#include "MainMenu.h"
#include "LeapOverlay.h"
#include "GameNode.h"

using namespace gameplay;

class MazeBallMain: public Game, public MainMenuController
{
public:
  MazeBallMain();
	void keyEvent(Keyboard::KeyEvent evt, int key);
  void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
  void MainMenuExit();
  void MainMenuPlay();

protected:
  void initialize();
  void finalize();
  void update(float elapsedTime);
  void render(float elapsedTime);
private:
  bool drawScene(Node* node);
  Scene* _scene;
  GameNode* mRootNode;

  MainMenu*     mMainMenu;
  LeapOverlay*  mOverlay;
  LeapManager   leap; // The one and only instance of the leap manager.
};

#endif
