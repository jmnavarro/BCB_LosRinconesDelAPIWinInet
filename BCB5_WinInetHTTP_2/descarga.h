//---------------------------------------------------------------------------
#ifndef descargaH
#define descargaH

#include <wininet.hpp>
#include <classes.hpp>
#pragma hdrstop

#include "conexiones.h"

//
// Función global para la descarga a través de Wininet.
//
int Descargar(const HINTERNET hInternet, const AnsiString &url, TConexiones &conexiones, AnsiString &destino);


#endif
