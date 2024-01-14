//----------------------------------------------------------------------//
// ファイルフィルタ処理クラス											//
//----------------------------------------------------------------------//
#include "usr_str.h"
#include "file_filter.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//フィルタ情報文字列を取得
//---------------------------------------------------------------------------
UnicodeString GetFilterInfStr(UnicodeString filter, bool is_grep)
{
	UnicodeString ret_str;
	if (!filter.IsEmpty()) {
		TStringDynArray flts = SplitString(filter, '|');
		TRegExOptions re_opt; re_opt << roIgnoreCase;
		for (int i=0; i<flts.Length; i++) {
			UnicodeString f = Trim(flts[i]);
			//Head
			TMatch mt = TRegEx::Match(f, "^Head\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2) {
				int n = mt.Groups.Item[1].Value.ToIntDef(0);
				if (n>0) {
					cat_separator(ret_str, " | ");
					ret_str.cat_sprintf(_T("先頭から%u行"), n);
					continue;
				}
			}
			//Tail
			mt = TRegEx::Match(f, "^Tail\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2) {
				int n = mt.Groups.Item[1].Value.ToIntDef(0);
				if (n>0) {
					cat_separator(ret_str, " | ");
					ret_str.cat_sprintf(_T("最後から%u行"), n);
					continue;
				}
			}

			//HtmlHead
			if (SameText(f, "HtmlHead")) {
				ins_sep_cat(ret_str, " | ", "head要素行");
				continue;
			}
			//HtmlBody
			if (SameText(f, "HtmlBody")) {
				ins_sep_cat(ret_str, " | ", "body要素行");
				continue;
			}

			//HtmlRe
			if (SameText(f, "HtmlRem")) {
				ins_sep_cat(ret_str, " | ", (is_grep? "コメント" : "コメント行"));
				continue;
			}

			//SubStr
			mt = TRegEx::Match(f, "^SubStr\\((\\d+)(?:,\\s?(\\d+))?\\)$", re_opt);
			if (is_grep && mt.Success && mt.Groups.Count>1) {
				int idx = mt.Groups.Item[1].Value.ToIntDef(0);
				int len = (mt.Success && mt.Groups.Count==3)? mt.Groups.Item[2].Value.ToIntDef(0) : 0;
				if (idx>0) {
					cat_separator(ret_str, " | ");
					if (len>0)
						ret_str.cat_sprintf(_T("%u文字目から%u文字"), idx, len);
					else
						ret_str.cat_sprintf(_T("%u文字目以降"), idx);
					continue;
				}
			}

			//DfmObj
			mt = TRegEx::Match(f, "^DfmObj\\(([\\w\\*\\?]+),\\s?([\\w\\*\\?]+)\\)$", re_opt);
			if (is_grep && mt.Success && mt.Groups.Count==3) {
				cat_separator(ret_str, " | ");
				ret_str.cat_sprintf(_T(".dfm - %s.%s"),
						mt.Groups.Item[1].Value.c_str(), mt.Groups.Item[2].Value.c_str());
				continue;
			}

			cat_separator(ret_str, "  ");
			ret_str.cat_sprintf(_T("!ERR:[%s]"), f.c_str());
			break;
		}
	}
	return ret_str;
}

