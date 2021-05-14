(*
    Checker for NEERC'2006 Problem H: Hard Life
    (C) Maxim Babenko, Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses 
  TestLib, SysUtils;

const
  MAX_N = 100;

type
  TAnswer = array[1..MAX_N] of Boolean;
    
var
  n : Integer;
  g : array[1..MAX_N, 1..MAX_N] of Boolean;
  ja, pa : TAnswer;
  pj, qj, pp, qp : Integer; 
  
procedure ReadGraph;
var
  m : Integer;
  i : Integer;
  a, b : Integer;
  
begin
  n := inf.ReadInteger;
  m := inf.ReadInteger;
  fillchar(g, sizeof(g), false);
  for i := 1 to m do begin
    a := inf.ReadInteger;
    b := inf.ReadInteger;
    g[a, b] := true;
    g[b, a] := true;
  end;  
end;

procedure ReadAnswer(var strm : InStream; var a : TAnswer);
var
  k, i, x, prev : Integer;
  
begin
  FillChar(a, SizeOf(a), false);
  k := strm.ReadInteger;
  if (k < 1) or (k > n) then
    strm.Quit(_WA, Format('Invalid sequence size: %d', [k]));
  prev := 0;
  for i := 1 to k do begin
    x := strm.ReadInteger;
    if (x < 1) or (x > n) then
      strm.Quit(_WA, Format('Invalid person index: %d', [x]));
    if x <= prev then
      strm.Quit(_WA, Format('Invalid order: %d after %d', [x, prev]));
    a[x] := true;
    prev := x;
  end;  
end;

procedure GetDensity(var a : TAnswer; var p, q : Integer);
var
  i, j : Integer;
  
begin
  q := 0;
  for i := 1 to n do
    if a[i] then
      Inc(q);
      
  p := 0;
  for i := 1 to n do
    if a[i] then
      for j := i + 1 to n do
        if a[j] and g[i,j] then
          Inc(p);
end;

begin
  ReadGraph;
  ReadAnswer(ouf, pa);
  ReadAnswer(ans, ja);
  GetDensity(pa, pp, qp);
  GetDensity(ja, pj, qj);
  
  if pp * qj = qp * pj then
    Quit(_OK, Format('%d/%d', [pp, qp]));
    
  if pp * qj < qp * pj then
    Quit(_WA, Format('%d/%d < %d/%d', [pp, qp, pj, qj]));
    
  Quit(_Fail, Format('%d/%d > %d/%d ', [pp, qp, pj, qj]));
end.
