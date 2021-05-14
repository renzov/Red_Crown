(*
    Checker for NEERC'2006 Problem F: Fool's Game
    (C) Andrew Lopatin, Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

function Parse(var strm: InStream): String;
begin
  Result := strm.ReadString;
  if (Result <> 'FIRST') and (Result <> 'SECOND') then
    strm.Quit(_PE, Result);
end;

var
  ja, pa: String;
begin
  ja := Parse(ans);
  pa := Parse(ouf);

  if not ouf.SeekEof then
    Quit(_PE, 'Extra lines in output');

  if (ja <> pa) then begin
    Quit(_WA, Format('%s instead of %s', [pa, ja]));
  end;

  Quit(_OK, pa);
end.
