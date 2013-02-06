#include "MainMenu.h"
#include <iostream>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}

MainMenu::MainMenu(MainMenuController* controller)
{
  do 
  {
    BREAK_IF(!controller); // ensure we have a controller, there will be no other opportunity to attach one.
    BREAK_IF(!setup()); // Our layout depends on this existing.
    initialize(); // Woo hoo, we made it. Go layout.
  } while (false);
  cerr << "Could not create main menu.\n";
}

bool MainMenu::setup()
{
  do 
  {
    mForm = Form::create("res/scenes/MainMenu/MainMenu.form");
    BREAK_IF(!mForm); // If the form doesn't load we're in for trouble.

    mTitleContainer = (Container*)mForm->getControl("TitleContainer");
    BREAK_IF(!mTitleContainer); // Our layout depends on this existing.

    return true;
  } while (false);
  return false;
}

MainMenu::~MainMenu(void)
{
  finalize();
}

void MainMenu::update(float delta)
{
  mForm->update(delta);
}

void MainMenu::draw()
{
  mForm->draw();
}

void MainMenu::reload()
{
  finalize();
  if(setup()) 
  {
    initialize();
  }
  else
  {
    cerr << "Could not reload MainMenu.\n";
  }
}

void MainMenu::initialize()
{
  mForm->setPosition(
    (float)(mForm->getWidth() - mTitleContainer->getWidth()) / 2.0f,
    (float)(mForm->getHeight() - mTitleContainer->getHeight()) / 2.0f); 
}

void MainMenu::finalize()
{
  mForm->release();
}
