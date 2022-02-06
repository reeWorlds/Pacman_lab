#include "DSU.h"

DSU::DSU(int sz)
{
	parent.resize(sz);

	for (int i = 0; i < parent.size(); i++)
	{
		parent[i] = i;
	}
}

int DSU::getParent(int p)
{
	if (parent[p] == p)
	{
		return p;
	}

	return parent[p] = getParent(parent[p]);
}

void DSU::merge(int u, int v)
{
	u = getParent(u);
	v = getParent(v);

	if (u != v)
	{
		parent[v] = u;
	}
}