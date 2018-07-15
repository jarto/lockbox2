program DSACmp;

uses
  Forms, Interfaces,
  DSACmp1 in 'DSACmp1.pas' {Form1};

{.$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
