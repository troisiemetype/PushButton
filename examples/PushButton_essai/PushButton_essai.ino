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
	bouton.begin(12);
//	pinMode(12, INPUT_PULLUP);

}

void loop(){

	bouton.update();

	bool pushed = bouton.isPressed();
	bool released = bouton.isReleased();
	bool longPressed = bouton.isLongPressed();
	bool longReleased = bouton.isLongReleased();
	bool justPressed = bouton.justPressed();
	bool justReleased = bouton.justReleased();


	if(pushed){
		Serial.println("pushed");
	}
	if(released){
		Serial.println("released");
	}
	if(justPressed){
		Serial.println("just pressed");
	}
	if(justReleased){
		Serial.println("just released");
	}
	if(longPressed){
		Serial.println("long pressed");
	}
	if(longReleased){
		Serial.println("long released");
	}
	
//	Serial.println(digitalRead(12));
}