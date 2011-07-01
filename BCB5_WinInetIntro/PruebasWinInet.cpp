//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("PruebasWinInet.res");
USEFORM("Ejecutar.cpp", EjecutarFrame); /* TFrame: File Type */
USEFORM("main.cpp", MainForm);
USELIB("wininet.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                                         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
