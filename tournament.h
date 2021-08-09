/*
 * Copyright (C) 2015 AnAkkk <anakin.cs@gmail.com>
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#pragma once

#include "SDK.h"
#include "utils.h"

#include "ModuleScanner.h"

class CTournament: public IGameEventListener2
{
public:
	bool Init(const CModuleScanner& EngineModule, const CModuleScanner& ServerModule);
	void OnServerActivate();
	void OnUnload();

	bool TournamentStarted() { return m_bTournamentStarted; }
	void DownloadConfig(const char *szURL, SOCKET sock, bool bOverwrite = true);

	void FireGameEvent(IGameEvent *pEvent );

	static void Tournament_Callback( IConVar *var, const char *pOldValue, float flOldValue );
	static void Tournament_Config_Callback( IConVar *var, const char *pOldValue, float flOldValue );

	static void __fastcall Tournament_Restart_Callback(ConCommand *pCmd, EDX const CCommand &args);
	static void __fastcall Pure_Callback(ConCommand *pCmd, EDX const CCommand &args);
	static void __fastcall Status_Callback(ConCommand *pCmd, EDX const CCommand &args);
	static void __fastcall Pause_Callback(ConCommand *pCmd, EDX const CCommand &args);
	static void __fastcall StartCompetitiveMatch(void *pGameRules EDX2);

private:
	bool m_bTournamentStarted    = false;

	int m_iConfigDownloadFailed  = 0;


	time_t m_tNextUnpauseAllowed = 0;
	std::chrono::high_resolution_clock::time_point begin;

	CFunctionRoute m_DispatchTournamentRestartRoute;
	CFunctionRoute m_DispatchPureRoute;
	CFunctionRoute m_DispatchStatusRoute;
	CFunctionRoute m_DispatchPauseRoute;
	CFunctionRoute m_StartCompetitiveMatchRoute;
};

extern CTournament g_Tournament;

extern ConVar tftrue_unpause_delay;
extern ConVar tftrue_log_verbose_pauses;