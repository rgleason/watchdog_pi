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
#ifdef DEBUG_BUILD
#  define DEBUGSL(x) do { \
time_t now = time(0); \
tm* localtm = localtime(&now); \
char *stime = asctime(localtm); \
stime[strlen(stime) - 1 ] = 0; \
std::cout << stime << " : " << x << std::endl; } while (0)

#  define DEBUGST(x) do { \
time_t now = time(0); \
tm* localtm = localtime(&now); \
char *stime = asctime(localtm); \
stime[strlen(stime) - 1 ] = 0; \
std::cout << stime << " : " << x; } while (0)

#  define DEBUGCONT(x) do { \
std::cout << x ; } while (0)

#  define DEBUGEND(x) do { \
std::cout << x << std::endl; } while (0)
#else
#  define DEBUGSL(x) do {} while (0)
#  define DEBUGST(x) do {} while (0)
#  define DEBUGCONT(x) do {} while (0)
#  define DEBUGEND(x) do {} while (0)
#endif

#ifndef _WATCHDOGPI_H_
#define _WATCHDOGPI_H_

#include "wx/wx.h"

#include <wx/fileconf.h>

#include "version.h"
#include "wxWTranslateCatalog.h"

#define ABOUT_AUTHOR_URL "http://seandepagnier.users.sourceforge.net"

#include "ocpn_plugin.h"

#ifdef __MSVC__
#include "msvcdefs.h"
#endif

double heading_resolve(double degrees, double offset=0);

//----------------------------------
//    The PlugIn Class Definition
//----------------------------------

#define WATCHDOG_TOOL_POSITION    -1          // Request default positioning of toolbar tool

#include "Alarm.h"

class piDC;
class WatchdogDialog;
class ConfigurationDialog;
class WatchdogPropertiesDialog;

enum {
    ID_ALARM_NEVER = 0,
    ID_ALARM_ALWAYS,
    ID_ALARM_ONCE,
    ID_ALARM_VISIBLE
};

class watchdog_pi : public wxEvtHandler, public opencpn_plugin_118
{
public:

    watchdog_pi(void *ppimgr);

      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      int GetPlugInVersionPatch();	  
      int GetPlugInVersionPost();	  
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

      int GetToolbarToolCount(void);
      void ShowPreferencesDialog( wxWindow* parent );
      void OnToolbarToolCallback(int id);
      void OnContextMenuItemCallback(int id);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      void Render(piDC &dc, PlugIn_ViewPort &vp);

      void OnTimer( wxTimerEvent & );

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

//    Other public methods
      void ShowConfigurationDialog( wxWindow* );
      static wxString StandardPath();

      void UpdateConfiguration();

      PlugIn_Position_Fix_Ex &LastFix() { return m_lastfix; }
      double Declination();

      /**
       * Filtered speed over ground in knots.
       *
       * Exponentially weighted moving average of speed over ground calculated
       * from position differences between timer cycles. Uses a 25%/75% weighting
       * (25% new data, 75% historical) to provide smooth, stable speed readings
       * that reduce GPS noise and sudden speed fluctuations.
       */
      double m_sog,

      /**
       * Filtered course over ground in degrees (0-359.9°)
       *
       * Exponentially weighted moving average of course over ground calculated
       * from bearing between consecutive position fixes. Uses a 25%/75% weighting
       * with proper circular averaging to handle heading discontinuities at 0°/360°.
       */
      m_cog,

      /**
       * Current magnetic heading in degrees from compass/HDM
       *
       * Direct copy of the magnetic heading (Hdm) field from the most recent
       * position fix. Unlike m_cog which is calculated from position changes,
       * this represents the actual compass heading direction the vessel is
       * pointing relative to magnetic north.
       */
      m_hdm;

      wxDateTime m_ValidFixTime;
      wxDateTime m_cursor_time;
      WatchdogDialog   *m_WatchdogDialog;
      
      int       m_iEnableType;
      bool      m_bWatchdogDialogShown;
      wxString m_pypilot_host;
      
protected:
      wxPoint m_cursor_position;

      /**
       * Current position fix data received from OpenCPN's timer-based updates
       *
       * Contains the most recent position fix data received via SetPositionFixEx(),
       * approximately once per second. This represents the "current" vessel state including
       * position, course, speed, and heading data.
       */
      PlugIn_Position_Fix_Ex m_lastfix,

      /**
       * Previous position fix data from the last timer cycle.
       */
      m_lasttimerfix;

private:
      void SetCursorLatLon(double lat, double lon);
      void SetNMEASentence(wxString &sentence);
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
      void SetPluginMessage(wxString &message_id, wxString &message_body);

      ConfigurationDialog *m_ConfigurationDialog;
      WatchdogPropertiesDialog *m_PropertiesDialog;
      int               m_leftclick_tool_id;

      void              RearrangeWindow();

      wxTimer m_Timer;

      double m_declination;
      wxDateTime m_declinationTime;
};

extern watchdog_pi *g_watchdog_pi;

#endif
