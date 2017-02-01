import java.util.*;
import java.io.*;

enum Type { MINUS,PLUS,MULT,VAR,INT };

class Node {
	public String token;
	public Node left;
	public Node right;
	public int number;
	public Type type;
	Node(Type type){
		this.type = type;
	}
	Node (){}
}

public class Main {
	static BufferedReader in = new BufferedReader( new InputStreamReader(System.in) );
	static PrintWriter out = new PrintWriter(System.out);
	static StringTokenizer parser;
	static HashMap<String,Integer> map = new HashMap<String, Integer>();
	static HashMap<Integer,Node> mem = new HashMap<Integer, Node>();
	static ArrayList<Boolean> visited = new ArrayList<Boolean>(); 
	static int N = 0;
	static String act_token;
	static boolean undef;
	static int p;
	static String line;
	public static void nextToken(){
		act_token = "";
		while (p < line.length() && Character.isSpaceChar(line.charAt(p))) p++;
		if (p >= line.length()) return;
		switch (line.charAt(p)){
			case ':' : p++; act_token = ":="; ++p; break;
			case '(' : p++; act_token = "("; break;
			case ')' : p++; act_token = ")"; break;
			case '+' : p++; act_token = "+"; break;
			case '-' : p++; act_token = "-"; break;
			case '*' : p++; act_token = "*"; break;
			default :
				while (p < line.length() && Character.isLetterOrDigit(line.charAt(p))){
					act_token += line.charAt(p);
					p++;
				}
				break;
		}
	}
	
	public static int evaluate(Node node){
		if (undef) return 0;
		if (node.type == Type.INT){
			return node.number;
		}
		if (node.type == Type.MULT){
			return evaluate(node.left) * evaluate(node.right);
		}
		if (node.type == Type.PLUS){
			return evaluate(node.left) + evaluate(node.right);
		}
		if (node.type == Type.MINUS){
			return evaluate(node.left) - evaluate(node.right);
		}
		if (node.type == Type.VAR){
			if (map.containsKey(node.token)){
				int idx = map.get(node.token);
				if (visited.get(idx)){
					undef = true;
					return 0;
				} 
				visited.set(idx,true);
				return evaluate(mem.get(idx));
			}
			else {
				undef = true;
			}
		}
		return 0;
	}
	
	public static Node Factor(){
		Node n = null;
		if (act_token.compareTo("(") == 0){
			nextToken();
			n = Expression();
			nextToken();
		}
		else {
			if (act_token.compareTo("-") == 0){
				nextToken();
				int num = Integer.parseInt(act_token);
				num *= -1;
				n = new Node(Type.INT);
				n.number = num;
				n.left = n.right = null;
				nextToken();
			}
			else {
				try {
					int num = Integer.parseInt(act_token);
					n = new Node(Type.INT);
					n.number = num;
					n.left = n.right = null;
				}
				catch (Exception ex){
					/* Es variable */
					n = new Node(Type.VAR);
					n.token = act_token;
					n.left = n.right = null;
				}
				finally {
					nextToken();
				}
			}
		}
		return n;
	}
	
	public static Node Term(){
		Node left = null;
		Node right = null;
		Node n = null;
		left = Factor();
		while (act_token.compareTo("*") == 0){
			nextToken();
			right = Term();
			n = new Node(Type.MULT);
			n.left = left;
			n.right = right;
			left = n;
		}
		return left;
	}
	
	public static Node Expression(){
		Node n = null;
		Node left = null;
		Node right = null;
		left = Term();
		while (act_token.compareTo("+")==0 || act_token.compareTo("-")==0){
			if (act_token.compareTo("+") == 0){
				nextToken();
				right = Term();
				n = new Node(Type.PLUS);
				n.left = left;
				n.right = right;
				left = n;
			}
			else if (act_token.compareTo("-") == 0){
				nextToken();
				right = Term();
				n = new Node(Type.MINUS);
				n.left = left;
				n.right = right;
				left = n;
			}
			else break;
		}
		return left;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			while (true){
				line = in.readLine();
				p = 0;
				nextToken();
				if (act_token.compareTo("PRINT") == 0){
					nextToken();
					if (map.containsKey(act_token)){
						undef = false;
						int idx = map.get(act_token);
						for (int i=0; i < N; ++i){
							visited.set(i, false);
						}
						visited.set(idx, true);
						int res = evaluate(mem.get(idx));
						if (undef) out.println("UNDEF");
						else out.println(res);
					}
					else {
						out.println("UNDEF");
					}
				}
				else if (act_token.compareTo("RESET") == 0){
					N = 0;
					mem.clear();
					map.clear();
					visited.clear();
				}
				else if (act_token.compareTo("") != 0){
					/* taking the ":=" */
					String tok = act_token;
					nextToken();
					nextToken();
					Node n = Expression();
					if (map.containsKey(tok)){
						mem.put(map.get(tok), n);
					}
					else {
						map.put(tok, N);
						visited.add(false);
						mem.put(N, n);
						N++;
					}
				}
			}
		}
		catch (Exception ex){
			
		}
		finally {
			out.close();
		}
	}

}
