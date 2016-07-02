#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class FeaturesReduction
{
public:
	FeaturesReduction();
	~FeaturesReduction();
	void generate(Mat& features, Mat& labels);
	void project(Mat& features, Mat& featOut);
	int getType();
	void setType(int i);
private:
	void makePCA(Mat& features, int numFeat);
	void makeLDA(Mat& features, Mat& target);
	void noReduction();

	Mat projection_result;

	PCA* pca = NULL;
	LDA* lda = NULL;
	int typeReduction = 0;

};

