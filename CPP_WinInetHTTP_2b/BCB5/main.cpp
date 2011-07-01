//---------------------------------------------------------------------------------------------
//
// Archivo: main.cpp
//
// Propósito:
//    Implementación del formulario principal con las pruebas de la cabecera RANGE.
//
// Autor:          José Manuel Navarro - http://www.lawebdejm.com
// Fecha:          01/05/2004
// Observaciones:  Unidad creada en C++ Builder 5.
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"

#include "HiloDescargaEventosBCB5.h"

#include <IniFiles.hpp>
#include <FileCtrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
inline bool LinkTo(const char *url)
{
   return ( HINSTANCE_ERROR <= (int) ::ShellExecute( ::GetForegroundWindow(),
												 NULL,
												 url,
												 NULL,
												 NULL,
												 SW_NORMAL) );
}


//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
	delete hilo;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_descargarClick(TObject *Sender)
{
	if (descargando) {
		hilo->cancelar();
		b_descargar->Caption = "Cancelando...";
		b_descargar->Enabled = false;
		cancelando = true;
	}
	else {
		AnsiString url = "http://" + e_url->Text;

		if (e_url->Text.Trim() == "" || e_carpeta->Text.Trim() == "" || !DirectoryExists(e_carpeta->Text)) {
			MessageBox(Handle, "Tienes que introducir una URL y carpeta válida.", "Descargar", MB_ICONWARNING);
			return;
		}

		hilo->descargar(url.c_str(), ExcludeTrailingBackslash(e_carpeta->Text).c_str());
		b_descargar->Caption = "Cancelar";
	}

	descargando = !descargando;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::lb_urlClick(TObject *Sender)
{
	DWORD size, lastByte;
	AnsiString filename, url;

	bool ret = dynamic_cast<THiloDescargaEventos*> (hilo)->getDatosDescarga(lb_url->Items->Strings[lb_url->ItemIndex], filename, size, lastByte);

	if (ret) {
		url = lb_url->Items->Strings[lb_url->ItemIndex];
		url.Delete(1, 7);
		e_url->Text = url;
		e_carpeta->Text = ExtractFilePath(filename);

		progreso->Max = size;
		progreso->Position = lastByte;
	}
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Image1Click(TObject *Sender)
{
   AnsiString  dir;
   if ( SelectDirectory("Examinar carpetas", "", dir) )
	   e_carpeta->Text = dir;
}


//---------------------------------------------------------------------------
void TMainForm::ParadaDescarga()
{
	b_descargar->Caption = "Descargar";
	b_descargar->Enabled = true;
	descargando = false;
	cancelando = false;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::l_wininetClick(TObject *Sender)
{
	if ( LinkTo("http://www.lawebdejm.com/prog/cpp/wininethttp_2.html") )
		static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::l_sintesisClick(TObject *Sender)
{
	if ( LinkTo("http://www.lawebdejm.com/prog/cpp/wininethttp_2.html#apdo8") )
		static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::l_rinconesClick(TObject *Sender)
{
	if ( LinkTo("http://www.lawebdejm.com/prog/win32/") )
		static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::l_jmClick(TObject *Sender)
{
	if ( LinkTo("http://www.lawebdejm.com") )
		static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_eliminarClick(TObject *Sender)
{
   if ( lb_url->ItemIndex != -1 ) {
	   lb_url->Items->Delete(lb_url->ItemIndex);
	   if ( lb_url->Items->Count == 0 )
		   b_eliminar->Enabled = false;

	   lb_url->ItemIndex = 0;
   }
   else
	   MessageBox(this->Handle, "Selecciona un elemento de la lista para eliminarlo.", "Eliminar", MB_ICONWARNING);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	descargando = false;
	cancelando = false;

	// truquillo para mostrar en un TImage el icono de la aplicación.
	HICON   icono = (void *) SendMessage(this->Handle, WM_GETICON, ICON_BIG, 0);
	i_icono->Picture->Icon->Handle = icono;

	hilo = new THiloDescargaEventos();
	dynamic_cast<THiloDescargaEventos*>(hilo)->ventana = this;
	dynamic_cast<THiloDescargaEventos*>(hilo)->getDescargasPendientes(lb_url->Items);

	if (lb_url->Items->Count == 1) {
		lb_url->ItemIndex = 0;
		lb_url->OnClick(this);
	}

	char buff[MAX_PATH];
	GetTempPath(MAX_PATH, buff);
	e_carpeta->Text = buff;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = !descargando && !cancelando;

	if (descargando)
		MessageBox(Handle, "No puedes salir de la aplicación mientras se está descargando.", Caption.c_str(), MB_ICONINFORMATION);
	else if (cancelando)
		MessageBox(Handle, "No puedes salir de la aplicación mientras se está cancelando la descarga.", Caption.c_str(), MB_ICONINFORMATION);
}

//---------------------------------------------------------------------------

