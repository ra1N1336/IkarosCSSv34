#include "cMenu.h"

tagPOINT Mouse;
int SavedX, SavedY;
bool bCfg = true;
bool bOnze = true;
bool bSave = false;
bool bSaveMonitorPos = false;
bool bSavePos = true;
bool bLock = false;
bool bClick = true;
bool bLoad = true;
bool bMouseOnce = true;
int Selection = 1, iSel = 0;

//char* Keys[] = { "Press Any Key", "L Mouse", "R Mouse", "Cancel", "M Mouse", "", "", "", "Backspace", "Tab", "", "", "Clear", "Return", "", "", "Shift", "Ctrl", "Alt", "Pause", "Caps Lock", "", "", "", "", "", "", "Escape", "", "", "", "", "Spacebar", "Page up", "Page down", "End", "Home", "L Arrow", "Up Arrow", "R Arrow", "D Arrow", "Select", "Print", "Execute", "P.Screen", "Insert", "Delete", "Help", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "L.Menu", "R.Menu", "App", "", "Sleep", "Num 0", "Num 1", "Num 2", "Num 3", "Num 4", "Num 5", "Num 6", "Num 7", "Num 8", "Num 9", "Multiply", "Add", "Separator", "Subtract", "Decimal", "Divide", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", "", "", "", "", "", "", "", "", "NumLock", "ScrLock", "Equals", "", "", "", "", "", "", "", "", "", "", "", "", "", "LShift", "RShift", "LCtrl", "RCtrl", "LMenu", "RMenu" };
char* TrigBox[7] = { "All", "Head", "Chest", "Pelvis", "Arms", "Legs", "Multi Hitbox" };
char* AimSelect[3] = { "Distance", "Field of View", "Next Shot" };
char* Removals[3] = { "Off", "Only Aimbot", "Always" };
char* AntiAimX[4] = { "SMAC/KAC Safe", "Normal", "Configurable", "Static" };
char* AntiAimY[6] = { "Normal", "Jitter", "Configurable", "Spinhack", "Fake Sideways", "Fake Static" };
char* Keys[11] = { "MouseW", "LMouse", "RMouse", "Mouse 4", "Mouse 5", "Shift", "Control", "Alt", "Q", "F", "E" };
char* AimMode[2] = { "Legit", "Rage" };
char* TrigMode[3] = { "Normal", "No Spread", "Seed"};
char* ESPStyle[4] = { "No", "Simple", "Dynamic", "InterwebZ" };
char* ESPHealth[4] = { "Off", "Text", "Healthbar", "InterwebZ" };
char* Crosshair[4] = { "Off", "Dot", "Small Cross", "Box" };
char* AimMethod[3] = { "Hitbox", "Bone", "Hack vs Hack" };
char* Strafe[3] = { "Off", "Assist", "Full" };
char* AAAPitch[4] = { "Off", "Auto", "Up", "Down" };
char* AAAYaw[4] = { "Off", "Inverse", "Half Left", "Half Right"};

enum Tabs
{
	tab0,
	tab1,
	tab2,
	tab3,
	tab4,
	tab5,
	tab6,
	tab7,
	tab8,
	tab9
};

struct OpenTab
{
	Tabs ActiveTab;
} openTab;

struct sComboBox
{
	bool Open, Active;
	int iSelect;
	char* Name;
} cComboBox[21];

void ESPBox(int x, int y, int x1, int y1, int r, int g, int b, int a)
{
	Ikaros.m_pDraw->Border(x, y, x1, y1, 1, r, g, b, a);
	Ikaros.m_pDraw->Border(x - 1, y - 1, x1 + 2, y1 + 2, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->Border(x + 1, y + 1, x1 - 2, y1 - 2, 1, 0, 0, 0, 255);
}

void DrawMouse(int x, int y)
{
	Ikaros.m_pDraw->FillRGBA(x, y, 1, 17, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x, y + 16, 2, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 2, y + 15, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 3, y + 14, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 4, y + 13, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 5, y + 14, 1, 2, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 6, y + 16, 1, 2, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 18, 2, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 8, y + 14, 1, 2, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 9, y + 16, 1, 2, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 12, 1, 2, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 12, 5, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 11, y + 11, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 10, y + 10, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 9, y + 9, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 8, y + 8, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 7, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 6, y + 6, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 5, y + 5, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 4, y + 4, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 3, y + 3, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 2, y + 2, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 1, y + 1, 1, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->FillRGBA(x + 1, y + 2, 1, 14, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 2, y + 3, 1, 12, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 3, y + 4, 1, 10, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 4, y + 5, 1, 8, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 5, y + 6, 1, 8, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 6, y + 7, 1, 9, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 8, 1, 4, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 8, y + 9, 1, 3, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 9, y + 10, 1, 2, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 10, y + 11, 1, 1, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 7, y + 14, 1, 4, 255, 255, 255, 255);
	Ikaros.m_pDraw->FillRGBA(x + 8, y + 16, 1, 2, 255, 255, 255, 255);
}

bool cMouse::IsInBox(int x, int y, int w, int h)
{
	if (Ikaros.m_pCvars->iMouseX >= x &&
		Ikaros.m_pCvars->iMouseX <= x + w &&
		Ikaros.m_pCvars->iMouseY >= y &&
		Ikaros.m_pCvars->iMouseY <= y + h)
		return true;
	else
		return false;
}

void cMouse::ClickHandler()
{
	if ((GetAsyncKeyState(VK_LBUTTON)))
	{
		bMouse1pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_LBUTTON)))
	{
		if (bMouse1pressed)
			bMouse1released = true;
		else
		{
			bMouse1released = false;
		}
		bMouse1pressed = false;
	}

	if ((GetAsyncKeyState(VK_RBUTTON)))
	{
		bMouse2pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_RBUTTON)))
	{
		if (bMouse2pressed)
			bMouse2released = true;
		else
		{
			bMouse2released = false;
		}
		bMouse2pressed = false;
	}
}

void CfgSelectButton(int x, int y)
{
	if (Ikaros.m_pMouse->IsInBox(x, y, 45, 15))
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(ClickedButtonColor), GREEN(ClickedButtonColor), BLUE(ClickedButtonColor), ALPHA(ClickedButtonColor));
		if (Ikaros.m_pMouse->bMouse1released)
		{
			bIsRage = !bIsRage;
			Ikaros.m_pSettings->LoadSettings();
		}	
	}
	else
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(SaveButtonColor), GREEN(SaveButtonColor), BLUE(SaveButtonColor), ALPHA(SaveButtonColor));
	}

	if (bIsRage)
	{
		Ikaros.m_pDraw->CenterText(x + 22, y - 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Rage");
	}
	else
	{
		Ikaros.m_pDraw->CenterText(x + 22, y - 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Legit");
	}
}

void SaveButton(int x, int y)
{
	if (bSave)
	{
		Ikaros.m_pSettings->SaveSettings();
		bSave = false;
	}
	if (Ikaros.m_pMouse->IsInBox(x, y, 45, 15))
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(ClickedButtonColor), GREEN(ClickedButtonColor), BLUE(ClickedButtonColor), ALPHA(ClickedButtonColor));
		Ikaros.m_pDraw->CenterText(x + 22, y - 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Save");
		if (Ikaros.m_pMouse->bMouse1released)
			bSave = true;
	}
	else
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(SaveButtonColor), GREEN(SaveButtonColor), BLUE(SaveButtonColor), ALPHA(SaveButtonColor));
		Ikaros.m_pDraw->CenterText(x + 22, y - 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Save");
	}
}

