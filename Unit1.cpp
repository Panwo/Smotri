//---------------------------------------------------------------------------
#define NO_WIN32_LEAN_AND_MEAN
#include <vcl.h>
#include <windows.h>
#include <clipbrd.hpp>
#include <shellapi.h>
using namespace std;
#define STRICT
#include <algorithm>

#include <gdiplus.h>
#include "Gdiplusgraphics.h"
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma comment(lib, "gdiplus.lib")
#pragma resource "*.dfm"
TForm1 *Form1;
using std::min;
using std::max;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
AnsiString helpfile;
float z_min=0;
float z_max=0;
int x;
Graphics::TBitmap *B=new Graphics::TBitmap;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
GdiplusStartup (& gdiplusToken,& gdiplusStartupInput, NULL); //èíèöèàëèçðóåì  gdiplus
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------



void zoom_up (float zmax)    //ôóíêöèÿ ìàñøòàáèðîâàíèÿ óâåëè÷åíèÿ êàðòèíêè
{
 Graphics::TBitmap *BUF;       //ñîçäàíèå è èíèöàëèçàöèÿ ðàáî÷åãî bitmap-à
BUF = new Graphics::TBitmap();
BUF->Width=int(Form1->Image1->Picture->Width*zmax); //ðàñ÷åò è óñòàíîâêà ðàçìåðîâ áèòìàïà
BUF->Height=int(Form1->Image1->Picture->Height*zmax);
BUF->Canvas->StretchDraw(TRect(0,0,BUF->Width,BUF->Height),B);   //ïðîðèñîâêà
if ((Form1->Image1->Width>=BUF->Width)||(Form1->Image1->Height>=BUF->Height)  )//ïîçèöèîíèðîâàíèå è
// ìàñøòàáèðîâàíèå îáëàñòè îòîáðàæåíèÿ êàðòèíêêè
{Form1->Image1->Align=alClient;}
if (Form1->Image1->Width<BUF->Width){Form1->Image1->Align=alNone; Form1->Image1->Width=BUF->Width;}
if (Form1->Image1->Height<BUF->Height){Form1->Image1->Align=alNone; Form1->Image1->Height=BUF->Height;}
Form1->Image1->Picture->Graphic=BUF;    //ïðîðèñîâêà  êàðòèíêè
Form1->Image1->Refresh();    //îáíîâëåíèå êàðòèíêè
delete BUF;    //î÷èñòêà ïàìÿòè
}



void zoom_down (float zmin)     //ôóíêöèÿ ìàñøòàáèðîâàíèÿ óìåíüøåíèÿ êàðòèíêè
//àíàëîãè÷íà ôóíêöèè óâåëè÷åíèÿ êðîìå ðàñ÷åòà íîâûõ ðàçìåðîâ èçîáðàæåíèÿ
{ Graphics::TBitmap *BUF;
BUF = new Graphics::TBitmap();
BUF->Width=int(Form1->Image1->Picture->Width/zmin);
BUF->Height=int(Form1->Image1->Picture->Height/zmin);
BUF->Canvas->StretchDraw(TRect(0,0,BUF->Width,BUF->Height),B);
if ((Form1->Image1->Width>=BUF->Width)||(Form1->Image1->Height>=BUF->Height)  )
{Form1->Image1->Align=alClient;}
if (Form1->Image1->Width<BUF->Width){Form1->Image1->Align=alNone; Form1->Image1->Width=BUF->Width;}
if (Form1->Image1->Height<BUF->Height){Form1->Image1->Align=alNone; Form1->Image1->Height=BUF->Height;}
Form1->Image1->Picture->Graphic=BUF;
Form1->Image1->Refresh();
delete BUF;
}



