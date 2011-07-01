//---------------------------------------------------------------------------
#pragma hdrstop

#include "HiloDescargaEventosBCB5.h"

#include <IniFiles.hpp>
#include "main.h"
//---------------------------------------------------------------------------


THiloDescargaEventos::THiloDescargaEventos()
	: HiloDescarga()
{
	InitializeCriticalSection(&protegerVCL);
}


THiloDescargaEventos::~THiloDescargaEventos()
{
	DeleteCriticalSection(&protegerVCL);
}


int THiloDescargaEventos::getDescargasPendientes(TStrings *lista)
{
	int c;

	TIniFile *ini = new TIniFile(getIniFile());
	try {
		c = lista->Count;
		ini->ReadSections(lista);
	}
	__finally {
		delete ini;
	}

	return (lista->Count - c);
}


bool THiloDescargaEventos::getDatosDescarga(AnsiString url, AnsiString &filename, DWORD &size, DWORD &lastByte)
{
	TIniFile *ini = new TIniFile(getIniFile());
	try {
		filename = ini->ReadString(url,  "filename", "");
		lastByte = ini->ReadInteger(url, "lastByte", 0);
	}
	__finally {
		delete ini;
	}

	if (filename == "")
		size = 0;
	else {
		HANDLE hFile = CreateFile(filename.c_str(), GENERIC_READ, FILE_SHARE_READ,
								NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		size = GetFileSize(hFile, NULL);
		if (size == 0xFFFFFFFF)
			size = 0;

		CloseHandle(hFile);
	}

	return (filename != "");
}


bool THiloDescargaEventos::onBeginDownload(DWORD &byteIni, DWORD &byteFin, DWORD size)
{
	DWORD ultimoByte;
	AnsiString msg;

	msg.sprintf("Inicio de descarga [%d - %d]", byteIni, byteFin);

	EnterCriticalSection(&protegerVCL);
	try {
		TIniFile *ini = new TIniFile(getIniFile());
		try {
			ultimoByte = ini->ReadInteger(getURL(), "lastByte", 0);
		}
		__finally {
			delete ini;
		}

		if (ultimoByte > 0) {
			byteIni = ultimoByte;
			byteFin = 0; // hasta el final
		}

		ventana->progreso->Min = 0;
		ventana->progreso->Max = size;

		ventana->lb_log->ItemIndex = ventana->lb_log->Items->Add(msg);
	}
	__finally {
		LeaveCriticalSection(&protegerVCL);
	}

	return true;
}


void THiloDescargaEventos::onEndDownload(DWORD totalBytes)
{
	AnsiString msg;

	msg.sprintf("Fin de descarga [%d]", totalBytes);

	EnterCriticalSection(&protegerVCL);
	try {
		ventana->lb_log->ItemIndex = ventana->lb_log->Items->Add(msg);
		ventana->ParadaDescarga();

		TIniFile *ini = new TIniFile(getIniFile());
		try {
			ini->EraseSection(getURL());
		}
		__finally {
			delete ini;
		}

		if (totalBytes > 0) {
			int ind = ventana->lb_url->Items->IndexOf(getURL());
			if (ind != -1)
				ventana->lb_url->Items->Delete(ind);

			MessageBox(ventana->Handle, "Descarga finalizada correctamente.\r\nA continuación se abrirá la carpeta donde se ha guardado del archivo descargado.", ventana->Caption.c_str(), MB_ICONINFORMATION);

			ShellExecute(GetForegroundWindow(), NULL, ventana->e_carpeta->Text.c_str(),
							NULL, NULL, SW_NORMAL);
		}
		else
			MessageBox(ventana->Handle, "No se ha podido descargar el recurso. Comprueba que la conexión esté activa y la URL sea correcta.", ventana->Caption.c_str(), MB_ICONINFORMATION);
	}
	__finally {
		LeaveCriticalSection(&protegerVCL);
	}
}


bool THiloDescargaEventos::onProcessDownload(DWORD currentBytes)
{
	AnsiString msg;

	msg.sprintf("Progreso [%d]", currentBytes);

	EnterCriticalSection(&protegerVCL);
	try {
		ventana->progreso->Position = currentBytes;

		if (ventana->lb_log->Items->Count >= 100)
			ventana->lb_log->Items->Delete(0);

		ventana->lb_log->ItemIndex = ventana->lb_log->Items->Add(msg);
	}
	__finally {
		LeaveCriticalSection(&protegerVCL);
	}

	return true;
}


void THiloDescargaEventos::onCancelDownload(DWORD currentByte)
{
	AnsiString msg;

	EnterCriticalSection(&protegerVCL);
	try {
		if (currentByte > 0) {
			TIniFile *ini = new TIniFile(getIniFile());
			try {
				ini->WriteString(getURL(),  "filename", getDestino());
				ini->WriteInteger(getURL(), "lastByte", currentByte);
			}
			__finally {
				delete ini;
			}
		}

		if (ventana->lb_url->Items->IndexOf(getURL()) == -1)
			ventana->lb_url->Items->Add(getURL());

		msg.sprintf("Descarga cancelada [%d]", currentByte);

		ventana->lb_log->ItemIndex = ventana->lb_log->Items->Add(msg);
		ventana->ParadaDescarga();
	}
	__finally {
		LeaveCriticalSection(&protegerVCL);
	}
}


AnsiString THiloDescargaEventos::getIniFile()
{
	AnsiString ret = ExtractFilePath(Application->ExeName);
	return IncludeTrailingBackslash(ret) + "descarga.ini";
}

