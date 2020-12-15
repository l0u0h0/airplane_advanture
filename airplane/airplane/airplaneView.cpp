
// airplaneView.cpp: CairplaneView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "airplane.h"
#endif

#include "airplaneDoc.h"
#include "airplaneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CairplaneView

IMPLEMENT_DYNCREATE(CairplaneView, CView)

BEGIN_MESSAGE_MAP(CairplaneView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_COMMAND(ID_APP_RESTART, &CairplaneView::OnAppRestart)
	ON_COMMAND(ID_MENU_START, &CairplaneView::OnGameStart)
	ON_COMMAND(ID_GAME_1, &CairplaneView::OnGameEasy)
	ON_COMMAND(ID_GAME_2, &CairplaneView::OnGameNormal)
	ON_COMMAND(ID_GAME_3, &CairplaneView::OnGameHard)
END_MESSAGE_MAP()

// CairplaneView 생성/소멸

CairplaneView::CairplaneView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	game = 0;
	difficulty = 2;
	back_x = 0;
	type = 0;
	index = 0;
	plane_y = 300;
	map_idx = 0;
	text_y = 0;
	bird_index = 1;
	bird_x = 0;
	bird_y = 300;
	bird_fly = 0;
	bird_type = 0;
	dragon_y = -300;
	fire_x = -300;
	fire_y = -300;
	save_fire = 0;
	// 각종 변수들 초기화
}

CairplaneView::~CairplaneView()
{
}

BOOL CairplaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CairplaneView 그리기

