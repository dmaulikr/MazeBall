#include "PlayView.h"
#include <iostream>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}

PlayView::PlayView(): GameNode("PlayView")
{
  mScene = NULL;
  mCube = NULL;
  mLight = NULL;
  mCamera = NULL;
}

PlayView::~PlayView()
{
}

PlayView* PlayView::create()
{
  PlayView* view = new PlayView();
  do {
    BREAK_IF(!view);
    BREAK_IF(!view->setup());
    view->initialize();
    return view;
  } while (false);
  SAFE_DELETE(view);
  return NULL;
}

bool PlayView::setup()
{
  do {
    Bundle* bundle = Bundle::create("res/box.gpb");
    BREAK_IF(!bundle);
    mScene = bundle->loadScene();
    BREAK_IF(!bundle);
    SAFE_RELEASE(bundle);
    
    mScene->getActiveCamera()->setAspectRatio((float)Game::getInstance()->getWidth() / (float)Game::getInstance()->getHeight());
    mScene->getActiveCamera()->getNode()->setRotation(Matrix::identity());
    mScene->getActiveCamera()->setFarPlane(250);

    mScene->getActiveCamera()->getNode()->setTranslation(0, 0, 200);
    
    Node* lightNode = mScene->findNode("directionalLight");
    BREAK_IF(!lightNode);
    mLight = lightNode->getLight();
    BREAK_IF(!mLight);

    Node* boxNode = mScene->findNode("box");
    BREAK_IF(!boxNode);
    mCube = boxNode->getModel();
    BREAK_IF(!mCube);
    
    Material* boxMaterial = mCube->setMaterial("res/box.material");
    BREAK_IF(!boxMaterial);
    boxMaterial->getParameter("u_ambientColor")->setValue(mScene->getAmbientColor());
    boxMaterial->getParameter("u_lightColor")->setValue(mLight->getColor());
    boxMaterial->getParameter("u_lightDirection")->setValue(lightNode->getForwardVectorView());
    
    return true;

  } while (false);
  return false;
}


void PlayView::initialize()
{
  int w = 150, h = 150;
  for(size_t i = 0; i < w; ++i)
  {
    mMaze.push_back( std::vector<Cell*>() );
    for(size_t j = 0; j < h; ++j)
    {
      mMaze[i].push_back(new Cell(i, j));
    }
  }
  
  for(size_t i = 0; i < mMaze.size(); ++i)
  {
    for(size_t j = 0; j < mMaze[i].size(); ++j)
    {
      mMaze[i][j]->link(mMaze);
    }
  }
  
  mMaze[0][0]->solve();
  
}

void PlayView::finalize()
{
  
}

void PlayView::draw()
{
  float startx = -((float)mMaze.size() / 2.0f) + 0.5f;
  float starty = -((float)mMaze[0].size() / 2.0f) + 0.5f;
  mCube->getNode()->setScale(0.8f);
  float thickness = 0.2f;
  for(int x = 0; x < mMaze.size(); ++x)
  {
    mCube->getNode()->setScaleX(1.0f);
    mCube->getNode()->setScaleY(thickness);
    mCube->getNode()->setTranslationX(startx + (float)x);
    mCube->getNode()->setTranslationY(starty - 0.5f);
    mScene->visit(this, &PlayView::drawScene);
    
    for(int y = 0; y < mMaze[x].size(); ++y)
    {
      if(x == 0)
      {
        mCube->getNode()->setScaleX(thickness);
        mCube->getNode()->setScaleY(1.0f);
        mCube->getNode()->setTranslationX(startx - 0.5f);
        mCube->getNode()->setTranslationY(starty + (float)y);
        mScene->visit(this, &PlayView::drawScene);
      }
      if(mMaze[x][y]->hasWall(Cell::N))
      {
        mCube->getNode()->setScaleX(1.0f);
        mCube->getNode()->setScaleY(thickness);
        mCube->getNode()->setTranslationX(startx + (float)x);
        mCube->getNode()->setTranslationY(starty + (float)y + 0.5f);
        mScene->visit(this, &PlayView::drawScene);
      }
      if(mMaze[x][y]->hasWall(Cell::E))
      {
        mCube->getNode()->setScaleX(thickness);
        mCube->getNode()->setScaleY(1.0f);
        mCube->getNode()->setTranslationX(startx + (float)x + 0.5f);
        mCube->getNode()->setTranslationY(starty + (float)y);
        mScene->visit(this, &PlayView::drawScene);
      }
    }
  }

}

void PlayView::update(float delta)
{
}

bool PlayView::drawScene(Node* node)
{
  Model* model = node->getModel();
  if (model)
  {
    model->draw();
  }
  return true;
}
