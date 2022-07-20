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
        TEXT("Oyun"), IDI_LOGO, IDI_LOGO_SM, 1260, 770);
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
    //srand(5);

    // Create the offscreen device context and bitmap
    _hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
    _hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
        _pGame->GetWidth(), _pGame->GetHeight());
    SelectObject(_hOffscreenDC, _hOffscreenBitmap);

    // Create and load the bitmaps
    HDC hDC = GetDC(hWindow);
    _pPlayerBitmap = new Bitmap(hDC, IDB_PLAYER, _hInstance);
    _pGameOverBitmap = new Bitmap(hDC, IDB_GAMEOVER, _hInstance);
    _bGameWonBitmap = new Bitmap(hDC, IDB_GAMEWON, _hInstance);
    _pWallBitmap = new Bitmap(hDC, IDB_WALL, _hInstance);
    _pStairBitmap = new Bitmap(hDC, IDB_STAIR, _hInstance);

    heartBitmap = new Bitmap(hDC, IDB_HEART, _hInstance);
    heartEmptyBitmap = new Bitmap(hDC, IDB_HEARTEMPTY, _hInstance);
    keyBitmap = new Bitmap(hDC, IDB_KEY, _hInstance);
    keyUIBitmap = new Bitmap(hDC, IDB_KEYHORIZONTAL, _hInstance);
    doorBitmap = new Bitmap(hDC, IDB_DOOR, _hInstance);

    mageBitmap = new Bitmap(hDC, IDB_MAGE, _hInstance);
    mageMissileBitmap = new Bitmap(hDC, IDB_MAGEMISSILE, _hInstance);
    batBitmap = new Bitmap(hDC, IDB_BAT, _hInstance);
    batMissileBitmap = new Bitmap(hDC, IDB_BATMISSILE, _hInstance);
    bomberBitmap = new Bitmap(hDC, IDB_BOMBER, _hInstance);
    bomberBombBitmap = new Bitmap(hDC, IDB_BOMBERBOMB, _hInstance);
    gollumBitmap = new Bitmap(hDC, IDB_GOLLUM, _hInstance);
    ghostBitmap = new Bitmap(hDC, IDB_GHOST, _hInstance);

    shieldBitmap = new Bitmap(hDC, IDB_SHIELD, _hInstance);
    _pMissileBitmap = new Bitmap(hDC, IDB_MISSILE, _hInstance);
    fireballCollectibleBitmap = new Bitmap(hDC, IDB_FIREBALLICON, _hInstance);

    gameTitleBitmap = new Bitmap(hDC, IDB_GAMETITLE, _hInstance);
    playButtonBitmap = new Bitmap(hDC, IDB_PLAYBUTTON, _hInstance);

    // Create the starry background
    _pBackground = new StarryBackground(1250, 800);

    // Play the background music
    _pGame->PlayMIDISong(TEXT("Music.mid"));

    // Start the game
    NewGame();
}

