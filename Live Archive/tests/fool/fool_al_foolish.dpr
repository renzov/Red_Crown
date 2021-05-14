{$APPTYPE CONSOLE}
{$O+,Q-,R-}
{solution without ANY alpha-beta pruning (but with very non-optimal
memoization)}
uses Math;
const MaxC=6;
      ASize=1 shl 24;
      Suits='SCDH';
      Values='6789TJQKA';

type valset=set of 0..31;

procedure readr (var x:integer; a, b:integer);
begin
  assert (not seekeoln); read (x); assert ((a<=x) and (x<=b));
end;

procedure readl;
var c:char;
begin
  {$IFNDEF LINUX}
  read (c); assert (c=#13); 
  {$ENDIF}
  read (c); assert (c=#10);
end;


var S:array [0..MaxC*2-1] of char;
    V:array [0..MaxC*2-1] of integer;

procedure readcard (x:integer);
var c:char;
begin
  read (c);
  V[x]:=pos (c, Values);
  assert (V[x]>0);
  read (S[x]);
  assert (pos (S[x], Suits)>0);
end;

var n1, n2, n:integer;
    TR:char;
    D:array [0..ASize-1] of shortint;
    CO:array [0..MaxC*2-1, 0..MaxC*2-1] of boolean;

procedure dump (st:integer);
var j:integer;
begin
  write ('1:');
  for j:=0 to n-1 do
    if (st shr (j+j)) and 3 = 0 then
      write (' ', Values[V[j]], S[j]);
  writeln;
  write ('2:');
  for j:=0 to n-1 do
    if (st shr (j+j)) and 3 = 1 then
      write (' ', Values[V[j]], S[j]);
  writeln;
  write ('T:');
  for j:=0 to n-1 do
    if (st shr (j+j)) and 3 = 2 then
      write (' ', Values[V[j]], S[j]);
  writeln;
end;

function toss (st, c, c1, c2:integer; t:valset):shortint;forward;

function take (st, c1, c2, l, p:integer; t:valset):shortint;
var j:integer;
begin
  if toss (st, 0, c1, c2, [])>0 then
    take:=-1
  else
    take:=1;
  if l>0 then
    for j:=p to n-1 do
      if (((st shr (j+j)) and 3) = 0) and (V[j] in t) then 
        if take (st or (1 shl (j+j)), c1-1, c2+1, l-1, j+1, t)<0 then begin
          take:=-1; {exit}
        end;
end;


function cover (st, c, c1, c2, p:integer; t:valset):shortint;
var j, l:integer;
begin
  cover:=-1;
  if c1>0 then begin
    {first, try to cover}
    for j:=0 to n-1 do
      if (((st shr (j+j)) and 3) = 1) and CO[j, p] then begin
        {can cover}
        //writeln ('here');
        if toss (st xor (3 shl (j+j)), c, c1, c2-1, t+[V[j]])<0 then begin
          cover:=1; {exit}
        end;
      end;
    {forced to take... maybe it helps...}
    l:=c2-1;
    for j:=0 to n-1 do
      if ((st shr (j+j)) and 3) = 2 then begin
        st:=st xor (3 shl (j+j));
        inc (c2);
      end;
    cover:=max (Result, take (st, c1, c2, l, 0, t));
  end;
end;


function toss (st, c, c1, c2:integer; t:valset):shortint;
var s2, j:integer;
begin
  //dump (st);
  if D[st]<>0 then toss:=D[st] else begin
    if c1=0 then toss:=1 else 
    if c2=0 then toss:=-1 else begin
      toss:=-1;
      {decided to end turn}
      if c>0 then begin
        s2:=st;
        for j:=0 to n-1 do
          case ((s2 shr (j+j)) and 3) of
            2, 0: s2:=s2 or (1 shl (j+j));
            1:s2:=s2 and not (1 shl (j+j));
          end;
        if toss (s2, 0, c2, c1, []) < 0 then toss:=1;
      end;
      {decided to toss}
      for j:=0 to n-1 do
        if ((st shr (j+j)) and 3) = 0 then 
          if (c=0) or (V[j] in t) then 
            {try to toss}
            if cover (st or (1 shl (j+j+1)), c+1, c1-1, c2, j, t+[V[j]]) < 0 then 
              toss:=1; 
    end;
    D[st]:=Result;
  end;
end;

var i, j, st:integer;
    c:char;


begin
  reset (input, 'fool.in'); rewrite (output, 'fool.out');
  readr (n1, 1, MaxC);
  readr (n2, 1, MaxC);
  read (c); assert (c=' ');
  read (TR); assert (pos (TR, Suits)>0);
  readl;
  for i:=0 to n1-1 do begin
    readcard (i);
    if i<n1-1 then begin read (c); assert (c=' ') end else readl;
  end;
  st:=0;
  for i:=n1 to n1+n2-1 do begin
    readcard (i);
    if i<n1+n2-1 then begin read (c); assert (c=' ') end else readl;
    st:=st or (1 shl (i+i));
  end;
  assert (eof);
  n:=n1+n2;
  for i:=0 to n1+n2-1 do
    for j:=0 to n1+n2-1 do
      CO[i, j]:=((V[i]>V[j]) and (S[i]=S[j])) or ((S[i]=TR) and (S[j]<>TR));
  for i:=0 to n1+n2-1 do
    for j:=i+1 to n1+n2-1 do
      assert ((V[i]<>V[j]) or (S[i]<>S[j]));
  //dump (st);
  if toss (st, 0, n1, n2, [])>0 then writeln ('FIRST') else writeln ('SECOND');
end.