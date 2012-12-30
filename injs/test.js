%token 
{
	IDENTIFIER : /\w+/	,
	TOKEN_REGULAR : //.*//	,
	TERMINAL : /"\S+"/	,
	NONTERMINAL : /<\w+>/	,
	ALTER : /\|/		,
	EPSILON : /ε/
}	

%grammar
{

<start> : <token_region> <bnf_region> ;
<token_region> : "%token" "{" [<token_expression>] "}" | ε ;
<token_expression> :  <token_name> ":" <token_regular> ["," <token_expression>];
<token_name> : IDENTIFIER ;
<token_regular> : TOKEN_REGULAR ;

<bnf_region> : "%grammar" "{" [<bnf_expression>] "}" | ε ;
<bnf_expression> : <nonterminal> ":" <bnf_rule> ;
<bnf_rule> : <bnf_element> <bnf_zeroOrMore> [<bnf_rule>] ";" ;
<bnf_element> : <nonterminal> | IDENTIFIER | <terminal> | ALTER | EPSILON ;
<bnf_zeroOrMore> : "\[" <bnf_element> "\]" | ε ;

<terminal> : TERMINAL ;
<nonterminal> : NONTERMINAL ;

}
