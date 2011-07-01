//---------------------------------------------------------------------------------------------
//
// Archivo: descarga.h
//
// Propósito:
//    Definición del prototipo de la función "Descarga"
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para Síntesis nº 15 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------
#ifndef descargaH
#define descargaH

#include "opciones.h"

//
// Defino un tipo puntero a función de callback
//
typedef void DESCARGA_CALLBACK (const char *msg);

//
// Función global para la descarga a través de Wininet.
//
int Descargar( const char         *url,
               const char         *destino,
               const TOpciones    *opc      = NULL,
               DESCARGA_CALLBACK  evento    = NULL);


#endif
