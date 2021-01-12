#pragma once
class Person
{
public:
	Person();
	~Person();
	// 나이 멤버변수 
	int m_age;
	// 상태 0=비감염자 -1=감염자 1=회복자
	int m_status;

	// x좌표
	int x;
	// y좌표
	int y;
	// 잠복기 0:비감염 or 회복 2~14:13단계의 잠복기..
	int m_hiden;
	// 회복기 7~21...15단계 감염시킬 수 있음..
	int m_Rcov_Period;
};

