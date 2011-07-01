//---------------------------------------------------------------------------------------------
//
// Archivo: main.h
//
// Propósito:
//    Formulario principal y función inline LinkTo
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para Síntesis nº 15 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#ifndef mainH
#define mainH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <SysInit.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <FileCtrl.hpp>

#include <SysUtils.hpp>

#pragma hdrstop


#include "opciones.h"



class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TImage *i_icono;
   TLabel *l_jm;
   TPanel *p_funciones;
   TLabel *l_rincones;
   TLabel *l_wininet;
   TLabel *l_sintesis;
   TLabel *Label1;
   TPanel *p_resultado;
   TShape *s_borde;
   TPanel *p_tab;
   TPageControl *pc_resultado;
   TTabSheet *ts_archivo;
   TButton *b_abrir;
   TEdit *e_localizacion;
   TEdit *e_asociado;
   TTabSheet *ts_vista;
   TMemo *m_vista;
    TComboBox *cb_url;
    TLabel *Label2;
    TListBox *lb_log;
    TButton *b_opciones;
    TButton *b_descargar;
    TLabel *Label3;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall l_jmClick(TObject *Sender);
   void __fastcall l_wininetClick(TObject *Sender);
   void __fastcall l_sintesisClick(TObject *Sender);
   void __fastcall l_rinconesClick(TObject *Sender);
   void __fastcall EnterLink(TObject *Sender);
   void __fastcall LeaveLink(TObject *Sender);
   void __fastcall b_abrirClick(TObject *Sender);
   void __fastcall b_descargarClick(TObject *Sender);
   void __fastcall pc_resultadoChange(TObject *Sender);
    void __fastcall b_opcionesClick(TObject *Sender);

private:
    TOpciones   m_opciones;

public:
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------



//
// Función auxiliar para lanzar el explorador por defecto
//
inline bool LinkTo(const char *url)
{
   return ( HINSTANCE_ERROR <= (int) ::ShellExecute( ::GetForegroundWindow(),
                                                 NULL,
                                                 url,
                                                 NULL,
                                                 NULL,
                                                 SW_NORMAL) );
}

#endif
