//---------------------------------------------------------------------------------------------
//
// Archivo: main.cpp
//
// Propósito:
//    Implementación del formulario principal con las pruebas del protocolo HTTP
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

#include "main.h"
#include "descarga.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner){}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    this->Color = (TColor) 0xF2F4F2;

	// truquillo para mostrar en un TImage el icono de la aplicación.
    HICON   icono = (void *) SendMessage(this->Handle, WM_GETICON, ICON_BIG, 0);
    i_icono->Picture->Icon->Handle = icono;

    m_opciones.m_destino = "C:\\";
    m_opciones.m_cabeceras = 0;
    m_opciones.m_internetOpenUrl = 0;
}


//
// Los distintos hiperenlaces
//
//---------------------------------------------------------------------------
void __fastcall TMainForm::l_jmClick(TObject *Sender)
{
   if ( LinkTo("http://users.servicios.retecal.es/sapivi/") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::l_wininetClick(TObject *Sender)
{
   if ( LinkTo("http://users.servicios.retecal.es/sapivi/prog/cpp/wininethttp.html") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::l_sintesisClick(TObject *Sender)
{
   if ( LinkTo("http://www.grupoalbor.com/Sintesis/Sintesis.htm") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::l_rinconesClick(TObject *Sender)
{
   if ( LinkTo("http://users.servicios.retecal.es/sapivi/prog/win32/") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::EnterLink(TObject *Sender)
{
   static_cast<TLabel*>(Sender)->Font->Style = TFontStyles() << fsUnderline;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LeaveLink(TObject *Sender)
{
   static_cast<TLabel*>(Sender)->Font->Style = TFontStyles();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_abrirClick(TObject *Sender)
{
   LinkTo(e_localizacion->Text.c_str());
}


//---------------------------------------------------------------------------
// Función de callback para la descarga
//---------------------------------------------------------------------------
void DescargaCallback(LPCTSTR msg)
{
    MainForm->lb_log->ItemIndex = MainForm->lb_log->Items->Add(msg);
}


//---------------------------------------------------------------------------
// Operaciones previas y llamada a la función de descarga
//---------------------------------------------------------------------------
void __fastcall TMainForm::b_descargarClick(TObject *Sender)
{
    DWORD       bytes;
    AnsiString  url("http://" + cb_url->Text);
    AnsiString  destino(IncludeTrailingBackslash(m_opciones.m_destino));

    // buscar la extensión. La función ExtractFileExt también nos sirve para Urls, porque
    // lo único que hace el buscar el punto comenzando por el final.
    destino += "datos" + ExtractFileExt(cb_url->Text);

    Screen->Cursor = crHourGlass;

    e_localizacion->Text = "Descargando...";
    e_asociado->Text     = e_localizacion->Text;
    b_abrir->Enabled     = false;
    ts_archivo->Repaint();

    __try
    {
        lb_log->Items->Clear();
        lb_log->Repaint();

        bytes = Descargar(url.c_str(), destino.c_str(), &m_opciones, &DescargaCallback);
    }
    __finally
    {
        Screen->Cursor = crDefault;

        if ( DWORD(-1) == bytes )
        {
            e_localizacion->Text = "";
            e_asociado->Text     = "";

            lb_log->ItemIndex = MainForm->lb_log->Items->Add("Se ha producido un error descargando el recurso.");
        }
        else
        {
            char buff[256];

            FindExecutable(destino.c_str(), NULL, buff);
            e_localizacion->Text = destino;
            e_asociado->Text     = buff;
            b_abrir->Enabled     = true;
            m_vista->Lines->Clear();

            lb_log->ItemIndex = MainForm->lb_log->Items->Add("El recurso ha sido descargado en " +
                    destino + ". Tamaño total: " + IntToStr(bytes) + " bytes.");
        }
    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::pc_resultadoChange(TObject *Sender)
{
    if ( m_vista->Lines->Count == 0  &&
         pc_resultado->ActivePage == ts_vista &&
         FileExists(e_localizacion->Text) )
    {
        m_vista->Lines->LoadFromFile(e_localizacion->Text);
    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_opcionesClick(TObject *Sender)
{
    TOpcionesFrm    *dlg = new TOpcionesFrm(NULL);
    __try
    {
        dlg->SetOpciones(m_opciones);
        if ( dlg->ShowModal() )
            dlg->GetOpciones(m_opciones);
    }
    __finally
    {
        delete dlg;
    }
}
//---------------------------------------------------------------------------

