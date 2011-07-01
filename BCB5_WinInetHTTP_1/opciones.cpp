//---------------------------------------------------------------------------------------------
//
// Archivo: opciones.cpp
//
// Propósito:
//    Implementación del formulario de opciones y las constantes de control de opciones
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 5 para Síntesis nº 15 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "opciones.h"

#define MAX_VALORES_INET  (int)11

const DWORD VALORES_INET[MAX_VALORES_INET] =
    {
        INTERNET_FLAG_HYPERLINK,
        INTERNET_FLAG_NO_AUTO_REDIRECT,
        INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP,
        INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS,
        INTERNET_FLAG_NEED_FILE,
        INTERNET_FLAG_NO_CACHE_WRITE,
        INTERNET_FLAG_NO_COOKIES,
        INTERNET_FLAG_NO_UI,
        INTERNET_FLAG_PRAGMA_NOCACHE,
        INTERNET_FLAG_RELOAD,
        INTERNET_FLAG_RESYNCHRONIZE
    };



const TCabecera CABECERAS[MAX_CABECERAS] =
{
    {HTTP_QUERY_STATUS_CODE,    MASK_STATUS_CODE,     "STATUS_CODE"},
    {HTTP_QUERY_STATUS_TEXT,    MASK_STATUS_TEXT,     "STATUS_TEXT"},
    {HTTP_QUERY_DATE,           MASK_DATE,            "DATE"},
    {HTTP_QUERY_SERVER,         MASK_SERVER,          "SERVER"},
    {HTTP_QUERY_MIME_VERSION,   MASK_MIME_VERSION,    "MIME_VERSION"},
    {HTTP_QUERY_CONTENT_TYPE,   MASK_CONTENT_TYPE,    "CONTENT_TYPE"},
    {HTTP_QUERY_CONTENT_LENGTH, MASK_CONTENT_LENGTH,  "CONTENT_LENGTH"},
    {HTTP_QUERY_LAST_MODIFIED,  MASK_LAST_MODIFIED,   "LAST_MODIFIED"},
    {HTTP_QUERY_EXPIRES,        MASK_EXPIRES,         "EXPIRES"},
    {HTTP_QUERY_ALLOW,          MASK_ALLOW,           "ALLOW"},
    {HTTP_QUERY_REQUEST_METHOD, MASK_REQUEST_METHOD,  "REQUEST_METHOD"},
    {HTTP_QUERY_ACCEPT,         MASK_ACCEPT,          "ACCEPT"}
};



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpcionesFrm *OpcionesFrm;

//---------------------------------------------------------------------------
__fastcall TOpcionesFrm::TOpcionesFrm(TComponent* Owner) : TForm(Owner)
{
}


//---------------------------------------------------------------------------
void TOpcionesFrm::SetOpciones( const TOpciones &opc )
{
    for (int i = 0; i < MAX_VALORES_INET; i++)
        lb_inet->Checked[i] = opc.m_internetOpenUrl & VALORES_INET[i];

    for (int i = 0; i < MAX_CABECERAS; i++)
        lb_cab->Checked[i] = opc.m_cabeceras & CABECERAS[i].mascara;

    e_destino->Text = opc.m_destino;
}


//---------------------------------------------------------------------------
void TOpcionesFrm::GetOpciones( TOpciones &opc )
{
    opc.m_internetOpenUrl = 0;
    for (int i = 0; i < MAX_VALORES_INET; i++)
        opc.m_internetOpenUrl |= lb_inet->Checked[i] ? VALORES_INET[i] : 0;

    opc.m_cabeceras = 0;
    for (int i = 0; i < MAX_CABECERAS; i++)
        opc.m_cabeceras |= lb_cab->Checked[i] ? CABECERAS[i].mascara: 0;

    opc.m_destino = e_destino->Text;
}


//---------------------------------------------------------------------------
void __fastcall TOpcionesFrm::b_seleccionarCarpetaClick(TObject *Sender)
{
    AnsiString dir(e_destino->Text);

    if ( SelectDirectory("Selecciona el directorio:", dir, dir) )
        e_destino->Text = dir;
}
