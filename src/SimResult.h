#pragma once
#include "afxwin.h"


// SimResult 대화 상자입니다.

class SimResult : public CDialog
{
	DECLARE_DYNAMIC(SimResult)

public:
	SimResult(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SimResult();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Result };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int Static_Time;
	// 시뮬레이션 종료 시 현재 감염률
	double Static_infection_rate;
	// 시뮬레이션 종료시 현재 회복률
	double Static_Rcov_rate;
	// 10대 이하 어린이 감염률
	double Static_child_rate;
	// 10대 감염률
	double Static_10s_rate;
	// 20대 감염률
	double Static_20s_rate;
	// 30대 감염률
	double Static_30s_rate;
	// 40대 감염률
	double Static_40s_rate;
	// 50대 감염률
	double Static_50s_rate;
	// 60대 감염률
	double Static_60s_rate;
	// 70대 감염률
	double Static_70s_rate;
	// 80대 감염률
	double Static_80s_rate;
	// 90대 감염률
	double Static_90s_rate;
};
