#include "cIniFile.h"

char soundsdir[255];
char cPath[255];
char cPath1[255];
char cPath2[255];

bool bIsRage = false;

bool cIni::CreateCfgFile()
{
	GetModuleFileNameA(hMod, cPath, 255);
	for (int i = strlen(cPath); i > 0; i--)
	{
		if (cPath[i] == '\\')
		{
			cPath[i + 1] = 0;
			break;
		}
	}

	HANDLE hFile, hFile2, hFile3;
	CreateDirectoryA(cPath, 0);
	strcat(cPath, "\\Ikaros");
	CreateDirectoryA(cPath, 0);
	strcpy(cPath1, cPath);
	strcpy(cPath2, cPath);
	strcpy(soundsdir, cPath);
	strcat(soundsdir, "\\Sounds");
	CreateDirectoryA(soundsdir, 0);
	strcat(cPath,  "\\Legitv34.cfg");
	strcat(cPath1, "\\Ragev34.cfg");
	strcat(cPath2, "\\Menuv34.cfg");

	hFile = CreateFileA(cPath, GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	CloseHandle(hFile);

	hFile2 = CreateFileA(cPath1, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile2 == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	CloseHandle(hFile2);

	hFile3 = CreateFileA(cPath2, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile3 == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	CloseHandle(hFile3);

	return true;
}

int cIni::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{
	int iResult;
	iResult = GetPrivateProfileIntA(szSection, szKey, iDefaultValue, bIsRage ? cPath1 : cPath);
	return iResult;
}

float cIni::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	float fltResult;
	sprintf(szDefault, "%f",fltDefaultValue);
	GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, 255, bIsRage ? cPath1 : cPath);
	fltResult =  atof(szResult);
	return fltResult;
}

char* cIni::ReadString(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileStringA(szSection, szKey, szDefaultValue, szResult, 255, bIsRage ? cPath1 : cPath);
	return szResult;
}

void cIni::WriteInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileStringA(szSection, szKey, szValue, bIsRage ? cPath1 : cPath);
}

void cIni::WriteFloat(char* szSection, char* szKey, float fltValue)
{
	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	WritePrivateProfileStringA(szSection, szKey, szValue, bIsRage ? cPath1 : cPath);
}

void cIni::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileStringA(szSection, szKey, szValue, bIsRage ? cPath1 : cPath);
}

int cIni::ReadMenuInteger(char* szSection, char* szKey, int iDefaultValue)
{
	int iResult;
	iResult = GetPrivateProfileIntA(szSection, szKey, iDefaultValue, cPath2);
	return iResult;
}

void cIni::WriteMenuInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileStringA(szSection, szKey, szValue, cPath2);
}