//---------------------------------------------------------------------------
//フィルタ指定のチェック
//---------------------------------------------------------------------------
bool TestFilter(UnicodeString filter, bool is_grep)
{
	bool ok = true;

	if (!filter.IsEmpty()) {
		TStringDynArray flts = SplitString(filter, '|');
		TRegExOptions re_opt; re_opt << roIgnoreCase;
		for (int i=0; i<flts.Length; i++) {
			UnicodeString f = Trim(flts[i]);
			//Head
			TMatch mt = TRegEx::Match(f, "^Head\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2 && mt.Groups.Item[1].Value.ToIntDef(0)>0) continue;
			//Tail
			mt = TRegEx::Match(f, "^Tail\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2 && mt.Groups.Item[1].Value.ToIntDef(0)>0) continue;

			if (SameText(f, "HtmlHead")) continue;
			if (SameText(f, "HtmlBody")) continue;
			if (SameText(f, "HtmlRem"))  continue;

			//SubStr
			mt = TRegEx::Match(f, "^SubStr\\((\\d+)(?:,\\s?(\\d+))?\\)$", re_opt);
			if (is_grep && mt.Success && mt.Groups.Count>1 && mt.Groups.Item[1].Value.ToIntDef(0)>0) continue;

			//DfmObj
			mt = TRegEx::Match(f, "^DfmObj\\(([\\w\\*\\?]+),\\s?([\\w\\*\\?]+)\\)$", re_opt);
			if (is_grep && mt.Success && mt.Groups.Count==3) continue;

			//Error
			ok = false;
			break;
		}
	}

	return ok;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// FileFilter クラス
//---------------------------------------------------------------------------
FileFilter::FileFilter()
{
	topLine    = 0;
	endLine    = 0;
	strIndex   = 0;
	strLength  = 0;
}

//---------------------------------------------------------------------------
FileFilter::~FileFilter()
{
}

//---------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------
bool FileFilter::Initialize(UnicodeString fnam, TStringList *fbuf, UnicodeString filter, FilterOption opt)
{
	FileBuff   = fbuf;
	Filter     = filter;
	topLine    = 0;
	endLine    = FileBuff->Count - 1;
	strIndex   = 0;
	strLength  = 0;
	objType    = EmptyStr;
	propName   = EmptyStr;
	isGrep     = opt.Contains(foIsGrep);
	excludeTag = opt.Contains(foExcludeTag);

	int ng_cnt = 0;
	if (!Filter.IsEmpty()) {
		TStringDynArray flts = SplitString(Filter, '|');
		TRegExOptions re_opt; re_opt << roIgnoreCase;
		for (int i=0; i<flts.Length; i++) {
			UnicodeString f = Trim(flts[i]);
			//Head
			TMatch mt = TRegEx::Match(f, "^Head\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2) {
				int n = mt.Groups.Item[1].Value.ToIntDef(0);
				if (n>0) {
					endLine = std::clamp(topLine + n - 1, 0, FileBuff->Count - 1);
					continue;
				}
			}
			//Tail
			mt = TRegEx::Match(f, "^Tail\\((\\d+)\\)$", re_opt);
			if (mt.Success && mt.Groups.Count==2) {
				int n = mt.Groups.Item[1].Value.ToIntDef(0);
				if (n>0) {
					topLine = std::clamp(endLine - n + 1, 0, FileBuff->Count - 1);
					continue;
				}
			}

			//HtmlHead
			if (SameText(f, "HtmlHead")) {
				GetBlockRange("head");	continue;
			}
			//HtmlBody
			if (SameText(f, "HtmlBody")) {
				GetBlockRange("body");	continue;
			}

			//HtmlComment
			if (SameText(f, "HtmlRem")) {
				SetHtmlComent();		continue;
			}

			//SubStr
			mt = TRegEx::Match(f, "^SubStr\\((\\d+)(?:,\\s?(\\d+))?\\)$", re_opt);
			if (isGrep && mt.Success && mt.Groups.Count>1) {
				int idx = mt.Groups.Item[1].Value.ToIntDef(0);
				int len = (mt.Success && mt.Groups.Count==3)? mt.Groups.Item[2].Value.ToIntDef(0) : 0;
				if (idx>0) {
					strIndex  = idx;
					strLength = len;
					continue;
				}
			}

			//DfmObj
			mt = TRegEx::Match(f, "DfmObj\\(([\\w\\*\\?]+),\\s?([\\w\\*\\?]+)\\)", re_opt);
			if (isGrep && mt.Success && mt.Groups.Count==3) {
				objType  = mt.Groups.Item[1].Value;
				propName = mt.Groups.Item[2].Value;
				continue;
			}

			ng_cnt++;
		}
	}

	return (ng_cnt==0);
}

//---------------------------------------------------------------------------
//指定タグ要素行を抽出
//---------------------------------------------------------------------------
bool FileFilter::GetBlockRange(UnicodeString tag)
{
	UnicodeString bgn_ptn = "<" + tag + "[\\s>]?";
	UnicodeString end_ptn = "</" + tag + ">";
	int lp1 = -1;
	int lp2 = -1;
	TRegExOptions opt; opt << roIgnoreCase;
	for (int lp=0; lp<FileBuff->Count; lp++) {
		UnicodeString lbuf = FileBuff->Strings[lp];
		if (TRegEx::IsMatch(lbuf, bgn_ptn, opt)) {
			lp1 = lp;
		}
		if (lp1!=-1 && ContainsText(lbuf, end_ptn)) {
			lp2 = lp;
			break;
		}
	}

	if (lp1>0 && lp2>=lp1) {
		topLine = lp1;
		endLine = lp2;
		return true;
	}
	else {
		return false;
	}
}

//---------------------------------------------------------------------------
//HTMLコメント行情報を設定
//---------------------------------------------------------------------------
void FileFilter::SetHtmlComent()
{
	bool in_rem = false;
	for (int lp=0; lp<FileBuff->Count; lp++) {
		UnicodeString lbuf = FileBuff->Strings[lp];
		int p1 = 0;
		int p2 = 0;
		if (!in_rem) {
			p1 = lbuf.Pos("<!--");
			if (p1>0) {
				in_rem = true;
				p2 = lbuf.Pos("-->");
				if (p2>p1) {
					p2 += 2;
					in_rem = false;
				}
				else {
					p2 = lbuf.Length();
				}
			}
		}
		else {
			p1 = 1;
			p2 = lbuf.Pos("-->");
			if (p2>=p1) {
				p2 += 2;
				in_rem = false;
			}
			else {
				p2 = lbuf.Length();
			}
		}

		//コメントを含む行
		if (p1>0 && p2>=p1) {
			if (isGrep)
				FileBuff->Objects[lp] = (TObject*)((NativeInt)MAKELONG(p1, p2 - p1 + 1));
			else
				FileBuff->Objects[lp] = (TObject*)((NativeInt)MAKELONG(1, lbuf.Length()));
		}
		//コメントではない
		else {
			FileBuff->Objects[lp] = (TObject*)((NativeInt)MAKELONG(1, 0));
		}
	}
}

//---------------------------------------------------------------------------
//行内容の取得
//  戻り値: 検索対象となる文字列
//---------------------------------------------------------------------------
UnicodeString FileFilter::GetLinePart(
	int idx, 
	int &r_idx, 			//[o] 開始位置
	int &r_len, 			//[o] 長さ
	UnicodeString &lbuf)	//[o] 表示用行内容
{
	r_idx = strIndex;
	r_len = strLength;
	UnicodeString sbuf;

	if (idx>=0 && idx<FileBuff->Count) {
		lbuf = FileBuff->Strings[idx];
		if (excludeTag) lbuf = TRegEx::Replace(lbuf, "^([^<]+>)|(<[^<>]+>)|(<[^>]+)$", EmptyStr);
		sbuf = lbuf;

		//行毎に設定された範囲指定
		DWORD p = (DWORD)FileBuff->Objects[idx];
		if (p>0) {	//設定有り
			if (HIWORD(p)>0) {
				r_idx = LOWORD(p);
				r_len = HIWORD(p);
				if (strIndex>0) {
					r_idx += (strIndex - 1);
					r_len -= (strIndex - 1);
					r_len = std::min(r_len, strLength);
				}
			}
			else {
				sbuf = EmptyStr;
			}
		}

		if (r_idx>0) {
			sbuf = sbuf.SubString(r_idx, (r_len>0)? r_len : sbuf.Length() - r_idx + 1);
		}
	}
	else {
		lbuf  = EmptyStr;
		r_len = 0;
	}

	return sbuf;
}
//---------------------------------------------------------------------------
//表示用行内容を取得
//---------------------------------------------------------------------------
UnicodeString FileFilter::GetDispLine(int idx)
{
	UnicodeString lbuf;
	if (idx>=0 && idx<FileBuff->Count) {
		lbuf = FileBuff->Strings[idx];
		if (excludeTag) lbuf = TRegEx::Replace(lbuf, "^([^<]+>)|(<[^<>]+>)|(<[^>]+)$", EmptyStr);
	}
	return lbuf;
}
//---------------------------------------------------------------------------
//検索対象行か？
//---------------------------------------------------------------------------
bool FileFilter::IsValidLine(int idx)
{
	bool ret = false;
	if (idx>=0 && idx<FileBuff->Count) {
		DWORD p = (DWORD)FileBuff->Objects[idx];
		if (p>0) {	//設定有り
			ret = (HIWORD(p)>0);
		}
		else {
			ret = true;
		}
	}
	return ret;
}
//---------------------------------------------------------------------------