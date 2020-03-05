/***************************************************************
 * Name:      BalancerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-07-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "BalancerMain.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h> // wxPaintDC
#include "BalancerProg.h"
#include "opencv2/core/types_c.h"
#include "util.h"

//(*InternalHeaders(BalancerFrame)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#else defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}
/*
* Menu : File View Conection Camera
* onView: hide
* onFile: open save
* onConnction: camera controler
* onCamera: Cam Detect
*/

void BalancerFrame::insertPickerLine()
{
    Gradient->Refresh();
    Gradient->Update();

    wxPaintDC lowLine(Gradient);
    wxPaintDC highLine(Gradient);

    int h = Gradient->GetSize().GetHeight();
    int w = Gradient->GetSize().GetWidth();

    int lowHue = ValueHLow->GetValue();
    int highHue = ValueHHigh->GetValue();


    if( ( 0 <= lowHue ) && ( lowHue <= w ) && ( 0 <= highHue ) && ( highHue <= w ) )
    {
        lowLine.DrawLine(lowHue,0,lowHue,h);
        highLine.DrawLine(highHue,0,highHue,h);
    }
}

void BalancerFrame::insertCameraStatus(int status)
{
    switch(status)
    {
        case 0:
            LabelCameraStatus->SetLabel("Enable");
            CameraLED->SetBackgroundColour(wxColour(0,200,0));
        break;
        case 1:
            LabelCameraStatus->SetLabel("Not Connected");
            CameraLED->SetBackgroundColour(wxColour(0,0,200));
        break;
        case 2:
            LabelCameraStatus->SetLabel("Disable");
            CameraLED->SetBackgroundColour(wxColour(200,0,0));
        break;
        default:
            LabelCameraStatus->SetLabel("Unknow");
            CameraLED->SetBackgroundColour(wxColour(200,200,200));
        break;
    }
}
void BalancerFrame::insertControlerStatus(int status)
{
    switch(status)
    {
        case 0:
            LabelControlerStatus->SetLabel("Enable");
            ControlerLED->SetBackgroundColour(wxColour(0,200,0));
        break;
        case 1:
            LabelControlerStatus->SetLabel("Not Connected");
            ControlerLED->SetBackgroundColour(wxColour(0,0,200));
        break;
        case 2:
            LabelControlerStatus->SetLabel("Disable");
            ControlerLED->SetBackgroundColour(wxColour(200,0,0));
        break;
        default:
            LabelCameraStatus->SetLabel("Unknow");
            ControlerLED->SetBackgroundColour(wxColour(200,200,200));
        break;
    }
}
void BalancerFrame::insertConfigPanel()
{
    if( !ColorView->IsChecked() && !FilterView->IsChecked() && !XPIDView->IsChecked() && !YPIDView->IsChecked() )
    {
        ConfigPanel->Hide();
    }else{
        ConfigPanel->Show();
    }
}
void BalancerFrame::insertConsoleSpace()
{
    // #Fun Send information about console space // insertConsoleSpace()
    unsigned int offSet = 0; // Space in lines between bottom and last line
    unsigned int hSpace = ConsoleLogPanel->GetSize().GetWidth() / ConsoleLog->GetFont().GetPixelSize().GetWidth();
    unsigned int vSpace = ConsoleLogPanel->GetSize().GetHeight() / ConsoleLog->GetFont().GetPixelSize().GetHeight();
    vSpace -= offSet;
    /* #Send hSpace & vSpace */
    console.sendSpace( hSpace, vSpace );
}
void BalancerFrame::insertCommand( wxString newCommand )
{
    // #Fun send and show newCommand // insertCommand( wxString newCommnad )
    /* #Fun Send information about console space */
    insertConsoleSpace();
    /* #Send newCommand.mb_str() */
    console.sendCommand( std::string(newCommand.mb_str()) );
    /* #Pick newLogs*/
    wxString newLogs( console.pickLogToDisplay() );

    ConsoleLog->SetLabel( newLogs );
}


