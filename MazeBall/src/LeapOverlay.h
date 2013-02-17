#pragma once

#include "gameplay.h"
using namespace gameplay;
#include "GameNode.h"

class LeapOverlay : public GameNode
{
public:
  static LeapOverlay* create();
  virtual void update(float delta);
  virtual void draw();

protected:
  virtual bool setup();
  virtual void initialize();
  virtual void finalize();

  SpriteBatch*        mFingerBatch;
  Form*               mForm;
  Container*          mOverlayContainer;

  LeapOverlay();
  ~LeapOverlay();
};