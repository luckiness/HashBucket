#include<iostream>
#include<vector>
using namespace std;
template<class K,class V>
//定义哈希桶的节点的结构体
struct HashTableNode
{
	K _key;//关键字
	V _value;//关键字对应的值域
	HashTableNode<K,V>* _next;

	HashTableNode(const K& key,const V& value):_key(key)
		                                       ,_value(value)
											   ,_next(NULL)
	{}
};

template<class K,class V>
class HashTableBucket
{
	typedef HashTableNode<K,V>  Node;
	typedef HashTableNode<K,V> Table;
private:
	vector<Node*> _tables;
	size_t _size;
public:
	HashTableBucket(size_t capacity):_size(0)
	{
	 _tables.resize(_Getnextprime(capacity));
	}                                  
	
	HashTableBucket(const Table &t):_size(0)
	{
	 _tables.resize(t._tables.size());
	 for(size_t i=0;i<t._tables.size();i++)
	 {
	  Node* cur=t._tables[i];
	  while(cur)
	  {
	   this->Insert(cur->_key,cur->_value);
	   cur=cur->_next;
	  }
	 }
	}

 Table& operator=(const Table& t)
 {
   if(this!=&t)
   {
   Table tmp(t);
   _tables.swap(tmp);
   swap(_size,tmp-ize);
   }
   return *this;
 }
bool Insert(const K& key,const V& value)
	{
		_Checkcapacity();
		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];
		while(cur)//检查链表上是否存在要插入的节点
		{
			//防冗余
			 if(cur->_key ==key)
			 {
			  return false;
			 }
			 cur=cur->_next;
		}
        //不存在则头插
		Node* tmp=new Node(key,value);
		tmp->_next=_tables[index];
		_tables[index]=tmp;
		++_size;

        return true;
	}

 bool Remove(const K& key)
 {
   size_t index=_HashFunc(key,_tables.size());
   Node* cur=_tables[index];
   if(cur==NULL)
   {
     return false;
   }
   //若删除的为头结点
	   if(cur->_key==key)
	   {
		Node* tmp=cur;
		cur=cur->_next;
		_tables[index]=cur;
		delete tmp;
		return true;
	   }
   //若为非头结点
	   Node* prev=cur;
	   cur=cur->_next; 
	   while(cur)
	   {
	    if(cur->_key==key)
		{
		 prev->_next=cur->_next;
		 delete cur;
		 cur=NULL;
		 return true;
		}
		prev=cur;
		cur=cur->_next;
	   }
	   return false;
 }

 bool Find(const K& key)
 {
  size_t index=_HashFunc(key,_tables.size());
  Node* cur=_tables[index];
  while(cur)
  {
   if(cur->_key==key)
   {
    return cur;
   }
   cur=cur->_next;
  }
  return false;
 }

  void print()
  {
	  for(size_t i=0;i<_tables.size();i++)
	  {
		 cout<<_tables[i]<<endl;
		 Node* cur=_tables[i];
		 while(cur)
		 {
         cout<<"["<<cur->_key <<" "<<cur->_value<<"]"<<"->";
		 cur=cur->_next;

		 }
		 cout<<"NULL"<<endl;
	  }
      cout<<endl;
  }
protected:
   size_t _HashFunc(const K& key,size_t capacity)
	{
	  return key%capacity;
	}
  size_t _Getnextprime(size_t size)
  {
    size_t  _PrimeList[28] =
    {
        53ul,         97ul,         193ul,       389ul,       769ul,
        1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
        49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
        1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
        50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
        1610612741ul, 3221225473ul, 4294967291ul
    };
		for(size_t i=0;i<28;i++)
		{
			if(_PrimeList[i]>size)
			{
			 return _PrimeList[i];
			}
		}	
		return _PrimeList[27];
  }
void _Checkcapacity()
	{
		if(_size==_tables.size())
		{   //扩容
			size_t nextprime=_Getnextprime(_size);
			vector<Node*> newtables;
			newtables.resize(nextprime);
			 for(size_t i=0;i<_tables.size();i++)
			 {
				  Node* cur=_tables[i];
				  while(cur)
				  {
					 //摘节点
					  Node* tmp=cur;
					  cur=cur->_next ;
					//头插
					 size_t index=_HashFunc(tmp->_key,newtables.size());
					 tmp->_next=newtables[index];
					 newtables[index]=tmp;
				  }
				  _tables[i]=NULL;
			 }	
			  _tables.swap(newtables);
		}
		
	}
	
};