void GameEnd()
{
    // Close the MIDI player for the background music
    _pGame->CloseMIDIPlayer();

    // Cleanup the offscreen device context and bitmap
    DeleteObject(_hOffscreenBitmap);
    DeleteDC(_hOffscreenDC);

    // Cleanup the bitmaps
    delete _pPlayerBitmap;
    delete _pGameOverBitmap;
    delete _pWallBitmap;
    delete _pStairBitmap;
    delete heartBitmap;
    delete heartEmptyBitmap;
    delete keyBitmap;
    delete keyUIBitmap;
    delete doorBitmap;
    delete mageBitmap;
    delete mageMissileBitmap;
    delete batBitmap;
    delete batMissileBitmap;
    delete bomberBitmap;
    delete bomberBombBitmap;
    delete gollumBitmap;
    delete ghostBitmap;
    delete shieldBitmap;
    delete _pMissileBitmap;
    delete fireballCollectibleBitmap;
    delete gameTitleBitmap;
    delete playButtonBitmap;

    for (int i = 0; i < numOfPlatformsDynmc; i++)
    {
        delete _pPlatform[i];
    }
    for (int i = 0; i < numOfStairsDynmc; i++)
    {
        delete _pStair[i];
    }

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
    _pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
    // Pause the background music
    _pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{
    // Draw the background
    _pBackground->Draw(hDC);

    if (!_bGameOver && !_bGameWon)
    {
        if (!_bGameMenu)
        {
            for (int y = 0; y < 29; y++)
            {
                for (int x = 0; x < 50; x++)
                {
                    if (map[y][x] == 1)
                    {
                        _pWallBitmap->Draw(hDC, _pWallBitmap->GetWidth() * x,
                            _pWallBitmap->GetHeight() * y + 25, TRUE);
                    }
                    else if (map[y][x] == 2)
                    {
                        _pStairBitmap->Draw(hDC, _pStairBitmap->GetWidth() * x,
                            25 * y + 25, TRUE);
                    }
                }
            }

            // Draw the sprites
            _pGame->DrawSprites(hDC);

            TCHAR szText[128];

            wsprintf(szText, "Lives: ");

            TextOut(hDC, 1040, 5, szText, strlen(szText));

            // Draw the number of remaining lives
            for (int i = 0; i < MAXLIVE; i++)
            {
                if (i < _iNumLives)
                    heartBitmap->Draw(hDC, 1100 + (heartBitmap->GetWidth() * i) + 10,
                        7, TRUE);
                else
                    heartEmptyBitmap->Draw(hDC, 1100 + (heartEmptyBitmap->GetWidth() * i) + 10,
                        7, TRUE);
            }

            wsprintf(szText, "Key Needed: ");

            TextOut(hDC, 50, 5, szText, strlen(szText));

            // Draw the number of remaining keys
            for (int i = 0; i < keyNeeded - keyAmount; i++)
                keyUIBitmap->Draw(hDC, 160 + (keyUIBitmap->GetWidth() * i), 7, TRUE);

            wsprintf(szText, "Fireball Amount: %dx", fireballAmount);

            TextOut(hDC, 600, 5, szText, strlen(szText));

            fireballCollectibleBitmap->Draw(hDC, 730, 8, TRUE);

            wsprintf(szText, "Level: %d", level);

            TextOut(hDC, 420, 5, szText, strlen(szText));
        }
        else
        {
            gameTitleBitmap->Draw(hDC, 300,  150, TRUE);
            playButtonBitmap->Draw(hDC, 600,  500, TRUE);

            playButtonX = 600;
            playButtonY = 500;
        }
    }


    // Draw the game over message, if necessary
    if (_bGameOver) {
        _pGameOverBitmap->Draw(hDC, 525, 325, TRUE);

        // Pause the background music
        _pGame->PauseMIDISong();
    }

    // Draw the game won message, if necessary
    if (_bGameWon) {
        _bGameWonBitmap->Draw(hDC, 525, 325, TRUE);

        // Pause the background music
        _pGame->PauseMIDISong();
    }
}

void GameCycle()
{
    if (!_bGameOver && !_bGameWon)
    {
        // Update the background
        _pBackground->Update();

        // Obtain a device context for repainting the game
        HWND  hWindow = _pGame->GetWindow();
        HDC   hDC = GetDC(hWindow);

        // Paint the game to the offscreen device context
        GamePaint(_hOffscreenDC);

        if (!_bGameMenu) 
        {
            isOnLadderFunc();
            CheckGround();
            FacingWhere();
            Collide();

            // Update the sprites
            _pGame->UpdateSprites();
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
    if (!_bGameOver && !_bGameWon)
    {
        if (!_bGameMenu)
        {
            // Move the player based upon which key presses
            POINT ptVelocity = _pPlayerSprite->GetVelocity();

            if (GetAsyncKeyState('A') >= 0 && GetAsyncKeyState('D') >= 0)
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

            if (_pPlayerSprite->GetPosition().bottom != _pPlayerSprite->GetBounds().bottom)
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

            if (GetAsyncKeyState('A') < 0)
            {
                // Move left
                ptVelocity.x = max(ptVelocity.x - 1, -8);
                _pPlayerSprite->SetVelocity(ptVelocity);
            }
            else if (GetAsyncKeyState('D') < 0)
            {
                // Move right
                ptVelocity.x = min(ptVelocity.x + 2, 8);
                _pPlayerSprite->SetVelocity(ptVelocity);
            }

            if (GetAsyncKeyState('W') < 0)
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

                        // Play the jump sound
                        PlaySound((LPCSTR)IDW_JUMP, _hInstance, SND_ASYNC |
                            SND_RESOURCE);
                    }
                }
            }

            // Ýnfinite jump açýk !! Ground check'te sýkýntý olabiliyor konumlarý check et.
            if (GetAsyncKeyState('W') >= 0 && isOnGrounded)
                isJumpPressed = false;


            // if space button pressed use shield
            if (shieldSprite->IsHidden()) {
                if (canUseShield) {   // D
                    if ((++shieldInputDelay > shieldMaxDelay) && GetAsyncKeyState('P') < 0) {
                        shieldSprite->SetHidden(false);

                        canUseShield = false;


                        // Reset the input delay
                        shieldInputDelay = 0;
                    }
                }
            }
            else {
                if ((++shieldUsageDelay > shieldUsageMaxDelay)) {
                    CloseShield();
                }
            }

            // Fire missiles based upon spacebar presses    // S
            if ((++_iFireInputDelay > _iFireMaxDelay) && GetAsyncKeyState(' ') < 0 && fireballAmount > 0)
            {
                // Create a new missile sprite
                RECT  rcBounds = { 0, 0, 1250, 800 };
                RECT  rcPos = _pPlayerSprite->GetPosition();
                Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);

                if (facingRight)
                {
                    pSprite->SetPosition(rcPos.right, _pPlayerSprite->GetPosition().bottom - _pPlayerBitmap->GetHeight() / 2);
                    pSprite->SetVelocity(7, 0);
                }
                else
                {
                    pSprite->SetPosition(rcPos.left, _pPlayerSprite->GetPosition().bottom - _pPlayerBitmap->GetHeight() / 2);
                    pSprite->SetVelocity(-7, 0);
                }

                _pGame->AddSprite(pSprite);
                /*
                // Play the missile (fire) sound
                PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC |
                    SND_RESOURCE | SND_NOSTOP);
                    */

                    // Reset the input delay
                _iFireInputDelay = 0;
                fireballAmount--;
            }
        }
    }
    // Start a new game based upon an Enter (Return) key press
    if ((_bGameOver || _bGameWon) && (GetAsyncKeyState(VK_RETURN) < 0)) 
    {
        // Start a new game
        NewGame();
    }
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
    if (_bGameMenu)
    {
        if (bLeft)
        {
            if (x > playButtonX && x < playButtonX + playButtonBitmap->GetWidth() &&
                y > playButtonY && y < playButtonY + playButtonBitmap->GetHeight())
            {
                _bGameMenu = false;
            }
        }
    }
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
    if ((pHitter == _pPlayerBitmap && (pHittee == heartBitmap || pHittee == keyBitmap || pHittee == fireballCollectibleBitmap)) ||
        (pHittee == _pPlayerBitmap && (pHitter == heartBitmap || pHitter == keyBitmap || pHitter == fireballCollectibleBitmap)))
    {
        if (pHitter == _pPlayerBitmap) {
            if (pHittee == heartBitmap && _iNumLives != MAXLIVE) {
                _iNumLives++;
                // Play the healing sound
                PlaySound((LPCSTR)IDW_HEAL, _hInstance, SND_ASYNC |
                    SND_RESOURCE);
                pSpriteHittee->Kill();
            }
            else if (pHittee == keyBitmap) {

                pSpriteHittee->Kill();
                keyAmount++;
                // Play the healing sound
                PlaySound((LPCSTR)IDW_KEY, _hInstance, SND_ASYNC |
                    SND_RESOURCE);

                if (keyAmount == keyNeeded) {
                    // Play the game over sound
                    PlaySound((LPCSTR)IDW_DOOROPEN, _hInstance, SND_ASYNC |
                        SND_RESOURCE);
                }
            }
            else if (pHittee == fireballCollectibleBitmap) {
                pSpriteHittee->Kill();
                fireballAmount++;
            }
        }
        else {
            if (pHitter == heartBitmap && _iNumLives != MAXLIVE) {
                _iNumLives++;
                pSpriteHitter->Kill();
            }
            else if (pHitter == keyBitmap) {

                pSpriteHitter->Kill();
                keyAmount++;

                if (keyAmount == keyNeeded) {
                    // Play the game over sound
                    PlaySound((LPCSTR)IDW_DOOROPEN, _hInstance, SND_ASYNC |
                        SND_RESOURCE);
                }
            }
            else if (pHitter == fireballCollectibleBitmap) {
                pSpriteHitter->Kill();
                fireballAmount++;
            }
        }
    }
    else if ((pHitter == _pPlayerBitmap && pHittee == doorBitmap) ||
        (pHittee == _pPlayerBitmap && pHitter == doorBitmap))
    {
        if (keyAmount == keyNeeded)
        {
            _bGameWon = TRUE;
            // Play the game over sound
            PlaySound((LPCSTR)IDW_VICTORY, _hInstance, SND_ASYNC |
                SND_RESOURCE);
        }
    }
    else if ((pHitter == _pPlayerBitmap && (pHittee == mageMissileBitmap || pHittee == batMissileBitmap || pHittee == bomberBombBitmap)) ||
        (pHittee == _pPlayerBitmap && (pHitter == mageMissileBitmap || pHitter == batMissileBitmap || pHitter == bomberBombBitmap)))
    {
        if (pHitter == _pPlayerBitmap) {
            pSpriteHittee->Kill();
            // Play the game over sound
            PlaySound((LPCSTR)IDW_DAMAGED, _hInstance, SND_ASYNC |
                SND_RESOURCE);
            if (--_iNumLives == 0)
            {
                // Play the game over sound
                PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
                    SND_RESOURCE);
                _bGameOver = TRUE;
            }
        }
        else {
            pSpriteHitter->Kill();

            PlaySound((LPCSTR)IDW_DAMAGED, _hInstance, SND_ASYNC |
                SND_RESOURCE);
            if (--_iNumLives == 0)
            {
                // Play the game over sound
                PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
                    SND_RESOURCE);
                _bGameOver = TRUE;
            }
        }
    }
    else if ((pHitter == _pPlayerBitmap && (pHittee == mageBitmap || pHittee == batBitmap || pHittee == bomberBitmap || pHittee == gollumBitmap || pHittee == ghostBitmap)) ||
        (pHittee == _pPlayerBitmap && (pHitter == mageBitmap || pHitter == batBitmap || pHitter == bomberBitmap || pHitter == gollumBitmap || pHitter == ghostBitmap)))
    {
        if (pHitter == _pPlayerBitmap) {
            _pPlayerSprite->SetPosition(startPosition);
            PlaySound((LPCSTR)IDW_DAMAGED, _hInstance, SND_ASYNC |
                SND_RESOURCE);
            if (--_iNumLives == 0)
            {
                // Play the game over sound
                PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
                    SND_RESOURCE);
                _bGameOver = TRUE;
            }
        }
        else {
            _pPlayerSprite->SetPosition(startPosition);
            PlaySound((LPCSTR)IDW_DAMAGED, _hInstance, SND_ASYNC |
                SND_RESOURCE);
            if (--_iNumLives == 0)
            {
                // Play the game over sound
                PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
                    SND_RESOURCE);
                _bGameOver = TRUE;
            }
        }
    }
    else if ((pHitter == _pMissileBitmap && (pHittee == mageBitmap || pHittee == batBitmap || pHittee == bomberBitmap || pHittee == gollumBitmap || pHittee == ghostBitmap)) ||
        (pHittee == _pMissileBitmap && (pHitter == mageBitmap || pHitter == batBitmap || pHitter == bomberBitmap || pHitter == gollumBitmap || pHitter == ghostBitmap)))
    {
        if (pHitter == _pMissileBitmap) {
            pSpriteHitter->Kill();
            pSpriteHittee->Kill();
        }
        else {
            pSpriteHitter->Kill();
            pSpriteHittee->Kill();
        }
    }
    else if (((pHitter == shieldBitmap && (pHittee == mageMissileBitmap || pHittee == batMissileBitmap || pHittee == bomberBombBitmap)) ||
        (pHittee == shieldBitmap && (pHitter == mageMissileBitmap || pHitter == batMissileBitmap || pHitter == bomberBombBitmap))) && !shieldSprite->IsHidden())
    {
        if (pHitter == shieldBitmap) {
            pSpriteHittee->Kill();
            PlaySound((LPCSTR)IDW_SHIELDBLOCK, _hInstance, SND_ASYNC |
                SND_RESOURCE);

            CloseShield();
        }
        else {
            pSpriteHitter->Kill();
            PlaySound((LPCSTR)IDW_SHIELDBLOCK, _hInstance, SND_ASYNC |
                SND_RESOURCE);

            CloseShield();
        }
    }
    else if (((pHitter == shieldBitmap && (pHittee == mageBitmap || pHittee == batBitmap || pHittee == bomberBitmap || pHittee == gollumBitmap || pHittee == ghostBitmap)) ||
        (pHittee == shieldBitmap && (pHitter == mageBitmap || pHitter == batBitmap || pHitter == bomberBitmap || pHitter == gollumBitmap || pHitter == ghostBitmap))) && !shieldSprite->IsHidden())
    {
        if (pHitter == shieldBitmap) {
            _pPlayerSprite->SetPosition(startPosition);
            CloseShield();
        }
        else {
            _pPlayerSprite->SetPosition(startPosition);
            CloseShield();

        }
    }
    else if (pHitter == bomberBombBitmap && pHittee == bomberBombBitmap)
    {
        pSpriteHittee->Kill();
    }
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
    RECT rcBounds = { _pWallBitmap->GetWidth(), _pWallBitmap->GetHeight() * 2,
        _pGame->GetWidth() - _pWallBitmap->GetWidth(), _pGame->GetHeight() - _pWallBitmap->GetHeight() * 2 };
    
    _pPlayerSprite = new Sprite(_pPlayerBitmap, rcBounds, BA_STOP);
    _pPlayerSprite->SetPosition(35, 760);
    _pPlayerSprite->SetZOrder(2);
    _pGame->AddSprite(_pPlayerSprite);

    startPosition = _pPlayerSprite->GetPosition();

    shieldSprite = new Shield(shieldBitmap, rcBounds, _pPlayerSprite, BA_STOP);
    shieldSprite->SetPosition(300, 405);
    shieldSprite->SetZOrder(3);
    shieldSprite->SetHidden(true);
    _pGame->AddSprite(shieldSprite);
    

    if (_bGameOver || (!_bGameOver && !_bGameWon)) 
    {
        _bGameMenu = TRUE;
        playButtonX = 0;
        playButtonY = 0;
        level = 1;
        _iNumLives = 3;
        keyNeeded = 1;
        maxGhostAmount = 3;
        fireballAmount = 3;
    }

    if (_bGameWon) 
    {
        level++;

        int k = rand() % 100;
        if (k < 60) 
        {
            keyNeeded++;
        }
            
        if (level % 5 == 0)
            maxGhostAmount++;

        k = rand() % 100;
        if (k < 45 && maxFireballAmount < 5)
            maxFireballAmount++;
    }

    // Initialize the game variables
    _iFireInputDelay = 0;
    keyAmount = 0;
    shieldInputDelay = shieldMaxDelay;
    shieldUsageDelay = shieldUsageMaxDelay;
    canUseShield = true;
    _bGameOver = FALSE;
    _bGameWon = FALSE;
    isOnStair = false;
    isOnGrounded = false;
    whichStair = -1;
    isCollide = 0;
    collideBottom = false;
    collideTop = false; 
    enemyFireRate = 50;
    gameDifficulty = 1 * level;

    // Play the background music
    _pGame->PlayMIDISong();

    CreateMap();
    FillPlatformArray();
    FillStairArray();
}

