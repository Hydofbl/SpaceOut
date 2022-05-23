//-----------------------------------------------------------------
// Space Out Application
// C++ Source - SpaceOut.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceOut.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
    // _pGame = new GameEngine(hInstance, TEXT("Oyun Adi"), TEXT("Oyun Adi"), LOGO_NORMAL, LOGO_SMALL, X_BOYUTU, Y_BOYUTU);
  // Create the game engine
    _pGame = new GameEngine(hInstance, TEXT("Oyun"),
        TEXT("Oyun"), IDI_LOGO, IDI_LOGO_SM, 1250, 800);
    if (_pGame == NULL)
        return FALSE;

    // Set the frame rate
    _pGame->SetFrameRate(30);

    // Store the instance handle
    _hInstance = hInstance;

    return TRUE;
}

void GameStart(HWND hWindow)
{
    // Seed the random number generator
    srand(GetTickCount());

    // Create the offscreen device context and bitmap
    _hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
    _hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
        _pGame->GetWidth(), _pGame->GetHeight());
    SelectObject(_hOffscreenDC, _hOffscreenBitmap);

    // Create and load the bitmaps
    HDC hDC = GetDC(hWindow);
    _pPlayerBitmap = new Bitmap(hDC, IDB_PLAYER, _hInstance);
    _pSmPlayerBitmap = new Bitmap(hDC, IDB_SMPLAYER, _hInstance);
    _pGameOverBitmap = new Bitmap(hDC, IDB_GAMEOVER, _hInstance);
    _pWallBitmap = new Bitmap(hDC, IDB_WALL, _hInstance);
    _pStairBitmap = new Bitmap(hDC, IDB_STAIR, _hInstance);

    missileBitmap = new Bitmap(hDC, IDB_MISSILE, _hInstance);
    heartBitmap = new Bitmap(hDC, IDB_HEART, _hInstance);
    keyBitmap = new Bitmap(hDC, IDB_KEY, _hInstance);
    doorBitmap = new Bitmap(hDC, IDB_DOOR, _hInstance);
    mageBitmap = new Bitmap(hDC, IDB_MAGE, _hInstance);
    mageMissileBitmap = new Bitmap(hDC, IDB_MAGEMISSILE, _hInstance);
    batBitmap = new Bitmap(hDC, IDB_BAT, _hInstance);
    batMissileBitmap = new Bitmap(hDC, IDB_BATMISSILE, _hInstance);
    bomberBitmap = new Bitmap(hDC, IDB_BOMBER, _hInstance);
    bomberBombBitmap = new Bitmap(hDC, IDB_BOMBERBOMB, _hInstance);

    // Create the starry background
    _pBackground = new StarryBackground(1250, 800);

    // Play the background music
    //_pGame->PlayMIDISong(TEXT("Music.mid"));

    // Start the game
    NewGame();
}

void GameEnd()
{
    // Close the MIDI player for the background music
    //_pGame->CloseMIDIPlayer();

    // Cleanup the offscreen device context and bitmap
    DeleteObject(_hOffscreenBitmap);
    DeleteDC(_hOffscreenDC);

    // Cleanup the bitmaps
    delete _pPlayerBitmap;
    delete _pSmPlayerBitmap;
    delete _pGameOverBitmap;
    delete _pWallBitmap;
    delete _pStairBitmap;
    delete heartBitmap;
    delete keyBitmap;
    delete doorBitmap;
    delete mageBitmap;
    delete mageMissileBitmap;

    /*
    delete _pPlatform[];
    delete _pStair[];
    */

    // Cleanup the background
    delete _pBackground;

    // Cleanup the sprites
    _pGame->CleanupSprites();

    // Cleanup the game engine
    delete _pGame;
}

