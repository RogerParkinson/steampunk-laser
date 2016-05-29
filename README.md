# steampunk-laser
Plays a melody on ATTiny85 using tone() PWM pin 4

This code was loaded into an ATTiny85 that was embedded into a toy pistol with a laser pointer in the tip. When the trigger is pulled the tone sounds and the laser is turned on. There are a couple of blinking LEDs as well.

The finished laser looks like this:

<img src="Finished.jpg" alt="Finished" style="width: 200px;"/>

The handle was designed in blender and 3D printed with a spacein it to hold a LIPO battery.
This is the bare handle:

<img src="Laser1.jpg" alt="Finished" style="width: 200px;"/>

And this is the handle after painting and covering with fake mother of pearl.

<img src="Laser2.jpg" alt="Finished" style="width: 200px;"/>

We adapted the idea to make a bird scarer with glowing eyes. Some minor changes to the circuit and the code and it wakes up every 15 minutes to scare swallows that were nesting on the side of a house. The noise was adjusted to sound like a growling animal. THis was powered by 2xAA batteries.
This was, in fact, a total failure. The swallows were initially bothers but in 3 weeks they had built a nest on top of it. The batteries were still going well, attesting to the usefulness of the ATTiny85's sleep function.

<img src="FakeRat.jpg" alt="Finished" style="width: 200px;"/>

The circuit for this is shown here:

<img src="FakeRatCircuit.jpg" alt="Finished" style="width: 200px;"/>








