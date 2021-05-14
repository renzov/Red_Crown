uses
    sysutils, math;

const
    max_n = 1000;

var
    n, m, k, d: longint;
    v, p: array [0..max_n - 1] of longint;
    i, t, s: longint;
begin
    reset(input, 'cell.in');
    rewrite(output, 'cell.out');

    while not seekeof do begin
        readln(n, m, d, k);

        for i := 0 to n - 1 do begin
            read(v[i]);
        end;

        for t := 1 to k do begin
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

        for i := 0 to n - 1 do begin
            write(v[i], ' ');
        end;
        writeln;
    end;
end.