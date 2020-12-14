/*
 * This Arduino library is for reading buttons
 * Copyright (C) 2016  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This library is for reading buttons.
 * Simply create a new instance of the library in your sketch.

 * This library can manage two types of buttons:
 * If a pin is to be associated with the button (most common case);
 * Call begin() and pass the number of the pin the button is attached to, and the type of button
 * (INPUT, OR INPUT_PULLUP).
 * Call update() as often has possible, then use the different methods provided to know switch state.
 *
 * If the button cannot read its own pin, e.g. if it's linked with a port expander:
 * Call begin() and pass the type of button (INPUT_PULLUP, PULLUP, or PULLDOWN).
 * Call update() as often as possible, and pass the button state as a boolean.
 */

/*
 * Once you have several buttons created, you may want to update all their readings at once:
 * Create one (or several) instances of PushButtonGroup, and add the button you've created to it.
 * Once done, you can call an update for each group of buttons.
 * The buttons attached to the group can be added or removed at any moment, as they are dynamicly attached.
 * Remove a button from a group doesn't suppress it, it will still be usable alone and/or in other groups.
 *
 * Nota: For now, PushButtonGroup can only manage buttons that handle their pin.
 * If buttons needs their state to be passed to update(), it won't work.
 */

 /* WARNING: the PushButtonGroup class uses dynamic memory allocation.
  * Compiler won't warn you about using too much memory size.
  * It's up to you to know that you don't overflow what can be used.
  * Each button set occupies 19 bytes of memory, and the ButtonGroup is 2 bytes per button, + 2.
  * When adding or removing a button to buttonGroup, you should have enough continguous memory to store a temp allocation of the table.
  */


#include "PushButton.h"

// Create an instance of a push button.
PushButton::PushButton(){

	_debounceDelay = 1;
	_longDelay = 1000;
	_doubleDelay = 100;

	_time = millis();
	_timeDouble = _time;

}

// Inialize a button without pin, for use with an external trigger ( a port expander for example)
void PushButton::begin(const uint8_t& mode){

	_pinMode = mode;

	if(_pinMode == INPUT_PULLUP || _pinMode == PULLUP){
		_states.invert = true;

		_states.state = true;
		_states.pState = true;
		_states.now = true;
		_states.prev = true;

	} else {
		_states.invert = false;

		_states.state = false;
		_states.pState = false;
		_states.now = false;
		_states.prev = false;

	}

	_states.longState = false;
	_states.longClick = false;

	_states.isJustPressed = true;
	_states.isJustReleased = true;

}

// Initialize a button with the given pin, and sets up initial state
void PushButton::begin(const uint8_t& pin, const uint8_t& mode){

	_pin = pin;
	_pinMode = mode;

	if(_pinMode == INPUT_PULLUP){
		pinMode(_pin, INPUT_PULLUP);
	} else {
		pinMode(_pin, INPUT);
	}

	begin(mode);
}

// Set debounce delay
void PushButton::setDebounceDelay(uint16_t delay){
	_debounceDelay = delay;
}

// Set delay for long clicks and releases.
void PushButton::setLongDelay(uint16_t delay){
	_longDelay = delay;
}

// Set delay for double clicks.
void PushButton::setDoubleDelay(uint16_t delay){
	_doubleDelay = delay;
}


// Function that update reading when the button handles its own pin.
bool PushButton::update(){
	return update(digitalRead(_pin));
}

// Function that update reading. To be called as often as possible, typically at the beginning of each loop.
bool PushButton::update(bool state){

	//Store the previous instant state, read the new one.
	_states.prev = _states.now;
	_states.now = state;

	uint32_t instantTime = millis();

	//If different, set timer to zero
	if(_states.now != _states.prev){
		_time = instantTime;
		return false;
	}

	//If instant state is different than button state, and time elapsed greater thant debounce time, change state.
	if((_states.state != _states.now) && ((instantTime - _time) > _debounceDelay)){
		_states.pState = _states.state;
		_states.state = _states.now;
		_states.longState = false;
		_states.isJustPressed = false;
		_states.isJustReleased = false;

		if(isPressed()){
			_states.longClick = false;
		}

		if(isReleased()){
			if((instantTime - _timeDouble) < _doubleDelay){
				_states.doubleClick = true;
			} else {
				_states.doubleClick = false;
			}
			_timeDouble = instantTime;
		}
		return true;
	}

	//If time elapsed since changed is greater than delay for long presses, set longState.
	if(!_states.longState && ((instantTime - _time) > _longDelay)){
		_states.longState = true;
		if(isPressed()){
			_states.longClick = true;
		}
		return true;
	}

	return false;
}

