#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/ml/ml.hpp>
#include <boost/filesystem.hpp>
#include <string.h>
#include "Config.h"
#include<iostream>
#include <fstream> 
using namespace cv;
using namespace std;
using namespace boost::filesystem3;

#ifndef CATEGORIZER_H
#define CATEGORIZER_H
 
class categorizer {
private:
map<string, Mat> templates, positive_data, negative_data;
multimap<string, Mat> train_set; 
map<string, CvSVM> svms;
vector<string> category_names,images;
int categories;
int clusters;
Mat vocab;
int no_train;
Ptr<FeatureDetector> featureDetector;
Ptr<DescriptorExtractor> descriptorExtractor;
Ptr<BOWKMeansTrainer> bowtrainer;
Ptr<BOWImgDescriptorExtractor> bowDescriptorExtractor;
Ptr<DescriptorMatcher> descriptorMatcher;

void make_train_set(int);
void make_pos_neg();
string remove_extension(string);

public:categorizer(int,int); 
void build_vocab();//for multimap
void train_classifiers();
string categorize(Mat);
void read_vocab();//reads svms also
double categorize_train(Mat,string);
};
 
void categorizer::read_vocab()
{
int i;
string str2="my_svm";
FileStorage f1("./data/vocab.xml", FileStorage::READ);
f1["vocabulary"] >> vocab;
f1.release();
for(i=0;i<category_names.size();i++)
{
string name=string("./data/")+category_names[i]+string("SVM.xml");
svms[category_names[i]].load(name.c_str());
}
}

string categorizer::remove_extension(string full) {
int last_idx = full.find_last_of(".");
string name = full.substr(0, last_idx);
return name;
}
 
categorizer::categorizer(int _clusters,int k) { 
clusters = _clusters;
featureDetector = (new SurfFeatureDetector());
descriptorExtractor = (new SurfDescriptorExtractor());
bowtrainer = (new BOWKMeansTrainer(clusters));
descriptorMatcher = (new FlannBasedMatcher());
bowDescriptorExtractor = (new BOWImgDescriptorExtractor(descriptorExtractor,descriptorMatcher));
for(directory_iterator i("./data/templates/"), end_iter; i != end_iter; i++) {
string filename = string("./data/templates/") + i->path().filename().string();
string category = remove_extension(i->path().filename().string());
Mat im = imread(filename);
//cvtColor(im, templ_im, CV_BGR2GRAY);
templates[category] = im;
}
make_train_set(k);
}
 
void categorizer::make_train_set(int k) {
string category;
for(recursive_directory_iterator i("./data/train_images/"), end_iter; i != end_iter; i++) {
if(i.level() == 0) {
category = (i -> path()).filename().string();
category_names.push_back(category);
}
else {
if(k==0)
continue;
string filename = string("./data/train_images/") + category + string("/") +(i -> path()).filename().string();
images.push_back(filename);
pair<string, Mat> p(category, imread(filename, CV_LOAD_IMAGE_GRAYSCALE));
train_set.insert(p);
}
}
categories = category_names.size();
}
 
void categorizer::make_pos_neg() {
no_train=0;
for(multimap<string, Mat>::iterator i = train_set.begin(); i != train_set.end(); i++) {
string category = (*i).first;
Mat im = (*i).second, feat;
if(category==category_names[0])
	no_train++; 
vector<KeyPoint> kp;
featureDetector -> detect(im, kp);
bowDescriptorExtractor -> compute(im, kp, feat);
 
Mat pos, neg;
for(int cat_index = 0; cat_index < categories; cat_index++) {
string check_category = category_names[cat_index];
if(check_category.compare(category) == 0)
{
positive_data[check_category].push_back(feat);
//images.push_back(check_category);
}
else
negative_data[check_category].push_back(feat);
}
}
}

void categorizer::build_vocab() { 
Mat vocab_descriptors;
for(map<string, Mat>::iterator i = templates.begin(); i != templates.end(); i++) {
vector<KeyPoint> kp; Mat templ = (*i).second, desc;
featureDetector -> detect(templ, kp);
descriptorExtractor -> compute(templ, kp, desc);
vocab_descriptors.push_back(desc);
}
 
bowtrainer -> add(vocab_descriptors);
vocab = bowtrainer->cluster();
 
FileStorage fs("./data/vocab.xml", FileStorage::WRITE);
fs << "vocabulary" << vocab;
fs.release();
 
}
 
void categorizer::train_classifiers() {
bowDescriptorExtractor -> setVocabulary(vocab);
make_pos_neg();
 for(int i = 0; i < categories; i++) {
string category = category_names[i];
 
Mat train_data = positive_data[category], train_labels = Mat::ones(train_data.rows, 1, CV_32S);
train_data.push_back(negative_data[category]);
Mat m = Mat::zeros(negative_data[category].rows, 1, CV_32S);
train_labels.push_back(m);
 
svms[category].train(train_data, train_labels);
 
string svm_filename =string("./data/")+category + string("SVM.xml");
svms[category].save(svm_filename.c_str());
}

int listing=0;
//sort(category_names.begin(),category_names.end());
//sort(images.begin(),images.end());
Mat disp;
ofstream myfile;
myfile.open ("prediction_values.txt");
for(int outer=0;outer<categories;outer++)
	{
for(int inner=0;inner<no_train;inner++)
{		
	disp=imread(images[listing]);
	//imshow("flag",disp);
	//waitKey(0);
	myfile<<category_names[outer]<<" "<<images[listing]<<" "<<categorize_train(disp,category_names[outer])<<" \n";
	listing++;
}
	} 
myfile.close();
}

double categorizer::categorize_train(Mat cap,string category) {
bowDescriptorExtractor -> setVocabulary(vocab);
vector<KeyPoint> kp;
Mat test11;
featureDetector -> detect(cap,kp);
bowDescriptorExtractor -> compute(cap,kp,test11);
double prediction = svms[category].predict(test11, true);
return prediction;
}

string categorizer::categorize(Mat cap) {
string predicted_category="";
bowDescriptorExtractor -> setVocabulary(vocab);
vector<KeyPoint> kp;
Mat test11;
featureDetector -> detect(cap,kp);
bowDescriptorExtractor -> compute(cap,kp,test11);
double best_score = 777, prediction=0;
for(int i = 0; i < categories; i++) {
string category = category_names[i];
prediction = svms[category].predict(test11, true);
if(prediction < best_score) {
best_score = prediction;
predicted_category = category;
}
}
ofstream myfile;
myfile.open ("prediction.txt");
myfile<<best_score;
myfile.close();
return predicted_category;
}

#endif
