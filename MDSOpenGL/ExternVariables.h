#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//Window
extern unsigned int uViewPortW, uViewPortH;

//Time
extern float fPreviousTimestep;
extern float fDeltatime;

//Input
extern int iKey;
extern int iKeyScanCode;
extern int iKeyAction;
extern int iKeyMods;
extern bool bKeyPressed;
extern char charCodePoint;
extern bool bCodePointFound;

extern glm::vec2 v2MousePosition;
extern int iMouseButton;
extern int iMouseAction;
extern int iMouseMods;
extern bool bMousePressed;

extern bool bTextInputEnabled;

void KeyFunction(GLFWwindow* _pWindow, int _iKey, int _iScanCode, int _iAction, int _iMods);
void UpdateMousePosition(GLFWwindow* _pWindow);
void MouseButtonFunction(GLFWwindow* _pWindow, int _iButton, int _iAction, int _iMods);
void UpdateInputPressed();
void TextInput(GLFWwindow* _pWindow, unsigned int _iCodePoint);