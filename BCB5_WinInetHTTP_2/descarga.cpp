#include "descarga.h"


//---------------------------------------------------------------------------
int Descargar(const HINTERNET hInternet, const AnsiString &url, TConexiones &conexiones, AnsiString &destino)
{
   const DWORD     BuffSize = 1024;

   URL_COMPONENTS  components;
   char            host[128];
   char            recurso[256];
   HINTERNET       hConnect, hReq;
   DWORD           size, dummy, data, copiado;
   TFileStream     *output;
   BYTE            *buff;


   //
   // Preparo la estructura URL_COMPONENTS para descomponer la URL
   //
   ::ZeroMemory(&components, sizeof(URL_COMPONENTS));
   components.dwStructSize = sizeof(URL_COMPONENTS);

   components.dwHostNameLength = 128;
   components.lpszHostName     = host;

   components.dwUrlPathLength  = 256;
   components.lpszUrlPath      = recurso;

   ::InternetCrackUrl( url.c_str(), 0, 0, &components);

   //
   // Conectar a un servidor determinado. Para ello utilizo el "pool" de conexiones
   // que me pasan por parámetro. Este pool se encarga de reutilizar las conexiones
   // en caso de que tengamos que conectar dos veces contra el mismo servidor.
   //
   AnsiString  aux = host;

   hConnect = conexiones.Connect(aux);
   if ( !hConnect )
   {
       ::MessageBox(GetActiveWindow(), "Error InternetConnect", "Error", MB_ICONERROR);
       return -1;
   }

   hReq = ::HttpOpenRequest(hConnect, "GET", recurso, "HTTP/1.0", NULL, NULL, 0, 0);
   if ( NULL == hReq )
       return -2;

   if ( ! ::HttpSendRequest(hReq, NULL, 0, NULL, 0) )
   {
       ::InternetCloseHandle(hReq);
       return -3;
   }

   size  = sizeof(data);
   dummy = 0;
   ::HttpQueryInfo(hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &data, &size, &dummy);


   // preparar el nombre de archivo destino
   destino += aux + "_";
   aux = recurso;
   if (aux[1] == '/')
       aux.Delete(1, 1);
   for(int i=1; i <= aux.Length(); i++)
       switch ( aux[i] )
       {
           case '/':
               aux[i] = '_';
               break;
       }

   destino += aux;

   int len = destino.Length();

   for(int i=1; i <= len; i++)
   {
       switch ( destino[i] )
       {
           case '.':
               if ( destino.SubString(i+1, len).Pos(".") != 0 )
                  destino[i] = '_';
               break;
           case '/':
               destino[i] = '_';
               break;
       }
   }

   output = new TFileStream(destino, fmCreate);
   buff = (char *) malloc(BuffSize);
   try
   {
       // hago una lectura directa, aunque debería hacerse comprobando los datos
       // disponibles con InternetQueryDataAvailable.
       // Para ver un ejemplo de cómo debería codificarse, ver el código del artículo
       // "WinInet y HTTP".
       copiado = 1;
       while ( copiado > 0 )
       {
           InternetReadFile(hReq, buff, BuffSize, &copiado);
           if ( copiado > 0 )
               output->WriteBuffer(buff, copiado);
       }

       // almacenar el caracter #0 terminador
       *buff = '\0';
       output->WriteBuffer(buff, 1);
   }
   __finally
   {
       free(buff);
       delete output;
   }

   return 1;
}