void DrawInfo(char* Text)
{
	Ikaros.m_pDraw->Text(Ikaros.m_pCvars->iMenuX + 165, Ikaros.m_pCvars->iMenuY + 445, 255, 255, 255, 255, Text);
}

void CMenu::DrawWindow(int x, int y, int w, int h, char* cName)
{
	Ikaros.m_pDraw->FillRGBA(x, y, w, h, RED(BackgroundColor), GREEN(BackgroundColor), BLUE(BackgroundColor), ALPHA(BackgroundColor));//Background
	Ikaros.m_pDraw->Border(x, y, w, h, 6, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));//Border
	Ikaros.m_pDraw->FillRGBA(x, y, w, 25, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));//Topbar
	Ikaros.m_pDraw->Text(x + 6, y + 6, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), cName);//Name
	Ikaros.m_pDraw->Border(x, y, w + 5, h + 5, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));//Black 1px Outline
	Ikaros.m_pDraw->Border(x + 5, y + 25, w - 5, h - 25, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));//Black 1px Inline
}

void CMenu::DrawGroupBox(int x, int y, int w, int h, char* Name)
{
	Ikaros.m_pDraw->FillRGBA(x, y, w, h, RED(Grey1), GREEN(Grey1), BLUE(Grey1), ALPHA(Grey1));//Background
	Ikaros.m_pDraw->FillRGBA(x, y, w, 20, RED(GroupBoxColor), GREEN(GroupBoxColor), BLUE(GroupBoxColor), ALPHA(GroupBoxColor));//Topbar
	Ikaros.m_pDraw->Text(x + 3, y + 4, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), Name);
}

void CMenu::DrawComboBox(int x, int y, char* Name, int &Selection, int num, int max, char** structs, char* Description)
{
	cComboBox[num].Name = structs[Selection];
	Ikaros.m_pDraw->FillRGBA(x + 2, y - 3, 85, 2, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Top
	Ikaros.m_pDraw->FillRGBA(x + 2, y - 3, 2, 22, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Left
	Ikaros.m_pDraw->FillRGBA(x + 87, y - 3, 2, 22, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Right
	if (cComboBox[num].Active)
	{
		cComboBox[num].iSelect = Selection;
		if (Ikaros.m_pMouse->IsInBox(x + 25, y - 1, 69, 23) && Ikaros.m_pMouse->bMouse1released && bClick)
		{
			cComboBox[num].Open = true;
			cComboBox[num].Active = false;
		}
		Ikaros.m_pDraw->FillRGBA(x + 2, y + 17, 85, 2, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Bottom
		Ikaros.m_pDraw->Text(x + 8, y + 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), cComboBox[num].Name);
		if (Ikaros.m_pMouse->IsInBox(x + 2, y - 3, 85, 22) && !bLock)
		{
			DrawInfo(Description);
		}
	}
	else
	{
		if (cComboBox[num].Open)
		{
			bLock = true;
			DrawInfo(Description);
			for (int i = 0; i < max; i++)
			{
				Ikaros.m_pDraw->FillRGBA(x + 2, y + (i * 20), 87, 20, RED(BackgroundColor), GREEN(BackgroundColor), BLUE(BackgroundColor), ALPHA(BackgroundColor));//Back 1
				Ikaros.m_pDraw->FillRGBA(x + 2, y - 1 + (i * 20), 2, 24, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Left * count
				Ikaros.m_pDraw->FillRGBA(x + 87, y - 1 + (i * 20), 2, 24, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Right * count
				if (Ikaros.m_pMouse->IsInBox(x + 6, y + 1 + (i * 20), 79, 20))
				{
					Ikaros.m_pDraw->FillRGBA(x + 6, y + 1 + (i * 20), 79, 20, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));//highlight selection
					if (Ikaros.m_pMouse->bMouse1released)
					{
						cComboBox[num].iSelect = i;
						cComboBox[num].Name = structs[cComboBox[num].iSelect];
						Selection = cComboBox[num].iSelect;
						cComboBox[num].Open = false;
						cComboBox[num].Active = true;
						bLock = false;
					}
				}
				Ikaros.m_pDraw->Text(x + 8, y + 3 + (i * 20), RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), structs[i]);//List struct
			}
			Ikaros.m_pDraw->FillRGBA(x + 2, y + 3 + (max * 20), 87, 2, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));//Bottom
		}
	}

	Ikaros.m_pDraw->Text(x + 92, y + 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), Name);
}

void CMenu::CloseAllComboBoxes()
{
	for (int n = 0; n <= 21; n++)
	{
		cComboBox[n].Open = false;
		cComboBox[n].Active = true;
	}
	bLock = false;
}

void CMenu::DrawCheckBox(int x, int y, const char* szString, bool &toggle, char* Description)
{
	Ikaros.m_pDraw->FillRGBA(x + 2, y - 3, 14, 14, RED(Grey0), GREEN(Grey0), BLUE(Grey0), ALPHA(Grey0));
	if (Ikaros.m_pMouse->IsInBox(x + 2, y - 3, 14, 14))
	{
		Ikaros.m_pDraw->Border(x + 2, y - 3, 13, 13, 1, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));
		DrawInfo(Description);
	}
	if (Ikaros.m_pMouse->IsInBox(x + 4, y - 1, 10, 10) && Ikaros.m_pMouse->bMouse1released)
	{
		toggle =! toggle;
	}
	if (toggle)
	{
		Ikaros.m_pDraw->FillRGBA(x + 4, y - 1, 10, 10, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));
	}
	Ikaros.m_pDraw->Text(x + 20, y - 2, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), szString);
}

void CMenu::DrawTabs(const char* Name, int tab, int x, int y)
{
	Ikaros.m_pDraw->FillRGBA(x, y, 150, 45, RED(Grey1), GREEN(Grey1), BLUE(Grey1), ALPHA(Grey1));

	if (Ikaros.m_pMouse->IsInBox(x, y, 150, 45))
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 150, 45, RED(Grey4), GREEN(Grey4), BLUE(Grey4), ALPHA(Grey4));
		if (Ikaros.m_pMouse->bMouse1released)
		{
			CloseAllComboBoxes();

			if (tab == 1)
				openTab.ActiveTab = tab1;
			else if (tab == 2)
				openTab.ActiveTab = tab2;
			else if (tab == 3)
				openTab.ActiveTab = tab3;
			else if (tab == 4)
				openTab.ActiveTab = tab4;
			else if (tab == 5)
				openTab.ActiveTab = tab5;
			else if (tab == 6)
				openTab.ActiveTab = tab6;
			else if (tab == 7)
				openTab.ActiveTab = tab7;
			else if (tab == 8)
				openTab.ActiveTab = tab8;
			else if (tab == 9)
				openTab.ActiveTab = tab9;
		}
	}

	Ikaros.m_pDraw->FillRGBA(x + 135, y + 5, 10, 35, RED(Grey3), GREEN(Grey3), BLUE(Grey3), ALPHA(Grey3));

	Ikaros.m_pDraw->Text(x + 25, y + 14, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), Name);
}

