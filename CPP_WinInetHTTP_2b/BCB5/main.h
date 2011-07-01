//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

class HiloDescarga;
//---------------------------------------------------------------------------

class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TImage *i_icono;
	TLabel *l_wininet;
	TLabel *l_sintesis;
	TLabel *l_jm;
	TShape *s_borde;
	TLabel *l_rincones;
	TPanel *p_funciones;
	TLabel *Label2;
	TBevel *Bevel1;
	TPanel *Panel1;
	TImage *Image1;
	TListBox *lb_url;
	TButton *b_eliminar;
	TEdit *e_carpeta;
	TButton *b_descargar;
	TProgressBar *progreso;
	TLabel *Label1;
	TListBox *lb_log;
	TBevel *Bevel2;
	TPanel *Panel2;
	TEdit *e_url;
	void __fastcall b_descargarClick(TObject *Sender);
	void __fastcall lb_urlClick(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall l_wininetClick(TObject *Sender);
	void __fastcall l_sintesisClick(TObject *Sender);
	void __fastcall l_rinconesClick(TObject *Sender);
	void __fastcall l_jmClick(TObject *Sender);
	void __fastcall b_eliminarClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
	HiloDescarga *hilo;
	bool descargando;
	bool cancelando;

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	__fastcall ~TMainForm();

	void ParadaDescarga();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
