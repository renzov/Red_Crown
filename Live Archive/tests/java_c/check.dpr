(*
    Checker for NEERC'2006 Problem J: Java vs C
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

var
  ja, pa: String;

begin
  ja := Trim(ans.readstring);
  pa := Trim(ouf.readstring);

  if not ouf.SeekEof then
    Quit(_PE, 'Extra lines in output');

  if ja <> pa then 
    Quit(_WA, Format('expected: %s, found: %s', [ja, pa]));
	
  Quit(_OK, pa);
end.
