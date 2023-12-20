/**
 * @file GameView.cpp
 * @author Shane Jose
 */

#include "pch.h"
#include "GameView.h"
#include "ids.h"

#include <sstream>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>


using namespace std;


/**
 * Initialize the Game view class.
 * @param parent The parent window for this class
 *
 */
void GameView::Initialize(wxFrame* parent)
{
    ///Create(parent, wxID_ANY);
    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileSolve, this, IDM_SOLVE);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewLevel0, this, IDM_ADDLEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewLevel1, this, IDM_ADDLEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewLevel2, this, IDM_ADDLEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewLevel3, this, IDM_ADDLEVEL3);
    mTimer.SetOwner(this);
    mTimer.Start(30);

    Bind(wxEVT_TIMER, &GameView::OnStartTimer,this);
    mStopWatch.Start();

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);

    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);

    const wstring level1FileName = L"resources/levels/level1.xml";
    mGame.Load(level1FileName);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 *
 */
void GameView::OnPaint(wxPaintEvent& event)
{

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;

    mTime = newTime;
    mGame.Update(elapsed);

    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

}

/**
 * Solves the Sudoku Board
 * @param event
 */
void GameView::OnFileSolve(wxCommandEvent &event)
{
    mGame.Solve();

}

/**
 * Displays the message of Level 0
 * @param event
 */
void GameView::OnViewLevel0(wxCommandEvent &event)
{
    const wstring level0FileName = L"resources/levels/level0.xml";
    mGame.ResetTimer();
    mGame.Load(level0FileName);
    mGame.SetLevel(0);
    mGame.SetDialogueVisible(true);
    mGame.SetDialogueDuration(3.0);

}


/**
 * Displays the message of Level 1
 * @param event
 */
void GameView::OnViewLevel1(wxCommandEvent &event)
{
    const wstring level1FileName = L"resources/levels/level1.xml";
    mGame.ResetTimer();
    mGame.Load(level1FileName);
    mGame.SetLevel(1);
    mGame.SetDialogueVisible(true);
    mGame.SetDialogueDuration(3.0);
}

/**
 * Displays the message of Level 2
 * @param event
 */
void GameView::OnViewLevel2(wxCommandEvent &event)
{
    const wstring level2FileName = L"resources/levels/level2.xml";
    mGame.ResetTimer();
    mGame.Load(level2FileName);
    mGame.SetLevel(2);
    mGame.SetDialogueVisible(true);
    mGame.SetDialogueDuration(3.0);
}


/**
 * Displays the message of Level 3
 * @param event
 */
void GameView::OnViewLevel3(wxCommandEvent &event)
{
    const wstring level3FileName = L"resources/levels/level3.xml";
    mGame.ResetTimer();
    mGame.TurnOnSound(true);
    mGame.Load(level3FileName);
    mGame.SetLevel(3);
    mGame.SetDialogueVisible(true);
    mGame.SetDialogueDuration(3.0);
}

/**
 * Refreshes the timer
 * @param event
 */
void GameView::OnStartTimer(wxTimerEvent &event)
{
    mTextY -= 10;
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.SpartyMovement(event.GetX(), event.GetY());
    mGame.SpartyMouthMovement(event.GetX(), event.GetY());
    Refresh();
}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);


}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent &event)
{

}

/**
 * Sparty performs specific movements based on the key user clicked
 * @param event
 *
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{

    if(event.GetKeyCode() == 'B')
    {
        mGame.SpartyHeadButtMovement();
    }

    if(event.GetKeyCode() ==  WXK_SPACE)
    {
        mGame.SpartyEatingMovement();
        mTextY= 650;
        mCheckFull = mGame.Eat();
        if (mCheckFull) {
            auto errorMessage = make_shared<ErrorMessage>();
            errorMessage->SetErrorLocation(mTextY);
            errorMessage->SetErrorMessage("I'm Full!");
            errorMessage->SetFullFontMessage(true);
            mGame.AddErrorMsg(errorMessage);

        }
    }

    if(event.GetKeyCode() >='0' && event.GetKeyCode() <= '8')
    {
        mRegurgitateMessage= false;
        mGame.SpartyEatingMovement();
        mTextY= 650;
        mRegurgitateMessage= mGame.SpartyRegurgitate(event.GetKeyCode() - '0');
        mGame.CheckSol();

        if (mRegurgitateMessage) {
            auto errorMessage = make_shared<ErrorMessage>();
            errorMessage->SetErrorLocation(mTextY);
            errorMessage->SetErrorMessage("Something already in here!");
            errorMessage->SetFullFontMessage(false);
            mGame.AddErrorMsg(errorMessage);
        }

    }

}



