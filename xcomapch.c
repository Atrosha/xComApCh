#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>


#define IDB_OPEN		1
#define IDB_SAVE		40
#define IDB_MAXBASE		31
#define IDB_MAXCASH		34
#define IDB_MAXPERS		32
#define IDB_CUREPERS	33

#define IDL_GAMENAME	11
#define IDL_GAMETIME	12
#define IDL_GAMECASH	13



// GLOBAL VARIABLES AND CONSTANTS
#define LOC_CASH 0x33D40
#define LOC_PERS 0x20D6A
#define LOC_BASE 0x1DF6A

static OPENFILENAME ofn;
char szFile[_MAX_PATH];
char szTitle[_MAX_FNAME + _MAX_EXT];
long int savegamecash;
char savegametime[40];
char savegamename[40];
int numpers = 0;
int numbase = 0;

struct tBase
	{
	char buf1[2];
	char Name[19];
	unsigned char Marker;
	unsigned char Structures[8][8];
	char buf2[616];
} base[8];

struct tPersonal
	{
	char Name[26];
	short int Index;
	char buf01[7];
	unsigned char Type; // 0 - Agent, 1 - Chemist, 2 - Engineer, 3 - Physic
	char buf2[10];

	unsigned char BSpeed;
	unsigned char BHealth;
	unsigned char BStamina; // divide by 2
	unsigned char BReaction;
	unsigned char BStrength;
	unsigned char BBravery; // multiply by 10
	unsigned char BAccuracy; // 100 - x
	unsigned char BPsiEnergy;
	unsigned char BPsiAttack;
	unsigned char BPsiDefence;

	char buf3[2];

	unsigned char TSpeed;
	unsigned char THealth;
	unsigned char CHealth; // current health - wounded, etc
	char buf4[1];
	unsigned char TStamina; // divide by 2
	unsigned char TReaction;
	unsigned char TStrength;
	unsigned char TBravery; // multiply 10
	unsigned char TPsiEnergy;
	unsigned char TPsiAttack;
	unsigned char TPsiDefence;
	char buf5[1];
	unsigned char TAccuracy; // 100 - x

	char buf6[2];

	unsigned char SkillBiochemist;
	unsigned char SkillPhysic;
	unsigned char SkillEngineer;

	char buf7[129];
} pers[180];


void FileInitialize(HWND hwnd)
    {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = hwnd;
	ofn.lpstrFilter       = "SaveGame Files (SAVEGAME.*)\0SAVEGAME.*\0"  \
							"All Files (*.*)\0*.*\0\0";
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFile[0]	  = '\0';
	ofn.nMaxFile          = _MAX_PATH;
	ofn.lpstrFileTitle    = szTitle;
	ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir   = NULL;
	}

