#include "Include.h"

bool bSendPacket = true;
void* baseptr = NULL;
bool bNoRecoil = true;
bool bRCS = true;
bool bChams = true;
bool bXQZ = true;
bool bShake = true;
bool bAntiAim = true;
bool bSilent = true;
bool bResChange = false;
int iChokedPackets = 0;
BYTE patch[2];
QAngle qRealView;

void AntiAntiAimYProxy(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float flYaw = pData->m_Value.m_Float;

	if (flYaw > 180.0f)
		flYaw -= 360.0f;
	if (flYaw < -180.0f)
		flYaw += 360.0f;

	static bool JitterFix[64];
	bool jitTemporary = JitterFix[((C_BaseEntity*)(pStruct))->index];

	JitterFix[((C_BaseEntity*)(pStruct))->index] = (flYaw >= 180 && flYaw <= 360);

	if (jitTemporary && (flYaw >= 0 && flYaw <= 181))
	{
		flYaw += 359;
	}

	flYaw = flYaw - (int)(flYaw / 360) * 360;

	if (flYaw < -181)
	{
		flYaw = flYaw + 360;
	}
	else if (flYaw > 181)
	{
		flYaw = flYaw - 360;
	}

	if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].bAdvancedYaw)
	{
		flYaw -= Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iAdvancedYaw;
	}
	else
	{
		if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iYaw == 1)
		{
			flYaw -= 180.0f;
		}
		else if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iYaw == 2)
		{
			flYaw += 90.0f;
		}
		else if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iYaw == 3)
		{
			flYaw -= 90.0f;
		}
	}

	*(float*)pOut = flYaw;
}

void AntiAntiAimXProxy(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float flPitch = pData->m_Value.m_Float;

	if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iPitch == 1)
	{
		if (flPitch > 181 && flPitch < 271)
		{
			flPitch = 269.0;
		}

		if (flPitch > 89 && flPitch < 181)
		{
			flPitch = 89.0;
		}
	}
	else if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iPitch == 2)
	{
		flPitch = -89.0f;
	}
	else if (Ikaros.m_pPlayerlist[((C_BaseEntity*)(pStruct))->index].iPitch == 3)
	{
		flPitch = 89.0f;
	}

	*(float*)pOut = flPitch;
}

void ForceCommands()
{
	ConVar* skybox = Ikaros.m_pCvar->FindVar("r_skybox");
	ConVar* clearsky = Ikaros.m_pCvar->FindVar("gl_clear");
	ConVar* bright = Ikaros.m_pCvar->FindVar("mat_fullbright");

	if (Ikaros.m_pCvars->iAntiAimTypeY == 3)
		Ikaros.m_pCvars->bAimAtTargets = false;

	if ((Ikaros.m_pCvars->iNoRecoil > 0) && bNoRecoil)
	{
		Ikaros.m_pCvars->iRCS = 0;
		bRCS = true;
		bNoRecoil = false;
	}

	if ((Ikaros.m_pCvars->iRCS > 0) && bRCS)
	{
		Ikaros.m_pCvars->iNoRecoil = 0;
		bRCS = false;
		bNoRecoil = true;
	}

	if (Ikaros.m_pCvars->bChams && bChams)
	{
		Ikaros.m_pCvars->bXQZWalls = false;
		bChams = false;
		bXQZ = true;
	}

	if (Ikaros.m_pCvars->bXQZWalls && bXQZ)
	{
		Ikaros.m_pCvars->bChams = false;
		bChams = true;
		bXQZ = false;
	}

	if (!Ikaros.m_pCvars->bSilent)
		Ikaros.m_pCvars->bPSilent = false;

	if (Ikaros.m_pCvars->bShowShake && bShake)
	{
		if (Ikaros.m_pCvars->iAntiAimTypeX == 3)
			Ikaros.m_pCvars->bAntiAim = false;

		Ikaros.m_pCvars->bSilent = false;
		bShake = false;
		bAntiAim = true;
		bSilent = true;
	}

	if (Ikaros.m_pCvars->bSilent && bSilent)
	{
		Ikaros.m_pCvars->bShowShake = false;
		bSilent = false;
		bAntiAim = true;
		bShake = true;
	}

	if (Ikaros.m_pCvars->bAntiAim && bAntiAim)
	{
		if (Ikaros.m_pCvars->iAntiAimTypeX == 3)
			Ikaros.m_pCvars->bShowShake = false;

		bAntiAim = false;
		bSilent = true;
		bShake = true;
	}

	if (Ikaros.m_pCvars->bNoSky)
	{
		skybox->SetValue(0);
		clearsky->SetValue(1);
	}
	else
	{
		skybox->SetValue(1);
		clearsky->SetValue(0);
	}

	if (Ikaros.m_pCvars->bFullbright)
	{
		bright->SetValue(1);
	}
	else
	{
		bright->SetValue(0);
	}

	if (Ikaros.m_pCvars->bSigFail)
	{
		Ikaros.m_pCvars->bPSilent = false;
		Ikaros.m_pCvars->bSpeed = false;
		if (Ikaros.m_pCvars->iAntiAimTypeX > 3)
			Ikaros.m_pCvars->iAntiAimTypeX = 3;
		if (Ikaros.m_pCvars->iAntiAimTypeY > 3)
			Ikaros.m_pCvars->iAntiAimTypeY = 3;
	}
}

