// Transform.h : Transform ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTransformApp:
// �� Ŭ������ ������ ���ؼ��� Transform.cpp�� �����Ͻʽÿ�.
//

class CTransformApp : public CWinApp
{
public:
	CTransformApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTransformApp theApp;