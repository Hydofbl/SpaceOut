//-----------------------------------------------------------------
// Space Out Application
// C++ Header - SpaceOut.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Background.h"
#include "Stair.h"
#include "Platform.h"
#include "AlienSprite.h"

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         _hInstance;
GameEngine*       _pGame;
HDC               _hOffscreenDC;
HBITMAP           _hOffscreenBitmap;
Bitmap*           _pPlayerBitmap;
Bitmap*           _pSmPlayerBitmap;
Bitmap*           _pGameOverBitmap;
Bitmap*			  _pWallBitmap;
Bitmap*			  _pStairBitmap;
StarryBackground* _pBackground;
Sprite*           _pPlayerSprite;
int               _iFireInputDelay;
int               _iNumLives, _iScore;
BOOL              _bGameOver;
int               _platformHeight = 105; 
const int	HORIZONTALGRIP = 1;
const int	GRAVITY = 1;
const int   MAXJUMPSPEED = 8;
const int   MAXLADDERSPEED = 6;
const int   MAXLIVE = 5;
BOOL        isJumpPressed = false;
BOOL		isOnStair = false;
const int			numOfStairs = 18;
const int			numOfPlatforms = 197;
int			whichStair = -1;
Stair*		_pStair[numOfStairs] = {};
Platform*	_pPlatform[numOfPlatforms] = {};
int isCollide = 0;
BOOL collideBottom = false;
BOOL collideTop = false;

int     _iDifficulty;

Bitmap* missileBitmap;
Sprite* missileSprite;

Bitmap* heartBitmap;
Sprite* heartSprite;

Bitmap* keyBitmap;
Sprite* keySprite;

Bitmap* doorBitmap;
Sprite* doorSprite;

Bitmap* mageBitmap;
Sprite* mageSprite;
Bitmap* mageMissileBitmap;
Sprite* mageMissileSprite;

Bitmap* gollumBitmap;
Sprite* gollumSprite;

Bitmap* batBitmap;
Sprite* batSprite; 
Bitmap* batMissileBitmap;
Sprite* batMissileSprite;

Bitmap* ghostBitmap;
Sprite* ghostSprite;

Bitmap* bomberBitmap;
Sprite* bomberSprite;
Bitmap* bomberBombBitmap;
Sprite* bomberBombSprite;

Bitmap* hunterBitmap;
Sprite* hunterSprite;


//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void isOnLadderFunc();
void Collide(Sprite* player, Platform* platform);
