// ReanudarWinInet.h : main header file for the REANUDARWININET application
//

#if !defined(AFX_REANUDARWININET_H__4F370BBE_9664_426D_972B_609EF8D4355D__INCLUDED_)
#define AFX_REANUDARWININET_H__4F370BBE_9664_426D_972B_609EF8D4355D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReanudarWinInetApp:
// See ReanudarWinInet.cpp for the implementation of this class
//

class CReanudarWinInetApp : public CWinApp
{
public:
	CReanudarWinInetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReanudarWinInetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReanudarWinInetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REANUDARWININET_H__4F370BBE_9664_426D_972B_609EF8D4355D__INCLUDED_)
