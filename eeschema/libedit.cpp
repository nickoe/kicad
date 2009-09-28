/****************************/
/*  EESchema - libedit.cpp  */
/****************************/

/* Routines de maintenanace des librairies:
 *   sauvegarde, modification de librairies.
 *   creation edition suppression de composants
 */

#include "fctsys.h"
#include "gr_basic.h"
#include "common.h"
#include "class_drawpanel.h"
#include "confirm.h"
#include "gestfich.h"
#include "eeschema_id.h"

#include "program.h"
#include "general.h"
#include "protos.h"
#include "libeditfrm.h"
#include "class_library.h"

#include "dialog_create_component.h"


/* Affiche dans la zone messages la librairie , et le composant edite */
void WinEDA_LibeditFrame::DisplayLibInfos()
{
    wxString msg = _( "Component Library Editor: " );

    if( m_library )
        msg += m_library->GetFullFileName();
    else
        msg += _( "no library selected" );

    SetTitle( msg );
}


/* Function to select the current library (working library) */
void WinEDA_LibeditFrame::SelectActiveLibrary()
{
    CMP_LIBRARY* Lib;

    Lib = SelectLibraryFromList( this );
    if( Lib )
    {
        m_library = Lib;
    }
    DisplayLibInfos();
}


/**
 * Function LoadOneLibraryPart()
 * load a library component from the current selected library
 * Prompt user for component name
 * If there is no current selected library,
 * prompt user for library name and make the selected library the current lib.
 */
void WinEDA_LibeditFrame::LoadOneLibraryPart( wxCommandEvent& event )
{
    int            i;
    wxString       msg;
    wxString       CmpName;
    CMP_LIB_ENTRY* LibEntry = NULL;

    DrawPanel->UnManageCursor( 0, wxCURSOR_ARROW );

    if( GetBaseScreen()->IsModify() && !IsOK( this, _( "Current part not \
saved.\n\nDiscard current changes?" ) ) )
        return;

     // No current lib, ask user for the library to use.
    if( m_library == NULL )
    {
        SelectActiveLibrary();
        if( m_library == NULL )
            return;
    }

    i = GetNameOfPartToLoad( this, m_library, CmpName );
    if( i == 0 )
        return;

    GetBaseScreen()->ClrModify();
    m_lastDrawItem = m_drawItem = NULL;

    // Delete previous library component, if any
    if( m_component )
    {
        SAFE_DELETE( m_component );
    }

    /* Load the new library component */
    LibEntry = m_library->FindEntry( CmpName );

    if( LibEntry == NULL )
    {
        msg.Printf( _( "Component or alias name \"%s\" not found in \
library \"%s\"." ),
                    (const wxChar*) CmpName,
                    (const wxChar*) m_library->GetName() );
        DisplayError( this, msg );
        return;
    }

    if( !LoadOneLibraryPartAux( LibEntry, m_library ) )
        return;

    g_EditPinByPinIsOn = false;
    GetScreen()->ClearUndoRedoList();
    Zoom_Automatique( false );
    DrawPanel->Refresh();
}


/*
 * Routine Pour Charger en memoire la copie de 1 libpart.
 *  retourne
 *  0 si OK
 *  1 si err
 *  m_component pointe la copie ainsi creee
 */
bool WinEDA_LibeditFrame::LoadOneLibraryPartAux( CMP_LIB_ENTRY* LibEntry,
                                                 CMP_LIBRARY*   Library )
{
    wxString msg, cmpName, rootName;
    LIB_COMPONENT* component;

    if( ( LibEntry == NULL ) || ( Library == NULL ) )
        return false;

    if( LibEntry->GetName().IsEmpty() )
    {
        wxLogWarning( wxT( "Entry in library <%s> has empty name field." ),
                      (const wxChar*) LibEntry );
        return false;
    }

    cmpName = LibEntry->GetName();
    m_aliasName.Empty();

    if( LibEntry->Type != ROOT )
    {
        LIB_ALIAS* alias = (LIB_ALIAS*) LibEntry;
        component = alias->GetComponent();

        wxASSERT( component != NULL && component->Type == ROOT );

        wxLogDebug( wxT( "\"<%s>\" is alias of \"<%s>\"" ),
                    (const wxChar*) cmpName,
                    (const wxChar*) component->GetName() );

        m_aliasName = cmpName;
    }
    else
    {
        component = (LIB_COMPONENT*) LibEntry;
    }

    if( m_component )
        SAFE_DELETE( m_component );

    m_component = new LIB_COMPONENT( *component );

    if( m_component == NULL )
    {
        msg.Printf( _( "Could not create copy of part <%s> in library <%s>." ),
                    (const wxChar*) LibEntry->GetName(),
                    (const wxChar*) Library->GetName() );
        DisplayError( this, msg );
        return false;
    }

    m_unit = 1;
    m_convert = 1;

    m_showDeMorgan = false;

    if( LookForConvertPart( m_component ) > 1 )
        m_showDeMorgan = true;

    GetBaseScreen()->ClrModify();
    DisplayLibInfos();
    UpdateAliasSelectList();
    UpdatePartSelectList();

    /* Display the document information based on the entry selected just in
     * case the entry is an alias. */
    DisplayCmpDoc();

    return true;
}


