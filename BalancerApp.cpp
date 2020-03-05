/***************************************************************
 * Name:      BalancerApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2019-07-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "BalancerApp.h"

//(*AppHeaders
#include "BalancerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(BalancerApp);

bool BalancerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	BalancerFrame* Frame = new BalancerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
