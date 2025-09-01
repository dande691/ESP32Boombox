#include "Draw.h"
uint8_t DisplayBuffer[1024]; //128x64 pixels / 8 bits per byte = 1024 bytes for the buffer
/*
	Simple draw functions used for drawing on SSD1306.
	Copyright © 2025 Dani Renlund <dani.renlund@gmail.com>
	This work is free. You can redistribute it and/or modify it under the
	terms of the Do What The Fuck You Want To Public License, Version 2,
	as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
	This is provided "as is", without warranty of any kind.
*/

void Draw::Setup() { //This should have all the stuff we need to make it work, "should".
	memset(DisplayBuffer, 0, 1024); //Clear the buffer incase there is some junk.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::DISPLAY_OFF)); //Turn off the display so we can configure it.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_DISPLAY_CLOCK_DIV));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x80); //Divide by 1.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_MULTIPLEX));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306_HEIGHT - 1)); //Height - 1, 0-63.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_DISPLAY_OFFSET));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x00); //No offset.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_START_LINE) | 0x0); //Set the start line to 0 aka top.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::CHARGE_PUMP));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x14); //Enable charge pump, 0x10 to disable (when supplied with 7.5V).
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::MEMORY_MODE));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x00); //Horizontal.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SEG_REMAP) | 0x1); //Set segment remap to 127.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::COM_SCAN_DEC));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_COM_PINS));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x12); //Alternative, disable COM left/right remap.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_CONTRAST));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0xFF); //0xFF = 255, max brightness.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_PRECHARGE));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0xF1); //1 : 15, recommended.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_VCOM_DETECT));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x40); //0.77 * VCC, recommended.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::ENTIRE_DISPLAY_ON_RESUME)); //Output RAM to display.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::NORMAL_DISPLAY)); //Set normal display.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::DISPLAY_ON)); //Turn the display on.
}

void Draw::ChangeBrightness(int Brightness) { //0-255.
	int ClampedBrightness = gMath.ClampInt(Brightness, 0, 255); //Clamp the brightness to 0-255.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::DISPLAY_OFF));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::SET_CONTRAST));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(ClampedBrightness));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::DISPLAY_ON));
}

void Draw::Update(bool Force) {
	if (!UpdateNeeded && !Force) return; //No need to update if nothing has changed.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::PAGE_ADDR));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x00); //Page start address.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0xFF); //Page end address.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306Commands::COLUMN_ADDR));
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), 0x00); //Column start address.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::COMMAND), static_cast<uint8_t>(SSD1306_WIDTH - 1)); //Page start address, 0-127.
	gI2C.WriteRegister(static_cast<uint8_t>(I2CDeviceAdresses::SSD1306), static_cast<uint8_t>(SSD1306Adresses::DATA), DisplayBuffer, sizeof(DisplayBuffer)); //Send the buffer data to the display.
	UpdateNeeded = false; //Reset the update flag.
}

void Draw::Clear() {
	memset(DisplayBuffer, 0, sizeof(DisplayBuffer)); //Clear the buffer by settings every byte to 0 aka off.
	UpdateNeeded = true; //Mark that an update is needed.
}

void Draw::SetPixel(int x, int y) { //Lets keep the calculations seperated instead of doing them in the buffer part to make it easier to read (its ass).
	if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) return; //Out of bounds check.
	uint8_t page_index = static_cast<int>(y) / 8; //Byte row index (0-7).
	uint8_t bit_position = static_cast<int>(y) % 8; //Bit position within the byte (0-7).
	uint16_t byte_index = static_cast<int>(x) + (page_index * SSD1306_WIDTH); //Calculate the byte index in the buffer.
	uint8_t bitmask = (1 << bit_position); //Create a bitmask for the specific bit.
	DisplayBuffer[byte_index] |= bitmask; //Set the bit to 1 (pixel on).
	UpdateNeeded = true; //Mark that an update is needed.
}

