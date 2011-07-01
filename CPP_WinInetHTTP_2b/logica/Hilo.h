#if !defined(AFX_HILO_H__336280D3_A5BD_4FB6_9802_0DA2E86FB018__INCLUDED_)
#define AFX_HILO_H__336280D3_A5BD_4FB6_9802_0DA2E86FB018__INCLUDED_

#include <windows.h>
#include <windef.h>

class Hilo  
{
public:
	Hilo();
	virtual ~Hilo();

	void cancelar();
	void pausar();
	void arrancar();
	void iniciar(bool parado);
	bool esperarHastaQueMuera(DWORD timeout = INFINITE);

protected:
	static DWORD WINAPI _funcionHilo(LPVOID param);
	virtual DWORD funcionHilo();

	bool getCancelado() const;
	void setCancelado(bool value);

private:
	HANDLE hHilo;
	DWORD  idHilo;

	bool cancelado;
};

#endif
