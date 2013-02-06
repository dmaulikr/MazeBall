#pragma once

#include "gameplay.h"
using namespace gameplay;

class LeapOverlay
{
public:
  LeapOverlay();
  ~LeapOverlay();

  void update(float delta);
  void draw();
  void reload();

private:
  bool setup();
  void initialize();
  void finalize();

  SpriteBatch*        mFingerBatch;
  Form*               mForm;
  Container*          mOverlayContainer;
};