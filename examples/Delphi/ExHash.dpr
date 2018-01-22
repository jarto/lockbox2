program ExHash;

uses
  Forms,
  ExHash1 in 'ExHash1.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