void CMenu::DrawCloseButton(int x, int y)
{
	if (Ikaros.m_pMouse->IsInBox(x, y, 45, 15))
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(Red1), GREEN(Red1), BLUE(Red1), ALPHA(Red1));
		if (Ikaros.m_pMouse->bMouse1released)
			Ikaros.m_pCvars->bShowGUI = false;
	}
	else
	{
		Ikaros.m_pDraw->FillRGBA(x, y, 45, 15, RED(Red0), GREEN(Red0), BLUE(Red0), ALPHA(Red0));
	}
	Ikaros.m_pDraw->Text(x + 19, y + 1, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "X");
}

void CMenu::Slider(int x, int y, bool bInt, float &iInput, float iMin, float iMax, char* Name, char* Description)
{
	float sliderpos, barpos;

	if (Ikaros.m_pMouse->IsInBox(x, y + 3, 200, 9))
	{
		DrawInfo(Description);
	}

	if (Ikaros.m_pMouse->IsInBox(x, y + 3, 200, 9) && Ikaros.m_pMouse->bMouse1pressed)
	{
		sliderpos = (Ikaros.m_pCvars->iMouseX - x);
	}
	else
	{
		sliderpos = (((iInput * 100) * 2) / iMax);
	}

	iInput = (iMax * (sliderpos / 2) / 100);
	barpos = (sliderpos / 200 * 100) * 2;

	if (barpos > 200)
		barpos = 200;

	if (bInt)
	{
		double integral;
		float fraction = (float)modf(iInput, &integral);
		if (fraction >= 0.5)
			iInput += 1;
		iInput = (int)integral;
	}
		
	iInput = clamp(iInput, iMin, iMax);

	Ikaros.m_pDraw->FillRGBA(x, y + 5, 202, 5, RED(Grey2), GREEN(Grey2), BLUE(Grey2), ALPHA(Grey2));

	Ikaros.m_pDraw->FillRGBA(x + 1, y + 6, barpos, 3, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));

	Ikaros.m_pDraw->FillRGBA(x + barpos - 2, y + 3, 5, 9, RED(ButtonColor), GREEN(ButtonColor), BLUE(ButtonColor), ALPHA(ButtonColor));

	Ikaros.m_pDraw->Text(x + 208, y, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "%s: %0.1f", Name, iInput);
}

void DrawMonitorBar(int x, int y, int cur, const char* title)
{
	cur = clamp(cur, 0, 100);

	Ikaros.m_pDraw->FillRGBA(x, y, 30, 160, (int)(cur*2.55), (255 - (int)(cur*2.55)), 0, 255);
	Ikaros.m_pDraw->FillRGBA(x, y, 30, 160 - (cur * 1.6), RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
	Ikaros.m_pDraw->Text(x, y + 169, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), title);
}

void CMenu::DrawMonitor(int x, int y)
{
	if (Ikaros.m_pMouse->IsInBox(x, y, 160, 240) && Ikaros.m_pMouse->bMouse1pressed)
	{
		if (!bSaveMonitorPos)
		{
			Ikaros.m_pCvars->iMonitorSavePosX = Ikaros.m_pCvars->iMouseX - x;
			Ikaros.m_pCvars->iMonitorSavePosY = Ikaros.m_pCvars->iMouseY - y;
			bSaveMonitorPos = true;
		}
		Ikaros.m_pCvars->iMonitorPosX = Ikaros.m_pCvars->iMouseX;
		Ikaros.m_pCvars->iMonitorPosY = Ikaros.m_pCvars->iMouseY;
		Ikaros.m_pCvars->iMonitorPosX = Ikaros.m_pCvars->iMonitorPosX - Ikaros.m_pCvars->iMonitorSavePosX;
		Ikaros.m_pCvars->iMonitorPosY = Ikaros.m_pCvars->iMonitorPosY - Ikaros.m_pCvars->iMonitorSavePosY;
	}
	else
	{
		bSaveMonitorPos = false;
	}

	DrawWindow(x, y, 155, 240, "Monitor");

	//Speed
	int iSpeed = 0;
	float flPunch = 0.0f;
	float flAccuracy = 0.0f;
	float gabenplz = 0.0f;
	if (Ikaros.m_pNeeded->CrashCheck())
	{
		Vector vSpeed = Ikaros.m_pMyPlayer->BaseEnt()->m_vecVelocity;
		iSpeed = (int)vSpeed.Length2D();

		QAngle pAngle = Ikaros.m_pEntity->GetPunchAngle(Ikaros.m_pMyPlayer->BaseEnt());
		float flModifier = VectorNormalize( pAngle.Base( ) );
 
		flModifier -= ( 10.0f + flModifier * 0.5f ) * Ikaros.m_pGlobals->interval_per_tick;
		pAngle *= flModifier;
		flPunch = ((pAngle.x * 17.77777777777778) * 1.25);

		float flAccuracy = Ikaros.m_pNoSpread->GetVecSpread(gabenplz);
		gabenplz = (int)(flAccuracy * 66.67);
	}

	DrawMonitorBar( x + 12, y + 42, (-flPunch), "Recoil");
	DrawMonitorBar( x + 65, y + 42, (iSpeed * 0.2), "Speed");
	DrawMonitorBar( x + 118, y + 42, (gabenplz), "Spread");
}

void CMenu::DrawPlayerList()
{
	int in = 1;
	int x1 = Ikaros.m_pCvars->iMenuX + 165;
	int y1 = Ikaros.m_pCvars->iMenuY + 35;

	if (Ikaros.m_pEngine->IsConnected()
		&& Ikaros.m_pEngine->IsInGame()
		&& Ikaros.m_pMyPlayer->BaseEnt()
		&& !Ikaros.m_pEngine->IsTakingScreenshot()
		&& !Ikaros.m_pEngine->IsLevelMainMenuBackground())
	{
		player_info_t pInfo;
		//----------------------------------//
		for (int index = 0; index < Ikaros.m_pGlobals->maxClients; index++)
		{
			if (index == Ikaros.m_pEngine->GetLocalPlayer())
				continue;

			IClientEntity* ClientEntity = Ikaros.m_pEntList->GetClientEntity(index);

			if (ClientEntity == NULL)
				continue;

			C_BaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

			if (pBaseEntity == NULL)
				continue;

			if (Ikaros.m_pEntity->GetTeamID(pBaseEntity) == Ikaros.m_pEntity->GetTeamID(Ikaros.m_pMyPlayer->BaseEnt()))
				continue;

			if (Ikaros.m_pEngine->GetPlayerInfo(index, &pInfo))
			{
				Ikaros.m_pPlayerlist[index].index = index;

				if (in >= 24)
					in = 1;

				if (Ikaros.m_pCvars->bShowGUI && Ikaros.m_pCvars->bPlayerList)
				{
					if (Ikaros.m_pMouse->IsInBox(x1, y1 + 16 + ((in)* 13), 625, 12))
					{
						Ikaros.m_pDraw->FillRGBA(x1, y1 + 16 + ((in)* 13), 625, 12, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor) + 5, ALPHA(MenuColor));//highlight selection
						if ((Ikaros.m_pMouse->bMouse1pressed))
						{
							iSel = in;
							Selection = Ikaros.m_pPlayerlist[index].index;
						}
					}

					Ikaros.m_pDraw->Text(x1 + 10, y1 + 15 + ((in)* 13), RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "%s: %s", pInfo.name, pInfo.guid);
				}
				in++;
			}
		}
	}
}

