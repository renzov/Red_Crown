{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='ascii';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';
  MaxN=100;
  MaxSize=100;
  Eps=1e-12;

Var
  N,W,H:Integer;
  X,Y:Array[1..MaxN]Of Integer;
  Res:Array[-1..MaxSize,-1..MaxSize]Of Real;

Procedure Load;
Var
  I:Integer;
Begin
  ReSet(Input,InFile);
  Read(N,W,H);
  For I:=1 To N Do Read(X[I],Y[I]);
  Close(Input);
End;

Function Floor(A:Real):Integer;
Begin
  Result:=Trunc(A+1000)-1000;
End;

Function Ceil(A:Real):Integer;
Begin
  Result:=-Floor(-A);
End;

Procedure Process(X1,Y1,X2,Y2,By:Integer);
Var
  I,X,Y,U,D:Integer;
  XU,XD,YL,YR,Tmp:Real;
Begin
  For X:=X1 To X2-1 Do Begin
    YL:=(X-X1)/(X2-X1)*(Y2-Y1)+Y1;
    YR:=((X+1)-X1)/(X2-X1)*(Y2-Y1)+Y1;
    If YL<YR Then Begin
      For I:=0 To Floor(YL)-1 Do Res[X,I]:=Res[X,I]+By;
      D:=Floor(YL);
      U:=Ceil(YR)-1;
      If D=U Then Begin
        Res[X,D]:=Res[X,D]+By*(YL-D+YR-D)/2;
      End Else If D<U Then Begin
        XU:=(D+1-Y1)/(Y2-Y1)*(X2-X1)+X1;
        Res[X,D]:=Res[X,D]+By*(1-(XU-X)*(D+1-YL)/2);
        XD:=(U-Y1)/(Y2-Y1)*(X2-X1)+X1;
        Res[X,U]:=Res[X,U]+By*((YR-U)*(X+1-XD)/2);
        For I:=D+1 To U-1 Do Begin
          XU:=(I+1-Y1)/(Y2-Y1)*(X2-X1)+X1;
          XD:=(I-Y1)/(Y2-Y1)*(X2-X1)+X1;
          Res[X,I]:=Res[X,I]+By*(X+1-XD+X+1-XU)/2;
        End;
      End;
    End Else Begin
      For I:=0 To Floor(YR)-1 Do Res[X,I]:=Res[X,I]+By;
      D:=Floor(YR);
      U:=Ceil(YL)-1;
      If D=U Then Begin
        Res[X,D]:=Res[X,D]+By*(YL-D+YR-D)/2;
      End Else If D<U Then Begin
        XU:=(D+1-Y1)/(Y2-Y1)*(X2-X1)+X1;
        Res[X,D]:=Res[X,D]+By*(1-(X+1-XU)*(D+1-YR)/2);
        XD:=(U-Y1)/(Y2-Y1)*(X2-X1)+X1;
        Res[X,U]:=Res[X,U]+By*((YL-U)*(XD-X)/2);
        For I:=D+1 To U-1 Do Begin
          XU:=(I+1-Y1)/(Y2-Y1)*(X2-X1)+X1;
          XD:=(I-Y1)/(Y2-Y1)*(X2-X1)+X1;
          Res[X,I]:=Res[X,I]+By*(XD-X+XU-X)/2;
        End;
      End;
    End;
  End;
End;

Procedure Solve;
Var
  I,X1,Y1,X2,Y2:Integer;
Begin
  FillChar(Res,SizeOf(Res),0);
  For I:=1 To N Do Begin
    X1:=X[I];
    Y1:=Y[I];
    X2:=X[I Mod N+1];
    Y2:=Y[I Mod N+1];
    If X1=X2 Then Continue;
    If X1<X2 Then
      Process(X1,Y1,X2,Y2,1)
    Else
      Process(X2,Y2,X1,Y1,-1);
  End;
End;

Procedure Save;
Var
  X,Y:Integer;
  R:Real;
Begin
  ReWrite(Output,OutFile);
  For Y:=H-1 DownTo 0 Do Begin
    For X:=0 To W-1 Do Begin
      R:=Res[X,Y];
      If R<1/4-Eps Then Write('.') Else If R<1/2-Eps Then Write('+') Else If R<3/4-Eps Then Write('o') Else If R<1-Eps Then Write('$') Else Write('#');
    End;
    WriteLn;
  End;
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