BOOL FileOpenDlg(HWND hwnd)
	{
    ofn.hwndOwner         = hwnd;
	ofn.Flags             = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	return GetOpenFileName(&ofn);
	}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     PSTR szCmdLine, int iCmdShow)
	{
	static char  szAppName[] = "XCOMApCh";
	HWND         hwnd;
	MSG          msg;
	WNDCLASSEX   wndclass;
	wndclass.cbSize        = sizeof(wndclass);
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground =(HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
						szAppName,
						"XCOMAPOC Cheat",
						WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						325,
						310,
						NULL,
						NULL,
						hInstance,
						NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	return msg.wParam;
	}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
	static HWND hwndButtonOpen,
				hwndButtonSave,
				hwndButtonMaxCash,
				hwndButtonMaxBases,
				hwndButtonMaxPersonel,
				hwndButtonCurePersonel;
	static HWND hwndStatusBar;
	static HWND hwndLabelGameName,
				hwndLabelGameTime,
				hwndLabelNumEditSt;

	void ReadFile()
		{
		FILE *datafile;
		char pszMem[200];

		if ((datafile = fopen(szFile, "rb")) != NULL) { // file opens?
			fseek(datafile, 0, SEEK_SET);
			fread(&savegametime, sizeof(savegametime), 1, datafile);
			fread(&savegamename, sizeof(savegamename), 1, datafile);

			SetWindowText(hwndLabelGameName, savegamename);
			SetWindowText(hwndLabelGameTime, savegametime);

			fseek(datafile, LOC_CASH, SEEK_SET);
			fread(&savegamecash, sizeof(savegamecash), 1, datafile);
			
		
			itoa(savegamecash,  pszMem, 10);
			SetWindowText(hwndButtonMaxCash, pszMem);
			EnableWindow(hwndButtonMaxCash, TRUE);
			EnableWindow(hwndButtonSave, TRUE);
		
			fseek(datafile, LOC_BASE, SEEK_SET);
				for (int i = 0; i < 8; i++) {
					fread(&base[i], sizeof(base[0]), 1, datafile);
					if (base[i].Marker > 0) { numbase++; };
				};

			fseek(datafile, LOC_PERS, SEEK_SET);
				for (int i = 0; i < 180; i++) {
					fread(&pers[i], sizeof(pers[0]), 1, datafile);
					if (pers[i].Index > 0) { numpers++; };
				};

			if (numbase > 0) {
				EnableWindow(hwndButtonMaxBases, TRUE);
				}
			else MessageBox(hwnd, "No Bases (Maybe error occured)", "Information", MB_OK | MB_ICONINFORMATION);

			if (numpers > 0) {
				EnableWindow(hwndButtonMaxPersonel, TRUE);
				EnableWindow(hwndButtonCurePersonel, TRUE);
				}
			else MessageBox(hwnd, "No personal (Agents, Scientists, Engineers)", "Information", MB_OK | MB_ICONINFORMATION);
		}
		else MessageBox(hwnd, strerror(errno), "Error while opening file", MB_OK | MB_ICONERROR);

		fclose(datafile);
		}
	
	void FileSave()
		{
		FILE *datafile;
		
		if ((datafile = fopen(szFile, "r+b")) != NULL) { // file opens?
			fseek(datafile, LOC_CASH, SEEK_SET);
			fwrite(&savegamecash, sizeof(savegamecash), 1, datafile);
			fseek(datafile, LOC_PERS, SEEK_SET);
			for (int i = 0; i < 180; i++) {
				fwrite(&pers[i], sizeof(pers[0]), 1, datafile);
			};
			fseek(datafile, LOC_BASE, SEEK_SET);
			for (int i = 0; i < 8; i++) {
				fwrite(&base[i], sizeof(base[0]), 1, datafile);
			};
		}
		else MessageBox(hwnd, strerror(errno), "Error while opening file", MB_OK | MB_ICONERROR);
	
		fclose(datafile);
		MessageBox(hwnd, "Changes Saved to File", "Information", MB_OK | MB_ICONINFORMATION);
		}

	void MaxPers()
		{
		for (int i = 0; i <= numpers; i++) {
			switch (pers[i].Type) {
			case 0:
				pers[i].TSpeed = 100;
				pers[i].THealth = 100;
				pers[i].CHealth = pers[i].THealth;
				pers[i].TStamina = 200;
				pers[i].TReaction = 100;
				pers[i].TStrength = 100;
				pers[i].TBravery = 10;
				if (pers[i].BPsiEnergy > 0) { pers[i].TPsiEnergy = 100; };
				if (pers[i].BPsiAttack > 0) { pers[i].TPsiAttack = 100; };
				pers[i].TPsiDefence = 100;
				pers[i].TAccuracy = 0;
				break;
			case 1:
				pers[i].SkillBiochemist = 255;
				break;
			case 2:
				pers[i].SkillEngineer = 255;
				break;
			case 3:
				pers[i].SkillPhysic = 255;
				break;
				}
		}
		EnableWindow(hwndButtonMaxPersonel, FALSE);
		EnableWindow(hwndButtonCurePersonel, FALSE);
		}

	void CurePers()
		{
		for (int i = 0; i <= numpers; i++) { pers[i].CHealth = pers[i].THealth; };
		EnableWindow(hwndButtonCurePersonel, FALSE);
		}

	void MaxBase()
		{
		for (int c = 0; c < numbase; c++) {
			for (int y = 1; y < 7; y++) {
				for (int x = 1; x < 7; x++) {
					if (base[c].Structures[y][x] < 15) { base[c].Structures[y][x] = 15; };
				};
			};
			for (int x = 1; x < 7; x++) {
				if (base[c].Structures[0][x] < 16) { base[c].Structures[0][x] = 14; };
				if (base[c].Structures[7][x] < 16) { base[c].Structures[7][x] = 11; };
			};
			for (int y = 1; y < 7; y++) {
				if (base[c].Structures[y][0] < 16) { base[c].Structures[y][0] = 7; };
				if (base[c].Structures[y][7] < 16) { base[c].Structures[y][7] = 13; };
			};

			if (base[c].Structures[0][0] < 16) { base[c].Structures[0][0] = 6; };
			if (base[c].Structures[0][7] < 16) { base[c].Structures[0][7] = 12; };
			if (base[c].Structures[7][0] < 16) { base[c].Structures[7][0] = 3; };
			if (base[c].Structures[7][7] < 16) { base[c].Structures[7][7] = 9; };
		};
		EnableWindow(hwndButtonMaxBases, FALSE);
		}

	void MaxCash()
		{
		char pszMem[200];

		savegamecash = 999999999;
		itoa(savegamecash,  pszMem, 10);
		SetWindowText(hwndButtonMaxCash, pszMem);
		EnableWindow(hwndButtonMaxCash, FALSE);
		}

    switch(iMsg)
		{
		case WM_CREATE :
			hwndStatusBar = CreateWindowEx(
						0,                       // no extended styles
						STATUSCLASSNAME,         // name of status bar class
						"Copyright 2020 Vasiliy 'Atrosha' Panasenko",
						WS_CHILD | WS_VISIBLE,   // creates a visible child window
						0, 0, 0, 0,              // ignores size and position
						hwnd,              // handle to parent window
						(HMENU) 0,       // child window identifier
						((LPCREATESTRUCT) lParam) -> hInstance, NULL);


			hwndButtonOpen = CreateWindow("BUTTON", "Open SAVEGAME file...",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				10, 10,
				300, 25,
				hwnd, (HMENU) IDB_OPEN,
				((LPCREATESTRUCT) lParam) -> hInstance, NULL);

			hwndLabelGameName = CreateWindow("static", "",
                                      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      10, 40,
									  300, 25,
                                      hwnd, (HMENU) IDL_GAMENAME,
                                      ((LPCREATESTRUCT) lParam) -> hInstance, NULL);

			hwndLabelGameTime = CreateWindow("static", "",
                                      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      10, 60,
									  300, 25,
                                      hwnd, (HMENU) IDL_GAMETIME,
                                      ((LPCREATESTRUCT) lParam) -> hInstance, NULL);

			hwndLabelNumEditSt = CreateWindow("static", "",
                                      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      10, 90,
									  100, 25,
                                      hwnd, (HMENU) IDL_GAMECASH,
                                      ((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			SetWindowText(hwndLabelNumEditSt, "Money:");
				
			hwndButtonMaxCash = CreateWindow("BUTTON", "Maximise Money",
								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				85, 85,
                225, 25,
                hwnd, (HMENU) IDB_MAXCASH,
                ((LPCREATESTRUCT) lParam) -> hInstance, NULL);

			hwndButtonMaxBases = CreateWindow("BUTTON", "Maximise Bases",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 115,
			300, 25,
			hwnd,(HMENU) IDB_MAXBASE,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			hwndButtonMaxPersonel = CreateWindow("BUTTON", "Maximise Personel",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 145,
			300, 24,
			hwnd,(HMENU) IDB_MAXPERS,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			hwndButtonCurePersonel = CreateWindow("BUTTON", "Cure all Personel",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 175,
			300, 24,
			hwnd,(HMENU) IDB_CUREPERS,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			hwndButtonSave = CreateWindow("BUTTON", "Save changes",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 220,
			300, 24,
			hwnd,(HMENU) IDB_SAVE,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			EnableWindow(hwndButtonMaxCash, FALSE);
			EnableWindow(hwndButtonSave, FALSE);
			EnableWindow(hwndButtonMaxBases, FALSE);
			EnableWindow(hwndButtonMaxPersonel, FALSE);
			EnableWindow(hwndButtonCurePersonel, FALSE);
			FileInitialize(hwnd);
			return 0;
		
		case WM_COMMAND :

			switch(LOWORD(wParam)) {

				case IDB_OPEN :
					if (!FileOpenDlg(hwnd)) {
						MessageBox(hwnd, strerror(errno), "Can't open file", MB_OK | MB_ICONERROR);
						return errno;
						}
					ReadFile();
					break;

				case IDB_SAVE :
					FileSave();
					break;

				case IDB_MAXBASE :
					MaxBase();
					break;

				case IDB_MAXPERS :
					MaxPers();
					break;

				case IDB_CUREPERS :
					CurePers();
					break;

				case IDB_MAXCASH :
					MaxCash();
					break;
			}
			return 0;
		
		case WM_DESTROY :
			PostQuitMessage(0);
			return 0; 
		}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}