//-----------------------------------------------------------------
// Sprite Object
// C++ Source - Sprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Platform.h"

//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Platform::Platform(RECT& rcPosition, Bitmap* pBitmap)
{
    // Initialize the member variables
    m_rcPosition = rcPosition;
    m_pBitmap = pBitmap;
}

Platform::~Platform()
{
}

void Platform::Draw(HDC hDC)
{
    // Draw the sprite if it isn't hidden
    if (m_pBitmap != NULL)
        m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, TRUE);
}
