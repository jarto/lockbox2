program ExHash;

{$MODE Delphi}

uses
{$IFDEF WIN32}
  Forms, Interfaces,
{$ENDIF}
{$IFDEF LINUX}
  QForms,
{$ENDIF}
  ExHash1 in 'ExHash1.pas' {Form1};

{.$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
