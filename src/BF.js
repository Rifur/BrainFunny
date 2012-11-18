var fs = require("fs"),
	path = require('path'),

	print = console.log,
	srcCode = null;


function readSourceCode(filename) {
	return fs.readFileSync(filename, "utf8");
}

process.argv.forEach(function (val, index, array) {	
	var filename = array[2];
	srcCode = readSourceCode(filename);
});