void CairplaneView::OnDraw(CDC* pDC)
{
	CairplaneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC mdc;
	CImage main;
	CImage start_back;
	CImage start_ani;
	CImage Credit;
	CImage bird;
	CImage airplane;
	CImage dragon;
	CImage fire;
	CBitmap background;
	CString birdname;
	CString filename;
	// 각종 이미지를 출력하기 위한 변수 선언
	if (game == 0) {
		main.Load(L"res/firework.jpg");
		main.Draw(*pDC, 0, 0, 1600, 800);
	}
	// 게임 시작 전 메인 화면 출력
	if (game == 1) { // 게임 시작 시 작동
		switch (type)
		{
		case 0: // 게임 시작시 화면 출력
			KillTimer(1);
			// 시작화면으로 돌아올 시 움직이는 텍스트의 타이머 정지
			start_back.Load(L"res/시작화면.png");
			start_back.Draw(*pDC, 0, 0, 1500, 800);
			break;
		case 1: //s를 눌렀을 시 출력되는 시작애니
			filename.Format(L"res/시작애니_%d.png", index);
			start_ani.Load(filename);
			start_ani.Draw(*pDC, 0, 0, 1200, 800);
			break;
		case 2: // 시작 애니가 끝나면 게임 화면 출력
			mdc.CreateCompatibleDC(pDC);
			if (0 <= map_idx && map_idx <= 2) {
				background.LoadBitmapW(IDB_BIT_BACK1);
				if (difficulty == 1) {
					bird_type = 1;
				}
				if (difficulty == 2) {
					bird_type = 1;
				}
				if (difficulty == 3) {
					bird_type = 1;
				}
			}// 배경이 세번 지나가면 배경 변경
			 // 설정한 난이도에 따라 새의 타입 변경
			else if (3 <= map_idx && map_idx <= 5) {
				background.LoadBitmapW(IDB_BIT_BACK2);
				if (difficulty == 1) {
					bird_type = 1;
				}
				if (difficulty == 2) {
					bird_type = 3;
				}
				if (difficulty == 3) {
					bird_type = 5;
				}
			}
			else if (6 <= map_idx && map_idx <= 8) {
				background.LoadBitmapW(IDB_BIT_BACK3);
				if (difficulty == 1) {
					bird_type = 2;
				}
				if (difficulty == 2) {
					bird_type = 4;
				}
				if (difficulty == 3) {
					bird_type = 6;
				}
			}
			else if (9 <= map_idx && map_idx <= 11) {
				background.LoadBitmapW(IDB_BIT_BACK4);
				if (difficulty == 1) {
					bird_type = 2;
				}
				if (difficulty == 2) {
					bird_type = 3;
				}
				if (difficulty == 3) {
					bird_type = 7;
				}
			}
			else if (12 <= map_idx && map_idx <= 14) {
				background.LoadBitmapW(IDB_BIT_BACK5);
				if (difficulty == 1) {
					bird_type = 3;
				}
				if (difficulty == 2) {
					bird_type = 5;
				}
				if (difficulty == 3) {
					bird_type = 8;
				}
			}
			else if (15 <= map_idx && map_idx <= 17) {
				background.LoadBitmapW(IDB_BIT_BACK6);
				if (difficulty == 1) {
					bird_type = 3;
				}
				if (difficulty == 2) {
					bird_type = 6;
				}
				if (difficulty == 3) {
					bird_type = 7;
				}
			}
			else if (18 <= map_idx && map_idx <= 20) {
				background.LoadBitmapW(IDB_BIT_BACK7);
				if (difficulty == 1) {
					bird_type = 4;
				}
				if (difficulty == 2) {
					bird_type = 7;
				}
				if (difficulty == 3) {
					bird_type = 8;
				}
			}
			else if (21 <= map_idx && map_idx <= 23) {
				background.LoadBitmapW(IDB_BIT_BACK8);
				if (difficulty == 1) {
					bird_type = 4;
				}
				if (difficulty == 2) {
					bird_type = 8;
				}
				if (difficulty == 3) {
					bird_type = 8;
				}
			}
			else if (23 < map_idx && map_idx <= 49) {
				background.LoadBitmapW(IDB_BIT_END);
				bird_type = 0;
				KillTimer(0);
				plane_y = -100;
				bird_y = -200;
				fire_y = -500;
				dragon_y = -500;
			}
			// 모든 배경이 지나갔을 시 종료 화면 출력과 타이머 종료,
			// 모든 그림 제거
			else if (50 == map_idx) {
				background.LoadBitmapW(IDB_BIT_GAMEOVER);
			}
			// 장애물과 부딪혔을 시 게임 오버 화면 출력
			mdc.SelectObject(&background);
			pDC->BitBlt(back_x, 0, 1200, 800, &mdc, 0, 0, SRCCOPY);
			pDC->BitBlt(1200 + back_x, 0, 1200, 800, &mdc, 0, 0, SRCCOPY);
			// 움직이는 배경을 위해 배경을 두번 출력

			airplane.Load(L"res/종이비행기.png");
			airplane.Draw(*pDC, 50, plane_y, 50, 50);
			// 종이비행기 출력
			birdname.Format(L"res/bird_%d.png", bird_index);
			bird.Load(birdname);
			bird.Draw(*pDC, WinRight + bird_x, bird_y, 115, 115);
			// 날갯짓 하는 비둘기 출력
			dragon.Load(L"res/드래곤.png");
			dragon.Draw(*pDC, 1000, dragon_y, 200, 200);
			fire.Load(L"res/fire.png");
			fire.Draw(*pDC, fire_x, fire_y, 125, 100);
			// 공룡과 불덩이 출력
			break;
		case 3:  //c눌렀을 시 크레딧 출력
			Credit.Load(L"res/크레딧.png");
			Credit.Draw(*pDC, 0, 0, 1600, 800);

			CImage text;
			text.Load(L"res/크레딧텍스트.png");
			text.Draw(*pDC, 200, text_y, 1000, 800);
			// 크레딧 화면과 움직이는 텍스트 출력
			SetTimer(1, 100, NULL);
			// 움직이는 크레딧을 위한 1번 타이머 실행
			break;
		}
	}


}


// CairplaneView 인쇄

BOOL CairplaneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CairplaneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CairplaneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CairplaneView 진단

#ifdef _DEBUG
void CairplaneView::AssertValid() const
{
	CView::AssertValid();
}

void CairplaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CairplaneDoc* CairplaneView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CairplaneDoc)));
	return (CairplaneDoc*)m_pDocument;
}
#endif //_DEBUG


// CairplaneView 메시지 처리기
// 새와 충돌하는 지 검사하는 함수 구현
int CairplaneView::crashTest(int bird_x, int bird_y, int plane_y)
{
	// TODO: 여기에 구현 코드 추가.
	int result = 0;
	if (90 >= WinRight + bird_x && 0 <= WinRight + bird_x) {
		if (bird_y + 115 >= plane_y && bird_y <= plane_y + 50) {
			result = 1;
		}
	}

	return result;
}

