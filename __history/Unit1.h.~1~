//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <VCLTee.TeeFilters.hpp>
#include <Vcl.Graphics.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.Buttons.hpp>
#include <IdAntiFreezeBase.hpp>
#include <IdBaseComponent.hpp>
#include <Vcl.IdAntiFreeze.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *note;
	TImage *bemol;
	TImage *diez;
	TImage *line;
	TImage *up;
	TImage *down;
	TADOQuery *ADOQuery1;
	TTimer *Timer1;
	TTimer *Timer2;
	TImage *fon;
	TImage *Image2;
	TImage *Xa;
	TImage *a1;
	TImage *b1;
	TImage *a2;
	TImage *b2;
	TImage *Xb;
	TPanel *Panel2;
	TImage *stan;
	TPanel *Panel1;
	TImage *Image1;
	TTimer *Timer3;
	TDataSource *DataSource1;
	TADOTable *ADOTable1;
	TDBGrid *DBGrid1;
	TImage *PlayStop;
	TImage *p1;
	TImage *p2;
	TImage *s1;
	TImage *s2;
	TImage *ClearBtn;
	TImage *ClearBtn2;
	TImage *ClearBtn1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Rend(int X, int Y, AnsiString obj);
	void __fastcall Reload(void);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall Image2MouseEnter(TObject *Sender);
	void __fastcall Image2MouseLeave(TObject *Sender);
	void __fastcall Image1MouseEnter(TObject *Sender);
	void __fastcall Image1MouseLeave(TObject *Sender);
	void __fastcall Random(void);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall PlayStopClick(TObject *Sender);
	void __fastcall PlayStopMouseEnter(TObject *Sender);
	void __fastcall PlayStopMouseLeave(TObject *Sender);
	void __fastcall StartStop(AnsiString mode);
	void __fastcall ClearBtnClick(TObject *Sender);
	void __fastcall ClearBtnMouseEnter(TObject *Sender);
	void __fastcall ClearBtnMouseLeave(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

void TableSet(void);
void Note(DWORD dwParam1);
void DrawLine(int X,int Y,AnsiString clef);
void DrawOktava(int X,int key);
void DrawTon(int X, int Y, AnsiString ton);


void CALLBACK midiCallback(HMIDIIN hMidiIn, UINT wMsg,
					DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
