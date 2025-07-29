#ifndef PHOTORESISTOR_H
	#define PHOTORESISTOR_H
#endif

// -------------------------------------------------------------------------------------
// Globals
const int photoPin = 28;    // A2
const int numBrightnessReadings = 20;
int brightness_readings[numBrightnessReadings];  // the readings from the analog input
int brightness_read_index = 0;          // the index of the current reading
int total_brightness = 0;              // the running total
int avg_brightness = 0;            // the average
int brightVal = 0;  // variable to store the value coming from the sensor
uint delay_countdown = 0;
// -------------------------------------------------------------------------------------

#define MAX_ADC_VAL 1023 // (CHECK) for pi pico -> 10-bit (?) adc ->  2^10=1024 resolution

// -------------------------------------------------------------------------------------
void read_photocell()
/* Read analog voltage. Add to array. Compute average. */
{
	// subtract the last reading:
	total_brightness = total_brightness - brightness_readings[brightness_read_index];

	// read from the sensor:
	brightness_readings[brightness_read_index] = analogRead(photoPin);

	// add the reading to the total:
	total_brightness = total_brightness + brightness_readings[brightness_read_index];

	// advance to the next position in the array:
	brightness_read_index = brightness_read_index + 1;

	// if we're at the end of the array...
	if (brightness_read_index >= numBrightnessReadings) {
		// ...wrap around to the beginning:
		brightness_read_index = 0;
	}

	// calculate the average:
	avg_brightness = total_brightness / numBrightnessReadings;
}

void init_photoresistor(){
	// Init brightness array
	for (uint8_t i=0;i<numBrightnessReadings;i++)
		brightness_readings[i]=0;
	read_photocell();
}