CUserCmd* __stdcall new_GetUserCmd(int sequence_number)
{
	static CUserCmd* pCommands = *(CUserCmd**)((DWORD)Ikaros.m_pInput + 0xC4);
	return &pCommands[sequence_number % MULTIPLAYER_BACKUP];
}

void __stdcall new_HudUpdate(bool bActive)
{
	ClientClass *pClass = Ikaros.m_pClient->GetAllClasses();
	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->GetName();

		if (!strcmp(pszName, "DT_CSPlayer"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = pClass->m_pRecvTable->GetProp(i);

				if (!strcmp(pProp->GetName(), "m_angEyeAngles[0]"))
					pProp->SetProxyFn(AntiAntiAimXProxy);
				if (!strcmp(pProp->GetName(), "m_angEyeAngles[1]"))
					pProp->SetProxyFn(AntiAntiAimYProxy);
			}
		}
		pClass = pClass->m_pNext;
	}

	pClientHook->Function<HudUpdate_t>(8)(bActive);
}

void __stdcall new_FrameStageNotify(ClientFrameStage_t curStage)
{
	if (Ikaros.m_pEngine->IsInGame())
	{
		if (curStage == FRAME_UNDEFINED)
			return;
	}

	QAngle *PunchAngle, OldPunchAngle;
	PunchAngle = (QAngle*)((DWORD)Ikaros.m_pMyPlayer->Ent() + Ikaros.m_pOffsets->PunchAngle);

	if (Ikaros.m_pCvars->bNoVisRecoil)
	{
		if (curStage == FRAME_RENDER_START)
		{
			if (Ikaros.m_pEngine->IsInGame() && Ikaros.m_pMyPlayer->Ent())
			{
				if (PunchAngle->x != 0 || PunchAngle->y != 0 || PunchAngle->z != 0)
				{
					OldPunchAngle = *PunchAngle;
					*PunchAngle = QAngle(0, 0, 0);
				}
			}
		}
	}

	pClientHook->Function<FrameStageNotify_t>(32)(curStage);

	if (Ikaros.m_pCvars->bNoVisRecoil)
	{
		if (curStage == FRAME_RENDER_START)
		{
			if (Ikaros.m_pEngine->IsInGame() && Ikaros.m_pMyPlayer->Ent())
			{
				if (PunchAngle->x == 0 || PunchAngle->y == 0 || PunchAngle->z == 0)
				{
					*PunchAngle = OldPunchAngle;
				}
			}
		}
	}
}

void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	pPanelHook->Function<PaintTraverse_t>(40)(vguiPanel, forceRepaint, allowForce);

	const char* pszPanelName = Ikaros.m_pPanel->GetName(vguiPanel);
	bool isValidPanel = false;

	if (pszPanelName && pszPanelName[0] == 'M' && pszPanelName[3] == 'S' &&
		pszPanelName[9] == 'T' && pszPanelName[12] == 'P')
		isValidPanel = true;

	if (isValidPanel)
	{
		DO_ONCE(
			Ikaros.m_pNeeded->FontInit();
		Ikaros.m_pEngine->GetScreenSize(sScreenSize.m_iWidth, sScreenSize.m_iHeight);
		Ikaros.m_pEvents->RegisterSelf();
		);

		Ikaros.m_pEngine->GetScreenSize(sScreenSize2.m_iWidth, sScreenSize2.m_iHeight);

		if (sScreenSize.m_iWidth != sScreenSize2.m_iWidth || sScreenSize.m_iHeight != sScreenSize2.m_iHeight)
		{
			sScreenSize.m_iWidth = sScreenSize2.m_iWidth;
			sScreenSize.m_iHeight = sScreenSize2.m_iHeight;
			bResChange = true;
		}

		if (bResChange)
		{
			Ikaros.m_pNeeded->FontInit();
			bResChange = false;
		}

		ForceCommands();
		Ikaros.m_pMenu->DrawMenu();
	}
}

