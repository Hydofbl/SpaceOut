//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AlienSprite.h"

//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Bitmap* mageBitmap;
extern Bitmap* gollumBitmap;
extern Bitmap* batBitmap;
extern Bitmap* ghostBitmap;
extern Bitmap* bomberBitmap;
extern Bitmap* hunterBitmap; 
extern Bitmap* mageMissileBitmap;
extern Bitmap* batMissileBitmap;
extern Bitmap* bomberBombBitmap;

extern int     _iDifficulty;

//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
AlienSprite::AlienSprite(Bitmap* pBitmap, RECT& rcBounds,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
  baBoundsAction)
{
}

AlienSprite::~AlienSprite()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION AlienSprite::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  // See if the alien should fire a missile
  if ((rand() % (_iDifficulty / 2)) == 0)
    saSpriteAction |= SA_ADDSPRITE;

  return saSpriteAction;
}

Sprite* AlienSprite::AddSprite()
{
  // Create a new missile sprite
  RECT    rcBounds = { 0, 0, 640, 410 };
  RECT    rcPos = GetPosition();
  Sprite* pSprite = NULL;
  if (GetBitmap() == mageBitmap)
  {
      rcBounds.right = 1250;
    pSprite = new Sprite(mageMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(3, 0);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.right + 25, rcPos.top + mageBitmap->GetHeight()/2 - 10 );
  }
  else if (GetBitmap() == batBitmap)
  {
      RECT          rcBounds2 = { 400, 0, 800, 800 };
    pSprite = new Sprite(batMissileBitmap, rcBounds2, BA_DIE);
    pSprite->SetVelocity(0, 5);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
  }
  else
  {
      RECT          rcBounds3 = { 400, 0, 800, 800 };
    pSprite = new Sprite(bomberBombBitmap, rcBounds3, BA_DIE);
    pSprite->SetVelocity(0, 0);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom - bomberBombBitmap->GetHeight()+20);
  }

  return pSprite;
}
