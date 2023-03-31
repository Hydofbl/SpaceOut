//-----------------------------------------------------------------
// Collectible Sprite Object
// C++ Source - Collectible.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Collectible.h"



//-----------------------------------------------------------------
// Collectible Constructor(s)/Destructor
//-----------------------------------------------------------------
Collectible::Collectible(Bitmap* pBitmap, RECT& rcBounds,
    BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
        baBoundsAction)
{
}

Collectible::~Collectible()
{
}

//-----------------------------------------------------------------
// Collectible General Methods
//-----------------------------------------------------------------
SPRITEACTION Collectible::Update()
{
    // Call the base sprite Update() method
    SPRITEACTION saSpriteAction;
    saSpriteAction = Sprite::Update();

    Move();

    return saSpriteAction;
}

void Collectible::Move() {


    if (++count > maxDelay)
    {
        int temp = (rand() % 4) + 1;

        if (temp == 1) {
            SetVelocity(5, 0);
        }
        else if (temp == 2) {
            SetVelocity(0, 5);
        }
        else if (temp == 3) {
            SetVelocity(-5, 0);
        }
        else {
            SetVelocity(0, -5);
        }    
        count = 0;
    }
}
