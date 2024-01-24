object NetShareDlg: TNetShareDlg
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  ClientHeight = 322
  ClientWidth = 232
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
  object ListPanel: TPanel
    Left = 0
    Top = 29
    Width = 232
    Height = 293
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object ShareListBox: TListBox
      Left = 0
      Top = 0
      Width = 228
      Height = 293
      Style = lbOwnerDrawFixed
      Align = alLeft
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderStyle = bsNone
      DoubleBuffered = False
      ParentDoubleBuffered = False
      PopupMenu = PopupMenu1
      TabOrder = 0
      StyleElements = [seBorder]
      OnClick = ShareListBoxClick
      OnDblClick = ShareListBoxDblClick
      OnDrawItem = ShareListBoxDrawItem
      OnKeyDown = ShareListBoxKeyDown
      OnKeyPress = ShareListBoxKeyPress
    end
  end
  object HiddenCanBtn: TButton
    Left = 0
    Top = 322
    Width = 232
    Height = 0
    Align = alBottom
    Cancel = True
    ModalResult = 2
    TabOrder = 2
    TabStop = False
  end
  object PathTabControl: TTabControl
    Left = 0
    Top = 0
    Width = 232
    Height = 29
    Align = alTop
    DoubleBuffered = False
    OwnerDraw = True
    ParentDoubleBuffered = False
    Style = tsFlatButtons
    TabOrder = 0
    TabStop = False
    OnChange = PathTabControlChange
    OnDrawTab = PathTabControlDrawTab
  end
  object PopupMenu1: TPopupMenu
    Left = 32
    Top = 112
    object CopyUncItem: TMenuItem
      Action = CopyUncAction
    end
    object CopyUncAllItem: TMenuItem
      Action = CopyUncAllAction
    end
    object CopyPathItem: TMenuItem
      Action = CopyPathAction
    end
    object CopyPathAllItem: TMenuItem
      Action = CopyPathAllAction
    end
    object SetColorItem: TMenuItem
      Action = SetColorAction
    end
    object SetSkipDirItem: TMenuItem
      Action = SetSkipDirAction
    end
    object EditListItem: TMenuItem
      Action = EditListAction
    end
  end
  object ActionList1: TActionList
    Left = 32
    Top = 45
    object CopyUncAction: TAction
      Caption = 'UNC'#12497#12473#12434#12467#12500#12540'(&C)'
      OnExecute = CopyUncActionExecute
      OnUpdate = CopyUncActionUpdate
    end
    object CopyUncAllAction: TAction
      Caption = #12377#12409#12390#12398'UNC'#12497#12473#12434#12467#12500#12540'(&A)'
      OnExecute = CopyUncAllActionExecute
      OnUpdate = CopyUncAllActionUpdate
    end
    object CopyPathAction: TAction
      Caption = #12487#12451#12524#12463#12488#12522#12539#12497#12473#12434#12467#12500#12540'(&C)'
      OnExecute = CopyPathActionExecute
      OnUpdate = CopyPathActionUpdate
    end
    object CopyPathAllAction: TAction
      Caption = #12377#12409#12390#12398#12487#12451#12524#12463#12488#12522#12539#12497#12473#12434#12467#12500#12540'(&A)'
      OnExecute = CopyPathAllActionExecute
      OnUpdate = CopyPathAllActionUpdate
    end
    object SetColorAction: TAction
      Caption = #34920#31034#33394#12398#35373#23450'(&C)...'
      OnExecute = SetColorActionExecute
      OnUpdate = SetColorActionUpdate
    end
    object SetSkipDirAction: TAction
      Caption = #38500#22806#12487#12451#12524#12463#12488#12522#12398#35373#23450'(&X)...'
      OnExecute = SetSkipDirActionExecute
      OnUpdate = SetSkipDirActionUpdate
    end
    object EditListAction: TAction
      Caption = #12522#12473#12488#12501#12449#12452#12523#12398#32232#38598'(&E)...'
      OnExecute = EditListActionExecute
      OnUpdate = EditListActionUpdate
    end
  end
end
