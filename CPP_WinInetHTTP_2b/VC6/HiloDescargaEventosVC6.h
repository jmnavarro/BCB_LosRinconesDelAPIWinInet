#if !defined(AFX_HILODESCARGAEVENTOS_H__B4C3BAA7_A447_44F8_A9B0_D1EB034CC8F6__INCLUDED_)
#define AFX_HILODESCARGAEVENTOS_H__B4C3BAA7_A447_44F8_A9B0_D1EB034CC8F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "HiloDescarga.h"

#include <afxwin.h>
#include <afxcoll.h>

class CReanudarWinInetDlg;


class CHiloDescargaEventos : public HiloDescarga  
{
public:
	CHiloDescargaEventos(CListBox *log, CListBox *urls, CProgressCtrl *prog, CReanudarWinInetDlg *dlg);
	virtual ~CHiloDescargaEventos();

	int getDescargasPendientes(CStringList *lista);
	bool getDatosDescarga(CString url, CString &filename, DWORD &size, DWORD &lastByte);
	void eliminarDescarga(LPCTSTR url);

	//
	// eventos
	//
	virtual bool onBeginDownload(DWORD &byteIni, DWORD &byteFin, DWORD size);
	virtual void onEndDownload(DWORD totalBytes);
	virtual bool onProcessDownload(DWORD currentBytes);
	virtual void onCancelDownload(DWORD currentByte);

private:
	CString getIniFile();

	
	CListBox		*log;
	CListBox		*urls;
	CProgressCtrl	*prog;
	CReanudarWinInetDlg *dlg;

	CRITICAL_SECTION protegerMFC;
};

#endif
