#include"BUCKET.h"
void TestInseret()
{
  HashTableBucket<int,int>ht(10);
  HashTableBucket<int,int>ht1(10);
  ht.Insert(1,1);
  ht.Insert(2,2);
  ht.Insert(21,2);
  ht.Insert(32,3);
  ht.Insert(31,3);
  ht.Insert(54,2);
  ht.Insert(107,3);
  ht.Remove(1);
  ht.Find(107);
  ht1=ht;
  ht1.print();

}
int main()
{
	TestInseret();
    getchar();
	return 0;
}