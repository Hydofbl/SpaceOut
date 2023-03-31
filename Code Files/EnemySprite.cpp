//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - EnemySprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "EnemySprite.h"

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

extern int     enemyFireRate;
extern int     gameDifficulty;

//-----------------------------------------------------------------
// EnemySprite Constructor(s)/Destructor
//-----------------------------------------------------------------
EnemySprite::EnemySprite(Bitmap* pBitmap, RECT& rcBounds,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
  baBoundsAction)
{
}

EnemySprite::EnemySprite(Bitmap* pBitmap, RECT& rcBounds, Sprite* _playerSprite,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds, _playerSprite,
  baBoundsAction)
{
    playerSprite = _playerSprite;
}

EnemySprite::~EnemySprite()
{
}

//-----------------------------------------------------------------
// EnemySprite General Methods
//-----------------------------------------------------------------
SPRITEACTION EnemySprite::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  Jump();
  LookFor();
  Track();

  // See if the alien should fire a missile
  if ((rand() % ((enemyFireRate - (gameDifficulty-1)) * 4)) == 0)
    saSpriteAction |= SA_ADDSPRITE;

  return saSpriteAction;
}

Sprite* EnemySprite::AddSprite()
{
  // Create a new missile sprite
  RECT    rcBounds = { 0, 0, 1260, 770 };
  RECT    rcPos = GetPosition();
  Sprite* pSprite = NULL;
  if (GetBitmap() == mageBitmap)
  {
    pSprite = new Sprite(mageMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(4, 0);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.right + 25, rcPos.top + mageBitmap->GetHeight()/2);
  }
  else if (GetBitmap() == batBitmap)
  {
    rcBounds = GetBounds();
    rcBounds.bottom = GetPosition().top + 540;
    pSprite = new Sprite(batMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(0, 5);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
  }
  else if(GetBitmap() == bomberBitmap && bombAmount < maxBombAmount)
  {
    pSprite = new Sprite(bomberBombBitmap, rcBounds, BA_DIE);

    // Set the missile sprite's position and return it
    pSprite->SetPosition(rcPos.left + (GetWidth() * 2), rcPos.bottom - bomberBombBitmap->GetHeight()+5);
  }

  return pSprite;
}


void EnemySprite::Jump() {
    if (GetBitmap() == gollumBitmap) {
        RECT    rcBounds = GetBounds();
        RECT    rcPos = GetPosition();
        POINT tempVelocity = GetVelocity();

        if (rcPos.bottom == rcBounds.bottom) {
            tempVelocity.y = min(-gollumMaxJumpSpeed, --tempVelocity.y);
            SetVelocity(tempVelocity);
        }
        else {
            if (tempVelocity.y != gollumMaxFallSpeed) {

                if (tempVelocity.y < gollumMaxFallSpeed) {
                    tempVelocity.y += gollumGravityPower;
                }
                else {
                    tempVelocity.y = gollumMaxFallSpeed;
                }
                SetVelocity(tempVelocity);
            }
        }
    }
}

void EnemySprite::LookFor()
{

    if (GetBitmap() == ghostBitmap) {
        RECT playerPos = playerSprite->GetPosition();
        RECT enemyPos = GetPosition();
        int diffY = (playerPos.top + playerSprite->GetHeight() / 2) - (enemyPos.top + GetHeight() / 2);
        int diffX = (playerPos.left + playerSprite->GetWidth() / 2) - (enemyPos.left + GetWidth() / 2);
        float temp = sqrt((diffY * diffY) + (diffX * diffX));

        if (temp <= ghostMaxDistance) {
            if (!isGhostcanSee)
                isGhostcanSee = true;
            ghostTargetPoint.x = playerPos.left + playerSprite->GetWidth() / 2;
            ghostTargetPoint.y = playerPos.top + playerSprite->GetHeight() / 2;

            if (diffX > 0)
                ghostDirection.x = 1;
            else
                ghostDirection.x = -1;
            if (diffY > 0)
                ghostDirection.y = 1;
            else
                ghostDirection.y = -1;
        }
        else {
            if (isGhostcanSee)
                isGhostcanSee = false;

            diffY = ghostTargetPoint.y - (enemyPos.top + GetHeight() / 2);
            diffX = ghostTargetPoint.x - (enemyPos.left + GetWidth() / 2);
        }
    }
}

void EnemySprite::Track() {
    if (GetBitmap() == ghostBitmap) {
        if (isGhostcanSee) {
            SetVelocity(ghostDirection.x * ghostTrackSpeed, ghostDirection.y * ghostTrackSpeed);
        }
    }
}

