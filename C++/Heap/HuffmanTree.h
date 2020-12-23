#pragma once

class HuffmanNode {
public:
	int Weight;
	HuffmanNode *Left, *Right;
	HuffmanNode(int);
	bool operator<(HuffmanNode &cH);
	bool operator>(HuffmanNode &cH) {
		return cH < *this;
	}
	bool operator<=(HuffmanNode &cH) {
		return !(*this > cH);
	}
	HuffmanNode(int, HuffmanNode*, HuffmanNode*);
};

using HuffmanTree = HuffmanNode*;

inline HuffmanNode::HuffmanNode(int weight, HuffmanNode* left, HuffmanNode* right) {
	Weight = weight;
	Left = left;
	Right = right;
}

inline HuffmanNode::HuffmanNode(int weight)
{
	Weight = weight;
	Left = nullptr;
	Right = nullptr;
}



inline bool HuffmanNode::operator<(HuffmanNode& cH)
{
	return this->Weight < cH.Weight;
}
