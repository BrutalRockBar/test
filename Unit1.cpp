//---------------------------------------------------------------------------
#include <vcl.h>
#include <iostream>
#pragma hdrstop
#include <mmsystem.h>
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
HMIDIIN hMidiIn;
Graphics::TBitmap * bmpDefault;
Graphics::TBitmap * bmp;
int PanelMode = 0;
int PlSt = 0;
int Err = 0;
int KeyDwn;
int KeyRand;
int KeyTimer;


struct TDataBase
{
 struct TStan
 {
  AnsiString Table_name;
  AnsiString nomer_key;
  AnsiString Y_note;
 };

 struct TKey
 {
  AnsiString Table_name;
  AnsiString nomer_key;
  AnsiString kod_sound;
 };

 struct TResult
 {
  AnsiString Table_name;
  AnsiString DT;
  AnsiString PlayTime;
  AnsiString Err;
  AnsiString Speed;
 };
 TStan Skrip;
 TStan Bas;
 TKey Key;
 TResult Result;
};
TDataBase db;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TableSet(void)
{
 db.Skrip.Table_name = "Скрипичный";
 db.Skrip.nomer_key = "Номер клавиши";
 db.Skrip.Y_note = "Координата ноты";

 db.Bas.Table_name = "Басовый";
 db.Bas.nomer_key = "Номер клавиши";
 db.Bas.Y_note = "Координата ноты";

 db.Key.Table_name = "Клавиши";
 db.Key.nomer_key = "Номер клавиши";
 db.Key.kod_sound = "Звук клавиши";

 db.Result.Table_name = "Результаты";
 db.Result.DT = "Дата";
 db.Result.PlayTime = "Продолжительность";
 db.Result.Err = "Ошибок";
 db.Result.Speed = "Скорость";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 MMRESULT rv;
 rv = midiInOpen(&hMidiIn,0,(DWORD)midiCallback,0,CALLBACK_FUNCTION);
	if (rv != MMSYSERR_NOERROR) {
		ShowMessage("midiInOpen() failed...rv=" +rv);
	}

 midiInStart(hMidiIn);

 bmpDefault = new Graphics::TBitmap();
 bmpDefault->Assign(stan->Picture->Graphic);

 TableSet();

 Panel1->Top = 0;
 Panel1->Width = Panel2->Width;
 Panel1->Height = Panel2->Height;
 Panel1->Left = Panel2->Width - 19;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 midiInStop(hMidiIn);
 midiInReset(hMidiIn);
 midiInClose(hMidiIn);
 delete bmpDefault;
}
//---------------------------------------------------------------------------
void CALLBACK midiCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance,
											DWORD dwParam1, DWORD dwParam2)
{
 switch(wMsg) {
   /*	case MIM_OPEN:
		Form1->Memo1->Lines->Add("wMsg=MIM_OPEN");
		break;
	case MIM_CLOSE:
		Form1->Memo1->Lines->Add("wMsg=MIM_CLOSE");
		break;
	case MIM_DATA: */
		//Form1->Memo1->Lines->Add((AnsiString)"wMsg=MIM_DATA, dwInstance="+dwInstance+", dwParam1="+dwParam1+", dwParam2="+dwParam2+"");
		Note(dwParam1);
		break;
   /*	case MIM_LONGDATA:
		Form1->Memo1->Lines->Add("wMsg=MIM_LONGDATA");
		break;
	case MIM_ERROR:
		Form1->Memo1->Lines->Add((AnsiString)"wMsg=MIM_ERROR");
		break;
	case MIM_LONGERROR:
		Form1->Memo1->Lines->Add((AnsiString)"wMsg=MIM_LONGERROR");
		break;
	case MIM_MOREDATA:
		Form1->Memo1->Lines->Add((AnsiString)"wMsg=MIM_MOREDATA");
		break;
	default:
		Form1->Memo1->Lines->Add((AnsiString)"wMsg = unknown");
		break; */
	}
}
//---------------------------------------------------------------------------
void Note(DWORD dwParam1)
{
 char s[20];
 itoa(dwParam1,s,8);
 AnsiString ss = s;
 if(s[6] == '0')
 {
  ss.Delete(1,3);
  ss.Delete(4,2);

  Form1->ADOQuery1->SQL->Text="SELECT * FROM `"+db.Key.Table_name+"` WHERE `"+db.Key.kod_sound+"` LIKE '"+ss.ToInt()+"'";
  Form1->ADOQuery1->Open();
  KeyDwn = Form1->ADOQuery1->FieldByName(db.Key.nomer_key)->AsInteger;
  Form1->ADOQuery1->Close();
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rend(int X, int Y, AnsiString obj)
{
 bmp = new Graphics::TBitmap();

 if(obj == "note") bmp->Assign(note->Picture->Graphic);
 if(obj == "bemol") bmp->Assign(bemol->Picture->Graphic);
 if(obj == "diez") bmp->Assign(diez->Picture->Graphic);
 if(obj == "line") bmp->Assign(line->Picture->Graphic);
 if(obj == "up") bmp->Assign(up->Picture->Graphic);
 if(obj == "down") bmp->Assign(down->Picture->Graphic);

 bmp->TransparentColor = clWhite;
 bmp->Transparent = true;

 stan->Canvas->Draw(X,Y,bmp);

 delete bmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Reload(void)
{
  stan->Canvas->Draw(0,0,bmpDefault);
}
//---------------------------------------------------------------------------
void DrawLine(int X,int Y,AnsiString clef)
{
 int param;   //вверх(1) или вниз(2)
 int XClef;
 
 if(clef == "Скрипичный" && Y < 143)
 {
  param = 1;
  XClef = 143;
 }
 if(clef == "Скрипичный" && Y > 239)
 {
  param = 2;
  XClef = 239;
 }

 
 if(clef == "Басовый" && Y < 338)
 {
  param = 1;
  XClef = 383;
 }
 if(clef == "Басовый" && Y > 479)
 {
  param = 2;
  XClef = 479;
 }
 
 if(param == 1) 
 {
  for(int YLine = XClef; YLine > Y; YLine = YLine - 24)
  {
   Form1->Rend(X - 34,YLine,"line");
  }	 
 }

 if(param == 2) 
 {
  for(int YLine = XClef; YLine <= Y + 24; YLine = YLine + 24)
  {
   Form1->Rend(X - 34,YLine,"line");
  }	 
 }
}
//---------------------------------------------------------------------------
void DrawOktava(int X,int key)
{
 if(key >= 75)
 {
  Form1->Rend(X,0,"up");
 }

 if(key <= 11)
 {
  Form1->Rend(X,570,"down");
 }
}
//---------------------------------------------------------------------------
void DrawTon(int X, int Y, AnsiString ton)
{
 if(ton == "diez")
 {
  Form1->Rend(X - 25,Y - 24,ton);
 }

 if(ton == "bemol")
 {
  Form1->Rend(X - 25,Y - 33,ton);
 }
}
 /*
  ============
  Редактирование:
  AnsiString query_text = "UPDATE `"+db.Table1.Table_name+"` SET `"
								   +db.Table1.XY1_note+"` = '666' WHERE `"
								   +db.Table1.kod_key+"` = '172'";


  ============
  Заполнение таблицы `Скрипичный` номерами клавиш и координатами:
  int Y = 335;
  for(int i = 0; i < Memo1->Lines->Count; i++)
  {
   ADOQuery1->SQL->Text="SELECT * FROM `"+db.Key.Table_name+"` WHERE `"+db.Key.kod_sound+"` LIKE '"+Memo1->Lines->Strings[i]+"'";
   ADOQuery1->Open();
   AnsiString nomer = ADOQuery1->FieldByName(db.Key.nomer_key)->AsString;
   ADOQuery1->Close();

   AnsiString query_text = "INSERT INTO `"+db.Skrip.Table_name+"` ( `"
										 +db.Skrip.nomer_key+"`,`"+db.Skrip.Y_note+"`) VALUES ('"+nomer+"','"+X+"')";
   ADOQuery1->SQL->Text = query_text;
   ADOQuery1->ExecSQL();
   Y = Y - 12;
  }


  ===========
  Заполнение таблицы `Басовый` номерами клавиш и координатами:
  int Y = 623;
  for(int i = 0; i < Memo1->Lines->Count; i++)
  {
  ADOQuery1->SQL->Text="SELECT * FROM `"+db.Key.Table_name+"` WHERE `"+db.Key.kod_sound+"` LIKE '"+Memo1->Lines->Strings[i]+"'";
  ADOQuery1->Open();
  AnsiString nomer = ADOQuery1->FieldByName(db.Key.nomer_key)->AsString;
  ADOQuery1->Close();

  AnsiString query_text = "INSERT INTO `"+db.Bas.Table_name+"` ( `"
										 +db.Bas.nomer_key+"`,`"+db.Bas.Y_note+"`) VALUES ('"+nomer+"','"+X+"')";
  ADOQuery1->SQL->Text = query_text;
  ADOQuery1->ExecSQL();
  Y = Y - 12;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 if(Panel1->Left >= 100)
 {
  Panel1->Left = Panel1->Left - 100;
 }

 if(Panel1->Left <= 100)
 {
  Timer1->Enabled = false;
  Panel1->Left = 0;
  PanelMode = 1;
  Image1->Picture->Bitmap = a2->Picture->Bitmap;
  ADOTable1->Active = true;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
 if(Panel1->Left <= Panel2->Width - 100)
 {
  Panel1->Left = Panel1->Left + 100;
 }

 if(Panel1->Left >= Panel2->Width - 100)
 {
  Timer2->Enabled = false;
  Panel1->Left = Panel2->Width - 19;
  PanelMode = 0;
  Image1->Picture->Bitmap = a1->Picture->Bitmap;
  ADOTable1->Active = false;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image2Click(TObject *Sender)
{
 this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseEnter(TObject *Sender)
{
 Image2->Picture->Bitmap = Xb->Picture->Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseLeave(TObject *Sender)
{
 Image2->Picture->Bitmap = Xa->Picture->Bitmap;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Image1Click(TObject *Sender)
{
  if(PanelMode == 0) Form1->Timer1->Enabled = true;
  else Form1->Timer2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseEnter(TObject *Sender)
{
 if(PanelMode == 0) Image1->Picture->Bitmap = b1->Picture->Bitmap;
 else Image1->Picture->Bitmap = b2->Picture->Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseLeave(TObject *Sender)
{
 if(PanelMode == 0) Image1->Picture->Bitmap = a1->Picture->Bitmap;
 else Image1->Picture->Bitmap = a2->Picture->Bitmap;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Random(void)
{
 Reload();

 int key;
 int X = 120 + rand() % (420-120);
 int Y;

 //ключ
 int clef = 1 + rand() % 2;

 //клавиша и её координата по Y
 if(clef == 1) //басовый
 {
  ADOQuery1->SQL->Text = "SELECT * FROM `"+db.Bas.Table_name+"`";
  ADOQuery1->Open();
  ADOQuery1->RecNo = 1 + rand() % 32;
  key = ADOQuery1->FieldByName(db.Bas.nomer_key)->AsInteger;
  Y = ADOQuery1->FieldByName(db.Bas.Y_note)->AsInteger;
  ADOQuery1->Close();

  DrawLine(X,Y,"Басовый");
 }
 else  //скрипичный
 {
  ADOQuery1->SQL->Text = "SELECT * FROM `"+db.Skrip.Table_name+"`";
  ADOQuery1->Open();
  ADOQuery1->RecNo = 1 + rand() % 35;
  key = ADOQuery1->FieldByName(db.Skrip.nomer_key)->AsInteger;
  Y = ADOQuery1->FieldByName(db.Skrip.Y_note)->AsInteger;
  ADOQuery1->Close();

  DrawLine(X,Y,"Скрипичный");
 }

 Rend(X,Y,"note");
 DrawOktava(X,key);

 //тон
 switch(rand() % 3) {
	case 1:
		 DrawTon(X, Y, "bemol");
		 key--;
		break;
	case 2:
		 DrawTon(X, Y, "diez");
		 key++;
		break;
	}
  KeyRand = key;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
 if(KeyTimer != KeyDwn)
 {
  if(KeyDwn == KeyRand)
  {
   Random();
   Err = 0;
  }
  else if(Err != 1)   //ошибся нотой
  {
   Err = 1;
   ADOQuery1->SQL->Text="UPDATE `"+db.Result.Table_name+"` SET `"+db.Result.Err+"` = `"+db.Result.Err+"` + 1 WHERE `"+db.Result.DT+"` = (SELECT MAX(`"+db.Result.DT+"`) FROM `"+db.Result.Table_name+"`)";
   ADOQuery1->ExecSQL();
  }
  KeyTimer = KeyDwn;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StartStop(AnsiString mode)
{
 if(mode == "Start")
 {
  PlayStop->Picture->Bitmap = s1->Picture->Bitmap;
  PlSt = 1;
  Err = 0;

  Random();
  Timer3->Enabled = true;

   AnsiString query_text = "INSERT INTO `"+db.Result.Table_name+"` ( `"
										 +db.Result.DT+"`) VALUES ('"+Now().FormatString("DD.MM.YYYY hh:nn:ss")+"')";
   ADOQuery1->SQL->Text = query_text;
   ADOQuery1->ExecSQL();
 }

 if(mode == "Stop")
 {
  PlayStop->Picture->Bitmap = p1->Picture->Bitmap;
  PlSt = 0;

  Timer3->Enabled = false;
  Reload();
 }
}




void __fastcall TForm1::PlayStopClick(TObject *Sender)
{
 if(PlSt == 0)StartStop("Start");
 else StartStop("Stop");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PlayStopMouseEnter(TObject *Sender)
{
 if(PlSt == 0) PlayStop->Picture->Bitmap = p1->Picture->Bitmap;
 else PlayStop->Picture->Bitmap = s1->Picture->Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PlayStopMouseLeave(TObject *Sender)
{
 if(PlSt == 0) PlayStop->Picture->Bitmap = p2->Picture->Bitmap;
 else PlayStop->Picture->Bitmap = s2->Picture->Bitmap;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::ClearBtnClick(TObject *Sender)
{
  if(Application->MessageBoxW(L"Все сохранённые данные будут удалены. Продолжить?",L"Удаление результатов",MB_YESNO) == IDYES)
  {
   ADOTable1->Active = false;
   ADOQuery1->SQL->Text = "DELETE FROM `"+db.Result.Table_name+"`";
   ADOQuery1->ExecSQL();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearBtnMouseEnter(TObject *Sender)
{
 ClearBtn->Picture->Bitmap = ClearBtn2->Picture->Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearBtnMouseLeave(TObject *Sender)
{
 ClearBtn->Picture->Bitmap = ClearBtn1->Picture->Bitmap;
}
//---------------------------------------------------------------------------


