//-----------------------------------------------------------------
// Sprite Object
// C++ Source - Sprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Stair.h"

//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Stair::Stair(RECT& rcPosition, Bitmap* pBitmap)
{
    // Initialize the member variables
    m_rcPosition = rcPosition;
    m_pBitmap = pBitmap;
}

Stair::~Stair()
{
}

void Stair::Draw(HDC hDC)
{
    // Draw the sprite if it isn't hidden
    if (m_pBitmap != NULL)
        m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, TRUE);
}
