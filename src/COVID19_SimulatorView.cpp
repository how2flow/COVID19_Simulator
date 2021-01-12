
// COVID19_SimulatorView.cpp : COVID19_SimulatorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "COVID19_Simulator.h"
#endif

#include "COVID19_SimulatorDoc.h"
#include "COVID19_SimulatorView.h"

#include "Simulation.h"
#include "Simulator.h"
#include "SimResult.h"
#include "Person.h"
#include <time.h>
#include <cstdlib>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//객체(사람) 관련 상수
#define MAX 1000 //객체 생성 최대 치
#define SIZE 10 //객체 크기
#define DivideRect 10 //활동 반경 제한을 위한 상수
#define SPEED 15 //객체 이동 속도
#define  Disease_progression_rate 5 //잠복기와 회복기 진행 정도 수치 타이머 n회당 1단계씩 진행

//타이머 관련 상수
#define ST 1000 //시뮬레이션 동작 타이머
#define TIMER 1001 // 시간측정 타이머
#define TERM 50 //타이머 호출 간격 (잠복기 -> 회복기 단계별 진행 속도 조절)
#define TIMECHECK 1000 //TIMECHECK 초마다 시간 측정

// COVID19_SimulatorView

IMPLEMENT_DYNCREATE(COVID19_SimulatorView, CView)

BEGIN_MESSAGE_MAP(COVID19_SimulatorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_MENU_SIMULATION, &COVID19_SimulatorView::OnMenuSimulation)
	ON_COMMAND(ID_MENU_SIMULATOR, &COVID19_SimulatorView::OnMenuSimulator)
	ON_COMMAND(ID_MENU_RESULT, &COVID19_SimulatorView::OnMenuResult)
	ON_COMMAND(ID_AC1, &COVID19_SimulatorView::OnAcceleratorresult)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// COVID19_SimulatorView 생성/소멸

COVID19_SimulatorView::COVID19_SimulatorView()
	: m_stage(1)
	, m_area(2)
	, m_infected(1)
	, init_flag(0)
	, start_flag(0)
	, age(0)
	, direction(0)
	, dx(0)
	, dy(0)
	, count(0)
	, t_count(0)
	, Result_infected(0)
	, Result_Non(0)
	, Resulted_Rcov(0)
	, m_time(0)
	, infected_child(0)
	, infected_10s(0)
	, infected_20s(0)
	, infected_30s(0)
	, infected_40s(0)
	, infected_50s(0)
	, infected_60s(0)
	, infected_70s(0)
	, infected_80s(0)
	, infected_90s(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(ID_AC1));

}

COVID19_SimulatorView::~COVID19_SimulatorView()
{
}

BOOL COVID19_SimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COVID19_SimulatorView 그리기


Person *Human = new Person[MAX]; //사람 객체 외부 선언
CPoint *pot = new CPoint[MAX]; //좌표값 연산을 위한 CPoint 외부 선언

