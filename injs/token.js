var show = function (x) { console.log(x + " Here!"); };

module.exports = {
	tokens : {

		'DEF_BLOCK' : "DEF",
		'DEF_FUNC' : "def",
		'END_BLOCK' : "END",

		'MAIN_BLOCK' : "MAIN",

		'LBRACE' : "\\{",
		'RBRACE' : "\\}",

		'LPARENTHESES' : "\\(", 
		'RPARENTHESES' : "\\)", 
		'HALT'	:	"!",

		'COMMA' : ',',

		'REF' : '\\$',
		'INC' : '\\+',
		'DEC' : '-',
		'PRINT' : '\\.',
		'READ' : ',',
		'BEGIN_LOOP' : '\\[',
		'END_LOOP' : '\\]',
		'FORWARD' : '>',
		'BACKWARD' : '<',

		'ASSIGN' : "=",

		'NUMBER' : '\\d+',
		'IDENTIFIER' : "\\w+",

		'EPSILON' : 'ε'

	},

	ignore : {
		'IGNORE' : '\\s+'
	},
};
