//----------------------------------------------------------------------//
// コントロールの検索＆マーク/エラー枠									//
//																		//
//----------------------------------------------------------------------//
#include "usr_scale.h"
#include "MarkList.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//	マークリスト (TList から継承)
//---------------------------------------------------------------------------
__fastcall MarkList::MarkList(Classes::TComponent* AOwner): TList()
{
	MarkOwner = (TForm*)AOwner;

	MarkColor = clYellow;
}
//---------------------------------------------------------------------------
__fastcall MarkList::~MarkList()
{
	ClearAll();
}

//---------------------------------------------------------------------------
//マークをすべてクリア
//---------------------------------------------------------------------------
void __fastcall MarkList::ClearAll()
{
	for (int i=0; i<Count; i++) delete Items[i];
	Clear();
}

//---------------------------------------------------------------------------
//コントロールの検索
//キャプションに検索語が含まれるコントロールをマーク
//---------------------------------------------------------------------------
int __fastcall MarkList::SearchControl(TWinControl *ctrl, UnicodeString wd)
{
	int cnt = 0;
	wd = wd.UpperCase();
	double scale = MarkOwner->CurrentPPI / 96.0;

	for (int i=0; i<ctrl->ControlCount; i++) {
		TControl *cp = ctrl->Controls[i];
		if (cp->ClassNameIs("TShape")) continue;

		UnicodeString capstr;
		if 		(cp->ClassNameIs("TLabel"))			capstr = ((TLabel*)cp)->Caption;
		else if (cp->ClassNameIs("TLabeledEdit"))	capstr = ((TLabeledEdit*)cp)->EditLabel->Caption;
		else if (cp->ClassNameIs("TGroupBox"))		capstr = ((TGroupBox*)cp)->Caption;
		else if (cp->ClassNameIs("TCheckBox"))		capstr = ((TCheckBox*)cp)->Caption;
		else if (cp->ClassNameIs("TButton"))		capstr = ((TButton*)cp)->Caption;

		if (ContainsText(capstr, wd)) {
			TShape *sp = new TShape(MarkOwner);
			sp->Parent = NULL;
			sp->Tag = (NativeInt)ctrl;
			TRect rc = cp->BoundsRect;
			InflateRect(rc, 2, 2);

			//※100%を超える場合の補正
			if (scale>1.0) {
				rc.Left   /= scale;
				rc.Top	  /= scale;
				rc.Right  /= scale;
				rc.Bottom /= scale;
			}

			sp->BoundsRect	 = rc;
			sp->Pen->Color	 = MarkColor;
			sp->Pen->Width	 = ScaledInt(2, MarkOwner);
			sp->Brush->Style = bsClear;
			sp->Visible 	 = false;
			Add(sp);
			cnt++;
		}

		TWinControl *wp = dynamic_cast<TWinControl *>(cp);	if (!wp) continue;
		if (wp->ControlCount>0) cnt += SearchControl(wp, wd);
	}
	return cnt;
}

//---------------------------------------------------------------------------
//検索マークを表示
//---------------------------------------------------------------------------
void __fastcall MarkList::ShowMark()
{
	for (int i=0; i<Count; i++) {
		TShape *sp	= Items[i];
		sp->Parent	= (TWinControl*)(sp->Tag);
		sp->Visible = true;
		sp->BringToFront();
	}
}

//---------------------------------------------------------------------------
//エラー枠を表示
//---------------------------------------------------------------------------
void __fastcall MarkList::SetErrFrame(TForm *Owner, TWinControl *cp, bool sw_show)
{
	TShape *sp = NULL;
	for (int i=0; i<Count && !sp; i++) {
		if ((TWinControl*)(Items[i]->Tag)==cp) sp = Items[i];
	}
	if (!sp) {
		sp = new TShape(Owner);
		sp->Tag = (NativeInt)cp;
		sp->Parent = cp->Parent;
		Add(sp);
	}

	TRect rc = cp->BoundsRect;
	int s1 = ScaledInt(1, Owner);
	InflateRect(rc, s1, s1);
	sp->BoundsRect   = rc;
	sp->Pen->Color   = MarkColor;
	sp->Pen->Width   = s1;
	sp->Brush->Style = bsClear;
	sp->Visible		 = sw_show;
	if (sw_show) sp->BringToFront();
}
//---------------------------------------------------------------------------
