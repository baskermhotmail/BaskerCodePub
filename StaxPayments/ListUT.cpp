#include "List.h"
#include <string>
using namespace std;
// Defining test verification methods

template <typename T> bool verifyCount(const List<T>& list , unsigned count )
{

  bool result =(list.size() == count);
  cout << "Expected count " << count << endl;
  if(result) { cout << "Count TEST PASS " << endl;}
  else  { cout << "Count TEST FAIL " << list.size()<< endl;}
  return result;
}

template <typename T> bool verifyValue(const T& t , const T& expected )
{
  bool result =(t == expected);
  cout << "Expected value " << expected << endl;
  if(result) { cout << " Value TEST PASS " << endl;}
  else  { cout << " Value TEST FAIL " <<t << endl;}
  return result;
}
bool TestString()
{
  List<string> strList;
  cout << "Adding Months of the year" <<endl;
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
  cout << "Removed Jun and Jul" << endl;
  strList.print();
  // Jun and Jul gone
  cout << "Removed Jan" << endl;
  strList.remove_all("Jan");
  strList.print();
  // Jan Jun and Jul gone
  cout << "Removed Dec" << endl;
  strList.remove("Dec");
  strList.print();
  // Jan Jun Jul and Dec gone    
  bool verifiedCount1 = verifyCount(strList,8);
  cout << "Checking first value " << endl;
  bool verifyValue1 = verifyValue(strList.front(),string("Feb"));
  cout << "Checking last value " << endl;
  bool verifyValue2 = verifyValue(strList.back(),string("Nov"));
  cout << "Clearing list " << endl;
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
  cout << "Initial List " << endl; 
  uList.print();
  cout << "Removed 1 element value 10 " << endl;
  uList.remove(10);
  uList.print();
 
  bool verifiedCount1 = verifyCount(uList,19);
  bool verifyValue1 = verifyValue(uList.front(),1U);
  bool verifyValue2 = verifyValue(uList.back(),1U);
  cout << "Removed 1 element value 7 " << endl;
  uList.remove(7);
  
  uList.print();
  bool verifiedCount2 = verifyCount(uList,18);
  cout << "Removed first element " << endl;
  uList.pop_front();
  uList.print();
  bool verifyValue3 = verifyValue(uList.front(),2U);
  bool verifyValue4 = verifyValue(uList.back(),1U);
  cout << " Removed all 4 and 5 " << endl;
  uList.remove_all(4);
  uList.remove_all(5);
  cout << "Removed last element" << endl;
  uList.pop_back();
  uList.print();
  bool verifiedCount3 = verifyCount(uList,12);
  uList.remove(1);
  cout << "Remove 1 if it exists " <<endl;
  bool verifiedCount4 = verifyCount(uList,12);
  uList.print();
  cout << "Clearing the list " << endl;
  uList.clear();
  uList.print();
  bool verifyEmpty = uList.empty();
  if(verifyEmpty) cout << "Emptiness PASS" << endl;
  else
    cout << "Emptiness FAIL" << endl;
  cout << "Adding value 100" << endl;
  uList.push_front(100);
  uList.print();
  bool verifyValue5 = verifyValue(uList.front(),100U);
  bool verifyValue6 = verifyValue(uList.back(),100U);
  return (verifiedCount1 &&
	  verifiedCount2 &&
	  verifiedCount3 &&
	  verifiedCount4 &&
	  verifyValue1 &&
	  verifyValue2 &&
	  verifyValue3 &&
	  verifyValue4 &&
	  verifyValue5 &&
	  verifyValue6 &&
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
  
