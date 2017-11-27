#ifndef STL_FUNCTION_H
#define STL_FUNCTION_H

#include <vector>
#include "STL__Kernel.h"
#define  PI 3.1415926535898
using namespace std;

ostream & operator<<(ostream &os,const Point_3 &P);
ostream & operator<<(ostream &os,const Face_Tri &Tri);
ostream & operator<<(ostream &os,const Edge &e);
bool operator<(Point_3 P1, Point_3 P2);

//STL�ļ���ȡ����
int Read_STL(vector<Point_3> &Point_List, vector<HalfEdge> &Half_Edge_List, vector<Face_Tri> &Tri_List);//��ȡSTL�ļ�,����������������Tri_List��ģ�ͽڵ���_rb_tree_node


/*
//���Һ���
int Search_Edge_Of_Node(Point_3& P, Edge& e);//�жϱ�e�ķ�����Ƿ��ڵ�p�������߱���
int Search_Edge(vector<Edge> &Edge_List, Edge e);//�����Ƿ�����ͬ��*/

/*
//������㷨��غ���
int Compare_Node(const Point_3 p1, const Point_3 p2);//�Ƚ�����p1��p2�Ĵ�С;  p1 > p2 ����1, p1 = p2 ����0, p1 < p2 ����-1*/


//�����ؽ�����
Model Build_ToPo_Of_Model(vector<Point_3> &Point_List, vector<HalfEdge> &H_E_L, vector<Face_Tri> &Tri_List);//����ģ�͵����˽ṹ
void Build_Edge_List(vector<Point_3> &Point_List, vector<HalfEdge> &H_E_L, vector<Edge> &Edge_List);//��������,����ģ�ͱ߱�
void Build_TriandEdge_List_Of_Face(vector<Face_Tri>& Tri_List, vector<Edge> Edge_List);//���������Σ����������ε��ڽ����
/*
void Del_FaceListOfNode(int tri_num,Point& p);//����tri�ӵ�p���ڽ������ɾ��
void Add_FaceListOfNode(Triangle tri,Point* p);//����tri�����p���ڽ����
void Set_Triangle_List_OfNode(ListOfTriangle* Tri_List);//���ø��ڵ�����
void ReNew_EdgeListOfNode(Edge tri,Point* p);//���½ڵ�ĶԱ߱�
void Set_Edge_List_OfNode(ListOfTriangle* Tri_List);//���ø��ڵ�������߱�*/

//�������ʷ�
vector<int> Find_Tri_List_OfEdge(vector<Edge>::iterator e, vector<HalfEdge>& H_L);//���Ҳ����ر�e���ڽ�����
void Get_Feature_Line(Model& MyModel);//��ȡģ�͵������ߺ�������
vector<Sub_Set> Surface_div(Model& MyModel);//ģ������ֽ�
int Search_Face(vector<Face_Tri> F_L);//��������δ�������Ƭ������� ��������  ���򷵻�0
/*void Mesh(Model& MyModel, double MySize);//�����ʷ�
int Greater_Length(Edge e1, Edge e2);//�߳��ȽϺ���  e1 > e2: ����1  ���� ����0

//ģ���޸�����
void Repair_Overlay(Model* model1);//�޸��ص�����
void Merge_Node(Model* model1, Point P1, Point p2);//�ϲ�����,���������� < ����ֵ�Ķ���ϲ�
void ReSet_Edge_List_OfNode(Point& P, Point New_Point, Point P1, Point P2);//���µ�P�������߱�*/

//�������
void Show_Node_List(vector<Point_3>& Point_List);//���ģ�ͽڵ�����
void Show_Edge_List(Model& MyModel);//���ģ�ͱ�����
void Show_Triangle_List(Model& MyModel);//���ģ������������
void Show_Edge_List_OfNode(Model& MyModel);//����ڵ������������
void Show_Tri_List_OfNode(Model& MyModel);//������ڵ���ڽ����
void Show_Tri_List_OfEdge(Model& MyModel);//����ߵ��ڽ�������
void Show_Tri_List_OfFace(Model& MyModel);//��������ε��ڽ���Ƭ
void Show_Half_Edge_List(vector<HalfEdge> H_E_L);//���ģ�͵İ�߱�
void Write_Data(Model& MyModel);//�����ظ������������Ƭд���м��ļ�
void Write_Data_F(Model& MyModel);

#endif