#include "MazeBallMain.h"
#include "Leap.h"

// Declare our game instance
MazeBallMain game;

MazeBallMain::MazeBallMain()
    : _scene(NULL)
{
}

void MazeBallMain::initialize()
{
    // Load game scene from file
    Bundle* bundle = Bundle::create("res/box.gpb");
    _scene = bundle->loadScene();
    SAFE_RELEASE(bundle);

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio((float)getWidth() / (float)getHeight());
    
    // Get light node
    Node* lightNode = _scene->findNode("directionalLight");
    Light* light = lightNode->getLight();

    // Initialize box model
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->setMaterial("res/box.material");
    boxMaterial->getParameter("u_ambientColor")->setValue(_scene->getAmbientColor());
    boxMaterial->getParameter("u_lightColor")->setValue(light->getColor());
    boxMaterial->getParameter("u_lightDirection")->setValue(lightNode->getForwardVectorView());
}

void MazeBallMain::finalize()
{
    SAFE_RELEASE(_scene);
}

void MazeBallMain::update(float elapsedTime)
{
  leap.update();
    // Rotate model
  _scene->findNode("box")->translate(leap.translationX() * 0.1f, leap.translationY() * 0.1f, leap.translationZ() * 0.1f);
  _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void MazeBallMain::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &MazeBallMain::drawScene);
}

bool MazeBallMain::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel(); 
    if (model)
    {
        model->draw();
    }
    return true;
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
