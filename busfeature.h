#ifndef _BUSFEATURE_
#define _BUSFEATURE_
#include "busheaders.h"
using namespace std;
using namespace cv;
class BUSFeature
{
    private:
    int imgcols,imgrows;
    //ͼ��Ŀ�ȣ�������,ͼ��ĸ߶ȣ�������
    Mat rgbimg,grayimg,edge,label,label255;
      //rgbimg grayimg edge label label255�ֱ���������rgbͼ�ͻҶ�ͼ,�;����ֶ����Զ��ָ��õ��������߽�ͼ��ֵΪ1ʱ�������߽�����ص㣩����������ʵ��ǩ����ֵͼ��,��������ʵ��ǩ��0 255��
    vector<Point> allPoint;
     //allPoint ��Opencv Point�ṹ���������߽���������Ϣ
    TextureEValues glcmfeature;
    //GlCM feature of tumor save in a struct including  float energy,contrast, homogenity,entropy;
    GLRLMValues<float> glrlmfeature;
     //glrlm feature of tumor save
    float tumorDepth,tumorMeanGray,tumorStdGray,solidity,majorAxisLength,minorAxisLength,tumorArea,tumorPerimeter,bgAvg,tumorNum;
     //�������������(���ظ���Ϊ��λ����),ƽ���Ҷ�,�Ҷȱ�׼��,solidity,���᳤��,���᳤��,���,�ܳ�,Otsu�㷨�õ�����ֵ(ǰ���ͱ�������ֵ),���������ظ���
    void IntialBaseVar(const contourpoint * plist,const int &plength);
    void getGLRLMFeatuure(const Mat& dst,int gravel,GLRLMValues<float>& glrlmData);
    TextureEValues getGlcmFeature(Mat dst);
public:
    BUSFeature(uchar* data,int width,int height,int format,const contourpoint *plist,const int & length);
    //data ͼƬ�ڴ��ַ
    //format #define GRAY8 CV_8UC1 8λ1ͨ�� #define RGB888 CV_8UC3 8λ3ͨ��
    // plist���������飺 struct contourpoint{int x;int y;};xΪ������б� y�Ǿ�����б�
    //length ���������
    BUSFeature(const char *imgpath,const contourpoint *plist,const int & length);
    // ����ԭͼ�ͺ��߱�עͼ�Ĺ��캯��
    // �������ԣ���ȡ�������Բ��ԡ�����ʱע�͵�
    BUSFeature(const char *imgpath,const char *bgpath);
    ~BUSFeature();
    float getDepth();
    //tumor �������
    float getMajorAxisLength();
    //����
    float getMinorAxisLength();
     //�̾�
    float getSolidity();
    //solidity
    float getArea();
    //���
    float getAvgGrayscale();
     //ƽ���Ҷ�
    float getStdGrayscale();
     //�Ҷȱ�׼��
    float getPerimeter();
   //�ܳ�
    vector<float>  getEdgeFeature();
   //��ñ�Ե����
    vector<float>  getInnerEchoFeature();
    //����ڲ���������
    vector<float>  getNangShiFeature(float nungthresh=0.4,float shithresh=0.9);
       //�����ʵ����
    vector<float>  getPosterEchoFeature();
        //��ú󷽻�������
    vector<float>  getShapeFeature();
    //�������״����
    void printAllFeature(string printpath);
    //�������е�����ֵ ,������ļ�·��Ϊ printpath+"-t.txt"
};
#endif
