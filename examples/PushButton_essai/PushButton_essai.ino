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


#include <PushButton.h>

PushButton bouton = PushButton();

void setup(){
	Serial.begin(115200);
	bouton.begin(4);

//	pinMode(12, INPUT_PULLUP);

}

void loop(){

	bouton.update();

	bool pushed = bouton.isPressed();
	bool released = bouton.isReleased();
	bool longPressed = bouton.isLongPressed();
	bool longReleased = bouton.isLongReleased();
//	bool justPressed = bouton.justPressed();
//	bool justReleased = bouton.justReleased();

	bool justDoubleClicked = bouton.justDoubleClicked();
	bool justClicked = bouton.justClicked();
	bool justLongClicked = bouton.justLongClicked();


	if(0){
		Serial.println("pressed");
	}
	if(0){
		Serial.println("released");
	}
	if(0){
		Serial.println("just pressed");
	}
	if(0){
		Serial.println("just released");
	}
	if(0){
		Serial.println("long pressed");
	}
	if(0){
		Serial.println("long released");
	}
	if(justClicked){
		Serial.println("clicked");
	}
	if(justLongClicked){
		Serial.println("long clicked");
	}
	if(justDoubleClicked){
		Serial.println("double clicked");
	}
	
//	Serial.println(digitalRead(12));
}