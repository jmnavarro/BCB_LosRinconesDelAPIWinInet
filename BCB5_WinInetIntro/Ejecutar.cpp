//---------------------------------------------------------------------------------------------
//
// Archivo: Ejecutar.cpp
//
// Propósito:
//    Implementación del Frame para la ejecución de cada una de las funciones.
//    Este frame lo que hace es simplificar el código del formulario principal.
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/04/2003
// Observaciones:  Unidad creada en C++ Builder 6 para Síntesis nº 14 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
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

   // el evento OnExecute me guarda en el tag el código de error
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
