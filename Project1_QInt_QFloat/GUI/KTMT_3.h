
// KTMT_3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKTMT3App:
// See KTMT_3.cpp for the implementation of this class
//

class CKTMT3App : public CWinApp
{
public:
	CKTMT3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CKTMT3App theApp;
