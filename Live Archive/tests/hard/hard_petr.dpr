{$APPTYPE CONSOLE}
{$R+,Q+,S-,H+,O+}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='hard';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';
  MaxN=100;
  NTries=200;

Var
  N:Integer;
  A:Array[1..MaxN,1..MaxN]Of Boolean;
  Take,BTake:Array[1..MaxN]Of Boolean;
  CE:Integer;
  CNum:Integer;
  Cur:Real;
  Best:Real;
  TryID:Integer;

Procedure Load;
Var
  M:Integer;
  P,Q:Integer;
  I:Integer;
Begin
  ReSet(Input,InFile);
  Read(N,M);
  FillChar(A,SizeOf(A),False);
  For I:=1 To M Do Begin
    Read(P,Q);
    A[P,Q]:=True;
    A[Q,P]:=True;
  End;
  Close(Input);
End;

Procedure TryIt;
Var
  I,J,K,Num:Integer;
  BOp:Integer;
  BImp,CImp:Real;
Begin
  FillChar(Take,SizeOf(Take),False);
  If TryID=1 Then Begin
    FillChar(Take,SizeOf(Take),True);
    Num:=N;
  End Else If TryID<=N+1 Then Begin
    Num:=1;
    Take[TryID-1]:=True;
  End Else Begin
    Num:=Random(N)+1;
    For I:=1 To Num Do Begin
      Repeat
        J:=Random(N)+1;
      Until Not Take[J];
      Take[J]:=True;
    End;
  End;
  CNum:=Num;
  CE:=0;
  For I:=1 To N Do If Take[I] Then
    For J:=I+1 To N Do If Take[J] Then
      If A[I,J] Then Inc(CE);
  While True Do Begin
    Cur:=CE/CNum;
    BImp:=1e-12;
    For I:=1 To N Do If Not Take[I] Then Begin
      K:=0;
      For J:=1 To N Do If Take[J] And A[J,I] Then Inc(K);
      CImp:=(CE+K)/(CNum+1)-Cur;
      If CImp>BImp Then Begin
        BImp:=CImp;
        BOp:=I;
      End;
    End;
    If CNum>1 Then
      For I:=1 To N Do If Take[I] Then Begin
        K:=0;
        For J:=1 To N Do If Take[J] And A[I,J] Then Inc(K);
        CImp:=(CE-K)/(CNum-1)-Cur;
        If CImp>BImp Then Begin
          BImp:=CImp;
          BOp:=-I;
        End;
      End;
    If BImp>1e-11 Then Begin
      If BOp>0 Then Begin
        Take[BOp]:=True;
        For J:=1 To N Do If Take[J] And A[J,BOp] Then Inc(CE);
        Inc(CNum);
      End Else Begin
        Take[-BOp]:=False;
        For J:=1 To N Do If Take[J] And A[J,-BOp] Then Dec(CE);
        Dec(CNum);
      End;
    End Else Break;
  End;
  If Cur>Best Then Begin
    Best:=Cur;
    BTake:=Take;
  End;
End;

Procedure Solve;
Begin
  Best:=-1;
  For TryID:=1 To NTries Do TryIt;
End;

Procedure Save;
Var
  I,Am:Integer;
Begin
  ReWrite(Output,OutFile);
  Am:=0;
  For I:=1 To N Do If BTake[I] Then Inc(Am);
  WriteLn(Am);
  For I:=1 To N Do If BTake[I] Then Begin
    WriteLn(I);
  End;
  Close(Output);
End;

begin
  RandSeed:=549731543;
  Load;
  Solve;
  Save;
end.