/* Function to redraw the current loaded library component */
void WinEDA_LibeditFrame::RedrawActiveWindow( wxDC* DC, bool EraseBg )
{
    if( GetScreen() == NULL )
        return;

    ActiveScreen = GetScreen();

    DC->SetBackground( *wxBLACK_BRUSH );
    DC->SetBackgroundMode( wxTRANSPARENT );
    GRResetPenAndBrush( DC );

    DrawPanel->CursorOff( DC ); // erase cursor
    if( DrawPanel->ManageCurseur )
    {
        DrawPanel->ManageCurseur( DrawPanel, DC, false );
    }

    if( EraseBg )
        DrawPanel->EraseScreen( DC );

    DrawPanel->DrawBackGround( DC );

    if( m_component )
        m_component->Draw( DrawPanel, DC, wxPoint( 0, 0 ), m_unit,
                           m_convert, GR_DEFAULT_DRAWMODE );

    DrawPanel->CursorOn( DC ); // redraw cursor

    if( DrawPanel->ManageCurseur )
    {
        DrawPanel->ManageCurseur( DrawPanel, DC, false );
    }

    GetScreen()->ClrRefreshReq();
    DisplayLibInfos();
    UpdateStatusBar();
}


/*
 * Save (on disk) the current library
 *  if exists the old file is renamed (.bak)
 */
void WinEDA_LibeditFrame::SaveActiveLibrary( wxCommandEvent& event )
{
    wxFileName fn;
    wxString   msg;

    DrawPanel->UnManageCursor( 0, wxCURSOR_ARROW );

    if( GetScreen()->IsModify() )
    {
        if( IsOK( this, _( "Include last component changes?" ) ) )
            SaveOnePartInMemory();
    }

    if( m_library == NULL )
    {
        DisplayError( this, wxT( "No library specified." ) );
        return;
    }

    fn = wxFileName( m_library->GetFullFileName() );

    msg = _( "Modify library file \"" ) + fn.GetFullPath() + _( "\"?" );

    if( !IsOK( this, msg ) )
        return;

    bool success = m_library->Save( fn.GetFullPath() );

    MsgPanel->EraseMsgBox();

    if( !success )
    {
        msg = _( "Error while saving library file \"" ) + fn.GetFullPath() +
              _( "\"." );
        MsgPanel->Affiche_1_Parametre( 1, wxT( "*** ERROR: ***" ), msg, RED );
        DisplayError( this, msg );
    }
    else
    {
        msg = _( "Library file \"" ) + fn.GetFullName() + wxT( "\" Ok" );
        fn.SetExt( DOC_EXT );
        wxString msg1 = _( "Document file \"" ) + fn.GetFullPath() +
                        wxT( "\" Ok" );
        MsgPanel->Affiche_1_Parametre( 1, msg, msg1, BLUE );
    }
}


/*
 *  Affiche la documentation du composant selectionne
 *  Utilis�e lors de l'affichage de la liste des composants en librairie
 */
