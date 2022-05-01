#include "ExternVariables.h"

//Window
extern unsigned int uViewPortW = 800, uViewPortH = 800;

//Time
float fPreviousTimestep = 0.0f;
float fDeltatime = 0.0f;

//Input
int iKey = 0;
int iKeyScanCode = 0;
int iKeyAction = 0;
int iKeyMods = 0;
bool bKeyPressed = false;
char charCodePoint = 0;
bool bCodePointFound = false;

glm::vec2 v2MousePosition;
int iMouseButton = 0;
int iMouseAction = 0;
int iMouseMods = 0;
bool bMousePressed = false;

bool bTextInputEnabled = false;

void KeyFunction(GLFWwindow* _pWindow, int _iKey, int _iScanCode, int _iAction, int _iMods)
{
	iKey = _iKey;
	iKeyScanCode = _iScanCode;
	iKeyAction = _iAction;
	iKeyMods = _iMods;
}

void UpdateMousePosition(GLFWwindow* _pWindow)
{
	double XPos, YPos;
	glfwGetCursorPos(_pWindow, &XPos, &YPos);

	v2MousePosition.x = (float)XPos;
	v2MousePosition.y = (float)YPos;
}

void MouseButtonFunction(GLFWwindow* _pWindow, int _iButton, int _iAction, int _iMods)
{
	iMouseButton = _iButton;
	iMouseAction = _iAction;
	iMouseMods = _iMods;
}

void UpdateInputPressed()
{
	if (iKeyAction == GLFW_RELEASE) bKeyPressed = false;
	else bKeyPressed = true;

	bCodePointFound = false;

	if (iMouseAction == GLFW_RELEASE) bMousePressed = false;
	else bMousePressed = true;
}

void TextInput(GLFWwindow* _pWindow, unsigned int _iCodePoint)
{
	bCodePointFound = true;
	charCodePoint = _iCodePoint;
}