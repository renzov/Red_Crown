{$APPTYPE CONSOLE}
{$O-,Q+,R+}
uses SysUtils;
const MaxN=30;
      MaxM=1000;
      HSize=17239;

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

type tarr=array [1..MaxN+1] of integer;
var h:array [0..HSize-1, 1..MaxN] of integer;
    z:array [0..HSize-1] of boolean;
    pos, n:integer;

function hash (var a:tarr):integer;
var i, j, h1, h2:integer;
    flag:boolean;
begin
  h1:=0; h2:=0;
  for i:=1 to n do begin
    h1:=h1*3+a[i]; while h1>=HSize do dec (h1, HSize);
    h2:=h2*5+a[i]; while h2>=HSize-1 do dec (h2, HSize-1);
  end;
  while z[h1] do begin
    flag:=true;
    for j:=1 to n do if a[j]<>h[h1, j] then begin flag:=false; break end;
    if flag then begin Result:=h1; exit end;
    inc (h1, h2); if h1>=HSize then dec (h1, HSize);
  end;
  z[h1]:=true;
  for j:=1 to n do h[h1, j]:=a[j];
  Result:=h1;
end;

var D:array [0..HSize-1] of extended;
    f:array [0..HSize-1] of boolean;

function rec (var a:tarr):extended;
var i, j, k, p, x, s, t:integer;
    b:tarr;
    r:extended;
begin
  {for i:=1 to n do begin
    if a[i]=0 then break;
    write (a[i], ' ');
  end;
  writeln;}
  x:=hash (a);
  if f[x] then begin Result:=D[x]; exit end;
//  inc (pos);
  fillchar (b, sizeof (b), 0);
  s:=0; r:=0;
  for i:=1 to n do
    if a[i]>0 then begin
      inc (s, a[i]*(a[i]-1));
      for j:=i+1 to n do
        if a[j]>0 then begin
          k:=1; t:=a[i]+a[j];
          while a[k]>t do begin
            b[k]:=a[k]; inc (k);
          end;
          p:=k; b[k]:=t; inc (k);
          while a[p]>0 do begin
            if (p<>i) and (p<>j) then begin
              b[k]:=a[p]; inc (k);
            end;
            inc (p);
          end;
          r:=r+rec (b)*(a[i]*a[j]);
        end;
      end;
  r:=(r*2+n*(n-1))/(n*(n-1)-s);
  f[x]:=true;
  D[x]:=r;
  Result:=r;
  {for i:=1 to n do begin
    if a[i]=0 then break;
    write (a[i], ' ');
  end;
  writeln (r);}
end;


var i, j, k, m, t, u, v:integer;
    g:array [1..MaxN] of boolean;
    c:array [1..MaxN] of integer;
    a:tarr;

begin
//  pos:=0;
  reset (input, 'interconnect.in'); rewrite (output, 'interconnect.out');
  readr (n, 1, MaxN); 
  readr (m, 0, MaxM);
  readl;
  fillchar (g, sizeof (g), true);
  a[1]:=n;
  t:=hash (a);
  F[t]:=true;
  a[1]:=0;
  for i:=1 to n do c[i]:=i;
  for i:=1 to m do begin
    readr (u, 1, n);
    readr (v, 1, n);
    assert (u<>v);
    if c[v]<>c[u] then begin
      t:=c[v];
      for j:=1 to n do
        if c[j]=t then c[j]:=c[u];
      g[t]:=false;
    end;
    readl;
  end;
  k:=0;
  for i:=1 to n do
    if g[i] then begin
      inc (k);
      for j:=1 to n do
        if c[j]=i then inc (a[k]);
    end;
  assert (eof);
  for i:=1 to n do
    for j:=i+1 to n do
      if a[j]>a[i] then begin
        t:=a[i]; a[i]:=a[j]; a[j]:=t;
      end;
  writeln (rec (a):0:15);
end.