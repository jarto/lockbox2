program RSAKeys;

uses
  Forms, Interfaces,
  RSAKeys1 in 'RSAKeys1.pas' {Form1};

{.$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
