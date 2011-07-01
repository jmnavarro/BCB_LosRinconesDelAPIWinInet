//---------------------------------------------------------------------------------------------
//
// Archivo: main.h
//
// Propósito:
//    Formulario principal y función inline LinkTo
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 6 para Síntesis nº 15 (http://www.grupoalbor.com)
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
#include <ActnList.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <SysInit.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include <FileCtrl.hpp>
#include <SysUtils.hpp>

#pragma hdrstop


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
   TListBox *lb_url;
   TButton *b_anadir;
   TButton *b_eliminar;
   TListBox *lb_resultado;
   TSplitter *Splitter1;
   TPanel *p_tab;
   TPageControl *pc_resultado;
   TTabSheet *ts_archivo;
   TButton *b_abrir;
   TEdit *e_asociado;
   TTabSheet *ts_vista;
   TMemo *m_vista;
   TLabel *Label2;
   TEdit *e_carpeta;
   TPanel *Panel1;
   TImage *Image1;
   TButton *b_descargar;
   TProgressBar *progreso;
   TBevel *Bevel1;
   TBevel *Bevel2;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall l_jmClick(TObject *Sender);
   void __fastcall l_wininetClick(TObject *Sender);
   void __fastcall l_sintesisClick(TObject *Sender);
   void __fastcall l_rinconesClick(TObject *Sender);
   void __fastcall b_abrirClick(TObject *Sender);
   void __fastcall b_descargarClick(TObject *Sender);
   void __fastcall b_anadirClick(TObject *Sender);
   void __fastcall lb_urlClick(TObject *Sender);
   void __fastcall b_eliminarClick(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall Image1Click(TObject *Sender);
   void __fastcall lb_resultadoClick(TObject *Sender);
   void __fastcall pc_resultadoChange(TObject *Sender);

private:
   TStringList   *m_listaBorrar;

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
