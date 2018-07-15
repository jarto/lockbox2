unit ExStrin1;

{$MODE Delphi}

interface

uses
  Graphics,
  Controls,
  Forms,
  Dialogs,
  StdCtrls,
  SysUtils,
  Classes;

type
  TForm1 = class(TForm)
    btnEncrypt: TButton;
    btnDecrypt: TButton;
    Label4: TLabel;
    cbxEncryption: TComboBox;
    mmoPlainText1: TMemo;
    Label5: TLabel;
    mmoCipherText: TMemo;
    Label7: TLabel;
    mmoPlainText2: TMemo;
    Label6: TLabel;
    Label1: TLabel;
    edtPassphrase: TEdit;
    procedure btnEncryptClick(Sender: TObject);
    procedure btnDecryptClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    procedure RefreshKeys;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

uses
  LbCipher, LbString, LbUtils;

type
  TEncryption = (eBf, eBfCbc, eDes, eDesCbc, e3Des, e3DesCbc, eRdl, eRdlCbc);


var
  Key64            : TKey64;
  Key128           : TKey128;
  Key192           : TKey192;
  Key256           : TKey256;

procedure TForm1.FormCreate(Sender: TObject);
begin
  cbxEncryption.ItemIndex := Integer(eDes);
end;

procedure TForm1.btnEncryptClick(Sender: TObject);
var
  PlainText, CipherText : UTF8String;
begin
  RefreshKeys;
  PlainText := StringToUTF8(mmoPlainText1.Text);
  case TEncryption(cbxEncryption.ItemIndex) of
    eBf      : CipherText := BFEncryptStringEx(PlainText, Key128, True);
    eBfCbc   : CipherText := BFEncryptStringCBCEx(PlainText, Key128, True);
    eDes     : CipherText := DESEncryptStringEx(PlainText, Key64, True);
    eDesCbc  : CipherText := DESEncryptStringCBCEx(PlainText, Key64, True);
    e3Des    : CipherText := TripleDESEncryptStringEx(PlainText, Key128, True);
    e3DesCbc : CipherText := TripleDESEncryptStringCBCEx(PlainText, Key128, True);
    eRdl     : CipherText := RDLEncryptStringEx(PlainText, Key128, 16, True);
    eRdlCbc  : CipherText := RDLEncryptStringCBCEx(PlainText, Key128, 16, True);
  end;
  mmoCipherText.Text := UTF8ToString(CipherText);
  mmoPlainText2.Clear;
end;

procedure TForm1.btnDecryptClick(Sender: TObject);
var
  PlainText, CipherText : UTF8String;
begin
  RefreshKeys;
  CipherText := StringToUTF8(mmoCipherText.Text);
  case TEncryption(cbxEncryption.ItemIndex) of
    eBf      : PlainText := BFEncryptStringEx(CipherText, Key128, False);
    eBfCbc   : PlainText := BFEncryptStringCBCEx(CipherText, Key128, False);
    eDes     : PlainText := DESEncryptStringEx(CipherText, Key64, False);
    eDesCbc  : PlainText := DESEncryptStringCBCEx(CipherText, Key64, False);
    e3Des    : PlainText := TripleDESEncryptStringEx(CipherText, Key128, False);
    e3DesCbc : PlainText := TripleDESEncryptStringCBCEx(CipherText, Key128, False);
    eRdl     : PlainText := RDLEncryptStringEx(CipherText, Key128, 16, False);
    eRdlCbc  : PlainText := RDLEncryptStringCBCEx(CipherText, Key128, 16, False);
  end;
  mmoPlainText2.Text := UTF8ToString(PlainText);
end;

procedure TForm1.RefreshKeys;
var
  Passphrase : UTF8String;
begin
  Passphrase := StringToUTF8(edtPassphrase.Text);
  GenerateLMDKey(Key64, SizeOf(Key64), Passphrase);
  GenerateLMDKey(Key128, SizeOf(Key128), Passphrase);
  GenerateLMDKey(Key192, SizeOf(Key192), Passphrase);
  GenerateLMDKey(Key256, SizeOf(Key256), Passphrase);
end;


end.