int __stdcall new_DrawModelEx(ModelRenderInfo_t &pInfo)
{
	pModelHook->Unhook(19);
	studiohdr_t* hdr = Ikaros.m_pModelinfo->GetStudiomodel(pInfo.pModel);
	if (pInfo.pModel && hdr)
	{
		static float fRed, fGreen, fBlue, fRed2, fGreen2, fBlue2, fRed3, fGreen3, fBlue3, fAlpha;
		const char* pszModelName = Ikaros.m_pModelinfo->GetModelName(pInfo.pModel);

		if (Ikaros.m_pCvars->bGlassChams)
		{
			fAlpha = 0.66f;
		}
		else
		{
			fAlpha = 1.0f;
		}

		if ((strstr(pszModelName, "models/player")))
		{
			if (Ikaros.m_pCvars->bChams && !Ikaros.m_pCvars->bPanicKey)
			{
				C_BaseEntity* pModelEntity = (C_BaseEntity*)Ikaros.m_pEntList->GetClientEntity(pInfo.entity_index);

				if (pModelEntity && Ikaros.m_pMyPlayer->BaseEnt())
				{
					player_info_t pinfo;

					if (Ikaros.m_pEntity->GetLifeState(pModelEntity)
						&& Ikaros.m_pEngine->GetPlayerInfo(pInfo.entity_index, &pinfo))
					{
						int iTeamIndex = Ikaros.m_pEntity->GetTeamID(pModelEntity);

						if (iTeamIndex == 2)
						{
							fRed = 1.0f;
							fGreen = 0.2f;
							fBlue = 0.2f;

							fRed3 = 1.0f;
							fGreen3 = 1.0f;
							fBlue3 = 0.2f;
						}
						else if (iTeamIndex == 3)
						{
							fRed = 0.2f;
							fGreen = 0.2f;
							fBlue = 1.0f;

							fRed3 = 0.2f;
							fGreen3 = 1.0f;
							fBlue3 = 0.2f;
						}
					}
					else
					{
						fRed = 1.0f;
						fGreen = 1.0f;
						fBlue = 1.0f;

						fRed3 = 1.0f;
						fGreen3 = 1.0f;
						fBlue3 = 1.0f;
					}
				}
				else
				{
					if (strstr(pszModelName, "models/player/t_"))
					{
						fRed = 1.0f;
						fGreen = 0.2f;
						fBlue = 0.2f;

						fRed3 = 1.0f;
						fGreen3 = 0.2f;
						fBlue3 = 0.2f;
					}
					if (strstr(pszModelName, "models/player/ct_"))
					{
						fRed = 0.2f;
						fGreen = 0.2f;
						fBlue = 1.0f;

						fRed3 = 0.2f;
						fGreen3 = 0.2f;
						fBlue3 = 1.0f;
					}
				}

				Ikaros.m_pNeeded->ForceMaterial(fRed3, fGreen3, fBlue3, fAlpha, mat3);
				Ikaros.m_pModelRender->DrawModelEx(pInfo);
				mat3->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				Ikaros.m_pNeeded->ForceMaterial(fRed, fGreen, fBlue, fAlpha, mat);
				Ikaros.m_pModelRender->DrawModelEx(pInfo);
			}
		}
		else if ((strstr(pszModelName, "models/weapons/w_")))
		{
			if (Ikaros.m_pCvars->bWeaponChams && !Ikaros.m_pCvars->bPanicKey)
			{
				if (strstr(pszModelName, "models/weapons/w_"))
				{
					fRed2 = 1.0f;
					fGreen2 = 1.0f;
					fBlue2 = 1.0f;
				}

				Ikaros.m_pNeeded->ForceMaterial(fRed2, fGreen2, fBlue2, fAlpha, mat2);
				Ikaros.m_pModelRender->DrawModelEx(pInfo);
				mat2->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			}
		}
		else
		{
			Ikaros.m_pModelRender->ForcedMaterialOverride(NULL);
		}
	}

	int bRet = Ikaros.m_pModelRender->DrawModelEx(pInfo);

	Ikaros.m_pModelRender->ForcedMaterialOverride(NULL);

	pModelHook->Hook((DWORD)new_DrawModelEx, 19);

	return bRet;
}

