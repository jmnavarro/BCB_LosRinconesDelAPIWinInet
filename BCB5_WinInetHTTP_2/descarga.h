//---------------------------------------------------------------------------
#ifndef descargaH
#define descargaH

#include <wininet.hpp>
#include <classes.hpp>
#pragma hdrstop

#include "conexiones.h"

//
// Funci�n global para la descarga a trav�s de Wininet.
//
int Descargar(const HINTERNET hInternet, const AnsiString &url, TConexiones &conexiones, AnsiString &destino);


#endif
