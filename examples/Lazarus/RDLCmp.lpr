program RDLCmp;

uses
  Forms, Interfaces,
  RDLCmp1 in 'RDLCmp1.pas' {Form1};


begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
