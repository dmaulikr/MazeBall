//
//  LeapManager.h
//  MazeBall
//
//  Created by Jared Thomson on 2013-01-29.
//
//

#ifndef __MazeBall__LeapManager__
#define __MazeBall__LeapManager__


#ifdef _WIN32
#include "../../Leap_SDK_win/include/Leap.h"
#else
#include "Leap.h"
#endif

class LeapManager : public Leap::Listener
{
public:
  LeapManager()
  {
    if(stackInstance)
    {
      std::cerr << "The leap manager was created more than once. This is wrong.\n";
      exit(1349); // leap, get it?
      
    }
    stackInstance = this;
    mController.addListener(*this);
    //memset(frameIDs, 0, sizeof(frameIDs)*sizeof(int));
  }
  
  ~LeapManager();
  
  static LeapManager* instance()
  {
    return stackInstance;
  }
  
  const Leap::Frame frame(int history = 0) const;

  Leap::Vector translation() const;
  float translationX() const;
  float translationY() const;
  float translationZ() const;
  
  void update();

  
private:
  static LeapManager* stackInstance;
  
  /// Overloaded from Leap::Listener
  void onInit(const Leap::Controller&);
  void onConnect(const Leap::Controller&);
  void onDisconnect(const Leap::Controller&);
  void onExit(const Leap::Controller&);
  void onFrame(const Leap::Controller&);
  
  int frameIDs[10];
  Leap::Controller mController;
  
};

#endif /* defined(__MazeBall__LeapManager__) */
