#ifndef TEMPLATEGAME_H_
#define TEMPLATEGAME_H_

#include "gameplay.h"
#include "LeapManager.h"

using namespace gameplay;

class MazeBallMain: public Game
{
public:
  MazeBallMain();
	void keyEvent(Keyboard::KeyEvent evt, int key);
  void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
protected:
  void initialize();
  void finalize();
  void update(float elapsedTime);
  void render(float elapsedTime);
private:
  bool drawScene(Node* node);
  Scene* _scene;

  Font* mTitleFont;

  LeapManager leap; // The one and only instance of the leap manager.
};

#endif
