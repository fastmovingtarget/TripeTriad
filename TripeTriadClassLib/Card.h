#pragma once
#include <stdlib.h>

using namespace System;

public ref class Card
{
	private:
		String^ top;
		String^ left;
		String^ right;
		String^ bottom;

	public:
		Card(String^ t, String^ l, String^ r, String^ b) : top(t), left(l), right(r), bottom(b) {}
		Card(String^ value) : top(value), left(value), right(value), bottom(value) {}

		String^ getTop() { return top; }
		String^ getLeft() { return left; }
		String^ getRight() { return right; }
		String^ getBottom() { return bottom; }
		int getTopInt() { return Int32::Parse(top); }
		int getLeftInt() { return Int32::Parse(left); }
		int getRightInt() { return Int32::Parse(right); }
		int getBottomInt() { return Int32::Parse(bottom); }
};