//---------------------------------------------------------------------------------------------
//
// Archivo: Ejecutar.cpp
//
// Prop�sito:
//    Implementaci�n del Frame para la ejecuci�n de cada una de las funciones.
//    Este frame lo que hace es simplificar el c�digo del formulario principal.
//
// Autor:          Jos� Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/04/2003
// Observaciones:  Unidad creada en C++ Builder 6 para S�ntesis n� 14 (http://www.grupoalbor.com)
// Copyright:      Este c�digo es de dominio p�blico y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a trav�s de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ejecutar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEjecutarFrame *EjecutarFrame;


//---------------------------------------------------------------------------
__fastcall TEjecutarFrame::TEjecutarFrame(TComponent* Owner)
   : TFrame(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TEjecutarFrame::Init(TCustomAction *accion)
{
   FAccion = accion;
   return;
}


//---------------------------------------------------------------------------
void __fastcall TEjecutarFrame::Execute(TObject *Sender)
{
	FAccion->Execute();

   // el evento OnExecute me guarda en el tag el c�digo de error
	if (1 == FAccion->Tag)
   {
       l_retorno->Caption = "Correcto";
       l_retorno->Font->Color = clGreen;
       l_retorno->Hint = "";
       l_retorno->ShowHint = false;
   }
   else if (0 != FAccion->Tag)
   {
       char    szBuff[256];
       char    szMsg[256];

       strcpy(szMsg, "Error: ");

       if (0 != ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                NULL, FAccion->Tag, 0,
                                szBuff, sizeof(szBuff), NULL))
       {
          strcat(szMsg, szBuff);
       }
       else
          strcat(szMsg, "(sin mensaje de error)");

       l_retorno->Caption = szMsg;
       l_retorno->Hint = l_retorno->Caption;
       l_retorno->ShowHint = true;
       l_retorno->Font->Color = clRed;
   }
}
//---------------------------------------------------------------------------
