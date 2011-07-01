#include "stdafx.h"
#include "ReanudarWinInet.h"
#include "ReanudarWinInetDlg.h"

#include "HiloDescargaEventosVC6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CReanudarWinInetDlg::CReanudarWinInetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReanudarWinInetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReanudarWinInetDlg)
	m_carpeta = _T("");
	m_url = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CReanudarWinInetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReanudarWinInetDlg)
	DDX_Control(pDX, IDC_LOG, m_log);
	DDX_Control(pDX, IDC_BUTTON1, m_descargar);
	DDX_Control(pDX, IDC_PROGRESS1, m_progreso);
	DDX_Control(pDX, IDC_ELIMINAR, m_bEliminar);
	DDX_Control(pDX, IDC_URLS, m_lbURL);
	DDX_Text(pDX, IDC_CARPETA, m_carpeta);
	DDX_Text(pDX, IDC_URL, m_url);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReanudarWinInetDlg, CDialog)
	//{{AFX_MSG_MAP(CReanudarWinInetDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ELIMINAR, OnEliminar)
	ON_BN_CLICKED(IDC_BUTTON1, OnDescargar)
	ON_LBN_SELCHANGE(IDC_URLS, OnSelchangeUrls)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReanudarWinInetDlg message handlers

BOOL CReanudarWinInetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	descargando = false;
	cancelando  = false;

	hilo = new CHiloDescargaEventos(&m_log, &m_lbURL, &m_progreso, this);

	CStringList	lista;	
	
	CHiloDescargaEventos* polyHilo = (CHiloDescargaEventos*)hilo;
	polyHilo->getDescargasPendientes(&lista);

	for(POSITION i = lista.GetHeadPosition(); i != NULL; ) {
		m_lbURL.AddString( lista.GetNext(i) );
	}

	if (m_lbURL.GetCount() > 0) {
		m_lbURL.SetCurSel(0);
		this->OnSelchangeUrls();
	}
	
	m_url = "http://users.servicios.retecal.es/sapivi/prog/oracle/iniciacion_oracle.zip";

	char buff[MAX_PATH];
	GetTempPath(MAX_PATH, buff);
	m_carpeta = buff;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReanudarWinInetDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReanudarWinInetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReanudarWinInetDlg::OnEliminar() 
{
	UpdateData();

	UINT sel = m_lbURL.GetCurSel();

	if (sel != LB_ERR) {
		CString url;

		m_lbURL.GetText(sel, url);

		CHiloDescargaEventos* polyHilo = (CHiloDescargaEventos*)hilo;
		polyHilo->eliminarDescarga((LPCTSTR)url);

		m_lbURL.DeleteString(sel);

		m_bEliminar.EnableWindow(m_lbURL.GetCount() > 0);
	}
	else
		MessageBox("Selecciona un elemento de la lista para eliminarlo.", "Eliminar", MB_ICONWARNING);

	
}

void CReanudarWinInetDlg::OnDescargar() 
{
	UpdateData();

	if (descargando) {
		hilo->cancelar();

		cancelando = true;
		m_descargar.SetWindowText("Cancelando...");
		m_descargar.EnableWindow(FALSE);
	}
	else {
		CString carpeta = m_carpeta;
		int l = carpeta.GetLength();
		if (carpeta[l-1] == '\\') {
			LPTSTR buff = carpeta.LockBuffer();
			buff[carpeta.GetLength()-1] = NULL;
			carpeta.UnlockBuffer();
		}

		hilo->descargar((LPCTSTR)m_url, (LPCTSTR)carpeta);

		cancelando = false;
		descargando = true;
		m_descargar.SetWindowText("Cancelar");
	}
}

BOOL CReanudarWinInetDlg::DestroyWindow() 
{
	delete hilo;
	
	return CDialog::DestroyWindow();
}

void CReanudarWinInetDlg::OnSelchangeUrls() 
{
	UpdateData();

	UINT sel = m_lbURL.GetCurSel();

	if (sel != LB_ERR) {
		DWORD size, lastByte;

		m_lbURL.GetText(sel, m_url);

		CHiloDescargaEventos* polyHilo = (CHiloDescargaEventos*)hilo;
		polyHilo->getDatosDescarga(m_url, m_carpeta, size, lastByte);

		TCHAR buff[MAX_PATH];
		strcpy(buff, m_carpeta);
		strrchr(buff, '\\')[1] = '\0';

		m_carpeta = buff;

		m_progreso.SetRange32(0, size);
		m_progreso.SetPos(lastByte);

		UpdateData(FALSE);
	}
}


void CReanudarWinInetDlg::DescargaParada()
{
	m_descargar.EnableWindow();
	m_descargar.SetWindowText("Descargar");
	descargando = false;
	cancelando  = false;
}
