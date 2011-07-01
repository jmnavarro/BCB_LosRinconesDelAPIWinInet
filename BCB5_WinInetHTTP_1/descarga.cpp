//---------------------------------------------------------------------------------------------
//
// Archivo: descarga.cpp
//
// Prop�sito:
//    Implementaci�n de la funci�n "Descarga" encargada de leer un recurso remoto a trav�s del
//    protocolo HTTP con Wininet.
//
// Autor:          Jos� Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para S�ntesis n� 15 (http://www.grupoalbor.com)
// Copyright:      Este c�digo es de dominio p�blico y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a trav�s de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#include "descarga.h"

#include <windows.h>  /* es importante incluir siempre windows.h ANTES de wininet.h */
#include <wininet.h>



//---------------------------------------------------------------------------
int Descargar(const char        *url,
              const char        *destino,
              const TOpciones   *opc,     /*= NULL */
              DESCARGA_CALLBACK  evento   /*= NULL */)
{
    char   msg[256];

    //
    // Paso 1: abrir la instancia de internet
    //
    HINTERNET  hInet = InternetOpen(
                            "Programa",                   // el user-agent
                            INTERNET_OPEN_TYPE_PRECONFIG, // configuraci�n por defecto
                            NULL, NULL,                   // sin proxy
                            0 );                          // sin opciones

    if (!hInet ) // esta condici�n es equivalente a hInet == NULL
    {
        if (evento)
        {
            wsprintf(msg, "InternetOpen - Ha ocurrido un error abriendo la instancia en Wininet. C�digo de error: %u",
                     GetLastError());
            evento(msg);
        }
        return -1;
    }
    else if (evento)
    {
        evento("InternetOpen - Instancia abierta en Wininet.");
    }

    //
    // Paso 2: siguiendo el m�todo directo, se llama a InternetOpenUrl
    // para acceder a un recurso remoto
    //
    HINTERNET  hPagina = InternetOpenUrl(
                                 hInet, // el descriptor del api
                                 url,
                                 NULL, 0,
                                 (opc ? opc->m_internetOpenUrl : 0), // opciones configuradas
                                 0 );
    if ( !hPagina )
    {
        if (evento)
        {
            if ( GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED )
                wsprintf(msg, "InternetOpenUrl - Ha ocurrido resolviendo el host. Posiblemente no haya una conexi�n a internet abierta.");
            else
                wsprintf(msg, "InternetOpenUrl - Ha ocurrido un error accediendo a la URL. C�digo de error: %u",
                         GetLastError());
            evento(msg);
        }

        // cerrar el descriptor para evitar la fuga de memoria
        if ( InternetCloseHandle(hInet) )
            hInet = NULL;

        return -1;
    }
    else if (evento)
    {
        evento("InternetOpenUrl - Recurso remoto abierto.");
    }


    //
    // Paso 3: consultamos los datos de cabecera requeridos
    //

    if ( evento && opc )
    {
        char   valor[256];
        DWORD  len;
        DWORD  indice;
        DWORD  numero;
        DWORD  flag;
        BOOL   ok;
        int    TipoDato;

        //
        // Proceso cada una de las cabeceras que quiere ver el usuario
        //
        for (int i = 0; i < MAX_CABECERAS; i++)
            if ( opc->m_cabeceras & CABECERAS[i].mascara )
            {
                valor[0] = '\0';
                indice = 0; // importante establecer a 0 para recuperar el primer valor

                //
                // dependiendo del tipo de cabecera que est� procesando en esta vuelta,
                // establezco el tipo entre string (por defecto), n�mero o fecha
                //
                switch( CABECERAS[i].mascara )
                {
                    case MASK_CONTENT_LENGTH:
                    case MASK_STATUS_CODE:
                        len = sizeof(DWORD);
                        flag = HTTP_QUERY_FLAG_NUMBER;
                        break;

                    case MASK_DATE:
                    case MASK_LAST_MODIFIED:
                        len = sizeof(SYSTEMTIME);
                        flag = HTTP_QUERY_FLAG_SYSTEMTIME;
                        break;

                    default:
                        len = 255;
                        flag = 0;
                }

                // recupero la cabecera
                if ( !HttpQueryInfo(hPagina, CABECERAS[i].tipo | flag, valor, &len, &indice) )
                {
                    switch ( GetLastError() )
                    {
                        case ERROR_HTTP_HEADER_NOT_FOUND:
                            wsprintf(msg, "HttpQueryInfo - %s: no disponible.", CABECERAS[i].descripcion);
                            break;

                        default:
                            wsprintf(msg, "HttpQueryInfo - No se ha podido recuperar la cabecera %s. C�digo de error: %d",
                                    CABECERAS[i].descripcion, GetLastError());
                            break;
                    }
                }
                else
                {
                    // dependiendo del tipo de dato recuperado, muestro un mensaje u otro
                    switch(flag)
                    {
                        case HTTP_QUERY_FLAG_NUMBER:
                            wsprintf(msg, "HttpQueryInfo - %s = %u", CABECERAS[i].descripcion,
                                     (DWORD)*((LPDWORD)valor));
                            break;

                        case HTTP_QUERY_FLAG_SYSTEMTIME:
                        {
                            PSYSTEMTIME    fecha = (PSYSTEMTIME)valor;

                            wsprintf(msg, "HttpQueryInfo - %s = %u/%u/%u %u:%u:%u,%u", CABECERAS[i].descripcion,
                                     fecha->wDay, fecha->wMonth, fecha->wYear,
                                     fecha->wHour, fecha->wMinute, fecha->wSecond, fecha->wMilliseconds);
                            break;
                        }
                        default:
                            wsprintf(msg, "HttpQueryInfo - %s = %s", CABECERAS[i].descripcion, valor);
                            break;
                    }
                }

                evento(msg);
            }
    }



    //
    // Paso 4: leemos los datos del recurso
    //
    DWORD  len        = 0;
    DWORD  len_data   = 0;
    DWORD  size_data  = 512;
    DWORD  disponible = 0;
    char  *data       = new char[size_data];
    char  *buff       = NULL;

    do
    {
        //
        // Consultar los datos que est�n disponibles en el servidor
        //
        if ( !InternetQueryDataAvailable( hPagina, &disponible, 0, 0) )
        {
            if ( GetLastError() == ERROR_NO_MORE_FILES )
            {
                disponible = (DWORD) -1;
                strcpy(msg, "El recurso no existe.");
            }
            else
            {
                disponible = 255;
                wsprintf( msg, "InternetQueryDataAvailable - Error consultado tama�o disponible. C�digo: %d",
                          GetLastError() );
            }
            if (evento)
                evento(msg);
        }

        if ( (DWORD) -1 == disponible )
        {
            if ( InternetCloseHandle(hPagina) ) hPagina = NULL;
            if ( InternetCloseHandle(hInet) )   hInet   = NULL;

            return -1;
        }
        else if ( 0 == disponible )
        {
            len = 0;
            continue;
        }
        else
            buff = new char[disponible];


        //
        // Leer el n�mero de bytes disponibles
        //
        if ( !InternetReadFile( hPagina, buff, disponible, &len) )
        {
            // recupero del servidor el c�digo y la descripci�n del error.
            DWORD err;
            DWORD size = 256;

            InternetGetLastResponseInfo(&err, buff, &size);
            wsprintf(msg, "InternetReadFile - Error en InternetReadFile.\nC�digo: %d\nMensaje: %s", err, buff);
            
            if (evento)
                evento(msg);
        }
        else if ( len > 0 )
        {
            // Se va duplicando el tama�o del buffer hasta que estemos seguros que
            // los datos le�dos tienen espacio suficiente.
            // La raz�n por la que se duplica el tama�o del buffer, en vez de ampliar
            // hasta lo que realmente se necesita, la expliqu� durante el art�culo
            // sobre los montones, que pod�is consultar en http://jm.here.ws/goto.htm?21130
            while ( size_data < len_data + len )
                size_data *= 2;

            // Una vez que sabemos el tama�o al que tenemos que ampliar, creamos un nuevo
            // buffer de ese tama�o y traspasamos los datos.

            // creo un buffer auxiliar donde copio el contenido
            char  *aux = new char[size_data];

            if ( len_data > 0 )
                CopyMemory(aux, data, len_data);

            delete [] data;   // elimino el buffer actual (que se ha quedado demasiado peque�o)
            data = aux;       // paso a utilizar el nuevo buffer, que es el doble que el anterior

            CopyMemory(data + len_data, buff, len);
            len_data += len;

            if (evento)
            {
                wsprintf(msg, "InternetQueryDataAvailable - %u bytes disponibles. InternetReadFile - %u bytes descargados. Total: %u bytes",
                        disponible, len, len_data);
                evento(msg);
            }
        }

        if ( buff )
            delete [] buff;
    }
    while ( len > 0 );

    //
    // ahora tenemos en el buffer "data" todo el contenido de la p�gina descargada.
    // Podemos hacer lo que queramos con ella: mostrarla, almacenar en un fichero, etc.
    // Nosotros vamos a almacenarla en un fichero, utilizando la t�cnica que ya conocemos
    // de archivos proyectados en memoria.
    // Para m�s informaci�n sobre c�mo utilizar esta t�cnica pod�is consultar el art�culo
    // publicado en http://jm.here.ws/goto.htm?21140
    //
    HANDLE hFile = CreateFile(
                      destino,       // los datos los guardamos en el destino
                      GENERIC_READ | GENERIC_WRITE, 0, NULL, // abrimos de lectura/escritura
                      CREATE_ALWAYS,                         // creamos un archivo si no existe
                      FILE_ATTRIBUTE_NORMAL, 0);

    if ( INVALID_HANDLE_VALUE == hFile )
    {
        if (evento)
            evento("CreateFile - Error intentando crear el archivo");
        len_data = -2;
    }
    else
    {
        HANDLE hFileMap = CreateFileMapping(hFile,                 // creamos la proyecci�n
                                            NULL, PAGE_READWRITE,  // de lectura/escritura
                                            0, len_data,           // del tama�o del buffer
                                            NULL);                 // sin nombre

        if ( !hFileMap )
        {
            if (evento)
                evento("CreateFileMapping - Error crear la proyecci�n de archivo.");
            len_data = -2;
        }
        else
        {
            LPSTR vista = (LPSTR) MapViewOfFile(
                                       hFileMap,       // creamos la vista sobre la proyecci�n
                                       FILE_MAP_WRITE, // de lectura/escritura
                                       0, 0, 0);
            if ( !vista )
            {
                if (evento)
                    evento("MapViewOfFile - Error crear la vista sobre la proyecci�n de archivo.");
                len_data = -2;
            }
            else
            {
                // como ya podemos acceder al archivo como si fuera un bloque de memoria,
                // copiamos los caracteres en �l,utilizando la funci�n del API Win32 CopyMemory
                CopyMemory(vista, data, len_data);

                // nos aseguramos que todo queda bien guardado
                FlushViewOfFile(vista, len_data);

                // y cerramos todos los descriptores abiertos
                if ( UnmapViewOfFile(vista) ) vista = NULL;
            }

            if ( CloseHandle(hFileMap) ) hFileMap = NULL;
        }

        if ( CloseHandle(hFile) ) hFile = NULL;
    }


    //
    // Paso 5: cerrar los descriptores
    //
    if ( InternetCloseHandle(hPagina) )  hPagina = NULL;
    if ( InternetCloseHandle(hInet) )    hInet   = NULL;

    // retorno el n�mero de bytes descargados
    return (len_data);
}
