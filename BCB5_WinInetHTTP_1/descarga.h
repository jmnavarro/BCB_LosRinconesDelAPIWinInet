//---------------------------------------------------------------------------------------------
//
// Archivo: descarga.h
//
// Prop�sito:
//    Definici�n del prototipo de la funci�n "Descarga"
//
// Autor:          Jos� Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para S�ntesis n� 15 (http://www.grupoalbor.com)
// Copyright:      Este c�digo es de dominio p�blico y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a trav�s de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------
#ifndef descargaH
#define descargaH

#include "opciones.h"

//
// Defino un tipo puntero a funci�n de callback
//
typedef void DESCARGA_CALLBACK (const char *msg);

//
// Funci�n global para la descarga a trav�s de Wininet.
//
int Descargar( const char         *url,
               const char         *destino,
               const TOpciones    *opc      = NULL,
               DESCARGA_CALLBACK  evento    = NULL);


#endif
