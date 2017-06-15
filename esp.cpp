#include "esp.h"

bool bOnce = true;
ScreenSize_t sScreenSize;
ScreenSize_t sScreenSize2;

void Esp::DrawHealthbar(int Health, Vector vScreen, int x, int y)
{
	int r = 255 - (Health*2.55);
	int g = Health*2.55;
	Ikaros.m_pDraw->FillRGBA(vScreen.x - x - 1, vScreen.y - y - 1, 5, 41, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
	Ikaros.m_pDraw->FillRGBA(vScreen.x - x, vScreen.y - y, 3, 39, r, g, 0, 255);
	Ikaros.m_pDraw->FillRGBA(vScreen.x - x, vScreen.y - y, 3, 39 - (Health / 2.5), RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
}

void DrawCornerBox(int x, int y, int w, int h, int borderPx, int r, int g, int b, int a)
{
	//Blackborder
	Ikaros.m_pDraw->FillRGBA((x - (w / 2)) - 1, (y - h + borderPx) - 1, (w / 3) + 2, borderPx + 2, 0, 0, 0, 255); //top
	Ikaros.m_pDraw->FillRGBA((x - (w / 2) + w - w / 3) - 1, (y - h + borderPx) - 1, w / 3, borderPx + 2, 0, 0, 0, 255); //top
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) - 1, (y - h + borderPx), borderPx + 2, (w / 3) + 1, 0, 0, 0, 255); //left 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) - 1, ((y - h + borderPx) + h - w / 3) - 1, borderPx + 2, (w / 3) + 2, 0, 0, 0, 255); //left 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2), y - 1, (w / 3) + 1, borderPx + 2, 0, 0, 0, 255); //bottom 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) + w - (w / 3 + 1), y - 1, (w / 3) + 2, borderPx + 2, 0, 0, 0, 255); //bottom 
	Ikaros.m_pDraw->FillRGBA((x + w - borderPx) - (w / 2) - 1, (y - h + borderPx) - 1, borderPx + 2, w / 3 + 2, 0, 0, 0, 255); //right 
	Ikaros.m_pDraw->FillRGBA((x + w - borderPx) - (w / 2) - 1, ((y - h + borderPx) + h - w / 3) - 1, borderPx + 2, (w / 3) + 2, 0, 0, 0, 255); //right 
	//Color
	Ikaros.m_pDraw->FillRGBA(x - (w / 2), (y - h + borderPx), w / 3, borderPx, r, g, b, a); //top
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) + w - w / 3, (y - h + borderPx), w / 3, borderPx, r, g, b, a); //top
	Ikaros.m_pDraw->FillRGBA(x - (w / 2), (y - h + borderPx), borderPx, w / 3, r, g, b, a); //left 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3, r, g, b, a); //left 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2), y, w / 3, borderPx, r, g, b, a); //bottom 
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) + w - w / 3, y, w / 3, borderPx, r, g, b, a); //bottom 
	Ikaros.m_pDraw->FillRGBA((x + w - borderPx) - (w / 2), (y - h + borderPx), borderPx, w / 3, r, g, b, a); //right 
	Ikaros.m_pDraw->FillRGBA((x + w - borderPx) - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3, r, g, b, a); //right 
}

