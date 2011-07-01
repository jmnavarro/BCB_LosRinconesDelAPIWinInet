#if !defined(AFX_REANUDARWININETDLG_H__6F3C2F82_4242_47D2_9FBA_8BD17D98F60A__INCLUDED_)
#define AFX_REANUDARWININETDLG_H__6F3C2F82_4242_47D2_9FBA_8BD17D98F60A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


class HiloDescarga;


class CReanudarWinInetDlg : public CDialog
{
public:
	CReanudarWinInetDlg(CWnd* pParent = NULL);

	void DescargaParada();

	//{{AFX_DATA(CReanudarWinInetDlg)
	enum { IDD = IDD_REANUDARWININET_DIALOG };
	CListBox	m_log;
	CButton	m_descargar;
	CProgressCtrl	m_progreso;
	CButton	m_bEliminar;
	CListBox	m_lbURL;
	CString	m_carpeta;
	CString	m_url;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReanudarWinInetDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	//{{AFX_MSG(CReanudarWinInetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEliminar();
	afx_msg void OnDescargar();
	afx_msg void OnSelchangeUrls();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HiloDescarga *hilo;
	bool descargando;
	bool cancelando;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REANUDARWININETDLG_H__6F3C2F82_4242_47D2_9FBA_8BD17D98F60A__INCLUDED_)
