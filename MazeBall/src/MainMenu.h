#pragma once

#include "gameplay.h"
using namespace gameplay;

class MainMenuController
{
public:
  virtual void MainMenuExit() = 0;
  virtual void MainMenuPlay() = 0;
};

class MainMenu
{
public:
  MainMenu(MainMenuController* controller);
  ~MainMenu(void);

  void update(float delta);
  void draw();
  void reload();

private:
  bool setup();
  void initialize();
  void finalize();

  MainMenuController* mController;
  Form*               mForm;
  Container*          mTitleContainer;
};