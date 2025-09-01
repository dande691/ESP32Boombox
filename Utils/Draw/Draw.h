#pragma once
#include "GlobalInfo.h"
#include "I2C.h"
#include "Fonts.h"

enum class FontSize : int {
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 3
};

class Draw {
public: //Main
	void Setup();
	void ChangeBrightness(int Brightness);
	void Update(bool Force);
	void Clear();
	void SetPixel(int x, int y);
	void DrawLine(int x, int y, int x2, int y2);
	void DrawRect(int x, int y, int w, int h);
	void DrawFilledRect(int x, int y, int w, int h);
	void DrawCircle(int x0, int y0, int r);
	void DrawChar(int x, int y, char c, FontSize Size, bool Bold);
	void DrawString(int x, int y, const char* str, FontSize Size, bool Bold);
	int GetStringWidth(const char* str, FontSize Size, bool Bold);

private:
	bool UpdateNeeded = false;
};
inline Draw gDraw;
