#pragma once

/*

#include <memory>

///////////////////////////
/////DEPRECATED!!/////////
//////////////////////////


class Shape;
class Material;

class Thing {
public:
	Shape* shape;
	Material* material;

	~Thing() {
		delete shape;
		delete material;
	}

	Thing(const Thing& o) = delete;
	Thing(const Thing* o) = delete;
	
	Thing(Thing* o)
		: Thing(*o)
	{}

	Thing(Thing& o) {
		shape = o.shape;
		material = o.material;

		o.shape = NULL;
		o.material = NULL;
	}
};

*/