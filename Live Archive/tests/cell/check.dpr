(*
    Checker for NEERC'2006 Problem C: Cell Automaton
    (C) Georgiy Korneev, Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

var
  n, i, ja, pa: Longint;
begin
  n := inf.ReadLongint();

  for i := 1 to n do begin
    ja := ans.ReadLongint();
    pa := ouf.ReadLongint();

    if ja <> pa then begin
      Quit(_WA, Format('Cell %d: %d instead %d', [i, pa, ja]));
    end;
  end;
  Quit(_OK, Format('%d cells', [n]));
end.