void Draw::DrawLine(int x, int y, int x2, int y2) { //Bresenham's algorithm, integer math is love https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm.
	int dx = (x2 > x) ? (x2 - x) : (x - x2); //Calculate the difference between start and end.
	int dy = (y2 > y) ? (y2 - y) : (y - y2);
	int sx = (x < x2) ? 1 : -1; //Define the direction
	int sy = (y < y2) ? 1 : -1;
	int err = dx - dy; //Difference between ideal path and actual grid.
	while (1) {
		SetPixel(x, y); //Send it to the buffer.
		if (x == x2 && y == y2) break; //Check if we are done.
		int e2 = 2 * err; //Calculate the new error term, multiply by 2 to avoid floating point.
		if (e2 > -dy) { //Check if the error is greater than the negative dy.
			err -= dy; //Adjust the error term.
			x += sx; //Move in the x direction.
		}
		if (e2 < dx) { //Same as above but for y.
			err += dx;
			y += sy;
		}
	}
}

void Draw::DrawRect(int x, int y, int w, int h) {
	DrawLine(x, y, x + w - 1, y); //Top
	DrawLine(x, y + h - 1, x + w - 1, y + h - 1); //Bottom
	DrawLine(x, y, x, y + h - 1); //Left
	DrawLine(x + w - 1, y, x + w - 1, y + h - 1); //Right
}

void Draw::DrawFilledRect(int x, int y, int w, int h) {
	for (int i = x; i < x + w && i < SSD1306_WIDTH; i++) { //Loop through the width.
		for (int j = y; j < y + h && j < SSD1306_HEIGHT; j++) { //Loop through the height.
			SetPixel(i, j);
		}
	}
}

void Draw::DrawCircle(int x0, int y0, int r) { //Midpoint algorithm https://en.wikipedia.org/wiki/Midpoint_circle_algorithm.
	int x = r; //Start at the rightmost point of the circle.
	int y = 0; //Start at the topmost point of the circle.
	int err = 0;
	while (x >= y) { //Only need to calculate 1/8 of the circle due to symmetry.
		SetPixel(x0 + x, y0 + y);
		SetPixel(x0 + y, y0 + x);
		SetPixel(x0 - y, y0 + x);
		SetPixel(x0 - x, y0 + y);
		SetPixel(x0 - x, y0 - y);
		SetPixel(x0 - y, y0 - x);
		SetPixel(x0 + y, y0 - x);
		SetPixel(x0 + x, y0 - y);
		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void Draw::DrawChar(int x, int y, char c, FontSize Size, bool Bold) {
	if (c < 32 || c > 126) return; //Out of bounds.
	const uint8_t* Font = Font5x7[c - 32]; //Get the font data for the character.
	for (int col = 0; col < 5; col++) { //Each character is 5 columns wide.
		int column_data = static_cast<int>(Font[col]); //Get the column data.
		for (int row = 0; row < 7; row++) { //Each column is 7 bits high.
			if (column_data & (1 << row)) { //Check if the bit is set.
				for (int sx = 0; sx < static_cast<int>(Size); sx++) { //Scale the pixel size.
					for (int sy = 0; sy < static_cast<int>(Size); sy++) { 
						int px = x + col * static_cast<int>(Size) + sx; //Calculate the pixel position.
						int py = y + row * static_cast<int>(Size) + sy;
						SetPixel(px, py);
						if (Bold) {
							SetPixel(px + 1, py);
							if (static_cast<int>(Size) > 1) { //Check if the size if greater than 1 to avoid overdrawing.
								SetPixel(px, py + 1);
								SetPixel(px + 1, py + 1);
							}
						}
					}
				}
			}
		}
	}
}

void Draw::DrawString(int x, int y, const char* str, FontSize Size, bool Bold) {
	if (!str) return; //Check for null pointer.
	int Width = (5 * static_cast<int>(Size)) + (Bold ? 1 : 0); 
	for (int i = 0; str[i] != '\0'; i++) { //Loop through each character.
		DrawChar(x + i * (Width + static_cast<int>(Size)), y, str[i], Size, Bold);
	}
}

int Draw::GetStringWidth(const char* str, FontSize Size, bool Bold) {
	uint8_t Width = (5 * static_cast<int>(Size)) + (Bold ? 1 : 0);
	uint8_t Length = strlen(str); //Get the length of the string.
	if (Length == 0) return 0; //Return 0 if the string is empty.
	return Length * Width + (Length - 1) * static_cast<int>(Size); //Calculate the total width.
}
