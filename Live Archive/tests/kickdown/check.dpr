(*
    Checker for NEERC'2006 Problem K: Kickdown
    (C) Georgiy Korneev, Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

uses
  TestLib, SysUtils;

var
  ja, pa: Longint;
begin
  ja := ans.ReadLongint();
  pa := ouf.ReadLongint();
    
  if (ja <> pa) then begin
    Quit(_WA, Format('%d instead %d', [pa, ja]));
  end;

  Quit(_OK, Format('%d', [ja]));
end.
