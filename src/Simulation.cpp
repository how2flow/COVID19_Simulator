// Simulation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "COVID19_Simulator.h"
#include "Simulation.h"
#include "afxdialogex.h"


// Simulation 대화 상자입니다.

IMPLEMENT_DYNAMIC(Simulation, CDialog)

Simulation::Simulation(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SimulationInit, pParent)
	, m_stage(0)
	, m_area(2)
	, m_infected(1)
	, init_flag(0)
{

}

Simulation::~Simulation()
{
}

void Simulation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOX, combox);
	DDX_Text(pDX, IDC_EDIT1, m_area);
	DDX_Text(pDX, IDC_EDIT2, m_infected);
	DDX_Text(pDX, IDC_EDIT1, m_area);
	DDV_MinMaxInt(pDX, m_area, 2, 1000);
	DDX_Text(pDX, IDC_EDIT2, m_infected);
	DDV_MinMaxInt(pDX, m_infected, 1, 999);
}


BEGIN_MESSAGE_MAP(Simulation, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBOX, &Simulation::OnCbnSelchangeCombox)
	ON_BN_CLICKED(IDOK, &Simulation::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Simulation::OnBnClickedCancel)
END_MESSAGE_MAP()


// Simulation 메시지 처리기입니다.

BOOL Simulation::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	combox.AddString(_T("Strong social distance(10%)"));
	combox.AddString(_T("Relaxed social distance(30%)"));
	combox.AddString(_T("Distance in life(50%)"));
	combox.AddString(_T("Everyday life(90%)"));
	combox.SetCurSel(0);
	m_area = 1;
	m_infected = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Simulation::OnCbnSelchangeCombox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_stage = combox.GetCurSel();
}



void Simulation::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	init_flag = 1;
	CDialog::OnOK();
}


void Simulation::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	init_flag = 0;
	CDialog::OnCancel();
}
