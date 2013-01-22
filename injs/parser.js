var	fs = require("fs"),
	path = require('path'),
	util = require('util'),
	lex = require('./lex.js'),
	CODE = "",
	FUNC_LIST = new Array();
	;


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
		codesave("line " + lex.linenum + " : syntax error");
	} else {
		codesave("line " + lex.linenum + " : " + msg);
	}
	process.exit();
}

function expect(symbol) {
	if(symbol()) {
		lex.nextToken();
		return true;
	} else {
		error_msg("Unrecongnized token");
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
	codesave("#include <stdio.h>\n#include <stdlib.h>\n#include <locale.h>\n");
	codesave("#define __def void\n");
	codesave("wchar_t *code, *p;\n");

	def_region();
	codegen();


	codesave("int main(void) { code = (wchar_t *)calloc(10000, sizeof(wchar_t)); p = &code[0];");
	codesave('setlocale(LC_CTYPE, "");');
	main_region();
	codesave("return 0; }");
	codegen();
}

function def_region() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		default:
			lex.nextToken();
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
	var funcName = "";
	var arg = new Array();
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

			//console.log("funcName: " + funcName);

			expect(LPARENTHESES);
			codesave("(");

			do {
				arg.push(lex.lookahead());
				expect(IDENTIFIER);
			} while(accept(COMMA))

			var arglist = "argc";
			for(var i=0; i<arg.length; ++i) {
				arglist = arglist + ", " + arg[i];
			}
			codesave(arglist);

			FUNC_LIST[funcName] = arg.length;

			expect(RPARENTHESES);
			codesave(") \\\n");

			expect(LBRACE);

			expression();

			expect(RBRACE);
			codesave("\n");
			

		break;
	}
}

function main_region() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		default:
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
			codesave("++*p;");
		break;

		case "DEC":
			codesave("--*p;");
		break;

		case "READ":
		case "COMMA":
			codesave("*p=getchar();");
		break;

		case "PRINT":
			//codesave("putchar(*p);");
			//codesave('printf("%d\\n",*p);');
			codesave('printf("%lc",*p);');
		break;

		case "FORWARD":
			codesave("++p;");
		break;

		case "BACKWARD":
			codesave("--p;");
		break;

		case "BEGIN_LOOP":
			codesave("while(*p){");
		break;

		case "END_LOOP":
			codesave("}");
		break;

		case "REF":
			ref_expression();
		break;

		case "ASSIGN":
			assign_expression();
		break;

		case "IDENTIFIER":
			// TODO: implementation of syntax has something wrong, needs to fix.
			//			should know what is variable and what is macro
			if(FUNC_LIST[d] == null) { // not a function
				if(accept(NUMBER)) {
					codesave("p=&code[" + d + "];");
				}
				else {
					//console.log(d + " at line " + lex.linenum);
					codesave("p=" + d + ";");
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

	//process.nextTick( expression );
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
			codesave("p=&code[" + addr + "];");
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
			codesave("*p=" + value + ";");
		break;
	}
}


function invoke_expression() {
	var d = lex.lookahead();
	var arg = 0;
	switch(lex.pattern) {
		case "IDENTIFIER":
			codesave(d);
			lex.nextToken();

			expect(LPARENTHESES);
			codesave("(" + FUNC_LIST[d]);

			do {
				arg = lex.lookahead();
				arg_type();

				lex.nextToken();
			} while(accept(COMMA));

			expect(RPARENTHESES);
			codesave(");");

		break;
	}
}

function arg_type() {
	var d = lex.lookahead();
	switch(lex.pattern) {
		case "NUMBER":
			codesave(", &code[" + d + "]");//codesave(", " + d + "");
		break;

		case "IDENTIFIER":
			codesave("," +  d);
		break;
	}
}

/*	TOKENS	*/
function DEF_BLOCK() {
	var d = lex.lookahead();
	if(lex.pattern == 'DEF_BLOCK') {
		codesave('DEF_BLOCK ' + d);
		//lex.nextToken();
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
