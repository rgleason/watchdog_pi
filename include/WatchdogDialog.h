/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  watchdog Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include "WatchdogUI.h"

#ifdef __WXMSW__
#include "GL/gl.h"            // local copy for Windows
#include <GL/glu.h>
#else
#endif

class watchdog_pi;

class WatchdogDialog: public WatchdogDialogBase
{
public:
    WatchdogDialog( watchdog_pi &_watchdog_pi, wxWindow* parent);
    ~WatchdogDialog();

    void UpdateAlarms();
    void UpdateStatus(int index);

    void OnDoubleClick( wxMouseEvent& event );
    void OnLeftDown( wxMouseEvent& event );
    void OnRightDown( wxMouseEvent& event );
    void OnNew( wxCommandEvent& event );
    void OnEdit( wxCommandEvent& event );
    void OnReset( wxCommandEvent& event );
    void OnDelete( wxCommandEvent& event );
    void OnResetAll( wxCommandEvent& event );
    void OnDeleteAll( wxCommandEvent& event );
    void OnConfiguration( wxCommandEvent& event );
    
private:
    long HitTest(wxPoint pos, int);
    watchdog_pi &m_watchdog_pi;
    Alarm *m_menualarm;
};