// 불덩이와 충돌하는 지 검사하는 함수 구현
int CairplaneView::fireTest(int fire_x, int fire_y, int plane_y)
{
	// TODO: 여기에 구현 코드 추가.
	int result = 0;
	if (90 >= fire_x && 0 <= fire_x) {
		if (fire_y + 100 >= plane_y && fire_y <= plane_y + 50) {
			result = 1;
		}
	}

	return result;
}

// 게임 오버 될 시 r키를 누르면 재시작을 위한 변수 초기화 진행
void CairplaneView::Restart()
{
	// TODO: 여기에 구현 코드 추가.
	back_x = 0;
	type = 0;
	index = 0;
	plane_y = 300;
	map_idx = 0;
	text_y = 0;
	bird_index = 1;
	bird_x = 0;
	bird_y = 300;
	bird_fly = 0;
	bird_type = 0;
	dragon_y = -300;
	fire_x = -300;
	fire_y = -300;
	save_fire = 0;
	// 생성된 변수들 중 메인화면을 출력하게 하는 game 변수와
	// 난이도 조절을 담당하는 difficulty 변수 제외하고 초기화
}


void CairplaneView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (game == 1) {
	// 게임 실행을 선택할 시 실행
		switch (nChar)
		{
		case VK_RIGHT: 
			// 오른쪽 방향키 눌렀을 시 타이머 스타트
			// 텍스트를 움직이게 하는 타이머가 아닌 0번 타이머 실행
			SetTimer(0, 100, NULL);
			break;
		case VK_LEFT: 
			// 왼쪽 방향키 눌렀을 시 정지 & 배경 반대로 이동
			KillTimer(0);
			back_x = back_x + 5;
			Invalidate(0);
			break;
		case VK_UP: 
			// 위쪽 방향키 눌렀을 시 비행기 위로 이동
			if (0 < plane_y)
				plane_y = plane_y - 10;
			Invalidate(0);
			break;
		case VK_DOWN: 
			// 아래쪽 방향키 눌렀을 시 비행기 아래로 이동
			if (WinBottom - 50 > plane_y)
				plane_y = plane_y + 10;
			Invalidate(0);
			break;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CairplaneView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (game == 1) {
	// 게임 실행이 선택 됐을 시 실행 가능
		if (nIDEvent == 0) {
		// 본 게임 타이머인 0번 타이머가 선택됐을 시 실행
			if (back_x > -1200) {
				back_x = back_x - 5;
				bird_x = bird_x - 6;
			}
			// 배경과 새가 동시에 왼쪽으로 이동하도록 설계
			if (back_x <= -1200) {
				back_x = 0;
			}
			if (WinRight + bird_x <= 0) {
				bird_x = 0;
			}
			// 배경과 새가 화면 왼쪽을 넘어가게 되면 다시 오른쪽 끝으로
			// 돌아오도록 설계
			if (bird_type == 1) { // 새가 움직이는 타입 설정
				if (bird_y <= 0) {
					bird_fly = 0;
				}
				if (bird_y >= WinBottom) {
					bird_fly = 1;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 5;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 5;
				}
			}
			else if (bird_type == 2) {
				if (bird_y <= 0) {
					bird_fly = 0;
				}
				if (bird_y >= WinBottom) {
					bird_fly = 1;
				}
				if (WinRight + bird_x <= 600 && WinRight + bird_x > 593) {
					bird_fly = 0;
				}
				if (WinRight + bird_x <= 400 && WinRight + bird_x > 393) {
					bird_fly = 1;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 10;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 10;
				}
			}
			else if (bird_type == 3) {
				bird_fly = 1;
				if (bird_y <= 0) {
					bird_y = WinBottom;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 15;
				}
			}
			else if (bird_type == 4) {
				bird_fly = 0;
				if (bird_y >= WinBottom) {
					bird_y = 1;
				}
				if (WinRight + bird_x <= 900 && WinRight + bird_x > 893) {
					bird_y = 0;
				}
				if (WinRight + bird_x <= 600 && WinRight + bird_x > 593) {
					bird_y = 0;
				}
				if (WinRight + bird_x <= 300 && WinRight + bird_x > 293) {
					bird_y = 0;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 10;
				}
			}
			else if (bird_type == 5) {
				if (bird_y <= 0) {
					bird_fly = 0;
				}
				if (bird_y >= WinBottom) {
					bird_fly = 1;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 10;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 10;
				}
				if (WinRight + bird_x >= 900) {
					bird_x = bird_x - 6;
				}
				if (WinRight + bird_x <= 600 && WinRight + bird_x >= 301) {
					bird_x = bird_x - 12;
				}
				if (WinRight + bird_x <= 300) {
					bird_x = bird_x - 20;
				}
			}
			else if (bird_type == 6) {
				if (bird_y <= 0) {
					bird_fly = 0;
				}
				if (bird_y >= WinBottom) {
					bird_fly = 1;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 25;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 25;
				}
			}
			else if (bird_type == 7) {
				if (bird_y <= 0) {
					bird_fly = 0;
				}
				if (bird_y >= WinBottom) {
					bird_fly = 1;
				}
				if (WinRight + bird_x <= 900 && WinRight + bird_x > 893) {
					bird_y = 300;
				}
				if (WinRight + bird_x <= 600 && WinRight + bird_x > 593) {
					bird_y = 500;
					bird_fly = 3;
				}
				if (WinRight + bird_x <= 300 && WinRight + bird_x > 293) {
					bird_fly = 1;
					bird_y = 400;
				}
				if (bird_fly == 0) {
					bird_y = bird_y + 10;
				}
				if (bird_fly == 1) {
					bird_y = bird_y - 10;
				}
			}
			else if (bird_type == 8) {
				if ((WinRight / 4) * 3 < WinRight + bird_x) {
					if (bird_y <= 0) {
						bird_y = bird_y + 10;
					}
					else if (bird_y >= WinBottom) {
						bird_y = bird_y - 10;
					}
					else if (bird_y > 0 && bird_y < WinBottom) {
						bird_y = bird_y + 10;
					}
				}
				else if ((WinRight / 4) * 3 >= WinRight + bird_x
					&& (WinRight / 4) * 2 < WinRight + bird_x) {
					bird_y = rand() % 500;
					bird_x = bird_x - 10;
				}
				else if ((WinRight / 4) * 2 >= WinRight + bird_x
					&& WinRight / 4 < WinRight + bird_x) {
					bird_y = rand() % 300;
					bird_x = bird_x - 20;
				}
				else if (WinRight / 4 >= WinRight + bird_x
					&& 0 < WinRight + bird_x) {
					bird_x = bird_x - 10;
					if (bird_y <= 0) {
						bird_fly = 0;
					}
					if (bird_y >= WinBottom) {
						bird_fly = 1;
					}
					if (bird_fly == 0) {
						bird_y = bird_y + 30;
					}
					if (bird_fly == 1) {
						bird_y = bird_y - 30;
					}
				}
			}
			if (difficulty == 1) {
			// 설정된 난이도가 1(쉬움)일 시 실행
				if (9 <= map_idx && map_idx <= 11) {
				// 이 난이도에서 공룡이 출력되는 스테이지 설정
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					// 공룡이 위쪽으로 다 올라가게 되면 다음 불덩이의 랜덤
					// 위치를 설정하고 공룡의 위치를 밑으로 옮김.
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					// 공룡이 불덩이를 내뿜을 위치까지 위로 상승
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					// 공룡이 불덩이를 내뿜으면 불덩이가 사라질 때 까지
					// 가만히 멈춰서있음
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					// 공룡이 불덩이를 내뿜는 위치에 멈춰서면 불덩이를
					// 그 위치의 공룡 앞에 출력
					if (fire_x >= -200) {
						fire_x = fire_x - 20;
					}
					// 불덩이가 왼쪽으로 이동
					// 난이도, 스테이지마다 불덩이의 속도를 조절
				}
				if (21 <= map_idx && map_idx <= 23) {
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					if (fire_x >= -200) {
						fire_x = fire_x - 20;
					}
				}
			}
			if (difficulty == 2) {
				if (3 <= map_idx && map_idx <= 5) {
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					if (fire_x >= -200) {
						fire_x = fire_x - 20;
					}
				}
				if (12 <= map_idx && map_idx <= 14) {
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					if (fire_x >= -200) {
						fire_x = fire_x - 30;
					}
				}
				if (18 <= map_idx && map_idx <= 20) {
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					if (fire_x >= -200) {
						fire_x = fire_x - 30;
					}
				}
				if (21 <= map_idx && map_idx <= 23) {
					if (dragon_y < -200) {
						save_fire = rand() % 600 + 1;
						dragon_y = 1000;
					}
					if (dragon_y >= -200 && dragon_y > save_fire - 10) {
						dragon_y = dragon_y - 10;
					}
					if (fire_x <= 0) {
						dragon_y = dragon_y - 10;
					}
					if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
						fire_x = 1000;
						fire_y = save_fire;
					}
					if (fire_x >= -200) {
						fire_x = fire_x - 40;
					}
				}
			}if (difficulty == 3) {
				if (dragon_y < -200) {
					save_fire = rand() % 600 + 1;
					dragon_y = 1000;
				}
				if (dragon_y >= -200 && dragon_y > save_fire - 10) {
					dragon_y = dragon_y - 10;
				}
				if (fire_x <= 0) {
					dragon_y = dragon_y - 10;
				}
				if (dragon_y <= save_fire && dragon_y > save_fire - 10) {
					fire_x = 1000;
					fire_y = save_fire;
				}
				if (fire_x >= -200) {
					fire_x = fire_x - 40;
				}
			}
			// 움직이는 공룡이 불뿜는 모션
			if (back_x == -5)
				map_idx = map_idx + 1;
			// 배경이 한 화면 지나갈때마다 포인트를 올려서 일정 포인트가 되면
			// 배경이 바뀜
			if (bird_index >= 1)
				bird_index = bird_index + 1;
			if (bird_index == 9)
				bird_index = 1;
			// 새 날갯짓 표현
			if (crashTest(bird_x, bird_y, plane_y) == 1) {
				back_x = 0;
				bird_y = -200;
				plane_y = -100;
				dragon_y = -500;
				fire_y = -500;
				map_idx = 50;
				KillTimer(0);
			}
			// 새와 충돌하면 게임 오버 화면 출력
			if (fireTest(fire_x, fire_y, plane_y) == 1) {
				back_x = 0;
				bird_y = -200;
				plane_y = -100;
				dragon_y = -500;
				fire_y = -500;
				map_idx = 50;
				KillTimer(0);
			}
			// 불덩이와 충돌하면 게임 오버 화면 출력
		}
		if (nIDEvent == 1) {
		// 크레딧 텍스트를 움직이게 하기 위한 1번 타이머
			if (text_y >= 0 && text_y < 700) {
				text_y = text_y + 10;
			}
			if (text_y >= 700) {
				text_y = 0;
			}
			// 크레딧화면 글자 움직임 구현
		}
	}
	Invalidate(0);
	CView::OnTimer(nIDEvent);
}


