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

#ifndef __DIALOG_CREATE_ARRAY__
#define __DIALOG_CREATE_ARRAY__

// Include the wxFormBuider header base:
#include <dialog_create_array_base.h>

class DIALOG_CREATE_ARRAY: public DIALOG_CREATE_ARRAY_BASE
{
public:

    enum CREATE_ARRAY_EDIT_T
    {
        CREATE_ARRAY_ABORT,     ///< if not changed or error
        CREATE_ARRAY_OK,        ///< if successfully changed
    };

    enum ARRAY_TYPE_T
    {
        ARRAY_GRID,         ///< A grid (x*y) array
        ARRAY_CIRCULAR,     ///< A circular array
    };

    /**
     * Persistent dialog options
     */
    struct ARRAY_OPTIONS
    {
        ARRAY_OPTIONS( ARRAY_TYPE_T type_ ):
            type( type_ )
        {}

        virtual ~ARRAY_OPTIONS() {};

        ARRAY_TYPE_T type;

        /*!
         * Function GetArrayPositions
         * Returns the set of points that represent the array
         * in order, if that is important
         *
         * TODO: Can/should this be done with some sort of iterator?
         */
        virtual void TransformItem( int n, BOARD_ITEM* item, const wxPoint& rotPoint ) const = 0;
        virtual int GetArraySize() const = 0;
    };

    struct ARRAY_GRID_OPTIONS: public ARRAY_OPTIONS
    {
        ARRAY_GRID_OPTIONS():
            ARRAY_OPTIONS( ARRAY_GRID ),
            m_nx( 0 ), m_ny( 0 ),
            m_horizontalThenVertical( true ),
            m_reverseNumberingAlternate( false ),
            m_stagger( 0 ),
            m_stagger_rows( true )
        {}

        long m_nx, m_ny;
        bool m_horizontalThenVertical, m_reverseNumberingAlternate;
        wxPoint m_delta;
        wxPoint m_offset;
        long m_stagger;
        bool m_stagger_rows;

        void TransformItem( int n, BOARD_ITEM* item, const wxPoint& rotPoint ) const; // override virtual
        int GetArraySize() const; // override virtual
    };

    struct ARRAY_CIRCULAR_OPTIONS: public ARRAY_OPTIONS
    {
        ARRAY_CIRCULAR_OPTIONS():
            ARRAY_OPTIONS( ARRAY_CIRCULAR ),
            n_pts( 0 ),
            d_angle( 0.0f ),
            m_rotateItems( false )
        {}

        long n_pts;
        double d_angle;
        wxPoint centre;
        bool m_rotateItems;

        void TransformItem( int n, BOARD_ITEM* item, const wxPoint& rotPoint ) const; // override virtual
        int GetArraySize() const; // override virtual
    };

    // Constructor and destructor
    DIALOG_CREATE_ARRAY( PCB_BASE_FRAME* aParent, ARRAY_OPTIONS** settings );
    virtual ~DIALOG_CREATE_ARRAY() {};

private:

    // the settings object returned to the caller
    // we update the caller's object and never have ownership
    ARRAY_OPTIONS** m_settings;

    void OnParameterChanged( wxCommandEvent& event );
    void OnCancelClick( wxCommandEvent& event );
    void OnOkClick( wxCommandEvent& event );

    void saveDialogOptions();

    struct CREATE_ARRAY_DIALOG_ENTRIES
    {
        CREATE_ARRAY_DIALOG_ENTRIES():
            m_optionsSet( false ),
            m_gridStaggerType( 0 ),
            m_gridNumberingAxis( 0 ),
            m_gridNumberingReverseAlternate( false ),
            m_circRotate( false ),
            m_arrayTypeTab( 0 )
        {}

        bool m_optionsSet;

        wxString m_gridNx, m_gridNy,
                 m_gridDx, m_gridDy,
                 m_gridOffsetX, m_gridOffsetY,
                 m_gridStagger,
                 m_circCentreX, m_circCentreY,
                 m_circAngle,
                 m_circCount;

        int m_gridStaggerType, m_gridNumberingAxis;
        bool m_gridNumberingReverseAlternate;
        bool m_circRotate;
        int m_arrayTypeTab;
    };

    static CREATE_ARRAY_DIALOG_ENTRIES m_options;
};

#endif      //  __DIALOG_CREATE_ARRAY__
