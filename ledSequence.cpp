// Do not remove the include below
#include "ledSequence.h"

//#define length(array) (sizeof(array) / sizeof(*(array)));

const	int16_t LED1 = 50;            // Port address of LEDx
const 	int16_t LED2 = 51;
const 	int16_t LED3 = 52;
const 	int16_t LED4 = 53;
const 	int16_t KEY1 = 48;            // Port address of KEYx
const 	int16_t KEY2 = 49;

enum  	dir {ascending, descending};// Enum var for sequence

/****************** + Functions prototypes + *******************/
bool turnOffLeds(int16_t* leds , int16_t len);
bool ledSequence(int16_t leds[], int16_t len, dir);
bool sequenceSpeed(int16_t tBase, int16_t tDelay);
bool toogleState();
/***************************************************************/

/*********************** + Setup loop + ************************/
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(KEY1, INPUT);
  pinMode(KEY2, INPUT);
}
/***************************************************************/

/************************ + Main loop + ************************/
void loop() {

	/**************** + Variables declaration + ****************/
			const 	int16_t t_base = 5;	// Time base for delay
			const 	int16_t fast = 250;	// Fast sequence time
			const 	int16_t slow = 750;	// Slow sequence time
			int16_t	t_delay = slow;
			int16_t	arrayOfLeds[] = {LED1, LED2, LED3, LED4};
			int16_t	length = sizeof(arrayOfLeds) / sizeof(int);
			dir 	direction = ascending;	// orientation
	/***********************************************************/

	while(1){
//		if ( digitalRead(KEY1) == LOW ){
		if ( readKey(KEY1) ){
			if(toogleState()){
				direction = ascending;
			} else{
				direction = descending;
			}
		}

		if ( readKey(KEY2) ){
			if(toogleState()){
				t_delay = fast;
			} else{
				t_delay = slow;
			}
		}

		/*if ( !digitalRead(KEY2) == LOW ){
			t_delay = fast;
		} else{
			t_delay = slow;
		}*/

		if ( sequenceSpeed(t_base, t_delay) ){
			ledSequence(arrayOfLeds, length, direction);
		}
	}
}
/***************************************************************/


bool turnOffLeds(int16_t* leds, int16_t len){
	for (int i = 0; i < len; ++i){
//	    digitalWrite(leds[i], LOW);
//	    if (digitalRead(leds[i])){
	    digitalWrite(leds[i], LOW);
	    if (digitalRead(leds[i])){
	    	return 0;
	    }
	}
	return 1;
}

bool ledSequence(int16_t leds[], int16_t len, dir orientation){
	static int16_t pos = 0;
	if (!turnOffLeds(leds, len)){
		return 0;
	}
	digitalWrite(leds[pos], HIGH);
	if (orientation == ascending){
		if (pos < len - 1){
			++pos;
	    } else{
	      pos = 0;
	    }
	} else{
		if (pos > 0){
			--pos;
	    } else{
	      pos = len - 1;
	    }
	}
	return 1;
}

bool sequenceSpeed(int16_t t_base, int16_t t_delay){
	static int16_t count = 0;
	delay(t_base);
	int16_t n_base = t_delay / t_base;
	if (count < n_base){
		++count;
		return 0;
	} else{
		count = 0;
		return 1;
	}
}


bool toogleState(){
	static bool var = 0;
	delay(25);
	var = !var;
	return var;
}
