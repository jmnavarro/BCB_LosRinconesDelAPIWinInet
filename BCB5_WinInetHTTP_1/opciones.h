//---------------------------------------------------------------------------------------------
//
// Archivo: opciones.h
//
// Propósito:
//    Definición del formulario de opciones y exportación de las constantes de opciones
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para Síntesis nº 15 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#ifndef opcionesH
#define opcionesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Graphics.hpp>
#include <CheckLst.hpp>
#include <wininet.h>

#pragma hdrstop


#define MASK_STATUS_CODE      0x00000001
#define MASK_STATUS_TEXT      0x00000002
#define MASK_DATE             0x00000004
#define MASK_SERVER           0x00000008
#define MASK_MIME_VERSION     0x00000010
#define MASK_CONTENT_TYPE     0x00000020
#define MASK_CONTENT_LENGTH   0x00000040
#define MASK_LAST_MODIFIED    0x00000080
#define MASK_EXPIRES          0x00000100
#define MASK_ALLOW            0x00000200
#define MASK_REQUEST_METHOD   0x00000400
#define MASK_ACCEPT           0x00000800

//---------------------------------------------------------------------------
class TCabecera
{
public:
    DWORD  tipo;
    DWORD  mascara;
    char  *descripcion;
};

#define MAX_CABECERAS  (int)12

extern const TCabecera CABECERAS[MAX_CABECERAS];

//---------------------------------------------------------------------------
class TOpciones
{
public:
    AnsiString  m_destino;
    DWORD       m_cabeceras;
    DWORD       m_internetOpenUrl;
};


//---------------------------------------------------------------------------
class TOpcionesFrm : public TForm
{
__published:	// IDE-managed Components
    TEdit *e_destino;
    TSpeedButton *b_seleccionarCarpeta;
    TShape *s_borde;
    TImage *i_icono;
    TCheckListBox *lb_inet;
    TCheckListBox *lb_cab;
    TLabel *l_carpeta;
    TButton *b_aceptar;
    TButton *Button1;
    TBevel *Bevel1;
    void __fastcall b_seleccionarCarpetaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TOpcionesFrm(TComponent* Owner);

    void SetOpciones( const TOpciones &opc );
    void GetOpciones( TOpciones &opc );
};
//---------------------------------------------------------------------------
extern PACKAGE TOpcionesFrm *OpcionesFrm;
//---------------------------------------------------------------------------
#endif
