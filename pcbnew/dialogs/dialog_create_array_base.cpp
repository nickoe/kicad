///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialog_create_array_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_CREATE_ARRAY_BASE::DIALOG_CREATE_ARRAY_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_gridTypeNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_gridPanel = new wxPanel( m_gridTypeNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labelNx = new wxStaticText( m_gridPanel, wxID_ANY, _("x Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelNx->Wrap( -1 );
	fgSizer2->Add( m_labelNx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryNx = new wxTextCtrl( m_gridPanel, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryNx, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( m_gridPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer2->Add( m_staticText15, 0, wxALL, 5 );
	
	m_labelNy = new wxStaticText( m_gridPanel, wxID_ANY, _("y Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelNy->Wrap( -1 );
	fgSizer2->Add( m_labelNy, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryNy = new wxTextCtrl( m_gridPanel, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryNy, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( m_gridPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer2->Add( m_staticText16, 0, wxALL, 5 );
	
	m_labelDx = new wxStaticText( m_gridPanel, wxID_ANY, _("x Spacing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelDx->Wrap( -1 );
	fgSizer2->Add( m_labelDx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryDx = new wxTextCtrl( m_gridPanel, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryDx, 0, wxALL, 5 );
	
	m_unitLabelDx = new wxStaticText( m_gridPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelDx->Wrap( -1 );
	fgSizer2->Add( m_unitLabelDx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelDy = new wxStaticText( m_gridPanel, wxID_ANY, _("y Spacing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelDy->Wrap( -1 );
	fgSizer2->Add( m_labelDy, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryDy = new wxTextCtrl( m_gridPanel, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryDy, 0, wxALL, 5 );
	
	m_unitLabelDy = new wxStaticText( m_gridPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelDy->Wrap( -1 );
	fgSizer2->Add( m_unitLabelDy, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelOffsetX = new wxStaticText( m_gridPanel, wxID_ANY, _("x Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelOffsetX->Wrap( -1 );
	fgSizer2->Add( m_labelOffsetX, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryOffsetX = new wxTextCtrl( m_gridPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryOffsetX, 0, wxALL, 5 );
	
	m_unitLabelOffsetX = new wxStaticText( m_gridPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelOffsetX->Wrap( -1 );
	fgSizer2->Add( m_unitLabelOffsetX, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelOffsetY = new wxStaticText( m_gridPanel, wxID_ANY, _("y Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelOffsetY->Wrap( -1 );
	fgSizer2->Add( m_labelOffsetY, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryOffsetY = new wxTextCtrl( m_gridPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryOffsetY, 0, wxALL, 5 );
	
	m_unitLabelOffsetY = new wxStaticText( m_gridPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelOffsetY->Wrap( -1 );
	fgSizer2->Add( m_unitLabelOffsetY, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelStaggerX = new wxStaticText( m_gridPanel, wxID_ANY, _("x Stagger:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelStaggerX->Wrap( -1 );
	fgSizer2->Add( m_labelStaggerX, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryStaggerX = new wxTextCtrl( m_gridPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryStaggerX, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( m_gridPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer2->Add( m_staticText30, 0, wxALL, 5 );
	
	m_labelStaggerY = new wxStaticText( m_gridPanel, wxID_ANY, _("y Stagger:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelStaggerY->Wrap( -1 );
	fgSizer2->Add( m_labelStaggerY, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_entryStaggerY = new wxTextCtrl( m_gridPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_entryStaggerY, 0, wxALL, 5 );
	
	m_staticText32 = new wxStaticText( m_gridPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer2->Add( m_staticText32, 0, wxALL, 5 );
	
	
	m_gridPanel->SetSizer( fgSizer2 );
	m_gridPanel->Layout();
	fgSizer2->Fit( m_gridPanel );
	m_gridTypeNotebook->AddPage( m_gridPanel, _("Grid"), true );
	m_circularPanel = new wxPanel( m_gridTypeNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labelCentreX = new wxStaticText( m_circularPanel, wxID_ANY, _("x Centre:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelCentreX->Wrap( -1 );
	fgSizer21->Add( m_labelCentreX, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryCentreX = new wxTextCtrl( m_circularPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_entryCentreX, 0, wxALL, 5 );
	
	m_unitLabelCentreX = new wxStaticText( m_circularPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelCentreX->Wrap( -1 );
	fgSizer21->Add( m_unitLabelCentreX, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelCentreY = new wxStaticText( m_circularPanel, wxID_ANY, _("y Centre:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelCentreY->Wrap( -1 );
	fgSizer21->Add( m_labelCentreY, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryCentreY = new wxTextCtrl( m_circularPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_entryCentreY, 0, wxALL, 5 );
	
	m_unitLabelCentreY = new wxStaticText( m_circularPanel, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelCentreY->Wrap( -1 );
	fgSizer21->Add( m_unitLabelCentreY, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelCircAngle = new wxStaticText( m_circularPanel, wxID_ANY, _("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelCircAngle->Wrap( -1 );
	fgSizer21->Add( m_labelCircAngle, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryCircAngle = new wxTextCtrl( m_circularPanel, wxID_ANY, _("90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_entryCircAngle, 0, wxALL, 5 );
	
	m_unitLabelCircAngle = new wxStaticText( m_circularPanel, wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_unitLabelCircAngle->Wrap( -1 );
	fgSizer21->Add( m_unitLabelCircAngle, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_labelCircCount = new wxStaticText( m_circularPanel, wxID_ANY, _("Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelCircCount->Wrap( -1 );
	fgSizer21->Add( m_labelCircCount, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryCircCount = new wxTextCtrl( m_circularPanel, wxID_ANY, _("4"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_entryCircCount, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( m_circularPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer21->Add( m_staticText24, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( m_circularPanel, wxID_ANY, _("Rotate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer21->Add( m_staticText25, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_entryRotateItemsCb = new wxCheckBox( m_circularPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_entryRotateItemsCb, 0, wxALL, 5 );
	
	
	m_circularPanel->SetSizer( fgSizer21 );
	m_circularPanel->Layout();
	fgSizer21->Fit( m_circularPanel );
	m_gridTypeNotebook->AddPage( m_circularPanel, _("Circular"), false );
	
	bMainSizer->Add( m_gridTypeNotebook, 0, wxEXPAND | wxALL, 5 );
	
	m_stdButtons = new wxStdDialogButtonSizer();
	m_stdButtonsOK = new wxButton( this, wxID_OK );
	m_stdButtons->AddButton( m_stdButtonsOK );
	m_stdButtonsCancel = new wxButton( this, wxID_CANCEL );
	m_stdButtons->AddButton( m_stdButtonsCancel );
	m_stdButtons->Realize();
	
	bMainSizer->Add( m_stdButtons, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bMainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_CREATE_ARRAY_BASE::OnClose ) );
	m_entryNx->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryNy->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryDx->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryDy->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryOffsetX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryOffsetY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryStaggerX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryStaggerY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCentreX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCentreY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCircAngle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCircCount->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_stdButtonsCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnCancelClick ), NULL, this );
	m_stdButtonsOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnOkClick ), NULL, this );
}

DIALOG_CREATE_ARRAY_BASE::~DIALOG_CREATE_ARRAY_BASE()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_CREATE_ARRAY_BASE::OnClose ) );
	m_entryNx->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryNy->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryDx->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryDy->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryOffsetX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryOffsetY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryStaggerX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryStaggerY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCentreX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCentreY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCircAngle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_entryCircCount->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnParameterChanged ), NULL, this );
	m_stdButtonsCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnCancelClick ), NULL, this );
	m_stdButtonsOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_CREATE_ARRAY_BASE::OnOkClick ), NULL, this );
	
}
