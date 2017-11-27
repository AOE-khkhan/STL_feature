#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <iterator>
#include "STL__Function.h"
using namespace std;

ostream & operator<<(ostream &os,const Point_3 &P)
{
	//os << P.V_ID() << setw(15) << P.X() << setw(15) << P.Y() << setw(15) << P.Z();
	os << P.X() << setw(15) << P.Y() << setw(15) << P.Z();
	return os;
}
ostream & operator<<(ostream &os,const Face_Tri &Tri)
{
	//os << Tri.F_ID() << setw(15) << Tri.P_ID(0) << setw(15) << Tri.P_ID(1) << setw(15) << Tri.P_ID(2);
	//os << setw(15) << Tri.P_ID(0) << setw(15) << Tri.P_ID(1) << setw(15) << Tri.P_ID(2);
	os << "3" << setw(15) << Tri.P_ID(0) - 1 << setw(15) << Tri.P_ID(1) - 1 << setw(15) << Tri.P_ID(2) - 1;
	return os;
}
ostream & operator<<(ostream &os,const Edge &e)
{
	os << e.P0() << ", " << e.P1();
	return os;
}
bool operator<(Point_3 P1, Point_3 P2)
{
	if (P1.X() < P2.X()-Tolerance || abs(P1.X() - P2.X()) < Tolerance && P1.Y() < P2.Y()-Tolerance || abs(P1.X() - P2.X()) < Tolerance && abs(P1.Y() - P2.Y()) < Tolerance && P1.Z() < P2.Z()-Tolerance)
		return 1;
	else return 0;
}
bool operator==(Point_3 P1, Point_3 P2)
{
	if (abs(P1.X() - P2.X()) < Tolerance && abs(P1.Y() - P2.Y()) && abs(P1.Z() - P2.Z()) < Tolerance)
		return 1;
	else return 0;
}