void Esp::CrossHair(void)
{
	if (Ikaros.m_pCvars->iCrosshair < 1)
		return;

	if (Ikaros.m_pCvars->iCrosshair == 1)
	{
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 2, (sScreenSize.m_iHeight / 2) - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 1, (sScreenSize.m_iHeight / 2) - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_BLACK));
	}
	else if (Ikaros.m_pCvars->iCrosshair == 2)
	{
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 5, (sScreenSize.m_iHeight / 2) - 1, 11, 3, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 1, (sScreenSize.m_iHeight / 2) - 5, 3, 11, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 4, (sScreenSize.m_iHeight / 2), 9, 1, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2), (sScreenSize.m_iHeight / 2) - 4, 1, 9, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE));
	}
	else if (Ikaros.m_pCvars->iCrosshair == 3)
	{
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 10, (sScreenSize.m_iHeight / 2), 20, 1, RED(CHEAT_WIREBLUE), GREEN(CHEAT_WIREBLUE), BLUE(CHEAT_WIREBLUE), ALPHA(CHEAT_WIREBLUE));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2), (sScreenSize.m_iHeight / 2) - 10, 1, 20, RED(CHEAT_WIREBLUE), GREEN(CHEAT_WIREBLUE), BLUE(CHEAT_WIREBLUE), ALPHA(CHEAT_WIREBLUE));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 5, (sScreenSize.m_iHeight / 2), 11, 1, RED(CHEAT_RED), GREEN(CHEAT_RED), BLUE(CHEAT_RED), ALPHA(CHEAT_RED));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2), (sScreenSize.m_iHeight / 2) - 5, 1, 11, RED(CHEAT_RED), GREEN(CHEAT_RED), BLUE(CHEAT_RED), ALPHA(CHEAT_RED));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 10, (sScreenSize.m_iHeight / 2) - 10, 20, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 10, (sScreenSize.m_iHeight / 2) + 10, 21, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) - 10, (sScreenSize.m_iHeight / 2) - 10, 1, 20, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
		Ikaros.m_pDraw->FillRGBA((sScreenSize.m_iWidth / 2) + 10, (sScreenSize.m_iHeight / 2) - 10, 1, 20, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
	}
}

void Esp::MaterialStuff(void)
{
	IMaterial* pFlash = Ikaros.m_pMaterialSystem->FindMaterial("effects\\flashbang", "ClientEffect textures");
	IMaterial *pfog = Ikaros.m_pMaterialSystem->FindMaterial("particle\\screenspace_fog", NULL);
	IMaterial *pSmokeEffect = Ikaros.m_pMaterialSystem->FindMaterial("particle\\particle_smokegrenade1", NULL);
	IMaterial* pFlash2 = Ikaros.m_pMaterialSystem->FindMaterial("effects\\flashbang_white", "ClientEffect textures");
	IMaterial* vhands = Ikaros.m_pMaterialSystem->FindMaterial("models\\weapons\\v_models\\hands\\v_hands", "Model textures");
	IMaterial* ct1 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\ct_gign\\ct_gign", "Model textures");
	IMaterial* ct2 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\ct_gsg9\\ct_gsg9", "Model textures");
	IMaterial* ct3 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\ct_sas\\ct_sas", "Model textures");
	IMaterial* ct4 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\ct_urban\\ct_urban", "Model textures");
	IMaterial* t1 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\t_arctic\\t_arctic", "Model textures");
	IMaterial* t2 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\t_guerilla\\t_guerilla", "Model textures");
	IMaterial* t3 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\t_leet\\t_leet", "Model textures");
	IMaterial* t4 = Ikaros.m_pMaterialSystem->FindMaterial("models\\player\\t_phoenix\\t_phoenix", "Model textures");

	if (Ikaros.m_pCvars->bNoSmoke)
	{
		pSmokeEffect->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (true));//nosmoke
		pfog->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (true));//nofog
	}
	else
	{
		pSmokeEffect->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (false));//nosmoke
		pfog->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (false));//nofog
	}

	if (Ikaros.m_pCvars->bNoFlash)
	{
		pFlash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (true));//noflash
		pFlash2->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (true));//noflash
	}
	else
	{
		pFlash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (false));//noflash
		pFlash2->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (false));//noflash
	}

	if (Ikaros.m_pCvars->bNoHands)
	{
		vhands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (true));
	}
	else
	{
		vhands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (false));
	}

	if (Ikaros.m_pCvars->bXQZWalls)
	{
		ct1->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		ct2->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		ct3->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		ct4->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		t1->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		t2->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		t3->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		t4->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (true));
		ct1->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		ct2->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		ct3->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		ct4->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		t1->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		t2->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		t3->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
		t4->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (true));
	}
	else
	{
		ct1->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		ct2->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		ct3->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		ct4->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		t1->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		t2->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		t3->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		t4->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, (false));
		ct1->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		ct2->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		ct3->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		ct4->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		t1->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		t2->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		t3->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
		t4->SetMaterialVarFlag(MATERIAL_VAR_FLAT, (false));
	}
}

