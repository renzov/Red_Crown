(*
    Checker for NEERC'2006 Problem B: Billing Tables
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

var
  jn, pn: Integer;
  ja, pa: String;
  wa: String;
  i: Integer;
begin
  jn := ans.ReadInteger;
  pn := ouf.ReadInteger;
  if jn <> pn then
    wa := Format('"%d" instead of "%d"', [pn, jn]);
  if not ouf.SeekEoln then 
    Quit(_pe, 'Extra data on first line');
  ouf.NextLine;
  ans.NextLine;
  for i := 1 to pn do begin
    pa := ouf.ReadString;
    if wa = '' then begin 
      ja := ans.ReadString;
      if pa <> ja then
        wa := Format('"%s" instead of "%s"', [pa, ja]);
    end;
  end;
  if not ouf.SeekEof then
    Quit(_pe, 'Extra lines in output');
  if wa <> '' then 
      Quit(_wa, wa);
  Quit(_ok, Format('Ok: %d', [pn]));
end.
