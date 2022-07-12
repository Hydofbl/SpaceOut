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
class Stair
{
protected:
    // Member Variables
    Bitmap* m_pBitmap;
public: RECT          m_rcPosition;

public:
    // Constructor(s)/Destructor
    Stair(RECT& rcPosition, Bitmap* pBitmap);
    virtual ~Stair();

    // General Methods
    void          Draw(HDC hDC);

    // Accessor Methods
    RECT& GetPosition() { return m_rcPosition; };
};