void COVID19_SimulatorView::OnDraw(CDC* pDC)
{
	COVID19_SimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	if (init_flag) //초기화 설정을 했을 경우
	{
		//시뮬레이션 동작 전 사람객체 초기화
		if (start_flag == 0)
		{
			CPen redPen;
			CPen* pOldPen;
			CBrush RBrush, BBrush, GBrush;
			CRect rect;
			if (m_area < m_infected)
			{
				MessageBox(_T("There should be more Social Population than Number of Infected."), _T("Warning!"), MB_ICONWARNING);
				return;
			}
			redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			RBrush.CreateSolidBrush(RGB(255, 0, 0));
			BBrush.CreateSolidBrush(RGB(0, 0, 255));
			GBrush.CreateSolidBrush(RGB(0, 255, 0));
			GetClientRect(&rect);
			pOldPen = pDC->SelectObject(&redPen);
			pDC->Rectangle((rect.right / DivideRect), (rect.bottom / DivideRect), (rect.right / DivideRect) * 9, (rect.bottom / DivideRect) * 9);
			pDC->SelectObject(pOldPen);
			//객체 전체 스캔
			for (int i = 0; i < m_area; i++)
			{
				//랜덤좌표 할당
				Human[i].x = (rand() % ((rect.right / DivideRect) * 9) - SIZE);
				Human[i].y = (rand() % ((rect.bottom / DivideRect) * 9) - SIZE);
				if (Human[i].x < (rect.right / DivideRect))
					Human[i].x += (rect.right / DivideRect) + SIZE;
				if (Human[i].y < (rect.bottom / DivideRect))
					Human[i].y += (rect.bottom / DivideRect) + SIZE;
				//객체 전원 나이 할당 (0~99세)
				Human[i].m_age = rand() % 100;
				//랜덤좌표값 pot에 각각 저장
				pot[i].x = Human[i].x;
				pot[i].y = Human[i].y;
				if (i < m_infected)
				{
					Human[i].m_status=-1; //초기 감염
					Human[i].m_hiden = (rand()%13) +2; //잠복기 랜덤 초기화
					Human[i].m_Rcov_Period = 0; //회복기 0 
					pDC->SelectObject(&RBrush);
					pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
				}
				else if (i >= m_infected)
				{
					Human[i].m_status=0; //초기 비감염
					Human[i].m_hiden = 0; //잠복기 0
					Human[i].m_Rcov_Period = 0; //회복기 0 
					pDC->SelectObject(&BBrush);
					pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
				}
			}
		}
		//시뮬레이션 동작 후
		else if (start_flag == 1)
		{
			//기본 화면 설정
			CPen redPen;
			CPen* pOldPen;
			CBrush RBrush, BBrush, GBrush;
			CRect rect;
			redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			RBrush.CreateSolidBrush(RGB(255, 0, 0));
			BBrush.CreateSolidBrush(RGB(0, 0, 255));
			GBrush.CreateSolidBrush(RGB(0, 255, 0));
			GetClientRect(&rect);
			pOldPen = pDC->SelectObject(&redPen);
			pDC->Rectangle((rect.right / DivideRect), (rect.bottom / DivideRect), (rect.right / DivideRect) * 9, (rect.bottom / DivideRect) * 9);
			pDC->SelectObject(pOldPen);
			//통계에 사용되는 모든 변수 초기화
			statistics_init();
			//객체 하나하나 상태에 따라 색상 변경 감염자:빨간색 비감염자:파란색 회복:초록색
			for (int i = 0; i < m_area; i++)
			{
				if (Human[i].m_status == -1)
				{
					pDC->SelectObject(&RBrush);
					Result_infected++;
				}
				else if (Human[i].m_status == 0)
				{
					pDC->SelectObject(&BBrush);
					Result_Non++;
				}
				else if (Human[i].m_status == 1)
				{
					pDC->SelectObject(&GBrush);
					Resulted_Rcov++;
				}
				//객체당 사각형 그리기
				pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
			}
			//나이별 감염자 수 구분하기(통계)
			Classification_by_age_group();
		}
		//시뮬레이션 동작 취소 시
		else if (start_flag == -1)
		{
			KillTimer(ST);
			KillTimer(TIMER);
			return;
		}

	}
}


// COVID19_SimulatorView 인쇄

BOOL COVID19_SimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COVID19_SimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COVID19_SimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// COVID19_SimulatorView 진단

#ifdef _DEBUG
void COVID19_SimulatorView::AssertValid() const
{
	CView::AssertValid();
}

