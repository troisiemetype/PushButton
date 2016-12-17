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

PushButton bouton1 = PushButton();
PushButton bouton2 = PushButton();
PushButton bouton3 = PushButton();

PushButtonGroup group = PushButtonGroup();

void setup(){
	Serial.begin(115200);
	bouton1.begin(10);
	bouton2.begin(11);
	bouton3.begin(12);

	group.add(&bouton1);
	group.add(&bouton2);
	group.add(&bouton3);

}

void loop(){

	if(group.update()){
		Serial.print(bouton1.isPressed());
		Serial.print("  |  ");
		Serial.print(bouton2.isPressed());
		Serial.print("  |  ");
		Serial.print(bouton3.isPressed());
		Serial.println();
	}

}