void WinEDA_LibeditFrame::DisplayCmpDoc()
{
    wxString msg;
    LIB_ALIAS* alias = NULL;

    MsgPanel->EraseMsgBox();

    if( m_library == NULL || m_component == NULL )
        return;

    msg = m_component->GetName();

    MsgPanel->AppendMessage( _( "Part" ), msg, BLUE, 8 );

    if( m_aliasName.IsEmpty() )
    {
        msg = _( "None" );
    }
    else
    {
        msg = m_aliasName;
        alias = m_library->FindAlias( m_aliasName );
    }

    MsgPanel->AppendMessage( _( "Alias" ), msg, RED, 8 );

    static wxChar UnitLetter[] = wxT( "?ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
    msg = UnitLetter[m_unit];

    MsgPanel->AppendMessage( _( "Unit" ), msg, BROWN, 8 );

    if( m_convert > 1 )
        msg = _( "Convert" );
    else
        msg = _( "Normal" );

    MsgPanel->AppendMessage( _( "Body" ), msg, GREEN, 8 );

    if( m_component->m_Options == ENTRY_POWER )
        msg = _( "Power Symbol" );
    else
        msg = _( "Component" );

    MsgPanel->AppendMessage( _( "Type" ), msg, MAGENTA, 8 );

    if( alias != NULL )
        msg = alias->m_Doc;
    else
        msg = m_component->m_Doc;

    MsgPanel->AppendMessage( _( "Description" ), msg, CYAN, 8 );

    if( alias != NULL )
        msg = alias->m_KeyWord;
    else
        msg = m_component->m_KeyWord;

    MsgPanel->AppendMessage( _( "Key words" ), msg, DARKDARKGRAY );
}


/*
 * Routine de suppression d'un composant dans la librairie courante
 *  (effacement en memoire uniquement, le fichier n'est pas modifie)
 *  Le composant peut etre un alias, ou la definition de base.
 *  Si c'est un alias:
 *  il est supprime, et la liste des alias de la definition
 *  de base est modifiee
 *  Si c'est le composant de base:
 *  Si la liste des alias est nulle, il est supprime
 *  Sinon le premier alias devient le composant de base, et les autres
 *  alias deviennent dependants de celui ci.
 */
void WinEDA_LibeditFrame::DeleteOnePart( wxCommandEvent& event )
{
    wxString       CmpName;
    CMP_LIB_ENTRY* LibEntry;
    wxArrayString  ListNames;
    wxString       msg;

    DrawPanel->UnManageCursor( 0, wxCURSOR_ARROW );

    m_lastDrawItem = NULL;
    m_drawItem = NULL;

    if( m_library == NULL )
    {
        SelectActiveLibrary();

        if( m_library == NULL )
        {
            DisplayError( this, _( "Please select a component library." ) );
            return;
        }
    }

    m_library->GetEntryNames( ListNames );

    if( ListNames.IsEmpty() )
    {
        msg.Printf( _( "Component library <%s> is empty." ),
                    ( const wxChar* ) m_library->GetName() );
        wxMessageBox( msg, _( "Delete Entry Error" ),
                      wxID_OK | wxICON_EXCLAMATION, this );
        return;
    }

    msg.Printf( _( "Select 1 of %d components to delete\nfrom library <%s>." ),
                ListNames.GetCount(),
                ( const wxChar* ) m_library->GetName() );

    wxSingleChoiceDialog dlg( this, msg, _( "Delete Component" ), ListNames );

    if( dlg.ShowModal() == wxID_CANCEL || dlg.GetStringSelection().IsEmpty() )
        return;

    LibEntry = m_library->FindEntry( dlg.GetStringSelection() );

    if( LibEntry == NULL )
    {
        msg.Printf( _( "Entry <%s> not found in library <%s>." ),
                    ( const wxChar* ) dlg.GetStringSelection(),
                    ( const wxChar* ) m_library->GetName() );
        DisplayError( this, msg );
        return;
    }

    msg.Printf( _( "Delete component \"%s\" from library \"%s\"?" ),
                (const wxChar*) LibEntry->GetName(),
                (const wxChar*) m_library->GetName() );

    if( !IsOK( this, msg ) )
        return;

    if( m_component == NULL
        || ( m_component->GetName().CmpNoCase( LibEntry->GetName() ) != 0
             && !m_component->HasAlias( LibEntry->GetName() ) ) )
    {
        m_library->RemoveEntry( LibEntry );
        return;
    }

    /* If deleting the current entry or removing one of the aliases for
     * the current entry, sync the changes in the current entry as well.
     */

    if( GetScreen()->IsModify()
        && !IsOK( this, _( "The component being deleted has been modified. \
All changes will be lost. Discard changes?" ) ) )
        return;

    wxString newCmpName;
    CMP_LIB_ENTRY* nextEntry;

    /*
     * If the current component has no aliases, then the next entry
     * in the library will be shown.  If the current component has
     * aliases, the updated component will be shown
     */
    if( m_component->GetName().CmpNoCase( LibEntry->GetName() ) == 0 )
    {
        if( m_component->m_AliasList.IsEmpty() )
        {
            nextEntry = m_library->GetNextEntry( m_component->GetName() );

            if( nextEntry != NULL )
                newCmpName = nextEntry->GetName();
        }
        else
        {
            newCmpName = m_component->m_AliasList[ 0 ];
        }
    }
    else
    {
        newCmpName = m_component->GetName();
    }

    m_library->RemoveEntry( LibEntry );

    if( !newCmpName.IsEmpty() )
    {
        nextEntry = m_library->FindEntry( newCmpName );

        if( nextEntry != NULL && LoadOneLibraryPartAux( nextEntry, m_library ) )
            Zoom_Automatique( false );

        DrawPanel->Refresh();
    }
}


/*
 * Routine to create a new library component
 *
 * If an old component is currently in edit, it is deleted.
 */
void WinEDA_LibeditFrame::CreateNewLibraryPart( wxCommandEvent& event )
{
    int            diag;
    wxString       msg;
    LIB_COMPONENT* NewStruct;

    if( m_component && GetScreen()->IsModify()
        && !IsOK( this, _( "All changes to the current component will be \
lost!\n\nClear the current component from the screen?" ) ) )
        return;

    DrawPanel->UnManageCursor( 0, wxCURSOR_ARROW );

    m_drawItem = NULL;

    WinEDA_CreateCmpDialog Dialogbox( this );
    diag = Dialogbox.ShowModal();
    if( diag != wxID_OK )
        return;
    msg = Dialogbox.ReturnCmpName();
    if( msg.IsEmpty() )
        return;
    msg.MakeUpper();
    msg.Replace( wxT( " " ), wxT( "_" ) );

    /* Test: y a t-il un composant deja de ce nom */
    if( m_library )
    {
        if( m_library->FindEntry( msg ) )
        {
            wxString msg;
            msg.Printf( _( "Component \"%s\" already exists in \
library \"%s\"." ),
                        (const wxChar*) Dialogbox.ReturnCmpName(),
                        (const wxChar*) m_library->GetName() );
            DisplayError( this, msg );
            return;
        }
    }

    NewStruct = new LIB_COMPONENT( msg );
    Dialogbox.SetComponentData( *NewStruct );
    if( NewStruct->m_Prefix.m_Text.IsEmpty() )
        NewStruct->m_Prefix.m_Text = wxT( "U" );
    NewStruct->m_Prefix.m_Text.MakeUpper();

    // Effacement ancien composant affich�
    if( m_component )
    {
        SAFE_DELETE( m_component );
    }
    m_component = NewStruct;
    m_unit = 1;
    m_convert  = 1;
    DisplayLibInfos();
    DisplayCmpDoc();
    UpdateAliasSelectList();
    UpdatePartSelectList();
    g_EditPinByPinIsOn = false;
    m_lastDrawItem = NULL;
    GetScreen()->ClearUndoRedoList();
    DrawPanel->Refresh();
}


/*
 * Routine de sauvegarde de la "partlib" courante dans la librairie courante
 *
 * Sauvegarde en memoire uniquement, et PAS sur fichier
 * La routine efface l'ancien composant ( ou / et les alias ) a remplacer
 * s'il existe, et sauve le nouveau et cree les alias correspondants.
 */
void WinEDA_LibeditFrame::SaveOnePartInMemory()
{
    LIB_COMPONENT* oldComponent;
    LIB_COMPONENT* Component;
    wxString       msg;

    if( m_component == NULL )
    {
        DisplayError( this, _( "No component to save." ) );
        return;
    }

    if( m_library == NULL )
        SelectActiveLibrary();

    if( m_library == NULL )
    {
        DisplayError( this, _( "No library specified." ) );
        return;
    }

    GetBaseScreen()->ClrModify();

    oldComponent = m_library->FindComponent( m_component->GetName() );

    if( oldComponent != NULL )
    {
        msg.Printf( _( "Component \"%s\" exists. Change it?" ),
                    (const wxChar*) oldComponent->GetName() );
        if( !IsOK( this, msg ) )
            return;
    }

    m_drawItem = m_lastDrawItem = NULL;

    wxASSERT( m_component->Type == ROOT );

    if( oldComponent != NULL )
        Component = m_library->ReplaceComponent( oldComponent, m_component );
    else
        Component = m_library->AddComponent( m_component );

    if( Component == NULL )
        return;

    msg.Printf( _( "Component %s saved in library %s" ),
                ( const wxChar* ) Component->GetName(),
                ( const wxChar* ) m_library->GetName() );
    Affiche_Message( msg );
}