void COVID19_SimulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COVID19_SimulatorDoc* COVID19_SimulatorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COVID19_SimulatorDoc)));
	return (COVID19_SimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// COVID19_SimulatorView 메시지 처리기

//시뮬레이션 초기화 실행 시
void COVID19_SimulatorView::OnMenuSimulation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Simulation sim;

	//대화상자 클래스 변수 값 -> 뷰클래스 변수 값
	//초기화 하기 전..
	if (!init_flag)
	{
		sim.DoModal();
		m_stage = sim.m_stage;
		m_area = sim.m_area;
		m_infected = sim.m_infected;
		init_flag = sim.init_flag;
		start_flag = 0; //start_flag 초기화
		Invalidate(); //OnDraw() 호출
	}
	//초기화 이후
	else if (init_flag)
	{
		//시뮬레이션 동작중 혹은 동작 이후 다시 초기화 할때 모든 플래그 off,타이머 off
		init_flag = 0;
		start_flag = 0;
		KillTimer(ST);
		KillTimer(TIMER);

		//이후 동작은 초기화 전과 동일
		//대화상자 클래스 변수 값-> 뷰클래스 변수값
		sim.DoModal();
		m_stage = sim.m_stage;
		m_area = sim.m_area;
		m_infected = sim.m_infected;
		init_flag = sim.init_flag;
		start_flag = 0; //start_flag 초기화
		Invalidate(); //OnDraw() 호출
	}
}

//시뮬레이터 동작 실행 시
void COVID19_SimulatorView::OnMenuSimulator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Simulator sim;
	//초기화가 되어있다면
	if (init_flag)
	{
		//시뮬레이터 동작 전, 플래그on 동작 타이머, 시간 측정 타이머 on
		if (!start_flag)
		{
			sim.DoModal();
			start_flag = sim.start_flag;
			SetTimer(ST, TERM, NULL);
			SetTimer(TIMER,TIMECHECK,NULL);
			Invalidate();
		}
		//이미 시뮬레이션 동작중 시뮬레이터 동작 명령은 무시
		else if (start_flag)
			return;
	}
}

//결과창 출력, Ctrl+X키 입력시 함수 호출
void COVID19_SimulatorView::OnMenuResult()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//시뮬레이션 동작중에만 적용
	if (start_flag)
	{
		KillTimer(ST); // 시뮬레이션 동작 타이머 off
		KillTimer(TIMER); //시간 측정 타이머 off
		SimResult sim;
		sim.Static_Time = t_count; //1초마다 호출되는 타이머 호출 횟수를 시뮬레이션 동작 시간에 표기(시간표기는 초단위 int형으로 데이터 저장)
		t_count = 0;//t_count 초기화
		sim.Static_infection_rate = floor(((Result_infected * 100) / m_area) * 100) / 100; //전체 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
		sim.Static_Rcov_rate = floor(((Resulted_Rcov * 100) / m_area) * 100) / 100; //전체 회복률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래 값에서*100
		//나이별 감염자 수 비율
		if (Result_infected != 0)
		{
			sim.Static_child_rate = floor(((infected_child * 100) / Result_infected) * 100) / 100; //유아 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_10s_rate = floor(((infected_10s * 100) / Result_infected) * 100) / 100; //10대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_20s_rate = floor(((infected_20s * 100) / Result_infected) * 100) / 100; //20대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_30s_rate = floor(((infected_30s * 100) / Result_infected) * 100) / 100; //30대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_40s_rate = floor(((infected_40s * 100) / Result_infected) * 100) / 100; //40대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_50s_rate = floor(((infected_50s * 100) / Result_infected) * 100) / 100; //50대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_60s_rate = floor(((infected_60s * 100) / Result_infected) * 100) / 100; //60대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_70s_rate = floor(((infected_70s * 100) / Result_infected) * 100) / 100; //70대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_80s_rate = floor(((infected_80s * 100) / Result_infected) * 100) / 100; //80대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_90s_rate = floor(((infected_90s * 100) / Result_infected) * 100) / 100; //90대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
		}
		else
		{
			//모두 회복되거나 감염자가 없을 경우
			//모든 감염률 = 0
			sim.Static_child_rate = 0;
			sim.Static_10s_rate = 0;
			sim.Static_20s_rate = 0;
			sim.Static_30s_rate = 0;
			sim.Static_40s_rate = 0;
			sim.Static_50s_rate = 0;
			sim.Static_60s_rate = 0;
			sim.Static_70s_rate = 0;
			sim.Static_80s_rate = 0;
			sim.Static_90s_rate = 0;
		}
		//카운터변수 초기화
		count = 0;
		//모든 플래그 초기화
		init_flag = 0;
		start_flag = 0;
		//결과창 띄우기
		sim.DoModal();
	}
}


