//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ReanudarWinInet.res");
USEFORM("main.cpp", MainForm);
USEUNIT("HiloDescargaEventosBCB5.cpp");
USEUNIT("..\logica\HiloDescarga.cpp");
USEUNIT("..\logica\Hilo.cpp");
USELIB("wininet.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Reanudar la descarga con WinInet";
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
