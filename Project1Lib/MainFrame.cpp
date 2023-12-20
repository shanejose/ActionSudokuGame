/**
 * @file MainFrame.cpp
 * @author Shane Jose
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );


    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);


    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );


    fileMenu->Append(IDM_SOLVE, "Solve\tCtrl-S", L"Save city as...");

    levelMenu->Append(IDM_ADDLEVEL0, L"&Level 0", L"Play at Level 0");
    levelMenu->Append(IDM_ADDLEVEL1, L"&Level 1", L"Play at Level 1");
    levelMenu->Append(IDM_ADDLEVEL2, L"&Level 2", L"Play at Level 2");
    levelMenu->Append(IDM_ADDLEVEL3, L"&Level 3", L"Play at Level 3");


}




