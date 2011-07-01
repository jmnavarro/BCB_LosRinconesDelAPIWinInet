//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("PruebasWininetHTTP.res");
USEFORM("main.cpp", MainForm);
USEFORM("opciones.cpp", OpcionesFrm);
USEUNIT("descarga.cpp");
USELIB("C:\Prog\CBuilder5\Lib\wininet.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
                    try
                    {
                                         Application->Initialize();
                                         Application->Title = "Pruebas con Wininet y HTTP";
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
