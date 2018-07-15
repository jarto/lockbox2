program RSACmp;

{$MODE Delphi}

uses
{$IFDEF WIN32}
  Forms, Interfaces,
{$ENDIF}
{$IFDEF LINUX}
  QForms,
{$ENDIF}
  RSACmp1 in 'RSACmp1.pas' {Form1};


begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
