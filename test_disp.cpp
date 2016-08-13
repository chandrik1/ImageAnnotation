#include "src2/categorizer.h"
#include<stdio.h>
int main(int argc,char* argv[]) {
// Number of clusters for building BOW vocabulary from SURF features
int clusters = 100;
try{
string read=string(argv[1]);
Mat input=imread(read);
categorizer c(clusters,0);
c.read_vocab();
//cout<<c.categorize(input);
string category=c.categorize(input);
//cout<<category<<endl;
    //stringstream ss; // Insert the string into a stream
    vector<string> tokens,preds; // Create vector to hold our words
ifstream infile;
infile.open("prediction_values.txt");
for (string line; getline(infile, line);) {
String sl="";
    //cout << line << endl;
int i,k=0,found=0; 
for(i=0;i<line.length();i++)
{
//cout<<line.length()<<endl;
if (line[i]!=' ')
sl=sl+line[i];
else
{
//cout<<sl<<endl;
if(k==0 && sl==category)
       {
	found=1;
	}
if(k==1 && found==1)
	tokens.push_back(sl);
if(k==2 && found==1)
       {
	k=0;
	preds.push_back(sl);
	found=0;
	}
sl="";
k++;
}
}
}
string pred_value;
infile.close();
vector<string> copy(preds);
sort(copy.begin(),copy.end());
ifstream myfile;
myfile.open ("prediction.txt");
getline(myfile,pred_value);
myfile.close();
int pos=0;
double min=999,val=0.0;
for(int i=0;i<copy.size();i++)
{
  val=abs(atof(copy[i].c_str())-atof(pred_value.c_str()));
  if(val<=min)
     {
	min=val;
  	pos = i;
       }  
}
string top3[3];
if(pos==0)
{
top3[0]=copy[pos];
top3[1]=copy[pos+1];
top3[2]=copy[pos+2];
}
else if(pos==copy.size()-1)
{
top3[0]=copy[pos];
top3[1]=copy[pos-1];
top3[2]=copy[pos-2];
}
else
{
min = abs(atof(copy[pos-1].c_str())-atof(pred_value.c_str()));
val = abs(atof(copy[pos+1].c_str())-atof(pred_value.c_str()));
top3[0]=copy[pos];
if(min<val)
{
top3[1]=copy[pos-1];
top3[2]=copy[pos+1];
}
else
{
top3[1]=copy[pos+1];
top3[2]=copy[pos-1];
}
}

string top3_images[3]="";
for(int i=0;i<preds.size();i++)
{
  if(top3[0]==preds[i])
	top3_images[0]=tokens[i];
  if(top3[1]==preds[i])
	top3_images[1]=tokens[i];
  if(top3[2]==preds[i])
	top3_images[2]=tokens[i];
}
string img_name[]={"Match 1","Match 2","Match 3"};
for(int i=0;i<3;i++){
	//cout<<top3_images[i]<<endl;
	Mat img=imread(top3_images[i]);
	imshow(img_name[i],img);
 }
waitKey(0);
}
catch(std::runtime_error& b)
{
cout<<"error- Runtime Error";
exit(0);
}
catch(cv::Exception& a)
{
cout<<"error- openCV Exception";
exit(0);
}
return 0;
}
