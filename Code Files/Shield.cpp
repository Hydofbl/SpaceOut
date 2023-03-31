//-----------------------------------------------------------------
// Shield Sprite Object
// C++ Source - Shield.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Shield.h"

//-----------------------------------------------------------------
// EnemySprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Shield::Shield(Bitmap* pBitmap, RECT& rcBounds,
    BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
        baBoundsAction)
{
}

Shield::Shield(Bitmap* pBitmap, RECT& rcBounds, Sprite* _playerSprite,
    BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds, _playerSprite,
        baBoundsAction)
{
    playerSprite = _playerSprite;
}

Shield::~Shield()
{
}

//-----------------------------------------------------------------
// EnemySprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Shield::Update()
{
    // Call the base sprite Update() method
    SPRITEACTION saSpriteAction;
    saSpriteAction = Sprite::Update();

    Track();

    return saSpriteAction;
}

void Shield::Track() {
    RECT playerPos = playerSprite->GetPosition();
    playerPos.left -= 8;
    playerPos.right -= 8;
    playerPos.top -= 12;
    playerPos.bottom -= 12;
    SetPosition(playerPos);
}
