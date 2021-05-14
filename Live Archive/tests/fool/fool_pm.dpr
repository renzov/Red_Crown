{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='fool';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';

  ranks = '6789TJQKA';
  suits = 'SCDH';

var
  n, m, tr: integer;
  r, s: array[1..12] of integer;

Procedure Load;
var
  ch: char;
  i: integer;
Begin
  ReSet(Input,InFile);
  read(n, m);
  if not seekeof then begin
    read(ch);
    tr := pos(ch, suits);
  end;
  for i := 1 to n + m do begin
    if not seekeof then begin
      read(ch);
      r[i] := pos(ch, ranks);
      read(ch);
      s[i] := pos(ch, suits);
    end;
  end;
  Close(Input);
End;

var
  d: array[0..1 shl 25] of byte;

function win(st: integer; rks: integer; n1, n2, qq: integer): boolean;
var
  i, j: integer;
  res: integer;
  ss, nn: integer;
  b: boolean;

label q;

begin
  if (d[st] = 1) then begin
    win := false;
    exit;
  end else if (d[st] = 2) then begin
    win := true;
    exit;
  end;
  if (n1 = 0) then begin
    res := 2;
  end else if n2 = 0 then begin
    res := 1;
  end else if (st shr ((n + m) * 2)) = 1 then begin
    if qq < n2 then
      for i := 1 to n + m do if (((st shr (2 * i - 2)) and 3) = 0) and (rks and (1 shl r[i]) > 0) then begin
        if win(st xor (2 shl (2 * i - 2)), rks, n1 - 1, n2, qq + 1) then begin
          res := 2;
          goto q;
        end;
      end;
    ss := st xor (1 shl ((n + m) * 2));
    nn := n2;
    for i := 1 to n + m do if (((st shr (2 * i - 2)) and 3) = 2) then begin
      ss := ss xor (3 shl (2 * i - 2));
      nn := nn + 1;
    end;
    if (win(ss, 0, n1, nn, 0)) then begin
      res := 2;
    end else begin
      res := 1;
    end;
  end else if rks = 0 then begin
    res := 1;
    for i := 1 to n + m do if ((st shr (2 * i - 2)) and 3) = 0 then begin
      b := true;
      if (n1 = 3) and (n2 = 6) then begin
        writeln('!!!');
      end;
      for j := 1 to n + m do if ((st shr (2 * j - 2)) and 3) = 1 then begin
        if ((s[j] = s[i]) and (r[j] > r[i])) or ((s[j] = tr) and (s[i] <> tr)) then begin
          if not win(st xor (2 shl (2 * i - 2)) xor (3 shl (2 * j - 2)), (1 shl r[i]) or (1 shl r[j]), n1 - 1, n2 - 1, 0) then begin
            b := false;
            break;
          end;
        end;
      end;
      if not b then continue;
      if not win(st xor (2 shl (2 * i - 2)) or (1 shl ((n + m) * 2)), 1 shl r[i], n1 - 1, n2, 1) then continue;
      res := 2;
      break;
    end;
  end else begin
    for i := 1 to n + m do if (((st shr (2 * i - 2)) and 3) = 0) and (rks and (1 shl r[i]) > 0) then begin
      b := true;
      for j := 1 to n + m do if ((st shr (2 * j - 2)) and 3) = 1 then begin
        if ((s[j] = s[i]) and (r[j] > r[i])) or ((s[j] = tr) and (s[i] <> tr)) then begin
          if not win(st xor (2 shl (2 * i - 2)) xor (3 shl (2 * j - 2)), rks or (1 shl r[i]) or (1 shl r[j]), n1 - 1, n2 - 1, qq) then begin
            b := false;
            break;
          end;
        end;
      end;
      if not b then continue;
      if not win(st xor (2 shl (2 * i - 2)) or (1 shl ((n + m) * 2)), rks or (1 shl r[i]), n1 - 1, n2, qq + 1) then continue;
      res := 2;
      goto q;
    end;
    ss := st;
    for i := 1 to n + m do if (((st shr (2 * i - 2)) and 3) <= 2) then begin
        ss := ss xor (1 shl (2 * i - 2));
    end;
    if (win(ss, 0, n2, n1, 0)) then res := 1 else res := 2;
  end;
  q:
//  writeln(st, ' ', res);
  d[st] := res;
  result := res = 2;
end;

var
  winner: string;

Procedure Solve;
var
  st, i: integer;
Begin
  st := 0;
  for i := n + 1 to n + m do st := st or (1 shl (2 * i - 2));
  if win(st, 0, n, m, 0) then begin
    winner := 'FIRST';
  end else begin
    winner := 'SECOND';
  end;
End;

Procedure Save;
Begin
  ReWrite(Output,OutFile);
  writeln(winner);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
