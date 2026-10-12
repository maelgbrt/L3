package fr.usmb.l3info.tp4;


import fr.usmb.l3info.tp4.parser.*;
import java_cup.runtime.Symbol;

public class Main {
	
    public static void main(String[] argv) throws Exception{
    	exemple();
    	question1();
    }


	private static void exemple() throws Exception {
    	System.out.println("****************** Exemple **************");
    	Parser p = new Parser(new TP4Scanner("(a)"));
    	Symbol s = p.parse();
    	String chaine = (String) s.value;
    	System.out.println(chaine);
	}
   
	

	private static void question1() {
    	System.out.println("****************** Question 1 **************");
		
	}
}

