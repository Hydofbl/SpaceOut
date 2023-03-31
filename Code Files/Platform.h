//-----------------------------------------------------------------
// Sprite Object
// C++ Header - Sprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Bitmap.h"

//-----------------------------------------------------------------
// Sprite Class
//-----------------------------------------------------------------
class Platform
{
protected:
    // Member Variables
    Bitmap* m_pBitmap;
    RECT          m_rcPosition;

public:
    // Constructor(s)/Destructor
    Platform(RECT& rcPosition, Bitmap* pBitmap);
    virtual ~Platform();

    // General Methods
    void          Draw(HDC hDC);

    // Accessor Methods
    RECT& GetPosition() { return m_rcPosition; };

    Bitmap* GetBitmap() { return m_pBitmap; };
};