unit RSAKeys1;

interface

uses
{$IFDEF WIN32}
  Windows,
  Messages,
  Graphics,
  Controls,
  Forms,
  Dialogs,
  StdCtrls,
  ExtCtrls,
  ComCtrls,
{$ENDIF}
{$IFDEF LINUX}
  QForms,
  QDialogs,
  QControls,
  QExtCtrls,
  QComCtrls,
  QStdCtrls,
{$ENDIF}
  SysUtils,
  Classes,
  LbAsym,
  LbRSA,
  LbCipher,
  LbClass;

type
  TlbRSAKeysForm = class(TForm)
    sbrVerify: TStatusBar;
    pnlPersistKeys: TPanel;
    grpPersistKeys: TGroupBox;
    dlgSave: TSaveDialog;
    dlgOpen: TOpenDialog;
    pnlKeys: TPanel;
    tbcKeyVisibility: TTabControl;
    lblExponent: TLabel;
    edtExponent: TEdit;
    btnLoad: TButton;
    btnSave: TButton;
    edtPassPhrase: TEdit;
    lblPassPhrase: TLabel;
    lblBase64Encoded: TLabel;
    mmoBase64Encoded: TMemo;
    lblModulus: TLabel;
    mmoModulus: TMemo;
    pnlKeySize: TPanel;
    lblKeySize: TLabel;
    cmbKeySize: TComboBox;
    lblIterations: TLabel;
    edtIterations: TEdit;
    btnCreateKeys: TButton;
    kpRSA: TLbRSA;
    procedure btnCreateKeysClick(Sender: TObject);
    procedure btnLoadClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure tbcKeyVisibilityChange(Sender: TObject);
    procedure cmbKeySizeChange(Sender: TObject);
  private
    FActiveKey : TLbRSAKey;
    procedure UpdateControls;
    procedure SetKeySize(const AValue : TLbAsymKeySize);
  public
    procedure AfterConstruction; override;
  end;

var
  lbRSAKeysForm: TlbRSAKeysForm;

implementation

{$R *.dfm}

uses
  LbUtils;

procedure TlbRSAKeysForm.AfterConstruction;
begin
  inherited;
//  cmbKeySize.ItemIndex := Ord(kpRSA.KeySize);
  FActiveKey := kpRSA.PublicKey;
  UpdateControls;
end;

procedure TlbRSAKeysForm.btnCreateKeysClick(Sender: TObject);
begin
  Screen.Cursor := crHourglass;
  sbrVerify.SimpleText := 'Generating key pair, this may take a while';
  try
    kpRSA.PrimeTestIterations := StrToIntDef(edtIterations.Text, 20);
    kpRSA.KeySize := TLbAsymKeySize(cmbKeySize.ItemIndex);
    kpRSA.GenerateKeyPair;
    tbcKeyVisibilityChange(self);
  finally
    Screen.Cursor := crDefault;
    sbrVerify.SimpleText := '';
  end;
end;

procedure TlbRSAKeysForm.btnLoadClick(Sender: TObject);
var
  FS : TFileStream;
begin
  if dlgOpen.Execute then
  begin
    FS := TFileStream.Create(dlgOpen.FileName, fmOpenRead);
    Screen.Cursor := crHourGlass;
    try
      FActiveKey.Clear;
      FActiveKey.LoadFromStream(FS, StringToUTF8(edtPassPhrase.Text));
      SetKeySize(FActiveKey.KeySize);
      UpdateControls;
    finally
      FS.Free;
      Screen.Cursor := crDefault;
    end;
  end;
end;

procedure TlbRSAKeysForm.btnSaveClick(Sender: TObject);
var
  FS : TFileStream;
begin
  if dlgSave.Execute then
  begin
    FS := TFileStream.Create(dlgSave.FileName, fmCreate);
    Screen.Cursor := crHourGlass;
    try
      FActiveKey.StoreToStream(FS, StringToUTF8(edtPassPhrase.Text));
    finally
      FS.Free;
      Screen.Cursor := crDefault;
    end;
  end;
end;

procedure TlbRSAKeysForm.cmbKeySizeChange(Sender: TObject);
begin
  SetKeySize(TLbAsymKeySize(cmbKeySize.ItemIndex));
end;

procedure TlbRSAKeysForm.SetKeySize(const AValue: TLbAsymKeySize);
begin
  if (kpRSA.KeySize <> AValue) then
  begin
    if (kpRSA.PublicKey.KeySize <> AValue) then
    begin
      kpRSA.PublicKey.Clear;
    end;

    if (kpRSA.PrivateKey.KeySize <> AValue) then
    begin
      kpRSA.PrivateKey.Clear;
    end;

    kpRSA.KeySize := AValue;
    UpdateControls;
  end;
end;

procedure TlbRSAKeysForm.UpdateControls;
begin
  edtExponent.Text := FActiveKey.ExponentAsString;
  mmoModulus.Text := FActiveKey.ModulusAsString;
  if (FActiveKey.Exponent.Size > 0) and (FActiveKey.Modulus.Size > 0) then
  begin
    mmoBase64Encoded.Text := UTF8ToString(FActiveKey.Base64EncodedText);
  end
  else
  begin
    mmoBase64Encoded.Text := '';
  end;

  cmbKeySize.ItemIndex := ord(FActiveKey.KeySize);
end;

procedure TlbRSAKeysForm.tbcKeyVisibilityChange(Sender: TObject);
begin
  if (tbcKeyVisibility.TabIndex = 0) then
  begin
    FActiveKey := kpRSA.PublicKey;
  end
  else
  begin
    FActiveKey := kpRSA.PrivateKey;
  end;

  UpdateControls;
end;

end.


