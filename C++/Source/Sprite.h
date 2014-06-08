#pragma once

#include "Includes.h"

// a d3d sprite / texture sprite abstraction to make sprite creation / drawing simpler and more efficient
class Sprite {
public:
	Sprite(char * fileName, char * directory, LPDIRECT3DDEVICE9 d3dDevice); // load a game sprite from a file and directory
	Sprite::Sprite(int x, int y, // load a game sprite from an external pre-loaded d3d texture and corresponding d3d sprite
				   int spriteWidth, int spriteHeight,
				   LPDIRECT3DTEXTURE9 externalTexture, LPD3DXSPRITE externalSprite) :	xOffset(x), yOffset(y),
																						width(spriteWidth), height(spriteHeight),
																						texture(externalTexture), sprite(externalSprite),
																						ownsSprite(false) { } // take into account that the game sprite does not own the d3d texture/sprite
	~Sprite();

	// get the center of the sprite (width / 2), (height / 2)
	int getOffsetX() { return xOffset; }
	int getOffsetY() { return yOffset; }

	// get the width and height of the sprite
	int getWidth() { return width; }
	int getHeight() { return height; }

	// extract the d3d texture/sprite associated with this game sprite
	LPDIRECT3DTEXTURE9 getTexture() { return texture; }
	LPD3DXSPRITE getSprite() { return sprite; }

	// draw the sprite from a set of 2D vectors describing the size, offset, angle and location of the sprite (create the matrix on the fly)
	void draw(D3DXVECTOR2 * scale, D3DXVECTOR2 * scalingOffset, float rotationDegrees, D3DXVECTOR2 * rotationOffset, D3DXVECTOR2 * position, LPDIRECT3DDEVICE9 d3dDevice);
	// draw the sprite from a pre-computed matrix
	void draw(D3DXMATRIX & transformation, LPDIRECT3DDEVICE9 d3dDevice);

private:
	// d3d texture / sprite information
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	bool ownsSprite;

	// temporary transformation matrix storage
	D3DXMATRIX transformationMatrix;

	// center of the sprite
	int xOffset;
	int yOffset;

	// width and height of the sprite
	int width;
	int height;
};
