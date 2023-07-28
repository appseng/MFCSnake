// MFCSnakeDlg.cpp: файл реализации
//
#include "pch.h"
#include "framework.h"
#include "MFCSnake.h"
#include "MFCSnakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно CMFCSnakeDlg

CMFCSnakeDlg::CMFCSnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSNAKE_DIALOG, pParent)
{
}

BEGIN_MESSAGE_MAP(CMFCSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// Обработчики сообщений CMFCSnakeDlg

BOOL CMFCSnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strTimerMenu;
		bNameValid = strTimerMenu.LoadString(IDS_TIMER);
		ASSERT(bNameValid);
		
		if (!strTimerMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_TIMER, strTimerMenu);
		}
	}

	points = new pp[m];

	timer = 0;
	LPRECT rec = new tagRECT;
	GetClientRect(rec);
	rec->right = rec->left + area + 16;
	rec->bottom = rec->top + area + 39;
	MoveWindow(rec);
	delete rec;
	srand(time(NULL));

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_TIMER)
		start();
	else
		CDialogEx::OnSysCommand(nID, lParam);
}

void CMFCSnakeDlg::start() 
{
	n = k = 5;
	d = NO;

	started = true;
	createFood();
	createSnake();
	timer = SetTimer(IDT_TIMER, duration, NULL);
}

void CMFCSnakeDlg::update()
{
	CClientDC dc(this);

	dc.FillSolidRect(0, 0, area, area, COLORREF(0xFFAABB));

	for (int i = 0; i < n; i++) 
		if (eatenFood.x == points[i].x && eatenFood.y == points[i].y && n != k ) 
			dc.Ellipse(points[i].x - 1, points[i].y - 1, points[i].x + circle + 1, points[i].y + circle + 1);
		else 
			dc.Ellipse(points[i].x, points[i].y, points[i].x + circle, points[i].y + circle);

	dc.Ellipse(food.x, food.y, food.x + circle, food.y + circle);
}

void CMFCSnakeDlg::step()
{
	if (extend) {
		n = k;
		extend = false;
	}

	for (int i = n - 1; i > 0; i--)
		points[i] = points[i - 1];

	if (d == NO)
		points[0].y -= length;
	else if (d == WE)
		points[0].x -= length;
	else if (d == SO)
		points[0].y += length;
	else if (d == EA)
		points[0].x += length;

	keyup = false;
}

void CMFCSnakeDlg::createFood()
{
	food.x = (rand() % (area / length)) * length;
	food.y = (rand() % (area / length)) * length;
}

void CMFCSnakeDlg::check()
{
	for (int i = 1; i < n; i++)
		if (points[0].x == points[i].x &&
			points[0].y == points[i].y) {
			gameOver();
			return;
		}
	
	if (points[n - 1].x == eatenFood.x && points[n - 1].y == eatenFood.y)
		extend = true;

	if (points[0].x == food.x && points[0].y == food.y) {
		k++;
		eatenFood = food;
		createFood();
	}
	else if (points[0].x < 0 ||
		points[0].y < 0 ||
		points[0].x > area - length ||
		points[0].y > area - length) {
		gameOver();
		return;
	}
	if (k == m)
		gameOver(true);
}

void CMFCSnakeDlg::createSnake()
{
	pp ns;
	ns.x = 15 * length;
	ns.y = 15 * length;

	for (int i = 0; i < n; i++) {
		points[i] = ns;
		ns.y += length;
	}
}

void CMFCSnakeDlg::gameOver(bool won)
{
	started = false;
	if (timer) {
		KillTimer(timer);
		timer = 0;
	}
	if (won) 
		AfxMessageBox(L"Победа!");
	else
		AfxMessageBox(L"Игра окончена");
}

CMFCSnakeDlg::~CMFCSnakeDlg()
{
	delete[] points;
}

void CMFCSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (started) {
		step();
		check();
		update();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCSnakeDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (keyup)
		return;

	if (nChar == VK_UP && d != SO)
		d = NO;
	else if (nChar == VK_LEFT && d != EA)
		d = WE;
	else if (nChar == VK_DOWN && d != NO)
		d = SO;
	else if (nChar == VK_RIGHT && d != WE)
		d = EA;

	keyup = true;

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}
