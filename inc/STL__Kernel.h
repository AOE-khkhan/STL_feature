#ifndef STL_KERNEL_H
#define STL_KERNEL_H

#define Tolerance 1.0e-14

#include <vector>
#include <set>
using std::vector;
using std::set;

class HalfEdge;

class Point_3
{
public:
	Point_3():id(0),flag(1),Feature_Point(0)
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	Point_3(double xi, double yi, double zi, int f = 1, int F_P = 0, int ID = 0)
		:flag(f),Feature_Point(F_P),id(ID)
	{
		x = xi;
		y = yi;
		z = zi;
		/*half_edge = 0;*/
	}
	const double& X() const  { return x; }

	const double& Y() const { return y; }

	const double& Z() const { return z; }

	const int& V_ID() const { return id; }//���ؽڵ���

	const int& Flag() const { return flag; }

	const int& Feature() const { return Feature_Point; }

	double & X() { return x; }

	double& Y() { return y; }

	double& Z() { return z; }

	int& V_ID() { return id; }//���ؽڵ���

	int& Flag() { return flag; }

    int& Feature() { return Feature_Point; }

	vector<int>& H_E() { return half_edge; }
private:
	int id;//������
	int flag;//ɾ����ǣ�1��δɾ��; 0����ɾ��
	int Feature_Point;//��������: 1: ������; 0:��ͨ��
	vector<int> half_edge;//�����ߵ�����
	double x;
	double y;
	double z;
};

class Face_Tri
{
public:
	Face_Tri():id(0),flag(1),Sub_Face_set(0)
	{
		for (int i = 0; i < 3; i++)
			e[i] = 0;
	}
	/*const int& const E0() { return e[0]; }

	const int& const E1() { return e[1]; }

	const int& const E2() { return e[2]; }*/

	const int& F_ID() const { return id; }

	const int& Flag() const { return flag; }

	const int& P_ID(int i) const { return p_id[i]; }

	const int& sub_face() const { return Sub_Face_set; }

	int& E(int i) { return e[i]; }

	int& F_ID() { return id; }

	int& Flag() { return flag; }

	int& P_ID(int i) { return p_id[i]; }

    int& sub_face() { return Sub_Face_set; }

	std::vector<double>& Dir() { return Direction; }
private:
	int id;//��Ƭ���
	int flag;//ɾ����ǣ�1��δɾ��; 0����ɾ��
	int Sub_Face_set;//������ 0:��ʾδ�������� >0:����������
	int e[3];//�����ߵ�����
	std::vector<double> Direction;//��Ƭ����
	int p_id[3];//������Ƭ��������ı��
};

class Face_Qua
{

};

class HalfEdge
{
public:
	HalfEdge()
	{
		id = 0;
		e_id = 0;
		p_of_halfedge = 0;
		tri_of_halfedge = 0;
	}
	HalfEdge(int P, int Tri, int HE_ID = 0, int E_ID = 0):id(HE_ID),e_id(E_ID)
	{
		p_of_halfedge = P;
		tri_of_halfedge = Tri;
	}
	const int& HE_ID() const { return id; }

	const int& E_ID() const { return e_id; }

	const int& Half_P() const { return p_of_halfedge; }//��������ڵ���

	const int& Half_F() const { return tri_of_halfedge; }//������������

    int& HE_ID() { return id; }//���ذ�߱��

	int& E_ID() { return e_id; }//���������ߵı��

	int& Half_P() { return p_of_halfedge; }//��������ڵ���

	int& Half_F() { return tri_of_halfedge; }//������������
private:
	int id;//��߱��
	int e_id;//���ڱߵı��
	int p_of_halfedge;//�������
	int tri_of_halfedge;//��������
};

class Edge
{
public:
	Edge()
	{
		id = 0;
		Feature_Line = 0;
		p_of_edge[0] = 0;
		p_of_edge[1] = 0;
	}
	Edge(int p0, int p1, int ID = 0):id(ID)
	{
		Feature_Line = 0;
		p_of_edge[0] = p0;
		p_of_edge[1] = p1;
	}
	const int& E_ID() const { return id; }
	const double& Length() const { return length; }
	const int& P0() const { return p_of_edge[0]; }
	const int& P1() const { return p_of_edge[1]; }
	const int& Feature() const { return Feature_Line; }
	const double& Angle() const { return Dih_Angle; }
	int& E_ID() { return id; }
	double& Length() { return length; }
	int& P0() { return p_of_edge[0]; }
	int& P1() { return p_of_edge[1]; }
	int& Feature() { return Feature_Line; }
	double& Angle() { return Dih_Angle; }
	vector<int>& H_Edge() { return half_edge; }
private:
	int id;//�߱��
	int Feature_Line;//�����߱��: 1: ������; 0:��ͨ��
	double length;//�ߵĳ���
	vector<int> half_edge;//��ɱߵ������� �������1:�߽�� 2:ȫ��
	int p_of_edge[2];//�ߵ����˵������
	double Dih_Angle;//�ߵĶ����
};

class Model
{
public:
	Model()
	{
		;
	}
	Model(vector<Point_3> P_L, vector<HalfEdge> H_L, vector<Edge> E_L, vector<Face_Tri> T_L)
	{
		Point_List = P_L;
		Half_Edge_List = H_L;
		Edge_List = E_L;
		Tri_List = T_L;
	}
	vector<Point_3>& point() { return Point_List; }
	vector<HalfEdge>& h_edge() { return Half_Edge_List; }
	vector<Edge>& edge() { return Edge_List; }
	vector<Face_Tri>& face() { return Tri_List; }
private:
	vector<Point_3> Point_List;//���
	vector<HalfEdge> Half_Edge_List;//��߱�
	vector<Edge> Edge_List;//�߱�
	vector<Face_Tri> Tri_List;//���
};

struct Sub_Set
{
	vector<int> Sub_Face;//����
	set<int> Loop_Edge;//����߽�
};

#endif