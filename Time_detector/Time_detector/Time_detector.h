
// Time_detector.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTime_detectorApp:
// �йش����ʵ�֣������ Time_detector.cpp
//

class CTime_detectorApp : public CWinApp
{
public:
	CTime_detectorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTime_detectorApp theApp;