#include "BBMath.h"
//This was named BBMath instead of Math, as Math caused the compiler to freak out.
/*
	Simple math used by the ESP32 based boombox.
	Copyright © 2025 Dani Renlund <dani.renlund@gmail.com>
	This work is free. You can redistribute it and/or modify it under the
	terms of the Do What The Fuck You Want To Public License, Version 2,
	as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
	This is provided "as is", without warranty of any kind.
*/

int Math::ClampInt(int Value, int Max, int Min) {
	if (Value > Max) return Max;
	if (Value < Min) return Min;
	return Value;
}

int Math::WrapInt(int Value, int Max, int Min) {
	if (Value > Max) return Min; //If value is bigger than max, return the min amount.
	if (Value < Min) return Max; //Same, but the otherway around
	return Value; //Return the value.
}

float Math::ClampFloat(float Value, float Max, float Min) {
	if (Value > Max) return Max;
	if (Value < Min) return Min;
	return Value;
}

float Math::WrapFloat(float Value, float Max, float Min) { //Same as above, but for float.
	if (Value > Max) return Min;
	if (Value < Min) return Max;
	return Value;
}

float Math::CompensateVoltageDrop(float Current, float Resistance) { //For our this is 0.05 Ohms, as per the datasheet of our cells.
	return Current * Resistance; //Ohm's law, calculate voltage drop caused by current draw.
}

float Math::ConvertToVoltage(float Input, float R1, float R2) { //Convert the input to voltage, as per the formula in the datasheet.
	return (Input / 4095.0f) * 3.3f * ((R1 + R2) / R2);
}
