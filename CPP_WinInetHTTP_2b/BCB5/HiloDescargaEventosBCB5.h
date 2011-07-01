//---------------------------------------------------------------------------
#ifndef HiloDescargaEventosH
#define HiloDescargaEventosH

#include <windows.h>

#include <system.hpp>
#include <classes.hpp>

#include "HiloDescarga.h"

class TMainForm;
//---------------------------------------------------------------------------



class THiloDescargaEventos : public HiloDescarga
{
public:
	THiloDescargaEventos();
	virtual ~THiloDescargaEventos();

	int getDescargasPendientes(TStrings *lista);
	bool getDatosDescarga(AnsiString url, AnsiString &filename, DWORD &size, DWORD &lastByte);

	TMainForm *ventana;

protected:
	// eventos
	virtual bool onBeginDownload(DWORD &byteIni, DWORD &byteFin, DWORD size);
	virtual void onEndDownload(DWORD totalBytes);
	virtual bool onProcessDownload(DWORD currentBytes);
	virtual void onCancelDownload(DWORD currentByte);

private:
	AnsiString getIniFile();

	CRITICAL_SECTION	protegerVCL;
};

#endif
