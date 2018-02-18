#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <boost/lambda/lambda.hpp>

using namespace std;

class PBRegException : public exception {
private:
  string msg;
public:
  PBRegException(const string s) : msg(s){}
  virtual ~PBRegException() throw(){};
  const char* what(){ return msg.c_str(); }
};


vector< vector<float> > ReadPoints(string filename){
  ifstream afile;
  vector< vector<float> > result;
  vector<float> x_vec;
  vector<float> y_vec;
  vector<float> z_vec;
  float x;
  afile.open(filename.c_str());
  int r = 0;
  while(afile >> x){
    if(r == 0){
      x_vec.push_back(x);
    } else if(r == 1){
      y_vec.push_back(x);
    } else {
      z_vec.push_back(x);
      r = -1;
    }
    r++;
  }
  result.push_back(x_vec);
  result.push_back(y_vec);
  result.push_back(z_vec);
  return result;
}

int main(){
  vector< vector<float> > a;
  a = ReadPoints("fixed.txt");
  for(int idx=0; idx<3; ++idx){
    for(int jdx=0; jdx<a[idx].size(); ++jdx){
      cout << a[idx][jdx] << endl;
    }
  }
  try {
    throw PBRegException("Bastard!");
  } catch (PBRegException &ex){
    cout << ex.what() << endl;
  }
  using namespace boost::lambda;
  typedef std::istream_iterator<int> in;

  std::for_each(
      in(std::cin), in(), std::cout << (_1 * 3) << " " );

  return 0;
}
