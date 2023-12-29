object GitGrepForm: TGitGrepForm
  Left = 0
  Top = 0
  ClientHeight = 445
  ClientWidth = 630
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  ShowHint = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  TextHeight = 15
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 630
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object HiddenCanBtn: TButton
      Left = 630
      Top = 0
      Width = 0
      Height = 34
      Align = alRight
      Cancel = True
      ModalResult = 2
      TabOrder = 2
      TabStop = False
    end
    object TopRightPanel: TPanel
      Left = 304
      Top = 0
      Width = 326
      Height = 34
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object CaseCheckBox: TCheckBox
        Left = 101
        Top = 9
        Width = 89
        Height = 17
        Caption = #22823#23567#21306#21029
        TabOrder = 1
      end
      object RegExCheckBox: TCheckBox
        Left = 8
        Top = 9
        Width = 89
        Height = 17
        Caption = #27491#35215#34920#29694
        TabOrder = 0
        OnClick = RegExCheckBoxClick
      end
      object StartBtn: TButton
        Left = 200
        Top = 5
        Width = 66
        Height = 25
        Action = GrepStartAction
        Default = True
        TabOrder = 2
      end
    end
    object TopLeftPanel: TPanel
      Left = 0
      Top = 0
      Width = 304
      Height = 34
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        304
        34)
      object Label1: TLabel
        Left = 16
        Top = 10
        Width = 65
        Height = 15
        Alignment = taRightJustify
        Caption = #26908#32034#25991#23383#21015
      end
      object FindComboBox: TComboBox
        Left = 85
        Top = 6
        Width = 204
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        ImeMode = imClose
        TabOrder = 0
        OnKeyDown = FindComboBoxKeyDown
        OnKeyPress = FindComboBoxKeyPress
      end
    end
  end
  object ResultPanel: TPanel
    Left = 0
    Top = 68
    Width = 630
    Height = 377
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object ResultListBox: TListBox
      Left = 0
      Top = 0
      Width = 630
      Height = 358
      Style = lbVirtualOwnerDraw
      Align = alLeft
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderStyle = bsNone
      Color = clBlack
      PopupMenu = PopupMenu1
      TabOrder = 0
      StyleElements = [seBorder]
      OnData = ResultListBoxData
      OnDrawItem = ResultListBoxDrawItem
      OnEnter = ResultListBoxEnter
      OnKeyDown = ResultListBoxKeyDown
      OnKeyPress = ResultListBoxKeyPress
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 358
      Width = 630
      Height = 19
      Panels = <
        item
          Width = 240
        end
        item
          Width = 50
        end>
    end
  end
  object OptPanel: TPanel
    Left = 0
    Top = 34
    Width = 630
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object OptLeftPanel: TPanel
      Left = 0
      Top = 0
      Width = 304
      Height = 34
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        304
        34)
      object Label2: TLabel
        Left = 20
        Top = 9
        Width = 61
        Height = 15
        Alignment = taRightJustify
        Caption = '-- pathspec'
      end
      object PathComboBox: TComboBox
        Left = 85
        Top = 5
        Width = 204
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        ImeMode = imClose
        TabOrder = 0
      end
    end
  end
  object ActionList1: TActionList
    Left = 40
    Top = 88
    object GrepStartAction: TAction
      Caption = #38283#22987
      OnExecute = GrepStartActionExecute
      OnUpdate = GrepStartActionUpdate
    end
    object ViewFileAction: TAction
      Caption = #12371#12398#12501#12449#12452#12523#12398#20869#23481#12434#34920#31034'(&V)...'
      OnExecute = ViewFileActionExecute
      OnUpdate = ViewFileActionUpdate
    end
    object EditFileAction: TAction
      Caption = #12486#12461#12473#12488#12456#12487#12451#12479#12391#38283#12367'(&E)'
      OnExecute = EditFileActionExecute
      OnUpdate = EditFileActionUpdate
    end
    object ClipCopyAction: TAction
      Caption = #26908#32034#32080#26524#12434#12463#12522#12483#12503#12508#12540#12489#12395#12467#12500#12540'(&C)'
      OnExecute = ClipCopyActionExecute
      OnUpdate = ResultActionUpdate
    end
    object LineCopyAction: TAction
      Caption = #12459#12540#12477#12523#34892#12434#12463#12522#12483#12503#12508#12540#12489#12395#12467#12500#12540'(&L)'
      OnExecute = LineCopyActionExecute
      OnUpdate = ResultActionUpdate
    end
    object SaveAsAction: TAction
      Caption = #26908#32034#32080#26524#12395#21517#21069#12434#20184#12369#12390#20445#23384'(&A)...'
      OnExecute = SaveAsActionExecute
      OnUpdate = ResultActionUpdate
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 144
    Top = 92
    object ClipCopyItem: TMenuItem
      Action = ClipCopyAction
    end
    object LineCopyItem: TMenuItem
      Action = LineCopyAction
    end
    object SaveAsItem: TMenuItem
      Action = SaveAsAction
    end
    object Sep_1: TMenuItem
      Caption = '-'
    end
    object EdieFileItem: TMenuItem
      Action = EditFileAction
    end
    object ViewFileItem: TMenuItem
      Action = ViewFileAction
    end
  end
end