void cIni::LoadSettings()
{
	Ikaros.m_pCvars->bAimActive = ReadInteger("Settings", "aim.active", 1);
	Ikaros.m_pCvars->iAim = ReadInteger("Settings", "aim.mode", 1);
	Ikaros.m_pCvars->iAim_Mode = ReadInteger("Settings", "aim.targetselection", 0);
	Ikaros.m_pCvars->iAimSpot = ReadInteger("Settings", "aim.spot", 12);
	Ikaros.m_pCvars->bAutoAim = ReadInteger("Settings", "aim.autoaim", 1);
	Ikaros.m_pCvars->bAutoShoot = ReadInteger("Settings", "aim.autoshoot", 1);
	Ikaros.m_pCvars->iAimKey = ReadInteger("Settings", "aim.key", 1);
	Ikaros.m_pCvars->flAimHeight = ReadFloat("Settings", "aim.height", 3.5f);
	Ikaros.m_pCvars->flFOV = ReadFloat("Settings", "aim.fov", 4);
	Ikaros.m_pCvars->bAdvancedSmooth = ReadInteger("Settings", "aim.smooth.advanced", 0);
	Ikaros.m_pCvars->flSmoothX = ReadFloat("Settings", "aim.smooth.x", 8);
	Ikaros.m_pCvars->flSmoothY = ReadFloat("Settings", "aim.smooth.y", 8);
	Ikaros.m_pCvars->bSilent = ReadInteger("Settings", "aim.silent", 1);
	Ikaros.m_pCvars->bPSilent = ReadInteger("Settings", "aim.psilent", 1);
	Ikaros.m_pCvars->bTeamAim = ReadInteger("Settings", "aim.team", 0);
	Ikaros.m_pCvars->bAutoWall = ReadInteger("Settings", "aim.autowall", 1);
	Ikaros.m_pCvars->bBodyAWP = ReadInteger("Settings", "aim.bodyawp", 1);
	Ikaros.m_pCvars->bDM = ReadInteger("Settings", "aim.dmfix", 1);
	Ikaros.m_pCvars->bHitscan = ReadInteger("Settings", "aim.hitscan", 1);
	Ikaros.m_pCvars->bMultipoint = ReadInteger("Settings", "aim.multipoint", 1);

	Ikaros.m_pCvars->bAntiAim = ReadInteger("Settings", "antiaim.active", 0);
	Ikaros.m_pCvars->bEdgeAntiAim = ReadInteger("Settings", "antiaim.edge", 1);
	Ikaros.m_pCvars->bAimAtTargets = ReadInteger("Settings", "antiaim.aimattargets", 1);
	Ikaros.m_pCvars->iAntiAimTypeX = ReadInteger("Settings", "antiaim.typex", 3);
	Ikaros.m_pCvars->iAntiAimTypeY = ReadInteger("Settings", "antiaim.typey", 4);
	Ikaros.m_pCvars->flAA_X = ReadFloat("Settings", "antiaim.x", 179.95f);
	Ikaros.m_pCvars->flAA_Y = ReadFloat("Settings", "antiaim.y", 180.00f);

	Ikaros.m_pCvars->bESP = ReadInteger("Settings", "esp.active", 1);
	Ikaros.m_pCvars->i2DBox = ReadInteger("Settings", "esp.box", 2);
	Ikaros.m_pCvars->bNameESP = ReadInteger("Settings", "esp.name", 1);
	Ikaros.m_pCvars->iHealthESP = ReadInteger("Settings", "esp.health", 2);
	Ikaros.m_pCvars->bBoneESP = ReadInteger("Settings", "esp.bone", 0);
	Ikaros.m_pCvars->bEnemyOnlyESP = ReadInteger("Settings", "esp.enemyonly", 0);
	Ikaros.m_pCvars->bAimspotESP = ReadInteger("Settings", "esp.aimspot", 0);

	Ikaros.m_pCvars->bAutoPistol = ReadInteger("Settings", "misc.autopistol", 1);
	Ikaros.m_pCvars->iAutoStrafe = ReadInteger("Settings", "misc.autostrafe", 1);
	Ikaros.m_pCvars->bBunnyHop = ReadInteger("Settings", "misc.bhop", 1);
	Ikaros.m_pCvars->iCrosshair = ReadInteger("Settings", "misc.crosshair", 2);
	Ikaros.m_pCvars->bHitSound = ReadInteger("Settings", "misc.hitsound", 0);
	Ikaros.m_pCvars->bSpeed = ReadInteger("Settings", "misc.speedhack", 1);
	Ikaros.m_pCvars->iSpeedVal = ReadFloat("Settings", "misc.speedvalue", 6.0f);
	Ikaros.m_pCvars->iSpeedKey = ReadInteger("Settings", "misc.speedkey", 10);
	Ikaros.m_pCvars->bFullbright = ReadInteger("Settings", "misc.fullbright", 0);
	Ikaros.m_pCvars->roundsay = ReadInteger("Settings", "misc.roundsay", 0);
	Ikaros.m_pCvars->bNameStealer = ReadInteger("Settings", "misc.namestealer", 0);

	Ikaros.m_pCvars->bPlayerList = ReadMenuInteger("Settings", "menu.playerlist", 0);
	Ikaros.m_pCvars->iMenuX = ReadMenuInteger("Settings", "menu.x", 50);
	Ikaros.m_pCvars->iMenuY = ReadMenuInteger("Settings", "menu.y", 50);
	Ikaros.m_pCvars->bWatermark = ReadInteger("Settings", "menu.watermark", 1);

	Ikaros.m_pCvars->bMonitorActive = ReadInteger("Settings", "monitor.active", 0);
	Ikaros.m_pCvars->iMonitorPosX = ReadMenuInteger("Settings", "monitor.x", 20);
	Ikaros.m_pCvars->iMonitorPosY = ReadMenuInteger("Settings", "monitor.y", 300);

	Ikaros.m_pCvars->bRadar2D = ReadInteger("Settings", "radar.active", 0);
	Ikaros.m_pCvars->bRadarBG = ReadInteger("Settings", "radar.window", 0);
	Ikaros.m_pCvars->flRadarPos_x = ReadMenuInteger("Settings", "radar.x", 75);
	Ikaros.m_pCvars->flRadarPos_y = ReadMenuInteger("Settings", "radar.y", 100);
	Ikaros.m_pCvars->bEnemyOnlyRadar = ReadInteger("Settings", "radar.enemyonly", 0);
	Ikaros.m_pCvars->bRadarName = ReadInteger("Settings", "radar.names", 1);

	Ikaros.m_pCvars->bAsusWalls = ReadInteger("Settings", "rem.asus", 1);
	Ikaros.m_pCvars->flAsusAlpha = ReadFloat("Settings", "rem.asusalpha", 0.5);
	Ikaros.m_pCvars->bNoFlash = ReadInteger("Settings", "rem.flash", 1);
	Ikaros.m_pCvars->bNoHands = ReadInteger("Settings", "rem.hands", 0);
	Ikaros.m_pCvars->bNoSmoke = ReadInteger("Settings", "rem.smoke", 1);
	Ikaros.m_pCvars->bNoSky = ReadInteger("Settings", "rem.sky", 0);
	Ikaros.m_pCvars->iRCS = ReadInteger("Settings", "rem.rcs", 0);
	Ikaros.m_pCvars->iNoRecoil = ReadInteger("Settings", "rem.recoil", 1);
	Ikaros.m_pCvars->iNoSpread = ReadInteger("Settings", "rem.spread", 1);
	Ikaros.m_pCvars->bNoVisRecoil = ReadInteger("Settings", "rem.visrecoil", 1);
	Ikaros.m_pCvars->iPNoSpread = ReadInteger("Settings", "rem.pspread", 2);
	Ikaros.m_pCvars->bShowShake = ReadInteger("Settings", "rem.showshake", 0);

	Ikaros.m_pCvars->bTriggerActive = ReadInteger("Settings", "trigger.active", 1);
	Ikaros.m_pCvars->iTrigDelay = ReadInteger("Settings", "trigger.delay", 0);
	Ikaros.m_pCvars->iTriggerbot = ReadInteger("Settings", "trigger.mode", 2);
	Ikaros.m_pCvars->bAutoTrigger = ReadInteger("Settings", "trigger.autoshoot", 0);
	Ikaros.m_pCvars->iTrigBone = ReadInteger("Settings", "trigger.hitbox", 1);
	Ikaros.m_pCvars->bTrigHead = ReadInteger("Settings", "trigger.multihitbox.head", 1);
	Ikaros.m_pCvars->bTrigChest = ReadInteger("Settings", "trigger.multihitbox.chest", 1);
	Ikaros.m_pCvars->bTrigPelvis = ReadInteger("Settings", "trigger.multihitbox.pelvis", 1);
	Ikaros.m_pCvars->bTrigArms = ReadInteger("Settings", "trigger.multihitbox.arms", 1);
	Ikaros.m_pCvars->bTrigLegs = ReadInteger("Settings", "trigger.multihitbox.legs", 1);
	Ikaros.m_pCvars->iTrigKey = ReadInteger("Settings", "trigger.key", 4);
	Ikaros.m_pCvars->bTrigTeam = ReadInteger("Settings", "trigger.team", 0);

	Ikaros.m_pCvars->bChams = ReadInteger("Settings", "vis.chams", 0);
	Ikaros.m_pCvars->bWeaponChams = ReadInteger("Settings", "vis.weaponchams", 0);
	Ikaros.m_pCvars->bGlassChams = ReadInteger("Settings", "vis.glasschams", 0);
	Ikaros.m_pCvars->bXQZWalls = ReadInteger("Settings", "vis.xqz", 0);
}