//  ôóíêöèÿ îòêðûòèÿ ôàéëà äëÿ ïðîñìîòðà ñ âõîäÿùèì ïàðàìåòðîì - èìåíåì îòêðûâàåìîãî ãðàôè÷åñêîãî ôàéëà
void BrouseFile(AnsiString FN)
{   float ho=0;
float wo;
if (FN!=""){//åñëè èìÿ ôàéëà óêàçàíî òî âûïîëíèòü äåéñòâèÿ
Form1->Image1->Align=alClient;//ðàçâîðà÷èâàåì îáëàñòü ïðîñìîòðà íà âñþ äîñòóïíþ ïëîùàäü
Form1->Image1->Picture->Assign(0);//î÷èùàåì îáëàñòü ïðîñìîòðà
WCHAR buff[10001];
Graphics::TBitmap *Buf = new Graphics::TBitmap();//ñîçäàåì îáúåêò êëàññà TBitmap
Gdiplus::Image *image =new Gdiplus::Image (FN.WideChar(buff,10000)); //ñîçäàåì îáúåêò êëàññà Gdiplus::Image è çàãðóæàåì â íåãî èçîáðàæåíèå èç âûáðàííîãî ôàéëà
Buf->Width=image->GetWidth();//óêàçûâàåì øèðèíó è âûñîòó èçîáðàæåíèÿ
Buf->Height=image->GetHeight();
Gdiplus::Graphics graphics(Buf->Canvas->Handle);//ïåðåäàåì óêàçàòåëü íà îáúåêò Buf
graphics.DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());
//ïðîðèñîâûâàåì âçÿòîå èç ôàéëà èçîáðàæåíèå â îáúåêòå Buf
Form1->Image1->Picture->Assign(Buf);//âûâîäì ïðîðèñîâàííîå èçîáðàæåíèå â îáëàñòü ïðîñìîòðà
Form1->ScrollBox1->Refresh();//îáíîâëÿåì ðàçìåðíîñòü îáëàñòè ïðîñìîòðà
z_min=1;//èíèöèàëèçèðåì ïåðåìåííûå ìàñøàáèðîâàíèÿ
z_max=1;

Form1->StatusBar1->Panels->Items[1]->Text="Ôàéë - "+Form1->FileListBox1->Items->Strings[Form1->FileListBox1->ItemIndex];//âûâîäèì ñëóæåáíóþ èíôîðìàöèþ
Form1->StatusBar1->Panels->Items[2]->Text="Ðàçìåð - "+IntToStr(image->GetWidth())+"x"+IntToStr(image->GetHeight());
//
B->Assign(0);//î÷èùàåì ðåçåðâíûé îáúåêò êëàññà TBitmap
B->Width=Form1->Image1->Picture->Bitmap->Width;//çàäàåì ðàçìåðû ðåçåðâíîãî îáúåêòà
B->Height=Form1->Image1->Picture->Bitmap->Height;
B->Canvas->Draw(0,0,Form1->Image1->Picture->Bitmap);//ïðîðèñîâûâàåì èçîáðàæåíèå â ðåçåðâíîì îáúåêòå èç îáëàñòè ïðîñìîòðà
          //åñëè êàðòèíêà èçíà÷àëüíî áîëüøå îáëàñòè ïðîñìîòðà
          //òî îíà áóäåò àâòîìàòè÷åñêè óìåíüøåíà
          //äàëåå îïðåäåëÿåì êîýô. óìåíüøåíèÿ
 if ((B->Height>Form1->Image1->Height)||(B->Width>Form1->Image1->Width))  //åñëè ïàðìåòðû êàðòèíêè ïðåâûøàþò ïàðàìåòðû îáëàñòè
{
ho=float(Form1->Image1->Height)/float(B->Height);   //âû÷èñëÿåì ñîîòíîøåíèÿ âåëè÷èí
wo=float(Form1->Image1->Width)/float(B->Width);
if (ho>wo)   //îïåðåäåëÿåì áîëüøóþ èç âåëè÷èí, ÷òîáû èçîáðàæåíèå ïîìåñòèëîñü â îáëàñòè ïðîñìîòðà
{z_min=1+ho;}    //óñòàíàâëèâàåì êîýô.
else {z_min=1+wo;}
}
delete image;//î÷èùàåì ïàìÿòü
delete Buf;

}
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
helpfile=ExtractFilePath(Application->ExeName)+"help.htm";

Image1->Picture->Assign(0); //î÷èñòêà îáëàñòè ïðîñìîòðà
FileListBox1->ItemIndex=0;  //ïåðåõîä ê ïåðâîìó ôàéëó â ñïèñêå
if (FileListBox1->Items->Count>0) BrouseFile(FileListBox1->FileName); //åñëè â ñïèñêå åñòü ôàéëû îòêðûâàåì ïåðâûé
StatusBar1->Panels->Items[3]->Text="Ðåæèì - ïðîñìîòð ôàéëîâ"; //âûâîä ñëóæåáíîé èíôîðìàöèè
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FileListBox1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==VK_DOWN) {   //åñëè áûëà íàæàòà êëàâèøà êóðñîðà "âíèç"
if (FileListBox1->ItemIndex==FileListBox1->Items->Count-1) //åñëè òåêóùàÿ ïîçèöèÿ â ñïèñêå ôàéëîâ ïîñëåäíÿÿ
{FileListBox1->ItemIndex=0;}   //òî ïåðåõîäèì ê ïåðâîé
}

