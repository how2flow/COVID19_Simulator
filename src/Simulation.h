#pragma once
#include "afxwin.h"


// Simulation 대화 상자입니다.

class Simulation : public CDialog
{
	DECLARE_DYNAMIC(Simulation)

public:
	Simulation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Simulation();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SimulationInit };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 콤보박스 컨트롤 변수
	CComboBox combox;
	// 방역단계 멤버변수
	int m_stage;
	// 사회 인원 수 멤버변수
	int m_area;
	// 감염자 수 멤버변수
	int m_infected;
	afx_msg void OnCbnSelchangeCombox();
	virtual BOOL OnInitDialog();
	int init_flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
