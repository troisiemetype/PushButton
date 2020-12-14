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

#ifndef PULLUP
#define PULLUP 			0x3
#endif
#ifndef PULLDOWN
#define PULLDOWN        0x4
#endif

class PushButton{

public:

	PushButton();

	void begin(const uint8_t& mode);
	void begin(const uint8_t& pin, const uint8_t& mode);

	void setDebounceDelay(uint16_t delay);
	void setLongDelay(uint16_t delay);
	void setDoubleDelay(uint16_t delay);

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

	uint8_t _pin;
	uint8_t _pinMode;

	struct{
		uint16_t state : 1;
		uint16_t pState : 1;
		uint16_t longState : 1;
		uint16_t longClick : 1;
		uint16_t doubleClick : 1;
		uint16_t now : 1;
		uint16_t prev : 1;
		uint16_t isJustPressed : 1;
		uint16_t isJustReleased : 1;
		uint16_t invert : 1;
	} _states;


	uint32_t _time;
	uint32_t _timeDouble;

	uint16_t _debounceDelay;
	uint16_t _longDelay;
	uint16_t _doubleDelay;

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
	uint8_t buttonsSize;

};

#endif