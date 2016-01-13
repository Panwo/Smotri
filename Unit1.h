//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ExtCtrls.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N5;
        TMenuItem *N10;
        TMenuItem *N11;
        TPanel *Panel1;
        TDirectoryListBox *DirectoryListBox1;
        TPanel *Panel2;
        TPanel *Panel3;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N15;
        TStatusBar *StatusBar1;
        TOpenDialog *OpenDialog1;
        TPanel *Panel4;
        TDriveComboBox *DriveComboBox1;
        TSaveDialog *SaveDialog1;
        TMenuItem *N14;
        TMenuItem *N16;
        TMenuItem *N17;
        TPanel *Panel5;
        TEdit *Edit1;
        TLabel *Label1;
        TTimer *Timer1;
        TPanel *Panel6;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        TSpeedButton *SpeedButton9;
        TSpeedButton *SpeedButton10;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TMenuItem *N6;
        TPanel *Panel7;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TFileListBox *FileListBox1;
        TSpeedButton *SpeedButton11;
        TSpeedButton *SpeedButton12;
        TPanel *Panel8;
        TSpeedButton *SpeedButton13;
        TMenuItem *N8;
        void __fastcall N5Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FileListBox1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall FileListBox1Change(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall N17Click(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall SpeedButton9Click(TObject *Sender);
        void __fastcall SpeedButton10Click(TObject *Sender);
        void __fastcall N15Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall FileListBox1Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall SpeedButton11Click(TObject *Sender);
        void __fastcall SpeedButton12Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall SpeedButton13Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
private:	// User declarations
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR  gdiplusToken;

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
