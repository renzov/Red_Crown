(*
    Checker for NEERC'2006 Problem A: ASCII Art
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

var
  ja, pa: String;
  wa: String;
  i: Integer;
begin
  while not ans.SeekEof do begin
    ja := ans.ReadString;
    pa := ouf.ReadString;
    if Length(pa) <> Length(ja) then
      Quit(_pe, Format('Wrong line length "%s"', [pa]));
    for i := 1 to Length(pa) do 
      if not (pa[i] in ['.', '+', 'o', '$', '#']) then
        Quit(_pe, Format('Wrong character in line "%s"', [pa]));
    if (wa = '') and (pa <> ja) then
      wa := Format('"%s" instead of "%s"', [pa, ja]);
  end;
  if not ouf.SeekEof then
    Quit(_pe, 'Extra lines in output');
  if wa <> '' then 
      Quit(_wa, wa);
  Quit(_ok, 'Ok');
end.
