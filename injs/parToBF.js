/*

Brainfuck-extension	 ::= Def_region Main_region
Def_region ::= "DEF" Definition "END"
Definition ::= ("def" Identifier "(" arg_list ")" "{" expression "}") *
arg_list ::= arg ("," arg)* | 
expression ::= "+" | "-" | "<" | ">" | "[" | "]" | "$"[0-9]+ | "="[0-9]+ | Identifier "(" arg_list ")"
Main_region ::= "MAIN" expression*
arg ::= "$"constant | variable

*/

var	fs = require("fs"),
	path = require('path'),
	util = require('util'),
	lex = require('./lex.js'),
	CODE = "",
	FUNC_LIST = new Array();
	;

var funcName = "";
var CurrentRegion = "";


module.exports = {
	input : function(s) {
		syntax = require(s);
	},

	parse : function() {
		start();
	}
};

function error_msg(msg) {
	if(msg == undefined) {
		console.log("line " + lex.linenum + " : syntax error " + "Unrecongnized token: " + lex.currentToken);
	} else {
		console.log("line " + lex.linenum + " : " + msg);
	}
}

function expect(symbol) {
	if(symbol()) {
		lex.nextToken();
		return true;
	} else {
		error_msg("Unrecongnized token: " + lex.currentToken + " by " + symbol.name);
		return false;
	}
}

function accept(symbol) {
	if(symbol()) {
		lex.nextToken();
		return true;
	} else {
		return false;
	}
}

/*  code generator  */
function codesave(code) {
	CODE = CODE + code;
}

function codegen() {
	console.log(CODE);
	CODE = "";
}

/*	SYNTEX	*/
function start() {

	CurrentRegion = "DEF";
	def_region();

	CurrentRegion = "MAIN";
	main_region();

	codegen();
}

function def_region() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		default:
			// nothing
		break;
		
		case 'DEF_BLOCK':
			lex.nextToken();

			do {
				def_func();
			} while(!accept(END_BLOCK));

		break;
	}
}

function def_func() {
	var d = lex.lookahead();
	
	switch(lex.pattern) {
		default:
			lex.nextToken();
		break;

		case 'DEF_FUNC':
			codesave("#define ");
			lex.nextToken();

			funcName = lex.lookahead();
			expect(IDENTIFIER);
			codesave(funcName);

			expect(LPARENTHESES);
			codesave("(");
				arg_list();
			expect(RPARENTHESES);
			codesave(") \\\n");

			
			expect(LBRACE);

				expression();

			expect(RBRACE);
			codesave("\n");
			
		break;
	}
}

function arg_list() {
	var d = lex.lookahead();
	var arg = new Array();

	switch(lex.pattern) {
		case 'IDENTIFIER':
			do {
				expect(IDENTIFIER);
				arg.push(lex.currentToken);
			} while(accept(COMMA))
		break;
	}

	var arglist = "argc";
	for(var i=0; i<arg.length; ++i) {
		arglist = arglist + ", " + arg[i];
	}
	codesave(arglist);

	FUNC_LIST[funcName] = arg.length;

}

function main_region() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		default:
			expression();
		break;

		case 'MAIN_BLOCK':
			lex.nextToken();

			expression();
		break;
	}
}

function expression() {
	var d = lex.lookahead();

	switch(lex.pattern) {
		case "INC":
			codesave("+");
		break;

		case "DEC":
			codesave("-");
		break;

		case "READ":
		case "COMMA":
			codesave(",");
		break;

		case "PRINT":
			codesave('.');
		break;

		case "FORWARD":
			codesave(">");
		break;

		case "BACKWARD":
			codesave("<");
		break;

		case "BEGIN_LOOP":
			codesave("[");
		break;

		case "END_LOOP":
			codesave("]");
		break;

		case "REF":
			ref_expression();
		break;

		case "ASSIGN":
			assign_expression();
		break;

		case "HALT":
		break;

		case "IDENTIFIER":
			if(FUNC_LIST[d] == null) { // not a function
				if(NUMBER()) {
					ref_expression();
				}
				else {
					codesave(d);
				}
			} else {
				invoke_expression();
			}

		break;

		default:
			//
			return;
		break;
	}

	lex.nextToken();

	expression();
}


function ref_expression() {
	var d = lex.lookahead();
	var addr = 0;
	switch(lex.pattern) {
		case "REF":
			lex.nextToken();
			addr = lex.lookahead();
			expect(NUMBER);
			codesave("$" + addr + " ");
		break;
	}
}

function assign_expression() {
	var d = lex.lookahead();
	var value = 0;
	switch(lex.pattern) {
		case "ASSIGN":
			lex.nextToken();
			value = lex.lookahead();
			expect(NUMBER);
			codesave("=" + value + " ");
		break;
	}
}


function invoke_expression() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		case "IDENTIFIER":
			codesave(d);
			lex.nextToken();

			expect(LPARENTHESES);
			codesave("(" + FUNC_LIST[d]);

				parameter_list();
			
			expect(RPARENTHESES);
			codesave(")");

		break;
	}
}

function parameter_list() {
	var d = lex.lookahead();

	switch(lex.pattern) {
		case 'IDENTIFIER':
		case 'REF':
			do {
				arg_type();
				lex.nextToken();
			} while(accept(COMMA));
		break;

		case 'RPARENTHESES':
		break;

		default:
			error_msg();
		break;
	}
}

function arg_type() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		case "REF":
			lex.nextToken();
			codesave(", $" + lex.lookahead());
		break;

		case "IDENTIFIER":
			codesave("," +  d);
		break;

		default:
			error_msg();
		break;
	}
}

/*	TOKENS	*/
function DEF_BLOCK() {
	var d = lex.lookahead();
	if(lex.pattern == 'DEF_BLOCK') {
		codesave('DEF_BLOCK ' + d);
		return true;
	}

	return false;
}

function IDENTIFIER() {
	var d = lex.lookahead();
	if(lex.pattern == 'IDENTIFIER') {
		return true;
	}

	return false;
}

function NUMBER() {
	var d = lex.lookahead();
	if(lex.pattern == 'NUMBER') {
		return true;
	}

	return false;
}

function LPARENTHESES() {
	var d = lex.lookahead();
	if(lex.pattern == 'LPARENTHESES') {
		return true;
	}

	return false;
}

function RPARENTHESES() {
	var d = lex.lookahead();
	if(lex.pattern == 'RPARENTHESES') {
		return true;
	}

	return false;
}

function LBRACE() {
	var d = lex.lookahead();
	if(lex.pattern == 'LBRACE') {
		return true;
	}

	return false;
}

function RBRACE() {
	var d = lex.lookahead();
	if(lex.pattern == 'RBRACE') {
		return true;
	}

	return false;
}

function COMMA() {
	var d = lex.lookahead();
	if(lex.pattern == 'COMMA') {
		return true;
	}

	return false;
}

function END_BLOCK() {
	var d = lex.lookahead();
	if(lex.pattern == 'END_BLOCK') {
		return true;
	}

	return false;
}
