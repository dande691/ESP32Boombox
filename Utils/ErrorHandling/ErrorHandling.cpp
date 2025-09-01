#include "ErrorHandling.h"

/*
    Error handling.
    Copyright © 2025 Dani Renlund <dani.renlund@gmail.com>
    This work is free. You can redistribute it and/or modify it under the
    terms of the Do What The Fuck You Want To Public License, Version 2,
    as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
    This is provided "as is", without warranty of any kind.
*/

void ErrorHandling::Main(esp_err_t Code, const char* CustomName) {
    const char* Error;
    if (gVars.System.Debug) {
        if (Code != ESP_OK) Error = esp_err_to_name(Code);
        else Error = CustomName;
        ESP_LOGE("ErrorHandling", "Error: %s", Error);
    }
    gVars.System.Error = true; //Set error flag as true, this is used to tell the user an error has occured.
    gVars.Save(); //Save all variables to EEPROM to prevent loss of settings.
    vTaskDelay(5000 / portTICK_PERIOD_MS); //Delay to allow the user to see the error.
    abort(); //Hard abort, we don't want to continue as something is fucked.
}   
