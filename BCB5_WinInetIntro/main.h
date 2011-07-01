//---------------------------------------------------------------------------------------------
//
// Archivo: main.h
//
// Propósito:
//    Formulario principal y función inline LinkTo
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/04/2003
// Observaciones:  Unidad creada en C++ Builder 6 para Síntesis nº 14 (http://www.grupoalbor.com)
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
#include "Ejecutar.h"
#include <ActnList.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>


//---------------------------------------------------------------------------
#include <wininet.h>
#include <Buttons.hpp>



class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TShape *sh_funcion;
   TImage *i_icono;
   TLabel *l_jm;
   TLabel *l_url;
   TLabel *l_conexion;
   TPanel *p_funciones;
   TPageControl *pc_funciones;
   TTabSheet *ts_modem;
   TPageControl *pc_modem;
   TTabSheet *ts_cookies;
   TPageControl *pc_cookies;
   TPanel *p_aux;
   TActionList *ActionList1;
   TTabSheet *ts_autodial;
   TEjecutarFrame *AutodialFrame;
   TTabSheet *ts_autodialHangup;
   TTabSheet *ts_dial;
   TTabSheet *ts_hangup;
   TEjecutarFrame *DialFrame;
   TEjecutarFrame *AutodialHangupFrame;
   TEjecutarFrame *HangupFrame;
   TAction *InetAutodial;
   TAction *InetAutodialHangup;
   TAction *InetDial;
   TAction *InetHangup;
   TAction *InetSetCookie;
   TAction *InetGetCookie;
   TTabSheet *ts_setcookie;
   TTabSheet *ts_getcookie;
   TEjecutarFrame *SetCookieFrame;
   TEjecutarFrame *GetCookieFrame;
   TCheckListBox *AutodialFlags;
   TCheckListBox *DialFlags;
   TEdit *e_idConn;
   TEdit *e_idConn2;
   TEdit *e_urlSetCookie;
   TEdit *e_variable;
   TEdit *e_valor;
   TEdit *e_urlGetCookie;
   TListBox *lb_variables;
   TLabel *l_rincones;
   TLabel *l_wininet;
   TLabel *l_sintesis;
   TBevel *bv;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall CambioFunciones(TObject *Sender);
   void __fastcall InetAutodialExecute(TObject *Sender);
   void __fastcall InetAutodialHangupExecute(TObject *Sender);
   void __fastcall InetDialExecute(TObject *Sender);
   void __fastcall InetHangupExecute(TObject *Sender);
   void __fastcall InetSetCookieExecute(TObject *Sender);
   void __fastcall InetGetCookieExecute(TObject *Sender);
   void __fastcall l_jmClick(TObject *Sender);
   void __fastcall l_wininetClick(TObject *Sender);
   void __fastcall l_sintesisClick(TObject *Sender);
   void __fastcall l_rinconesClick(TObject *Sender);

private:
    TLabel *FLabelFunciones[2];
    TLabel *FLabelActiva;

    void __fastcall InitFunciones();

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
