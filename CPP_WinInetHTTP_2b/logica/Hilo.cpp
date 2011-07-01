#include "Hilo.h"


Hilo::Hilo()
{
	hHilo = 0;
	idHilo = 0;
	cancelado = false;
}


Hilo::~Hilo()
{
}


void Hilo::cancelar()
{
	cancelado = true;
}


void Hilo::pausar()
{
	SuspendThread(hHilo);
}


void Hilo::arrancar()
{
	ResumeThread(hHilo);
}


void Hilo::iniciar(bool parado)
{
	DWORD flag = parado ? CREATE_SUSPENDED : 0;
	hHilo = CreateThread(NULL, 0, _funcionHilo, this, flag, &idHilo);
}


bool Hilo::esperarHastaQueMuera(DWORD timeout /*=INFINITE*/)
{
	return (WAIT_OBJECT_0 == WaitForSingleObject(hHilo, timeout));
}


DWORD WINAPI Hilo::_funcionHilo(LPVOID param)
{
	Hilo *obj = reinterpret_cast<Hilo*> (param);

	return obj->funcionHilo();
}


DWORD Hilo::funcionHilo()
{
	return 0;
}


bool Hilo::getCancelado() const
{
	return cancelado;
}


void Hilo::setCancelado(bool value)
{
	cancelado = value;
}
