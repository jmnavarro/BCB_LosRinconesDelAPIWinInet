//---------------------------------------------------------------------------

#ifndef ConexionesH
#define ConexionesH
//---------------------------------------------------------------------------

#include <wininet.hpp>
#include <vector>
#pragma hdrstop




//
// La clase conexiones, que representa un pool (a través de un std::vector) de conexiones
//
class TConexiones
{
public:

   TConexiones();
   virtual ~TConexiones();

   void SetInternet(const HINTERNET hInternet);

   HINTERNET Connect(AnsiString &host);
   void DisconnectAll();

private:
   //
   // defino una estructura donde almacenaré el nombre de host y su descriptor asociado
   //
   typedef struct tagCONEXION
   {
      HINTERNET   handle;
      AnsiString  host;
   } CONEXION, *LPCONEXION;


   HINTERNET               m_hInternet;
   std::vector<CONEXION>   m_pool;
};


#endif
