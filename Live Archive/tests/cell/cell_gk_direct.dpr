uses
    sysutils, math;

const
    max_n = 1000;

var
    n, m, d, k: longint;
    i, j, t: longint;
    v, p: array [0..max_n - 1] of longint;
begin
    reset(input, 'cell.in');
    rewrite(output, 'cell.out');

    while not seekeof do begin
        readln(n, m, d, k);

        for i := 1 to n do begin
            read(v[i]);
        end;

        for t := 1 to k do begin
            p := v;
            for i := 1 to n do begin
                v[i] := 0;
                for j := 1 to n do begin
                    if (min(abs(i - j), n - abs(i - j)) <= d) then begin
                        v[i] := v[i] + p[j];
                    end;
                end;
                v[i] := v[i] mod m;
            end;
        end;

        for i := 1 to n do begin
            write(v[i], ' ');
        end;
        writeln;
    end;
end.