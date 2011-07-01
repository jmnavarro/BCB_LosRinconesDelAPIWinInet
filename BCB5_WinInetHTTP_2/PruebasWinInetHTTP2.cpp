//---------------------------------------------------------------------------------------------
//
// Archivo: PruebasHTTPWinInet2.cpp
//
// Prop�sito:
//
//
// Autor:          Jos� Manuel Navarro (http://www.lawebdejm.com)
// Fecha:          01/08/2003
// Observaciones:  Unidad creada en C++ Builder 5 para S�ntesis n� 16 (http://www.grupoalbor.com)
// Copyright:      Este c�digo es de dominio p�blico y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a trav�s de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("main.cpp", MainForm);
USEUNIT("descarga.cpp");
USEUNIT("conexiones.cpp");
USELIB("C:\Prog\CBuilder5\Lib\wininet.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "Pruebas Wininet";
       Application->CreateForm(__classid(TMainForm), &MainForm);
                                         Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   catch (...)
   {
       try
       {
           throw Exception("");
       }
       catch (Exception &exception)
       {
           Application->ShowException(&exception);
       }
   }
   return 0;
}
//---------------------------------------------------------------------------
