/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 20012 Jean-Pierre Charras, jaen-pierre.charras@gipsa-lab.inpg.com
 * Copyright (C) 2008-2012 Wayne Stambaugh <stambaughw@verizon.net>
 * Copyright (C) 1992-2012 KiCad Developers, see AUTHORS.txt for contributors.
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

/**
 * @file wildcards_and_files_ext.cpp
 */
#include <wildcards_and_files_ext.h>

/**
 * file extensions and wildcards used in kicad.
 */

const wxString SchematicSymbolFileExtension( wxT( "sym" ) );
const wxString SchematicLibraryFileExtension( wxT( "lib" ) );
const wxString SchematicBackupFileExtension( wxT( "bak" ) );

const wxString VrmlFileExtension( wxT( "wrl" ) );

const wxString ProjectFileExtension( wxT( "pro" ) );
const wxString SchematicFileExtension( wxT( "sch" ) );
const wxString NetlistFileExtension( wxT( "net" ) );
const wxString FootprintLibFileExtension( wxT( "mod" ) );
const wxString ComponentFileExtension( wxT( "cmp" ) );
const wxString GerberFileExtension( wxT( "pho" ) );
const wxString PcbFileExtension( wxT( "brd" ) );
const wxString PdfFileExtension( wxT( "pdf" ) );
const wxString MacrosFileExtension( wxT( "mcr" ) );
const wxString DrillFileExtension( wxT( "drl" ) );
const wxString SVGFileExtension( wxT( "svg" ) );
const wxString ReportFileExtension( wxT( "rpt" ) );
const wxString FootprintPlaceFileExtension( wxT( "pos" ) );

// These strings are wildcards for file selection dialogs.
// Because thes are static, one should explicitely call wxGetTranslation
// to display them translated.
const wxString SchematicSymbolFileWildcard( _( "KiCad drawing symbol file (*.sym)|*.sym" ) );
const wxString SchematicLibraryFileWildcard( _( "KiCad component library file (*.lib)|*.lib" ) );
const wxString ProjectFileWildcard( _( "KiCad project files (*.pro)|*.pro" ) );
const wxString SchematicFileWildcard( _( "KiCad schematic files (*.sch)|*.sch" ) );
const wxString NetlistFileWildcard( _( "KiCad netlist files (*.net)|*.net" ) );
const wxString GerberFileWildcard( _( "Gerber files (*.pho)|*.pho" ) );
const wxString LegacyPcbFileWildcard( _( "KiCad printed circuit board files (*.brd)|*.brd" ) );
const wxString EaglePcbFileWildcard( _( "Eagle ver. 6.x XML PCB files (*.brd)|*.brd" ) );
const wxString PcbFileWildcard( _( "KiCad s-expr printed circuit board files (*.kicad_pcb)|*.kicad_pcb" ) );
const wxString FootprintLibFileWildcard( _( "KiCad footprint library file (*.mod)|*.mod" ) );
const wxString PdfFileWildcard( _( "Portable document format files (*.pdf)|*.pdf" ) );
const wxString MacrosFileWildcard( _( "KiCad recorded macros (*.mcr)|*.mcr" ) );
const wxString AllFilesWildcard( _( "All files (*)|*" ) );

// Wildcard for cvpcb component to footprint link file
const wxString ComponentFileWildcard( _( "KiCad cmp/footprint link files (*.cmp)|*.cmp" ) );

const wxString DrillFileWildcard( _( "Drill files (*.drl)|*.drl;*.DRL" ) );
const wxString SVGFileWildcard( _( "SVG files (*.svg)|*.svg;*.SVG" ) );
const wxString ReportFileWildcard = _( "Report files (*.rpt)|*.rpt" );
const wxString FootprintPlaceFileWildcard = _( "Footprint place files (*.pos)|*.pos" );
const wxString VrmlFileWildcard( _( "Vrml files (*.wrl)|*.wrl" ) );