void __stdcall CL_FixMove(CUserCmd* cmd, QAngle viewangles)
{
	Vector move, movenorm, dir, set;
	QAngle movenormang, adjusted;

	float len;

	move.Init(cmd->forwardmove, cmd->sidemove, cmd->upmove);

	movenorm = move;

	VectorNormalize(movenorm);

	len = move.Length();

	VectorAngles(movenorm, movenormang);

	if (Ikaros.m_pCvars->bAntiAim)
	{
		if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
		{
			if (viewangles.x >= 0.0f && viewangles.x <= 89.0f)
			{
				viewangles.x = cmd->viewangles.x + 180.0f;
			}
			if (viewangles.x <= 0.0f && viewangles.x >= -89.0f)
			{
				viewangles.x = cmd->viewangles.x - 180.0f;
			}
		}
	}

	adjusted = movenormang + (cmd->viewangles - viewangles);

	AngleVectors(adjusted, &dir);

	set = dir * len;

	if (Ikaros.m_pCvars->bAntiAim)
	{
		if ((cmd->viewangles.x > 89.0f) || (cmd->viewangles.x < -89.0f))
			cmd->forwardmove = set.x;
		else if ((cmd->viewangles.x == 89.0f || cmd->viewangles.x == -89.0f))
			cmd->forwardmove = -set.x;
		else
			cmd->forwardmove = set.x;

		if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
			cmd->sidemove = -set.y;
		else
			cmd->sidemove = set.y;
	}
	else
	{
		cmd->forwardmove = set.x;
		cmd->sidemove = set.y;
	}
}

void Prediction(CUserCmd* pCmd, C_BasePlayer* LocalPlayer)
{
	float curtime = Ikaros.m_pGlobals->curtime;
	float frametime = Ikaros.m_pGlobals->frametime;

	Ikaros.m_pGlobals->curtime = Ikaros.m_pGlobals->interval_per_tick * Ikaros.m_pEntity->GetTickBase(LocalPlayer);
	Ikaros.m_pGlobals->frametime = Ikaros.m_pGlobals->interval_per_tick;
	
	*(CUserCmd**)((DWORD)LocalPlayer + 0xD60) = pCmd;				// m_pCurrentCommand
	*(C_BasePlayer**)((DWORD)hClient + 0x3B2EF8) = LocalPlayer;		// m_pPredictedPlayer
	*(int*)((DWORD)hClient + 0x38FF74) = pCmd->random_seed;			// m_pPredictedRandomSeed

	//BYTE byMoveData[0xA3];
	CMoveData Data;
	memset(&Data, 0, sizeof(Data));
	Ikaros.m_pPrediction->SetupMove(LocalPlayer, pCmd, NULL, &Data);
	Ikaros.m_pGameMovement->ProcessMovement(LocalPlayer, &Data);
	Ikaros.m_pPrediction->FinishMove(LocalPlayer, pCmd, &Data);

	*(CUserCmd**)((DWORD)LocalPlayer + 0xD60) = 0;					// m_pCurrentCommand
	*(C_BasePlayer**)((DWORD)hClient + 0x3B2EF8) = 0;				// m_pPredictedPlayer
	*(int*)((DWORD)hClient + 0x38FF74) = -1;						// m_pPredictedRandomSeed

	Ikaros.m_pGlobals->curtime = curtime;
	Ikaros.m_pGlobals->frametime = frametime;
	++*(int*)((DWORD)LocalPlayer + Ikaros.m_pOffsets->TickBase);
}