//STL�ļ���ȡ
int Read_STL(vector<Point_3> &Point_List, vector<HalfEdge> &Half_Edge_List, vector<Face_Tri> &Tri_List)
{
	//��ȡSTL�ļ�,����������������Tri_List��ģ�ͽڵ�����Point_List
	set<Point_3> Point_Set;
	ifstream read;
	read.open("123.stl",ios::in);
	string line;
	getline(read, line);
	string end = "end" + line;
	int n = 0;//number of Triangle
	int m = 0;//number of Node
	int k = 0;//number of Half_Edge
	set<Point_3>::const_iterator point_itr;
	Point_List.reserve(10000);
	Half_Edge_List.reserve(10000);
	Tri_List.reserve(10000);
	std::cout << "�ļ���ȡ��...\n";
	while (1)
	{
		getline(read, line);
		if (line == end) break;
		getline(read, line);
		Face_Tri Tri;
		Point_3 p[3],q[3];//�洢������������
		n++;
		Tri.F_ID() = n; // ������Ƭ���
		if (n > 1)
		{
			for (int j = 0; j < 3; j++)
				q[j] = p[j];
		}
		for (int i = 0; i < 3; i++)
		{
			read >> line;
			Point_3 pt;
			read >> pt.X() >> pt.Y() >> pt.Z();
			int flag = 0;
			for (int j = 0; j < 3; j++)
			{
				if (pt == q[j])
			    {
					pt.V_ID() = q[j].V_ID();
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				point_itr = Point_Set.find(pt);
				if (point_itr == Point_Set.end())
				{
					m++;
					pt.V_ID() = m;
					Point_List.push_back(pt);//�����µ�
					Point_Set.insert(pt);
				}
				else pt.V_ID() = point_itr->V_ID();
			}
			p[i] = pt;
			Tri.P_ID(i) = pt.V_ID();
			read.get();
		}
		//---------------------------������߱�--------------------------------------//
		HalfEdge he0(p[0].V_ID(), n, ++k); Half_Edge_List.push_back(he0); 
		Point_List[p[2].V_ID() - 1].H_E().push_back(k);//���ýڵ�ĳ����߱�
		Tri.E(0) = k;//����������Ƭ�������߱�
		HalfEdge he1(p[1].V_ID(), n, ++k); Half_Edge_List.push_back(he1);
		Point_List[p[0].V_ID() - 1].H_E().push_back(k);
		Tri.E(1) = k;
		HalfEdge he2(p[2].V_ID(), n, ++k); Half_Edge_List.push_back(he2);
		Point_List[p[1].V_ID() - 1].H_E().push_back(k);
		Tri.E(2) = k;

		Tri_List.push_back(Tri);
		getline(read, line);
		getline(read, line);
	}
	read.close();
	std::cout << "�ļ���ȡ����...\n";
	vector<Point_3>(Point_List).swap(Point_List);//ѹ��ʣ��ռ�
	vector<HalfEdge>(Half_Edge_List).swap(Half_Edge_List);
	vector<Face_Tri>(Tri_List).swap(Tri_List);
	cout << "Number of Node: " << m << endl;
	cout << "Number of Triangle: " << n << endl;
	return 1;
}

//�����ؽ�
Model Build_ToPo_Of_Model(vector<Point_3> &Point_List, vector<HalfEdge> &H_E_L, vector<Face_Tri> &Tri_List)
{//�ýڵ������������������ģ�����˽ṹ
    std::cout << "�����ؽ�...\n";
	//-----------------------����������Ƭ����ģ�ͱ��������ڵ������߱�--------------------------------------//
	vector<Face_Tri>::iterator it_Tri;
	for (it_Tri = Tri_List.begin(); it_Tri != Tri_List.end(); it_Tri++)
	{//��ÿ��������Ƭ
		//-------------------------------����������Ƭ�ĵ�λ��ʸ------------------------------------------------//
		double D_X, D_Y, D_Z;
		Point_3 p0 = Point_List[(*it_Tri).P_ID(0) - 1];
		Point_3 p1 = Point_List[(*it_Tri).P_ID(1) - 1];
		Point_3 p2 = Point_List[(*it_Tri).P_ID(2) - 1];
		/*std::cout << p0 << std::endl;
		std::cout << p1 << std::endl;
		std::cout << p2 << std::endl;*/
		D_X = (p2.Y()- p1.Y()) * (p0.Z() - p1.Z()) - (p2.Z() - p1.Z()) * (p0.Y() - p1.Y());
		D_Y = -(p2.X() - p1.X()) * (p0.Z() - p1.Z()) + (p2.Z() - p1.Z()) * (p0.X() - p1.X());
		D_Z = (p2.X() - p1.X()) * (p0.Y() - p1.Y()) - (p2.Y() - p1.Y()) * (p0.X() - p1.X());

		double Length = sqrt(D_X * D_X + D_Y * D_Y + D_Z * D_Z);
		D_X /= Length; D_Y /= Length; D_Z /= Length;
		
		it_Tri->Dir().push_back(D_X); it_Tri->Dir().push_back(D_Y); it_Tri->Dir().push_back(D_Z);
		//-------------------------------����ģ�͵ı߱�------------------------------------------------//
		/*Edge e0(it_Tri->P[0], it_Tri->P[1]), e1(it_Tri->P[1], it_Tri->P[2]), e2(it_Tri->P[2], it_Tri->P[0]);
		e0.num = 0; e1.num = 1; e2.num = 2; 
		e0.flag = 0; e1.flag = 0; e2.flag = 0;
		e0.Tri_List.push_back(it_Tri->num); e1.Tri_List.push_back(it_Tri->num); e2.Tri_List.push_back(it_Tri->num);
		//-------------------------------���õ��������------------------------------------------------//
		Point_List[it_Tri->P[0].num - 1].Edge_List.push_back(e2);
		Point_List[it_Tri->P[1].num - 1].Edge_List.push_back(e0);
		Point_List[it_Tri->P[2].num - 1].Edge_List.push_back(e1);*/
		//std::cout << it_Tri->Dir()[0] << "  " << it_Tri->Dir()[1] << "  " << it_Tri->Dir()[2] << std::endl; 
	}
	//--------------------------------------------------------------------------------------------------------//
	vector<Edge> Edge_List;
	Build_Edge_List(Point_List, H_E_L, Edge_List);//����ģ�͵ı�����,ͬʱ����ÿ���ߵ��ڽ�����������
	/*Build_TriandEdge_List_Of_Face(Tri_List, Edge_List);//Ϊÿ����������Ƭ������������ڽ����*/
	Model MyModel(Point_List, H_E_L, Edge_List, Tri_List);
	return MyModel;
}

void Build_Edge_List(vector<Point_3> &Point_List, vector<HalfEdge> &H_E_L, vector<Edge> &Edge_List)
{
	vector<Point_3>::iterator itp = Point_List.begin();
	int edge_num = 0;//�߱��
	//Edge_List.reserve(20000);
	while (itp != Point_List.end())
	{
		vector<int>::iterator ite_of_p = itp->H_E().begin();
		while (ite_of_p != itp->H_E().end())
		{
			if (H_E_L[*ite_of_p - 1].E_ID() != 0)
				ite_of_p++;
			else
			{//����һ���±�
				edge_num++;//�߱��
				Edge e(H_E_L[*ite_of_p- 1].Half_P(), itp->V_ID(), edge_num);
				H_E_L[*ite_of_p- 1].E_ID() = edge_num;//���ð�������ıߵı��
				e.H_Edge().push_back(*ite_of_p);//������ɱߵİ��(ÿ�������������������)
				//������һ�����
				Point_3 p_temp = Point_List[H_E_L[*ite_of_p- 1].Half_P() - 1];
				//��p_temp�ĳ����߱��в��������Ϊitp�İ��
				vector<int>::iterator ite_of_p_temp = p_temp.H_E().begin();
				while (ite_of_p_temp != p_temp.H_E().end())
				{
					if (H_E_L[*ite_of_p_temp - 1].Half_P() == itp->V_ID() && H_E_L[*ite_of_p_temp - 1].E_ID() == 0)
					{
						H_E_L[*ite_of_p_temp - 1].E_ID() = edge_num;
						e.H_Edge().push_back(*ite_of_p_temp);//������ɱߵ���һ�����
						break;
					}
					else ite_of_p_temp++;
				}
				Point_3 p_temp0 = Point_List[H_E_L[*ite_of_p- 1].Half_P() - 1];
				Point_3 p_temp1 = Point_List[itp->V_ID() - 1];
				double length = (p_temp0.X() - p_temp1.X()) * (p_temp0.X() - p_temp1.X())
					           +(p_temp0.Y() - p_temp1.Y()) * (p_temp0.Y() - p_temp1.Y())
							   +(p_temp0.Z() - p_temp1.Z()) * (p_temp0.Z() - p_temp1.Z());
				e.Length() = length;//����ߵĳ���*/
				Edge_List.push_back(e);
				//cout << ite_of_p->num << endl;
			}
		}
		itp++;
	}
	std::cout << "�����ؽ����...\n";
	cout << "Number of Edge: " << edge_num <<endl;
}

//�����ط�
void Get_Feature_Line(Model& MyModel)
{//��ȡģ�͵������ߺ�������
	//----------------------------------------------���ڶ����--------------------------------------------------------------------//
	double alpha1 = 0.0;//С��10�ȵ����ֵ
	double alpha2 = 180.0;//����10�ȵ���Сֵ
	double alpha_fa = 0.0;//����Ƿ�ֵ
	struct Ratio_Of_Edge
	{
		int num;//�ߵı��
		double r_o_e;//�ܳ���ֵ
	};//�洢�ߵ��ܳ���ֵ
	vector<Ratio_Of_Edge> Ratio;
	//-----------------------------����ÿ���ߵĶ����ֵ���ܳ���ֵ----------------------------------------------------//
	vector<Edge>::iterator it_Edge;
	for (it_Edge = MyModel.edge().begin(); it_Edge != MyModel.edge().end(); it_Edge++)
	{//��ģ�͵�ÿ����
		if (it_Edge->H_Edge().size() != 2)
		{
			it_Edge->Angle() = 180.0;
			std::cout << *it_Edge << "  " << it_Edge->H_Edge().size() << std::endl;
		}
		else
		{
			//cout << "#" << it_Edge->P0() << ", " << it_Edge->P1() << endl;
			vector<int> F_L_E = Find_Tri_List_OfEdge(it_Edge, MyModel.h_edge());
			//-----------------------�����ڽ������ε��ܳ���-------------------------------------------//
			int he0, he1, he2;
			he0 = MyModel.face()[F_L_E[0] - 1].E(0);
			he1 = MyModel.face()[F_L_E[0] - 1].E(1);
			he2 = MyModel.face()[F_L_E[0] - 1].E(2);
			int e0, e1, e2;
			e0 = MyModel.h_edge()[he0 - 1].E_ID();
			e1 = MyModel.h_edge()[he1 - 1].E_ID();
			e2 = MyModel.h_edge()[he2 - 1].E_ID();
			//std::cout << "!!!  " << e0 << "  " << e1 << " " << e2 << std::endl;
			double lengthA;
			lengthA = MyModel.edge()[e0 - 1].Length() + MyModel.edge()[e1 - 1].Length() + MyModel.edge()[e2 - 1].Length();
			he0 = MyModel.face()[F_L_E[1] - 1].E(0);
			he1 = MyModel.face()[F_L_E[1] - 1].E(1);
			he2 = MyModel.face()[F_L_E[1] - 1].E(2);

			e0 = MyModel.h_edge()[he0 - 1].E_ID();
			e1 = MyModel.h_edge()[he1 - 1].E_ID();
			e2 = MyModel.h_edge()[he2 - 1].E_ID();
			double lengthB = MyModel.edge()[e0 - 1].Length() + MyModel.edge()[e1 - 1].Length() + MyModel.edge()[e2 - 1].Length();
			if (lengthA < lengthB)
			{//��֤lengthA > lengthB
				double temp;
				temp = lengthA;
				lengthA = lengthB;
				lengthB = temp;
			}
			Ratio_Of_Edge rae;
			rae.num = it_Edge->E_ID();  rae.r_o_e = sqrt(lengthA / lengthB);
			Ratio.push_back(rae);
			//---------------------------------��������---------------------------------------------//
			double A = sqrt(MyModel.face()[F_L_E[0] - 1].Dir()[0] * MyModel.face()[F_L_E[0] - 1].Dir()[0] 
			               +MyModel.face()[F_L_E[0] - 1].Dir()[1] * MyModel.face()[F_L_E[0] - 1].Dir()[1]
			               +MyModel.face()[F_L_E[0] - 1].Dir()[2] * MyModel.face()[F_L_E[0] - 1].Dir()[2]
			               );
			double B = sqrt(MyModel.face()[F_L_E[1] - 1].Dir()[0] * MyModel.face()[F_L_E[1] - 1].Dir()[0] 
			               +MyModel.face()[F_L_E[1] - 1].Dir()[1] * MyModel.face()[F_L_E[1] - 1].Dir()[1]
			               +MyModel.face()[F_L_E[1] - 1].Dir()[2] * MyModel.face()[F_L_E[1] - 1].Dir()[2]
			               );
			double AB = MyModel.face()[F_L_E[0] - 1].Dir()[0] * MyModel.face()[F_L_E[1] - 1].Dir()[0]
			           +MyModel.face()[F_L_E[0] - 1].Dir()[1] * MyModel.face()[F_L_E[1] - 1].Dir()[1]
			           +MyModel.face()[F_L_E[0] - 1].Dir()[2] * MyModel.face()[F_L_E[1] - 1].Dir()[2];
			it_Edge->Angle() = acos(AB / (A * B)) * 180 / PI;
			if (it_Edge->Angle() > alpha1 && it_Edge->Angle() < 10.0) alpha1 = it_Edge->Angle();
			else if (it_Edge->Angle() < alpha2 && it_Edge->Angle() > 10.0) alpha2 = it_Edge->Angle();
			//cout << it_Edge->Angle() << endl;
		}
	}
	alpha_fa = (alpha1 + alpha2) / 2.0;
	cout << "alpha = " << alpha_fa << endl;
	for (it_Edge = MyModel.edge().begin(); it_Edge != MyModel.edge().end(); it_Edge++)
	{
		if (it_Edge->Angle() > alpha_fa) 
		{
			it_Edge->Feature() = 1;//���øñ�Ϊ������
			MyModel.point()[it_Edge->P0() - 1].Feature() = 1;//���ñߵ����˵�Ϊ������
			MyModel.point()[it_Edge->P1() - 1].Feature() = 1;
		}
	}
	//--------------------------------------------------------------------���ڱ߳���ֵ--------------------------------------------------------------//
	vector<Ratio_Of_Edge>::iterator it_roe;
	double sum = 0.0;
	for (it_roe = Ratio.begin(); it_roe != Ratio.end(); it_roe++)
	{
		sum += it_roe->r_o_e;
	}
	double Tao = 4 * sum / Ratio.size();
	for (it_roe = Ratio.begin(); it_roe != Ratio.end(); it_roe++)
	{
		if (it_roe->r_o_e >= Tao)
		{
			int ne = it_roe->num;
			if (MyModel.edge()[ne - 1].Feature() != 1)
			{
				MyModel.edge()[ne - 1].Feature() = 2;//���øñ�Ϊ������
				MyModel.point()[MyModel.edge()[ne - 1].P0() - 1].Feature() = 1;//���ñߵ����˵�Ϊ������
				MyModel.point()[MyModel.edge()[ne - 1].P1() - 1].Feature() = 1;
			}
		}
	}
}

vector<int> Find_Tri_List_OfEdge(vector<Edge>::iterator e, vector<HalfEdge>& H_L)
{
	vector<int> F_L;
	vector<int>::iterator it_H_E_L;
	for (it_H_E_L = e->H_Edge().begin(); it_H_E_L != e->H_Edge().end(); it_H_E_L++)
	{
		int fa = H_L[*it_H_E_L - 1].Half_F();
		F_L.push_back(fa);
	}
	return F_L;
}

vector<Sub_Set> Surface_div(Model& MyModel)
{//������������߽�(�߽�δ����)
	std::cout << "����ֽ�...\n";
	vector<Sub_Set> Div_Result;//����ֽ���
	vector<Face_Tri>& F_L = MyModel.face();
	vector<Edge>& E_L = MyModel.edge();
	vector<HalfEdge>& H_E_L = MyModel.h_edge();
	int temp = 0;
	int Num_Set = 0;//ͳ���������
	while (temp = Search_Face(F_L))
	{//�������δ�������Ƭ 
		Sub_Set Sub_Surface;
		Num_Set++;
		stack<int> fl_Temp;//��ʱջ ���ڴ洢���������Ƭ
		fl_Temp.push(temp);

		//����ͨ������������� ����Ƭ���з���
		while (fl_Temp.size() != 0)
		{//���ջ��Ϊ��
			int f = fl_Temp.top();//����ջ��Ԫ��
			fl_Temp.pop();
			//cout << f << "...\n";
			Sub_Surface.Sub_Face.push_back(f);//����Ƭ��ż�����Ƭ��
			F_L[f - 1].sub_face() = Num_Set;//������Ƭ��������Ƭ�����
			for (int j = 0; j < 3; j++)
			{//�Ը���Ƭ��ÿ����
				int hei = F_L[f - 1].E(j);
				int ei = H_E_L[hei - 1].E_ID();
				set<int>::iterator it_s;
				it_s = Sub_Surface.Loop_Edge.find(ei);
				if (it_s != Sub_Surface.Loop_Edge.end())
					Sub_Surface.Loop_Edge.erase(ei);
				else Sub_Surface.Loop_Edge.insert(ei);
				if (E_L[ei - 1].Feature() == 0)
				{//�����ñ߲���������
					for (vector<int>::iterator it_H_E = E_L[ei - 1].H_Edge().begin(); it_H_E != E_L[ei - 1].H_Edge().end(); it_H_E++)
					{//�Ըñߵ�ÿ�����
						if (*it_H_E != hei)
						{
							if (F_L[H_E_L[*it_H_E - 1].Half_F() - 1].sub_face() == 0)//���ڽ��治����Ƭ����
							    fl_Temp.push(H_E_L[*it_H_E - 1].Half_F());//������Ƭѹ��ջ
							break;
						}
					}
				}
			}
		}
		//cout << "!!!\n";
		Div_Result.push_back(Sub_Surface);
	}
	std::cout << "����ֽ����...\n";
	std::cout << "Number of SubSet: " << Div_Result.size() << std::endl;
	return Div_Result;
}

int Search_Face(vector<Face_Tri> F_L)
{//��������δ�������Ƭ������� ��������  ���򷵻�0
	for (int i = 0; i < F_L.size(); i++)
	{
		if (F_L[i].sub_face() == 0)
		{
			return F_L[i].F_ID();
			break;
		}
	}
	return 0;
}

//�������
void Show_Node_List(vector<Point_3>& Point_List)
{//���ģ�͵Ľڵ�����
	vector<Point_3>::iterator itp;
	cout << "ģ�ͽڵ��б�:\n";
	for (itp = Point_List.begin(); itp != Point_List.end(); itp++)
	{
		if (itp->Feature() == 1)
		  cout << *itp << endl;
	}
}

void Show_Edge_List(Model& MyModel)
{//���ģ�͵ı�����
	vector<Edge>& Edge_List = MyModel.edge(); 
	vector<Edge>::iterator ite;
	cout << "ģ�ͱ��б�:\n";
	for (ite = Edge_List.begin(); ite != Edge_List.end(); ite++)
	{
		//if (ite->Feature() == 2)
		//{
			cout << "# " << ite->E_ID() << endl;
			cout << "(" << ite->P0() << ", " << ite->P1() << ")" << "... " << ite->Feature() << endl;
		//}
	}
}

void Show_Triangle_List(Model& MyModel)
{
	vector<Face_Tri>& Tri_List = MyModel.face();
	cout << "ģ�͵�������Ƭ�б�:\n";
	vector<Face_Tri>::iterator itt;
	for (itt = Tri_List.begin(); itt != Tri_List.end(); itt++)
	{
		cout << *itt << endl;
		/*cout << itt->Direction[0] << "    " << itt->Direction[1] << "     " << itt->Direction[2] << endl;*/
	}
}

void Show_Edge_List_OfNode(Model& MyModel)
{//����ڵ�ĳ����߱�
	vector<Point_3>& P_L = MyModel.point();
	vector<HalfEdge>& H_E_L = MyModel.h_edge();
	vector<Edge>& E_L = MyModel.edge();
	vector<Point_3>::iterator it_Point;
	cout << "���ڵ�ĳ������б�:\n";
	for (it_Point = P_L.begin(); it_Point != P_L.end(); it_Point++)
	{//��ÿ���ڵ�
		//if (ite->flag < 0)
		cout << "#" << it_Point->V_ID() << endl;
		vector<int>::iterator it_Edge;
		for (it_Edge = it_Point->H_E().begin(); it_Edge != it_Point->H_E().end(); it_Edge++)
		{
			int h_e_temp = *it_Edge;//�ڵ�ĳ����߱��
			int p_temp = H_E_L[h_e_temp - 1].Half_P();
			cout << "(" << it_Point->V_ID() << ", " << p_temp << ")" << endl;
		}
	}
}

void Show_Tri_List_OfNode(Model& MyModel)
{//������ڵ���ڽ����
	//������ʽ:��-->���-->��
	vector<Point_3> P_L = MyModel.point();
	vector<HalfEdge> H_E_L = MyModel.h_edge();
	vector<int>::iterator it_H_E;//�������
	vector<Point_3>::iterator it_P;
	cout << "���ڵ���ڽ����:\n";
	for (it_P = P_L.begin(); it_P != P_L.end(); it_P++)
	{//��ÿ������
		cout << "#" << it_P->V_ID() << endl;
		for (it_H_E = it_P->H_E().begin(); it_H_E != it_P->H_E().end(); it_H_E++)
		{
			cout << H_E_L[*it_H_E - 1].Half_F() << ", ";
		}
		cout << endl;
	}
	//vector<Point_3>
}

void Show_Tri_List_OfEdge(Model& MyModel)
{//���ģ��ÿ���ߵ��ڽ����
	//������ʽ:��-->���-->��
	vector<Edge>& E_L = MyModel.edge();
	vector<HalfEdge>& H_L = MyModel.h_edge();
	vector<Edge>::iterator it_E;
	for (it_E = E_L.begin(); it_E != E_L.end(); it_E++)
	{//��ÿ����
		cout << "#" << it_E->E_ID() << "(" << it_E->P0() << ", " << it_E->P1() << ")" << endl;
		vector<int>::iterator it_H_E_L;//�������
		for (it_H_E_L = it_E->H_Edge().begin(); it_H_E_L != it_E->H_Edge().end(); it_H_E_L++)
		{//�Ըñ���������ÿ�����
			cout << H_L[*it_H_E_L - 1].Half_F() << ", " << endl;
		}
	}
}

void Show_Tri_List_OfFace(Model& MyModel)
{//��������ε��ڽ���Ƭ
	//������ʽ:��-->���-->��-->���-->��
	vector<Face_Tri>& F_T = MyModel.face();
	vector<HalfEdge>& H_E_L = MyModel.h_edge();
	vector<Edge>& E_L = MyModel.edge();
	vector<Face_Tri>::iterator it_F;
	for (it_F = F_T.begin(); it_F != F_T.end(); it_F++)
	{//��ÿ��������Ƭ
		cout << "#" << it_F->F_ID() << endl;
		cout << "(" << it_F->P_ID(0) << ", " << it_F->P_ID(1) << ", " << it_F->P_ID(2) << ")" << endl;
		vector<int>::iterator it_H_E;
		for (int i = 0; i < 3; i++)
		{//��ÿ��������
			int hei = it_F->E(i);//��߱��
			int ei = H_E_L[hei - 1].E_ID();//��������ıߵı��
			for (it_H_E = E_L[ei - 1].H_Edge().begin(); it_H_E != E_L[ei - 1].H_Edge().end(); it_H_E++)
			{//�Ըñߵ�ÿ�����
				if (*it_H_E != hei)
				{
					cout << H_E_L[*it_H_E - 1].Half_F() << ", ";
					break;
				}
			}
		}
		cout << endl;
	}
}

void Show_Half_Edge_List(vector<HalfEdge> H_E_L)
{//���ģ�͵İ�߱�
	vector<HalfEdge>::iterator it_h_e_l;
	for (it_h_e_l = H_E_L.begin(); it_h_e_l != H_E_L.end(); it_h_e_l++)
	{
		cout << "#" << it_h_e_l->HE_ID() << "  ";
		cout << it_h_e_l->Half_P() << endl;
	}
}

void Write_Data(Model& MyModel)
{
	vector<Point_3>& P_L = MyModel.point();
	vector<Face_Tri>& F_L = MyModel.face();
	ofstream outfile;
	outfile.open("123.face",ios::out);
	vector<Point_3>::iterator itp;
	//outfile << "Coordinates\n";
	outfile << "OFF\n";
	outfile << P_L.size() << "  " << P_L.size() << "  " << "0\n\n";
	for (itp = P_L.begin(); itp != P_L.end(); itp++)
	{
		outfile << *itp << endl;
	}
	//outfile << "end coordinates\n\n";
	vector<Face_Tri>::iterator itt;
	//outfile << "Elements\n";
	for (itt = F_L.begin(); itt != F_L.end(); itt++)
		outfile << *itt << endl;
	outfile << endl;
	//outfile << "end elements\n";
	outfile.close();
	std::cout << "����д�����...\n";
}

void Write_Data_F(Model& MyModel)
{
	vector<Point_3>& P_L = MyModel.point();
	vector<Edge>& E_L = MyModel.edge();
	ofstream outfile;
	outfile.open("123.edge",ios::out);
	vector<Edge>::iterator ite;
	for (ite = E_L.begin(); ite != E_L.end(); ite++)
	{
		if (ite->Feature() != 0)
		{//��������ߵ������˵�
			int NA = ite->P0();
			int NB = ite->P1();
			outfile << P_L[NA - 1] << endl;
			outfile << P_L[NB - 1] << endl;
		}
	}
	outfile.close();
}