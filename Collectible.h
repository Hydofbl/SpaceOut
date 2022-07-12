//-----------------------------------------------------------------
// Collectible Sprite Object
// C++ Header - Collectible.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"


//-----------------------------------------------------------------
// Collectible Class
//-----------------------------------------------------------------
class Collectible : public Sprite
{
protected:
    int count= 0;
    int maxDelay = 40;
public:
    // Constructor(s)/Destructor
    Collectible(Bitmap* pBitmap, RECT& rcBounds,
        BOUNDSACTION baBoundsAction = BA_STOP);
    virtual ~Collectible();

    // General Methods
    virtual SPRITEACTION  Update();

    RECT& GetBounds() { return m_rcBounds; };

    void Move();
};