void CairplaneView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (game == 1) {
	// 게임 실행 선택할 시 실행
		switch (nChar)
		{
		case 'c': 
			// c눌렀을 시 크레딧 화면 출력
			type = 3;
			Invalidate(0);
			break;
		case 's': 
			// s눌렀을 시 시작 애니메이션 출력
			type = 1;
			Invalidate(0);
			break;
		case 'a': 
			// a눌렀을 시 시작 애니메이션 다음 화면으로 이동
			index = index + 1;
			if (index == 4) { 
			// 시작 애니 화면 끝나면 게임 스타트
				type = 2;
				Invalidate(0);
			}
			Invalidate(0);
			break;
		case 'r':
		// 게임 오버시 재시작 버튼 구현
			Restart(); 
			Invalidate(0);
			break;
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

// 윈도우 창의 오른쪽과 하단 값 저장.
void CairplaneView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	WinBottom = cy;
	WinRight = cx;
}

// 메뉴에서 재시작을 누를 시 실행되는 재시작 함수
void CairplaneView::OnAppRestart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	Restart();
	Invalidate(0);
}

// 메뉴에서 게임 실행을 누를 시 실행되는 게임 실행 함수
void CairplaneView::OnGameStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	game = 1;
	Invalidate();
}

// 이하 난이도 조절을 위한 쉬움, 보통, 어려움 함수
void CairplaneView::OnGameEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	difficulty = 1;
	Invalidate();
}


void CairplaneView::OnGameNormal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	difficulty = 2;
	Invalidate();
}


void CairplaneView::OnGameHard()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	difficulty = 3;
	Invalidate();
}
