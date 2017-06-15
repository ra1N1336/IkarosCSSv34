#ifndef _CVARS_H_
#define _CVARS_H_
#include "Include.h"

class cVars
{
public: 
	bool bAutoAim, bTeamAim, bAutoShoot, bSilent, bPSilent, bAutoWall, bAimActive, bShowShake, bBodyAWP, bDM, bAdvancedSmooth, bHitscan, bMultipoint;
	bool bTrigHead, bTrigChest, bTrigPelvis, bTrigArms, bTrigLegs, bTrigTeam;
	float flFOV, flAimHeight, flSmoothX, flSmoothY, iAimSpot;
	int iAim, iAim_Mode;
	
	int iAimKey, iSpeedKey, iTrigKey;
		
	bool bAntiAim, bEdgeAntiAim, bAimAtTargets;
	int iAntiAimTypeX, iAntiAimTypeY;
	float flAA_X, flAA_Y;

	bool bESP, bNameESP, bRadar2D, bRadarName, bEnemyOnlyESP, bEnemyOnlyRadar, bBoneESP, bAimspotESP;
	int iHealthESP, i2DBox;

	bool bNoSmoke, bNoFlash, bFullbright, bBunnyHop, bNoHands, bAutoPistol, bSpeed, bPanicKey, bMenuActive, bShowGUI, bTriggerActive;
	bool bChams, bXQZWalls, bWeaponChams, bRadarBG, bMonitorActive, bWatermark, roundsay, bGlassChams, bPlayerList;
	bool bAutoTrigger, bNameStealer, bNoSky, bNoVisRecoil, bAsusWalls, bAiming, bSigFail, bHitSound, bFlashSpam;
	int iSavedRadarX, iSavedRadarY, iCrosshair, iMenuX, iMenuY, iMonitorPosX, iMonitorPosY, iMonitorSavePosX, iMonitorSavePosY;
	int iTriggerbot, iTrigBone, iNoSpread, iPNoSpread, iNoRecoil, iRCS, iMouseX, iMouseY, iAutoStrafe;
	float flSavedPos_x, flSavedPos_y, flRadarPos_x, flRadarPos_y, flStartTime, flAsusAlpha, iSpeedVal, iTrigDelay;
};

#endif