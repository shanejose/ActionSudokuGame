/**
 * @file GameView.h
 * @author Shane Jose
 *
 * View class for our Game
 */

#ifndef PROJECT1_PROJECT1LIB_GAMEVIEW_H
#define PROJECT1_PROJECT1LIB_GAMEVIEW_H

#include "Game.h"
#include <vector>


/**
 * View class for our Game
 *
 */
class GameView : public wxWindow
{
private:
    /// An object that describes our game
    Game mGame;

    void OnPaint(wxPaintEvent& event);

    void OnViewLevel0(wxCommandEvent &event);
    void OnViewLevel1(wxCommandEvent &event);
    void OnViewLevel2(wxCommandEvent &event);
    void OnViewLevel3(wxCommandEvent &event);
    void OnFileSolve(wxCommandEvent &event);
    void OnStartTimer(wxTimerEvent &event);

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent& event);



    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// Flag for pop up message for regurgitate
    bool mRegurgitateMessage= false;

    /// The last stopwatch time
    long mTime = 0;

    /// boolean to check full
    bool mCheckFull = false;

    /// updates the time of the text
    int mTextY = 650;


    /// graphics to draw on game view
    std::shared_ptr<wxGraphicsContext> graphics;


public:
    void Initialize(wxFrame* parent);


};

#endif //PROJECT1_PROJECT1LIB_GAMEVIEW_H
