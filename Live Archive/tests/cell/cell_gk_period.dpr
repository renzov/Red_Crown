uses
    sysutils, math;

const
    max_n = 1000;

type
    trow = array [0..max_n - 1] of longint;

var
    n, m, k, d: longint;
    v1, v2: trow;
    i, t: longint;

procedure next(var v: trow);
var
    p: trow;
    i: longint;
    s: longint;
begin
    s := 0;
    for i := 0 to 2 * d do begin
        s := s + v[i];
    end;
    s := s mod m;

    p := v;
    for i := 0 to n - 1 do begin
        v[(i + d) mod n] := s;
        s := (s - p[i] + p[(2 * d + i + 1) mod n] + m) mod m;
    end;
end;

var
    f: boolean;
begin
    reset(input, 'cell.in');
    rewrite(output, 'cell.out');

    while not seekeof do begin
        readln(n, m, d, k);

        for i := 0 to n - 1 do begin
            read(v1[i]);
            //v2[i] := v1[i];
        end;

        for t := 1 to k do begin
            next(v1);
            next(v2);
            next(v2);
            f := true;
            for i := 1 to n do begin
                f := f and (v1[i] = v2[i]);
            end;
            if f then break;
        end;

        for i := 0 to n - 1 do begin
            write(v1[i], ' ');
        end;
        writeln;
        writeln(t);
    end;
end.