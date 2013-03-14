#include "PlayView.h"
#include <iostream>
#include <Windows.h>
using namespace std;

#define BREAK_IF(condition) if(condition){break;}
#define DEG_TO_RAD(deg) ((deg) * 0.0174532925f)

PlayView::PlayView(): GameNode("PlayView")
{
  mScene = NULL;
  mWallNE = NULL;
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
  do 
  {
    // Each tile is 100x100x100
    const float cameraDistance = 1500.0f;
    
    Bundle* bundle = Bundle::create("res/MazeBits.gpb");
    BREAK_IF(!bundle);
    mScene = bundle->loadScene();
    BREAK_IF(!mScene);
    SAFE_RELEASE(bundle);

    mScene->getActiveCamera()->setAspectRatio((float)Game::getInstance()->getWidth() / (float)Game::getInstance()->getHeight());
    mScene->getActiveCamera()->getNode()->setRotation(Matrix::identity());
    mScene->getActiveCamera()->setFarPlane(cameraDistance * 2.0f);
    mScene->getActiveCamera()->getNode()->setTranslation(0, -900.0f, cameraDistance);

    mScene->getActiveCamera()->getNode()->rotateX(DEG_TO_RAD(30.0f));

    Node* node = mScene->findNode("north_east_simple");
#define WALL_MODEL_COUNT 4
    Model** models[WALL_MODEL_COUNT] = { 
      &mWallNE, 
      &mWallN, 
      &mWallE,
      &mFloor};

    const char* modelNames[WALL_MODEL_COUNT] = { 
      "north_east_simple", 
      "north_simple", 
      "east_simple",
      "blank_simple"};

    for(int i = 0; i < WALL_MODEL_COUNT; ++i)
    {
      Node* node = mScene->findNode(modelNames[i]);
      BREAK_IF(!node);
      *models[i] = node->getModel();
      BREAK_IF(!*models[i]);

      Material* boxMaterial = (*models[i])->setMaterial("res/box.material");
      BREAK_IF(!boxMaterial);
      boxMaterial->getParameter("u_ambientColor")->setValue(mScene->getAmbientColor());
      boxMaterial->getParameter("u_lightColor")->setValue(Vector3(1, 1, 1));
      boxMaterial->getParameter("u_lightDirection")->setValue(Vector3(0, 0, -1));

      node->setTranslation(Vector3::zero());
      node->setScale(Vector3::one());
      //node->rotateX(DEG_TO_RAD(90));
      node->rotateY(DEG_TO_RAD(-90));
    }

    return true;

  } while (false);
  return false;
}


void PlayView::initialize()
{
  size_t w = 10, h = 10;
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

  mMaze[0][0]->generate();
  Cell::reset(mMaze);
}

void PlayView::finalize()
{

}

void PlayView::draw()
{
  mScene->visit(this, &PlayView::drawScene);
}

void PlayView::update(float delta)
{
  //mCube->getNode()->rotate(Vector3(0,1,0), DEG_TO_RAD(delta)*0.5f);
  //mMaze[0][0]->solve(mMaze[mMaze.size()-1][mMaze[0].size()-1]);
}

bool PlayView::drawScene(Node* node)
{
  
  const float scale = 100.0f;
  
  float startx = scale*-(((float)mMaze.size()/2.0f));
  float starty = scale*-(((float)mMaze[0].size()/2.0f)-0.5f);

  
  Model* model = node ? node->getModel() : NULL;

  if(model == mWallNE)
  {
    for(int ix = 0; ix < (int)mMaze.size(); ++ix)
    {
      for(int iy = 0; iy < (int)mMaze[ix].size(); ++iy)
      {
        if(mMaze[ix][iy]->hasWall(Cell::N) && mMaze[ix][iy]->hasWall(Cell::E))
        {
          node->setTranslationX((startx)+((float)ix) * scale);
          node->setTranslationY((starty)+((float)iy) * scale);
          model->draw();
        }
      }
    }
  }
  else if(model == mWallN)
  {
    for(int ix = 0; ix < (int)mMaze.size(); ++ix)
    {
      for(int iy = 0; iy < (int)mMaze[ix].size(); ++iy)
      {
        if(mMaze[ix][iy]->hasWall(Cell::N) && !mMaze[ix][iy]->hasWall(Cell::E))
        {
          node->setTranslationX((startx)+((float)ix) * scale);
          node->setTranslationY((starty)+((float)iy) * scale);
          model->draw();
        }
      }
    }
  }
  else if(model == mWallE) 
  {
    for(int ix = 0; ix < (int)mMaze.size(); ++ix)
    {
      for(int iy = 0; iy < (int)mMaze[ix].size(); ++iy)
      {
        if(!mMaze[ix][iy]->hasWall(Cell::N) && mMaze[ix][iy]->hasWall(Cell::E))
        {
          node->setTranslationX((startx)+((float)ix) * scale);
          node->setTranslationY((starty)+((float)iy) * scale);
          model->draw();
        }
      }
    }
  }
  else if(model == mFloor)
  {
    for(int ix = 0; ix < (int)mMaze.size(); ++ix)
    {
      for(int iy = 0; iy < (int)mMaze[ix].size(); ++iy)
      {
        if(!mMaze[ix][iy]->hasWall(Cell::N) && !mMaze[ix][iy]->hasWall(Cell::E))
        {
          node->setTranslationX((startx)+((float)ix) * scale);
          node->setTranslationY((starty)+((float)iy) * scale);
          model->draw();
        }
      }
    }
  }
  

  return true;
}