void AddOtherSprites(int whichSprite, int x, int y, int x1, int x2) {
    RECT          rcBounds = { 25 * x1, 50, 25 * x2, 725 };

    EnemySprite* pSprite;

    if (whichSprite == 3)
    {
        // MAGE
        pSprite = new EnemySprite(mageBitmap, rcBounds, BA_STOP);
        pSprite->SetPosition(mageBitmap->GetWidth() * x, 25 * y +7);
        _pGame->AddSprite(pSprite);
    }
    else if (whichSprite == 4)
    {
        // BAT
        pSprite = new EnemySprite(batBitmap, rcBounds, BA_BOUNCE);
        pSprite->SetPosition(batBitmap->GetWidth() * x, 25 * y + 25);
        pSprite->SetVelocity(-3, 0);
        _pGame->AddSprite(pSprite);
    }
    else if (whichSprite == 5)
    {
        // Bomber
        pSprite = new EnemySprite(bomberBitmap, rcBounds, BA_BOUNCE);
        pSprite->SetPosition(bomberBitmap->GetWidth() * x, 25 * y + 15);
        pSprite->SetVelocity(-3, 0);
        _pGame->AddSprite(pSprite);
    }
    else if (whichSprite == 6)
    {
        //gollum
        rcBounds.bottom = y * 25 + 50;
        pSprite = new EnemySprite(gollumBitmap, rcBounds, BA_BOUNCEHORIZONTAL);
        pSprite->SetPosition(gollumBitmap->GetWidth() * x, 25 * y + 25);
        pSprite->SetVelocity(-3, 0);
        _pGame->AddSprite(pSprite);
    }
    else if (whichSprite == 7)
    {
        //ghost
        RECT          rcBoundsAll = { 0, 0, 1260, 770 };
        pSprite = new EnemySprite(ghostBitmap, rcBoundsAll, _pPlayerSprite, BA_BOUNCE);
        pSprite->SetPosition(ghostBitmap->GetWidth() * x, 25 * y + 25);
        pSprite->SetVelocity(-1, 2);
        _pGame->AddSprite(pSprite);
    }
    else if (whichSprite == 8)    // heart
    {
        heartSprite = new Collectible(heartBitmap, rcBounds, BA_STOP);
        heartSprite->SetPosition(heartBitmap->GetWidth() * x, 25 * y + 25);
        _pGame->AddSprite(heartSprite);
    }
    else if (whichSprite == 9)    // key
    {
        keySprite = new Collectible(keyBitmap, rcBounds, BA_STOP);
        keySprite->SetPosition(keyBitmap->GetWidth() * x, 25 * y + 25);
        _pGame->AddSprite(keySprite);
    }
    else if (whichSprite == 10)    // fireball Collectible
    {
        fireballCollectibleSprite = new Collectible(fireballCollectibleBitmap, rcBounds, BA_STOP);
        fireballCollectibleSprite->SetPosition(fireballCollectibleBitmap->GetWidth() * x, 25 * y - 7);
        _pGame->AddSprite(fireballCollectibleSprite);
    }
    else if (whichSprite == 11)    // door
    {
        doorSprite = new Sprite(doorBitmap, rcBounds, BA_STOP);
        doorSprite->SetPosition(doorBitmap->GetWidth() * x, 25 * y -7);
        _pGame->AddSprite(doorSprite);
    }
    
}

