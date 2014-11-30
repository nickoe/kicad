/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2014 John Beard, john.j.beard@gmail.com
 * Copyright (C) 1992-2014 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <wxPcbStruct.h>
#include <base_units.h>

#include <class_drawpanel.h>
#include <class_board.h>
#include <class_module.h>

#include "dialog_create_array.h"

DIALOG_CREATE_ARRAY::DIALOG_CREATE_ARRAY( PCB_BASE_FRAME* aParent, ARRAY_OPTIONS** settings ):
        DIALOG_CREATE_ARRAY_BASE( aParent ),
        m_settings( settings )
{
}


void DIALOG_CREATE_ARRAY::OnParameterChanged( wxCommandEvent& event )
{
   event.Skip();
}

void DIALOG_CREATE_ARRAY::OnCancelClick( wxCommandEvent& event )
{
    EndModal( CREATE_ARRAY_ABORT );
}


void DIALOG_CREATE_ARRAY::OnOkClick( wxCommandEvent& event )
{
    ARRAY_OPTIONS* newSettings = NULL;

    const wxWindow* page = m_gridTypeNotebook->GetCurrentPage();

    if ( page == m_gridPanel )
    {
        ARRAY_GRID_OPTIONS* newGrid = new ARRAY_GRID_OPTIONS();
        bool ok = true;
        double x, y;

        // ints
        ok = ok && m_entryNx->GetValue().ToLong( &newGrid->n_x );
        ok = ok && m_entryNy->GetValue().ToLong( &newGrid->n_y );


        ok = ok && m_entryDx->GetValue().ToDouble( &x );
        ok = ok && m_entryDy->GetValue().ToDouble( &y );

        newGrid->delta.x = From_User_Unit( g_UserUnit, x );
        newGrid->delta.y = From_User_Unit( g_UserUnit, y );

        ok = ok && m_entryOffsetX->GetValue().ToDouble( &x );
        ok = ok && m_entryOffsetY->GetValue().ToDouble( &y );

        newGrid->offset.x = From_User_Unit( g_UserUnit, x );
        newGrid->offset.y = From_User_Unit( g_UserUnit, y );

        ok = ok && m_entryStaggerX->GetValue().ToLong( &newGrid->stagger_x );
        ok = ok && m_entryStaggerY->GetValue().ToLong( &newGrid->stagger_y );

        // Only use settings if all values are good
        if ( ok )
            newSettings = newGrid;
    }
    else if ( page == m_circularPanel )
    {
        ARRAY_CIRCULAR_OPTIONS* newCirc = new ARRAY_CIRCULAR_OPTIONS();
        bool ok = true;

        double x, y;
        ok = ok && m_entryCentreX->GetValue().ToDouble( &x );
        ok = ok &&m_entryCentreY->GetValue().ToDouble( &y );

        newCirc->centre.x = From_User_Unit( g_UserUnit, x );
        newCirc->centre.y = From_User_Unit( g_UserUnit, y );

        ok = ok && m_entryCircAngle->GetValue().ToDouble( &newCirc->d_angle );
        ok = ok && m_entryCircCount->GetValue().ToLong( &newCirc->n_pts );

        newCirc->m_rotateItems = m_entryRotateItemsCb->GetValue();

        // Only use settings if all values are good
        if ( ok )
            newSettings = newCirc;
    }

    // If we got good settings, send them out and finish
    if (newSettings)
    {
        delete *m_settings;

        // assign pointer and ownership here
        *m_settings = newSettings;

        EndModal( CREATE_ARRAY_OK );
    }
 }

// ARRAY OPTION implementation functions

int DIALOG_CREATE_ARRAY::ARRAY_GRID_OPTIONS::GetArraySize() const
{
    return n_x * n_y;
}

void DIALOG_CREATE_ARRAY::ARRAY_GRID_OPTIONS::TransformItem( int n, BOARD_ITEM* item ) const
{
    wxPoint point;

    // left-to-right, top-to-bottom
    const int x = n % n_x;
    const int y = n / n_x;

    point.x = x * delta.x + y * offset.x;
    point.y = y * delta.y + x * offset.y;

    if(stagger_y > 1)
    {
        const int stagger_idx = ( y % stagger_y );
        point.x += ( delta.x / stagger_y) * stagger_idx;
        point.y += ( offset.y / stagger_y) * stagger_idx;
    }

    if(stagger_x > 1)
    {
        const int stagger_idx = ( x % stagger_x );
        point.y += ( delta.y / stagger_x) * stagger_idx;
        point.x += (offset.x / stagger_x ) * stagger_idx;
    }

    // this is already relative to the first array entry
    item->Move( point );
}

int DIALOG_CREATE_ARRAY::ARRAY_CIRCULAR_OPTIONS::GetArraySize() const
{
    return n_pts;
}

void DIALOG_CREATE_ARRAY::ARRAY_CIRCULAR_OPTIONS::TransformItem( int n, BOARD_ITEM* item ) const
{
    const double angle = d_angle * n * 10;

    item->Rotate( centre, angle);

    //take off the rotation (but not the translation) if needed
    if ( !m_rotateItems )
    {
        item->Rotate( item->GetCenter(), -angle);
    }
}