if (Key==VK_UP){   //åñëè áûëà íàæàòà êëàâèøà êóðñîðà "ââåðõ"
if(FileListBox1->ItemIndex==0)         //åñëè òåêóùàÿ ïîçèöèÿ â ñïèñêå ôàéëîâ ïåðâàÿ
 {FileListBox1->ItemIndex=FileListBox1->Items->Count-1;}        //òî ïåðåõîäì íà ïîñëåäíþþ
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
if (FileListBox1->ItemIndex+1==FileListBox1->Items->Count)
{FileListBox1->ItemIndex=0;} else {FileListBox1->ItemIndex=FileListBox1->ItemIndex+1;}
BrouseFile(FileListBox1->FileName);
x= FileListBox1->ItemIndex;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
if (FileListBox1->ItemIndex==0)//åñëè âûáðàí ïåðâûé ôàéë ñïèñêà
{FileListBox1->ItemIndex=FileListBox1->Items->Count-1;}//òî ïåðåõîäèì ê ïîñëåäíåìó ôàéëó ñïèñêà
else {//åñëè òåêóùèé ôàéë íå ïåðâûé â ñïèñêå
FileListBox1->ItemIndex=FileListBox1->ItemIndex-1; }//òî âîçâðàùàåìñÿ ê ïðåäûäóùåìó
BrouseFile(FileListBox1->FileName);//îòêðûâàåì äëÿ ïðîñìîòðà âûáðàííûé ôàéë
x= FileListBox1->ItemIndex;}//çàïîìèíàåì òåêóùóþ ïîçèöèþ â ñïèñêå ôàéëîâ

//---------------------------------------------------------------------------




void __fastcall TForm1::N3Click(TObject *Sender)
{OpenDialog1->Execute();  //àêòèâàöèÿ äèàëîãà îòêðûòèÿ
if (OpenDialog1->FileName!=""){   //åñëè ôàéë âûáðàí âûïîëíèòü äåéñòâèÿ
DirectoryListBox1->FileList=0;     //îòêëþ÷åíèå àâòîìàòè÷åñêîãî ñîçäàíèÿ ñïèñêà
FileListBox1->Items->Add(OpenDialog1->FileName);//äîáàâëåíèå â ñïèñîê âûáðàííîãî ôàéëà
FileListBox1->ItemIndex=FileListBox1->Items->Count-1;//ïåðåõîä ê ïîñëåäíåìó ôàéëó â ñïèñêå
BrouseFile(OpenDialog1->FileName);//ïðîðèñîâêà âûáðàííîãî ôàéëà
DirectoryListBox1->FileList=FileListBox1;//ïîäêëþ÷åíèå àâòîìàòè÷åñêîãî ñîçäàíèÿ ñïèñêà
}}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1Change(TObject *Sender)
{
StatusBar1->Panels->Items[0]->Text="Êîëè÷åñòâî ôàéëîâ â ïàïêå - "+IntToStr(FileListBox1->Items->Count);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
ShowMessage("Paramonov V.D");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){
z_min=z_min+0.1;    //âû÷èñëåíèå êîýô. óìåíøåíèÿ
zoom_down(z_min); //âûïîëíåíèå óìåíüøåíèÿ êàðòèíêè è åå ïðîðèñîâêà
z_max=1;// ñáðîñ êîýô. óâåëè÷åíèÿ
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
delete B; 
Gdiplus::GdiplusShutdown(gdiplusToken);  //îòêëþ÷åíèå  Gdiplus
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)  //àíàëîã ôóíêöèè óìåíüøåíèÿ
{
if (FileListBox1->ItemIndex>=0){
z_max=z_max+0.1;
zoom_up(z_max);
z_min=1;
 }
}
//---------------------------------------------------------------------------
void rotation () //ôóíêöèÿ ïîâîðîòà êàðòèíêè
{
Graphics::TBitmap *SB=new Graphics::TBitmap; //îáúÿâëåíèå ðàáî÷èõ áèòìàïîâ
Graphics::TBitmap *DB=new Graphics::TBitmap;
SB->Assign(Form1->Image1->Picture->Bitmap);  //çàãðóçêà òåêóùåãî èçîáðàæåíèÿ èç îáëàñòè ïðîñìîòðà
DB->Width=SB->Height;     //óñòàíîâêà ðàçìåðîâ êàðòèíêè ïîñëå ïîâîðîòà
DB->Height=SB->Width;
//âûïîëíåíèå ïîâîðîòà îñóùåñòâëÿåòñÿ ïîïèêñåëüíîé ïðîðèñîâêîé
for (int x=0;x<SB->Width;x++)
{
  for(int y=0;y<SB->Height;y++)
  {
    DB->Canvas->Pixels[y][SB->Width-1-x]=
       SB->Canvas->Pixels[x][y];
  }
}
Form1->Image1->Picture->Bitmap=DB;  //ïðîðèñîâêà ïîâåðíóòîî èçîáðàæåíèÿ â îáëàñòè ïðîñìîòðà
delete DB;         //î÷èñòêà ïàìÿòè
delete SB;
}

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){ rotation ();}  //âûçîâ ôóíêöèè ïîâîðîòà êàðòèíêè
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N17Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){ rotation ();}  //âûçîâ ôóíêöèè ïîâîðîòà êàðòèíêè
    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
