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
#include "EnemySprite.h"
#include "Shield.h"
#include "Collectible.h"

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------

// Generals
HINSTANCE         _hInstance;
GameEngine*       _pGame;
HDC               _hOffscreenDC;
HBITMAP           _hOffscreenBitmap;

Bitmap*           _pGameOverBitmap;
Bitmap*			  _bGameWonBitmap;

StarryBackground* _pBackground;
Bitmap*			  _pWallBitmap;
Bitmap*			  _pStairBitmap;

Bitmap*			  _pPlayerBitmap;
Sprite*           _pPlayerSprite;

// Level Informations
BOOL    _bGameOver, _bGameWon, _bGameMenu, _bGameHowToPlay;
int     enemyFireRate;
int		gameDifficulty = 1;
int		level = 1;
int		maxGhostAmount = 3;

// Menu
Bitmap* gameTitleBitmap;
Bitmap* playButtonBitmap;
int playButtonX = 0, playButtonY = 0, playButtonYOffset = -50;
Bitmap* howToPlayButtonBitmap;
int howToPlayButtonX = 0, howToPlayButtonY = 0, howToPlayButtonYOffset = 75;
Bitmap* exitButtonBitmap;
int exitButtonX = 0, exitButtonY = 0, exitButtonYOffset = 200;

// How To Play
Bitmap* backButtonBitmap;
Bitmap* howToPlayBitmap;
Bitmap* howToPlayTitleBitmap;
int backButtonX = 0, backButtonY = 0, backButtonYOffset = 285;

// Firing
int               _iFireInputDelay; 
const int		  _iFireMaxDelay = 3;
Bitmap*			  _pMissileBitmap;
Bitmap*			  fireballCollectibleBitmap;
Sprite*			  fireballCollectibleSprite;
int				  maxFireballAmount = 3;
int				  fireballAmount = 3;

// Collectibles
const int		  MAXLIVE = 7;
int               _iNumLives;
int				  keyNeeded = 1, keyAmount = 0;

// About Player
RECT			startPosition;
BOOL			facingRight = true;

// About player movement, physic and jumping
const int	HORIZONTALGRIP = 2;
const int	GRAVITY = 1;
const int   MAXJUMPSPEED = 8;
const int   MAXLADDERSPEED = 6;
const int   MAXMOVESPEED = 8;
const int   ACCELERATIONFORCE = 3;
BOOL        isJumpPressed = false;

// About Stairs and platforms
BOOL		isOnStair = false;
BOOL		isOnGrounded = false;
const int			numOfStairs = 1000;
const int			numOfPlatforms = 2000;
const int			numOfFloor = 7;
int			numOfStairsDynmc;
int			numOfPlatformsDynmc;
int			numOfFloorDynmc;
int			whichStair = -1;

// About collision and platforms
Platform* _pPlatform[numOfPlatforms] = {};	// Dynamic
int isCollide = 0;
BOOL collideBottom = false;
BOOL collideTop = false;

// Map
int         map[29][50] = {};
Stair*		_pStair[numOfStairs] = {};		// Dynamic
int			floorBottoms[numOfFloor] = {};	// Dynamic

// Enemy Bitmaps and Sprites
Sprite* missileSprite;

Bitmap* heartBitmap;
Bitmap* heartEmptyBitmap;
Sprite* heartSprite;

Bitmap* keyBitmap;
Bitmap* keyUIBitmap;
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
EnemySprite* bomberSprite;
Bitmap* bomberBombBitmap;

Bitmap* hunterBitmap;
Sprite* hunterSprite;

// Shield
Bitmap* shieldBitmap;
Sprite* shieldSprite;
int shieldInputDelay = 0;
int shieldMaxDelay = 8;
int shieldUsageDelay = 0;
int shieldUsageMaxDelay = 8;
BOOL canUseShield = true;

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void AddOtherSprites(int whichSprite, int x, int y, int x1, int x2);
BOOL CheckMapIfContains(int num);
int CheckMapForQuantity(int num);
BOOL CheckIntervalForDoor(int x1, int x2, int y);
void CreateMap();
void FillPlatformArray();
void FillStairArray();
void isOnLadderFunc();
void CheckGround();
void FacingWhere();
void CloseShield();
void Collide();
