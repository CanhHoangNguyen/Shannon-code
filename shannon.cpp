#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

// Shannon Variable
vector <double> Probability;
vector <double> Probability_i;
vector <double> Length;
int COUNT = 0;
bool FileChecker = false;

// Take the Probability
void get_input() {
  ifstream myfile ("example.txt");

  if (myfile.is_open())
  {
    double current_number = 0;
    while (myfile >> current_number){
        Probability.push_back(current_number);
        COUNT ++;
    }
    FileChecker = true;
    myfile.close();
  }
  else
    {
      cout << "Unable to open file";
      FileChecker = false;
    }
}

// check the Probability equal to 1
bool test_input() {
  double sum;
  for (int i=0; i < COUNT; i++)
    sum += Probability[i];
  return pow(10,-8)> abs(1-sum) && abs(1-sum)< pow(10,-7);
}

// Decreasing Sort
void soft() {
      for(int i = 0; i < COUNT - 1 ; i++){
          for(int j = i + 1; j < COUNT ; j++){
              if(Probability[j] > Probability[i]){
                  double middle = Probability[i];
                  Probability[i] = Probability[j];
                  Probability[j] = middle;
              }
          }
      }
}


// Calculate the Value of Pi
void caculate_P_i() {
  Probability_i.push_back(0);
  for(int i = 0; i < COUNT; i++)
    Probability_i.push_back(Probability[i]+Probability_i[i]);
}


// Calculate the code's length
void length_code() {
  for(int i=0; i < COUNT; i++) {
    double mock = log2(1/Probability[i]);
    if (mock > int(mock)) Length.push_back( int(log2(1/Probability[i])) + 1);
    else Length.push_back(int( log2(1/Probability[i])) );
  }
}


// Convert decimal to binary
void decToBinary(double mock, int length)
{
    int binaryNum[17];
    int count = 0;
    if (mock == 0)
      for (int i=0; i<length ; i++) cout <<'0';
    else {
      int n =  int(mock * pow(2,16));
      while (n > 0) {
          binaryNum[count] = n % 2;
          n /= 2;
          count++;
      }
      if (count < 16) {
        int clone = count;
        for (int j=0; j < 16-clone; j++)
          binaryNum[++count -1] = 0;
      }
      for (int j = count-1 ; j >=count-length; j--)
        cout << binaryNum[j];
    }
}


//Convert P(i) to Shanon code
void Converter() {
  cout << setw(10) << "Px" << setw(10) <<"Pi" << setw(25) << "Độ dài từ mã" << setw(13) << "Từ Mã" <<endl;
  for (int i = 0; i < COUNT; i++) {
    cout << setw(10) << Probability[i] << setw(10) << Probability_i[i] << setw(10) <<Length[i] << setw(15);
    decToBinary(Probability_i[i],Length[i]);
    cout <<endl;
  }
}

void caculate_kt(){
  double L=0;
  double H = 0;
  double a = COUNT;
  for (int i=0; i<COUNT;i++){
    L += Length[i] * Probability[i];
    H += Probability[i] *log2(1/Probability[i]);
  }
  cout <<endl<<" Kt ="<< H/L<<endl;
  double max = 1/a;
  double Hmax = 0;
  for (int j = 0; j < COUNT; j++) {
    Hmax +=max*log2(1/max);
  }
  cout <<endl<<" Kn ="<<Hmax;
}

int main () {
  get_input();
  if (FileChecker == true) {
    if (test_input() == true) {
      soft();
      caculate_P_i();
      length_code();
      Converter();
      caculate_kt();
    }
    else cout << endl << "Please enter the correct probability";
  }
  return 0;
}