static char box[6][4] =
{
	{ 0, 4, 6, 2 }, // +X
	{ 0, 1, 5, 4 }, // +Y
	{ 0, 2, 3, 1 }, // +Z
	{ 7, 5, 1, 3 }, // -X
	{ 7, 3, 2, 6 }, // -Y
	{ 7, 6, 4, 5 }, // -Z
};

bool __fastcall ScreenProjectPoint(Vector &vIn, int*pOut)
{
	Vector vScreen;

	bool bOK = Ikaros.m_pNeeded->WorldToScreen(vIn, vScreen);
	if (bOK)
	{
		pOut[0] = vScreen.x;
		pOut[1] = vScreen.y;
	}

	return bOK;
}

void RenderBox(Vector const& vMin, Vector const& vMax, matrix3x4_t const& xToWorld)
{
	INT iPosX[4],
		iPosY[4], iScreen[2];

	Vector vPos[8],
		vTmp;

	for (INT k = 0; k < 8; k++)
	{
		vTmp[0] = (k & 1) ? vMin[0] : vMax[0];
		vTmp[1] = (k & 2) ? vMin[1] : vMax[1];
		vTmp[2] = (k & 4) ? vMin[2] : vMax[2];
		VectorTransform(vTmp, xToWorld, vPos[k]);
	}

	for (INT k = 0; k < 6; k++)
	{
		bool bDraw = true;

		for (INT l = 0; l < 4 && bDraw; ++l)
		{
			if (ScreenProjectPoint(vPos[box[k][l]], iScreen))
			{
				iPosX[l] = iScreen[0];
				iPosY[l] = iScreen[1];
			}
			else
				bDraw = false;
		}

		if (bDraw)
		{
			Ikaros.m_pMatSurface->DrawPolyLine(iPosX, iPosY, 4);
		}
	}
}

void Esp::NameChange(void)
{
	if (!Ikaros.m_pMyPlayer->BaseEnt())
		return;

	static int iChange = 0;
	player_info_t pInfo;

	int index = Ikaros.m_pGlobals->maxClients;
	//----------------------------------//
	for (; index >= 1; index--)
	{
		if (index == Ikaros.m_pEngine->GetLocalPlayer())
			continue;

		IClientEntity* ClientEntity = Ikaros.m_pEntList->GetClientEntity(index);

		if (ClientEntity == NULL
			|| ClientEntity->IsDormant())
			continue;

		C_BaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

		if (pBaseEntity == NULL
			|| pBaseEntity->IsDormant())
			continue;

		if (Ikaros.m_pEngine->GetPlayerInfo(index, &pInfo))
		{
			iChange++;
			if (iChange >= 500)
			{
				char szPlayerNames[64];
				sprintf(szPlayerNames, "setinfo name \"%s \"", pInfo.name);
				Ikaros.m_pEngine->ClientCmd(szPlayerNames);
				iChange = 0;
			}
		}
	}
}

void Esp::DrawHeader(INT x, INT y, INT w, INT r, INT g, INT b, INT HealthBarWidth)
{
	INT i = 0;
	INT xCoord = x;
	INT yCoord = y;

	// Male Male :)
	for (i = 0; i < 5; i++)
	{
		Ikaros.m_pDraw->FillRGBA(x - i, y + i, w, 1, 0, 0, 0, 255);
		Ikaros.m_pDraw->FillRGBA(x - i, y + i, HealthBarWidth + 2, 1, r, g, b, 255);
		Ikaros.m_pDraw->FillRGBA(x - 3, y + 3, HealthBarWidth + 2, 1, (INT)(r / 1.5f), (INT)(g / 1.5f), (INT)(b / 1.5f), 255);
		Ikaros.m_pDraw->FillRGBA(x - 4, y + 4, HealthBarWidth + 2, 1, (INT)(r / 1.5f), (INT)(g / 1.5f), (INT)(b / 1.5f), 255);
	}

	// Oben
	Ikaros.m_pDraw->FillRGBA(x, y, w, 1, 255, 255, 255, 255);

	// Unten
	Ikaros.m_pDraw->FillRGBA((x + 1) - 5, y + 5, w, 1, 255, 255, 255, 255);

	for (i = 0; i < 5; i++)
	{
		// Schräg links
		Ikaros.m_pDraw->FillRGBA(x, y, 1, 1, 255, 255, 255, 255);
		x--;
		y++;
	}

	x = xCoord;
	y = yCoord;

	for (i = 0; i < 5; i++)
	{
		// Schräg rechts
		if (i != 0)
			Ikaros.m_pDraw->FillRGBA(x + w, y, 1, 1, 255, 255, 255, 255);

		x--;
		y++;
	}
}

