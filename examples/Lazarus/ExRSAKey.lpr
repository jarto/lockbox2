program ExRSAKey;

uses
  Forms, Interfaces,
  ExRSAKe1 in 'ExRSAKe1.pas' {Form1};

{.$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
