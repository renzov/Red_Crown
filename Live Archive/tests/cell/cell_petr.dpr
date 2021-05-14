{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='cell';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';
  MaxN=500;

Type
  TMatr=Array[1..MaxN,1..MaxN]Of Int64;
  TVect=Array[1..MaxN]Of Int64;
  PMatr=^TMatr;

Var
  N,M,D,K:Integer;
  T1,T2,T3:PMatr;
  Start,Finish:TVect;

Procedure Load;
Var
  I:Integer;
Begin
  ReSet(Input,InFile);
  Read(N,M,D,K);
  For I:=1 To N Do Read(Start[I]);
  Close(Input);
End;

Procedure Mul(Var M1,M2:TMatr; Var M3:TMatr); overload;
Var
  I,J,K:Integer;
  V:Int64;
Begin
  For I:=1 To N Do
    For J:=1 To N Do Begin
      V:=0;
      If I=1 Then
        For K:=1 To N Do Begin
          V:=V+M1[I,K]*M2[K,J];
        End
      Else
        V:=M3[1,(J-I+N) Mod N+1];
      M3[I,J]:=V Mod M;
    End;
End;

Procedure Mul(Var M1:TMatr; Var A:TVect; Var B:TVect); overload;
Var
  I,J:Integer;
  V:Int64;
Begin
  For I:=1 To N Do Begin
    V:=0;
    For J:=1 To N Do
      V:=V+M1[I,J]*A[J];
    B[I]:=V Mod M;
  End;
End;

Procedure Solve;
Var
  I,J:Integer;
  At:Integer;
  Tmp:PMatr;
Begin
  New(T1);
  New(T2);
  New(T3);
  FillChar(T1^,SizeOf(T1^),0);
  For I:=1 To N Do T1^[I,I]:=1;
  FillChar(T2^,SizeOf(T2^),0);
  For I:=1 To N Do
    For J:=1 To N Do
      If Min(Abs(I-J),N-Abs(I-J))<=D Then
        T2^[I,J]:=1
      Else
        T2^[I,J]:=0;
  While K>0 Do Begin
    If Odd(K) Then Begin
      Mul(T1^,T2^,T3^);
      Tmp:=T3;
      T3:=T1;
      T1:=Tmp;
    End;
    Mul(T2^,T2^,T3^);
    Tmp:=T2;
    T2:=T3;
    T3:=Tmp;
    K:=K Shr 1;
  End;
  Mul(T1^,Start,Finish);
End;

Procedure Save;
Var
  I:Integer;
Begin
  ReWrite(Output,OutFile);
  For I:=1 To N Do Begin
    If I>1 Then Write(' ');
    Write(Finish[I]);
  End;
  WriteLn;
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
