#include <fstream>
#include <sstream>

#include <windows.h>

#include "wintab.h"
#define PACKETDATA	(PK_X | PK_Y | PK_BUTTONS | PK_NORMAL_PRESSURE)
#define PACKETMODE	PK_BUTTONS
#include "pktdef.h"
#include "utils.h"

#define LOG(message) \
	g_fout.open("FREPenTablet.log", fstream::app); \
	g_fout << message << endl; \
	g_fout.close();

using namespace std;

fstream g_fout;

HWND g_hwnd = NULL;
HINSTANCE g_hInstance = NULL;

unsigned int g_currentPressure = 0;
unsigned int g_currentX = 0;
unsigned int g_currentY = 0;

HCTX CreateTabletContext(HWND hWnd)
{
	LOGCONTEXT lcMine;

	gpWTInfoA(WTI_DEFCONTEXT, 0, &lcMine);

	wsprintf(lcMine.lcName, "FREPenTablet:%x", g_hInstance);
	lcMine.lcOptions |= CXO_SYSTEM;
	lcMine.lcOptions |= CXO_MESSAGES;
	lcMine.lcPktData = PACKETDATA;
	lcMine.lcPktMode = PACKETMODE;
	lcMine.lcMoveMask = PACKETDATA;
	lcMine.lcBtnUpMask = lcMine.lcBtnDnMask;

	lcMine.lcOutOrgX = lcMine.lcOutOrgY = 0;
	lcMine.lcOutExtX = 10000;
	lcMine.lcOutExtY = 10000;

	return gpWTOpenA(hWnd, &lcMine, TRUE);
}

LRESULT FAR PASCAL WndProc(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam)
{
	static HCTX hctx = NULL;
	PACKET pkt;

	switch(message)
	{
		case WM_CREATE:
			hctx = CreateTabletContext(hWnd);
			if(!hctx) 
			{
				LOG("Could not open tablet context");
				SendMessage(hWnd, WM_DESTROY, 0, 0L);
			}
			break;

		case WT_PACKET:
			if(gpWTPacket((HCTX)lParam, wParam, &pkt)) 
			{
				g_currentX = pkt.pkX;
				g_currentY = pkt.pkY;
				g_currentPressure = pkt.pkNormalPressure;
			}
			break;

		case WM_DESTROY:
			if(hctx)
			{
				gpWTClose(hctx);
				LOG("Tablet context closed");
			}
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL CreateAppWindow()
{
	WNDCLASS  wc;

	wc.style = 0;
	wc.lpfnWndProc = WndProc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wc.lpszMenuName =  "FREPenTabletMenu";
	wc.lpszClassName = "FREPenTabletClass";

	if(RegisterClass(&wc))
	{
		HWND hWnd;

		if(LoadWintab())
		{
			if(gpWTInfoA(0, 0, NULL)) 
			{
				char title[50];
				wsprintf(title, "FREPenTablet:%x", g_hInstance);

				hWnd = CreateWindow("FREPenTabletClass", title, WS_DISABLED,
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					HWND_MESSAGE, NULL, g_hInstance, NULL);

				if(hWnd)
				{
					return TRUE;
				}
				LOG("Window could not be created");
				return FALSE;
			}
			LOG("Wintab services not available");
			return FALSE;
		}
		LOG("Wintab not available");
		return FALSE;
	}
	LOG("Unable to register window class");
	return FALSE;
}

DWORD WINAPI CreateAppThread()
{
	LOG("CreateAppThread called");

	if(CreateAppWindow())
	{
		MSG msg;

		while(GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return TRUE;
	}

	LOG("Unable to create window");
	return FALSE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID lpvReserved)
{
	LOG("DllMain called: " << reason);

	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
			g_hInstance = hInstance;

			HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateAppThread, (LPVOID)NULL, 0, NULL);

			LOG("CreateThread result:" << thread);

			break;
	}

	return TRUE;
}