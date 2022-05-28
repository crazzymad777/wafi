// Wait All F*cking Input
// Copyright (C) 2022  Yury Moskov
//
// Licensed under GPL 3.0
// See LICENSE or https://www.gnu.org/licenses/gpl-3.0.txt
//

#include "buffer.h"

EditableBuffer::EditableBuffer() {
	current = data.end();
	index = 0;
}

void EditableBuffer::put(char ch) {
	if (current != data.end()) {
		current++;
	}

	data.insert(current, ch);
	index++;
}

void EditableBuffer::pop() {
	if (current != data.begin()) {
		current--;
		current = data.erase(current);
		index--;
	}
}

std::string EditableBuffer::str() {
	return std::string(data.begin(), data.end());
}

int EditableBuffer::getIndex() {
	return index;
}

void EditableBuffer::next() {
	if (current != data.end()) {
		current++;
		index++;
	}
}

void EditableBuffer::prev() {
	if (current != data.begin()) {
		current--;
		index--;
	}
}

int EditableBuffer::length() {
	return data.size();
}


