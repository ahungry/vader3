# Flydigi Vader 3 Bluetooth driver for GNU/Linux

Adds support for the 4 back buttons/paddles, C/Z buttons, and
circle/home buttons, while connected in D-Input mode under a
Bluetooth connection.

# Toggling Flydigi Vader 3 Input Modes

Swap the slider on the back to the center position.

If the status light is white, you're in X-Input mode, just hold the
circle button (left-center under the joysticks) and the A button for
around 3 seconds - you'll see the device power off, then reboot with
the status light blue.

To revert to X-Input mode, repeat the process, but hold X instead of A.

X-Input mode does not support the custom buttons as native hardware
events, they will replay the bindings mapped in the Flydigi
SpaceStation app (which unfortunately can't do keyboard binds under
GNU/Linux, or multi-button key-presses).

# Force Feedback (FF)/ Rumble Support

Due to hardware limitations, there is none - this is unfortunately not
something I can change at a driver level.

You can use the 2.4ghz dongle on dongle mode + X-Input (dongle
default, and changed the same way as Bluetooth mode is) if you want
rumble support on GNU/Linux (the USB hid-generic driver handles it
correctly), but this means that you will miss out on the ability to
map native button presses using Qjoypad or AntiMicroX (I enjoy having
8 additional buttons myself).

# License

GPLv3 or later

# Copyright

Matthew Carter <m@ahungry.com>
