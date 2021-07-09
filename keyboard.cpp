/*
 * keyboard.cpp
 *
 *  Created on: Jul 9, 2021
 *      Author: ismaelminchala
 */

#include "keyboard.h"

bool readKey(int16_t key){
	if (!digitalRead(key)){
		delay(20);
		return !digitalRead(key);
	} else{
		return 0;
	}
}

