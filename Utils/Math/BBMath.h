#pragma once
#include "GlobalInfo.h"
class Math {
public: //Main
	int ClampInt(int Value, int Max, int Min);
	int WrapInt(int Value, int Max, int Min);
	float ClampFloat(float Value, float Max, float Min);
	float WrapFloat(float Value, float Max, float Min);
	float CompensateVoltageDrop(float Current, float Resistance = 0.05);
	float ConvertToVoltage(float Input, float R1, float R2);
};
inline Math gMath;
