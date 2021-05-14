{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='driving';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';
  Eps=1e-10;
  MaxN=50;
  Inf=1e50;
  MagicNumber=54315431;

Type
  TPoint=Record
    X,Y:Real;
  End;
  TRectangle=Record
    X1,Y1,X2,Y2:Real;
  End;

Var
  Rad:Real;
  N:Integer;
  Start,Finish:TPoint;
  Rect:Array[1..MaxN]Of TRectangle;
  NC:Integer;
  CWho:Array[1..4*MaxN]Of Integer;
  CC:Array[1..4*MaxN]Of TPoint;
  NV:Integer;
  VCId:Array[1..10*MaxN*MaxN]Of Integer;
  V:Array[1..10*MaxN*MaxN]Of TPoint;
  L:Array[1..10*MaxN*MaxN]Of Real;
  Prev:Array[1..10*MaxN*MaxN]Of Integer;
  Mark:Array[1..10*MaxN*MaxN]Of Boolean;

Procedure Load;
Var
  I:Integer;
Begin
  ReSet(Input,InFile);
  Read(Rad,N);
  With Start Do Read(X,Y);
  With Finish Do Read(X,Y);
  For I:=1 To N Do With Rect[I] Do Begin
    Read(X1,Y1,X2,Y2);
  End;
  Close(Input);
End;

Function Dist(X1,Y1,X2,Y2:Real):Real;
Begin
  Result:=Sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
End;

Function IsInside(Var P:TPoint; Var R:TRectangle):Boolean;
Begin
  Result:=True;
  If Dist(P.X,P.Y,R.X1,R.Y1)<Rad-Eps Then Exit;
  If Dist(P.X,P.Y,R.X1,R.Y2)<Rad-Eps Then Exit;
  If Dist(P.X,P.Y,R.X2,R.Y1)<Rad-Eps Then Exit;
  If Dist(P.X,P.Y,R.X2,R.Y2)<Rad-Eps Then Exit;
  If (P.X>R.X1+Eps) And (P.X<R.X2-Eps) And (P.Y>R.Y1-Rad+Eps) And (P.Y<R.Y2+Rad-Eps) Then Exit;
  If (P.X>R.X1-Rad+Eps) And (P.X<R.X2+Rad-Eps) And (P.Y>R.Y1+Eps) And (P.Y<R.Y2-Eps) Then Exit;
  Result:=False;
End;

Function IsGoodPoint(Var P:TPoint):Boolean;
Var
  I:Integer;
Begin
  Result:=False;
  If P.X=MagicNumber Then Exit;
  For I:=1 To N Do If IsInside(P,Rect[I]) Then Exit;
  Result:=True;
End;

Function Intersects(Var P1,P2:TPoint; CX,CY:Real):Boolean; overload;
Var
  Z:Real;
Begin
  Result:=True;
  If Dist(P1.X,P1.Y,CX,CY)<Rad-Eps Then Exit;
  If Dist(P2.X,P2.Y,CX,CY)<Rad-Eps Then Exit;
  Result:=False;
  Z:=(CX-P1.X)*(P2.X-P1.X)+(CY-P1.Y)*(P2.Y-P1.Y);
  If Z<Eps Then Exit;
  Z:=(CX-P2.X)*(P1.X-P2.X)+(CY-P2.Y)*(P1.Y-P2.Y);
  If Z<Eps Then Exit;
  Z:=Abs((CX-P1.X)*(P2.Y-P1.Y)-(CY-P1.Y)*(P2.X-P1.X))/Dist(P1.X,P1.Y,P2.X,P2.Y);
  If Z>Rad-Eps Then Exit;
  Result:=True;
End;

Function Sign(Z:Real):Integer;
Begin
  If Abs(Z)<Eps Then Sign:=0 Else If Z<0 Then Sign:=-1 Else Sign:=1;
End;

Function Intersects(Var P1,P2:TPoint; X1,Y1,X2,Y2:Real):Boolean; overload;
Var
  A,B,C:Real;
  S1,S2,S3,S4:Integer;
Begin
  Result:=False;
  If (P1.X<X1+Eps) And (P2.X<X1+Eps) Then Exit;
  If (P1.X>X2-Eps) And (P2.X>X2-Eps) Then Exit;
  If (P1.Y<Y1+Eps) And (P2.Y<Y1+Eps) Then Exit;
  If (P1.Y>Y2-Eps) And (P2.Y>Y2-Eps) Then Exit;
  A:=P2.Y-P1.Y;
  B:=P1.X-P2.X;
  C:=Sqrt(A*A+B*B);
  If (C<Eps) Then Exit;
  A:=A/C;
  B:=B/C;
  C:=-(A*P1.X+B*P1.Y);
  S1:=Sign(A*X1+B*Y1+C);
  S2:=Sign(A*X2+B*Y1+C);
  S3:=Sign(A*X1+B*Y2+C);
  S4:=Sign(A*X2+B*Y2+C);
  If (S1>=0) And (S2>=0) And (S3>=0) And (S4>=0) Then Exit;
  If (S1<=0) And (S2<=0) And (S3<=0) And (S4<=0) Then Exit;
  Result:=True;
End;

Function Intersects(Var P1,P2:TPoint; Var R:TRectangle):Boolean; overload;
Begin
  Result:=True;
  If Intersects(P1,P2,R.X1,R.Y1) Then Exit;
  If Intersects(P1,P2,R.X1,R.Y2) Then Exit;
  If Intersects(P1,P2,R.X2,R.Y1) Then Exit;
  If Intersects(P1,P2,R.X2,R.Y2) Then Exit;
  If Intersects(P1,P2,R.X1-Rad,R.Y1,R.X2+Rad,R.Y2) Then Exit;
  If Intersects(P1,P2,R.X1,R.Y1-Rad,R.X2,R.Y2+Rad) Then Exit;
  Result:=False;
End;

Function Intersects(Var P1,P2,Center:TPoint; CX,CY:Real):Boolean; overload;
Var
  S1,S2:Integer;
Begin
  Result:=False;
  If Dist(Center.X,Center.Y,CX,CY)>2*Rad-Eps Then Exit;
  S1:=Sign((CX-Center.X)*(P1.Y-Center.Y)-(CY-Center.Y)*(P1.X-Center.X));
  S2:=Sign((CX-Center.X)*(P2.Y-Center.Y)-(CY-Center.Y)*(P2.X-Center.X));
  If (S1*S2>=0) Then Exit;
  Result:=True;
End;

Function Intersects(Var P1,P2,Center:TPoint; X1,Y1,X2,Y2:Real):Boolean; overload;
Begin
  Result:=False;
  If (Center.X<X1-Rad+Eps) Then Exit;
  If (Center.X>X2+Rad-Eps) Then Exit;
  If (Center.Y<Y1-Rad+Eps) Then Exit;
  If (Center.Y>Y2+Rad-Eps) Then Exit;
{  Result:=True;
  If Dist(X1,Y1,Center.X,Center.Y)<Rad-Eps Then Exit;
  If Dist(X1,Y2,Center.X,Center.Y)<Rad-Eps Then Exit;
  If Dist(X2,Y1,Center.X,Center.Y)<Rad-Eps Then Exit;
  If Dist(X2,Y2,Center.X,Center.Y)<Rad-Eps Then Exit;}
  Result:=False;
End;

Function Intersects(Var P1,P2,Center:TPoint; Var R:TRectangle):Boolean; overload;
Begin
  Result:=True;
  If Intersects(P1,P2,Center,R.X1,R.Y1) Then Exit;
  If Intersects(P1,P2,Center,R.X1,R.Y2) Then Exit;
  If Intersects(P1,P2,Center,R.X2,R.Y1) Then Exit;
  If Intersects(P1,P2,Center,R.X2,R.Y2) Then Exit;
  If Intersects(P1,P2,Center,R.X1-Rad,R.Y1,R.X2+Rad,R.Y2) Then Exit;
  If Intersects(P1,P2,Center,R.X1,R.Y1-Rad,R.X2,R.Y2+Rad) Then Exit;
  Result:=False;
End;

Function IsGoodSegment(Var P1,P2:TPoint):Boolean;
Var
  I:Integer;
Begin
  Result:=False;
  If (Abs(P1.X-P2.X)<Eps) And (Abs(P1.Y-P2.Y)<Eps) Then Begin
    Result:=True;
    Exit;
  End;
  For I:=1 To N Do If Intersects(P1,P2,Rect[I]) Then Exit;
  Result:=True;
End;

Function IsGoodArc(Var P1,P2,Center:TPoint; Who:Integer):Boolean;
Var
  I:Integer;
Begin
  Result:=False;
  If (Abs(P1.X-P2.X)<Eps) And (Abs(P1.Y-P2.Y)<Eps) Then Begin
    Result:=True;
    Exit;
  End;
  For I:=1 To N Do If (I<>Who) And Intersects(P1,P2,Center,Rect[I]) Then Exit;
  Result:=True;
End;

Procedure GetTangentPoints(Var P:TPoint; CX,CY:Real; Var R1,R2:TPoint); Overload;
Var
  Gamma,Alpha:Real;
Begin
  Alpha:=Rad/Dist(P.X,P.Y,CX,CY);
  If (Alpha>1) And (Alpha<1+Eps) Then Alpha:=1;
  If Abs(Alpha)<=1 Then Begin
    Alpha:=ArcCos(Alpha);
    Gamma:=ArcTan2(P.Y-CY,P.X-CX);
    R1.X:=CX+Rad*Cos(Alpha+Gamma);
    R1.Y:=CY+Rad*Sin(Alpha+Gamma);
    R2.X:=CX+Rad*Cos(-Alpha+Gamma);
    R2.Y:=CY+Rad*Sin(-Alpha+Gamma);
  End Else Begin
    R1.X:=MagicNumber;
    R1.Y:=MagicNumber;
    R2.X:=MagicNumber;
    R2.Y:=MagicNumber;
  End;
End;

Procedure GetTangentPoints(CX1,CY1,CX2,CY2:Real; Var R1,R2,R3,R4:TPoint); Overload;
Var
  Gamma,Alpha:Real;
Begin
  Gamma:=ArcTan2(CY2-CY1,CX2-CX1);
  Alpha:=Rad*2/Dist(CX1,CY1,CX2,CY2);
  If (Alpha>1) And (Alpha<1+Eps) Then Alpha:=1;
  If Abs(Alpha)<=1 Then Begin
    Alpha:=ArcCos(Alpha);
    R1.X:=CX1+Rad*Cos(Alpha+Gamma);
    R1.Y:=CY1+Rad*Sin(Alpha+Gamma);
    R2.X:=CX1+Rad*Cos(-Alpha+Gamma);
    R2.Y:=CY1+Rad*Sin(-Alpha+Gamma);
  End Else Begin
    R1.X:=MagicNumber;
    R1.Y:=MagicNumber;
    R2.X:=MagicNumber;
    R2.Y:=MagicNumber;
  End;
  Alpha:=Pi/2;
  R3.X:=CX1+Rad*Cos(Alpha+Gamma);
  R3.Y:=CY1+Rad*Sin(Alpha+Gamma);
  R4.X:=CX1+Rad*Cos(-Alpha+Gamma);
  R4.Y:=CY1+Rad*Sin(-Alpha+Gamma);
End;

Procedure Relax(I,J:Integer; D:Real);
Begin
  If D<L[I] Then Begin
    L[I]:=D;
    Prev[I]:=J;
  End;
End;

Function CDist(A:Real):Real;
Begin
  A:=Abs(A);
  If A>Pi Then A:=2*Pi-A;
  Result:=A;
End;

Procedure Solve;
Var
  I,J:Integer;
  R1,R2,R3,R4:TPoint;
  M:Real;
  MI:Integer;
Begin
  NC:=0;
  For I:=1 To N Do With Rect[I] Do Begin
    Inc(NC);
    CWho[NC]:=I;
    With CC[NC] Do Begin
      X:=X1;
      Y:=Y1;
    End;
    Inc(NC);
    CWho[NC]:=I;
    With CC[NC] Do Begin
      X:=X1;
      Y:=Y2;
    End;
    Inc(NC);
    CWho[NC]:=I;
    With CC[NC] Do Begin
      X:=X2;
      Y:=Y1;
    End;
    Inc(NC);
    CWho[NC]:=I;
    With CC[NC] Do Begin
      X:=X2;
      Y:=Y2;
    End;
  End;

  NV:=2;
  V[1]:=Start;
  VCId[1]:=-1;
  V[2]:=Finish;
  VCId[2]:=-2;

  If Not IsGoodPoint(Start) Then Assert(False);
  If Not IsGoodPoint(Finish) Then Assert(False);

  For I:=1 To NC Do
    For J:=1 To NC Do If I<>J Then Begin
      GetTangentPoints(CC[I].X,CC[I].Y,CC[J].X,CC[J].Y,R1,R2,R3,R4);
      If IsGoodPoint(R1) Then Begin
        Inc(NV);
        V[NV]:=R1;
        VCId[NV]:=I;
      End;
      If IsGoodPoint(R2) Then Begin
        Inc(NV);
        V[NV]:=R2;
        VCId[NV]:=I;
      End;
      If IsGoodPoint(R3) Then Begin
        Inc(NV);
        V[NV]:=R3;
        VCId[NV]:=I;
      End;
      If IsGoodPoint(R4) Then Begin
        Inc(NV);
        V[NV]:=R4;
        VCId[NV]:=I;
      End;
    End;

  For I:=1 To NC Do Begin
    GetTangentPoints(Start,CC[I].X,CC[I].Y,R1,R2);
    If IsGoodPoint(R1) Then Begin
      Inc(NV);
      V[NV]:=R1;
      VCId[NV]:=I;
    End;
    If IsGoodPoint(R2) Then Begin
      Inc(NV);
      V[NV]:=R2;
      VCId[NV]:=I;
    End;
    GetTangentPoints(Finish,CC[I].X,CC[I].Y,R1,R2);
    If IsGoodPoint(R1) Then Begin
      Inc(NV);
      V[NV]:=R1;
      VCId[NV]:=I;
    End;
    If IsGoodPoint(R2) Then Begin
      Inc(NV);
      V[NV]:=R2;
      VCId[NV]:=I;
    End;
  End;

  For I:=1 To NV Do L[I]:=Inf;
  L[1]:=0;
  FillChar(Mark,SizeOf(Mark),False);
  While Not Mark[2] Do Begin
    M:=Inf/2;
    MI:=-1;
    For I:=1 To NV Do If Not Mark[I] And (L[I]<M) Then Begin
      M:=L[I];
      MI:=I;
    End;
    If MI<0 Then Break;
    Mark[MI]:=True;
    For I:=1 To NV Do If Not Mark[I] Then Begin
    If (MI=16) ANd (I=113) Then Begin
      WritELn('!!!');
    End;
      If IsGoodSegment(V[MI],V[I]) Then Begin
        Relax(I,MI,L[MI]+Dist(V[MI].X,V[MI].Y,V[I].X,V[I].Y));
      End;
      If (VCId[MI]=VCId[I]) And IsGoodArc(V[MI],V[I],CC[VCId[I]],CWho[VCId[I]]) Then Begin
        Relax(I,MI,L[MI]+Rad*CDist(ArcTan2(V[MI].Y-CC[VCId[I]].Y,V[MI].X-CC[VCId[I]].X)-ArcTan2(V[I].Y-CC[VCId[I]].Y,V[I].X-CC[VCId[I]].X)));
      End;
    End;
  End;
End;

Procedure Save;
Begin
  ReWrite(Output,OutFile);
  If L[2]>Inf/2 Then WriteLn('no solution') Else WriteLn(L[2]:0:10);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