void cIni::SaveSettings()
{
	WriteInteger("Settings", "aim.active", Ikaros.m_pCvars->bAimActive);
	WriteInteger("Settings", "aim.mode", Ikaros.m_pCvars->iAim);
	WriteInteger("Settings", "aim.targetselection", Ikaros.m_pCvars->iAim_Mode);
	WriteInteger("Settings", "aim.spot", Ikaros.m_pCvars->iAimSpot);
	WriteInteger("Settings", "aim.autoaim", Ikaros.m_pCvars->bAutoAim);
	WriteInteger("Settings", "aim.autoshoot", Ikaros.m_pCvars->bAutoShoot);
	WriteInteger("Settings", "aim.key", Ikaros.m_pCvars->iAimKey);
	WriteFloat("Settings", "aim.height", Ikaros.m_pCvars->flAimHeight);
	WriteFloat("Settings", "aim.fov", Ikaros.m_pCvars->flFOV);
	WriteInteger("Settings", "aim.smooth.advanced", Ikaros.m_pCvars->bAdvancedSmooth);
	WriteFloat("Settings", "aim.smooth.x", Ikaros.m_pCvars->flSmoothX);
	WriteFloat("Settings", "aim.smooth.y", Ikaros.m_pCvars->flSmoothY);
	WriteInteger("Settings", "aim.silent", Ikaros.m_pCvars->bSilent);
	WriteInteger("Settings", "aim.psilent", Ikaros.m_pCvars->bPSilent);
	WriteInteger("Settings", "aim.team", Ikaros.m_pCvars->bTeamAim);
	WriteInteger("Settings", "aim.autowall", Ikaros.m_pCvars->bAutoWall);
	WriteInteger("Settings", "aim.bodyawp", Ikaros.m_pCvars->bBodyAWP);
	WriteInteger("Settings", "aim.dmfix", Ikaros.m_pCvars->bDM);
	WriteInteger("Settings", "aim.hitscan", Ikaros.m_pCvars->bHitscan);
	WriteInteger("Settings", "aim.multipoint", Ikaros.m_pCvars->bMultipoint);

	WriteInteger("Settings", "antiaim.active", Ikaros.m_pCvars->bAntiAim);
	WriteInteger("Settings", "antiaim.edge", Ikaros.m_pCvars->bEdgeAntiAim);
	WriteInteger("Settings", "antiaim.aimattargets", Ikaros.m_pCvars->bAimAtTargets);
	WriteInteger("Settings", "antiaim.typex", Ikaros.m_pCvars->iAntiAimTypeX);
	WriteInteger("Settings", "antiaim.typey", Ikaros.m_pCvars->iAntiAimTypeY);
	WriteFloat("Settings", "antiaim.x", Ikaros.m_pCvars->flAA_X);
	WriteFloat("Settings", "antiaim.y", Ikaros.m_pCvars->flAA_Y);

	WriteInteger("Settings", "esp.active", Ikaros.m_pCvars->bESP);
	WriteInteger("Settings", "esp.box", Ikaros.m_pCvars->i2DBox);
	WriteInteger("Settings", "esp.name", Ikaros.m_pCvars->bNameESP);
	WriteInteger("Settings", "esp.health", Ikaros.m_pCvars->iHealthESP);
	WriteInteger("Settings", "esp.bone", Ikaros.m_pCvars->bBoneESP);
	WriteInteger("Settings", "esp.enemyonly", Ikaros.m_pCvars->bEnemyOnlyESP);
	WriteInteger("Settings", "esp.aimspot", Ikaros.m_pCvars->bAimspotESP);

	WriteInteger("Settings", "misc.autopistol", Ikaros.m_pCvars->bAutoPistol);
	WriteInteger("Settings", "misc.autostrafe", Ikaros.m_pCvars->iAutoStrafe);
	WriteInteger("Settings", "misc.bhop", Ikaros.m_pCvars->bBunnyHop);
	WriteInteger("Settings", "misc.crosshair", Ikaros.m_pCvars->iCrosshair);
	WriteInteger("Settings", "misc.hitsound", Ikaros.m_pCvars->bHitSound);
	WriteInteger("Settings", "misc.speedhack", Ikaros.m_pCvars->bSpeed);
	WriteFloat("Settings", "misc.speedvalue", Ikaros.m_pCvars->iSpeedVal);
	WriteInteger("Settings", "misc.speedkey", Ikaros.m_pCvars->iSpeedKey);
	WriteInteger("Settings", "misc.fullbright", Ikaros.m_pCvars->bFullbright);
	WriteInteger("Settings", "misc.roundsay", Ikaros.m_pCvars->roundsay);
	WriteInteger("Settings", "misc.namestealer", Ikaros.m_pCvars->bNameStealer);

	WriteMenuInteger("Settings", "menu.playerlist", Ikaros.m_pCvars->bPlayerList);
	WriteMenuInteger("Settings", "menu.x", Ikaros.m_pCvars->iMenuX);
	WriteMenuInteger("Settings", "menu.y", Ikaros.m_pCvars->iMenuY);
	WriteInteger("Settings", "menu.watermark", Ikaros.m_pCvars->bWatermark);

	WriteInteger("Settings", "monitor.active", Ikaros.m_pCvars->bMonitorActive);
	WriteMenuInteger("Settings", "monitor.x", Ikaros.m_pCvars->iMonitorPosX);
	WriteMenuInteger("Settings", "monitor.y", Ikaros.m_pCvars->iMonitorPosY);

	WriteInteger("Settings", "radar.active", Ikaros.m_pCvars->bRadar2D);
	WriteInteger("Settings", "radar.window", Ikaros.m_pCvars->bRadarBG);
	WriteMenuInteger("Settings", "radar.x", Ikaros.m_pCvars->flRadarPos_x);
	WriteMenuInteger("Settings", "radar.y", Ikaros.m_pCvars->flRadarPos_y);
	WriteInteger("Settings", "radar.enemyonly", Ikaros.m_pCvars->bEnemyOnlyRadar);
	WriteInteger("Settings", "radar.names", Ikaros.m_pCvars->bRadarName);

	WriteInteger("Settings", "rem.asus", Ikaros.m_pCvars->bAsusWalls);
	WriteFloat("Settings", "rem.asusalpha", Ikaros.m_pCvars->flAsusAlpha);
	WriteInteger("Settings", "rem.flash", Ikaros.m_pCvars->bNoFlash);
	WriteInteger("Settings", "rem.hands", Ikaros.m_pCvars->bNoHands);
	WriteInteger("Settings", "rem.smoke", Ikaros.m_pCvars->bNoSmoke);
	WriteInteger("Settings", "rem.sky", Ikaros.m_pCvars->bNoSky);
	WriteInteger("Settings", "rem.rcs", Ikaros.m_pCvars->iRCS);
	WriteInteger("Settings", "rem.recoil", Ikaros.m_pCvars->iNoRecoil);
	WriteInteger("Settings", "rem.spread", Ikaros.m_pCvars->iNoSpread);
	WriteInteger("Settings", "rem.visrecoil", Ikaros.m_pCvars->bNoVisRecoil);
	WriteInteger("Settings", "rem.pspread", Ikaros.m_pCvars->iPNoSpread);
	WriteInteger("Settings", "rem.showshake", Ikaros.m_pCvars->bShowShake);

	WriteInteger("Settings", "trigger.active", Ikaros.m_pCvars->bTriggerActive);
	WriteInteger("Settings", "trigger.delay", Ikaros.m_pCvars->iTrigDelay);
	WriteInteger("Settings", "trigger.mode", Ikaros.m_pCvars->iTriggerbot);
	WriteInteger("Settings", "trigger.autoshoot", Ikaros.m_pCvars->bAutoTrigger);
	WriteInteger("Settings", "trigger.hitbox", Ikaros.m_pCvars->iTrigBone);
	WriteInteger("Settings", "trigger.multihitbox.head", Ikaros.m_pCvars->bTrigHead);
	WriteInteger("Settings", "trigger.multihitbox.chest", Ikaros.m_pCvars->bTrigChest);
	WriteInteger("Settings", "trigger.multihitbox.pelvis", Ikaros.m_pCvars->bTrigPelvis);
	WriteInteger("Settings", "trigger.multihitbox.arms", Ikaros.m_pCvars->bTrigArms);
	WriteInteger("Settings", "trigger.multihitbox.legs", Ikaros.m_pCvars->bTrigLegs);
	WriteInteger("Settings", "trigger.key", Ikaros.m_pCvars->iTrigKey);
	WriteInteger("Settings", "trigger.team", Ikaros.m_pCvars->bTrigTeam);

	WriteInteger("Settings", "vis.chams", Ikaros.m_pCvars->bChams);
	WriteInteger("Settings", "vis.weaponchams", Ikaros.m_pCvars->bWeaponChams);
	WriteInteger("Settings", "vis.glasschams", Ikaros.m_pCvars->bGlassChams);
	WriteInteger("Settings", "vis.xqz", Ikaros.m_pCvars->bXQZWalls);
}