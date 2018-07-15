object frmRSAKeys: TfrmRSAKeys
  Left = 332
  Top = 305
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Generate RSA Public/Private Key Pair'
  ClientHeight = 258
  ClientWidth = 514
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 8
    Top = 56
    Width = 64
    Height = 13
    Caption = 'Key Modulus:'
  end
  object Label5: TLabel
    Left = 8
    Top = 102
    Width = 101
    Height = 13
    Caption = 'Public Key Exponent:'
  end
  object Label6: TLabel
    Left = 8
    Top = 148
    Width = 105
    Height = 13
    Caption = 'Private Key Exponent:'
  end
  object Bevel1: TBevel
    Left = 8
    Top = 193
    Width = 497
    Height = 9
    Shape = bsBottomLine
  end
  object Label9: TLabel
    Left = 8
    Top = 22
    Width = 41
    Height = 13
    Caption = 'Key Size'
  end
  object Label1: TLabel
    Left = 160
    Top = 30
    Width = 43
    Height = 13
    Caption = 'Iterations'
  end
  object Label8: TLabel
    Left = 160
    Top = 16
    Width = 46
    Height = 13
    Caption = 'Prime test'
  end
  object btnClose: TButton
    Left = 430
    Top = 208
    Width = 75
    Height = 25
    Caption = 'Close'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = btnCloseClick
  end
  object edtModulus: TEdit
    Left = 8
    Top = 72
    Width = 497
    Height = 21
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    ReadOnly = True
    TabOrder = 1
  end
  object edtPublicExponent: TEdit
    Left = 8
    Top = 118
    Width = 497
    Height = 21
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    ReadOnly = True
    TabOrder = 2
  end
  object edtPrivateExponent: TEdit
    Left = 8
    Top = 164
    Width = 497
    Height = 21
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    ReadOnly = True
    TabOrder = 3
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 239
    Width = 514
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object cbxKeySize: TComboBox
    Left = 56
    Top = 18
    Width = 81
    Height = 21
    Style = csDropDownList
    TabOrder = 5
    Items.Strings = (
      '128'
      '256'
      '512'
      '768'
      '1024')
  end
  object edtIterations: TEdit
    Left = 216
    Top = 18
    Width = 33
    Height = 21
    TabOrder = 6
    Text = '20'
  end
  object btnGenerate: TButton
    Left = 263
    Top = 16
    Width = 90
    Height = 25
    Caption = 'Generate Keys'
    TabOrder = 7
    OnClick = btnGenRSAKeysClick
  end
  object btnClear: TButton
    Left = 367
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 8
    OnClick = btnClearClick
  end
end
