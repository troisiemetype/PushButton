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

#ifndef BOUTON_H
#define BOUTON_H

#include <Arduino.h>

#define PULLUP 			0x3
#define PULLDOWN        0x4

class PushButton{

public:

	PushButton();

	void begin(byte mode);
	void begin(int pin, byte mode);

	void setDebounceDelay(int delay);
	void setLongDelay(int delay);
	void setDoubleDelay(int delay);

	bool update(bool state);
	bool update();
	bool isPressed();
	bool isReleased();
	bool isLongPressed();
	bool isLongReleased();

	bool justPressed();
	bool justReleased();

	bool justClicked();
	bool justLongClicked();
	bool justDoubleClicked();

protected:

	int _pin;
	byte _pinMode;

	uint16_t _state;

	bool _state;
	bool _pState;
	bool _longState;
	bool _longClick;
	bool _doubleClick;
	bool _now;
	bool _prev;

	bool _isJustPressed;
	bool _isJustReleased;

	bool _invert;

	long _time;
	long _timeDouble;

	int _debounceDelay;
	int _longDelay;
	int _doubleDelay;

};

class PushButtonGroup{

public:		

	PushButtonGroup();
	~PushButtonGroup();

	void add(PushButton* button);
	void remove(PushButton* button);

	bool update();

protected:

	PushButton **buttons;
	int buttonsSize;

};

#endif