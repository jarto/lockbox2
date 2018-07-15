program DSAKeys;

uses
  Forms, Interfaces,
  DSAKeys1 in 'DSAKeys1.pas' {frmDSAKeys};

{.$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmDSAKeys, frmDSAKeys);
  Application.Run;
end.
