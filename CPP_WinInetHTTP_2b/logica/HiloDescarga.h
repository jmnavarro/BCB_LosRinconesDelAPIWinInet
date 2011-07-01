#if !defined(AFX_HILODESCARGA_H__F435A178_8998_4FF5_99E6_0B923D080F1B__INCLUDED_)
#define AFX_HILODESCARGA_H__F435A178_8998_4FF5_99E6_0B923D080F1B__INCLUDED_

#include "Hilo.h"

#include <wininet.h>

class HiloDescarga : public Hilo
{
public:
	HiloDescarga();
	virtual ~HiloDescarga();

	virtual bool descargar(LPCSTR url, LPCSTR destino);

protected:
	virtual DWORD funcionHilo();

	//
	// eventos
	//
	virtual bool onBeginDownload(DWORD &byteIni, DWORD &byteFin, DWORD size) { return false; };
	virtual void onEndDownload(DWORD totalBytes) {};
	virtual bool onProcessDownload(DWORD currentBytes) { return false; };
	virtual void onCancelDownload(DWORD currentByte) {};

	bool openInternet(HINTERNET &hInet);
	bool connectInternet(HINTERNET hInet, HINTERNET &hConn, char* recurso, DWORD len);
	bool sendRequest(HINTERNET hConn, HINTERNET &hRecurso, char *recurso, DWORD &size, DWORD &byteIni, DWORD &byteFin);
	bool downloadFile(HINTERNET hRecurso, LPBYTE data, DWORD byteIni, DWORD &sizeDescargado);
	bool parseURLData(const char *URL, char *host, int sizeHost, char *recurso, int sizeRecurso);
	DWORD getSize(HINTERNET conexion, char *recurso);
	bool getHeader(DWORD byteIni, DWORD byteFin, char *cabecera, DWORD len);

	LPBYTE openFile(const char *filename, DWORD size);
	void saveFile(LPBYTE &data);

	char* getURL()     { return url; }
	char* getDestino() { return destino; }

private:
	char url[256];
	char destino[256];

	LPBYTE data;

	HANDLE hFile;
	HANDLE hMap;
};

#endif
