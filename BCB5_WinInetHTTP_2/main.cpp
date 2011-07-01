//---------------------------------------------------------------------------------------------
//
// Archivo: main.cpp
//
// Propósito:
//    Implementación del formulario principal con las pruebas de marcado del módem y gestión
//    de cookies.
//
// Autor:          José Manuel Navarro (jose_manuel_navarro@yahoo.es)
// Fecha:          01/06/2003
// Observaciones:  Unidad creada en C++ Builder 6 para Síntesis nº 15 (http://www.grupoalbor.com)
// Copyright:      Este código es de dominio público y se puede utilizar y/o mejorar siempre que
//                 SE HAGA REFERENCIA AL AUTOR ORIGINAL, ya sea a través de estos comentarios
//                 o de cualquier otro modo.
//
//---------------------------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "conexiones.h"
#include "descarga.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TMainForm *MainForm;


//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   this->Color = (TColor) 0xF2F4F2;

   // truquillo para mostrar en un TImage el icono de la aplicación.
   HICON   icono = (void *) SendMessage(this->Handle, WM_GETICON, ICON_BIG, 0);
   i_icono->Picture->Icon->Handle = icono;

   char buff[256];

   GetTempPath(255, buff);
   e_carpeta->Text = buff;

   m_listaBorrar = new TStringList();
   m_listaBorrar->Duplicates = dupIgnore;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   delete m_listaBorrar;
}



//---------------------------------------------------------------------------
//
// Los distintos hiperenlaces
//
//---------------------------------------------------------------------------
void __fastcall TMainForm::l_jmClick(TObject *Sender)
{
   if ( LinkTo("http://www.lawebdejm.com") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
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
   if ( LinkTo("http://www.grupoalbor.com/Sintesis/Sintesis.htm") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::l_rinconesClick(TObject *Sender)
{
   if ( LinkTo("http://www.lawebdejm.com/prog/win32/") )
      static_cast<TLabel*>(Sender)->Font->Color = clPurple;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_abrirClick(TObject *Sender)
{
   if ( lb_resultado->ItemIndex == -1 )
       return;

   AnsiString  fich = m_listaBorrar->Strings[lb_resultado->ItemIndex];

   ShellExecute(Handle, NULL, fich.c_str(), NULL, NULL, SW_NORMAL);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_descargarClick(TObject *Sender)
{

   TConexiones conexiones;
   AnsiString  destino;

   Screen->Cursor = crHourGlass;
   //
   // Paso 1: abrir una instancia en Wininet;
   //
   HINTERNET  hInternet = ::InternetOpen(
                                  "Pruebas C++ Builder",       // agente
                                  INTERNET_OPEN_TYPE_PRECONFIG,// tipo de acceso
                                  NULL, NULL,                  // proxy y excepciones del proxy
                                  0);                          // opciones
   if ( !hInternet )
   {
      ::MessageBox(GetActiveWindow(), "Error InternetOpen", "Error", MB_ICONERROR);
      Screen->Cursor = crDefault;
      return;
   }

   conexiones.SetInternet(hInternet);

   progreso->Max = lb_url->Items->Count + 1;

   for ( int i = 0; i < lb_url->Items->Count; i++ )
   {
       progreso->Position = i + 1;

       int index = lb_resultado->Items->AddObject("Descargando...", NULL);

       destino = IncludeTrailingBackslash(e_carpeta->Text);

       switch ( Descargar(hInternet, lb_url->Items->Strings[i], conexiones, destino) )
       {
           case -1:
               lb_resultado->Items->Strings[index] = "Error";
               break;

           case 0:
               lb_resultado->Items->Strings[index] = "El recurso no existe";
               break;

           default:
               lb_resultado->Items->Strings[index] = ExtractFileName(destino);
               lb_resultado->Items->Objects[index] = (TObject *) m_listaBorrar->Add(destino);
               break;
       }
       lb_resultado->Repaint();
   }

   progreso->Position = progreso->Max;


   //
   // Cierre de todos los descriptores
   //
   conexiones.DisconnectAll();
   ::InternetCloseHandle(hInternet);


   destino = "Descarga terminada.\n\nPuedes acceder a los archivos descargados en la carpeta \"" + e_carpeta->Text + "\"";
   MessageBox(Handle, destino.c_str(), "Descarga", MB_ICONINFORMATION);

   Screen->Cursor = crDefault;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_anadirClick(TObject *Sender)
{
   AnsiString  ret;

   if ( InputQuery("Añadir URL", "Introduce la URL (http://servidor/ruta/archivo)", ret) )
   {
       if ( ret.Pos("http://") != 1 )
           ret.Insert("http://", 1);

       lb_url->ItemIndex = lb_url->Items->Add(ret);
       b_eliminar->Enabled  = true;
       e_carpeta->Enabled = true;
   }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::b_eliminarClick(TObject *Sender)
{
   if ( lb_url->ItemIndex != -1 )
   {
       lb_url->Items->Delete(lb_url->ItemIndex);
       if ( lb_url->Items->Count == 0 )
       {
           b_eliminar->Enabled = false;
           e_carpeta->Enabled = false;
       }
       lb_url->ItemIndex = 0;
   }
   else
       MessageBox(this->Handle, "Selecciona un elemento de la lista para eliminarlo.", "Eliminar", MB_ICONWARNING);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::lb_urlClick(TObject *Sender)
{
   b_eliminar->Enabled = true;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::Image1Click(TObject *Sender)
{
   AnsiString  dir;
   if ( SelectDirectory("Examinar carpetas", "", dir) )
       e_carpeta->Text = dir;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::lb_resultadoClick(TObject *Sender)
{
   if ( lb_resultado->ItemIndex == -1 )
       return;

   AnsiString  fich = m_listaBorrar->Strings[lb_resultado->ItemIndex];

   //
   // ahora se muestra el archivo resultante y su programa asociado
   //
   char      buff[256];
   HINSTANCE ret = FindExecutable(fich.c_str(), NULL, buff);
   if ( (int) ret > HINSTANCE_ERROR )
   {
      e_asociado->Text = buff;
      b_abrir->Enabled = true;
   }
   else
   {
      e_asociado->Text = "";
      b_abrir->Enabled = false;
   }

   if ( pc_resultado->ActivePage == ts_vista )
       pc_resultadoChange(NULL);
   else
      m_vista->Lines->Clear();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::pc_resultadoChange(TObject *Sender)
{
   if ( lb_resultado->ItemIndex == -1 )
       return;

   if ( pc_resultado->ActivePage == ts_vista && (m_vista->Lines->Text == "" || Sender == NULL))
   {
      AnsiString  fich = m_listaBorrar->Strings[lb_resultado->ItemIndex];
      m_vista->Lines->LoadFromFile(fich);
   }
}
//---------------------------------------------------------------------------

