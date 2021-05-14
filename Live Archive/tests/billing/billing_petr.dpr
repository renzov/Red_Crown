{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}
{$MINSTACKSIZE 4000000}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='billing';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';
  Invalid='invalid';
  Various='@';
  Len=12;
  MaxN=100;
  MaxRes=5000000;

Var
  N:Integer;
  A,B,Plan:Array[1..MaxN]Of String;
  NRes:Integer;
  Res:Array[1..MaxRes]Of String;
  RP:Array[1..MaxRes]Of String;

Function ReadWord:String;
Var
  Ch:Char;
Begin
  Repeat
    Read(Ch);
  Until Ch>' ';
  Result:='';
  Repeat
    Result:=Result+Ch;
    Read(Ch);
  Until Ch<=' ';
End;

Procedure MakeIt(L,R:String; Var A,B:String);
Var
  I:Integer;
Begin
  R:=Copy(L,1,Length(L)-Length(R))+R;
  A:=L;
  A:='5'+A;
  While Length(A)<Len Do A:=A+'0';
  For I:=Length(A) DownTo 1 Do
    If A[I]='0' Then A[I]:='9' Else Begin
      Dec(A[I]);
      Break;
    End;
  B:=R;
  B:='5'+B;
  While Length(B)<Len Do B:=B+'9';
  For I:=Length(B) DownTo 1 Do
    If B[I]='9' Then B[I]:='0' Else Begin
      Inc(B[I]);
      Break;
    End;
End;

Procedure Load;
Var
  Ch:Char;
  I:Integer;
  L,R:String;
Begin
  ReSet(Input,InFile);
  Read(N);
  For I:=1 To N Do Begin
    L:=ReadWord;
    ReadWord;
    R:=ReadWord;
    Plan[I]:=ReadWord;
    MakeIt(L,R,A[I],B[I]);
  End;
  Close(Input);
End;

Function Resolve(P:String):String;
Var
  I,J:Integer;
Begin
  Result:=Various;
  For I:=1 To N Do Begin
    If (Copy(A[I],1,Length(P))=P) And (Length(P)<Len) Then Exit;
    If (Copy(B[I],1,Length(P))=P) And (Length(P)<Len) Then Exit;
    If (A[I]<P) And (P<B[I]) Then Begin
      Result:=Plan[I];
      Exit;
    End;
  End;
  Result:=Invalid;
End;

Function ProcessPrefix(P:String):String;
Var
  Children:Array['0'..'9']Of String;
  Ch:Char;
Begin
  If (Length(P)>1) Then Begin
    Result:=Resolve(P);
    If Result<>Various Then Exit;
  End;
  Result:='';
  For Ch:='0' To '9' Do Begin
    Children[Ch]:=ProcessPrefix(P+Ch);
    If Result='' Then Result:=Children[Ch] Else If Result<>Children[Ch] Then Result:=Various;
  End;
  If (Result=Various) Or (Length(P)=1) Then Begin
    For Ch:='0' To '9' Do If (Children[Ch]<>Various) And (Children[Ch]<>Invalid) Then Begin
      Inc(NRes);
      Res[NRes]:=P+Ch;
      RP[NRes]:=Children[Ch];
    End;
  End;
End;

Procedure QSort(L,R:Integer);
Var
  I,J:Integer;
  X,Y:String;
Begin
  I:=L;
  J:=R;
  X:=Res[(L+R) Div 2];
  While I<=J Do Begin
    While Res[I]<X Do Inc(I);
    While X<Res[J] Do Dec(J);
    If I<=J Then Begin
      Y:=Res[I];
      Res[I]:=Res[J];
      Res[J]:=Y;
      Y:=RP[I];
      RP[I]:=RP[J];
      RP[J]:=Y;
      Inc(I);
      Dec(J);
    End;
  End;
  If I<R Then QSort(I,R);
  If L<J Then QSort(L,J);
End;

Procedure Solve;
Begin
  NRes:=0;
  ProcessPrefix('5');
  If NRes>1 Then QSort(1,NRes);
End;

Procedure Save;
Var
  I:Integer;
Begin
  ReWrite(Output,OutFile);
  WriteLn(NRes);
  For I:=1 To NRes Do WriteLn(Copy(Res[I],2,1000),' ',RP[I]);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
