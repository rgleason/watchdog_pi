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
#include <algorithm>

NewAlarmDialog::NewAlarmDialog(wxWindow* parent)
    : NewAlarmDialogBase(parent)
{
    // Set up two columns: Alarm Type and Description
    m_lAlarmType->InsertColumn(0, _("Alarm Type"), wxLIST_FORMAT_LEFT, 120);
    m_lAlarmType->InsertColumn(1, _("Description"), wxLIST_FORMAT_LEFT, 300);


    // fill the list
    m_alarmTypeList = {
        {ANCHOR, _("Anchor"), _("Alerts when boat drifts beyond set radius from anchor position")},
        {BOUNDARY, _("Boundary"), _("Alerts when crossing user-defined boundaries or exclusion zones")},
        {COURSE, _("Course"), _("Alerts when boat deviates from set course by specified angle")},
        {CROSSTRACKERROR, _("Cross Track Error"), _("Alerts when boat deviates from planned route or track corridor")},
        {DEADMAN, _("Deadman"), _("Alerts after no user activity for specified time period")},
        {DEPTH, _("Depth"), _("Monitors water depth - alerts on shallow/deep water or rapid depth changes")},
        {LANDFALL, _("Landfall"), _("Alerts when approaching land or crossing coastline")},
        {NMEADATA, _("NMEA Data"), _("Alerts when required NMEA sentences are not received")},
        {PYPILOT, _("Pypilot"), _("Monitors autopilot status - hardware errors and steering problems")},
        {RUDDER, _("Rudder"), _("Alerts when rudder angle exceeds set limits")},
        {SPEED, _("Speed"), _("Monitors speed over ground - alerts on over/under speed conditions")},
        {WEATHER, _("Weather"), _("Monitors weather data - barometer, temperature, humidity changes")},
        {WIND, _("Wind"), _("Monitors wind speed and direction - alerts on wind changes")}
    };

    // Sort alphabetically on label
    std::sort(m_alarmTypeList.begin(), m_alarmTypeList.end(), [](const AlarmTypeEntry& a, const AlarmTypeEntry& b) {
        return a.label.CmpNoCase(b.label) < 0;
    });

    // Add to GUI list
    for(const auto& entry : m_alarmTypeList) {
        long idx = m_lAlarmType->InsertItem(m_lAlarmType->GetItemCount(), entry.label);
        m_lAlarmType->SetItem(idx, 1, entry.description);
    }

    // Auto-size columns
    m_lAlarmType->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_lAlarmType->SetColumnWidth(1, wxLIST_AUTOSIZE);
}
// added to sort alarmtypes alphabetically
int NewAlarmDialog::GetSelectedAlarmType() const
{
    long selectedIndex = m_lAlarmType->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(selectedIndex < 0 || selectedIndex >= (long)m_alarmTypeList.size())
        return -1;

    return m_alarmTypeList[selectedIndex].id;
}
