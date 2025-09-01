#pragma once
#include "Vars.h"
#include "esp_err.h"
class ErrorHandling {
public:
	void Main(esp_err_t Code, const char* CustomName = "");  //Set CustomName to "" so we can skip it if not needed.
};
inline ErrorHandling gErrorHandling;