BOOL CheckMapIfContains(int num) 
{
    for (int y = 0; y < 29; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            if (map[y][x] == num)
                return true;
        }
    }
    return false;
}

int CheckMapForQuantity(int num) 
{
    int quantity = 0;

    for (int y = 0; y < 29; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            if (map[y][x] == num)
                quantity++;
        }
    }
    return quantity;
}

BOOL CheckIntervalForDoor(int x1, int x2, int y) {
    for (int i = x1; i <= x2; i++)
    {
        if (map[y - 1][i] == 11)
            return true;
    }
    return false;
}

void CreateMap() {
    int			kat[10] = {};
    int x, y, yy;
    int ara, arasayisi, artype, aryer, arkenar, araok;  //artype: 2,5
    int x0, x1, x2;  //x1,x2:duvar baþý sonu
    int mersayisi;   // merdiven sayisi, yeri
    int haveEnemy;  // düþman varmý yok mu?
    int rn;

    //çerçeve ve kat duvarlarý
    for (y = 0; y < 29; y++)
    {
        for (x = 0; x < 50; x++)
        {
            map[y][x] = 0;
            if (x == 0 || x == 49 || y % 4 == 0)  map[y][x] = 1;   //duvar
        }
    }

    //katlarda boþluk yaratma
    for (y = 24; y > 0; y -= 4)
    {
        for (x = 0; x < 10; x++) kat[x] = 0;  //katý temizle

        rn = rand() % 100;       //boþluk sayýsý
        // %70 ihtimal 3 tane aralýk, %30 ihtimal 4 tane aralýk koyar kat'a
        if (rn < 70) arasayisi = 3;
        else arasayisi = 4;

        for (ara = 0; ara < arasayisi; ara++)
        {
            araok = 0;
            rn = rand() % 100;      //boþluðun büyüklüðü
            // %75 5'lik - %25 2'lik
            if (rn < 75) artype = 5;
            else artype = 2;         //küçük boþluk, 10'luk yer ayýr ortasý 2 boþluk


            aryer = rand() % 10;
            // Eðer 5'lik boþluk konacak ve koyulacak yer boþ ise
            if (artype == 5 && kat[aryer] == 0)
            {
                kat[aryer] = 1;
                for (x = 0; x < 5; x++) map[y][aryer * 5 + x] = 0;  //mapte yeri boþalt
                araok = 1;
            }
            // Eðer 2'lik boþluk kanacak, aryer 9'dan küçük, aryer'in gösterdiði yer boþ ve aryer'den sonraki yer de boþ ise
            if (artype == 2 && aryer < 9 && kat[aryer] == 0 && kat[aryer + 1] == 0)
            {
                kat[aryer] = 1; kat[aryer + 1] = 1;
                map[y][aryer * 5 + 4] = 0; map[y][aryer * 5 + 5] = 0;   //mapte yeri boþalt
                araok = 1;
            }

            if (araok == 0) ara--; // uygun ara bulamadý tekrar deneyecek
        }
    }

    //katlara merdiven koyma
    for (y = 24; y > 0; y -= 4)
    {
        x0 = 1;
        while (true)
        {
            x1 = 0; x2 = 0;    // x0:baþlangýç,  x1,x2 sýfýrlama
            for (x = x0; x < 49; x++)
            {
                // Eðer dolu bir konumdaysak ve x1 0 ise x1'i x'e eþitle
                if (x1 == 0 && map[y][x] == 1) x1 = x;

                // Baþýný bulduk ve (boþ bir konum bulduk veya sona geldik) ama x2=0 ise x2'yi x-1'e eþitle
                if (x1 != 0 && x2 == 0 && (map[y][x] == 0 || x == 48))
                {
                    x2 = x - 1;
                    //eðer sondan bir öncekindeyse son'a eþitle
                    if (x2 == 47) x2 = 48;
                }
            }
            // Eðer x1 ve x2'nin deðerleri 0'dan farklý ise, x0'ý (baþlangýç) x2'nin devamýna eþitle
            if (x1 != 0 && x2 != 0) x0 = x2 + 1;
            // Eðer bu kondisyonu saðlamayan bir durum varsa, x0 = x+1
            else x0 = x + 1;


            rn = rand() % 100;        //merdiven sayýsý
            // %75 - %25
            if (rn < 75) mersayisi = 1;
            else mersayisi = 2;

            // Platform boyutu 6'dan küçükse tek merdiven içerir
            if (x2 - x1 < 6) mersayisi = 1;

            if (mersayisi == 2)
            {
                for (yy = 0; yy < 29; yy += 4)
                {
                    //gerekirse daha aþaðýya uzanan merdiven

                    // End of line
                    if (y + yy >= 29) break;
                    if (yy > 0 && map[y + yy][x1] != 0) break;

                    // 4'lü merdiven
                    map[y + yy][x1] = 2;
                }
                for (yy = 0; yy < 29; yy += 4)
                {
                    // End of line
                    if (y + yy >= 29) break;
                    if (yy > 0 && map[y + yy][x2] != 0) break;

                    // 4'lü merdiven
                    map[y + yy][x2] = 2;
                }
            }

            if (mersayisi == 1)
            {
                if (rand() % 2 == 0)
                {
                    for (yy = 0; yy < 29; yy += 4)
                    {
                        //gerekirse daha aþaðýya uzanan merdiven

                        // End of line
                        if (y + yy >= 29) break;
                        // Bakýlan yerde duvar vs. bir obje varsa break'le
                        if (yy > 0 && map[y + yy][x1] != 0) break;

                        // 4'lü merdiven
                        map[y + yy][x1] = 2;
                    }
                }
                else
                {
                    for (yy = 0; yy < 29; yy += 4)
                    {
                        // End of line
                        if (y + yy >= 29) break;
                        // Bakýlan yerde duvar vs. bir obje varsa break'le
                        if (yy > 0 && map[y + yy][x2] != 0) break;

                        // 4'lü merdiven
                        map[y + yy][x2] = 2;
                    }
                }
            }

            if (x0 >= 48) break;
        }
    }

    // Kapý koyma
    BOOL isDoorCreated = false;
    for (y = 24; y > 0; y -= 4)
    {
        x0 = 1;
        while (true)
        {
            x1 = 0; x2 = 0;    // x0:baþlangýç,  x1,x2 sýfýrlama
            for (x = x0; x < 49; x++)
            {
                // Eðer dolu bir konumdaysak ve x1 0 ise x1'i x'e eþitle
                if (x1 == 0 && map[y][x] == 1) x1 = x;

                // Baþýný bulduk ve (boþ bir konum bulduk veya sona geldik) ama x2=0 ise x2'yi x-1'e eþitle
                if (x1 != 0 && x2 == 0 && (map[y][x] == 0 || x == 48))
                {
                    x2 = x - 1;
                    //eðer sondan bir öncekindeyse son'a eþitle
                    if (x2 == 47) x2 = 48;
                }
            }
            // Eðer x1 ve x2'nin deðerleri 0'dan farklý ise, x0'ý (baþlangýç) x2'nin devamýna eþitle
            if (x1 != 0 && x2 != 0) x0 = x2 + 1;
            // Eðer bu kondisyonu saðlamayan bir durum varsa, x0 = x+1
            else x0 = x + 1;


            int haveDoor = rand() % 100;

            // %20
            if (haveDoor < 20 && x2 != 0 && x1 != 0)
            {
                // Choose a random number between x1 and x2
                int xn = (rand() % (x2 - x1)) + x1;

                map[y - 1][xn] = 11;
                AddOtherSprites(11, xn, y - 1, x1, x2);
                isDoorCreated = true;
            }

            if (x0 >= 48 || isDoorCreated) break;
        }
        if (isDoorCreated)
            break;
        if (y == 4 && !isDoorCreated)
            y = 24;
    }

    //katlara düþman koyma
    for (y = 24; y > 0; y -= 4)
    {
        x0 = 1;
        while (true)
        {
            x1 = 0; x2 = 0;    // x0:baþlangýç,  x1,x2 sýfýrlama
            for (x = x0; x < 49; x++)
            {
                // Eðer dolu bir konumdaysak ve x1 0 ise x1'i x'e eþitle
                if (x1 == 0 && map[y][x] == 1) x1 = x;

                // Baþýný bulduk ve (boþ bir konum bulduk veya sona geldik) ama x2=0 ise x2'yi x-1'e eþitle
                if (x1 != 0 && x2 == 0 && (map[y][x] == 0 || x == 48))
                {
                    x2 = x - 1;
                    //eðer sondan bir öncekindeyse son'a eþitle
                    if (x2 == 47) x2 = 48;
                }
            }
            // Eðer x1 ve x2'nin deðerleri 0'dan farklý ise, x0'ý (baþlangýç) x2'nin devamýna eþitle
            if (x1 != 0 && x2 != 0) x0 = x2 + 1;
            // Eðer bu kondisyonu saðlamayan bir durum varsa, x0 = x+1
            else x0 = x + 1;


            haveEnemy = rand() % 2000;

            // if this platform contains door and its lecgth is less than 8, pass this platform.
            if (CheckIntervalForDoor(x1, x2, y) && x2 - x1 < 8)
                continue;

            // %(10 * gameDiff)
            if (haveEnemy < 250+250*gameDifficulty && x2 != 0 && x1 != 0)
            {
                // Choose a random number between x1 and x2
                int xn = (rand() % (x2 - x1)) + x1;

                // Choose an enemy between 3 and 7
                int whichEnemy = (rand() % 5) + 3;

                // Bat
                if (whichEnemy == 4) {
                    map[y - 3][xn] = whichEnemy;
                    AddOtherSprites(whichEnemy, xn, y - 3, x1, x2);
                }
                // Mage
                else if (whichEnemy == 3) {
                    if (!CheckMapIfContains(3)) {
                        if(x1 >= 4)
                            x0 = x1;
                        else {
                            if (xn < 4) {
                                map[y - 1][xn] = whichEnemy;
                                AddOtherSprites(whichEnemy, xn, y - 1, x1, x2);
                            }
                            else
                            {
                                xn = (rand() % (3 - x1)) + x1;
                                map[y - 1][xn] = whichEnemy;
                                AddOtherSprites(whichEnemy, xn, y - 1, x1, x2);
                            }
                        }
                    }
                    else
                        x0 = x1;
                }
                // Ghost
                else if (whichEnemy == 7) {
                    if (CheckMapForQuantity(7) < maxGhostAmount) 
                    {
                        int temp = rand() % 100;
                        if (temp < 60) {
                            map[y - 1][xn] = whichEnemy;
                            AddOtherSprites(whichEnemy, xn, y - 1, x1, x2);
                        }
                    }
                    else {
                        x0 = x1;
                    }
                }
                // Others
                else {
                    map[y - 1][xn] = whichEnemy;
                    AddOtherSprites(whichEnemy, xn, y - 1, x1, x2);
                }
            }

            if (x0 >= 48) break;
        }
    }

    int createdLives = 0, createdKeys = 0, fireballCreated = 0;
    //katlara toplanabilir obje ekleme
    for (y = 24; y > 0; y -= 4)
    {
        x0 = 1;
        while (true)
        {
            x1 = 0; x2 = 0;    // x0:baþlangýç,  x1,x2 sýfýrlama
            for (x = x0; x < 49; x++)
            {
                // Eðer dolu bir konumdaysak ve x1 0 ise x1'i x'e eþitle
                if (x1 == 0 && map[y][x] == 1) x1 = x;

                // Baþýný bulduk ve (boþ bir konum bulduk veya sona geldik) ama x2=0 ise x2'yi x-1'e eþitle
                if (x1 != 0 && x2 == 0 && (map[y][x] == 0 || x == 48))
                {
                    x2 = x - 1;
                    //eðer sondan bir öncekindeyse son'a eþitle
                    if (x2 == 47) x2 = 48;
                }
            }
            // Eðer x1 ve x2'nin deðerleri 0'dan farklý ise, x0'ý (baþlangýç) x2'nin devamýna eþitle
            if (x1 != 0 && x2 != 0) x0 = x2 + 1;
            // Eðer bu kondisyonu saðlamayan bir durum varsa, x0 = x+1
            else x0 = x + 1;


            int haveCollectible = rand() % 100;

            // %65
            if (haveCollectible < 35 && x2 != 0 && x1 != 0)
            {
                // Choose a random number between x1 and x2
                int xn = (rand() % (x2 - x1)) + x1;

                // Choose an enemy between 8 and 10
                int whichCollectible = (rand() % 3) + 8;

                // Heart
                if (whichCollectible == 8) {
                    if (_iNumLives > createdLives) {
                        createdLives++;
                        map[y - 1][xn] = whichCollectible;
                        AddOtherSprites(whichCollectible, xn, y - 1, x1, x2);
                    }
                }
                // Key
                else if (whichCollectible == 9) {
                    if (keyNeeded > createdKeys) {
                        createdKeys++;
                        map[y - 1][xn] = whichCollectible;
                        AddOtherSprites(whichCollectible, xn, y - 1, x1, x2);
                    }
                }
                // fireball
                else {
                    if (maxFireballAmount > fireballCreated) {
                        fireballCreated++;
                        map[y - 1][xn] = whichCollectible;
                        AddOtherSprites(whichCollectible, xn, y - 1, x1, x2);
                    }
                }

            }

            if (x0 >= 48 || (keyNeeded == createdKeys && _iNumLives == createdLives && maxFireballAmount == fireballCreated)) break;
        }
        if (keyNeeded == createdKeys && _iNumLives == createdLives && maxFireballAmount == fireballCreated)
            break;
        if (y == 4 && (keyNeeded > createdKeys || _iNumLives > createdLives || maxFireballAmount > fireballCreated))
            y = 24;
    }


    // Duvarlarý Güncelleme
    for (y = 0; y < 29; y++)
    {
        for (x = 0; x < 50; x++)
        {
            if (x == 0 || x == 49) map[y][x] = 1;   //duvar
        }
    }
}

