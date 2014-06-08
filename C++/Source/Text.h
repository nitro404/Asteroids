#pragma once

#include "Includes.h"

// simple 2D text abstraction - colour and position are pre-determined, but can be changed on the fly
// text that is rendered to the screen is passed when it actually draws onto the screen (incase it is to change)
class Text {
public:
	Text(const char * fontFace, int fontSize, int fontWeight, bool italic, int fontAlignment, int fontOffset, int xPos, int yPos, D3DCOLOR fontColour, LPDIRECT3DDEVICE9 d3dDevice);
	~Text();
	
	void setColour(D3DCOLOR newColour); // change the colour of the text

	void draw(const char * text, ...); // draw a text (with optional parameter list) to the screen with previously specified attributes

	// font style constants
	const static int NORMAL;
	const static int REGULAR;
	const static int BOLD;

	// font offset/alignment constants
	const static int LEFT;
	const static int CENTER;
	const static int RIGHT;

private:
	void drawHelper(const char * text);

private:
	// the pre-created font and sprite that the text is to be drawn onto
	LPD3DXFONT font;
	LPD3DXSPRITE sprite;

	// dimensions, location, allignment and offset of the text
	int size;
	int x, y;
	int alignment;
	int offset;

	// colour of the text
	D3DCOLOR colour;

	// text boundary box
	RECT textBox;
};