void COVID19_SimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnTimer(nIDEvent);
	if (nIDEvent == ST) //시뮬레이터 동작 시 호출...
	{
		int infect_rate = rand() % 9;
		for (int i = 0; i < m_area; i++)
		{
			CRect rect;
			GetClientRect(&rect);
			direction = (rand() % 4) + 1; // 4사분면 기준.
			dx = rand() % SPEED;
			dy = rand() % SPEED;
			switch (direction)
			{
			case 1://1사분면 방향 ++ 
					pot[i].x += dx;
					pot[i].y += dy;
				break;
			case 2://2사분면 방향 -+
					pot[i].x -= dx;
					pot[i].y += dy;			
				break;
			case 3://3사분면 방향 --
					pot[i].x -= dx;
					pot[i].y -= dy;
				break;
			case 4://4사분면 방향 +-
					pot[i].x += dx;
					pot[i].y -= dy;
				break;
			}
		}
		SocailArea();
		Period_H();
		Period_Rcov();
		switch (m_stage)
		{
		case 0://10%
			if (infect_rate == 0)
				Contact();
			break;
		case 1://30%
			if (infect_rate >= 0 && infect_rate<=2)
				Contact();
			break;
		case 2://50%
			if (infect_rate >= 0 && infect_rate <= 4)
				Contact();
			break;
		case 3://90%
			if (infect_rate != 9)
				Contact();
			break;
		}
		if (Result_infected + Resulted_Rcov == m_area || Result_infected == 0 || t_count >= 30) //모든 사람이 감염되거나 더이상 감염이 안되거나 시뮬레이션 30초가 지났을 경우
		{
			KillTimer(ST); // 시뮬레이션 동작 타이머 off
			KillTimer(TIMER); //시간 측정 타이머 off
			SimResult sim;
			sim.Static_Time = t_count; //1초마다 호출되는 타이머 호출 횟수를 시뮬레이션 동작 시간에 표기(시간표기는 초단위 int형으로 데이터 저장)
			t_count = 0;//t_count 초기화
			sim.Static_infection_rate = floor(((Result_infected * 100) / m_area) * 100) / 100; //전체 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			sim.Static_Rcov_rate = floor(((Resulted_Rcov * 100) / m_area) * 100) / 100; //전체 회복률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래 값에서*100
																						//나이별 감염자 수 비율
			if (Result_infected != 0)
			{
				sim.Static_child_rate = floor(((infected_child * 100) / Result_infected) * 100) / 100; //유아 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_10s_rate = floor(((infected_10s * 100) / Result_infected) * 100) / 100; //10대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_20s_rate = floor(((infected_20s * 100) / Result_infected) * 100) / 100; //20대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_30s_rate = floor(((infected_30s * 100) / Result_infected) * 100) / 100; //30대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_40s_rate = floor(((infected_40s * 100) / Result_infected) * 100) / 100; //40대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_50s_rate = floor(((infected_50s * 100) / Result_infected) * 100) / 100; //50대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_60s_rate = floor(((infected_60s * 100) / Result_infected) * 100) / 100; //60대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_70s_rate = floor(((infected_70s * 100) / Result_infected) * 100) / 100; //70대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_80s_rate = floor(((infected_80s * 100) / Result_infected) * 100) / 100; //80대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
				sim.Static_90s_rate = floor(((infected_90s * 100) / Result_infected) * 100) / 100; //90대 감염률 계산 floor 함수에서 소수점 둘째 자리에 반올림 하기 위한 본래값에서 *100
			}
			else
			{
				//모두 회복되거나 감염자가 없을 경우
				//모든 감염률 = 0
				sim.Static_child_rate = 0;
				sim.Static_10s_rate = 0;
				sim.Static_20s_rate = 0;
				sim.Static_30s_rate = 0;
				sim.Static_40s_rate = 0;
				sim.Static_50s_rate = 0;
				sim.Static_60s_rate = 0;
				sim.Static_70s_rate = 0;
				sim.Static_80s_rate = 0;
				sim.Static_90s_rate = 0;
			}
			//카운터변수 초기화
			count = 0;
			//모든 플래그 초기화
			init_flag = 0;
			start_flag = 0;
			//결과창 띄우기
			sim.DoModal();
		}
		count++; //타이머 호출 될 때마다 +1 , 객체의 잠복기, 회복기 진행을 위해 필요한 변수
		Invalidate();
	}
	else if (nIDEvent == TIMER)
	{
		t_count++; //시간 확인 주기마다 +1 
	}


}

