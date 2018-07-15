program RSAKeys;

uses
  Forms, Interfaces,
  RSAKeys1 in 'RSAKeys1.pas' {Form1};

{.$R *.res}

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TlbRSAKeysForm, lbRSAKeysForm);
  Application.Run;
end.
