#pragma once
#ifndef TRIE_H
#define TRIE_H
#include <WString.h>

template <class Type>
class Trie {
public:
    class Node {
    public:
        Node *Child = nullptr;
        Node *next = nullptr;
        Type val;
        bool isLeaf=false;
        char value = 0;
        Node(){}
        Node(char _val, bool leaf, Type _tvalue) : value(_val), isLeaf(leaf), val(_tvalue) {}
        Node(char _val, Type _tvalue): value(_val), val(_tvalue) {}
        Node* Find(char _val) {
            Node *current = this;
            while (current != nullptr) {
                if (current->value == _val) return current;
                current = current->next;
            }
            return nullptr;
        }
    };
	Node* core = nullptr;
	Trie(){}
	void Insert(const String &value, Type _val) {
		Insert(core, value, _val);
	}
	void Insert(Node* to, String value, Type _val) {
		int textSize = value.length();
		if (textSize <= 0) return;
		if (core == nullptr) {
			core = new Node(0, false, _val);
			to = core;
		}
		if (to->Child == nullptr) {
			to->Child = new Node(value[0], _val);
			if (textSize == 1) to->Child->isLeaf = true;
			else Insert(to->Child, value.substring(1, textSize),_val);
		}
		else {
			Node *prev = nullptr;
			Node *current = to->Child;
			Node *father = to;
			Node *toAdd = new Node(value[0],_val);

			while (current != nullptr) {
				if (toAdd->value < current->value) {
					if (prev == nullptr) {
						toAdd->next = father->Child;
						father->Child = toAdd;
					}
					else {
						prev->next = toAdd;
						toAdd->next = current;
					}
					if (textSize == 1) toAdd->isLeaf = true;
					else Insert(toAdd, value.substring(1, textSize),_val);
					return;
				}
				else if (toAdd->value == current->value) {
					delete toAdd;
					if (textSize == 1) current->isLeaf = true;
					else Insert(current, value.substring(1, textSize),_val);
					return;
				}
				prev = current;
				current = current->next;
			}
			if (prev != nullptr) {
				prev->next = toAdd;
				if (textSize == 1) toAdd->isLeaf = true;
				else Insert(toAdd, value.substring(1, textSize),_val);
				return;
			}
		}
	}
	Type Find(String word) {
		Node* result = nullptr;
		if (core == nullptr) return nullptr;
		Node* current = core->Child;
		for (int i = 0; i < word.length(); i++) {
			result = current->Find(word[i]);
			if (result == nullptr) return nullptr;
			current = result->Child;
		}
        if(result==nullptr) return nullptr;
		return result->val;
	}
};

#endif