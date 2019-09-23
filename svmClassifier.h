#ifndef _SVMCLASSIFIER_
#define _SVMCLASSIFIER_
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <vector>
#include <fstream>
#include "./include/svm/svm.h"

//���������ĳ���
#define EdgeFeaturelen 2
#define InnerEchoFeaturelen 5
#define PosterEchoFeaturelen 4
#define ShapeFeaturelen 6
#define NangshiFeaturelen 24
using namespace std;
static int (*info)(const char *fmt,...) = &printf;

//ģ���ļ�·��
typedef struct modelpath
{
    char * edge;
    char * innerecho;
    char * posterecho;
    char * nangshi;
    char * shape;
} modelpath;
//�����ļ�·��
struct profilepath
{
    char * edge;
    char * innerecho;
    char * posterecho;
    char * nangshi;
    char * shape;
};
struct featurerange
{
    float minf;
    float maxf;
};

class svmClassifier
{
    private:
     struct svm_model*  EdgeModel;
     struct svm_model*  InnerEchoModel;
     struct svm_model*  NangShiModel;
     struct svm_model*  PosterEchoModel;
     struct svm_model*  ShapeModel;
     struct featurerange EdgeRange[EdgeFeaturelen],NangShiRange[NangshiFeaturelen],PosterEchoRange[PosterEchoFeaturelen], ShapeRange[ShapeFeaturelen],InnerEchoRange[InnerEchoFeaturelen];
     svmClassifier(struct modelpath & model,struct profilepath & path);
public:
//����ģ�ͺ���������ļ�
    static svmClassifier & getModel(struct modelpath & model,struct profilepath & path)
    {
        static svmClassifier instance=svmClassifier(model,path);  //�ֲ���̬����
        return instance;
    }
  //  ~svmClassifier();
    void loadModel(struct modelpath & model);
    void loadProfile(struct profilepath & path);
//ϵͳ�ر�ʱ�ͷ��ڴ�
     void freeModel();

    void scaleFeature(const vector<float> & feature,vector<float> & scaledfeature,struct featurerange * range);
//Ԥ�⺯��
    float predictLabel(const vector<float> & attrlist,struct svm_model *model);
    int   getEdgeLabel(const vector<float> &feature);
    // �߽�������label 1 Ϊ���� -1Ϊģ��
    int   getInnerEchoLabel(const vector<float> & feature);
    //�ڲ�����label 1 �ͻ��� 2�޻��� 3 ��ϻ���
    int   getNangShiLabel(const vector<float> &feature);
    //��ʵ״̬ 1 Ϊ���� 2 Ϊʵ�� 3 ���
    int   getPosterEchoLabel(const vector<float> &feature);
    //�󷽻���label 1 Ϊ˥�� 2���� 3 ��ǿ
    int   getShapeLabel(const vector<float> &feature);

};


#endif

