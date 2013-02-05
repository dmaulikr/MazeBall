/******************************************************************************\
* Copyright (C) 2012-2013 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

using System;
using System.Threading;
using Leap;

class SampleListener : Listener
{
    private Object thisLock = new Object();

    private void SafeWriteLine(String line)
    {
        lock (thisLock)
        {
            Console.WriteLine(line);
        }
    }

    public override void OnInit(Controller controller)
    {
        SafeWriteLine("Initialized");
    }

    public override void OnConnect(Controller controller)
    {
        SafeWriteLine("Connected");
    }

    public override void OnDisconnect(Controller controller)
    {
        SafeWriteLine("Disconnected");
    }

    public override void OnExit(Controller controller)
    {
        SafeWriteLine("Exited");
    }

    public override void OnFrame(Controller controller)
    {
        // Get the most recent frame and report some basic information
        Frame frame = controller.Frame();
        SafeWriteLine("Frame id: " + frame.Id
                    + ", timestamp: " + frame.Timestamp
                    + ", hands: " + frame.Hands.Count
                    + ", fingers: " + frame.Fingers.Count
                    + ", tools: " + frame.Tools.Count);

        if (!frame.Hands.Empty)
        {
            // Get the first hand
            Hand hand = frame.Hands[0];

            // Check if the hand has any fingers
            FingerList fingers = hand.Fingers;
            if (!fingers.Empty)
            {
                // Calculate the hand's average finger tip position
                Vector avgPos = Vector.Zero;
                foreach (Finger finger in fingers)
                {
                    avgPos += finger.TipPosition;
                }
                avgPos /= fingers.Count;
                SafeWriteLine("Hand has " + fingers.Count
                            + " fingers, average finger tip position: " + avgPos);
            }

            // Get the hand's sphere radius and palm position
            SafeWriteLine("Hand sphere radius: " + hand.SphereRadius.ToString("n2")
                        + " mm, palm position: " + hand.PalmPosition);

            // Get the hand's normal vector and direction
            Vector normal = hand.PalmNormal;
            Vector direction = hand.Direction;

            // Calculate the hand's pitch, roll, and yaw angles
            SafeWriteLine("Hand pitch: " + direction.Pitch * 180.0f / (float)Math.PI  + " degrees, "
                        + "roll: " + normal.Roll * 180.0f / (float)Math.PI + " degrees, "
                        + "yaw: " + direction.Yaw * 180.0f / (float)Math.PI + " degrees\n");
        }
    }
}

class Sample
{
    public static void Main()
    {
        // Create a sample listener and controller
        SampleListener listener = new SampleListener();
        Controller controller = new Controller();

        // Have the sample listener receive events from the controller
        controller.AddListener(listener);

        // Keep this process running until Enter is pressed
        Console.WriteLine("Press Enter to quit...");
        Console.ReadLine();

        // Remove the sample listener when done
        controller.RemoveListener(listener);
        controller.Dispose();
    }
}
