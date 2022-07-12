//-----------------------------------------------------------------
// Shield Sprite Object
// C++ Header - Shield.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"

//-----------------------------------------------------------------
// Shield Class
//-----------------------------------------------------------------
class Shield : public Sprite
{
protected:
    Sprite* playerSprite;

public:
    // Constructor(s)/Destructor
    Shield(Bitmap* pBitmap, RECT& rcBounds,
        BOUNDSACTION baBoundsAction = BA_STOP);

    Shield(Bitmap* pBitmap, RECT& rcBounds, Sprite* _playerSprite,
        BOUNDSACTION baBoundsAction = BA_STOP);
    virtual ~Shield();

    // General Methods
    virtual SPRITEACTION  Update();

    RECT& GetBounds() { return m_rcBounds; };
    void SetPlayerSprite(Sprite* sprite) { playerSprite = sprite; };

    void Track();
};