void __stdcall new_CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	if (Ikaros.m_pInput)
	{
		CUserCmd* cmd = Ikaros.m_pInput->GetUserCmd(sequence_number);
		C_BaseCombatWeapon* m_pWeapon = Ikaros.m_pNeeded->GetBaseCombatActiveWeapon(Ikaros.m_pMyPlayer->BaseEnt());

		if (Ikaros.m_pEngine->IsInGame() && Ikaros.m_pMyPlayer->BaseEnt() && !Ikaros.m_pEngine->IsHLTV())
		{
			if (Ikaros.m_pCvars->bNameStealer)
				Ikaros.m_pESP->NameChange();

			bSendPacket = true;

			if (Ikaros.m_pEntity->GetLifeState(Ikaros.m_pMyPlayer->BaseEnt()) && m_pWeapon)
			{
				int iFlags = Ikaros.m_pEntity->GetFlags(Ikaros.m_pMyPlayer->BaseEnt());
				int MoveType = Ikaros.m_pEntity->GetMoveType(Ikaros.m_pMyPlayer->BaseEnt());
				QAngle qPunchAngle = Ikaros.m_pEntity->GetPunchAngle(Ikaros.m_pMyPlayer->BaseEnt());
				int iWeaponID = Ikaros.m_pEntity->GetWeaponID(m_pWeapon);

				if (Ikaros.m_pCvars->bBunnyHop)
					Ikaros.m_pBunnyHop->BunnyHop(cmd);

				qRealView = cmd->viewangles;

				Ikaros.m_pESP->MaterialStuff();

				Ikaros.m_pCvar->FindVar("cl_pred_optimize")->SetValue(0);
				Prediction(cmd, (C_BasePlayer*)Ikaros.m_pMyPlayer->Ent());

				if (!(Ikaros.m_pNeeded->IsDefusing(m_pWeapon, cmd)
					|| Ikaros.m_pNeeded->IsCurWepGrenade(m_pWeapon)
					|| Ikaros.m_pNeeded->IsCurWepKnife(m_pWeapon)))
				{
					if (Ikaros.m_pCvars->bAimActive)
						Ikaros.m_pAimbot->AimAtTarget(cmd, m_pWeapon);

					if (Ikaros.m_pCvars->iPNoSpread == 2)
					{
						if (cmd->buttons & IN_ATTACK)
						{
							cmd->random_seed = 141;

							for (int iCmd = cmd->command_number;; iCmd++)
							{
								UINT uSeed = MD5_PseudoRandom(iCmd) & 0x7FFFFFF;
								uSeed &= 255;

								if (uSeed == 141)
								{
									cmd->command_number = iCmd;
									break;
								}
							}
						}
					}

					if ((!Ikaros.m_pCvars->bAntiAim
						&& (Ikaros.m_pCvars->iAntiAimTypeX == 3 || Ikaros.m_pCvars->iAntiAimTypeX == 4))
						|| (Ikaros.m_pCvars->bAntiAim && Ikaros.m_pCvars->iAntiAimTypeX != 3))
					{
						if (Ikaros.m_pCvars->iNoRecoil == 2)
						{
							cmd->viewangles -= qPunchAngle * 2;
						}

						if (Ikaros.m_pCvars->iNoSpread == 2)
						{
							float flSpread[2];
							Ikaros.m_pNoSpread->GetSpreadFix(cmd->random_seed, cmd->viewangles, flSpread);
							cmd->viewangles.x += flSpread[0];
							cmd->viewangles.y += flSpread[1];
							cmd->viewangles.z += flSpread[2];
						}
					}

					if (Ikaros.m_pCvars->bAimActive && Ikaros.m_pCvars->bSilent && Ikaros.m_pCvars->bPSilent && Ikaros.m_pCvars->iAim)
					{
						if (Ikaros.m_pNeeded->CrashCheck())
						{
							iChokedPackets++;

							float flServer = (float)Ikaros.m_pEntity->GetTickBase(Ikaros.m_pMyPlayer->BaseEnt()) * Ikaros.m_pGlobals->interval_per_tick;
							float flPrimaryAttack = Ikaros.m_pEntity->GetNextPrimaryAttack(m_pWeapon);

							bool bCanshoot = false;

							if (flPrimaryAttack <= flServer)
								bCanshoot = true;

							if (cmd->buttons & IN_ATTACK && !bCanshoot)
							{
								cmd->buttons &= ~IN_ATTACK;
							}
							else if (cmd->buttons & IN_ATTACK && bCanshoot)
							{
								if (iChokedPackets <= 10)
								{
									if (Ikaros.m_pCvars->bAimActive && Ikaros.m_pCvars->bAiming)
										cmd->viewangles = Ikaros.m_pAimbot->qAim;

									if (Ikaros.m_pCvars->iNoRecoil == 1)
									{
										cmd->viewangles -= qPunchAngle * 2;
									}

									if (Ikaros.m_pCvars->iNoSpread == 1)
									{
										float flSpread[2];
										Ikaros.m_pNoSpread->GetSpreadFix(cmd->random_seed, cmd->viewangles, flSpread);
										cmd->viewangles.x += flSpread[0];
										cmd->viewangles.y += flSpread[1];
										cmd->viewangles.z += flSpread[2];
									}

									bSendPacket = false;
								}
								else
								{
									bSendPacket = true;
									iChokedPackets = 0;
								}
							}
							else
							{
								cmd->viewangles = qRealView;
								bSendPacket = true;
							}
						}
					}
					else
					{
						if (Ikaros.m_pCvars->bAutoPistol)
							Ikaros.m_pAimbot->AutoPistol(cmd, m_pWeapon);
					}

					if (Ikaros.m_pCvars->bTriggerActive)
						Ikaros.m_pAimbot->Seedtrigger(cmd);

					if (Ikaros.m_pCvars->bAntiAim)
						Ikaros.m_pAntiAim->BackFlipAngles(cmd, m_pWeapon);

					NormalizeAngles(cmd->viewangles);

					CL_FixMove(cmd, qRealView);
				}
			}
		}
	}
}
