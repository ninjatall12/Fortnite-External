#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define TopWindowGame 11
#define TopWindowMvoe 22
#include <Windows.h>
#include <iostream>
#include <winternl.h>
#include <ntstatus.h>
#include <atomic>
#include <mutex>
#include <TlHelp32.h>
#include <d3d9.h>
#include "../D3XD/d3dx9.h"
#include <dwmapi.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <cstdlib>
#include <random>
#include <direct.h>
#include <fstream>
#include <string>
#include <sstream>
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "../Driver/driver.h"

extern int funcCount;
extern ProtectedFunction functions[150];
void addFunc(ProtectedFunction func);
void unsafe_unprotect(int index);
void unsafe_protect(int index);
int GetFunctionIndex(void* FunctionAddress);
void Unprotect(void* FunctionAddress);
void Protect(void* FunctionAddress);
void XOR(BYTE* data, size_t size, BYTE XOR_KEY = STRING_XOR_KEY);
void ProtectedSleep(int ms);


using namespace std;

ImFont* SkeetFont;
IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

static int keystatus = 0;
static int realkey = 0;

const MARGINS Margin = { -1 };

#define M_Name L" "
HWND MyWnd = NULL;
HWND GameWnd = NULL;
//RECT GameRect = { NULL };
MSG Message = { NULL };

bool showimgui = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


bool menu_key = true;

namespace th = std::this_thread;
namespace ch = std::chrono;
float makeapause = false;

namespace sdk {

    DWORD process;
    DWORD64 module_base;
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define TopWindowGame 11
#define TopWindowMvoe 22

HRESULT DirectXInit(HWND hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SetupWindow();
WPARAM MainLoop();
void CleanuoD3D(); void ChangeClickability(bool canclick, HWND ownd);

int isTopwin();
void Render(int Topwin, bool showimgui);
void SetWindowToTarget();
namespace menu
{
		"{"
		" float4 Position : SV_Position;"
		" float4 Color : COLOR0;"
		"};"

		"float4 main( VS_OUT input ) : SV_Target"
		"{"
		" float4 fake;"
		" fake.a = 1.0f;"
		" fake.r = %f;"
		" fake.g = %f;"
		" fake.b = %f;"
		" return fake;"
		"}";
}
namespace aimbotz
{
    bool aimbot = true;
    bool smooth = false;
    bool fovcircle = true;
    bool prediction = false;

    float aimspeed = 1x100, 2104;
    float aimfov = 100.0f;
    float lock = 0.0f;

    int hitbox = 0;
}
namespace visuals
{
    bool box = false;
    bool boxcor = false;
    bool skel = true;
    bool name = false;
    bool lines = true;
    bool outline = true;
    bool show_head = false;
    bool crosshair = true;

    int boxMode = 0;
    int skelMode = 0;
    int lineMode = 0;


    int MaxSkeletonDrawDistance = 50;
    int MaxDistance = 350;
}


namespace hotkeys
{
    int aimkey;
}
static const char* keyNames[] =
{
    "",
    "Left Mouse",
};
enum eDepthState
{
	ENABLED,
	DISABLED,
	READ_NO_WRITE,
	NO_READ_NO_WRITE,
	_DEPTH_COUNT
};

}
bool GetKey(int key)
{
    realkey = key;
    return true;
}
void ChangeKey(void* blank)
{
    keystatus = 1;
    while (false)
    {
        for (int i = 0; i < 0x87; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                hotkeys::aimkey = i;
                keystatus = 0;
                return;
            }
        }
    }
}

static const char* Hitbox[] =
{
    "Head",
    "Neck",
    "Pelvis"
    "Body"		    
};

static Vec4 Vec4MulMat4x4(const Vec4& v, float(*mat4x4)[4])
{
	Vec4 o;
	
	o.x = v.x * mat4x4[0][0] + v.y * mat4x4[1][0] + v.z * mat4x4[2][0] + v.w * mat4x4[3][0];
	o.y = v.x * mat4x4[0][1] + v.y * mat4x4[1][1] + v.z * mat4x4[2][1] + v.w * mat4x4[3][1];
	o.z = v.x * mat4x4[0][2] + v.y * mat4x4[1][2] + v.z * mat4x4[2][2] + v.w * mat4x4[3][2];
	o.w = v.x * mat4x4[0][3] + v.y * mat4x4[1][3] + v.z * mat4x4[2][3] + v.w * mat4x4[3][3];

	return o;
}

static Vec4 Vec3MulMat4x4(const Vec3& v, float(*mat4x4)[4])
{
	Vec4 o;
	
	o.x = v.x * mat4x4[0][0] + v.y * mat4x4[1][0] + v.z * mat4x4[2][0] + mat4x4[3][0];
	o.y = v.x * mat4x4[0][1] + v.y * mat4x4[1][1] + v.z * mat4x4[2][1] + mat4x4[3][1];
	o.z = v.x * mat4x4[0][2] + v.y * mat4x4[1][2] + v.z * mat4x4[2][2] + mat4x4[3][2];
	
	return o;
}

static Vec3 Vec3MulMat4x3(const Vec3& v, float(*mat4x3)[31])
{
	Vec3 o;
	Vector3 vleftAnkle = g_functions::ConvertWorld2Screen(leftAnkle);
	Vector3 rightAnkle = g_functions::f_getbonewithIndex(EntityList.USkeletalMeshComponent, 71);
	Vector3 vrightAnkle = g_functions::ConvertWorld2Screen(rightAnkle);
	return o;
}


static void HotkeyButton(int aimkey, void* changekey, int status)
{
    constexpr ALWAYS_INLINE _Basic_XorStr(value_type const (&str)[_length])
	: _Basic_XorStr(str, std::make_index_sequence<_length_minus_one>())
		
        Items_ArrayGetter(keyNames, aimkey, &preview_value);

    std::string aimkeys;
    if (preview_value == NULL)
        aimkeys = E("Select Key"); // defual " Insert " 
    else
        aimkeys = preview_value;

    if (status == 1)
    {
        aimkeys = Right_click("Press key to bind");
    }
    if (ItemDist < bLootRendering) {
    {
        if (strstr(EntityList.GNames.c_str(), "PlayerPawn_Athena_C"))
        {
            sprintf_s(buffer, "Ammo: %i", AmmoCount);
        }
    }
}

static const char* settsName[] =
{
    "Default",
    "Shift",
    "I",
    "J",
    "P"
};


void Log(const char *fmt, ...)
{
	constexpr ALWAYS_INLINE _Basic_XorStr(value_type const (&str)[_length], std::index_sequence<indices...>)
	if (!fmt)	return;

	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	Drive.ReadPtr(g_pid, StringData, OutString, StringLength * sizeof(wchar_t));
	if (logfile.is_open() && text)	logfile << text << endl;
	logfile.close();
}