void CMenu::DrawMainFrame(int x, int y)
{
	//Main Window
	DrawWindow(x, y, 800, 475, "Ikaros Recode by n0xius");
	DrawCloseButton(x + 755, y + 1);

	//Tabs
	DrawTabs("Aimbot", 1, x + 6, y + 26);
	DrawTabs("Triggerbot", 2, x + 6, y + 71);
	DrawTabs("ESP", 3, x + 6, y + 116);
	DrawTabs("Radar", 4, x + 6, y + 161);
	DrawTabs("Anti Aim", 5, x + 6, y + 206);
	DrawTabs("Render", 6, x + 6, y + 251);
	DrawTabs("Miscellaneous", 7, x + 6, y + 296);
	DrawTabs("Player List", 8, x + 6, y + 341);
	DrawTabs("Color", 9, x + 6, y + 386);
	//Config Zone
	Ikaros.m_pDraw->FillRGBA(x + 6, y + 430, 150, 45, RED(Grey1), GREEN(Grey1), BLUE(Grey1), ALPHA(Grey1));
	CfgSelectButton(x + 20, y + 445);
	SaveButton(x + 90, y + 445);

	Ikaros.m_pDraw->FillRGBA(x + 160, y + 435, 635, 35, RED(Grey1), GREEN(Grey1), BLUE(Grey1), ALPHA(Grey1));

	if (openTab.ActiveTab == tab1)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 31, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 315, 400, "");
		DrawGroupBox(x + 480, y + 30, 315, 400, "Options:");
		DrawCheckBox(x + 165, y + 60, "Active", Ikaros.m_pCvars->bAimActive, "Enable Aimbot(Aim Help).");
		DrawCheckBox(x + 485, y + 60, "Auto Aim", Ikaros.m_pCvars->bAutoAim, "Aim automatically on the Target.");
		DrawCheckBox(x + 485, y + 90, "Auto Shoot", Ikaros.m_pCvars->bAutoShoot, "Shoot automatically when aimbot is on the target.");
		Slider(x + 485, y + 120, 0, Ikaros.m_pCvars->flAimHeight, 0.0f, 5.0f, "Aim Height", "Adjusts the aimbot height.");
		Slider(x + 485, y + 150, 1, Ikaros.m_pCvars->iAimSpot, 1, 12, "Aim Spot", "Adjusts the aim spot.");
		if (Ikaros.m_pCvars->iAim == 1)
		{
			DrawCheckBox(x + 485, y + 180, "Silent Aim", Ikaros.m_pCvars->bSilent, "Hides Aimbot movement for you.");
			DrawCheckBox(x + 485, y + 210, "Perfect Silent Aim", Ikaros.m_pCvars->bPSilent, "Hides Aimbot movement for you and spectators.");
			DrawCheckBox(x + 485, y + 240, "Aim at Team", Ikaros.m_pCvars->bTeamAim, "Aimbot aims at your teammates.");
			DrawCheckBox(x + 485, y + 270, "Autowall", Ikaros.m_pCvars->bAutoWall, "Aimbot shoots through penetratable walls.");
			DrawCheckBox(x + 485, y + 300, "Body AWP", Ikaros.m_pCvars->bBodyAWP, "Aimbot aims with the awp on the body(even when you set another aim spot).");
			DrawCheckBox(x + 485, y + 330, "Hitscan", Ikaros.m_pCvars->bHitscan, "Aimbot scans after visible parts of the body.");
			//DrawCheckBox(x + 485, y + 360, "Multipoint", Ikaros.m_pCvars->bMultipoint, "Aimbot scans after visible corners of the body.");
			if (Ikaros.m_pCvars->iAim_Mode == 1)
			{
				Slider(x + 165, y + 180, 1, Ikaros.m_pCvars->flFOV, 2.0f, 360.0f, "Field of View", "Adjusts how near at your crosshar the enemy should be that the aimbots aims.");
				DrawCheckBox(x + 165, y + 210, "Deathmatch Rage", Ikaros.m_pCvars->bDM, "Aimbot ignores targets that have more than 100 HP.");
			}
			else
			{
				DrawCheckBox(x + 165, y + 180, "Deathmatch Rage", Ikaros.m_pCvars->bDM, "Aimbot ignores targets that have more than 100 HP.");
			}
		}
		else
		{
			DrawCheckBox(x + 485, y + 180, "Aim at Team", Ikaros.m_pCvars->bTeamAim, "Aimbot aims at your teammates.");
			if (Ikaros.m_pCvars->iAim_Mode == 1)
			{
				DrawCheckBox(x + 165, y + 180, "Advanced Smooth", Ikaros.m_pCvars->bAdvancedSmooth, "Enable advanced smooth aim.");
				Slider(x + 165, y + 210, 1, Ikaros.m_pCvars->flFOV, 1.0f, 360.0f, "Field of View", "Adjusts how near at your crosshar the enemy should be that the aimbots aims.");
				if (Ikaros.m_pCvars->bAdvancedSmooth)
				{
					Slider(x + 165, y + 240, 1, Ikaros.m_pCvars->flSmoothX, 1.0f, 100.0f, "Smoothness X", "Adjusts how smooth the aimbot aims with the x(Pitch) axis.");
					Slider(x + 165, y + 270, 1, Ikaros.m_pCvars->flSmoothY, 1.0f, 100.0f, "Smoothness Y", "Adjusts how smooth the aimbot aims with the y(Yaw) axis.");
				}
				else
				{
					Slider(x + 165, y + 240, 1, Ikaros.m_pCvars->flSmoothX, 1.0f, 100.0f, "Smoothness", "Adjusts the smoothness of the aimbot.");
				}
			}
			else
			{
				DrawCheckBox(x + 165, y + 180, "Advanced Smooth", Ikaros.m_pCvars->bAdvancedSmooth, "Enable advanced smooth aim.");
				if (Ikaros.m_pCvars->bAdvancedSmooth)
				{
					Slider(x + 165, y + 210, 1, Ikaros.m_pCvars->flSmoothX, 1.0f, 100.0f, "Smoothness X", "Adjusts how smooth the aimbot aims with the x(Pitch) axis.");
					Slider(x + 165, y + 240, 1, Ikaros.m_pCvars->flSmoothY, 1.0f, 100.0f, "Smoothness Y", "Adjusts how smooth the aimbot aims with the y(Yaw) axis.");
				}
				else
				{
					Slider(x + 165, y + 210, 1, Ikaros.m_pCvars->flSmoothX, 1.0f, 100.0f, "Smoothness", "Adjusts the smoothness of the aimbot.");
				}
			}
		}
		DrawComboBox(x + 165, y + 150, "Aim on Key", Ikaros.m_pCvars->iAimKey, 3, 11, Keys, "Choose on which key the aimbot should activate.");
		DrawComboBox(x + 165, y + 120, "Target Selection", Ikaros.m_pCvars->iAim_Mode, 2, 3, AimSelect, "Select how the aimbot selects targets.");
		DrawComboBox(x + 165, y + 90, "Aimbot", Ikaros.m_pCvars->iAim, 1, 2, AimMode, "Choose the aimbot style.");
	}
	else if (openTab.ActiveTab == tab2)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 76, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 315, 400, "");
		DrawGroupBox(x + 480, y + 30, 315, 400, "Multi Hitbox:");
		DrawCheckBox(x + 165, y + 60, "Active", Ikaros.m_pCvars->bTriggerActive, "Enables Triggerbot(Shoots for you).");
		DrawCheckBox(x + 165, y + 90, "Auto Trigger", Ikaros.m_pCvars->bAutoTrigger, "Shoots automatically if the triggerbot should hit a target");
		DrawCheckBox(x + 165, y + 210, "Trigger at Team", Ikaros.m_pCvars->bTrigTeam, "Triggerbot also shoots on teammates.");
		DrawCheckBox(x + 485, y + 60, "Head", Ikaros.m_pCvars->bTrigHead, "");
		DrawCheckBox(x + 485, y + 90, "Chest", Ikaros.m_pCvars->bTrigChest, "");
		DrawCheckBox(x + 485, y + 120, "Pelvis", Ikaros.m_pCvars->bTrigPelvis, "");
		DrawCheckBox(x + 485, y + 150, "Arms", Ikaros.m_pCvars->bTrigArms, "");
		DrawCheckBox(x + 485, y + 180, "Legs", Ikaros.m_pCvars->bTrigLegs, "");
		DrawComboBox(x + 165, y + 180, "Key", Ikaros.m_pCvars->iTrigKey, 6, 11, Keys, "Choose on which key the triggerbot should activate.");
		DrawComboBox(x + 165, y + 150, "Hitbox", Ikaros.m_pCvars->iTrigBone, 5, 7, TrigBox, "Choose on which hitbox the triggerbot should shoot.");
		DrawComboBox(x + 165, y + 120, "Mode", Ikaros.m_pCvars->iTriggerbot, 4, 3, TrigMode, "Select the triggerbot mode.");
		Slider(x + 165, y + 240, 1, Ikaros.m_pCvars->iTrigDelay, 0, 1000, "Triggerdelay", "How delayed the triggerbot should shoot.");
	}
	else if (openTab.ActiveTab == tab3)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 121, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 315, 400, "");
		DrawGroupBox(x + 480, y + 30, 315, 400, "Preview:");
		DrawCheckBox(x + 165, y + 60, "Active ", Ikaros.m_pCvars->bESP, "Enables ESP(Extrasensory perception).");
		DrawCheckBox(x + 165, y + 90, "Name ESP ", Ikaros.m_pCvars->bNameESP, "Shows name esp on target.");
		DrawCheckBox(x + 165, y + 120, "Hitbox ESP ", Ikaros.m_pCvars->bBoneESP, "Shows all hitboxes on target.");
		DrawCheckBox(x + 165, y + 150, "Aimspot ESP ", Ikaros.m_pCvars->bAimspotESP, "Shows the aimbot aim spot.");
		DrawCheckBox(x + 165, y + 180, "Enemy Only ", Ikaros.m_pCvars->bEnemyOnlyESP, "Draws ESP only on enemy.");
		DrawComboBox(x + 165, y + 240, "Health", Ikaros.m_pCvars->iHealthESP, 8, 4, ESPHealth, "Select the Health ESP style.");
		DrawComboBox(x + 165, y + 210, "Box", Ikaros.m_pCvars->i2DBox, 7, 4, ESPStyle, "Select the ESP Box style.");
		if (Ikaros.m_pCvars->bESP)
		{
			int Health = 78;
			int g = Health * 2.55;
			int r = 255 - g;
			if (Ikaros.m_pCvars->i2DBox == 1)
			{
				ESPBox(x + 603 - 20, y + 188 - 20, 40, 40, 255, 255, 0, 255);
				if (Ikaros.m_pCvars->bNameESP)
				{
					Ikaros.m_pDraw->Text(x + 603 + 28, y + 182, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Gabe Newell");
				}
				if (Ikaros.m_pCvars->bAimspotESP)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 2, y + 122 - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
					Ikaros.m_pDraw->FillRGBA(x + 603 - 1, y + 122 - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_BLACK));
				}
				if (Ikaros.m_pCvars->iHealthESP == 1)
				{
					Ikaros.m_pDraw->Text(x + 603 + 28, y + 194, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 2)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 28, y + 188 - 20, 5, 40, r, g, 0, 255);
					Ikaros.m_pDraw->FillRGBA(x + 603 - 28, y + 188 - 20, 5, 40 - (Health / 2.5), 0, 0, 0, 255);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 3)
				{
					Ikaros.m_pESP->DrawHeader(x + 603 - 19, y + 188 + 23, 39 + 2, 255, 255, 0, (Health / 2.5) - 2);
				}
			}
			else if (Ikaros.m_pCvars->i2DBox == 2)
			{
				ESPBox(x + 603 - 40, y + 188 - 90, 80, 180, 255, 255, 0, 255);
				if (Ikaros.m_pCvars->bNameESP)
				{
					Ikaros.m_pDraw->Text(x + 606 + 40, y + 188 - 15, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Gabe Newell");
				}
				if (Ikaros.m_pCvars->bAimspotESP)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 2, y + 122 - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
					Ikaros.m_pDraw->FillRGBA(x + 603 - 1, y + 122 - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_BLACK));
				}
				if (Ikaros.m_pCvars->iHealthESP == 1)
				{
					Ikaros.m_pDraw->Text(x + 606 + 40, y + 190 - 5, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 2)
				{
					float multi = 180 / 100;
					Ikaros.m_pDraw->FillRGBA(x + 563 - 8, y + 98, 5, 180, r, g, 0, 255);
					Ikaros.m_pDraw->FillRGBA(x + 563 - 8, y + 98, 5, 180 - (180 * ((float)Health / 100.0f)), 0, 0, 0, 255);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 3)
				{
					Ikaros.m_pESP->DrawHeader(x + 603 - 40 + 2, y + 278 + 3, 80, 255, 255, 0, (Health / (100 / 80)) - 2);
				}
			}
			else if (Ikaros.m_pCvars->i2DBox == 3)
			{
				int h = 180;
				int w = 12;

				//Left Up
				Ikaros.m_pDraw->FillRGBA(x + 563 - 1, y + 98 - 1, w, 3, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 563 - 1, y + 98 - 1, 3, w, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 563, y + 98, w - 2, 1, 255, 255, 0, 255);
				Ikaros.m_pDraw->FillRGBA(x + 563, y + 98, 1, w - 2, 255, 255, 0, 255);

				//Left Down
				Ikaros.m_pDraw->FillRGBA(x + 563 - 1, y + 280 - 4, w, 3, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 563 - 1, y + 280 - w - 2, 3, w, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 563, y + 280 - 3, w - 2, 1, 255, 255, 0, 255);
				Ikaros.m_pDraw->FillRGBA(x + 563, y + 280 - w - 1, 1, w - 2, 255, 255, 0, 255);

				//Right Up
				Ikaros.m_pDraw->FillRGBA(x + 643 - w, y + 98 - 1, w, 3, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 643 - 3, y + 98 - 1, 3, w, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 643 - w + 1, y + 98, w - 2, 1, 255, 255, 0, 255);
				Ikaros.m_pDraw->FillRGBA(x + 643 - 2, y + 98, 1, w - 2, 255, 255, 0, 255);

				//Right Down
				Ikaros.m_pDraw->FillRGBA(x + 643 - w, y + 280 - 4, w, 3, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 643 - 3, y + 280 - w - 2, 3, w, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
				Ikaros.m_pDraw->FillRGBA(x + 643 - w + 1, y + 280 - 3, w - 2, 1, 255, 255, 0, 255);
				Ikaros.m_pDraw->FillRGBA(x + 643 - 2, y + 280 - w - 1, 1, w - 2, 255, 255, 0, 255);

				if (Ikaros.m_pCvars->bNameESP)
				{
					Ikaros.m_pDraw->Text(x + 606 + 40, y + 188 - 15, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Gabe Newell");
				}
				if (Ikaros.m_pCvars->bAimspotESP)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 2, y + 122 - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
					Ikaros.m_pDraw->FillRGBA(x + 603 - 1, y + 122 - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_BLACK));
				}
				if (Ikaros.m_pCvars->iHealthESP == 1)
				{
					Ikaros.m_pDraw->Text(x + 606 + 40, y + 190 - 5, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 2)
				{
					float multi = 180 / 100;
					Ikaros.m_pDraw->FillRGBA(x + 563 - 8, y + 98, 5, 180, r, g, 0, 255);
					Ikaros.m_pDraw->FillRGBA(x + 563 - 8, y + 98, 5, 180 - (180 * (float)((float)Health / 100.0f)), 0, 0, 0, 255);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 3)
				{
					Ikaros.m_pESP->DrawHeader(x + 603 - 40 + 2, y + 278 + 3, 80, 255, 255, 0, (Health / (100 / 80)) - 2);
				}
			}
			else
			{
				if (Ikaros.m_pCvars->bNameESP)
				{
					Ikaros.m_pDraw->Text(x + 606, y + 182, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Gabe Newell");
				}
				if (Ikaros.m_pCvars->bAimspotESP)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 2, y + 122 - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
					Ikaros.m_pDraw->FillRGBA(x + 603 - 1, y + 122 - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_BLACK));
				}
				if (Ikaros.m_pCvars->iHealthESP == 1)
				{
					Ikaros.m_pDraw->Text(x + 606, y + 194, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), "Health : %i", Health);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 2)
				{
					Ikaros.m_pDraw->FillRGBA(x + 603 - 28, y + 188 - 20, 5, 40, r, g, 0, 255);
					Ikaros.m_pDraw->FillRGBA(x + 603 - 28, y + 188 - 20, 5, 40 - (Health / 2.5), 0, 0, 0, 255);
				}
				else if (Ikaros.m_pCvars->iHealthESP == 3)
				{
					Ikaros.m_pESP->DrawHeader(x + 603 - 19, y + 188 + 23, 39 + 2, 255, 255, 0, (Health / 2.5) - 2);
				}
			}
		}
	}
	else if (openTab.ActiveTab == tab4)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 166, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 635, 400, "");
		DrawCheckBox(x + 165, y + 60, "Active ", Ikaros.m_pCvars->bRadar2D, "Enables Radar.");
		DrawCheckBox(x + 165, y + 90, "Hide Radar Background ", Ikaros.m_pCvars->bRadarBG, "Draws only a crosshair as radar.");
		DrawCheckBox(x + 165, y + 120, "Enemy Only ", Ikaros.m_pCvars->bEnemyOnlyRadar, "Shows only enemy on the radar.");
		DrawCheckBox(x + 165, y + 150, "Show Names ", Ikaros.m_pCvars->bRadarName, "Shows names on the radar.");
	}
	else if (openTab.ActiveTab == tab5)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 211, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 635, 400, "");
		DrawCheckBox(x + 165, y + 60, "Active", Ikaros.m_pCvars->bAntiAim, "Enables Anti Aim(makes it harder to hit you with an aimbot).");
		DrawCheckBox(x + 165, y + 150, "Edge Anti Aim", Ikaros.m_pCvars->bEdgeAntiAim, "Rotates your model to look at a wall if you stand at a wall.");
		DrawCheckBox(x + 165, y + 180, "Aim At Targets", Ikaros.m_pCvars->bAimAtTargets, "Aims at the target to make it harder to hit you with an aimbot.");
		if (Ikaros.m_pCvars->iAntiAimTypeX == 2)
		{
			if (Ikaros.m_pCvars->iAntiAimTypeY == 2)
			{
				Slider(x + 165, y + 210, 0, Ikaros.m_pCvars->flAA_X, 0.0f, 360.0f, "X Axis", "Define the x(Pitch) axis of the anti aim.");
				Slider(x + 165, y + 240, 0, Ikaros.m_pCvars->flAA_Y, 0.0f, 360.0f, "Y Axis", "Define the y(Yaw) axis of the anti aim.");
			}
			else
			{
				Slider(x + 165, y + 210, 0, Ikaros.m_pCvars->flAA_X, 0.0f, 360.0f, "X Axis", "Define the x(Pitch) axis of the anti aim.");
			}
		}
		if (Ikaros.m_pCvars->iAntiAimTypeY == 2)
		{
			if (Ikaros.m_pCvars->iAntiAimTypeX == 2)
			{
				Slider(x + 165, y + 210, 0, Ikaros.m_pCvars->flAA_X, 0.0f, 360.0f, "X Axis", "Define the x(Pitch) axis of the anti aim.");
				Slider(x + 165, y + 240, 0, Ikaros.m_pCvars->flAA_Y, 0.0f, 360.0f, "Y Axis", "Define the y(Yaw) axis of the anti aim.");
			}
			else
			{
				Slider(x + 165, y + 210, 0, Ikaros.m_pCvars->flAA_Y, 0.0f, 360.0f, "Y Axis", "Define the y(Yaw) axis of the anti aim.");
			}
		}
		DrawComboBox(x + 165, y + 120, "Y", Ikaros.m_pCvars->iAntiAimTypeY, 17, 6, AntiAimY, "Select the anti aim y(Yaw) style.");
		DrawComboBox(x + 165, y + 90, "X", Ikaros.m_pCvars->iAntiAimTypeX, 9, 4, AntiAimX, "Select the anti aim x(Pitch) style.");
	}
	else if (openTab.ActiveTab == tab6)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 256, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 635, 400, "");
		DrawCheckBox(x + 165, y + 60, "Chams", Ikaros.m_pCvars->bChams, "Enables Chams(Colored Models).");
		DrawCheckBox(x + 165, y + 90, "Weapon Chams", Ikaros.m_pCvars->bWeaponChams, "Enables Weapon Chams(Colored Weapons).");
		DrawCheckBox(x + 165, y + 120, "XQZ Wallhack", Ikaros.m_pCvars->bXQZWalls, "Makes all players visible through walls.");
		DrawCheckBox(x + 165, y + 150, "Glass Chams", Ikaros.m_pCvars->bGlassChams, "Makes the Chams more transparent.");
		DrawCheckBox(x + 165, y + 180, "No Flash", Ikaros.m_pCvars->bNoFlash, "Disables the Flashbang Effect.");
		DrawCheckBox(x + 165, y + 210, "No Smoke", Ikaros.m_pCvars->bNoSmoke, "Disables the Smoke Effect from smoke granades.");
		DrawCheckBox(x + 485, y + 60, "No Hands", Ikaros.m_pCvars->bNoHands, "Removes Hands.");
		DrawCheckBox(x + 485, y + 90, "No Sky", Ikaros.m_pCvars->bNoSky, "Makes the sky black(to boost fps).");
		DrawCheckBox(x + 485, y + 120, "Fullbright", Ikaros.m_pCvars->bFullbright, "Enables full brightness.");
		DrawCheckBox(x + 485, y + 150, "Monitor", Ikaros.m_pCvars->bMonitorActive, "Enables a info monitor for recoil, speed and spread.");
		DrawCheckBox(x + 485, y + 180, "Watermark", Ikaros.m_pCvars->bWatermark, "Enables Watermark.");
		//DrawCheckBox(x + 20, y + 520, "Asus Walls", Ikaros.m_pCvars->bAsusWalls);
		//DrawFloatSlider("Asus Walls Alpha", x + 20, y + 560, 0.1, 1, Ikaros.m_pCvars->flAsusAlpha, 0.1);
		DrawComboBox(x + 485, y + 210, "Crosshair", Ikaros.m_pCvars->iCrosshair, 16, 4, Crosshair, "Choose a custom crosshair which is drawn over your normal crosshair.");
	}
	else if (openTab.ActiveTab == tab7)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 301, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 635, 400, "");
		DrawCheckBox(x + 165, y + 60, "Bunny Hop", Ikaros.m_pCvars->bBunnyHop, "Makes you jump continuously if you hold space.");
		DrawCheckBox(x + 165, y + 90, "Auto Pistol", Ikaros.m_pCvars->bAutoPistol, "Fires pistols like automatic rifles.");
		DrawCheckBox(x + 165, y + 120, "Speedhack", Ikaros.m_pCvars->bSpeed, "Enables Speedhack.");
		DrawCheckBox(x + 165, y + 150, "No Visual Recoil", Ikaros.m_pCvars->bNoVisRecoil, "Removes any visual recoil.");
		Slider(x + 165, y + 180, 1, Ikaros.m_pCvars->iSpeedVal, 1.0f, 10.0f, "Speed Value", "Choose how fast the speedhack is.");

		if (!Ikaros.m_pCvars->iAim)
		{
			DrawCheckBox(x + 165, y + 270, "Namestealer", Ikaros.m_pCvars->bNameStealer, "Steals the other players name.");
			DrawCheckBox(x + 165, y + 300, "Roundsay", Ikaros.m_pCvars->roundsay, "Advises the cheat.");
			DrawCheckBox(x + 485, y + 180, "Hit Sound", Ikaros.m_pCvars->bHitSound, "Plays a sound if you hit the enemy.");
			DrawCheckBox(x + 485, y + 210, "Flashlight Spam", Ikaros.m_pCvars->bFlashSpam, "Spams the flashlight command to make a annoying noise.");
			DrawComboBox(x + 485, y + 150, "No Shake No Spread", Ikaros.m_pCvars->iPNoSpread, 14, 3, Removals, "Removes spread without any visual shake.");
			DrawComboBox(x + 485, y + 120, "No Spread", Ikaros.m_pCvars->iNoSpread, 13, 3, Removals, "Removes spread with visual shakes.");
			DrawComboBox(x + 485, y + 90, "Recoil Control System", Ikaros.m_pCvars->iRCS, 12, 2, Removals, "Removes recoil in a controlled way(spraydown).");
		}
		else
		{
			DrawCheckBox(x + 165, y + 270, "Namestealer", Ikaros.m_pCvars->bNameStealer, "Steals the other players name.");
			DrawCheckBox(x + 165, y + 300, "Roundsay", Ikaros.m_pCvars->roundsay, "Advises the cheat.");
			DrawCheckBox(x + 165, y + 330, "Show Shaking", Ikaros.m_pCvars->bShowShake, "Shows you the shake of norecoil and nospread while aimboting.");
			DrawCheckBox(x + 485, y + 180, "Flashlight Spam", Ikaros.m_pCvars->bFlashSpam, "Spams the flashlight command to make a annoying noise.");
			DrawCheckBox(x + 485, y + 150, "Hit Sound", Ikaros.m_pCvars->bHitSound, "Plays a sound if you hit the enemy.");
			DrawComboBox(x + 485, y + 120, "No Shake No Spread", Ikaros.m_pCvars->iPNoSpread, 14, 3, Removals, "Removes spread without any visual shake.");
			DrawComboBox(x + 485, y + 90, "No Spread", Ikaros.m_pCvars->iNoSpread, 13, 3, Removals, "Removes spread with visual shakes for spectators.");
		}
		DrawComboBox(x + 485, y + 60, "No Recoil", Ikaros.m_pCvars->iNoRecoil, 11, 3, Removals, "Removes recoil with visual shakes for spectators.");
		DrawComboBox(x + 165, y + 240, "Auto Strafe", Ikaros.m_pCvars->iAutoStrafe, 18, 3, Strafe, "Enables strafe helper for gaining speed while bunnyhopping.");
		DrawComboBox(x + 165, y + 210, "Speedhack Key", Ikaros.m_pCvars->iSpeedKey, 10, 11, Keys, "Choose on which key the speedhack enables.");
	}
	else if (openTab.ActiveTab == tab8)
	{
		int x1 = x + 165;
		int y1 = y + 35;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 346, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		Ikaros.m_pCvars->bPlayerList = true;
		DrawGroupBox(x + 160, y + 30, 635, 400, "Players");
		DrawGroupBox(x + 165, y + 330, 625, 100, "Options");

		DrawCheckBox(x1 + 315, y1 + 325, "Manually Yaw Correction", Ikaros.m_pPlayerlist[Selection].bAdvancedYaw, "Enables manually Yaw(y axis) Correction.");
		if (Ikaros.m_pPlayerlist[Selection].bAdvancedYaw)
		{
			Slider(x1 + 315, y1 + 355, 1, Ikaros.m_pPlayerlist[Selection].iAdvancedYaw, 0, 360, "Yaw Correction", "Manually correct Yaw(y axis) for anti aim users with fake yaw.");
		}
		else
		{
			DrawComboBox(x1 + 315, y1 + 355, "Yaw Correction", Ikaros.m_pPlayerlist[Selection].iYaw, 20, 4, AAAYaw, "Correct Yaw(y axis) for anti aim users with fake yaw.");
		}
		DrawComboBox(x1, y1 + 355, "Pitch Correction", Ikaros.m_pPlayerlist[Selection].iPitch, 19, 4, AAAPitch, "Correct Pitch(x axis) for anti aim users with fake pitch or 'magic' pitch.");
		DrawCheckBox(x1, y1 + 325, "Friend", Ikaros.m_pPlayerlist[Selection].bFriend, "Makes the esp on the player white and aimbot, triggerbot won't kill him.");

		if (iSel > 0)
		{
			Ikaros.m_pDraw->FillRGBA(x1, y1 + 16 + (iSel * 13), 625, 12, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));//highlight selection
		}
	}
	else if (openTab.ActiveTab == tab9)
	{
		Ikaros.m_pCvars->bPlayerList = false;
		Ikaros.m_pDraw->FillRGBA(x + 141, y + 391, 10, 35, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor));
		DrawGroupBox(x + 160, y + 30, 635, 400, "");
		/*Ikaros.m_pDraw->Text(x + 160, y + 30, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Credits(i haz dem):");
		Ikaros.m_pDraw->Text(x + 160, y + 50, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " Kamay");
		Ikaros.m_pDraw->Text(x + 160, y + 70, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " KeyBode");
		Ikaros.m_pDraw->Text(x + 160, y + 90, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " MattDog");
		Ikaros.m_pDraw->Text(x + 160, y + 110, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " me(n0xius)");
		Ikaros.m_pDraw->Text(x + 160, y + 130, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " InUrFace");
		Ikaros.m_pDraw->Text(x + 160, y + 150, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " royalhack.ru");
		Ikaros.m_pDraw->Text(x + 160, y + 170, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " game-deception.com(P47R!CK, Tetsuo, Darawk, Dom1n1k, PizzaPan, Panzer, s0beit, [myg0t]wav, etc..)");
		Ikaros.m_pDraw->Text(x + 160, y + 190, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Greets:");
		Ikaros.m_pDraw->Text(x + 160, y + 210, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " BH4X0R");
		Ikaros.m_pDraw->Text(x + 160, y + 230, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " Kamay");
		Ikaros.m_pDraw->Text(x + 160, y + 250, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " KeyBode");
		Ikaros.m_pDraw->Text(x + 160, y + 270, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " MattDog");
		Ikaros.m_pDraw->Text(x + 160, y + 290, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " gopnix");
		Ikaros.m_pDraw->Text(x + 160, y + 310, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), " maximum1441");*/
	}
}

