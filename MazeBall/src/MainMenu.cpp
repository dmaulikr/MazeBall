#include "MainMenu.h"
#include <iostream>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}

MainMenu::MainMenu(MainMenuController* controller) : GameNode("MainMenu")
{
  mController = controller;
}

bool MainMenu::setup()
{
  do 
  {
    mForm = Form::create("res/scenes/MainMenu/MainMenu.form");
    BREAK_IF(!mForm); // If the form doesn't load we're in for trouble.

    mTitleContainer = (Container*)mForm->getControl("TitleContainer");
    BREAK_IF(!mTitleContainer); // Our layout depends on this existing.


    mPlayButton = (Button*)mForm->getControl("PlayButton");
    BREAK_IF(!mPlayButton);
    
    mExitButton = (Button*)mForm->getControl("ExitButton");
    BREAK_IF(!mExitButton);
    
    return true;
  } while (false);
  return false;
}

MainMenu::~MainMenu(void)
{
  finalize();
}

MainMenu* MainMenu::create(MainMenuController* controller)
{
  MainMenu* mainMenu = NULL;
  do {
    mainMenu = new MainMenu(controller);
    BREAK_IF(!mainMenu->mController); // ensure we have a controller, there will be no other opportunity to attach one.
    BREAK_IF(!mainMenu); // Out of memory
    BREAK_IF(!mainMenu->setup()); // Our layout depends on this existing.
    mainMenu->initialize(); // Woo hoo, we made it. Go layout.
    return mainMenu;
  } while (false);
  cerr << " Could not create main menu.\n";
  if(mainMenu)
  {
    mainMenu->release();
  }
  return NULL;
}

void MainMenu::update(float delta)
{
  mForm->update(delta);
}

void MainMenu::draw()
{
  mForm->draw();
}

void MainMenu::controlEvent(Control* control, EventType evt)
{
  if(control == mPlayButton)
  {
    mController->MainMenuPlay();
  }
  else if(control == mExitButton)
  {
    mController->MainMenuExit();
  }
}

void MainMenu::initialize()
{
  mForm->setPosition(
    (float)(mForm->getWidth() - mTitleContainer->getWidth()) / 2.0f,
    (float)(mForm->getHeight() - mTitleContainer->getHeight()) / 2.0f);
  
  mPlayButton->addListener(this, Control::Listener::RELEASE);
  mExitButton->addListener(this, Control::Listener::RELEASE);
}

void MainMenu::finalize()
{
  mForm->release();
}
