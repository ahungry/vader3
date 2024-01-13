# Flydigi Vader 3 Bluetooth driver for GNU/Linux

Adds support for the 4 back buttons/paddles, C/Z buttons, and
circle/home buttons, while connected in D-Input mode under a
Bluetooth connection.

# Installation (you have to compile it)

```
make -C hid-vader3
sudo ./uninstall.sh
sudo ./install.sh
sudo modprobe hid-vader3
```

You can confirm it loaded/bound to your controller by checking dmesg
(you should see a similar output):

```
[45188.559255] loaded hid-vader3 0.0.1-1-g6c50ff3-dirty
[45188.559400] input: Flydigi VADER3P as /devices/virtual/misc/uhid/0005:D7D7:0041.0023/input/input526
[45188.559483] vader3 0005:D7D7:0041.0023: input,hidraw0: BLUETOOTH HID v1.01 Gamepad [Flydigi VADER3P] on 14:85:7f:e2:41:03
```

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

# Copyright

Matthew Carter <m@ahungry.com>

# License

GPLv3 or later (see: LICENSE)

## Disclaimer and Limitation of Liability

This is the standard GPLv3 verbiage (see LICENSE), but bears
repeating - I haven't had any issues with this on my machine or
controller, but this is the first driver I've written - peer review by
experts, and feedback from users is always appreciated.

```
  15. Disclaimer of Warranty.

  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

  16. Limitation of Liability.

  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.

```