bool bWarning = true;

void DrawWarning(int x, int y, int w, int h)
{
	Ikaros.m_pMenu->DrawWindow(x - (w / 2), y - (h / 2), w, h, "Warning");
	Ikaros.m_pDraw->Text(x - (w / 2) + 10, y - (h / 2) + 30, 255, 255, 255, 255, "CL_Move Signature Scan failed.");
	Ikaros.m_pDraw->Text(x - (w / 2) + 10, y - (h / 2) + 43, 255, 255, 255, 255, "Disabled Features: Perfect Silent Aim, Fake Pitch/Yaw, Speedhack.");
	Ikaros.m_pDraw->FillRGBA(x - (w / 2) + ((w / 2) - 22), y - (h / 2) + ((h / 2) + 25), 45, 20, RED(Grey2), GREEN(Grey2), BLUE(Grey2), ALPHA(Grey2));

	if (Ikaros.m_pMouse->IsInBox(x - (w / 2) + ((w / 2) - 22), y - (h / 2) + ((h / 2) + 25), 45, 20))
	{
		Ikaros.m_pDraw->FillRGBA(x - (w / 2) + ((w / 2) - 22), y - (h / 2) + ((h / 2) + 25), 45, 20, RED(Grey3), GREEN(Grey3), BLUE(Grey3), ALPHA(Grey3));
		if (Ikaros.m_pMouse->bMouse1pressed)
			bWarning = false;
	}

	Ikaros.m_pDraw->Border(x - (w / 2) + ((w / 2) - 22), y - (h / 2) + ((h / 2) + 25), 45, 20, 1, 0, 0, 0, 255);
	Ikaros.m_pDraw->Text(x - (w / 2) + ((w / 2) - 10), y - (h / 2) + ((h / 2) + 28), 255, 255, 255, 255, "OK");
}

