import java.util.*;
import java.io.*;

class Reader {
	public char lastRead;
	BufferedReader in = new BufferedReader( new InputStreamReader(System.in) );
	public Reader(){
		read();
	}
	void read(){
		int c = -1;
		try {
			do {
				c = in.read();
				c = c < 0 ? '?' : c;
				this.lastRead = (char)c;
			}
			while ( c != '(' && c != ')' && c != '.' && 
					c != '?' && !Character.isLetter(c) );
		}
		catch (Exception ex){}
	}
}

abstract class Expression{
	public static final int MaxCycle = 1000;
	public static Expression read( Reader r  ){
		if ( r.lastRead == 'L' ) return Lambda.read(r);
		if ( r.lastRead == '(' ) return Function.read(r);
		return Variable.read(r);
	}
	public Expression eval(int cycles){
		return this;
	}
	public Expression replace(char var,Expression e){
		return this;
	}
	public abstract void print(PrintWriter out);
	public boolean last(){ return false; }
}

class Lambda extends Expression {
	char var;
	Expression e;
	public Lambda(char v, Expression e){ this.var = v; this.e = e; }
	public static Expression read( Reader r ){
		r.read(); //Skip L
		char v = r.lastRead;
		r.read(); //Skip Variable
		r.read(); //Skip .
		Expression e = Expression.read(r);
		return new Lambda(v,e);
	}
	public Expression replace(char v, Expression ex){
		return (v==this.var)? this : new Lambda(this.var,this.e.replace(v, ex));
	}
	public void print(PrintWriter out){
		out.print("L" + this.var + "." );
		this.e.print(out);
	}
}

class Variable extends Expression {
	char value;
	public Variable(char v){ this.value = v; }
	public static Expression read( Reader r ){
		char v = r.lastRead; r.read();
		return new Variable(v);
	}
	public Expression replace( char var, Expression e ){
		return this.value == var? e : this;
	}
	public void print(PrintWriter out){ out.print(this.value); }
	public boolean last(){ return this.value == 'z'; }
}

class Function extends Expression {
	Expression func;
	Expression param;
	public Function(Expression f,Expression p){ this.func = f; this.param = p; }
	public static Expression read( Reader r ){
		r.read(); //Skip (
		Expression f = Expression.read(r);
		r.read(); //Skip )
		Expression p = Expression.read(r);
		return new Function(f, p);
	}
	public Expression eval(int cycles){
		if ( cycles > MaxCycle ) return new Undef();
		Expression f = this.func.eval(cycles+1);
		Expression p = this.param.eval(cycles+1);
		if ( !(f instanceof Lambda) ) return new Function(f, p);
		Lambda L = (Lambda) f;
		Expression funcEval = L.e.replace(L.var,p).eval(cycles+1);
		return funcEval;
	}
	public Expression replace(char v,Expression e){
		return new Function( this.func.replace(v, e) , this.param.replace(v, e) );
	}
	public void print( PrintWriter out ){
		out.print('('); this.func.print(out); out.print(')'); this.param.print(out);
	}
}

class Undef extends Expression {
	public void  print(PrintWriter out){
		out.print("unterminated");
	}
}

public class Main {
	static PrintWriter out = new PrintWriter(System.out);
	public static void main(String[] args) {
		Reader r = new Reader();
		while (true){
			Expression e = Expression.read(r);
			for ( int i=1; i <= 1000; ++i ){
				e = e.eval(0);
				if ( !(e instanceof Function) ) break;
			}
			e.print(out); out.println();
			if ( e.last() ) break;
		}
		out.close();
	}
}
