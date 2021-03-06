///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOG_TRACK_VIA_SIZE_BASE_H__
#define __DIALOG_TRACK_VIA_SIZE_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wxunittext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_TRACK_VIA_SIZE_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_TRACK_VIA_SIZE_BASE : public wxDialog 
{
	private:
	
	protected:
		WX_UNIT_TEXT* m_trackWidth;
		WX_UNIT_TEXT* m_viaDiameter;
		WX_UNIT_TEXT* m_viaDrill;
		wxStdDialogButtonSizer* m_stdButtons;
		wxButton* m_stdButtonsOK;
		wxButton* m_stdButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DIALOG_TRACK_VIA_SIZE_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Track width and via size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DIALOG_TRACK_VIA_SIZE_BASE();
	
};

#endif //__DIALOG_TRACK_VIA_SIZE_BASE_H__
