#ifndef SENSOR_CURRENT_H
	#define SENSOR_CURRENT_H
#endif

#ifndef _LIB_ADAFRUIT_INA219_
	#include <Adafruit_INA219.h>
#endif

String print_current_byref(Adafruit_INA219* ina219)
/* Print current & voltage */
{
	float shuntvoltage = 0;
	float busvoltage = 0;
	float current_mA = 0;
	float loadvoltage = 0;
	float power_mW = 0;

	shuntvoltage = ina219->getShuntVoltage_mV();
	busvoltage = ina219->getBusVoltage_V();
	current_mA = ina219->getCurrent_mA();
	power_mW = ina219->getPower_mW();
	loadvoltage = busvoltage + (shuntvoltage / 1000);

	if (current_mA<0)
		power_mW*=-1;

	char buf[40];
	sprintf(buf,"%.2fV  %.1fmA  %.1fmW",loadvoltage,current_mA,power_mW);

	return buf;
}

void get_vals_current_sensor(Adafruit_INA219* ina219, float* loadvoltage, float* current_mA, float* power_mW, float* shuntvoltage,float* busvoltage){

	*shuntvoltage = ina219->getShuntVoltage_mV();
	*busvoltage = ina219->getBusVoltage_V();
	*current_mA = ina219->getCurrent_mA();
	*power_mW = ina219->getPower_mW();
	*loadvoltage = *busvoltage + (*shuntvoltage / 1000.0);

	if (*current_mA<0.0)
		*power_mW*=-1.0;
}