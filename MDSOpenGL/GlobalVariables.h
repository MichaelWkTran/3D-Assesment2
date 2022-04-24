#pragma once
#include <GLFW/glfw3.h>

//Window
extern unsigned int uViewPortW, uViewPortH;

//Time
extern float fPreviousTimestep;
extern float fDeltatime;

//Input
extern int iKey;
extern int iScanCode;
extern int iAction;
extern int iMods;
extern bool bKeyPressed;

void KeyFunction(GLFWwindow* _pWindow, int _iKey, int _iScanCode, int _iAction, int _iMods);
void UpdateKeyPressed();