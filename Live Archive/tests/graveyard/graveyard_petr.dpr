{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='graveyard';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';

Var
  N,M:Integer;
  Res:Real;

Procedure Load;
Begin
  ReSet(Input,InFile);
  Read(N,M);
  Close(Input);
End;

Procedure Solve;
Var
  I:Integer;
  At:Real;
Begin
  Res:=0;
  For I:=1 To N-1 Do Begin
    At:=(I/N)*(N+M);
    Res:=Res+Abs(At-Round(At))/(N+M);
  End;
End;

Procedure Save;
Begin
  ReWrite(Output,OutFile);
  WriteLn(Res*10000:0:20);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
