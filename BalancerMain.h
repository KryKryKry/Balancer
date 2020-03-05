/***************************************************************
 * Name:      BalancerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2019-07-24
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef BALANCERMAIN_H
#define BALANCERMAIN_H

#include "BalancerProg.h"

//(*Headers(BalancerFrame)
#include <wx/clrpicker.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

class BalancerFrame: public wxFrame
{
    public:

        BalancerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BalancerFrame();

    private:

        //(*Handlers(BalancerFrame)
        void OnValueWidthChange(wxSpinEvent& event);
        void OnSliderWidthChange(wxScrollEvent& event);
        void OnValueHeightChange(wxSpinEvent& event);
        void OnSliderHeightChange(wxScrollEvent& event);
        void OnValuePChange(wxSpinEvent& event);
        void OnSliderPChange(wxScrollEvent& event);
        void OnValueIChange(wxSpinEvent& event);
        void OnSliderIChange(wxScrollEvent& event);
        void OnValueDChange(wxSpinEvent& event);
        void OnSliderDChange(wxScrollEvent& event);
        void OnConsoleCommandEnter(wxCommandEvent& event);
        void OnColorPickerChanged(wxColourPickerEvent& event);
        void OnConsoleView(wxCommandEvent& event);
        void OnColorView(wxCommandEvent& event);
        void OnFilterView(wxCommandEvent& event);
        void OnPIDView(wxCommandEvent& event);
        void OnDataView(wxCommandEvent& event);
        void OnToolsView(wxCommandEvent& event);
        void OnStatusView(wxCommandEvent& event);
        void OnCameraConnection(wxCommandEvent& event);
        void OnControlerConnection(wxCommandEvent& event);

        void OnFrameRate(wxTimerEvent& event);
        void OnSliderXPCmdScroll(wxScrollEvent& event);
        void OnValueXPChange(wxSpinEvent& event);
        void OnValueXIChange(wxSpinEvent& event);
        void OnValueXDChange(wxSpinEvent& event);
        void OnSliderXPChange(wxScrollEvent& event);
        void OnSliderXIChange(wxScrollEvent& event);
        void OnSliderXDChange(wxScrollEvent& event);
        void OnSliderYPChange(wxScrollEvent& event);
        void OnSliderYIChange(wxScrollEvent& event);
        void OnSliderYDChange(wxScrollEvent& event);
        void OnValueYPChange(wxSpinEvent& event);
        void OnValueYIChange(wxSpinEvent& event);
        void OnValueYDChange(wxSpinEvent& event);
        void OnXPIDView(wxCommandEvent& event);
        void OnYPIDView(wxCommandEvent& event);
        void OnValueHLowChange(wxSpinEvent& event);
        void OnValueHHighChange(wxSpinEvent& event);
        void OnValueSLowChange(wxSpinEvent& event);
        void OnValueSHighChange(wxSpinEvent& event);
        void OnValueVLowChange(wxSpinEvent& event);
        void OnValueVHighChange(wxSpinEvent& event);
        //*)

		void OnVideoCapture(wxTimerEvent& event);

        //(*Identifiers(BalancerFrame)
        static const long ID_COLOURPICKERCTRL1;
        static const long ID_STATICBITMAP1;
        static const long ID_COLOURPICKERCTRL2;
        static const long ID_STATICTEXT23;
        static const long ID_SPINBUTTON10;
        static const long ID_STATICTEXT24;
        static const long ID_SPINBUTTON11;
        static const long ID_STATICTEXT21;
        static const long ID_SPINBUTTON8;
        static const long ID_STATICTEXT22;
        static const long ID_SPINBUTTON9;
        static const long ID_STATICTEXT19;
        static const long ID_SPINBUTTON6;
        static const long ID_STATICTEXT20;
        static const long ID_SPINBUTTON7;
        static const long ID_PANEL11;
        static const long ID_STATICTEXT5;
        static const long ID_SLIDER4;
        static const long ID_SPINBUTTON4;
        static const long ID_STATICTEXT6;
        static const long ID_SLIDER5;
        static const long ID_SPINBUTTON5;
        static const long ID_PANEL12;
        static const long ID_STATICTEXT2;
        static const long ID_SLIDER1;
        static const long ID_SPINBUTTON3;
        static const long ID_STATICTEXT3;
        static const long ID_SLIDER3;
        static const long ID_SPINBUTTON1;
        static const long ID_STATICTEXT4;
        static const long ID_SLIDER2;
        static const long ID_SPINBUTTON2;
        static const long ID_PANEL13;
        static const long ID_STATICTEXT25;
        static const long ID_SLIDER8;
        static const long ID_SPINBUTTON12;
        static const long ID_STATICTEXT26;
        static const long ID_SLIDER7;
        static const long ID_SPINBUTTON13;
        static const long ID_STATICTEXT27;
        static const long ID_SLIDER6;
        static const long ID_SPINBUTTON14;
        static const long ID_PANEL9;
        static const long ID_PANEL2;
        static const long ID_PANEL14;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT16;
        static const long ID_PANEL15;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT18;
        static const long ID_PANEL1;
        static const long ID_PANEL6;
        static const long ID_PANEL7;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT12;
        static const long ID_PANEL10;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT10;
        static const long ID_PANEL8;
        static const long ID_STATICTEXT1;
        static const long ID_PANEL5;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM7;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM6;
        static const long ID_MENUITEM8;
        static const long ID_MENUITEM9;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(BalancerFrame)
        wxColourPickerCtrl* HighColorPicker;
        wxColourPickerCtrl* LowColorPicker;
        wxMenu* Menu3;
        wxMenu* Menu4;
        wxMenuItem* CameraConnection;
        wxMenuItem* ColorView;
        wxMenuItem* ConsoleView;
        wxMenuItem* ControlerConnection;
        wxMenuItem* DataView;
        wxMenuItem* FilterView;
        wxMenuItem* StatusView;
        wxMenuItem* XPIDView;
        wxMenuItem* YPIDView;
        wxNotebook* VideoNotebook;
        wxPanel* BinPanel;
        wxPanel* CamPanel;
        wxPanel* CameraLED;
        wxPanel* ConfigColorPanel;
        wxPanel* ConfigFilterPanel;
        wxPanel* ConfigPanel;
        wxPanel* ConfigXPIDPanel;
        wxPanel* ConfigYPIDPanel;
        wxPanel* ConsoleLogPanel;
        wxPanel* ConsolePanel;
        wxPanel* ControlerLED;
        wxPanel* DataPanel;
        wxPanel* Panel1;
        wxPanel* StatusPanel;
        wxPanel* VideoPanel;
        wxSlider* SliderHeight;
        wxSlider* SliderWidth;
        wxSlider* SliderXD;
        wxSlider* SliderXI;
        wxSlider* SliderXP;
        wxSlider* SliderYD;
        wxSlider* SliderYI;
        wxSlider* SliderYP;
        wxSpinButton* ValueHHigh;
        wxSpinButton* ValueHLow;
        wxSpinButton* ValueHeight;
        wxSpinButton* ValueSHigh;
        wxSpinButton* ValueSLow;
        wxSpinButton* ValueVHigh;
        wxSpinButton* ValueVLow;
        wxSpinButton* ValueWidth;
        wxSpinButton* ValueXD;
        wxSpinButton* ValueXI;
        wxSpinButton* ValueXP;
        wxSpinButton* ValueYD;
        wxSpinButton* ValueYI;
        wxSpinButton* ValueYP;
        wxStaticBitmap* Gradient;
        wxStaticText* ConsoleLog;
        wxStaticText* LabelCamera;
        wxStaticText* LabelCameraStatus;
        wxStaticText* LabelControler;
        wxStaticText* LabelControlerStatus;
        wxStaticText* LabelHHigh;
        wxStaticText* LabelHLow;
        wxStaticText* LabelHeight;
        wxStaticText* LabelSHigh;
        wxStaticText* LabelSLow;
        wxStaticText* LabelVHigh;
        wxStaticText* LabelVLow;
        wxStaticText* LabelWidth;
        wxStaticText* LabelXD;
        wxStaticText* LabelXI;
        wxStaticText* LabelXP;
        wxStaticText* LabelYD;
        wxStaticText* LabelYI;
        wxStaticText* LabelYP;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStatusBar* StatusBar1;
        wxTextCtrl* ConsoleCommand;
        wxTimer FrameRate;
        //*)

        DECLARE_EVENT_TABLE()

        ///  FUNKCJE POMOCNICZE ///
        void insertCommand( wxString newCommnad );
        void insertConsoleSpace();
        void insertConfigPanel();
        void insertCameraStatus(int status);
        void insertControlerStatus(int status);
        void insertPickerLine();

        void video();

        /// OBIETKY ///
        Console console;
        Camera camera;
        SerialPort arduino;
};



#endif // BALANCERMAIN_H
