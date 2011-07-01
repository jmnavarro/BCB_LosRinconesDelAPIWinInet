//---------------------------------------------------------------------------------------------
//
// Archivo: main.cpp
//
// Propósito:
//    Implementación del formulario principal con las pruebas de marcado del módem y gestión
//    de cookies.
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

#include "main.h"
#include <RasError.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Ejecutar"
#pragma resource "*.dfm"


TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner){ }


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   // truquillo para mostrar en un TImage el icono de la aplicación.
   HICON   icono = (void *) SendMessage(this->Handle, WM_GETICON, ICON_BIG, 0);
   i_icono->Picture->Icon->Handle = icono;

   this->Color = (TColor) 0xF2F4F2;

   FLabelFunciones[0] = l_url;
   FLabelFunciones[1] = l_conexion;

   FLabelActiva = FLabelFunciones[0];


   InitFunciones();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InitFunciones()
{
   AutodialFrame->Init(InetAutodial);
   DialFrame->Init(InetDial);
   AutodialHangupFrame->Init(InetAutodialHangup);
   HangupFrame->Init(InetHangup);
   SetCookieFrame->Init(InetSetCookie);
   GetCookieFrame->Init(InetGetCookie);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::CambioFunciones(TObject *Sender)
{
   if (FLabelActiva == Sender)
       return;

   int encontrado = -1;

   for (int i = 0; i < 2; i++)
       if (FLabelFunciones[i] == Sender)
       {
           encontrado = i;
           break;
       }

   if (-1 == encontrado)
       return;

   //
   // restaurar la anterior
   //
   FLabelActiva->Cursor = crHandPoint;
   FLabelActiva->Font->Color = clBlue;

   //
   // cambiar la nueva activa
   //
   FLabelActiva = FLabelFunciones[encontrado];

   FLabelActiva->Cursor = crDefault;
   FLabelActiva->Font->Color = clBlack;

   //
   // Mover el shape
   //
   sh_funcion->Top = FLabelActiva->Top - 6;
   p_aux->Top = sh_funcion->Top + 1;

   pc_funciones->ActivePageIndex = encontrado;
}



//---------------------------------------------------------------------------
//
// Los distintos hyperenlaces
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
   if ( LinkTo("http://users.servicios.retecal.es/sapivi/prog/cpp/wininetintro.html") )
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
//
// Aquí empiezan los eventos Execute de las distintas acciones
//
//---------------------------------------------------------------------------
void __fastcall TMainForm::InetAutodialExecute(TObject *Sender)
{
   const static DWORD s_autodialFlags[] = {
           INTERNET_AUTODIAL_FORCE_ONLINE,
           INTERNET_AUTODIAL_FORCE_UNATTENDED
   };

   DWORD   flags = 0;

   Screen->Cursor = crHourGlass;
   __try
   {
       for(int i = 0; i < 2; i++)
           if (AutodialFlags->Checked[i])
               flags |= s_autodialFlags[i];

       if ( ::InternetAutodial(flags, this->Handle) )
            static_cast<TAction*>(Sender)->Tag = 1;
        else
            static_cast<TAction*>(Sender)->Tag = ::GetLastError();
   }
   __finally {
      Screen->Cursor = crDefault;
   }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InetAutodialHangupExecute(TObject *Sender)
{
   if ( ::InternetAutodialHangup(0) )
       static_cast<TAction*>(Sender)->Tag = 1;
   else
       static_cast<TAction*>(Sender)->Tag = ::GetLastError();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InetDialExecute(TObject *Sender)
{
   const static DWORD s_dialFlags[] = {
           INTERNET_AUTODIAL_FORCE_ONLINE,
           INTERNET_AUTODIAL_FORCE_UNATTENDED,
           INTERNET_DIAL_FORCE_PROMPT,
           INTERNET_DIAL_UNATTENDED,
           INTERNET_DIAL_SHOW_OFFLINE
   };

   DWORD   flags = 0;
   for( int i=0; i < 5; i++ )
       if ( DialFlags->Checked[i] )
           flags |= s_dialFlags[i];

   DWORD   id;
   DWORD   ret = ::InternetDial(this->Handle, NULL, flags, &id, 0);

   switch (ret)
   {
       case ERROR_SUCCESS:
          static_cast<TAction*>(Sender)->Tag = 1;
          e_idConn->Text = IntToStr(id);
          break;

       case ERROR_INVALID_PARAMETER:
          static_cast<TAction*>(Sender)->Tag = 0;
          e_idConn->Text = "";
          DialFrame->l_retorno->Caption = "Parámetro incorrecto";
          break;

       case ERROR_USER_DISCONNECTION:
          static_cast<TAction*>(Sender)->Tag = 0;
          e_idConn->Text = "";
          DialFrame->l_retorno->Caption = "Se ha pulsado \"Cancelar\" o \"Trabajar sin conexión\"";
          break;

       default:
          static_cast<TAction*>(Sender)->Tag = ::GetLastError();
          e_idConn->Text = "";
          break;
   }
   e_idConn2->Text = e_idConn->Text;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InetHangupExecute(TObject *Sender)
{
   DWORD   id;
   if ( 0 == e_idConn2->Text.Length() )
       id = 0;
   else
      id = StrToInt(e_idConn2->Text);

   if ( ERROR_SUCCESS == ::InternetHangUp(id, 0) )
       static_cast<TAction*>(Sender)->Tag = 1;
   else
       static_cast<TAction*>(Sender)->Tag = ::GetLastError();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InetSetCookieExecute(TObject *Sender)
{
       char  buff[256];
       char  cookieBuff[256];

       wsprintf(cookieBuff, "%s=%s; expires=Sat, 01-Mar-2010 01:00:00 GTM",
                            e_variable->Text.c_str(),
                            e_valor->Text.c_str() );

       if ( ::InternetSetCookie(e_urlSetCookie->Text.c_str(), NULL, cookieBuff) )
           static_cast<TAction*>(Sender)->Tag = 1;
       else
           static_cast<TAction*>(Sender)->Tag = ::GetLastError();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::InetGetCookieExecute(TObject *Sender)
{

   lb_variables->Items->Clear();

   //
   // hago una llamada inicial para saber el número de bytes necesarios
   //
   DWORD tam = 0;

   ::InternetGetCookie(e_urlGetCookie->Text.c_str(), NULL, NULL, &tam);

   //
   // ahora en tam tengo los bytes necesarios
   //
   char * buff = new char[tam];

   if ( ::InternetGetCookie(e_urlGetCookie->Text.c_str(), NULL, buff, &tam) )
   {
       char *variable = buff;
       char *valor;
       char *sep;
       char linea[256];

       do
       {
           valor = strchr(variable, '=');
           *valor = '\0';
           valor++;

           sep = strchr(valor, ';');
           if ( sep )
               *sep = '\0';

           // quitar los posibles espacios iniciales
           while (' ' == *variable) ++variable;
           while (' ' == *valor   ) ++valor;

           wsprintf(linea, "%s\t%s", variable, valor);
           lb_variables->Items->Add(linea);

           variable = sep + (sep ? 1 : 0);

       } while (variable);

       static_cast<TAction*>(Sender)->Tag = 1;
   }
   else
       static_cast<TAction*>(Sender)->Tag = ::GetLastError();

   //
   // libero el buffer dinámico
   //
   delete [] buff;
}
//---------------------------------------------------------------------------

