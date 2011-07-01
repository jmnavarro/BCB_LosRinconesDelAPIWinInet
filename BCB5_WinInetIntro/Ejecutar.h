//---------------------------------------------------------------------------------------------
//
// Archivo: Ejecutar.h
//
// Prop�sito:
//    Interfaz del Frame para la ejecuci�n de cada una de las funciones.
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

#ifndef EjecutarH
#define EjecutarH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------

class TEjecutarFrame : public TFrame
{
__published:	// IDE-managed Components
   TPanel *p_pie;
   TLabel *l_retorno2;
   TLabel *l_retorno;
   TBevel *Bevel1;
   TButton *b_ejecutar;
   void __fastcall Execute(TObject *Sender);

private:
   TCustomAction  *FAccion;

public:
   __fastcall TEjecutarFrame(TComponent* Owner);
   void __fastcall Init(TCustomAction *accion);

};

//---------------------------------------------------------------------------
extern PACKAGE TEjecutarFrame *EjecutarFrame;
//---------------------------------------------------------------------------
#endif
