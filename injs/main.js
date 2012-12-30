var fs = require("fs"),
	lex = require('./lex.js'),
	parser = require('./parser.js'),
	path = require('path'),

	print = console.log,

	srcCodeNum = -2,
	srcCode = new Array();


function readSourceCode(filename) {
	return fs.readFileSync(filename, "utf8");
}

process.argv.forEach(function (val, index, array) {
	// ignore nodejs and main.js, so srcCodeNum starts from -2
	if(srcCodeNum >= 0) {
		var filename = val;
		srcCode[srcCodeNum] = readSourceCode(filename);
	}

	srcCodeNum += 1;
});

if(srcCodeNum == 0) {
	print("Usage: nodejs main.js <src1 src2...>");
	process.exit();
}


var str = srcCode[0];
lex.input(str);
parser.parse(str);