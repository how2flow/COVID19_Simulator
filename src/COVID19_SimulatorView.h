
// COVID19_SimulatorView.h : COVID19_SimulatorView 클래스의 인터페이스
//

#pragma once


class COVID19_SimulatorView : public CView
{
protected: // serialization에서만 만들어집니다.
	COVID19_SimulatorView();
	DECLARE_DYNCREATE(COVID19_SimulatorView)

// 특성입니다.
public:
	COVID19_SimulatorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~COVID19_SimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 방역단계 멤버변수
	int m_stage;
	// 사회 인원수 멤버변수
	int m_area;
	// 감염자 수 멤버변수
	int m_infected;
	// 시뮬레이션 초기화 플래그
	int init_flag;
	// 시뮬레이션 시작 플래그 0 / 1 / -1 :초기화만 되어있는 상태 / 시뮬레이션 on / 시뮬레이션 off
	int start_flag;
	// 나이 변수
	int age;
	// 방향을 나타내는 변수
	int direction;
	// x증분
	int dx;
	// y증분
	int dy;
	// 접촉 여부 판단 함수	
	void Contact();
	// 범위 내에서 이동
	void SocailArea();
	// 잠복기 기간..
	void Period_H();
	// 회복기 기간..
	void Period_Rcov();
	//시뮬레이션 타이머 호출 횟수
	int count;
	// 시간 측정 변수
	int t_count;
	// 감염자수(결과)
	double Result_infected;
	// 비감염자 수(결과) 
	double Result_Non;
	// 회복자 수(결과)
	double Resulted_Rcov;
	// 시간 값 저장 변수
	int m_time;
	// 어린이 감염률(~9세)
	double infected_child;
	// 10대 감염자 수
	double infected_10s;
	// 20대 감염자 수
	double infected_20s;
	// 30대 감염자 수
	double infected_30s;
	// 40대 감염자 수
	double infected_40s;
	// 50대 감염자 수
	double infected_50s;
	// 60대 감염자 수
	double infected_60s;
	// 70대 감염자 수
	double infected_70s;
	// 80대 감염자 수
	double infected_80s;
	// 90대 감염자 수
	double infected_90s;
	//단축키 등록 변수
	HACCEL m_hAccel;
	// 통계에 사용되는 변수 초기화
	void statistics_init();
	// 나이별 감염자 수 구분
	void Classification_by_age_group();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnAcceleratorresult();
	afx_msg void OnMenuSimulation();
	afx_msg void OnMenuSimulator();
	afx_msg void OnMenuResult();
};

#ifndef _DEBUG  // COVID19_SimulatorView.cpp의 디버그 버전
inline COVID19_SimulatorDoc* COVID19_SimulatorView::GetDocument() const
   { return reinterpret_cast<COVID19_SimulatorDoc*>(m_pDocument); }
#endif

