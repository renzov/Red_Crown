const
	MAX_N = 100;
	
	INPUT_FILENAME = 'hard.in';
	OUTPUT_FILENAME = 'hard.out';
	
var
	n, m : integer;
	g : array[1..MAX_N, 1..MAX_N] of boolean;
	used, answer : array[1..MAX_N] of boolean;
	nbr : array[1..MAX_N] of integer;
	
	a, b : integer;
	i : integer;
	            
	maxDen, den: real;
	
	numEdges : integer;
	count : integer;

procedure use(i : integer);
var
	j : integer;
	
begin
	inc(numEdges, nbr[i]);
	for j := 1 to n do
		if g[i,j] then
			inc(nbr[j]);
	used[i] := true;
end;

procedure tryFrom(start : integer);
var
	i, j, k : integer;
	
begin
	numEdges := 0;
	fillchar(used, sizeof(used), false);
	fillchar(nbr, sizeof(nbr), 0);
	use(start);
	for i := 1 to n do begin
		k := 0;
		for j := 1 to n do
			if not used[j] and ((k = 0) or (nbr[j] > nbr[k])) then
				k := j;

		use(k);		
		den := numEdges / i;
		if den > maxDen then begin
			maxDen := den;
			answer := used;
		end;	
	end;
end;
	
begin
	reset(input, INPUT_FILENAME);
	read(n, m);
	fillchar(g, sizeof(g), false);
	for i := 1 to m do begin
		read(a, b);
		g[a,b] := true;
		g[b,a] := true;
	end;
	
	maxDen := -1;
	for i := 1 to n do
		tryFrom(i);
	
	count := 0;
	for i := 1 to n do
		if answer[i] then
			inc(count);

	rewrite(output, OUTPUT_FILENAME);		
	writeln(count);
	for i := 1 to n do 
		if answer[i] then
			writeln(i);
	close(output);		
end.