void FillPlatformArray() {
    numOfPlatformsDynmc = 0;
    int floorTemp = 0, tempy = -1;
    for (int y = 0; y < 29; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            //duvar deðilse
            if (x != 0 && x != 49 && y != 0 && y != 28) 
            {
                if (map[y][x] == 1) {
                    RECT rcPosition = { 0,0,0,0 };

                    rcPosition.left = _pWallBitmap->GetWidth() * x;
                    rcPosition.top = _pWallBitmap->GetHeight() * (y + 1);
                    rcPosition.right = _pWallBitmap->GetWidth() * x + _pWallBitmap->GetWidth();
                    rcPosition.bottom = _pWallBitmap->GetHeight() * (y + 1) + _pWallBitmap->GetHeight();

                    _pPlatform[numOfPlatformsDynmc++] = new Platform(rcPosition, _pWallBitmap);

                    // Floor Bottoms for jumping
                    if (tempy != y) {
                        if(25*y != 600)
                            floorBottoms[floorTemp++] = 25 * y + 123;
                        else
                            floorBottoms[floorTemp++] = 25 * y + 120;

                        tempy = y;
                    }
                }
            }

            // Floor Bottoms for jumping
            if (y == 0 && tempy != y) {
                floorBottoms[floorTemp++] = 25 * y + 123;
                tempy = y;
            }
        }
    }
}

