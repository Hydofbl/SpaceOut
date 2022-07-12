//-----------------------------------------------------------------
// Enemy Sprite Object
// C++ Header - EnemySprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"
#include <cmath>

//-----------------------------------------------------------------
// EnemySprite Class
//-----------------------------------------------------------------
class EnemySprite : public Sprite
{
protected:
    int gollumMaxFallSpeed = 8;
    int gollumMaxJumpSpeed = 10;
    int gollumGravityPower = 1;

    float		ghostMaxDistance = 280;
    float		ghostTrackSpeed = 2;
    BOOL		isGhostcanSee = false;

    POINT ghostTargetPoint;
    POINT ghostDirection;

    int bombAmount = 0;
    int maxBombAmount = 5;

    Sprite* playerSprite;

public:
  // Constructor(s)/Destructor
          EnemySprite(Bitmap* pBitmap, RECT& rcBounds, 
            BOUNDSACTION baBoundsAction = BA_STOP);
          
          EnemySprite(Bitmap* pBitmap, RECT& rcBounds, Sprite* _playerSprite,
            BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~EnemySprite();

  // General Methods
  virtual SPRITEACTION  Update();
  virtual Sprite*       AddSprite();

  RECT& GetBounds() { return m_rcBounds; };
  void SetPlayerSprite(Sprite* sprite) { playerSprite = sprite; };

  void DecreaseBombAmount() { bombAmount--; };

  void Jump(); 
  void LookFor();
  void Track();
};
