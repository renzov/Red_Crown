(*
    Checker for NEERC'2006 Problem E: Exchange
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

function Get(var strm: InStream): String;
begin
  Result := strm.ReadString;
  if Length(Result) < 5 then
     strm.Quit(_pe, Format('Invalid message "%s"', [Result]));
  if Copy(Result, 1, 5) = 'QUOTE' then begin
    ; // check? 
  end else if Copy(Result, 1, 5) = 'TRADE' then begin
    ; // check? 
  end else
     strm.Quit(_pe, Format('Invalid message "%s"', [Result]));
end;

var
  ja, pa: String;
  wa: String;
  n: Integer;
begin
  n := 0;
  while not ouf.SeekEof do begin
    pa := Get(ouf);
    if wa = '' then begin 
      if ans.SeekEof then
        wa := Format('Extra message "%s"', [pa])
      else begin
        ja := Get(ans);
        if pa <> ja then
          wa := Format('"%s" instead of "%s"', [pa, ja]);
      end;
    end;
    Inc(n);
  end;
  if (wa = '') and not ans.SeekEof then
    Quit(_wa, 'Missing messages in output');
  if wa <> '' then 
      Quit(_wa, wa);
  Quit(_ok, Format('Ok: %d', [n]));
end.
