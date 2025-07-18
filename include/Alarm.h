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

#include <vector>
#include <list>

class piDC;
class TiXmlElement;

enum AlarmType {ANCHOR, COURSE, SPEED, WIND, WEATHER, DEADMAN, NMEADATA, DEPTH, LANDFALL, BOUNDARY, RUDDER, PYPILOT, CROSSTRACKERROR};

class Alarm : public wxEvtHandler {
public:
    static void RenderAll(piDC &dc, PlugIn_ViewPort &vp);
    static void LoadConfigAll();
    static void SaveConfigAll();
    static void DeleteAll();
    static void ResetAll();
    static void StopAll();
    static void NMEAStringAll(const wxString &sentence);
    static Alarm *NewAlarm(enum AlarmType type);
    static void SaveAlarms(wxString filename);
    static void LoadAlarms(wxString filename);

    static std::vector<Alarm*> s_Alarms;

    Alarm(bool gfx=false, int interval=1);
    virtual ~Alarm();

    wxString Action();
    virtual void Run();

    virtual wxString Type() = 0;
    virtual bool Test() = 0;
    virtual wxString GetStatus() = 0;
    virtual int GetCount() { return m_count; }
    virtual void NMEAString(const wxString &sentence) {}
    virtual void Render(piDC &dc, PlugIn_ViewPort &vp) {}
    virtual wxWindow *OpenPanel(wxWindow *parent) = 0;
    virtual void SavePanel(wxWindow *panel) = 0;
    virtual void LoadConfig(TiXmlElement *e) = 0;
    virtual void SaveConfig(TiXmlElement *c) = 0;
    virtual void OnAISMessage(int iAlarmIndex) {return;}
    virtual void OnAISMessage() {return;}

    void LoadConfigBase(TiXmlElement *e);
    void SaveConfigBase(TiXmlElement *c);

    virtual void OnTimer(wxTimerEvent &);
    virtual void StopTimer();

    void Reset() { m_bFired = false; m_count = 0; }

    bool m_bHasGraphics, m_bEnabled, m_bgfxEnabled, m_bFired, m_bSpecial;

protected:
    bool m_bSound, m_bCommand, m_bMessageBox, m_bNoData, m_bRepeat, m_bAutoReset;
    wxString m_sSound, m_sCommand;
    wxDateTime m_LastAlarmTime;
    int m_iRepeatSeconds;
    int m_iDelay;

    wxTimer    m_Timer;
    wxDateTime m_DelayTime;

private:
    friend class EditAlarmDialog;

    void ConfigItem(bool read, wxString name, wxControl *control);
    virtual void GetStatusControls(wxControl *&Text, wxControl *&status) { Text = status = NULL; }
    virtual wxString MessageBoxText() { return ""; }

    int m_interval, m_count;
};

class TestAlarm : public Alarm
{
public:
    TestAlarm() {}
    wxString Type() { return _("Test"); }
    bool Test() { return false; }
    wxString GetStatus() { return _T(""); }
    wxWindow *OpenPanel(wxWindow *parent) { return NULL; }
    void SavePanel(wxWindow *p) {}
    void LoadConfig(TiXmlElement *e) {}
    void SaveConfig(TiXmlElement *c) {}
};

enum WeatherAlarmVariable {BAROMETER, AIR_TEMPERATURE, SEA_TEMPERATURE, RELATIVE_HUMIDITY};
