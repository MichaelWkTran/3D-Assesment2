#pragma once
#include "GlobalVariables.h"
//#include <GLFW/glfw3.h>

//Window
extern unsigned int uViewPortW = 800, uViewPortH = 800;

//Time
float fPreviousTimestep = 0.0f;
float fDeltatime = 0.0f;

//Input
int iKey = 0;
int iScanCode = 0;
int iAction = 0;
int iMods = 0;
bool bKeyPressed = false;

void KeyFunction(GLFWwindow* _pWindow, int _iKey, int _iScanCode, int _iAction, int _iMods)
{
	iKey = _iKey;
	iScanCode = _iScanCode;
	iAction = _iAction;
	iMods = _iMods;
}

void UpdateKeyPressed()
{
    if (iAction == GLFW_RELEASE)
		bKeyPressed = false;
    else
		bKeyPressed = true;
}