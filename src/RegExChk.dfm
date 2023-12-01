object RegExChecker: TRegExChecker
  Left = 0
  Top = 0
  HelpContext = 85
  BorderIcons = [biSystemMenu]
  Caption = #27491#35215#34920#29694#12481#12455#12483#12459#12540
  ClientHeight = 400
  ClientWidth = 625
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  Position = poDesigned
  ShowHint = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  TextHeight = 15
  object Splitter1: TSplitter
    Left = 380
    Top = 0
    Width = 5
    Height = 400
    Align = alRight
    AutoSnap = False
    MinSize = 60
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 380
    Height = 400
    Align = alClient
    BevelOuter = bvNone
    BorderWidth = 4
    Constraints.MinWidth = 376
    TabOrder = 0
    object Splitter2: TSplitter
      Left = 4
      Top = 254
      Width = 372
      Height = 5
      Cursor = crVSplit
      Align = alTop
      AutoSnap = False
      MinSize = 60
      ExplicitTop = 248
    end
    object OpePanel: TPanel
      Left = 4
      Top = 4
      Width = 372
      Height = 250
      Align = alTop
      BevelOuter = bvNone
      Constraints.MinHeight = 220
      TabOrder = 0
      DesignSize = (
        372
        250)
      object TLabel
        Left = 35
        Top = 7
        Width = 41
        Height = 15
        Alignment = taRightJustify
        Caption = #12497#12479#12540#12531
      end
      object TLabel
        Left = 4
        Top = 138
        Width = 52
        Height = 15
        Caption = #26908#32034#23550#35937
      end
      object StxPaintBox: TPaintBox
        Left = 83
        Top = 26
        Width = 201
        Height = 22
        Anchors = [akLeft, akTop, akRight]
        OnPaint = StxPaintBoxPaint
      end
      object Bevel1: TBevel
        Left = 0
        Top = 121
        Width = 372
        Height = 4
        Anchors = [akLeft, akTop, akRight]
        Shape = bsBottomLine
      end
      object CaseCheckBox: TCheckBox
        Left = 290
        Top = 33
        Width = 80
        Height = 17
        Anchors = [akTop, akRight]
        Caption = #22823#23567#21306#21029
        TabOrder = 2
      end
      object CCopyBtn: TButton
        Tag = 1
        Left = 86
        Top = 92
        Width = 114
        Height = 24
        Action = CopyCAction
        Anchors = [akTop, akRight]
        Caption = #12467#12500#12540'(C'#25991#23383#21015')'
        TabOrder = 5
      end
      object MatchBtn: TButton
        Left = 288
        Top = 3
        Width = 80
        Height = 24
        Action = TestAction
        Anchors = [akTop, akRight]
        Default = True
        TabOrder = 1
      end
      object PtnComboBox: TComboBox
        Left = 80
        Top = 4
        Width = 204
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        DropDownCount = 20
        TabOrder = 0
        StyleElements = [seClient, seBorder]
        OnChange = PtnComboBoxChange
      end
      object ReplaceBtn: TButton
        Left = 288
        Top = 60
        Width = 80
        Height = 24
        Action = ReplaceAction
        Anchors = [akTop, akRight]
        TabOrder = 4
      end
      object ReplaceEdit: TLabeledEdit
        Left = 80
        Top = 60
        Width = 204
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 65
        EditLabel.Height = 23
        EditLabel.Caption = #32622#25563#25991#23383#21015
        LabelPosition = lpLeft
        PopupMenu = UserModule.EditPopupMenuE
        TabOrder = 3
        Text = ''
        StyleElements = [seClient, seBorder]
      end
      object CopyBtn: TButton
        Left = 204
        Top = 92
        Width = 80
        Height = 24
        Action = CopyAction
        Anchors = [akTop, akRight]
        TabOrder = 6
      end
      object PasteBtn: TButton
        Left = 288
        Top = 92
        Width = 80
        Height = 24
        Action = PasteAction
        Anchors = [akTop, akRight]
        ModalResult = 1
        TabOrder = 7
      end
      object ObjMemo: TMemo
        Left = 0
        Top = 162
        Width = 372
        Height = 88
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Lines.Strings = (
          '')
        ScrollBars = ssVertical
        TabOrder = 11
        StyleElements = [seFont, seBorder]
      end
      object FileEdit: TLabeledEdit
        Left = 120
        Top = 133
        Width = 124
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 37
        EditLabel.Height = 23
        EditLabel.Caption = #12501#12449#12452#12523
        LabelPosition = lpLeft
        TabOrder = 8
        Text = ''
      end
      object RefFileBtn: TButton
        Left = 248
        Top = 134
        Width = 36
        Height = 22
        Anchors = [akTop, akRight]
        Caption = '...'
        TabOrder = 9
        OnClick = RefFileBtnClick
      end
      object UpdtCheckBox: TCheckBox
        Left = 290
        Top = 136
        Width = 78
        Height = 17
        Anchors = [akTop, akRight]
        Caption = #22793#26356#21453#26144
        TabOrder = 10
      end
    end
    object ResPanel: TPanel
      Left = 4
      Top = 259
      Width = 372
      Height = 137
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object ResultLabel: TLabel
        Left = 4
        Top = 6
        Width = 26
        Height = 15
        Caption = #32080#26524
      end
      object ResListBox: TListBox
        Left = 0
        Top = 26
        Width = 372
        Height = 111
        Style = lbOwnerDrawFixed
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        ItemHeight = 13
        TabOrder = 1
        TabWidth = 40
        StyleElements = [seFont, seBorder]
        OnDrawItem = ResListBoxDrawItem
      end
      object DetailCheckBox: TCheckBox
        Left = 204
        Top = 4
        Width = 65
        Height = 17
        Caption = #35443#32048
        TabOrder = 0
        OnClick = DetailCheckBoxClick
      end
    end
  end
  object ReferPanel: TPanel
    Left = 385
    Top = 0
    Width = 240
    Height = 400
    Align = alRight
    BevelOuter = bvLowered
    BorderWidth = 4
    TabOrder = 1
    object Splitter3: TSplitter
      Left = 5
      Top = 225
      Width = 230
      Height = 5
      Cursor = crVSplit
      Align = alTop
      ExplicitTop = 145
    end
    object ReferListBox: TListBox
      Left = 5
      Top = 5
      Width = 230
      Height = 220
      Align = alTop
      BorderStyle = bsNone
      ItemHeight = 15
      TabOrder = 0
      TabWidth = 36
      OnDblClick = ReferListBoxDblClick
    end
    object HiddenCanBtn: TButton
      Left = 5
      Top = 395
      Width = 230
      Height = 0
      Align = alBottom
      Cancel = True
      ModalResult = 2
      TabOrder = 1
      TabStop = False
    end
    object SampleListBox: TListBox
      Tag = 1
      Left = 5
      Top = 230
      Width = 230
      Height = 165
      Align = alClient
      BorderStyle = bsNone
      ItemHeight = 15
      PopupMenu = PopupMenu1
      TabOrder = 2
      TabWidth = 36
      OnDblClick = ReferListBoxDblClick
    end
  end
  object ActionList1: TActionList
    Left = 440
    Top = 16
    object TestAction: TAction
      Caption = #12486#12473#12488
      OnExecute = TestActionExecute
      OnUpdate = TestActionUpdate
    end
    object ReplaceAction: TAction
      Caption = #32622#25563
      OnExecute = ReplaceActionExecute
      OnUpdate = ReplaceActionUpdate
    end
    object PasteAction: TAction
      Caption = #36028#12426#20184#12369'(&P)'
      OnExecute = PasteActionExecute
      OnUpdate = PasteActionUpdate
    end
    object CopyAction: TAction
      Caption = #12467#12500#12540'(&C)'
      OnExecute = CopyActionExecute
      OnUpdate = CopyActionUpdate
    end
    object CopyCAction: TAction
      Tag = 1
      Caption = #12467#12500#12540'(C'#29992#25991#23383#21015')'
      OnExecute = CopyActionExecute
      OnUpdate = CopyActionUpdate
    end
    object LoadSamplAction: TAction
      Caption = #12501#12449#12452#12523#12363#12425#35501#12415#36796#12416'(&L)...'
      OnExecute = LoadSamplActionExecute
    end
    object EditSampleAction: TAction
      Caption = #32232#38598'(&E)'
      OnExecute = EditSampleActionExecute
      OnUpdate = EditSampleActionUpdate
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 441
    Top = 264
    object LoadSampleItem: TMenuItem
      Action = LoadSamplAction
    end
    object EditSampleItem: TMenuItem
      Action = EditSampleAction
    end
  end
end
