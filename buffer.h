// Wait All F*cking Input
// Copyright (C) 2022  Yury Moskov
//
// Licensed under GPL 3.0
// See LICENSE or https://www.gnu.org/licenses/gpl-3.0.txt
//

#include <string>
#include <list>

class EditableBuffer {
public:
	EditableBuffer();
	void put(char ch);
	void pop();

	int getIndex();
	int length();
	void next();
	void prev();

	std::string str();
private:
	std::list<char> data; // erase with iterator: O(1)
			      // access with iterator: O(1)
			      // insertion with iterator: O(1)
			      // Probably what we want
	std::list<char>::iterator current;
	int index;
};