void GameActivate(HWND hWindow)
{
    // Resume the background music
    //_pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
    // Pause the background music
    //_pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{
    // Draw the background
    _pBackground->Draw(hDC);

    // Draw the sprites
    _pGame->DrawSprites(hDC);


    // Drawing platforms
    // Boundaries
    // Top
    for (int i = 0; i < 50; i++)
    {
        _pWallBitmap->Draw(hDC, _pWallBitmap->GetWidth() * i,
            _pWallBitmap->GetHeight(), TRUE);
    }
    // Bottom
    for (int i = 0; i < 50; i++)
    {
        _pWallBitmap->Draw(hDC, _pWallBitmap->GetWidth() * i,
            _pGame->GetHeight() - _pWallBitmap->GetHeight() * 2, TRUE);
    }
    // Left
    for (int i = 0; i < 30; i++)
    {
        _pWallBitmap->Draw(hDC, 0,
            (_pWallBitmap->GetHeight() * i) + 25, TRUE);
    }
    // Right
    for (int i = 0; i < 30; i++)
    {
        _pWallBitmap->Draw(hDC, _pGame->GetWidth() - _pWallBitmap->GetWidth(),
            (_pWallBitmap->GetHeight() * i) + 25, TRUE);
    }


    RECT rcPosition = { 0,0,0,0 };
    int num = 6, temp = 0;

    for (int j = 0; j < 20; j++)
    {
        _pWallBitmap->Draw(hDC, 0 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 19)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 10; j++)
    {
        _pWallBitmap->Draw(hDC, 575 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 575 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 575 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 9)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 11; j++)
    {
        _pWallBitmap->Draw(hDC, 950 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 950 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 950 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    //second floor
    num--;

    for (int j = 0; j < 1; j++)
    {
        _pWallBitmap->Draw(hDC, 25 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 25 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 25 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 30; j++)
    {
        _pWallBitmap->Draw(hDC, 200 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 200 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 200 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 15)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 3; j++)
    {
        _pWallBitmap->Draw(hDC, 1150 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 1150 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 1150 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    //Third floor
    num--;

    for (int j = 0; j < 20; j++)
    {
        _pWallBitmap->Draw(hDC, 25 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 25 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 25 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 19)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 7; j++)
    {
        _pWallBitmap->Draw(hDC, 875 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 875 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 875 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 7; j++)
    {
        _pWallBitmap->Draw(hDC, 1100 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 1100 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 1100 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 5)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }


    //Forth floor
    num--;

    for (int j = 0; j < 2; j++)
    {
        _pWallBitmap->Draw(hDC, 25 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 25 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 25 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();
    }

    for (int j = 0; j < 3; j++)
    {
        _pWallBitmap->Draw(hDC, 275 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 275 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 275 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 32; j++)
    {
        _pWallBitmap->Draw(hDC, 425 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 425 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 425 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    //Fifth floor
    num--;

    for (int j = 0; j < 12; j++)
    {
        _pWallBitmap->Draw(hDC, 25 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 25 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 25 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 11)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 12; j++)
    {
        _pWallBitmap->Draw(hDC, 575 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 575 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 575 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();


        if (j != 0 && j != 11)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 6; j++)
    {
        _pWallBitmap->Draw(hDC, 1125 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 1125 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 1125 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 3)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    //Sixth floor
    num--;

    for (int j = 0; j < 25; j++)
    {
        _pWallBitmap->Draw(hDC, 25 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 25 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 25 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();

        if (j != 24)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 8; j++)
    {
        _pWallBitmap->Draw(hDC, 775 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 775 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 775 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();


        if (j != 0)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }

    for (int j = 0; j < 8; j++)
    {
        _pWallBitmap->Draw(hDC, 1075 + (_pWallBitmap->GetWidth() * j),
            _platformHeight * num + _pWallBitmap->GetHeight(), TRUE);

        rcPosition.left = 1075 + _pWallBitmap->GetWidth() * j;
        rcPosition.top = _platformHeight * num + _pWallBitmap->GetHeight();
        rcPosition.right = 1075 + _pWallBitmap->GetWidth() * j + _pWallBitmap->GetWidth();
        rcPosition.bottom = _platformHeight * num + _pWallBitmap->GetHeight() + _pWallBitmap->GetHeight();


        if (j != 2)
            _pPlatform[temp++] = new Platform(rcPosition, _pWallBitmap);
    }


    // for stair ; 1. floor
    int wall_x_length = 25;
    double s_num = 800 / (5.99 * wall_x_length);
    temp = 0;

    // 1. stair 
    _pStairBitmap->Draw(hDC, (18 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (18 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (18 * wall_x_length) + (_pStairBitmap->GetWidth()) + (_pStairBitmap->GetWidth());
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);


    // 2. stair 
    _pStairBitmap->Draw(hDC, (31 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (31 * wall_x_length) + _pStairBitmap->GetWidth();
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (31 * wall_x_length) + _pStairBitmap->GetWidth() + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 3. stair 
    _pStairBitmap->Draw(hDC, (37 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (37 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (37 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    s_num--; // 5

    // 4.stair

    _pStairBitmap->Draw(hDC, (0 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (0 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (0 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 6.stair
    _pStairBitmap->Draw(hDC, (22 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (22 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (22 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 7.stair

    _pStairBitmap->Draw(hDC, (45 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (45 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (45 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    s_num--; // 4

    // 8.stair
    _pStairBitmap->Draw(hDC, (19 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (19 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (19 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 9.stair
    _pStairBitmap->Draw(hDC, (34 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (34 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (34 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 10.stair

    _pStairBitmap->Draw(hDC, (47 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (47 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (47 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    s_num--; // 3

    // 11.stair 

    _pStairBitmap->Draw(hDC, (10 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (10 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (10 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 12.stair 

    _pStairBitmap->Draw(hDC, (16 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (16 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (16 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    s_num--; // 2

    // 15.stair

    _pStairBitmap->Draw(hDC, (11 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (11 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (11 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);


    // 16.stair

    _pStairBitmap->Draw(hDC, (22 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (22 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (22 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 17.stair
    _pStairBitmap->Draw(hDC, (33 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);


    rcPosition.left = (33 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (33 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 18.stair

    _pStairBitmap->Draw(hDC, (47 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (47 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (47 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    s_num--; // 1

    // 20.stair
    _pStairBitmap->Draw(hDC, (24 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (24 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (24 * wall_x_length) + (_pStairBitmap->GetWidth() + _pStairBitmap->GetWidth());
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 21.stair

    _pStairBitmap->Draw(hDC, (30 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (30 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (30 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    // 22.stair

    _pStairBitmap->Draw(hDC, (44 * wall_x_length) + (_pStairBitmap->GetWidth()),
        _platformHeight * s_num + _pStairBitmap->GetHeight(), TRUE);

    rcPosition.left = (44 * wall_x_length) + (_pStairBitmap->GetWidth());
    rcPosition.top = _platformHeight * s_num + _pStairBitmap->GetHeight();
    rcPosition.right = (44 * wall_x_length) + (_pStairBitmap->GetWidth()) + _pStairBitmap->GetWidth();
    rcPosition.bottom = _platformHeight * s_num + _pStairBitmap->GetHeight() + _pStairBitmap->GetHeight();

    _pStair[temp++] = new Stair(rcPosition, _pStairBitmap);

    if (s_num == 0)
        s_num = 800 / (6 * wall_x_length);



    // Draw the number of remaining lives (cars)
    for (int i = 0; i < _iNumLives; i++)
        heartBitmap->Draw(hDC, 1150 + (heartBitmap->GetWidth() * i) + 10,
            10, TRUE);

    // Draw the game over message, if necessary
    if (_bGameOver)
        _pGameOverBitmap->Draw(hDC, 190, 149, TRUE);

    POINT ptVelocity = _pPlayerSprite->GetVelocity();
    RECT  rcPos = _pPlayerSprite->GetPosition();
    TCHAR szText[128];
    wsprintf(szText, "%d", isCollide);

    TextOut(hDC, 10, 10, szText, strlen(szText));

    TCHAR szText2[128];
    wsprintf(szText2, "position:%d", rcPos.left);

    TextOut(hDC, 50, 50, szText2, strlen(szText2));

    TCHAR szText3[128];
    wsprintf(szText3, "position-y:%d", rcPos.top);

    TextOut(hDC, 80, 80, szText3, strlen(szText3));
}

void GameCycle()
{
    if (!_bGameOver)
    {
        // Update the background
        _pBackground->Update();

        // Update the sprites
        _pGame->UpdateSprites();

        // Obtain a device context for repainting the game
        HWND  hWindow = _pGame->GetWindow();
        HDC   hDC = GetDC(hWindow);

        // Paint the game to the offscreen device context
        GamePaint(_hOffscreenDC);

        isOnLadderFunc();

        for (int i = 0; i < numOfPlatforms; i++)
        {
            Collide(_pPlayerSprite, _pPlatform[i]);
        }

        // Blit the offscreen bitmap to the game screen
        BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
            _hOffscreenDC, 0, 0, SRCCOPY);

        // Cleanup
        ReleaseDC(hWindow, hDC);
    }
}

void HandleKeys()
{
    if (!_bGameOver)
    {
        // Move the player based upon which key presses
        POINT ptVelocity = _pPlayerSprite->GetVelocity();

        if (GetAsyncKeyState(VK_LEFT) >= 0 && GetAsyncKeyState(VK_RIGHT) >= 0)
        {
            if (ptVelocity.x > 0)
            {
                ptVelocity.x -= HORIZONTALGRIP;
                _pPlayerSprite->SetVelocity(ptVelocity);
            }
            else if (ptVelocity.x < 0)
            {
                ptVelocity.x += HORIZONTALGRIP;
                _pPlayerSprite->SetVelocity(ptVelocity);
            }
        }

        // Düzenle
        if (_pPlayerSprite->GetPosition().top + _pPlayerBitmap->GetHeight() / 2 != 729)
        {
            if (ptVelocity.y != MAXJUMPSPEED) {

                if (ptVelocity.y < MAXJUMPSPEED) {
                    ptVelocity.y += GRAVITY;
                }
                else {
                    ptVelocity.y = MAXJUMPSPEED;
                }
                _pPlayerSprite->SetVelocity(ptVelocity);
            }
        }
        else {
            ptVelocity.y = 0;
        }

        if (GetAsyncKeyState(VK_LEFT) < 0)
        {
            // Move left
            ptVelocity.x = max(ptVelocity.x - 1, -8);
            _pPlayerSprite->SetVelocity(ptVelocity);
        }
        else if (GetAsyncKeyState(VK_RIGHT) < 0)
        {
            // Move right
            ptVelocity.x = min(ptVelocity.x + 2, 8);
            _pPlayerSprite->SetVelocity(ptVelocity);
        }

        if (GetAsyncKeyState(VK_UP) < 0)
        {
            if (isOnStair)
            {
                // Move up
                ptVelocity.y = -MAXLADDERSPEED;
                _pPlayerSprite->SetVelocity(ptVelocity);
            }
            else
            {
                if (!isJumpPressed) {
                    ptVelocity.y = min(-MAXJUMPSPEED, --ptVelocity.y);
                    _pPlayerSprite->SetVelocity(ptVelocity);
                    isJumpPressed = true;
                }
            }
        }

        // Collision'a baðlý olarak bunu saðlamak lazým düzenle!!!
        if (GetAsyncKeyState(VK_UP) >= 0)
            isJumpPressed = false;

    }
    // Start a new game based upon an Enter (Return) key press
    if (_bGameOver && (GetAsyncKeyState(VK_RETURN) < 0))
        // Start a new game
        NewGame();
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{

}

void MouseButtonUp(int x, int y, BOOL bLeft)
{

}

void MouseMove(int x, int y)
{

}

void HandleJoystick(JOYSTATE jsJoystickState)
{

}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
    // See if a player missile and an alien have collided
    Bitmap* pHitter = pSpriteHitter->GetBitmap();
    Bitmap* pHittee = pSpriteHittee->GetBitmap();

    // See if an alien missile has collided with the car
    if ((pHitter == _pPlayerBitmap && (pHittee == heartBitmap || pHittee == keyBitmap)) ||
      (pHittee == _pPlayerBitmap && (pHitter == heartBitmap || pHitter == keyBitmap)))
    {
        /*
      // Play the large explosion sound
      PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
        SND_RESOURCE);
      */

      // Kill the missile sprite
        if (pHitter == _pPlayerBitmap) {
            if (pHittee == heartBitmap && _iNumLives != MAXLIVE) {
                _iNumLives++;
                /*
                // Move the player back to the start
                else if (pHittee == missileBitmap)
                    _pPlayerSprite->SetPosition(300, 405);
                    */
                pSpriteHittee->Kill();
            }
            else if (pHittee == keyBitmap) {

                pSpriteHittee->Kill();
            }
        }
        else {
            if (pHitter == heartBitmap && _iNumLives != MAXLIVE) {
                _iNumLives++;
                /*
                // Move the player back to the start
                else if (pHittee == missileBitmap)
                    _pPlayerSprite->SetPosition(300, 405);
                    */
                pSpriteHitter->Kill();
            }
            else if (pHitter == keyBitmap) {

                pSpriteHitter->Kill();
            }
        }

      /*
      // See if the game is over
      if (--_iNumLives == 0)
      {
        // Play the game over sound
        PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
          SND_RESOURCE);
        
        _bGameOver = TRUE;
      }
        */
    }
    else if ((pHitter == _pPlayerBitmap && pHittee == doorBitmap) ||
        (pHittee == _pPlayerBitmap && pHitter == doorBitmap))
    {
        /**/
    }
    else if ((pHitter == _pPlayerBitmap && (pHittee == mageMissileBitmap || pHittee == batMissileBitmap || pHittee == bomberBombBitmap)) ||
        (pHittee == _pPlayerBitmap && (pHitter == mageMissileBitmap || pHitter == batMissileBitmap || pHittee == bomberBombBitmap)))
    {
        if (pHitter == _pPlayerBitmap) {
            pSpriteHittee->Kill();

            if (--_iNumLives == 0)
            {
                _bGameOver = TRUE;
            }
        }
        else {
            pSpriteHitter->Kill();

            if (--_iNumLives == 0)
            {
                _bGameOver = TRUE;
            }
        }
    }

    // Swap the sprite velocities so that they appear to bounce
      /*
      POINT ptSwapVelocity = pSpriteHitter->GetVelocity();
      pSpriteHitter->SetVelocity(pSpriteHittee->GetVelocity());
      pSpriteHittee->SetVelocity(ptSwapVelocity);
      */

    return FALSE;
}

void SpriteDying(Sprite* pSprite)
{
    /*
    // See if an alien missile sprite is dying
    if (pSprite->GetBitmap() == _pBMissileBitmap ||
      pSprite->GetBitmap() == _pJMissileBitmap ||
      pSprite->GetBitmap() == _pTMissileBitmap)
    {
      // Play the small explosion sound
      PlaySound((LPCSTR)IDW_SMEXPLODE, _hInstance, SND_ASYNC |
        SND_RESOURCE | SND_NOSTOP);

      // Create a small explosion sprite at the missile's position
      RECT rcBounds = { 0, 0, 600, 450 };
      RECT rcPos = pSprite->GetPosition();
      Sprite* pSprite = new Sprite(_pSmExplosionBitmap, rcBounds);
      pSprite->SetNumFrames(8, TRUE);
      pSprite->SetPosition(rcPos.left, rcPos.top);
      _pGame->AddSprite(pSprite);
    }
    */
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
    // Clear the sprites
    _pGame->CleanupSprites();

    // Create the player sprite 
    // Boundaries(left, top, right, bottom)
    RECT rcBounds = { _pWallBitmap->GetWidth(), _pWallBitmap->GetHeight(),
        _pGame->GetWidth() - _pWallBitmap->GetWidth(), _pGame->GetHeight() - _pWallBitmap->GetHeight() * 2 };
    _pPlayerSprite = new Sprite(_pPlayerBitmap, rcBounds, BA_STOP);
    _pPlayerSprite->SetPosition(300, 405);
    _pGame->AddSprite(_pPlayerSprite);

    heartSprite = new Sprite(heartBitmap, rcBounds, BA_STOP);
    heartSprite->SetPosition(18 + heartBitmap->GetWidth(), 530);
    _pGame->AddSprite(heartSprite);

    heartSprite = new Sprite(heartBitmap, rcBounds, BA_STOP);
    heartSprite->SetPosition(684 + heartBitmap->GetWidth(), 490);
    _pGame->AddSprite(heartSprite);

    heartSprite = new Sprite(heartBitmap, rcBounds, BA_STOP);
    heartSprite->SetPosition(1115 + heartBitmap->GetWidth(), 110);
    _pGame->AddSprite(heartSprite);

    keySprite = new Sprite(keyBitmap, rcBounds, BA_STOP);
    keySprite->SetPosition(400, 400);
    _pGame->AddSprite(keySprite);

    doorSprite = new Sprite(doorBitmap, rcBounds, BA_STOP);
    doorSprite->SetPosition(_pWallBitmap->GetWidth(), 65);
    _pGame->AddSprite(doorSprite);

    RECT          rcBounds2 = { 0, 0, 1250, 800 };
    AlienSprite* pSprite;
    pSprite = new AlienSprite(mageBitmap, rcBounds2, BA_STOP);
    pSprite->SetPosition(mageBitmap->GetWidth(), 295);
    _pGame->AddSprite(pSprite);

    RECT          rcBounds3 = { 400, 0, 800, 800 };
    pSprite = new AlienSprite(batBitmap, rcBounds3, BA_BOUNCE);
    pSprite->SetPosition(410, 300);
    pSprite->SetVelocity(-5,0);
    _pGame->AddSprite(pSprite); 
    
    RECT          rcBounds4 = { 400, 0, 800, 800 };
    pSprite = new AlienSprite(bomberBitmap, rcBounds4, BA_BOUNCE);
    pSprite->SetPosition(300 + (bomberBitmap->GetWidth()), 510);
    pSprite->SetVelocity(-4, 0);
    _pGame->AddSprite(pSprite);

    // Initialize the game variables
    _iFireInputDelay = 0;
    _iScore = 0;
    _iNumLives = 3;
    _bGameOver = FALSE;
    isOnStair = false;
    whichStair = -1;
    isCollide = 0;
    collideBottom = false;
    collideTop = false;
    _iDifficulty = 40;

    // Play the background music
    //_pGame->PlayMIDISong();
}

void isOnLadderFunc() {
    if (whichStair == -1) {
        for (int i = 0; i < 22; i++)
        {
            RECT StairPos = _pStair[i]->GetPosition();
            RECT playerPos = _pPlayerSprite->GetPosition();

            if (StairPos.left <= playerPos.left + _pPlayerBitmap->GetWidth() / 2 &&
                StairPos.right >= playerPos.left + _pPlayerBitmap->GetWidth() / 2 &&
                StairPos.top <= playerPos.bottom &&
                StairPos.bottom >= playerPos.top)
            {
                isOnStair = true;
                whichStair = i;
                break;
            }
        }
    }
    else {
        RECT StairPos = _pStair[whichStair]->GetPosition();
        RECT playerPos = _pPlayerSprite->GetPosition();

        if (!(StairPos.left <= playerPos.left + _pPlayerBitmap->GetWidth() / 2 &&
            StairPos.right >= playerPos.left + _pPlayerBitmap->GetWidth() / 2 &&
            StairPos.top <= playerPos.bottom &&
            StairPos.bottom >= playerPos.top))
        {
            isOnStair = false;
            whichStair = -1;
        }
    }

}

void Collide(Sprite* player, Platform* platform) {
    RECT playerPos = player->GetPosition();
    RECT platformPos = platform->GetPosition();
    platformPos.top -= 10;

    // collide olduðu platforma kilitleyip diðerlerinin kontrolünü kapayabiliriz. Bunun için paltform tutucu bir number ekle ve
    // collision bitene kadar onu kontrol et sadece. Bitince de collide'ý false yap ve diðerlerini kontrole devam et.

    if (playerPos.left <= platformPos.right &&
        playerPos.right >= platformPos.left)
    {
        if (playerPos.top <= platformPos.bottom &&
            playerPos.bottom >= platformPos.top)
        {
            isCollide = 1;
        }
        else {
            isCollide = 0;
        }
        if (playerPos.top < platformPos.bottom && playerPos.top > platformPos.top)
        {
            collideBottom = true;
        }
        else {
            collideBottom = false;
        }
        if (playerPos.bottom > platformPos.top && playerPos.bottom < platformPos.bottom)
        {
            collideTop = true;
        }
        else {
            collideTop = false;
        }

        if (isCollide == 1) {

            if (player->GetVelocity().y > 0 && collideTop) {
                POINT ptNewPosition;
                ptNewPosition.x = playerPos.left;
                ptNewPosition.y = platformPos.top - player->GetBitmap()->GetHeight();
                player->SetPosition(ptNewPosition);
            }
            if (player->GetVelocity().y < 0 && collideBottom) {
                POINT ptNewPosition;
                ptNewPosition.x = playerPos.left;
                ptNewPosition.y = platformPos.bottom;
                player->SetPosition(ptNewPosition);
            }

        }
    }
}
