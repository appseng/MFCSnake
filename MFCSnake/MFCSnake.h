
// MFCSnake.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCSnakeApp:
// Сведения о реализации этого класса: MFCSnake.cpp
//

class CMFCSnakeApp : public CWinApp
{
public:
	CMFCSnakeApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCSnakeApp theApp;
