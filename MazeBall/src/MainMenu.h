#pragma once

#include "gameplay.h"
using namespace gameplay;
#include "GameNode.h"

class MainMenuController
{
public:
  virtual void MainMenuExit() = 0;
  virtual void MainMenuPlay() = 0;
};

class MainMenu: public Control::Listener, public GameNode
{
public:
  static MainMenu* create(MainMenuController* controller);
  virtual void update(float delta);
  virtual void draw();
  
  // Handle events coming back from the main form.
  void controlEvent(Control* control, EventType evt);
private:
  bool setup();
  void initialize();
  void finalize();

  MainMenuController* mController;
  Form*               mForm;
  Container*          mTitleContainer;
  Button*             mPlayButton;
  Button*             mExitButton;
  
  MainMenu(MainMenuController* controller);
protected:
  ~MainMenu(void);
};