void Esp::DrawEsp(void)
{
	if (!Ikaros.m_pMyPlayer->BaseEnt())
		return;

	player_info_t pInfo;
	Vector vScreen, vScreen2, vScreen3, vWorldPosition, vWorldPosition2, vPlayerHead; 
	int iCurWep = 0, index = Ikaros.m_pGlobals->maxClients;
	//----------------------------------//
	for (; index >= 1; index--)
	{
		if (index == Ikaros.m_pEngine->GetLocalPlayer())
			continue;

		IClientEntity* ClientEntity = Ikaros.m_pEntList->GetClientEntity(index);

		if (ClientEntity == NULL
			|| ClientEntity->IsDormant())
			continue;

		C_BaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

		if (pBaseEntity == NULL
			|| pBaseEntity->IsDormant())
			continue;

		int iTeamIndex = Ikaros.m_pEntity->GetTeamID(pBaseEntity);

		DWORD dwGetTeamColor = CHEAT_WHITE;

		if (Ikaros.m_pEngine->GetPlayerInfo(index, &pInfo))
		{
			if (Ikaros.m_pAimbot->GetVisible(Ikaros.m_pMyPlayer->BaseEnt()->EyePosition(), pBaseEntity->EyePosition(), pBaseEntity))
			{
				//if (iTeamIndex != MyTeamIndex)//Enemy
				if (iTeamIndex == 2)
					dwGetTeamColor = CHEAT_RED;

				//if (iTeamIndex == MyTeamIndex)//Team
				if (iTeamIndex == 3)
					dwGetTeamColor = CHEAT_BLUE;
			}
			else
			{
				//if (iTeamIndex != MyTeamIndex)//Enemy
				if (iTeamIndex == 2)
					dwGetTeamColor = CHEAT_YELLOW;

				//if (iTeamIndex == MyTeamIndex)//Team
				if (iTeamIndex == 3)
					dwGetTeamColor = CHEAT_GREEN;
			}

			if (!strcmp("STEAM_0:0:1635822221", pInfo.guid))
				dwGetTeamColor = CHEAT_WHITE;

			if (Ikaros.m_pPlayerlist[index].bFriend)
				dwGetTeamColor = CHEAT_WHITE;

			Vector targetDest[9];
			C_BaseCombatWeapon* m_pWeapon = Ikaros.m_pNeeded->GetBaseCombatActiveWeapon(Ikaros.m_pMyPlayer->BaseEnt());

			if (m_pWeapon)
				iCurWep = Ikaros.m_pEntity->GetWeaponID(m_pWeapon);

			Ikaros.m_pNeeded->GetWorldSpaceCenter(pBaseEntity, vWorldPosition);
			Ikaros.m_pNeeded->GetWorldSpaceCenter(pBaseEntity, vWorldPosition2);

			if (Ikaros.m_pNeeded->WorldToScreenRadar(vWorldPosition2, vScreen2))
			{
				if (Ikaros.m_pCvars->bRadar2D)
				{
					if (Ikaros.m_pCvars->bEnemyOnlyRadar)
					{
						if (Ikaros.m_pEntity->GetTeamID(pBaseEntity) == Ikaros.m_pEntity->GetTeamID(Ikaros.m_pMyPlayer->BaseEnt()))
							continue;
					}

					if (Ikaros.m_pEntity->GetLifeState(pBaseEntity))
					{
						Ikaros.m_pRadar->DrawRadarPoint(pBaseEntity->GetAbsOrigin(), Ikaros.m_pMyPlayer->BaseEnt()->GetAbsOrigin(), Ikaros.m_pMyPlayer->BaseEnt()->GetAbsAngles(), pInfo.name, ALPHA(dwGetTeamColor), RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor));
					}
				}
			}

			if (Ikaros.m_pCvars->bESP)
			{
				if (Ikaros.m_pEntity->GetLifeState(pBaseEntity))
				{
					if (Ikaros.m_pCvars->bEnemyOnlyESP)
					{
						if (pBaseEntity->GetTeamNumber() == Ikaros.m_pMyPlayer->BaseEnt()->GetTeamNumber())
							continue;
					}

					if (Ikaros.m_pCvars->bAimspotESP)
					{
						if (Ikaros.m_pAimbot->GetHitboxPosition((Ikaros.m_pCvars->bBodyAWP && Ikaros.m_pCvars->iAim && iCurWep == WEAPON_AWP) ? 9 : Ikaros.m_pCvars->iAimSpot, targetDest, pBaseEntity))
						{
							if (Ikaros.m_pNeeded->WorldToScreen(targetDest[0], vScreen3))
							{
								Ikaros.m_pDraw->FillRGBA(vScreen3.x - 2, vScreen3.y - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
								Ikaros.m_pDraw->FillRGBA(vScreen3.x - 1, vScreen3.y - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE));
							}
						}
					}

					if (Ikaros.m_pNeeded->WorldToScreen(vWorldPosition, vScreen))
					{
						int Health = Ikaros.m_pEntity->GetHealth(pBaseEntity);
						int iHealth = clamp(Health, 0, 100);
						int iFlags = Ikaros.m_pEntity->GetFlags(pBaseEntity);

						Vector vPlayerFoot = pBaseEntity->GetAbsOrigin();
						Vector vPlayerHead;
						if (iFlags & FL_DUCKING)
							vPlayerHead = vPlayerFoot + Vector(0, 0, 52);
						else
							vPlayerHead = vPlayerFoot + Vector(0, 0, 72);

						Vector vPlayerFootScreen, vPlayerHeadScreen;
						Ikaros.m_pNeeded->WorldToScreen(vPlayerFoot, vPlayerFootScreen);
						Ikaros.m_pNeeded->WorldToScreen(vPlayerHead, vPlayerHeadScreen);

						float width = (vPlayerFootScreen.y - vPlayerHeadScreen.y) / 4;
						float height = (vPlayerFootScreen.x - vPlayerHeadScreen.x) / 4;

						if (Ikaros.m_pNeeded->WorldToScreen(pBaseEntity->EyePosition(), vPlayerHead))
						{
							if (Ikaros.m_pCvars->bBoneESP)
							{
								matrix3x4_t pmatrix[MAXSTUDIOBONES];
								studiohdr_t* pStudioHdr = (studiohdr_t*)Ikaros.m_pModelinfo->GetStudiomodel((model_t*)pBaseEntity->GetModel());
								if (pStudioHdr)
								{
									if (!pBaseEntity->SetupBones(pmatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, Ikaros.m_pGlobals->curtime))
										return;

									int m_nHitboxSet = 0;
									mstudiohitboxset_t* HitboxSet = (mstudiohitboxset_t*)pStudioHdr->pHitboxSet(m_nHitboxSet);

									if (HitboxSet)
									{
										for (int iHitBoxCount = 0; iHitBoxCount < pStudioHdr->iHitboxCount(m_nHitboxSet); iHitBoxCount++)
										{
											mstudiobbox_t* m_pHitBox = (mstudiobbox_t*)pStudioHdr->pHitbox(iHitBoxCount, m_nHitboxSet);

											if (m_pHitBox)
											{
												Vector vecPosition;
												QAngle angles;
												MatrixAngles(pmatrix[m_pHitBox->bone], angles, vecPosition);
												Ikaros.m_pMatSurface->DrawSetColor(RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), 90);
												RenderBox(m_pHitBox->bbmin, m_pHitBox->bbmax, pmatrix[m_pHitBox->bone]);
											}
										}
									}
								}
							}

							if (Ikaros.m_pCvars->i2DBox == 1)
							{
								Ikaros.m_pDraw->Rectangle(vScreen.x - 21, vScreen.y - 21, 41, 41, 3, 0, 0, 0, 255);
								Ikaros.m_pDraw->Rectangle(vScreen.x - 20, vScreen.y - 20, 39, 39, 1, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), ALPHA(dwGetTeamColor));
								if (Ikaros.m_pCvars->bNameESP)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 28, vScreen.y - 9, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "%s", pInfo.name);
								}
								if (Ikaros.m_pCvars->iHealthESP == 1)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 28, vScreen.y + 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 2)
								{
									DrawHealthbar(iHealth, vScreen, 28, 20);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 3)
								{
									DrawHeader(vScreen.x - 19, vScreen.y + 24, 39 + 2, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), (iHealth / 2.5) - 2);
								}
							}
							else if (Ikaros.m_pCvars->i2DBox == 2)
							{
								int h = vPlayerFootScreen.y - vPlayerHeadScreen.y;
								Ikaros.m_pDraw->Rectangle(vPlayerHeadScreen.x - width - 1, vPlayerHeadScreen.y - 1, width * 2 + 1, h + 1, 3, 0, 0, 0, 255);
								Ikaros.m_pDraw->Rectangle(vPlayerHeadScreen.x - width, vPlayerHeadScreen.y, width * 2 - 1, h - 1, 1, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), ALPHA(dwGetTeamColor));
								if (Ikaros.m_pCvars->bNameESP)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 5 + width, vScreen.y - 8 - height, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "%s", pInfo.name);
								}
								if (Ikaros.m_pCvars->iHealthESP == 1)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 5 + width, vScreen.y + 8 - height, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 2)
								{
									int r = 255 - (iHealth*2.55);
									int g = iHealth*2.55;
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 10, vPlayerHeadScreen.y - 1, 5, h + 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 9, vPlayerHeadScreen.y, 3, h - 1, r, g, 0, 255);
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 9, vPlayerHeadScreen.y, 3, h - 1 - (h * ((float)iHealth / 100.0f)), RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
								}
								else if (Ikaros.m_pCvars->iHealthESP == 3)
								{
									DrawHeader(vPlayerHeadScreen.x - width + 2, vPlayerFootScreen.y + 3, width * 2, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), (iHealth / (100 / (width * 2)) - 2));
								}
							}
							else if (Ikaros.m_pCvars->i2DBox == 3)
							{
								int h = vPlayerFootScreen.y - vPlayerHeadScreen.y;
								//int w = clamp(width / 1.35, 4, 18);
								
								DrawCornerBox(vPlayerHeadScreen.x, vPlayerFootScreen.y, width * 2, h, 1, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), ALPHA(dwGetTeamColor));

								if (Ikaros.m_pCvars->bNameESP)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 5 + width, vScreen.y - 8 - height, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "%s", pInfo.name);
								}
								if (Ikaros.m_pCvars->iHealthESP == 1)
								{
									Ikaros.m_pDraw->Text(vScreen.x + 5 + width, vScreen.y + 8 - height, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 2)
								{
									int r = 255 - (iHealth * 2.55);
									int g = iHealth * 2.55;
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 10, vPlayerHeadScreen.y - 1, 5, h + 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 9, vPlayerHeadScreen.y, 3, h - 1, r, g, 0, 255);
									Ikaros.m_pDraw->FillRGBA(vPlayerHeadScreen.x - width - 9, vPlayerHeadScreen.y, 3, h - 1 - (h * ((float)iHealth / 100.0f)), RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
								}
								else if (Ikaros.m_pCvars->iHealthESP == 3)
								{
									DrawHeader(vPlayerHeadScreen.x - width + 2, vPlayerFootScreen.y + 3, width * 2, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), (iHealth / (100 / (width * 2))) - 2);
								}
							}
							else
							{
								if (Ikaros.m_pCvars->bNameESP)
								{
									Ikaros.m_pDraw->Text(vScreen.x, vScreen.y - 8, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "%s", pInfo.name);
								}
								if (Ikaros.m_pCvars->iHealthESP == 1)
								{
									Ikaros.m_pDraw->Text(vScreen.x, vScreen.y + 8, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 2)
								{
									DrawHealthbar(iHealth, vScreen, 28, 20);
								}
								else if (Ikaros.m_pCvars->iHealthESP == 3)
								{
									DrawHeader(vScreen.x - 19, vScreen.y + 24, 39 + 2, RED(dwGetTeamColor), GREEN(dwGetTeamColor), BLUE(dwGetTeamColor), (iHealth / 2.5) - 2);
								}
							}
						}
					}
				}
			}
		}
	}
}