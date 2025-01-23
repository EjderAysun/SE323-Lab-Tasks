package LAB_3.LAB3_Solutions.LAB3_3_JAVA;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Process implements Const {	
	int charClass;
	char nextChar;
	int lexLen;
	int token;
	int nextToken;
	BufferedReader r = null;
	StringBuilder lexeme = null;
	
	void getChar() {	
		try {
			nextChar = (char) r.read();		
		} catch (IOException e) {
			nextChar =  (char) EOF;
		}
		if (Character.isLetter(nextChar))
			charClass = LETTER;
		else if (Character.isDigit(nextChar))
			charClass = DIGIT;
		else 
			charClass = UNKNOWN;
	}
	
	void addChar() {
		lexeme.append(nextChar);
	}
	void getNonBlank() {
		while  (Character.isSpaceChar(nextChar)) 
			getChar();
	}
	
	int lookup(char ch) {
		switch (ch) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		// e
		case '<':
			addChar();
			nextToken = LT_OP;
			break;
		case '>':
			addChar();
			nextToken = GT_OP;
			break;
		case '{':
			addChar();
			nextToken = RBR_OP;
			break;
		case '}':
			addChar();
			nextToken = LBR_OP;
			break;
		// in addition
		case '=':
			addChar();
			nextToken = EQ_SIGN;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
		}
		return nextToken;
	}

	int lex() {
		lexeme = new StringBuilder();
		getNonBlank();
		switch (charClass) {
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		case EOF:
			nextToken = EOF;
			lexeme = new StringBuilder("EOF");
			break;
		}
		System.out.println("Next Token is : "+ nextToken + " Next lexeme is " +  lexeme.toString());
		return nextToken;
	}
	public void doIt() {		
		System.out.println("Starting ..... \n");
		try {
			r = new BufferedReader(new FileReader("LAB_3/Mission_Documents#3/front.txt"));
			getChar();
			do {
				lex();
			} while (nextToken!=EOF);
		} catch (FileNotFoundException e) {
			System.out.println("file not found");
		}
				
	}	
}