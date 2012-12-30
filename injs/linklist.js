const ATOM_TYPE = 1;
const LIST_TYPE = 2;

llNode = function(whatType, value) {
	return {
		type: whatType,
		key: value,
		forward : null,
		next : null,
		id : -1
	};
};

linklist = function() {}
linklist.prototype = {
	head: null,
	tail: null,
	length: 0
};

linklist.prototype.append = function(node) {
	if(this.head == null) {
		this.head = new llNode(LIST_TYPE, null);
		this.head.id = 0;
		this.tail = this.head;
	}

	this.tail.next = node;
	node.forward = this.tail;
	this.tail = node;

	if(node.type == LIST_TYPE) {
		if(node.key == this) {
			node.id = this.head.id;
		} else {
			node.id = this.length;
		}
	}

	this.length++; 
};

linklist.prototype.travel = function() {
	
	var ary = this.toArray();
	while(ary.length > 0) {
		console.log(ary.shift().key);
	}
	console.log("Length: " + this.length);
};

linklist.prototype.search = function(value) {
	var ary = this.toArray();
	value = value.toString();

	while(ary.length > 0) {
		t = ary.shift().key.toString();

		if(t == value) {
			return true;
		}
	}

	return false;
};

linklist.prototype.toArray = function(current) {
	var ary = new Array();
	var list = new Array();
	var tmp = new Array();
	var hasViewd = false;

	if(this.length == 0)
		return ary;

	if(current == null) {
		list.push(this.head);
		current = this.head.next;
	}

	while(current) {
		if(current == null) {
			current = tmp.pop();
			continue;
		}

		if(current.type == LIST_TYPE) {
			hasViewd = false;
			for(var i in list) {
				if(list[i].id == current.id) {
					hasViewd = true;
					break;
				}
			}

			if(hasViewd == true) {
				current = current.next;
				continue;
			} else {
				list.push(current);
				tmp.push(current.next);
				current = current.key.head.next;
			}
		}

		ary.push(current);
		current = current.next;
		
	}

	delete list;
	delete tmp;

	return ary;

};


linklist.prototype.linklistTest = function() {
	var L1 = new linklist();
	var L2 = new linklist();
	var L3 = new linklist();
	var L4 = new linklist();

	L1.append(new llNode(ATOM_TYPE, 0));
	L1.append(new llNode(ATOM_TYPE, 1));

	L2.append(new llNode(ATOM_TYPE, 2));
	L2.append(new llNode(ATOM_TYPE, 3));

	L2.append(new llNode(LIST_TYPE, L1));
	L2.append(new llNode(LIST_TYPE, L2));


	L3.append(new llNode(ATOM_TYPE, 4));
	L3.append(new llNode(ATOM_TYPE, 5));

	L2.travel();
	L3.travel();
	L4.travel();

	delete L1;
	delete L2;
	delete L3;
	delete L4;
};