{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='kickdown';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';

Var
  S1,S2:String;
  Res:Integer;

Procedure Load;
Begin
  ReSet(Input,InFile);
  ReadLn(S1);
  ReadLn(S2);
  Close(Input);
End;

Procedure Solve;
Var
  Shift,I:Integer;
  Ok:Boolean;
Begin
  Res:=1000;
  For Shift:=-100 To 100 Do Begin
    Ok:=True;
    For I:=1 To Length(S2) Do If S2[I]='2' Then Begin
      If (I+Shift>=1) And (I+Shift<=Length(S1)) And (S1[I+Shift]='2') Then Ok:=False;
    End;
    If Ok Then Res:=Min(Res,Max(Length(S1),Length(S2)+Shift)-Min(1,1+Shift)+1);
  End;
End;

Procedure Save;
Begin
  ReWrite(Output,OutFile);
  WriteLn(Res);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
