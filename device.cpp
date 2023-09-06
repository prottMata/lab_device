#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
int streamcounter;

class Stream
{
    private:
      double mass_flow;
      string name;
    public:
      Stream(int s){setName("s"+std::to_string(s));}
      void setName(string s){name=s;}
      string getName(){return name;}
      void setMassFlow(double m){mass_flow=m;}
      double getMassFlow(){return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" flow = "<<getMassFlow()<<endl;}
};

class Device
{
    protected:
      vector<shared_ptr<Stream>> inputs;
      vector<shared_ptr<Stream>> outputs;
    public:
      void addInput(shared_ptr<Stream> s){inputs.push_back(s);}
      void addOutput(shared_ptr<Stream> s){outputs.push_back(s);}
      virtual void updateOutputs() = 0;
};

class Absorber: public Device
{
    public:
      void updateOutputs() override
      {
        double sum = 0;
        for (const auto& in_str : inputs)
        {
          sum += in_str ->getMassFlow();
          in_str -> print();
        }
        sum/=2;
        for (const auto& out_str : outputs)
        {
          out_str ->setMassFlow(sum);
          out_str ->print();
        }
    };
};

int main()
{
    streamcounter=0;
    Absorber d1;
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    
    d1.addInput(s1);
    d1.addInput(s2);
    d1.addOutput(s1);
    d1.addOutput(s2);
    d1.updateOutputs();
    
    return 0;
}
