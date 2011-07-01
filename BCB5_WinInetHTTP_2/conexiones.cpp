//---------------------------------------------------------------------------


#pragma hdrstop

#include "Conexiones.h"
#include <assert.h>


//---------------------------------------------------------------------------
TConexiones::TConexiones()
{
   m_hInternet = NULL;
}

//---------------------------------------------------------------------------
TConexiones::~TConexiones()
{
   this->DisconnectAll();
}


//---------------------------------------------------------------------------
void TConexiones::SetInternet(const HINTERNET hInternet)
{
   if ( hInternet != m_hInternet )
       m_hInternet = hInternet;
}


//---------------------------------------------------------------------------
HINTERNET TConexiones::Connect(AnsiString &host)
{
   //
   // primero hay que buscar
   //
   CONEXION    conn;
   const unsigned int size = m_pool.size();

   conn.handle = NULL;

   for (unsigned int i=0; i < size; i++)
       if ( m_pool[i].host == host )
       {
           conn.handle = m_pool[i].handle;
           break;
       }

   //
   // Si no se ha encontrado, entonces se conecta y lo añade al vector
   //
   if ( !conn.handle )
   {
      conn.host   = host.LowerCase();
      conn.handle = InternetConnect(
                           m_hInternet,                // descriptor dado por InternetOpen
                           host.c_str(),               // servidor al que conectarse
                           INTERNET_DEFAULT_HTTP_PORT, // puerto (80)
                           "", "",                     // usuario y clave
                           INTERNET_SERVICE_HTTP,      // protocolo (http)
                           0, 0);                      // opciones y contexto
      m_pool.push_back(conn);
      assert(m_pool.size() == size + 1);
   }

   return (conn.handle);
}

//---------------------------------------------------------------------------
void TConexiones::DisconnectAll()
{
   LPCONEXION  conn;

   while ( !m_pool.empty() )
   {
       conn = &m_pool.back();
       InternetCloseHandle(conn->handle);
       m_pool.pop_back();
   }
}


