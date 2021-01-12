#pragma once


// Simulator 대화 상자입니다.

class Simulator : public CDialog
{
	DECLARE_DYNAMIC(Simulator)

public:
	Simulator(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Simulator();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Simulator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int start_flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
