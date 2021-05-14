const
	MAX_N = 100;
	
	INPUT_FILENAME = 'hard.in';
	OUTPUT_FILENAME = 'hard.out';
	
var
	n, m : integer;
	g : array[1..MAX_N, 1..MAX_N] of boolean;
	used, answer : array[1..MAX_N] of boolean;
	deg : array[1..MAX_N] of integer;
	
	a, b : integer;
	i, j, k : integer;
	            
	maxDen, den: real;
	
	numEdges : integer;
	count : integer;
	
begin
	reset(input, INPUT_FILENAME);
	read(n, m);
	fillchar(g, sizeof(g), false);
	fillchar(deg, sizeof(deg), 0);
	for i := 1 to m do begin
		read(a, b);
		g[a,b] := true;
		g[b,a] := true;
		inc(deg[a]);
		inc(deg[b]);
	end;
	
	maxDen := -1;
	numEdges := 0;
	fillchar(used, sizeof(used), false);
	for i := 1 to n do begin
		k := 0;
		for j := 1 to n do
			if not used[j] and ((k = 0) or (deg[j] > deg[k])) then
				k := j;
		
		for j := 1 to n do
			if used[j] and g[j,k] then
				inc(numEdges);

		den := numEdges / i;
		used[k] := true;
		if den > maxDen then begin
			maxDen := den;
			answer := used;
		end;	
	end;
	
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