//(*IdInit(BalancerFrame)
const long BalancerFrame::ID_COLOURPICKERCTRL1 = wxNewId();
const long BalancerFrame::ID_STATICBITMAP1 = wxNewId();
const long BalancerFrame::ID_COLOURPICKERCTRL2 = wxNewId();
const long BalancerFrame::ID_STATICTEXT23 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON10 = wxNewId();
const long BalancerFrame::ID_STATICTEXT24 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON11 = wxNewId();
const long BalancerFrame::ID_STATICTEXT21 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON8 = wxNewId();
const long BalancerFrame::ID_STATICTEXT22 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON9 = wxNewId();
const long BalancerFrame::ID_STATICTEXT19 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON6 = wxNewId();
const long BalancerFrame::ID_STATICTEXT20 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON7 = wxNewId();
const long BalancerFrame::ID_PANEL11 = wxNewId();
const long BalancerFrame::ID_STATICTEXT5 = wxNewId();
const long BalancerFrame::ID_SLIDER4 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON4 = wxNewId();
const long BalancerFrame::ID_STATICTEXT6 = wxNewId();
const long BalancerFrame::ID_SLIDER5 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON5 = wxNewId();
const long BalancerFrame::ID_PANEL12 = wxNewId();
const long BalancerFrame::ID_STATICTEXT2 = wxNewId();
const long BalancerFrame::ID_SLIDER1 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON3 = wxNewId();
const long BalancerFrame::ID_STATICTEXT3 = wxNewId();
const long BalancerFrame::ID_SLIDER3 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON1 = wxNewId();
const long BalancerFrame::ID_STATICTEXT4 = wxNewId();
const long BalancerFrame::ID_SLIDER2 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON2 = wxNewId();
const long BalancerFrame::ID_PANEL13 = wxNewId();
const long BalancerFrame::ID_STATICTEXT25 = wxNewId();
const long BalancerFrame::ID_SLIDER8 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON12 = wxNewId();
const long BalancerFrame::ID_STATICTEXT26 = wxNewId();
const long BalancerFrame::ID_SLIDER7 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON13 = wxNewId();
const long BalancerFrame::ID_STATICTEXT27 = wxNewId();
const long BalancerFrame::ID_SLIDER6 = wxNewId();
const long BalancerFrame::ID_SPINBUTTON14 = wxNewId();
const long BalancerFrame::ID_PANEL9 = wxNewId();
const long BalancerFrame::ID_PANEL2 = wxNewId();
const long BalancerFrame::ID_PANEL14 = wxNewId();
const long BalancerFrame::ID_STATICTEXT7 = wxNewId();
const long BalancerFrame::ID_STATICTEXT16 = wxNewId();
const long BalancerFrame::ID_PANEL15 = wxNewId();
const long BalancerFrame::ID_STATICTEXT17 = wxNewId();
const long BalancerFrame::ID_STATICTEXT18 = wxNewId();
const long BalancerFrame::ID_PANEL1 = wxNewId();
const long BalancerFrame::ID_PANEL6 = wxNewId();
const long BalancerFrame::ID_PANEL7 = wxNewId();
const long BalancerFrame::ID_NOTEBOOK1 = wxNewId();
const long BalancerFrame::ID_PANEL3 = wxNewId();
const long BalancerFrame::ID_STATICTEXT8 = wxNewId();
const long BalancerFrame::ID_STATICTEXT9 = wxNewId();
const long BalancerFrame::ID_STATICTEXT15 = wxNewId();
const long BalancerFrame::ID_STATICTEXT12 = wxNewId();
const long BalancerFrame::ID_PANEL10 = wxNewId();
const long BalancerFrame::ID_STATICTEXT11 = wxNewId();
const long BalancerFrame::ID_STATICTEXT14 = wxNewId();
const long BalancerFrame::ID_STATICTEXT13 = wxNewId();
const long BalancerFrame::ID_STATICTEXT10 = wxNewId();
const long BalancerFrame::ID_PANEL8 = wxNewId();
const long BalancerFrame::ID_STATICTEXT1 = wxNewId();
const long BalancerFrame::ID_PANEL5 = wxNewId();
const long BalancerFrame::ID_TEXTCTRL1 = wxNewId();
const long BalancerFrame::ID_PANEL4 = wxNewId();
const long BalancerFrame::idMenuQuit = wxNewId();
const long BalancerFrame::ID_MENUITEM1 = wxNewId();
const long BalancerFrame::ID_MENUITEM3 = wxNewId();
const long BalancerFrame::ID_MENUITEM4 = wxNewId();
const long BalancerFrame::ID_MENUITEM5 = wxNewId();
const long BalancerFrame::ID_MENUITEM7 = wxNewId();
const long BalancerFrame::ID_MENUITEM2 = wxNewId();
const long BalancerFrame::ID_MENUITEM6 = wxNewId();
const long BalancerFrame::ID_MENUITEM8 = wxNewId();
const long BalancerFrame::ID_MENUITEM9 = wxNewId();
const long BalancerFrame::idMenuAbout = wxNewId();
const long BalancerFrame::ID_STATUSBAR1 = wxNewId();
const long BalancerFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(BalancerFrame,wxFrame)
    //(*EventTable(BalancerFrame)
    //*)
END_EVENT_TABLE()

