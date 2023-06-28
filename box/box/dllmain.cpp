// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <atomic>

using namespace std;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

class box {
    private:
        double length;
        double breadth;
        double height;
    public:
        box(double len, double brth, double hgt);
        ~box();
        double calArea();
        double calVolume();
};

extern "C" __declspec(dllexport) int __cdecl dll_newBox(box * *p_box, double length, double breadth, double hgt);
extern "C" __declspec(dllexport) int __cdecl dll_freeBox(box * *p_box);
extern "C" __declspec(dllexport) int __cdecl dll_calArea(box * *p_box, double* area);
extern "C" __declspec(dllexport) int __cdecl dll_calVolume(box * *p_box, double* volume);

box::box(double l = 1, double b = 1, double h = 1) {
    length = l; breadth = b; height = h;
}

box::~box() {}

double box::calArea() {
    return length * breadth;
}

double box::calVolume() {
    return length * breadth * height;
}

__declspec(dllexport) int __cdecl dll_newBox(box** p_box, double length, double breadth, double height)
{
    *p_box = new box(length, breadth, height);
    return 0;
}

__declspec(dllexport) int __cdecl dll_freeBox(box** p_box)
{
    delete* p_box;
    return 0;
}

__declspec(dllexport) int __cdecl dll_calArea(box** p_box, double* area)
{
    *area = (*p_box)->calArea();
    return 0;
}

__declspec(dllexport) int __cdecl dll_calVolume(box** p_box, double* volume)
{
    *volume = (*p_box)->calVolume();
    return 0;
}