void FillStairArray() {
    numOfStairsDynmc = 0;
    for (int y = 0; y < 29; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            //duvar deðilse
            if (x != 0 && x != 49 && y != 0 && y != 28)
            {
                if (map[y][x] == 2) {
                    RECT rcPosition = { 0,0,0,0 };

                    rcPosition.left = _pWallBitmap->GetWidth() * x;
                    rcPosition.top = _pWallBitmap->GetHeight() * (y + 1);
                    rcPosition.right = _pWallBitmap->GetWidth() * x + _pStairBitmap->GetWidth();
                    rcPosition.bottom = _pWallBitmap->GetHeight() * (y + 1) + _pStairBitmap->GetHeight();

                    _pStair[numOfStairsDynmc++] = new Stair(rcPosition, _pStairBitmap);
                }
            }
        }
    }
}

void isOnLadderFunc() {
    if (whichStair == -1) {
        for (int i = 0; i < numOfStairsDynmc; i++)
        {
            if (_pStair[i] != NULL) {
                RECT StairPos = _pStair[i]->m_rcPosition;
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

void Collide() {
    for (int i = 0; i < numOfPlatformsDynmc; i++)
    {
        if (_pPlatform[i] == NULL)
            continue;
        RECT playerPos = _pPlayerSprite->GetPosition();
        RECT platformPos = _pPlatform[i]->GetPosition();
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

                if (_pPlayerSprite->GetVelocity().y > 0 && collideTop) {
                    POINT ptNewPosition;
                    ptNewPosition.x = playerPos.left;
                    ptNewPosition.y = platformPos.top - _pPlayerSprite->GetBitmap()->GetHeight();
                    _pPlayerSprite->SetPosition(ptNewPosition);
                }
                if (_pPlayerSprite->GetVelocity().y < 0 && collideBottom) {
                    POINT ptNewPosition;
                    ptNewPosition.x = playerPos.left;
                    ptNewPosition.y = platformPos.bottom;
                    _pPlayerSprite->SetPosition(ptNewPosition);
                }

            }
        }
    }
}

void CheckGround() {
    for (int i = 0; i < numOfFloor; i++)
    {
        int floorBottomPos = floorBottoms[i];
        RECT playerPos = _pPlayerSprite->GetPosition();

        if (playerPos.bottom == floorBottomPos)
        {
            isOnGrounded = true;
            break;
        }
        isOnGrounded = false;
    }
}

void FacingWhere()
{
    if (_pPlayerSprite->GetVelocity().x > 0)
    {
        facingRight = true;
    }
    else if (_pPlayerSprite->GetVelocity().x < 0)
    {
        facingRight = false;
    }
}

void CloseShield() {
    if (!shieldSprite->IsHidden()) {
        shieldSprite->SetHidden(true);

        canUseShield = true;

        // Reset the input delay
        shieldUsageDelay = 0;
    }
}