//범위 내 이동
void COVID19_SimulatorView::SocailArea()
{
	RECT rect;
	GetClientRect(&rect);
	//객체 전체 스캔
	for (int i = 0; i < m_area; i++)
	{
		//왼쪽 사이드 영역을 이탈한 경우
		if (pot[i].x - SIZE <= ((rect.right) / DivideRect))
		{
			pot[i].x += dx * 3; // x 축에서 x증분 3배 만큼 오른쪽으로 이동
		}
		//오른쪽 사이드 영역을 이탈한 경우
		else if (pot[i].x + SIZE >= ((rect.right * 9) / DivideRect))
		{
			pot[i].x -= dx * 3; // x 축에서 x증분 3배 만큼 왼쪽으로 이동
		}
		//위쪽 사이드 영역을 이탈한 경우
		else if (pot[i].y - SIZE <= ((rect.bottom) / DivideRect))
		{
			pot[i].y += dy * 3; //y 축에서 y증분 3배 만큼 아래로 이동
		}
		//아래쪽 사이드 영역을 이탈한 경우
		else if (pot[i].y + SIZE >= ((rect.bottom * 9) / DivideRect))
		{
			pot[i].y -= dy * 3; //y축에서 y증분 3배 만큼 위로 이동
		}
	}

}

// 잠복기 기간..
void COVID19_SimulatorView::Period_H()
{
	for (int i = 0; i < m_area; i++)
	{
		//잠복기일 경우
		if (count% Disease_progression_rate == 0 && Human[i].m_hiden >= 2)
		{
			// 시뮬레이션 동작 호출 Disease_progression_rate회 마다 한번씩 잠복기 진행
			Human[i].m_hiden++;
			if (Human[i].m_hiden >= 14)
			{
				Human[i].m_Rcov_Period = (rand()%5)+7; //회복기 상태(랜덤, 7~11) 돌입
				Human[i].m_hiden = 0; //잠복기 0 => 다음 for문 무시
			}
		}
	}
}


// 회복기 기간..
void COVID19_SimulatorView::Period_Rcov()
{
	for (int i = 0; i < m_area; i++)
	{
		//회복기일 경우
		if (count % Disease_progression_rate*2 == 0 && Human[i].m_Rcov_Period >= 7) //회복기 주기를 잠복기 보다 2배 더 늘렸다.
		{
			// 시뮬레이션 동작 호출 Disease_progression_rate회 마다 한번씩 회복기 진행
			Human[i].m_Rcov_Period++;
			if (Human[i].m_Rcov_Period >= 21)
			{
				Human[i].m_Rcov_Period = 0; //다음 for문 무시
				Human[i].m_hiden = 0; //잠복기 초기화
				Human[i].m_status = 1; //회복자 표기
			}

		}

	}

}

