#include "stdafx.h"
#include "HiloDescargaEventosVC6.h"

#include "Resource.h"
#include "ReanudarWinInetDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CHiloDescargaEventos::CHiloDescargaEventos(CListBox *log, CListBox *urls, CProgressCtrl *prog, CReanudarWinInetDlg *dlg)
	: HiloDescarga()
{
	this->log  = log;
	this->urls = urls;
	this->prog = prog;
	this->dlg  = dlg;

	InitializeCriticalSection(&protegerMFC);
}

CHiloDescargaEventos::~CHiloDescargaEventos()
{
	DeleteCriticalSection(&protegerMFC);
}


int CHiloDescargaEventos::getDescargasPendientes(CStringList *lista)
{
	int c;
	TCHAR buff[1024];

	c = lista->GetCount();

	GetPrivateProfileSectionNames(buff, 1024, getIniFile());

	LPTSTR ptr = buff;
	while (*ptr) {
		lista->AddTail(ptr);
		ptr += strlen(ptr) + 1;
	}

	return (lista->GetCount() - c);
}


void CHiloDescargaEventos::eliminarDescarga(LPCTSTR url)
{
	WritePrivateProfileString(url, NULL, NULL, getIniFile());
}


bool CHiloDescargaEventos::getDatosDescarga(CString url, CString &filename, DWORD &size, DWORD &lastByte)
{
	CString ini = getIniFile();

	lastByte = GetPrivateProfileInt(url, "lastByte", 0, ini);

	LPTSTR buffer = filename.GetBuffer(MAX_PATH);
	GetPrivateProfileString(url, "filename", "", buffer, MAX_PATH, ini);
	filename.ReleaseBuffer();

	if (filename == "")
		size = 0;
	else {
		HANDLE hFile = CreateFile((LPCTSTR)filename, GENERIC_READ, FILE_SHARE_READ,
								NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		size = GetFileSize(hFile, NULL);
		if (size == 0xFFFFFFFF)
			size = 0;

		CloseHandle(hFile);
	}

	return (filename != "");
}


bool CHiloDescargaEventos::onBeginDownload(DWORD &byteIni, DWORD &byteFin, DWORD size)
{
	DWORD ultimoByte;
	CString msg;

	msg.Format("Inicio de descarga [%d - %d]", byteIni, byteFin);

	EnterCriticalSection(&protegerMFC);

	ultimoByte = GetPrivateProfileInt(getURL(), "lastByte", 0, getIniFile());

	if (ultimoByte > 0) {
		byteIni = ultimoByte;
		byteFin = 0; // hasta el final
	}

	prog->SetRange32(0, size);

	log->SetCurSel(log->AddString(msg));

	LeaveCriticalSection(&protegerMFC);

	return true;
}


void CHiloDescargaEventos::onEndDownload(DWORD totalBytes)
{
	CString msg;

	msg.Format("Fin de descarga [%d]", totalBytes);

	EnterCriticalSection(&protegerMFC);

	log->SetCurSel(log->AddString(msg));

	dlg->DescargaParada();

	WritePrivateProfileString(getURL(), NULL, NULL, getIniFile());

	TCHAR title[256];
	dlg->GetWindowText(title, 256);

	if (totalBytes > 0) {
		UINT ind = urls->FindStringExact(-1, getURL());
		if (ind != LB_ERR)
			urls->DeleteString(ind);

		::MessageBox(dlg->m_hWnd, "Descarga finalizada correctamente.\r\nA continuación se abrirá la carpeta donde se ha guardado del archivo descargado.", title, MB_ICONINFORMATION);

		::ShellExecute( ::GetForegroundWindow(), NULL, dlg->m_carpeta,
						NULL, NULL, SW_NORMAL);
	}
	else
		MessageBox(dlg->m_hWnd, "No se ha podido descargar el recurso. Comprueba que la conexión esté activa y la URL sea correcta.", title, MB_ICONINFORMATION);

	LeaveCriticalSection(&protegerMFC);
}


bool CHiloDescargaEventos::onProcessDownload(DWORD currentBytes)
{
	CString msg;

	msg.Format("Progreso [%d]", currentBytes);

	EnterCriticalSection(&protegerMFC);

	prog->SetPos(currentBytes);

	if (urls->GetCount() >= 100)
		urls->DeleteString(0);

	log->SetCurSel(log->AddString(msg));

	LeaveCriticalSection(&protegerMFC);

	return true;
}


void CHiloDescargaEventos::onCancelDownload(DWORD currentByte)
{
	CString msg;

	EnterCriticalSection(&protegerMFC);

	WritePrivateProfileString(getURL(),  "filename", getDestino(), getIniFile());

	msg.Format("%d", currentByte);
	WritePrivateProfileString(getURL(), "lastByte", msg, getIniFile());

	if (urls->FindStringExact(-1, getURL()) == LB_ERR)
		urls->AddString(getURL());

	msg.Format("Descarga cancelada [%d]", currentByte);
	log->SetCurSel(log->AddString(msg));

	dlg->DescargaParada();

	LeaveCriticalSection(&protegerMFC);
}


CString CHiloDescargaEventos::getIniFile()
{
	char filename[MAX_PATH], *ptr;

	GetModuleFileName(GetModuleHandle(NULL), filename, MAX_PATH);
	
	ptr = strrchr(filename, '\\');
	ptr[1] = NULL;
	strcat(filename, "descarga.ini");

	CString ret(filename);

	return (ret);
}
