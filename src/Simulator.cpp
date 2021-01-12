// Simulator.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "COVID19_Simulator.h"
#include "Simulator.h"
#include "afxdialogex.h"


// Simulator 대화 상자입니다.

IMPLEMENT_DYNAMIC(Simulator, CDialog)

Simulator::Simulator(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Simulator, pParent)
	, start_flag(0)
{

}

Simulator::~Simulator()
{
}

void Simulator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Simulator, CDialog)
	ON_BN_CLICKED(IDOK, &Simulator::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Simulator::OnBnClickedCancel)
END_MESSAGE_MAP()


// Simulator 메시지 처리기입니다.


void Simulator::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	start_flag = 1;
	CDialog::OnOK();
}


void Simulator::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	start_flag = -1;
	CDialog::OnCancel();
}
