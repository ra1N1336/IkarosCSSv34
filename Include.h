#ifndef __INCLUDE_H__
#define __INCLUDE_H__

//#define DEBUG

#include "SDK.h"
#include "detours.h"

#include "n0xius.h"
#include "vtable.h"
#include "Needed.h"
#include "CAimbot.h"
#include "cNetVars.h"
#include "cNoSpread.h"
#include "draw.h"
#include "cVars.h"
#include "cIniFile.h"
#include "cMenu.h"
#include "esp.h"
#include "CAimbot.h"
#include "cBhop.h"
#include "cAntiAim.h"
#include "cRadar.h"
#include "CGameEventManager2.h"

extern void StartHooking();
extern HANDLE hClient;
extern HANDLE hEngine;
extern bool bIsRage;
extern bool bSendPacket;
extern IMaterial* mat;
extern IMaterial* mat2;
extern IMaterial* mat3;
extern QAngle qRealView;
extern HMODULE hMod;
extern DWORD dwCL_MOVE;
extern void* baseptr;

#define	CS_MASK_SHOOT (MASK_SOLID|CONTENTS_DEBRIS)

#define CLIENT(offset) ((DWORD)hClient + offset)
#define Offset_BaseEntity(name) Ikaros.m_pNetVar->GetOffset("DT_BaseEntity",name)
#define Offset_BasePlayer(name) Ikaros.m_pNetVar->GetOffset("DT_BasePlayer",name)
#define Offset_CSPlayer(name) Ikaros.m_pNetVar->GetOffset("DT_CSPlayer",name)
#define Offset_BaseCombatCharacter(name) Ikaros.m_pNetVar->GetOffset("DT_BaseCombatCharacter",name)
#define Offset_BaseAnimating(name) Ikaros.m_pNetVar->GetOffset("DT_BaseAnimating",name)
#define Offset_BaseCombatWeapon(name) Ikaros.m_pNetVar->GetOffset("DT_BaseCombatWeapon",name)

#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define RGBA(COLORCODE) RED( COLORCODE ), GREEN( COLORCODE ), BLUE( COLORCODE ), ALPHA( COLORCODE )

#define CHEAT_ORANGE COLORCODE( 255, 100, 000, 255 )
#define CHEAT_YELLOW COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED COLORCODE( 255, 50, 0, 255 )
#define CHEAT_GREEN COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE COLORCODE( 0, 0, 255, 255 )
#define CHEAT_WIREBLUE COLORCODE( 0, 255, 255, 255 )
#define CHEAT_BLACK COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE COLORCODE( 255, 255, 255, 255 )
#define CHEAT_NOCOLOR COLORCODE( 0, 0, 0, 0 )

#define SaveButtonColor		COLORCODE( 0, 180, 220, 255 )
#define TabColor			COLORCODE( 78, 186, 242, 255 )
#define BackTabColor		COLORCODE( 38, 38, 38, 255 )
#define Grey0				COLORCODE( 40, 40, 40, 255 )
#define Grey1				COLORCODE( 60, 60, 60, 255 )
#define Grey2				COLORCODE( 75, 75, 75, 255 )
#define Grey3				COLORCODE( 90, 90, 90, 255 )
#define Grey4				COLORCODE( 120, 120, 120, 255 )
#define Red0				COLORCODE( 220, 0, 0, 255 )
#define Red1				COLORCODE( 255, 0, 0, 255 )
#define FontColor			COLORCODE( 255, 255, 255, 255 )
#define ButtonColor			COLORCODE( 0, 180, 220, 255 )
#define ClickedButtonColor	COLORCODE( 0, 220, 220, 255 )
#define GroupBoxColor		COLORCODE( 78, 186, 242, 255 )
#define MenuColor			COLORCODE( 78, 186, 242, 255 )
#define BackgroundColor		COLORCODE( 50, 50, 50, 220 )

enum modtype_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

class CTraceFilterNoPlayers : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

typedef void(*CL_Move_t)(float accumulated_extra_samples, bool bFinalTick);

typedef void(__stdcall*CreateMove_t)(int, float, bool);
extern void __stdcall new_CreateMove(int sequence_number, float tick, bool active);

typedef void(__stdcall* RunCommand_t)(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper);

typedef BOOL(WINAPI* SetCursorPos_t)(int, int);
typedef BOOL(WINAPI* PeekMessageA_t)(LPMSG, HWND, UINT, UINT, UINT);

typedef void(__stdcall*PaintTraverse_t)(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce);
extern void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce);

typedef IMaterial * (__stdcall *FindMaterial_t)(const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
//extern IMaterial *__stdcall new_FindMaterial(const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);

typedef int(__stdcall *Init_t)(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals);

typedef CUserCmd* (__stdcall* GetUserCmd_t)(int sequence_number);
extern CUserCmd* __stdcall new_GetUserCmd(int sequence_number);

typedef void(__stdcall* FrameStageNotify_t)(ClientFrameStage_t curStage);
extern void __stdcall new_FrameStageNotify(ClientFrameStage_t curStage);

typedef void(__stdcall*HudUpdate_t)(bool);
extern void __stdcall new_HudUpdate(bool bActive);

typedef int(__stdcall* DrawModelEx_t)(ModelRenderInfo_t &pInfo);
extern int __stdcall new_DrawModelEx(ModelRenderInfo_t &pInfo);

#endif