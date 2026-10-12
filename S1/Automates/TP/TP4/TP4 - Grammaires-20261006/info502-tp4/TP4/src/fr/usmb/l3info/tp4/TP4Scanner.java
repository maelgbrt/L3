package fr.usmb.l3info.tp4;

import fr.usmb.l3info.tp4.parser.sym;
import java_cup.runtime.*;

public class TP4Scanner {
    /* single lookahead character */
    private int cnt= 0;
	private final String s;
	
    /* we use a SymbolFactory to generate Symbols */
    private final SymbolFactory sf = new ComplexSymbolFactory();


    public TP4Scanner(String string) {
    	this.s = string;
	}

    /* recognize and return the next complete token */
    public Symbol next_token()
    {
    	if (cnt < s.length()) {
    		Character next_char = s.charAt(cnt); 
    		cnt++;	
    		switch (next_char) {
    		case '0':
    			return sf.newSymbol("ZERO", sym.ZERO);
    		//case '1': return sf.newSymbol("ONE", sym.ONE);
    		case 'a': case 'b': case 'c': case 'd': case 'e':
   				return sf.newSymbol("LETTRE",sym.LETTRE, next_char);
    		case '(': return sf.newSymbol("LPAREN",sym.LPAREN);
    		case ')': return sf.newSymbol("RPAREN",sym.RPAREN);
    		}
    	
    	}
    	return sf.newSymbol("EOF",sym.EOF);
    }
};