BalancerFrame::BalancerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(BalancerFrame)
    wxBoxSizer* ColorizerBox;
    wxBoxSizer* ConfigBox;
    wxBoxSizer* ConsoleBox;
    wxBoxSizer* ConsoleCommandBox;
    wxBoxSizer* ConsoleLogBox;
    wxBoxSizer* ConsoleTextBox;
    wxBoxSizer* DataBox;
    wxBoxSizer* DifferentiatorXBox;
    wxBoxSizer* DifferentiatorYBox;
    wxBoxSizer* FilterHeightBox;
    wxBoxSizer* FilterWidthBox;
    wxBoxSizer* FremeBox;
    wxBoxSizer* GradientBox;
    wxBoxSizer* HSVBox;
    wxBoxSizer* HighColorBox;
    wxBoxSizer* HueBox;
    wxBoxSizer* IntegratingXBox;
    wxBoxSizer* IntegratingYBox;
    wxBoxSizer* LabelHeightBox;
    wxBoxSizer* LabelWidthBox;
    wxBoxSizer* LabelXDBox;
    wxBoxSizer* LabelXIBox;
    wxBoxSizer* LabelXPBox;
    wxBoxSizer* LabelYDBox;
    wxBoxSizer* LabelYIBox;
    wxBoxSizer* LabelYPBox;
    wxBoxSizer* LeftBox;
    wxBoxSizer* LowColorBox;
    wxBoxSizer* MiddleBox;
    wxBoxSizer* ProportionalXBox;
    wxBoxSizer* ProportionalYBox;
    wxBoxSizer* RightBox;
    wxBoxSizer* SaturationBox;
    wxBoxSizer* SliderHeightBox;
    wxBoxSizer* SliderWidthBox;
    wxBoxSizer* SliderXDBox;
    wxBoxSizer* SliderXIBox;
    wxBoxSizer* SliderXPBox;
    wxBoxSizer* SliderYDBox;
    wxBoxSizer* SliderYIBox;
    wxBoxSizer* SliderYPBox;
    wxBoxSizer* StatusBox;
    wxBoxSizer* ValueBox;
    wxBoxSizer* ValueHeightBox;
    wxBoxSizer* ValueWidthBox;
    wxBoxSizer* ValueXDBox;
    wxBoxSizer* ValueXIBox;
    wxBoxSizer* ValueXPBox;
    wxBoxSizer* ValueYDBox;
    wxBoxSizer* ValueYIBox;
    wxBoxSizer* ValueYPBox;
    wxBoxSizer* VideoBox;
    wxGridSizer* LeftDataLayoutBox;
    wxGridSizer* RightDataLayoutBox;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* ConfigColor;
    wxStaticBoxSizer* ConfigFilter;
    wxStaticBoxSizer* ConfigXPID;
    wxStaticBoxSizer* ConfigYPID;

    Create(parent, wxID_ANY, _("Balancer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetExtraStyle( GetExtraStyle() | wxFRAME_EX_METAL|wxFRAME_EX_CONTEXTHELP|wxWS_EX_BLOCK_EVENTS|wxWS_EX_VALIDATE_RECURSIVELY );
    FremeBox = new wxBoxSizer(wxHORIZONTAL);
    LeftBox = new wxBoxSizer(wxVERTICAL);
    ConfigPanel = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    ConfigBox = new wxBoxSizer(wxVERTICAL);
    ConfigColorPanel = new wxPanel(ConfigPanel, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    ConfigColor = new wxStaticBoxSizer(wxVERTICAL, ConfigColorPanel, _("Color"));
    ColorizerBox = new wxBoxSizer(wxHORIZONTAL);
    LowColorBox = new wxBoxSizer(wxHORIZONTAL);
    LowColorPicker = new wxColourPickerCtrl(ConfigColorPanel, ID_COLOURPICKERCTRL1, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    LowColorBox->Add(LowColorPicker, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColorizerBox->Add(LowColorBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GradientBox = new wxBoxSizer(wxHORIZONTAL);
    Gradient = new wxStaticBitmap(ConfigColorPanel, ID_STATICBITMAP1, wxBitmap(wxImage(_T("img/HSV-Hue.png"))), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    GradientBox->Add(Gradient, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColorizerBox->Add(GradientBox, 1, wxALL|wxEXPAND, 5);
    HighColorBox = new wxBoxSizer(wxHORIZONTAL);
    HighColorPicker = new wxColourPickerCtrl(ConfigColorPanel, ID_COLOURPICKERCTRL2, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL2"));
    HighColorBox->Add(HighColorPicker, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColorizerBox->Add(HighColorBox, 0, wxEXPAND, 5);
    ConfigColor->Add(ColorizerBox, 0, wxTOP|wxBOTTOM|wxEXPAND, 10);
    HSVBox = new wxBoxSizer(wxVERTICAL);
    HueBox = new wxBoxSizer(wxHORIZONTAL);
    LabelHLow = new wxStaticText(ConfigColorPanel, ID_STATICTEXT23, _("H Low"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    HueBox->Add(LabelHLow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueHLow = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON10, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON10"));
    ValueHLow->SetRange(0, 255);
    HueBox->Add(ValueHLow, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LabelHHigh = new wxStaticText(ConfigColorPanel, ID_STATICTEXT24, _("H High"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    HueBox->Add(LabelHHigh, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueHHigh = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON11, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON11"));
    ValueHHigh->SetRange(0, 255);
    HueBox->Add(ValueHHigh, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HSVBox->Add(HueBox, 1, wxALL|wxEXPAND, 5);
    SaturationBox = new wxBoxSizer(wxHORIZONTAL);
    LabelSLow = new wxStaticText(ConfigColorPanel, ID_STATICTEXT21, _("S Low"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    SaturationBox->Add(LabelSLow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueSLow = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON8, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON8"));
    ValueSLow->SetRange(0, 255);
    SaturationBox->Add(ValueSLow, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LabelSHigh = new wxStaticText(ConfigColorPanel, ID_STATICTEXT22, _("S High"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    SaturationBox->Add(LabelSHigh, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueSHigh = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON9, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON9"));
    ValueSHigh->SetRange(0, 255);
    SaturationBox->Add(ValueSHigh, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HSVBox->Add(SaturationBox, 1, wxALL|wxEXPAND, 5);
    ValueBox = new wxBoxSizer(wxHORIZONTAL);
    LabelVLow = new wxStaticText(ConfigColorPanel, ID_STATICTEXT19, _("V Low"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    ValueBox->Add(LabelVLow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueVLow = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON6, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON6"));
    ValueVLow->SetRange(0, 255);
    ValueBox->Add(ValueVLow, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LabelVHigh = new wxStaticText(ConfigColorPanel, ID_STATICTEXT20, _("V High"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    ValueBox->Add(LabelVHigh, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueVHigh = new wxSpinButton(ConfigColorPanel, ID_SPINBUTTON7, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON7"));
    ValueVHigh->SetRange(0, 255);
    ValueBox->Add(ValueVHigh, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HSVBox->Add(ValueBox, 0, wxALL|wxEXPAND, 5);
    ConfigColor->Add(HSVBox, 1, wxALL|wxEXPAND, 5);
    ConfigColorPanel->SetSizer(ConfigColor);
    ConfigColor->Fit(ConfigColorPanel);
    ConfigColor->SetSizeHints(ConfigColorPanel);
    ConfigBox->Add(ConfigColorPanel, 0, wxALL|wxEXPAND, 5);
    ConfigFilterPanel = new wxPanel(ConfigPanel, ID_PANEL12, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    ConfigFilter = new wxStaticBoxSizer(wxVERTICAL, ConfigFilterPanel, _("Filter"));
    FilterWidthBox = new wxBoxSizer(wxHORIZONTAL);
    LabelWidthBox = new wxBoxSizer(wxHORIZONTAL);
    LabelWidth = new wxStaticText(ConfigFilterPanel, ID_STATICTEXT5, _("Width"), wxDefaultPosition, wxSize(60,-1), 0, _T("ID_STATICTEXT5"));
    LabelWidthBox->Add(LabelWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterWidthBox->Add(LabelWidthBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderWidthBox = new wxBoxSizer(wxHORIZONTAL);
    SliderWidth = new wxSlider(ConfigFilterPanel, ID_SLIDER4, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER4"));
    SliderWidthBox->Add(SliderWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterWidthBox->Add(SliderWidthBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueWidthBox = new wxBoxSizer(wxHORIZONTAL);
    ValueWidth = new wxSpinButton(ConfigFilterPanel, ID_SPINBUTTON4, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON4"));
    ValueWidth->SetRange(0, 100);
    ValueWidthBox->Add(ValueWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterWidthBox->Add(ValueWidthBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigFilter->Add(FilterWidthBox, 0, wxEXPAND, 5);
    FilterHeightBox = new wxBoxSizer(wxHORIZONTAL);
    LabelHeightBox = new wxBoxSizer(wxHORIZONTAL);
    LabelHeight = new wxStaticText(ConfigFilterPanel, ID_STATICTEXT6, _("Height"), wxDefaultPosition, wxSize(60,-1), 0, _T("ID_STATICTEXT6"));
    LabelHeightBox->Add(LabelHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterHeightBox->Add(LabelHeightBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderHeightBox = new wxBoxSizer(wxHORIZONTAL);
    SliderHeight = new wxSlider(ConfigFilterPanel, ID_SLIDER5, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER5"));
    SliderHeightBox->Add(SliderHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterHeightBox->Add(SliderHeightBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueHeightBox = new wxBoxSizer(wxHORIZONTAL);
    ValueHeight = new wxSpinButton(ConfigFilterPanel, ID_SPINBUTTON5, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON5"));
    ValueHeight->SetRange(0, 100);
    ValueHeightBox->Add(ValueHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilterHeightBox->Add(ValueHeightBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigFilter->Add(FilterHeightBox, 0, wxEXPAND, 5);
    ConfigFilterPanel->SetSizer(ConfigFilter);
    ConfigFilter->Fit(ConfigFilterPanel);
    ConfigFilter->SetSizeHints(ConfigFilterPanel);
    ConfigBox->Add(ConfigFilterPanel, 0, wxALL|wxEXPAND, 5);
    ConfigXPIDPanel = new wxPanel(ConfigPanel, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    ConfigXPID = new wxStaticBoxSizer(wxVERTICAL, ConfigXPIDPanel, _("PID Axis X"));
    ProportionalXBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXPBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXP = new wxStaticText(ConfigXPIDPanel, ID_STATICTEXT2, _("P"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT2"));
    LabelXPBox->Add(LabelXP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalXBox->Add(LabelXPBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderXPBox = new wxBoxSizer(wxHORIZONTAL);
    SliderXP = new wxSlider(ConfigXPIDPanel, ID_SLIDER1, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    SliderXPBox->Add(SliderXP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalXBox->Add(SliderXPBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueXPBox = new wxBoxSizer(wxHORIZONTAL);
    ValueXP = new wxSpinButton(ConfigXPIDPanel, ID_SPINBUTTON3, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON3"));
    ValueXP->SetRange(0, 100);
    ValueXPBox->Add(ValueXP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalXBox->Add(ValueXPBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigXPID->Add(ProportionalXBox, 0, wxEXPAND, 5);
    IntegratingXBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXIBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXI = new wxStaticText(ConfigXPIDPanel, ID_STATICTEXT3, _("I"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT3"));
    LabelXIBox->Add(LabelXI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingXBox->Add(LabelXIBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderXIBox = new wxBoxSizer(wxHORIZONTAL);
    SliderXI = new wxSlider(ConfigXPIDPanel, ID_SLIDER3, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER3"));
    SliderXIBox->Add(SliderXI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingXBox->Add(SliderXIBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueXIBox = new wxBoxSizer(wxHORIZONTAL);
    ValueXI = new wxSpinButton(ConfigXPIDPanel, ID_SPINBUTTON1, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
    ValueXI->SetRange(0, 100);
    ValueXIBox->Add(ValueXI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingXBox->Add(ValueXIBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigXPID->Add(IntegratingXBox, 0, wxEXPAND, 5);
    DifferentiatorXBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXDBox = new wxBoxSizer(wxHORIZONTAL);
    LabelXD = new wxStaticText(ConfigXPIDPanel, ID_STATICTEXT4, _("D"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT4"));
    LabelXDBox->Add(LabelXD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorXBox->Add(LabelXDBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderXDBox = new wxBoxSizer(wxHORIZONTAL);
    SliderXD = new wxSlider(ConfigXPIDPanel, ID_SLIDER2, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER2"));
    SliderXDBox->Add(SliderXD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorXBox->Add(SliderXDBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueXDBox = new wxBoxSizer(wxHORIZONTAL);
    ValueXD = new wxSpinButton(ConfigXPIDPanel, ID_SPINBUTTON2, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON2"));
    ValueXD->SetRange(0, 100);
    ValueXDBox->Add(ValueXD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorXBox->Add(ValueXDBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigXPID->Add(DifferentiatorXBox, 0, wxEXPAND, 5);
    ConfigXPIDPanel->SetSizer(ConfigXPID);
    ConfigXPID->Fit(ConfigXPIDPanel);
    ConfigXPID->SetSizeHints(ConfigXPIDPanel);
    ConfigBox->Add(ConfigXPIDPanel, 0, wxALL|wxEXPAND, 5);
    ConfigYPIDPanel = new wxPanel(ConfigPanel, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    ConfigYPID = new wxStaticBoxSizer(wxVERTICAL, ConfigYPIDPanel, _("PID Axis Y"));
    ProportionalYBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYPBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYP = new wxStaticText(ConfigYPIDPanel, ID_STATICTEXT25, _("P"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT25"));
    LabelYPBox->Add(LabelYP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalYBox->Add(LabelYPBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderYPBox = new wxBoxSizer(wxHORIZONTAL);
    SliderYP = new wxSlider(ConfigYPIDPanel, ID_SLIDER8, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER8"));
    SliderYPBox->Add(SliderYP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalYBox->Add(SliderYPBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueYPBox = new wxBoxSizer(wxHORIZONTAL);
    ValueYP = new wxSpinButton(ConfigYPIDPanel, ID_SPINBUTTON12, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON12"));
    ValueYP->SetRange(0, 100);
    ValueYPBox->Add(ValueYP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProportionalYBox->Add(ValueYPBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigYPID->Add(ProportionalYBox, 1, wxALL|wxEXPAND, 5);
    IntegratingYBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYIBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYI = new wxStaticText(ConfigYPIDPanel, ID_STATICTEXT26, _("I"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT26"));
    LabelYIBox->Add(LabelYI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingYBox->Add(LabelYIBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderYIBox = new wxBoxSizer(wxHORIZONTAL);
    SliderYI = new wxSlider(ConfigYPIDPanel, ID_SLIDER7, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER7"));
    SliderYIBox->Add(SliderYI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingYBox->Add(SliderYIBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueYIBox = new wxBoxSizer(wxHORIZONTAL);
    ValueYI = new wxSpinButton(ConfigYPIDPanel, ID_SPINBUTTON13, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON13"));
    ValueYI->SetRange(0, 100);
    ValueYIBox->Add(ValueYI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    IntegratingYBox->Add(ValueYIBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigYPID->Add(IntegratingYBox, 1, wxALL|wxEXPAND, 5);
    DifferentiatorYBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYDBox = new wxBoxSizer(wxHORIZONTAL);
    LabelYD = new wxStaticText(ConfigYPIDPanel, ID_STATICTEXT27, _("D"), wxDefaultPosition, wxSize(12,-1), 0, _T("ID_STATICTEXT27"));
    LabelYDBox->Add(LabelYD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorYBox->Add(LabelYDBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderYDBox = new wxBoxSizer(wxHORIZONTAL);
    SliderYD = new wxSlider(ConfigYPIDPanel, ID_SLIDER6, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER6"));
    SliderYDBox->Add(SliderYD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorYBox->Add(SliderYDBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ValueYDBox = new wxBoxSizer(wxHORIZONTAL);
    ValueYD = new wxSpinButton(ConfigYPIDPanel, ID_SPINBUTTON14, wxDefaultPosition, wxSize(70,-1), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON14"));
    ValueYD->SetRange(0, 100);
    ValueYDBox->Add(ValueYD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DifferentiatorYBox->Add(ValueYDBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConfigYPID->Add(DifferentiatorYBox, 1, wxALL|wxEXPAND, 5);
    ConfigYPIDPanel->SetSizer(ConfigYPID);
    ConfigYPID->Fit(ConfigYPIDPanel);
    ConfigYPID->SetSizeHints(ConfigYPIDPanel);
    ConfigBox->Add(ConfigYPIDPanel, 0, wxALL|wxEXPAND, 5);
    ConfigPanel->SetSizer(ConfigBox);
    ConfigBox->Fit(ConfigPanel);
    ConfigBox->SetSizeHints(ConfigPanel);
    LeftBox->Add(ConfigPanel, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FremeBox->Add(LeftBox, 0, wxALL|wxALIGN_TOP, 5);
    MiddleBox = new wxBoxSizer(wxVERTICAL);
    StatusPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StatusPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    StatusBox = new wxBoxSizer(wxHORIZONTAL);
    CameraLED = new wxPanel(StatusPanel, ID_PANEL14, wxDefaultPosition, wxSize(20,20), wxTAB_TRAVERSAL, _T("ID_PANEL14"));
    StatusBox->Add(CameraLED, 0, wxALL|wxEXPAND, 5);
    LabelCamera = new wxStaticText(StatusPanel, ID_STATICTEXT7, _("Camera:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    StatusBox->Add(LabelCamera, 0, wxALL|wxALIGN_TOP, 5);
    LabelCameraStatus = new wxStaticText(StatusPanel, ID_STATICTEXT16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    StatusBox->Add(LabelCameraStatus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ControlerLED = new wxPanel(StatusPanel, ID_PANEL15, wxDefaultPosition, wxSize(20,20), wxTAB_TRAVERSAL, _T("ID_PANEL15"));
    StatusBox->Add(ControlerLED, 0, wxALL|wxEXPAND, 5);
    LabelControler = new wxStaticText(StatusPanel, ID_STATICTEXT17, _("Controler2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StatusBox->Add(LabelControler, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LabelControlerStatus = new wxStaticText(StatusPanel, ID_STATICTEXT18, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StatusBox->Add(LabelControlerStatus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StatusPanel->SetSizer(StatusBox);
    StatusBox->Fit(StatusPanel);
    StatusBox->SetSizeHints(StatusPanel);
    MiddleBox->Add(StatusPanel, 0, wxALL|wxEXPAND, 5);
    VideoPanel = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    VideoBox = new wxBoxSizer(wxHORIZONTAL);
    VideoNotebook = new wxNotebook(VideoPanel, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    CamPanel = new wxPanel(VideoNotebook, ID_PANEL6, wxDefaultPosition, wxSize(623,516), wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    BinPanel = new wxPanel(VideoNotebook, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    VideoNotebook->AddPage(CamPanel, _("Cam"), false);
    VideoNotebook->AddPage(BinPanel, _("Detect"), false);
    VideoBox->Add(VideoNotebook, 1, wxALL|wxEXPAND, 5);
    VideoPanel->SetSizer(VideoBox);
    VideoBox->Fit(VideoPanel);
    VideoBox->SetSizeHints(VideoPanel);
    MiddleBox->Add(VideoPanel, 1, wxALL|wxEXPAND, 5);
    DataPanel = new wxPanel(this, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    DataPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
    DataBox = new wxBoxSizer(wxHORIZONTAL);
    LeftDataLayoutBox = new wxGridSizer(2, 2, 0, 0);
    StaticText1 = new wxStaticText(DataPanel, ID_STATICTEXT8, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    LeftDataLayoutBox->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(DataPanel, ID_STATICTEXT9, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    LeftDataLayoutBox->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(DataPanel, ID_STATICTEXT15, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    LeftDataLayoutBox->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(DataPanel, ID_STATICTEXT12, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    LeftDataLayoutBox->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DataBox->Add(LeftDataLayoutBox, 1, wxEXPAND, 5);
    Panel1 = new wxPanel(DataPanel, ID_PANEL10, wxDefaultPosition, wxSize(20,-1), wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    DataBox->Add(Panel1, 0, wxEXPAND, 5);
    RightDataLayoutBox = new wxGridSizer(2, 2, 0, 0);
    StaticText5 = new wxStaticText(DataPanel, ID_STATICTEXT11, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    RightDataLayoutBox->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(DataPanel, ID_STATICTEXT14, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    RightDataLayoutBox->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(DataPanel, ID_STATICTEXT13, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    RightDataLayoutBox->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(DataPanel, ID_STATICTEXT10, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    RightDataLayoutBox->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DataBox->Add(RightDataLayoutBox, 1, wxEXPAND, 5);
    DataPanel->SetSizer(DataBox);
    DataBox->Fit(DataPanel);
    DataBox->SetSizeHints(DataPanel);
    MiddleBox->Add(DataPanel, 0, wxALL|wxEXPAND, 5);
    FremeBox->Add(MiddleBox, 1, wxEXPAND, 5);
    RightBox = new wxBoxSizer(wxHORIZONTAL);
    ConsolePanel = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    ConsoleBox = new wxBoxSizer(wxVERTICAL);
    ConsoleTextBox = new wxBoxSizer(wxHORIZONTAL);
    ConsoleLogPanel = new wxPanel(ConsolePanel, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    ConsoleLogPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    ConsoleLogBox = new wxBoxSizer(wxHORIZONTAL);
    ConsoleLog = new wxStaticText(ConsoleLogPanel, ID_STATICTEXT1, _("Label"), wxDefaultPosition, wxSize(200,203), 0, _T("ID_STATICTEXT1"));
    ConsoleLogBox->Add(ConsoleLog, 0, wxALL|wxEXPAND, 5);
    ConsoleLogPanel->SetSizer(ConsoleLogBox);
    ConsoleLogBox->Fit(ConsoleLogPanel);
    ConsoleLogBox->SetSizeHints(ConsoleLogPanel);
    ConsoleTextBox->Add(ConsoleLogPanel, 1, wxALL|wxEXPAND, 5);
    ConsoleBox->Add(ConsoleTextBox, 1, wxEXPAND, 5);
    ConsoleCommandBox = new wxBoxSizer(wxHORIZONTAL);
    ConsoleCommand = new wxTextCtrl(ConsolePanel, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    ConsoleCommandBox->Add(ConsoleCommand, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ConsoleBox->Add(ConsoleCommandBox, 0, wxEXPAND, 5);
    ConsolePanel->SetSizer(ConsoleBox);
    ConsoleBox->Fit(ConsolePanel);
    ConsoleBox->SetSizeHints(ConsolePanel);
    RightBox->Add(ConsolePanel, 1, wxEXPAND, 5);
    FremeBox->Add(RightBox, 0, wxEXPAND, 5);
    SetSizer(FremeBox);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    ConsoleView = new wxMenuItem(Menu3, ID_MENUITEM1, _("Console"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(ConsoleView);
    ConsoleView->Check(true);
    ColorView = new wxMenuItem(Menu3, ID_MENUITEM3, _("Color"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(ColorView);
    ColorView->Check(true);
    FilterView = new wxMenuItem(Menu3, ID_MENUITEM4, _("Filter"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(FilterView);
    FilterView->Check(true);
    XPIDView = new wxMenuItem(Menu3, ID_MENUITEM5, _("PID Axis X"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(XPIDView);
    XPIDView->Check(true);
    YPIDView = new wxMenuItem(Menu3, ID_MENUITEM7, _("PID Axis Y"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(YPIDView);
    YPIDView->Check(true);
    StatusView = new wxMenuItem(Menu3, ID_MENUITEM2, _("Status"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(StatusView);
    StatusView->Check(true);
    DataView = new wxMenuItem(Menu3, ID_MENUITEM6, _("Parameters"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(DataView);
    DataView->Check(true);
    MenuBar1->Append(Menu3, _("&View"));
    Menu4 = new wxMenu();
    CameraConnection = new wxMenuItem(Menu4, ID_MENUITEM8, _("Camera"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(CameraConnection);
    ControlerConnection = new wxMenuItem(Menu4, ID_MENUITEM9, _("Controler3"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(ControlerConnection);
    MenuBar1->Append(Menu4, _("Connection"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FrameRate.SetOwner(this, ID_TIMER1);
    FrameRate.Start(100, false);
    FremeBox->Fit(this);
    FremeBox->SetSizeHints(this);
    Center();

    Connect(ID_COLOURPICKERCTRL1,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&BalancerFrame::OnColorPickerChanged);
    Connect(ID_COLOURPICKERCTRL2,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&BalancerFrame::OnColorPickerChanged);
    Connect(ID_SPINBUTTON10,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueHLowChange);
    Connect(ID_SPINBUTTON11,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueHHighChange);
    Connect(ID_SPINBUTTON8,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueSLowChange);
    Connect(ID_SPINBUTTON9,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueSHighChange);
    Connect(ID_SPINBUTTON6,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueVLowChange);
    Connect(ID_SPINBUTTON7,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueVHighChange);
    Connect(ID_SLIDER4,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderWidthChange);
    Connect(ID_SPINBUTTON4,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueWidthChange);
    Connect(ID_SLIDER5,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderHeightChange);
    Connect(ID_SPINBUTTON5,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueHeightChange);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderXPChange);
    Connect(ID_SPINBUTTON3,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueXPChange);
    Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderXIChange);
    Connect(ID_SPINBUTTON1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueXIChange);
    Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderXDChange);
    Connect(ID_SPINBUTTON2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueXDChange);
    Connect(ID_SLIDER8,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderYPChange);
    Connect(ID_SPINBUTTON12,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueYPChange);
    Connect(ID_SLIDER7,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderYIChange);
    Connect(ID_SPINBUTTON13,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueYIChange);
    Connect(ID_SLIDER6,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&BalancerFrame::OnSliderYDChange);
    Connect(ID_SPINBUTTON14,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&BalancerFrame::OnValueYDChange);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&BalancerFrame::OnConsoleCommandEnter);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnConsoleView);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnColorView);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnFilterView);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnXPIDView);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnYPIDView);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnStatusView);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnDataView);
    Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnCameraConnection);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&BalancerFrame::OnControlerConnection);

    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&BalancerFrame::OnFrameRate);
    //*)

    // #Fun Send information about console space // insertConsoleSpace()
    insertConsoleSpace();

}

BalancerFrame::~BalancerFrame()
{
    //(*Destroy(BalancerFrame)
    //*)
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        onColor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BalancerFrame::OnColorPickerChanged(wxColourPickerEvent& event)
{
    wxColor lowPick = LowColorPicker->GetColour();
    wxColor highPick = HighColorPicker->GetColour();

    /* Set LOW */
    Color::HSV lowColor = Color::toHSV( lowPick.Red(), lowPick.Green(), lowPick.Blue() );

    ValueHLow->SetValue( lowColor.h );
    ValueSLow->SetValue( lowColor.s );
    ValueVLow->SetValue( lowColor.v );

    /* Set HIGH */
    Color::HSV highColor = Color::toHSV( highPick.Red(), highPick.Green(), highPick.Blue() );

    ValueHHigh->SetValue( highColor.h );
    ValueSHigh->SetValue( highColor.s );
    ValueVHigh->SetValue( highColor.v );

    insertPickerLine();

    Color::HSV newColor;

    newColor.h = ValueHLow->GetValue();
    newColor.s = ValueSLow->GetValue();
    newColor.v = ValueVLow->GetValue();
    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'L' );

    newColor.h = ValueHHigh->GetValue();
    newColor.s = ValueSHigh->GetValue();
    newColor.v = ValueVHigh->GetValue();
    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'H' );

}
/*-----------------------------------------------------------------------*/
void BalancerFrame::OnValueHLowChange(wxSpinEvent& event)
{
    insertPickerLine();


    Color::HSV newColor;
    newColor.h = ValueHLow->GetValue();
    newColor.s = ValueSLow->GetValue();
    newColor.v = ValueVLow->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    LowColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'L' );

}

void BalancerFrame::OnValueHHighChange(wxSpinEvent& event)
{
    insertPickerLine();

    Color::HSV newColor;
    newColor.h = ValueHHigh->GetValue();
    newColor.s = ValueSHigh->GetValue();
    newColor.v = ValueVHigh->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    HighColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'H' );

}

void BalancerFrame::OnValueSLowChange(wxSpinEvent& event)
{
    Color::HSV newColor;
    newColor.h = ValueHLow->GetValue();
    newColor.s = ValueSLow->GetValue();
    newColor.v = ValueVLow->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    LowColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'L' );
}

void BalancerFrame::OnValueSHighChange(wxSpinEvent& event)
{
    Color::HSV newColor;
    newColor.h = ValueHHigh->GetValue();
    newColor.s = ValueSHigh->GetValue();
    newColor.v = ValueVHigh->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    HighColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'H' );
}

void BalancerFrame::OnValueVLowChange(wxSpinEvent& event)
{
    Color::HSV newColor;
    newColor.h = ValueHLow->GetValue();
    newColor.s = ValueSLow->GetValue();
    newColor.v = ValueVLow->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    LowColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'L' );
}

void BalancerFrame::OnValueVHighChange(wxSpinEvent& event)
{
    Color::HSV newColor;
    newColor.h = ValueHHigh->GetValue();
    newColor.s = ValueSHigh->GetValue();
    newColor.v = ValueVHigh->GetValue();

    Color::RGB RGBColor = Color::toRGB( newColor );
    HighColorPicker->SetColour( wxColor( RGBColor.r, RGBColor.g, RGBColor.b ) );

    camera.sendHSV( newColor.h, newColor.s, newColor.v, 'H' );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        onFilter
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BalancerFrame::OnValueWidthChange(wxSpinEvent& event)
{
    SliderWidth->SetValue( ValueWidth->GetValue() );
    /* #Send ValueWidth->GetValue() */
    camera.sendFilter( ValueWidth->GetValue(), 'W' );
}

void BalancerFrame::OnSliderWidthChange(wxScrollEvent& event)
{
    ValueWidth->SetValue( SliderWidth->GetValue() );
    /* #Send ValueWidth->GetValue() */
    camera.sendFilter( ValueWidth->GetValue(), 'W' );
}

void BalancerFrame::OnValueHeightChange(wxSpinEvent& event)
{
    SliderHeight->SetValue( ValueHeight->GetValue() );
    /* #Send ValueHeight->GetValue() */
    camera.sendFilter( ValueHeight->GetValue(), 'H' );
}

void BalancerFrame::OnSliderHeightChange(wxScrollEvent& event)
{
    ValueHeight->SetValue( SliderHeight->GetValue() );
    /* #Send ValueHeight->GetValue() */
    camera.sendFilter( ValueHeight->GetValue(), 'H' );

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        onPID
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BalancerFrame::OnValueXPChange(wxSpinEvent& event)
{
    SliderXP->SetValue( ValueXP->GetValue() );
    insertCommand( wxString("# Value Parameter P is changed") );
    /* #Send ValueXP->GetValue() */
	insertCommand( wxString("onPID") );
	if(arduino.good()) {
		arduino.serialPortWrite(ValueXP->GetValue(), ValueYP->GetValue());
		insertCommand( wxString("VAl") );
	}

}

void BalancerFrame::OnSliderXPChange(wxScrollEvent& event)
{
    ValueXP->SetValue( SliderXP->GetValue() );
    insertCommand( wxString("# Value Parameter P is changed") );
    /* #Send ValueXP->GetValue() */
	insertCommand( wxString("onPID") );
	if(arduino.good()) {
		arduino.serialPortWrite(ValueXP->GetValue(), ValueYP->GetValue());
		insertCommand( wxString("VAl") );
	}
}

void BalancerFrame::OnValueXIChange(wxSpinEvent& event)
{
    SliderXI->SetValue( ValueXI->GetValue() );
    /* #Send ValueXI->GetValue() */
}

void BalancerFrame::OnSliderXIChange(wxScrollEvent& event)
{
    ValueXI->SetValue( SliderXI->GetValue() );
    /* #Send ValueXI->GetValue() */
}

void BalancerFrame::OnValueXDChange(wxSpinEvent& event)
{
    SliderXD->SetValue( ValueXD->GetValue() );
    /* #Send ValueXD->GetValue() */
}

void BalancerFrame::OnSliderXDChange(wxScrollEvent& event)
{
    ValueXD->SetValue( SliderXD->GetValue() );
    /* #Send ValueXD->GetValue() */
}
/*-----------------------------------------------------------------------*/
void BalancerFrame::OnValueYPChange(wxSpinEvent& event)
{
    SliderYP->SetValue( ValueYP->GetValue() );
    /* #Send ValueYP->GetValue() */

}

void BalancerFrame::OnSliderYPChange(wxScrollEvent& event)
{
    ValueYP->SetValue( SliderYP->GetValue() );
    /* #Send ValueYP->GetValue() */
}

void BalancerFrame::OnValueYIChange(wxSpinEvent& event)
{
    SliderYI->SetValue( ValueYI->GetValue() );
    /* #Send ValueYI->GetValue() */
}

void BalancerFrame::OnSliderYIChange(wxScrollEvent& event)
{
    ValueYI->SetValue( SliderYI->GetValue() );
    /* #Send ValueXI->GetValue() */
}

void BalancerFrame::OnValueYDChange(wxSpinEvent& event)
{
    SliderYD->SetValue( ValueYD->GetValue() );
    /* #Send ValueYD->GetValue() */
}

void BalancerFrame::OnSliderYDChange(wxScrollEvent& event)
{
    ValueYD->SetValue( SliderYD->GetValue() );
    /* #Send ValueYD->GetValue() */
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        onConsole
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BalancerFrame::OnConsoleCommandEnter(wxCommandEvent& event)
{
    wxString newCommand("$ "); // $ mean command by user
    newCommand += ConsoleCommand->GetValue();
    ConsoleCommand->SetValue("");

    insertCommand(newCommand);

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        onView
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BalancerFrame::OnConsoleView(wxCommandEvent& event)
{
    if( ConsoleView->IsChecked() )
    {
        ConsolePanel->Show();
    }else{
        ConsolePanel->Hide();
    }
    Layout();
}

void BalancerFrame::OnColorView(wxCommandEvent& event)
{
    if( ColorView->IsChecked() )
    {
        ConfigColorPanel->Show();
    }else{
        ConfigColorPanel->Hide();
    }

    // Aktualizacja Lini
    insertPickerLine();

    insertConfigPanel();
    Layout();
}

void BalancerFrame::OnFilterView(wxCommandEvent& event)
{
    if( FilterView->IsChecked() )
    {
        ConfigFilterPanel->Show();
    }else{
        ConfigFilterPanel->Hide();
    }

    insertConfigPanel();
    Layout();
}

void BalancerFrame::OnXPIDView(wxCommandEvent& event)
{
    if( XPIDView->IsChecked() )
    {
        ConfigXPIDPanel->Show();
    }else{
        ConfigXPIDPanel->Hide();
    }

    insertConfigPanel();
    Layout();
}

void BalancerFrame::OnYPIDView(wxCommandEvent& event)
{
    if( YPIDView->IsChecked() )
    {
        ConfigYPIDPanel->Show();
    }else{
        ConfigYPIDPanel->Hide();
    }

    insertConfigPanel();
    Layout();
}

void BalancerFrame::OnDataView(wxCommandEvent& event)
{
    if( DataView->IsChecked() )
    {
        DataPanel->Show();
    }else{
        DataPanel->Hide();
    }
    Layout();
}

void BalancerFrame::OnStatusView(wxCommandEvent& event)
{
    if( StatusView->IsChecked() )
    {
        StatusPanel->Show();
    }else{
        StatusPanel->Hide();
    }
    Layout();
}

void BalancerFrame::OnCameraConnection(wxCommandEvent& event)
{
    insertCameraStatus(1);
    if( camera.connect(0) )
    {
        insertCameraStatus(0);
    }
    else{
        insertCameraStatus(2);
    }
}

void BalancerFrame::OnFrameRate(wxTimerEvent& event)
{


    if( camera.good() )
    {
        camera.pickFrame(0);

        if( camera.videoData )
        {
        wxImage videoImg(camera.videoWidth, camera.videoHeight, camera.videoData, true);
        wxBitmap videoBmp = wxBitmap(videoImg.Scale( CamPanel->GetSize().GetWidth() , CamPanel->GetSize().GetHeight() ) );
        wxPaintDC videoFrame(CamPanel);
        videoFrame.DrawBitmap(videoBmp, 0, 0, false);

        //wxImage videoImg2(camera.videoWidth, camera.videoHeight, camera.videoData, true);
        wxBitmap videoBmp2 = wx_from_mat(camera.imgBin2).Scale( CamPanel->GetSize().GetWidth() , CamPanel->GetSize().GetHeight() );
        wxPaintDC videoFrame2(BinPanel);
        videoFrame2.DrawBitmap(videoBmp2, 0, 0, false);
        }



    }
}

void BalancerFrame::OnControlerConnection(wxCommandEvent& event)
{
	insertControlerStatus(1);
    if(arduino.serialPortInit("/dev/ttyACM0", B9600) == SerialPort::Error::OPEN_GOOD) {
		insertControlerStatus(0);
      arduino.serialPortWrite(ValueXP->GetValue(), ValueYP->GetValue());
	  insertCommand( wxString("I'm Here!!"));
  }
}

void BalancerFrame::OnVideoCapture(wxTimerEvent& event)
{

	insertCommand( wxString("Here"));

	// if( camera.good() )
	// {
	// 	camera.pickFrame(0);
	//
	// 	if( camera.videoData )
	// 	{
	// 	wxImage videoImg(camera.videoWidth, camera.videoHeight, camera.videoData, true);
	// 	wxBitmap videoBmp = wxBitmap(videoImg.Scale( CamPanel->GetSize().GetWidth() , CamPanel->GetSize().GetHeight() ) );
	// 	wxPaintDC videoFrame(CamPanel);
	// 	videoFrame.DrawBitmap(videoBmp, 0, 0, false);
	// 	}
	// }
}


//void BalancerFrame::OnValueXPChange(wxSpinEvent& event)
//{
//}
//
//void BalancerFrame::OnValueXIChange(wxSpinEvent& event)
//{
//}
//
//void BalancerFrame::OnValueXDChange(wxSpinEvent& event)
//{
//}

//void BalancerFrame::OnSliderXPChange(wxScrollEvent& event)
//{
//}
//
//void BalancerFrame::OnSliderXIChange(wxScrollEvent& event)
//{
//}
//
//void BalancerFrame::OnSliderXDChange(wxScrollEvent& event)
//{
//}

//void BalancerFrame::OnSliderYPChange(wxScrollEvent& event)
//{
//}
//
//void BalancerFrame::OnSliderYIChange(wxScrollEvent& event)
//{
//}
//
//void BalancerFrame::OnSliderYDChange(wxScrollEvent& event)
//{
//}
//
//void BalancerFrame::OnValueYPChange(wxSpinEvent& event)
//{
//}
//
//void BalancerFrame::OnValueYIChange(wxSpinEvent& event)
//{
//}
//
//void BalancerFrame::OnValueYDChange(wxSpinEvent& event)
//{
//}

//void BalancerFrame::OnXPIDView(wxCommandEvent& event)
//{
//}

//void BalancerFrame::OnYPIDView(wxCommandEvent& event)
//{
//}
