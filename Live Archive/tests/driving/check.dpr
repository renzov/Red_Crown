(*
    Checker for NEERC'2006 Problem D: Driving Directions
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

const
  EPS = 1.1e-6;
  NS = -1;

var
  ja, pa: Double;

function Get(var strm: InStream): Double;
var
  s: String;
  code: Integer;
begin
  s := Trim(strm.ReadString);
  if s = 'no solution' then
    Result := NS
  else begin
    Val(s, Result, code);
    if code <> 0 then 
      strm.Quit(_pe, 'Expected real instead of "' + s + '"');
    if Result < -EPS then
      strm.Quit(_wa, Format('%.7f -- negative number', [Result]));
  end;
end;

begin
  ja := Get(ans);
  pa := Get(ouf);

  if not ouf.SeekEof then
    Quit(_pe, 'Extra lines in output');

  if Abs(ja - pa) > eps then
    Quit(_wa, Format('%.7f instead of %.7f', [pa, ja]));

  if ja = NS then
    Quit(_ok, 'no solution')
  else
    Quit(_ok, Format('%.7f', [ja]));
end.
