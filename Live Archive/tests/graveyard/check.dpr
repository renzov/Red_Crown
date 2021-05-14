(*
    Checker for NEERC'2006 Problem G: Graveyard
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

const
  EPS = 1.1e-4;

var
  ja, pa: Double;

begin
  ja := ans.ReadReal;
  pa := ouf.ReadReal;

  if not ouf.SeekEof then
    Quit(_PE, 'Extra lines in output');

  if Abs(ja - pa) > eps then
    Quit(_WA, Format('%.5f instead of %.5f', [pa, ja]));

  Quit(_OK, Format('%.5f', [pa]));
end.
