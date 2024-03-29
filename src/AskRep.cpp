//----------------------------------------------------------------------//
// NyanFi																//
//  置換確認ダイアログ													//
//----------------------------------------------------------------------//
#include "UserFunc.h"
#include "Global.h"
#include "AskRep.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAskRepDlg *AskRepDlg = NULL;

//---------------------------------------------------------------------
__fastcall TAskRepDlg::TAskRepDlg(TComponent* AOwner)
	: TForm(AOwner)
{
	FoundPos = FoundLine = 0;
	CurIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::FormCreate(TObject *Sender)
{
	ListScrPanel = new UsrScrollPanel(ListPanel, RepListBox, USCRPNL_FLAG_P_WP | USCRPNL_FLAG_L_WP);
}
//---------------------------------------------------------------------
void __fastcall TAskRepDlg::FormShow(TObject *Sender)
{
	IniFile->LoadPosInfo(this, DialogCenter);

	set_ListBoxItemHi(RepListBox, GrepResFont);
	set_UsrScrPanel(ListScrPanel);
	RepListBox->Color = get_ListBgCol();
	ListScrPanel->UpdateKnob();

	AssignScaledFont(StatusBar1, ViewHdrFont);
	StatusBar1->Height = get_FontHeightMgnS(StatusBar1->Font, 4, 4);
	StatusBar1->Panels->Items[0]->Text = yen_to_delimiter(FileName).cat_sprintf(_T(" - %u行 %u桁"), FoundLine, FoundPos);
	StatusBar1->Panels->Items[1]->Text = UnicodeString().sprintf(_T(" File %u/%u"), FileIndex + 1, FileCount);

	OKBtn->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
	IniFile->SavePosInfo(this);
}
//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::FormDestroy(TObject *Sender)
{
	delete ListScrPanel;
}

//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::FormResize(TObject *Sender)
{
	RepListBox->Invalidate();
	StatusBar1->Panels->Items[0]->Width = ClientWidth - SCALED_THIS(120);
}

//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	SpecialKeyProc(this, Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::StatusBar1DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
	const TRect &Rect)
{
	TCanvas *cv = StatusBar->Canvas;
	cv->Font->Assign(StatusBar->Font);
	cv->Brush->Color = get_InfHdrBgCol();
	cv->FillRect(Rect);
	cv->Font->Color  = get_InfHdrFgCol();
	cv->TextOut(Rect.Left + SCALED_THIS(2), Rect.Top, Panel->Text);
}

//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::RepListBoxDrawItem(TWinControl *Control,
		int Index, TRect &Rect, TOwnerDrawState State)
{
	TListBox *lp = (TListBox*)Control;
	TCanvas  *cv = lp->Canvas;
	cv->Font->Assign(lp->Font);

	cv->Brush->Color = get_ListBgCol();
	cv->FillRect(Rect);

	UnicodeString itmstr = lp->Items->Strings[Index];
	int xp = Rect.Left + SCALED_THIS(2);
	int yp = Rect.Top  + get_TopMargin(cv);

	//行番号
	TRect rc = Rect;
	int f_idx = FoundLine - CurIndex + Index - 1;
	LineNoOut(cv, rc, f_idx + 1);
	cv->Brush->Color = get_ListBgCol();
	xp = rc.Left + SCALED_THIS(4);

	//マッチ行
	if (Index==CurIndex) {
		cv->Font->Color = get_ListFgCol();
		if (FoundPos>0) {
			//マッチ語前
			UnicodeString s0 = itmstr.SubString(1, FoundPos - 1);
			int wd = Rect.Width() - xp;
			if (cv->TextWidth(s0 + KeyWord) > wd) {
				int p1 = FoundPos;
				wd /= 2;
				int w_r = cv->TextWidth(itmstr.SubString(p1, itmstr.Length() - p1 + 1));
				if (w_r<wd) wd += (wd - w_r);
				wd -= cv->TextWidth("… ");
				int w = 0;
				for (int i=p1; i>4; i--) {
					w += cv->TextWidth(itmstr.SubString(i, 1));
					if (w<wd) continue;
					s0.Delete(1, i);
					s0.Insert("…", 1);
					break;
				}
			}
			TabCrTextOut(s0, cv, xp, yp, get_ListFgCol(), Rect.Right);
			itmstr.Delete(1, FoundPos - 1);
			//マッチ語強調表示
			TxtOutOption opt;  opt << toOnlyTop;
			EmphasisTextOutEx(itmstr, KeyWord, cv, xp, yp, opt, col_fgEmp, col_bgEmp);
		}
		else {
			TabCrTextOut(itmstr, cv, xp, yp, get_ListFgCol(), Rect.Right);
		}

		//カーソル線
		int lw = std::max(CursorWidth, 1);
		int yp = Rect.Bottom - lw;
		draw_Line(cv, Rect.Left, yp, Rect.Right, yp, lw, col_Cursor);
	}
	//前後行
	else {
		TabCrTextOut(itmstr, cv, xp, yp, (f_idx>=TopIndex && f_idx<=EndIndex)? get_ListFgCol() : col_InvItem, Rect.Right);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAskRepDlg::RepListBoxEnter(TObject *Sender)
{
	OKBtn->SetFocus();
}
//---------------------------------------------------------------------------
