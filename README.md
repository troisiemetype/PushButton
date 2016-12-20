#PushButton

##This library is intended to read buttons on arduino boards.

Its based on polling the pins as often as possible. Further développment may lead to interrupt based polling.

Simply import it in your Arduino Sketch, call `begin()` in the setup by passing the pin the button is plugged on, and call update on each loop. There are three ways you can use the button, that are expose above.

###PushButton
It provides some usefull functions for button reading.

`begin(int pin, byte pinMode = INPUT_PULLUP)` start a new button, on the given pin. It default to INPUT_PULLUP. Call it during setup. Possible values for pin mode are:

INPUT_PULLUP (default): sets the pin as input pullup, and invert behavior: pin is considered releasd when HIGH, and pressed when LOW.

PULLUP: sets the pin as input, and invert behavior, as above. It's up to you to set up an external pull up resistor.

PULLDOWN: sets the pin as input, and normal behavior: pin is considered released when LOW, and pressed when HIGH. It's up to you to set up an external pull down resistor.


`setDebouncedDelay()` is used to set the delay for debounce. If not called it will default to 5 ms.

`setLongDelay()` is used to set the delay for long presses. If not called it will default to 1s.

`setDoubleDelay()` sets the delay for double clicks. If not called it will default to 300ms.


`update()` is used for polling the button state. Call it on every loop.


`isPressed()` returns true if button is being pressed.

`isReleased()` ditto not being pressed.

`isLongPressed()` returns true is button is being pressed for longer than the delay specified with long delay.

`isLongReleased()` ditto not being pressed.



`justPressed()` returns true is the button is pressed and has not been read since it changed state. returns false once read, until the button is presed again.

`justReleased()` do the same for button released.


`justClicked()` returns true when a button has been released for longer than the double click delay, and the click is not a long click.

`justLongClicked()` returns true when a button has been released that was pressed for longer than longDelay.

`justDoubleClicked()` returns true if there was a double click.

These three methods are based on justReleased(), so they will return false is you call justReleased() before.


###PushButtonGroup

In addition, there is a PushButtonGroup class that just keeps a table of all the buttons sets, and can update all readings at once.

`addButton(&button)` adds the button to the group.

`removeButton(&button)` removes the button from the group.


`update()` to exactly the same than for on button, but for all the buttons listed in the group. It returns true if a button or more have changed state.


You may as well create several groups of buttons that have to be read together.


You are free to use this library for wathever project your working on.