void CMenu::DrawMenu()
{
	DO_ONCE(openTab.ActiveTab = tab1;);

	if (bLock)
	{
		bClick = false;
	}
	else
	{
		bClick = true;
	}

	ConVar* mouseenable = Ikaros.m_pCvar->FindVar("cl_mouseenable");

	if (GetAsyncKeyState(VK_F12) & 1)
	{
		Ikaros.m_pCvars->bPanicKey = !Ikaros.m_pCvars->bPanicKey;
	}

	if (!Ikaros.m_pCvars->bPanicKey)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Ikaros.m_pCvars->bShowGUI = !Ikaros.m_pCvars->bShowGUI;
			//if (!Ikaros.m_pCvars->bShowGUI && !Ikaros.m_pCvars->bPanicKey)
			//Save();
			if (Ikaros.m_pCvars->bShowGUI)
				CloseAllComboBoxes();
		}

		Ikaros.m_pRadar->DrawRadar();

		if (Ikaros.m_pEngine->IsConnected()
			&& Ikaros.m_pEngine->IsInGame()
			&& Ikaros.m_pMyPlayer->BaseEnt()
			&& !Ikaros.m_pEngine->IsTakingScreenshot()
			&& !Ikaros.m_pEngine->IsLevelMainMenuBackground())
		{
			Ikaros.m_pESP->DrawEsp();
			//Ikaros.m_pDraw->Text(2, 20, 255, 255, 255, 255, "flDistance: %f", flDistance);
			//Ikaros.m_pDraw->Text(2, 30, 255, 255, 255, 255, "flRangeModifier: %f", flRangeModifier);
			//Ikaros.m_pDraw->Text(2, 40, 255, 255, 255, 255, "iBulletType: %i", iBulletType);
			//Ikaros.m_pDraw->Text(2, 50, 255, 255, 255, 255, "iPenetration: %i", iPenetration);
		}

		Ikaros.m_pESP->CrossHair();

		if (Ikaros.m_pCvars->bMonitorActive)
			DrawMonitor(Ikaros.m_pCvars->iMonitorPosX, Ikaros.m_pCvars->iMonitorPosY);

		if (Ikaros.m_pCvars->bWatermark)
			Ikaros.m_pDraw->Text(2, 2, 255, 255, 255, 255, "Ikaros Recode"); 

		if (Ikaros.m_pCvars->bShowGUI)
		{
			if (!bMouseOnce)
			{
				mouseenable->SetValue(0);
				bMouseOnce = true;
			}

			GetCursorPos(&Mouse);
			LPPOINT penis = &Mouse;
			ScreenToClient(GetForegroundWindow(), penis);

			Mouse.x = penis->x;
			Mouse.y = penis->y;
			Ikaros.m_pCvars->iMouseX = Mouse.x;
			Ikaros.m_pCvars->iMouseY = Mouse.y;
			
			DrawMainFrame(Ikaros.m_pCvars->iMenuX, Ikaros.m_pCvars->iMenuY);
		}

		DrawPlayerList();

		if (Ikaros.m_pCvars->bShowGUI)
		{
			if (Ikaros.m_pCvars->bSigFail)
				if (bWarning)
					DrawWarning(sScreenSize.m_iWidth / 2, sScreenSize.m_iHeight / 2, 350, 100);

			if (Ikaros.m_pMouse->IsInBox(Ikaros.m_pCvars->iMenuX, Ikaros.m_pCvars->iMenuY, 802, 28) && Ikaros.m_pMouse->bMouse1pressed)
			{
				if (!bSavePos)
				{
					SavedX = Ikaros.m_pCvars->iMouseX - Ikaros.m_pCvars->iMenuX;
					SavedY = Ikaros.m_pCvars->iMouseY - Ikaros.m_pCvars->iMenuY;
					bSavePos = true;
				}
				Ikaros.m_pCvars->iMenuX = Ikaros.m_pCvars->iMouseX;
				Ikaros.m_pCvars->iMenuY = Ikaros.m_pCvars->iMouseY;
				Ikaros.m_pCvars->iMenuX = Ikaros.m_pCvars->iMenuX - SavedX;
				Ikaros.m_pCvars->iMenuY = Ikaros.m_pCvars->iMenuY - SavedY;
			}
			else
			{
				bSavePos = false;
			}

			Ikaros.m_pMouse->ClickHandler();
			DrawMouse(Ikaros.m_pCvars->iMouseX, Ikaros.m_pCvars->iMouseY);
		}
		else
		{
			if (bMouseOnce)
			{
				mouseenable->SetValue(1);
				bMouseOnce = false;
			}
		}
	}
	else
	{
		Ikaros.m_pCvars->bShowGUI = false;
	}
}