// Return true if button is pressed.
bool PushButton::isPressed(){
	return _states.state ^ _states.invert;
}

// Return true if button is released.
bool PushButton::isReleased(){
	return !_states.state ^ _states.invert;
}

// Return true when the button is pressed for a long time.
bool PushButton::isLongPressed(){
	return (_states.state ^ _states.invert) && _states.longState;
}

// Return true if button is released for a long time
bool PushButton::isLongReleased(){
	return (!_states.state ^ _states.invert) && _states.longState;
}

// Return true when button is newly pressed.
// Returns true only once, then it needs to be released to return true again.
bool PushButton::justPressed(){
	if(isPressed() && !_states.isJustPressed){
		_states.isJustPressed = true;
		return true;
	} else {
		return false;
	}
}

// Return true when button is newly released.
// Returns true only once, then it needs to be pressed to return true again.
// click methods are based on it, so don't use it if you want to call justClicked(), justLongClicked() or 
// justDoubleClick().
bool PushButton::justReleased(){
	if(isReleased() && !_states.isJustReleased){
		_states.isJustReleased = true;
		return true;
	} else {
		return false;
	}
}

// Return true if a click has happened, that is not a long click, or the first of a double click.
// This function will return false if a click has happenned for a time lesser than doubleDelay.
// If you need to immediately know a clicked has been made, use justReleased() instead.
bool PushButton::justClicked(){
	if(((millis() - _timeDouble) < _doubleDelay) || (_states.longClick || _states.doubleClick)) return false;

	return justReleased();
}

// Return true if a long click has happened.
bool PushButton::justLongClicked(){
	if(!_states.longClick) return false;

	if(justReleased()){
		_states.longClick = false;
		return true;
	} else {
		return false;
	}
}

// Return true if a double click has happened.
bool PushButton::justDoubleClicked(){
	if(!_states.doubleClick) return false;

	if(justReleased()){
		_states.doubleClick = false;
		return true;
	} else {
		return false;
	}
}


// Create a button group.
PushButtonGroup::PushButtonGroup(){
	buttons = NULL;
	buttonsSize = 0;
}

// Delete a button group.
PushButtonGroup::~PushButtonGroup(){
	free(buttons);
}

// Add a new button to the group. Use realloc to dynamicly change the size of the pointers table
void PushButtonGroup::add(PushButton* button){
	buttonsSize++;
	PushButton **tmp = (PushButton**)realloc(buttons, sizeof(PushButton*) * buttonsSize);
	if(tmp == NULL){
		return;
	}
	buttons = tmp;
	buttons[buttonsSize - 1] = button;
}

// Remove a button from the group.
// To be modified : guard for the case when remove is called while no buttons was privously added.
void PushButtonGroup::remove(PushButton* button){
	buttonsSize--;
	if(buttonsSize == 0){
		delete(buttons);
		return;
	}

	PushButton **tmp = (PushButton**)realloc(buttons, sizeof(PushButton*) * buttonsSize);
	if(tmp == NULL){
		return;
	}
	
	uint8_t top = buttonsSize + 1;
	uint8_t count = 0;

	for(uint8_t i = 0; i < top; i++){
		if(buttons[i] == button){continue;}
		tmp[count] = buttons[i];
		count++;
	}

	buttons = tmp;
}

//Update the readings of all buttons.
bool PushButtonGroup::update(){
	bool state = false;
	for(uint8_t i = 0; i < buttonsSize; i++){
		if(buttons[i]->update()){
			state = true;
/*
			Serial.print("button ");
			Serial.print(i);
			Serial.print(": ");
			Serial.print(buttons[i]->isPressed());
			Serial.println();
			Serial.println();
*/
		}
	}
	return state;
}