// 접촉 여부 판단 함수
void COVID19_SimulatorView::Contact()
{

	for (int i = 0; i < m_area; i++)
	{
		int first_x = pot[i].x + (SIZE / 2); //객체들의 중앙 좌표값(x)을 저장
		int first_y = pot[i].y + (SIZE / 2); //객체들의 중앙 좌표값(y)을 저장
		for (int j = 0; j < m_area; j++)
		{
			int last_x = pot[j].x + (SIZE / 2); //객체들의 중앙 좌표값(x)을 저장
			int last_y = pot[j].y + (SIZE / 2); //객체들의 중앙 좌표값(y)을 저장
			//sqrt(a^2+b^2)=c 피타고라스 정리 
			double distance_s = ((first_x - last_x)*(first_x - last_x)) + ((first_y - last_y)*(first_y - last_y)); 
			double distance = sqrt(distance_s);
			//상하 좌우 2만큼의 여유를 두었다. (접촉 판정을 높였다.)
			if (distance < (double)(SIZE + 2))
			{
				if (i != j) //서로 다른 객체들 끼리 비교
				{
					if (Human[i].m_status == 0 && Human[j].m_status == 0) //비감염자 & 비감염자 접촉
					{
						Human[i].m_status = 0;
					}
					else if (Human[i].m_status == 0 && Human[j].m_Rcov_Period >= 7) // 비감염자 & 감염자 접촉
					{
						//감염과 더불어 잠복기 돌입
						Human[i].m_status = -1;
						Human[i].m_hiden = 2;
					}
					else if (Human[i].m_status == -1 && Human[j].m_Rcov_Period >= 7) //감염자 & 감염자 접촉
					{
						Human[i].m_status = -1;
					}
					else if (Human[i].m_Rcov_Period >= 7 && Human[j].m_status == 0) //감염자 & 비감염자 접촉
					{
						//감염과 더불어 잠복기 돌입
						Human[j].m_status = -1;
						Human[j].m_hiden = 2;
					}
				}
			}
		}
	}
}

// 통계에 사용되는 변수 초기화
void COVID19_SimulatorView::statistics_init()
{
	infected_child = 0;
	infected_10s = 0;
	infected_20s = 0;
	infected_30s = 0;
	infected_40s = 0;
	infected_50s = 0;
	infected_60s = 0;
	infected_70s = 0;
	infected_80s = 0;
	infected_90s = 0;
	Result_infected = 0; //감염자 수 (결과) 초기화
	Result_Non = 0; //비 감염자 수 (결과) 초기화
	Resulted_Rcov = 0; //회복자 수 (결과) 초기화
}


// 나이별 감염자 수 구분
void COVID19_SimulatorView::Classification_by_age_group()
{
	for (int i = 0; i < m_area; i++)
	{
		switch (Human[i].m_age / 10)
		{
		case 0://어린이(0~9세)
			if (Human[i].m_status == -1) //감염자라면
				infected_child++; //어린이 감염자 +1
			break;
		case 1://10대
			if (Human[i].m_status == -1) //감염자라면
				infected_10s++; //10대 감염자 +1
			break;
		case 2://20대
			if (Human[i].m_status == -1) //감염자라면
				infected_20s++; //20대 감염자 +1
			break;
		case 3://30대
			if (Human[i].m_status == -1) //감염자라면
				infected_30s++; //30대 감염자 +1
			break;
		case 4://40대
			if (Human[i].m_status == -1) //감염자라면
				infected_40s++; //40대 감염자 +1
			break;
		case 5://50대
			if (Human[i].m_status == -1) //감염자라면
				infected_50s++; //50대 감염자 +1
			break;
		case 6://60대
			if (Human[i].m_status == -1) //감염자라면
				infected_60s++; //60대 감염자 +1
			break;
		case 7://70대
			if (Human[i].m_status == -1) //감염자라면
				infected_70s++; //70대 감염자 +1
			break;
		case 8://80대
			if (Human[i].m_status == -1) //감염자라면
				infected_80s++; //80대 감염자 +1
			break;
		case 9://90대
			if (Human[i].m_status == -1) //감염자라면
				infected_90s++; //90대 감염자 +1
			break;
		}
	}

}

//단축키 동작 시 Ctrl + X
void COVID19_SimulatorView::OnAcceleratorresult()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnMenuResult(); //결과창 띄우기
	Invalidate(); //화면 지우기
}
