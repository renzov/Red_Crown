{$APPTYPE CONSOLE}
{$R+,Q+,S+,H+,O-}

uses
  Math, SysUtils;

Type
  Integer=LongInt;
  Real=Extended;

Const
  TaskID='java_c';
  InFile=TaskID+'.in';
  OutFile=TaskID+'.out';

var
  s, ss: string;

Procedure Load;
Begin
  ReSet(Input,InFile);
  readln(s);
  s := trim(s);
  Close(Input);
End;

Procedure Solve;
var
  b: boolean;
  i: integer;
Begin
  b := true;
  for i := 1 to length(s) do begin
    if (s[i] in ['A'..'Z']) then begin
      b := false;
      break;
    end;
    if (s[i] = '_') then begin
      if (i = 1) or (i = length(s)) then begin
        b := false;
        break;
      end;
      if (s[i - 1] = '_') then begin
        b := false;
        break;
      end;
    end;
  end;
  if b then begin
    ss := s[1];
    for i := 2 to length(s) do begin
      if (s[i - 1] <> '_') then begin
        if (s[i] <> '_') then
          ss := ss + s[i];
      end else begin
        ss := ss + uppercase(s[i]);
      end;
    end;
    exit;
  end;
  b := true;
  for i := 1 to length(s) do begin
    if s[i] = '_' then begin
      b := false;
      break;
    end;
  end;
  if (s[1] in ['A'..'Z']) then b := false;
  if b then begin
    ss := '';
    for i := 1 to length(s) do begin
      if (s[i] in ['A'..'Z']) then begin
        ss := ss + '_' + lowercase(s[i]);
      end else begin
        ss := ss + s[i];
      end;
    end;
    exit;
  end;
  ss := 'Error!';
End;

Procedure Save;
Begin
  ReWrite(Output,OutFile);
  writeln(ss);
  Close(Output);
End;

begin
  Load;
  Solve;
  Save;
end.
