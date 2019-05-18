//definition
class DisjointSet
{
	public:
		DisjointSet(unsigned size);
		unsigned find(unsigned x);
		void Union(unsigned i,unsigned j);
		~DisjointSet();
	private:
		unsigned *tree,*rank,size;
};
inline void swap(unsigned x,unsigned y)
{
    unsigned t=x;x=y;y=t;
}




//implementation
DisjointSet::DisjointSet(unsigned size) : tree(new unsigned[size]) , rank(new unsigned[size]) , size(size)
{
    for(unsigned i=0;i!=size;++i)
    {
        tree[i]=i;
        rank[i]=0;
    }
}

unsigned DisjointSet::find(unsigned x)
{
    if(tree[x]!=x)
        tree[x]=find(tree[x]);
    return tree[x];
}

void DisjointSet::Union(unsigned i,unsigned j)
{
    i=find(i);j=find(j);
    if(i!=j)
    {
        if(rank[i]<rank[j])
            swap(i,j);
        tree[j]=i;
        if(rank[i]==rank[j])
            ++rank[i];
    }
}

DisjointSet::~DisjointSet()
{
    delete[] tree;
    delete[] rank;
}

