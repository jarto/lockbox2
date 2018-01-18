object frmSymmetricKey: TfrmSymmetricKey
  Left = 538
  Top = 127
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Generate Symmetric Encryption Key'
  ClientHeight = 215
  ClientWidth = 420
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
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 62
    Height = 13
    Caption = '&Pass Phrase:'
  end
  object Label3: TLabel
    Left = 8
    Top = 128
    Width = 21
    Height = 13
    Caption = 'Key:'
  end
  object Bevel1: TBevel
    Left = 8
    Top = 169
    Width = 401
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
    Left = 152
    Top = 22
    Width = 45
    Height = 13
    Caption = 'Key Type'
  end
  object btnClose: TButton
    Left = 334
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Close'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object edtKey: TEdit
    Left = 8
    Top = 144
    Width = 401
    Height = 21
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    ReadOnly = True
    TabOrder = 1
  end
  object cbxKeySize: TComboBox
    Left = 56
    Top = 18
    Width = 81
    Height = 21
    Style = csDropDownList
    TabOrder = 2
    OnChange = rgKeySizeChange
    Items.Strings = (
      '64'
      '128'
      '192'
      '256')
  end
  object cbxKeyType: TComboBox
    Left = 208
    Top = 18
    Width = 105
    Height = 21
    Style = csDropDownList
    TabOrder = 3
    OnChange = rgKeyTypeChange
    Items.Strings = (
      'Random'
      'Text'
      'Text (Case Sensitive)')
  end
  object btnGenerate: TButton
    Left = 336
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Generate'
    TabOrder = 4
    OnClick = btnGenerateClick
  end
  object edtPassphrase: TEdit
    Left = 8
    Top = 72
    Width = 401
    Height = 21
    TabOrder = 5
    OnChange = edtPassphraseChange
  end
end
