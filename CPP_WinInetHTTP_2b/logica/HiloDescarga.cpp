#include "HiloDescarga.h"


HiloDescarga::HiloDescarga()
	: Hilo()
{
}


HiloDescarga::~HiloDescarga()
{
}

bool HiloDescarga::descargar(LPCSTR url, LPCSTR destino)
{
	strncpy(this->url, url, 256);
	strncpy(this->destino, destino, 256);

	iniciar(true);
	arrancar();

	return true;
}


DWORD HiloDescarga::funcionHilo()
{
	const int RECURSO_LEN = 256;

	HINTERNET hInet = NULL;
	HINTERNET hConn = NULL;
	HINTERNET hRecurso = NULL;
	DWORD	size, sizeDescargado;
	DWORD	byteIni, byteFin;
	char	recurso[RECURSO_LEN];
	LPBYTE	data;

	setCancelado(false);

	if ( !openInternet(hInet) )
		goto Err;

	if ( !connectInternet(hInet, hConn, recurso, RECURSO_LEN) )
		goto Err;

	if ( !sendRequest(hConn, hRecurso, recurso, size, byteIni, byteFin) )
		goto Err;

	strcat(destino, "\\");
	strcat(destino, strrchr(recurso, '/')+1);
	data = openFile(destino, size);
	if (!data)
		goto Err;

	if ( !downloadFile(hRecurso, data, byteIni, sizeDescargado) )
		goto Err;
	
	saveFile(data);

	if (getCancelado())
		onCancelDownload(byteIni + sizeDescargado);
	else
		onEndDownload(byteIni + sizeDescargado);

	return 1;

Err:
	if (hRecurso)
		InternetCloseHandle(hRecurso);

	if (hConn)
		InternetCloseHandle(hConn);

	if (hInet)
		InternetCloseHandle(hInet);

	onEndDownload(0);

	return 0;
}


bool HiloDescarga::openInternet(HINTERNET &hInet)
{
	hInet = InternetOpen("Multi-Descarga", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	return (hInet != NULL);
}


bool HiloDescarga::connectInternet(HINTERNET hInet, HINTERNET &hConn, char* recurso, DWORD len)
{
	const int HOST_LEN = 128;

	char host[HOST_LEN];

	parseURLData(url, host, HOST_LEN, recurso, len);

	hConn = InternetConnect(hInet, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	return (hConn != NULL);
}


bool HiloDescarga::sendRequest(HINTERNET hConn, HINTERNET &hRecurso, char *recurso, DWORD &size, DWORD &byteIni, DWORD &byteFin)
{
	hRecurso = HttpOpenRequest(hConn, "GET", recurso, NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);

	size = getSize(hConn, recurso);
	if (size == 0)
		return false;

	byteIni = 0;
	byteFin = size;

	if ( !onBeginDownload(byteIni, byteFin, size) )
		return false;

	if (byteIni > 0 || byteFin > size) {
		const int HEADER_LEN = 64;
		char header[HEADER_LEN];

		if ( getHeader(byteIni, byteFin, header, HEADER_LEN) )
			HttpAddRequestHeaders(hRecurso, header, strlen(header), HTTP_ADDREQ_FLAG_ADD_IF_NEW);
	}

	if (TRUE == HttpSendRequest(hRecurso, NULL, 0, NULL, 0))
		return true;
	else
		return false;
}

bool HiloDescarga::downloadFile(HINTERNET hRecurso, LPBYTE data, DWORD byteIni, DWORD &sizeDescargado)
{
//	const int CHUNK_SIZE = 4;
	const int CHUNK_SIZE = 4 * 1024;

	DWORD	leido;
	LPBYTE	dataPtr;
	BYTE	buffer[CHUNK_SIZE];


	dataPtr = data + byteIni;
	sizeDescargado = 0;

	do {
		memset(buffer, 0, sizeof(buffer));
		InternetReadFile(hRecurso, buffer, sizeof(buffer), &leido);
		if (leido > 0) {
			memcpy(dataPtr, buffer, leido);
			sizeDescargado += leido;
			dataPtr += leido;

			if ( !onProcessDownload(sizeDescargado + byteIni) )
				return false;
		}
	} while (!getCancelado() && leido > 0);

	if (!getCancelado())
		data[sizeDescargado + byteIni] = NULL;

	return true;
}


bool HiloDescarga::parseURLData(const char *URL, char *host, int sizeHost, char *recurso, int sizeRecurso)
{
	URL_COMPONENTS  components;

	// Preparo la estructura URL_COMPONENTS para descomponer la URL
	::ZeroMemory(&components, sizeof(URL_COMPONENTS));
	components.dwStructSize = sizeof(URL_COMPONENTS);

	components.dwHostNameLength = sizeHost;
	components.lpszHostName     = host;

	components.dwUrlPathLength  = sizeRecurso;
	components.lpszUrlPath      = recurso;

	// se hace el "if" para evitar el warning de VC++
	if (::InternetCrackUrl(URL, 0, 0, &components) == TRUE)
		return true;
	else
		return false;
}


DWORD HiloDescarga::getSize(HINTERNET conexion, char *recurso)
{
	DWORD size = 0;
	DWORD len = sizeof(size);
	DWORD dummy = 0;
	HINTERNET hRecurso = HttpOpenRequest(conexion, "HEAD", recurso, NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
	if (!recurso)
		goto Err;

	if ( !HttpSendRequest(hRecurso, NULL, 0, NULL, 0) )
		goto Err;

	if ( !HttpQueryInfo(hRecurso, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &size, &len, &dummy) ) {
		size = 0;
		goto Err;
	}

Err:
	InternetCloseHandle(hRecurso);

	return (size);
}


bool HiloDescarga::getHeader(DWORD byteIni, DWORD byteFin, char *cabecera, DWORD len)
{
	if (byteIni > 0 && byteFin > 0)
		wsprintf(cabecera, "Range: bytes=%d-%d", byteIni, byteFin);
	else if (byteIni > 0)
		wsprintf(cabecera, "Range: bytes=%d-", byteIni, byteFin);
	else
		cabecera[0] = '\0';

	return (cabecera[0] != '\0');
}


LPBYTE HiloDescarga::openFile(const char *filename, DWORD size)
{
	hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return NULL;

	hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, size, NULL);
	if (!hMap) {
		CloseHandle(hFile);
		return NULL;
	}

	return (LPBYTE) MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
}


void HiloDescarga::saveFile(LPBYTE &data)
{
	FlushViewOfFile(data, 0);
	UnmapViewOfFile(data);
	data = NULL;

	CloseHandle(hMap);
	CloseHandle(hFile);

	hMap = 0;
	hFile = 0;
}
