#include "categorizer.h"
 
int main() {
// Number of clusters for building BOW vocabulary from SURF features
int clusters = 100;
categorizer c(clusters,1);
c.build_vocab();
c.train_classifiers();
return 0;
}

