#pragma once

#include "includes.h"

class DSU
{
	vector <int> parent;

public:

	DSU(int sz);

	int getParent(int p);
	void merge(int u, int v);
};