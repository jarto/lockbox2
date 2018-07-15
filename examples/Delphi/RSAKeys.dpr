program RSAKeys;

uses
  Forms,
  RSAKeys1 in 'RSAKeys1.pas' {lbRSAKeysForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TlbRSAKeysForm, lbRSAKeysForm);
  Application.Run;
end.
