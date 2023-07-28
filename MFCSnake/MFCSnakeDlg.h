
// MFCSnakeDlg.h: файл заголовка
//

#pragma once


struct pp {
	int x;
	int y;
};
enum dir {
	NO,
	WE,
	EA,
	SO
};
// Диалоговое окно CMFCSnakeDlg
class CMFCSnakeDlg : public CDialogEx
{
// Создание
public:
	CMFCSnakeDlg(CWnd* pParent = nullptr);	// стандартный конструктор
	~CMFCSnakeDlg();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSNAKE_DIALOG };
#endif

// Реализация
protected:
	const int length = 17;
	const int area = 400;
	const int circle = 16;
	short n;
	short k;
	const short m = 26;
	const int duration = 360;
	UINT timer;
	dir d;
	pp* points;
	pp food;
	pp eatenFood;
	bool started = false;
	bool keyup = false;
	bool extend = false;
	
	void start();
	void update();
	void createSnake();
	void createFood();
	void step();
	void check();
	void gameOver(bool = false);

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
