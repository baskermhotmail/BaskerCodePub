#include "List.h"
#include <string>
using namespace std;
// Defining test verification methods

template <typename T> bool verifyCount(const List<T>& list , unsigned count )
{

  bool result =(list.size() == count);
  if(result) { cout << " Count TEST PASS " << endl;}
  else  { cout << " COUNT TEST FAIL " << list.size()<< endl;}
  return result;
}

template <typename T> bool verifyValue(const T& t , const T& expected )
{
  bool result =(t == expected);
  if(result) { cout << " Value TEST PASS " << endl;}
  else  { cout << " Value TEST FAIL " << endl;}
  return result;
}
bool TestString()
{
  List<string> strList;
  strList.push_back("Jan");
  strList.push_back("Feb");
  strList.push_back("Mar");
  strList.push_back("Apr");

  strList.push_back("May");
  strList.push_back("Jun");
  strList.push_back("Jul");
  strList.push_back("Aug");

  strList.push_back("Sep");
  strList.push_back("Oct");
  strList.push_back("Nov");
  strList.push_back("Dec");
  strList.print();
  // Should show Jan to Dec
  strList.remove("Jun");
  strList.remove("Jul");  
  strList.print();
  // Jun and Jul gone
  strList.remove_all("Jan");
  strList.print();
  // Jan Jun and Jul gone  
  strList.remove("Dec");
  strList.print();
  // Jan Jun Jul and Dec gone    
  bool verifiedCount1 = verifyCount(strList,8);
  bool verifyValue1 = verifyValue(strList.front(),string("Feb"));
  bool verifyValue2 = verifyValue(strList.back(),string("Nov"));
  strList.clear();
  strList.print();
  bool verifyCount2 = verifyCount(strList,0);
  bool verifyEmpty = strList.empty();
  if(verifyEmpty) cout << "Emptiness PASS" << endl;
  else
    cout << "Emptiness FAIL" << endl;
  return verifiedCount1 && verifyValue1 && verifyValue2&&verifyCount2 && verifyEmpty;  
}

bool TestUnsigned()
{
  List<unsigned> uList;
  for (unsigned i = 1; i<=10; i++) {
    uList.push_back(i);
  }
  for (unsigned i = 10; i>=1; i--) {
    uList.push_back(i);
  }
  uList.print();
  uList.remove(10);
  bool verifiedCount1 = verifyCount(uList,19);
  bool verifyValue1 = verifyValue(uList.front(),1U);
  bool verifyValue2 = verifyValue(uList.back(),1U);
  uList.print();
  uList.remove(7);
  bool verifiedCount2 = verifyCount(uList,18);
  uList.pop_front();
  bool verifyValue3 = verifyValue(uList.front(),2U);
  bool verifyValue4 = verifyValue(uList.back(),1U);
  uList.remove_all(4);
  uList.remove_all(5);
  uList.pop_back();
  bool verifiedCount3 = verifyCount(uList,12);
  uList.remove(1);
  bool verifiedCount4 = verifyCount(uList,12);
  uList.print();
  uList.clear();
  bool verifyEmpty = uList.empty();
  if(verifyEmpty) cout << "Emptiness PASS" << endl;
  else
    cout << "Emptiness FAIL" << endl;
  return (verifiedCount1 &&
	  verifiedCount2 &&
	  verifiedCount3 &&
	  verifiedCount4 &&
	  verifyValue1 &&
	  verifyValue2 &&
	  verifyValue3 &&
	  verifyValue4 &&
	  verifyEmpty); 
}

int main()
{
  bool testUnsigned = TestUnsigned();
  bool testString = TestString();
  cout << "Unsigned Test " << (testUnsigned?"PASS":"FAIL") << endl;
  cout << "String Test   " << (testString?"PASS":"FAIL") << endl;
  return 0;
}
  
