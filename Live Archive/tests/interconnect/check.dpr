(*
    Checker for NEERC'2006 Problem I: Interconnect
    (C) Andrew Lopatin, Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

uses
  TestLib, SysUtils;

const
  EPS = 1.1e-6;

var
  ja, pa: Extended;
begin
  ja := ans.ReadReal();
  pa := ouf.ReadReal();

  if not ouf.SeekEof then
    Quit(_PE, 'Extra lines in output');

  if abs(ja - pa) > EPS then 
    Quit(_WA, Format('%.7f instead of %.7f', [pa, ja]));

  Quit(_OK, Format('%.7f', [pa]));
end.