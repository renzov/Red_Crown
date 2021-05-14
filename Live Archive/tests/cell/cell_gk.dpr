uses
    sysutils, math;

const
    max_n = 500;
    max_m = 1000000;
    max_k = 10000000;

type
    trow = array[0..max_n * 2 - 1] of int64;

var
    n, m, d, k: longint;

procedure mul(var a, b: trow);
var
    c: trow;
    i, k: longint;
begin
    for i := 0 to n - 1 do begin
        c[i] := 0;
        for k := 0 to n - 1 do begin
            c[i] := c[i] + a[(k - i + n) mod n] * b[(n - k) mod n];
        end;
        c[i] := c[i] mod m;
    end;
    a := c;
end;

var
    i, j: longint;
    v, p, a: trow;
    q: int64;
begin
    reset(input, 'cell.in');
    rewrite(output, 'cell.out');

    while not seekeof do begin
        readln(n, m, d, k);

        assert((1 <= n) and (n <= max_n));
        assert((1 <= m) and (m <= max_m));
        assert((0 <= d) and (d < n / 2));
        assert((1 <= k) and (k <= max_k));

        for i := 0 to n - 1 do begin
            read(v[i]);
            assert((0 <= v[i]) and (v[i] < m));
        end;

        for j := -d to d do begin
            p[(j + n) mod n] := 1;
        end;

        a[0] := 1;
        while k <> 0 do begin
            if k mod 2 = 1 then begin
                mul(a, p);
            end;
            mul(p, p);
            k := k div 2;
        end;

        for i := 0 to n - 1 do begin
            q := 0;
            for j := 0 to n - 1 do begin
                q := q + (a[(i - j + n) mod n] * v[j]);
            end;
            write(q mod m, ' ');
        end;

        writeln;
    end;
end.