if (FileListBox1->ItemIndex+1==FileListBox1->Items->Count)
{FileListBox1->ItemIndex=0;} else {FileListBox1->ItemIndex=FileListBox1->ItemIndex+1;}
BrouseFile(FileListBox1->FileName);
x= FileListBox1->ItemIndex;      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N16Click(TObject *Sender)
{
if (FileListBox1->ItemIndex==0)//åñëè âûáðàí ïåðâûé ôàéë ñïèñêà
{FileListBox1->ItemIndex=FileListBox1->Items->Count-1;}//òî ïåðåõîäèì ê ïîñëåäíåìó ôàéëó ñïèñêà
else {//åñëè òåêóùèé ôàéë íå ïåðâûé â ñïèñêå
FileListBox1->ItemIndex=FileListBox1->ItemIndex-1; }//òî âîçâðàùàåìñÿ ê ïðåäûäóùåìó
BrouseFile(FileListBox1->FileName);//îòêðûâàåì äëÿ ïðîñìîòðà âûáðàííûé ôàéë
x= FileListBox1->ItemIndex;}//çàïîìèíàåì òåêóùóþ ïîçèöèþ â ñïèñêå ôàéëîâ
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
if ((Key < '0' || Key > '9') && Key != 8) Key= 0;  //ðàçðåøàåì ââîäèòü òîëüêî öèôðû      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
if (FileListBox1->Items->Count>0){  //åñëè â ñïèñêå åñòü èìåíà ôàéëîâ
Panel5->Visible=true;  //îòêðûâàåì ïàíåëü ñ íàñòðîéêà àâòîïðîñìîòðà è ñêðûâàåì íåíóæíûå
Panel6->Visible=false;
Panel1->Enabled=false;
x=0;
 StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð";  //âûâîä ñëóæåáíîé èíôîðìàöèè
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{ 
if (FileListBox1->Items->Count>0){  //åñëè â ñïèñêå åñòü ôàéëû
if (FileListBox1->Items->Count>=x){ //óñòàíàâëèâàåì óêàçàòåëü íà ôàéë ñîãëàñíî íàñòðîéêå ñòàðòà àâòîïðîñìîòðà
FileListBox1->ItemIndex=x;
BrouseFile(FileListBox1->FileName); //îòîáðàæàåì âûáðàííûé ôàéë
x++;  //èíêðåìèíèðóåì ñ÷åò÷èê
if (FileListBox1->Items->Count<x)   //åñëè äîøëè äî êîíöà ñïèñêà îñòàíàâëèâàåìñÿ
{StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð";
Timer1->Enabled=false;}
}     
else {      //åñëè â ñïèñêå ôàéëîâ íåò îòìåíÿåì çàïóñê àâòîïðñîìòðà
Timer1->Enabled=false;
StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð";}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
if (StrToInt(Edit1->Text)>0) {  //åñëè âðåìÿ ñìåíû êàðòèíîê ââåäåíî âåðíî
Timer1->Interval=int(StrToInt(Edit1->Text)*1000); //óñòàíàâëèâàåì ââåäåííîå âðåìÿ
Timer1->Enabled=true;   //çàïóñêàåì òàéìåð
StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð [ïóñê]"; //âûâîäèì ñëóæåáíóþ èíôîðìàöèÿþ
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{  //îñòàíàâëèâàåì òàéìåð
Timer1->Enabled=false;
//ñêðûâàåì ïàíåëü íàñòðîåê àâòîïðîñìîòðà è îòêðûâàåì ïàíåëè ñ êíîïêàìè ôóíêöèé
Panel5->Visible=false;
Panel6->Visible=true;
Panel1->Enabled=true;
StatusBar1->Panels->Items[3]->Text="Ðåæèì - ïðîñìîòð ôàéëîâ"; //âûâîä ñëóæ. èíô.
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{   //îñòàíàâëèâàåì òàéìåð åñëè îí çàïóùåí èëè çàïóñêàåì åñëè ñòîèò è âûâîä ñëóæåáíóþ èíôîðìàöèþ
if (Timer1->Enabled==true) {Timer1->Enabled=false;StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð [ïàóçà]";} else {Timer1->Enabled=true;StatusBar1->Panels->Items[3]->Text="Ðåæèì - àâòîïðîñìîòð [ïóñê]";}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N15Click(TObject *Sender)
{

ShellExecute(0,0,helpfile.c_str(), NULL, NULL, SW_SHOW);//çàïóñêàåì ôàéë ñïðàâêè ïî óêàçàííîìó àäðåñó
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
x=0;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
x=FileListBox1->ItemIndex;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
BrouseFile(FileListBox1->FileName);        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N6Click(TObject *Sender)
{ AnsiString tip="";//îáúÿâëåíèå è èíèöèàëèçàöèÿ ïåðåìåííîé ñîäåðæàùåé òèï ñîõðàíÿåìîãî ôàéëà
SaveDialog1->Execute();//àêòèâàöèÿ äèàëîãà ñîõðàíåíèÿ
if (SaveDialog1->FileName!="")//åñëè èìÿ ôàéëà ââåäåíî âûïîëíèòü äåéñòâèÿ
{ switch (SaveDialog1->FilterIndex)//îïðåäåëÿåì òèï âûáðàííîãî ðàñøèðåíèÿ èç ñïèñêà ðàñøèðåíèé
{case 1: {tip=".bmp"; break;}
case 2: {tip=".ico"; break;}
case 3: {tip=".gif"; break;}
case 4: {tip=".jpg"; break;}
case 5: {tip=".png"; break;}
case 6: {tip=".emf"; break;}
case 7: {tip=".tiff"; break;}
case 8: {tip=".wmf"; break;}
}
Image1->Picture->SaveToFile(SaveDialog1->FileName+tip);//ñîõðàíÿåì èçîáðàæåíèå ñ óêàçàííûì èìåíåì è ðàñøèðåíèåì
}}

//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){
z_max=z_max+0.1;
zoom_up(z_max);
z_min=1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){
z_min=z_min+0.1;    //âû÷èñëåíèå êîýô. óìåíøåíèÿ
zoom_down(z_min); //âûïîëíåíèå óìåíüøåíèÿ êàðòèíêè è åå ïðîðèñîâêà
z_max=1;// ñáðîñ êîýô. óâåëè÷åíèÿ
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton11Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){  //åñëè åñòü âûáðàííûé ôàéë
Clipboard()->Assign(Image1->Picture->Bitmap);  //êîïèðîâàíèå â áóôåð
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton12Click(TObject *Sender)
{  //âñòàâêà èç áóôåðà åñëè òàì êàðòèíêà
if (Clipboard()->HasFormat(CF_PICTURE)) Image1->Picture->Bitmap->Assign(Clipboard());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
if (FileListBox1->ItemIndex>=0){  //åñëè åñòü âûáðàííûé ôàéë
Clipboard()->Assign(Image1->Picture->Bitmap);  //êîïèðîâàíèå â áóôåð
}}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton13Click(TObject *Sender)
{
 Application->Terminate();    //çàêðûâàåì ïðèëîæåíèå    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
 //âñòàâêà èç áóôåðà åñëè òàì êàðòèíêà
if (Clipboard()->HasFormat(CF_PICTURE)) Image1->Picture->Bitmap->Assign(Clipboard());
}
//---------------------------------------------------------------------------

