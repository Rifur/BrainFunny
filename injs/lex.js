var	path = require('path'),
	util = require('util'),
	token = require('./token.js');

function error_msg() {
	console.log("Bad character");
	process.exit();
}

var text = '';

module.exports = {

	pattern : { },
	linenum : { },

	input : function (src) {
		var self = this;
		self.linenum = 1;
		self.currentTokenLength = 0;
		text = src;
	},


	lex : function () {
		var self = this;
		var d = '';
		
		self._ignore();

		if(text == '') {
			return;	// end of text
		}

		d = self.lookahead();

		if(d != '') {
			eval("token." + self.pattern + "(d)");
			self.nextToken(d);
			process.nextTick(function () { self.lex(); });

		} else {
			error_msg();
		}
	},


	nextToken : function () {
		var self = this;
		text = text.substr(self.currentTokenLength);
		self.currentTokenLength = 0;
	},


	lookahead : function () {
		var self = this;
		var d = '';

		self._ignore();

		for(self.pattern in token.tokens) {
			d = String(text.match("^" + token.tokens[self.pattern]));
			if(d != 'null') {
				self.currentTokenLength = d.length;
				return d;	// match
			}
		}

		self.pattern = '';
		return '';
	},


	_ignore : function () {
		var self = this;
		var d = '';

		for(var ig in token.ignore) {
			d = String(text.match("^" + token.ignore[ig]));
			if(d == 'null') {
				return;
			}

			self.currentTokenLength = d.length;
			if(d.match('\n')) {
				self.linenum += d.match(/\n/g).length;
			} 
			self.nextToken();
		}

		process.nextTick(function () { self._ignore(); });
	},

	_getPattern : function () {
		return self.pattern;
	}
};
