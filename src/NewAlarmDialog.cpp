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

#include "watchdog_pi.h"
#include "NewAlarmDialog.h"

NewAlarmDialog::NewAlarmDialog(wxWindow* parent)
    : NewAlarmDialogBase(parent)
{
    // Set up two columns: Alarm Type and Description
    m_lAlarmType->InsertColumn(0, _("Alarm Type"), wxLIST_FORMAT_LEFT, 120);
    m_lAlarmType->InsertColumn(1, _("Description"), wxLIST_FORMAT_LEFT, 300);
    
    // Add alarm types with descriptions
    long index;
    
    index = m_lAlarmType->InsertItem(ANCHOR, _("Anchor"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when boat drifts beyond set radius from anchor position"));
    
    index = m_lAlarmType->InsertItem(DEPTH, _("Depth"));
    m_lAlarmType->SetItem(index, 1, _("Monitors water depth - alerts on shallow/deep water or rapid depth changes"));
    
    index = m_lAlarmType->InsertItem(COURSE, _("Course"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when boat deviates from set course by specified angle"));
    
    index = m_lAlarmType->InsertItem(SPEED, _("Speed"));
    m_lAlarmType->SetItem(index, 1, _("Monitors speed over ground - alerts on over/under speed conditions"));
    
    index = m_lAlarmType->InsertItem(WIND, _("Wind"));
    m_lAlarmType->SetItem(index, 1, _("Monitors wind speed and direction - alerts on wind changes"));
    
    index = m_lAlarmType->InsertItem(WEATHER, _("Weather"));
    m_lAlarmType->SetItem(index, 1, _("Monitors weather data - barometer, temperature, humidity changes"));
    
    index = m_lAlarmType->InsertItem(DEADMAN, _("Deadman"));
    m_lAlarmType->SetItem(index, 1, _("Alerts after no user activity for specified time period"));
    
    index = m_lAlarmType->InsertItem(NMEADATA, _("NMEA Data"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when required NMEA sentences are not received"));
    
    index = m_lAlarmType->InsertItem(LANDFALL, _("Landfall"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when approaching land or crossing coastline"));
    
    index = m_lAlarmType->InsertItem(BOUNDARY, _("Boundary"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when crossing user-defined boundaries or exclusion zones"));
    
    index = m_lAlarmType->InsertItem(PYPILOT, _("Pypilot"));
    m_lAlarmType->SetItem(index, 1, _("Monitors autopilot status - hardware errors and steering problems"));
    
    
    index = m_lAlarmType->InsertItem(RUDDER, _("Rudder"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when rudder angle exceeds set limits"));
    
    index = m_lAlarmType->InsertItem(CROSSTRACKERROR, _("Cross Track Error"));
    m_lAlarmType->SetItem(index, 1, _("Alerts when boat deviates from planned route or track corridor"));
    
    // Auto-size columns
    m_lAlarmType->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_lAlarmType->SetColumnWidth(1, wxLIST_AUTOSIZE);
}
