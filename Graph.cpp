#include "Graph.h"
using namespace std;
//
// ���������� ��������� ������� ���� 
//

int WinW = 1080;		             
int WinH = 780;			              

bool* Mouse_Vert = new bool[maxSize];     //������ ����� (������ � ���� ������� ��� ���)
bool standView = false;		              //�������� �� ������������ ����� � ����������� ��� (��� ������� ����������� �� �����)
bool Vert_Move = false;		              //�������� �� ����������� ������ 


int R;                                    //������ ������ �����
int Button_Flag;                          //���� ������ � ���� ������, ��������� �������� ������ ������ (��������� ������ ��� ���������)
int Moving_Vertex;				          //����� ������������ �������
int CursorX;		                      //������� ������� �� �
int CursorY;                              //������� ������� �� �

vertCoord vertC[maxSize + 2];	          //������ �������� (���������� ������), +2 ����� �� �������� ����., ��� ���������� �� maxSize
Graph graph; 

vector<pair<int, int>> Way;
vector<int> New_Way;



Graph::Graph()                            //�����������, ���������� ������� ��������� 0 � ����� Mouse_Vert 		                      
{
	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++)
		{
			adjMatrix[i][j] = 0;
		}
		Mouse_Vert[i] = false;
	}
}

Graph::~Graph()                           //����������
{ }

int Graph::GetVertPos(const int& vertex)  //��������� ������ ������� � ������� ������
{
	for (size_t i = 0; i < vertList.size(); i++)
	{
		if (vertList[i] == vertex)
			return i;
	}
	return -1;
}

bool Graph::IsEmpty()                     //�������� �� �������
{
	if (vertList.size() != 0)
		return false;
	else
		return true;		
}

bool Graph::IsFull()                      //�������� �� ������� 
{
	return (vertList.size() == maxSize);
}

void Graph::InsertVertex(const int& vertex) //���������� ����� ������� 
{
	if (!IsFull())
		vertList.push_back(vertex);
	else
	{
		cout << "���� ��� ��������. ���������� �������� ����� ������� " << endl;
		return;
	}
}

void Graph::InsertEdge(const int& vertex1, const int& vertex2, int weight)              //���������� ������ �����
{
	if (weight < 1)
	{
		cout << "\n������ �������� ���� �����������\n";
		return;
	}
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))						//���� ������� ���� � �����
	{
		int vertPos1 = GetVertPos(vertex1);												//������� ������� ������
		int vertPos2 = GetVertPos(vertex2);
		if (adjMatrix[vertPos1][vertPos2] != 0 && adjMatrix[vertPos2][vertPos1] != 0)	//���� ����� ���� ��� ���� �����
		{
			cout << "����� ����� ��������� ��� ����" << endl;
			return;
		}
		else																			//����� ��������� �����
		{
			adjMatrix[vertPos1][vertPos2] = weight;
		}
	}
	else
	{
		cout << "����� ������ (��� ����� �� ���) ��� � ����� " << endl;
		return;
	}
}

void Graph::Print()                                                                     //����� ������� ��������� �� �����
{
	if (!IsEmpty())
	{
		cout << "������� ��������� �����: " << endl;
		for (int i = 0; i < vertList.size(); i++)
		{
			cout << vertList[i] << " ";
			for (int j = 0; j < vertList.size(); j++)
				cout << setw(4) << adjMatrix[i][j];
			cout << endl;
		}
	}
	else
		cout << "\n���� ����\n" << endl;
}

void Graph::EraseLastVert()                                                             //�������� ��������� ������� 
{
	if (IsEmpty())
	{
		cout << "\n���� ����\n";
		return;
	}
	int n = vertList.size();
	for (int j = 0; j < n; j++)
	{
		adjMatrix[n - 1][j] = 0;
		adjMatrix[j][n - 1] = 0;
	}

	vertList.pop_back();
}

void Graph::EraseEdge(const int& vertex1, const int& vertex2)                           //�������� �����
{
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))						//���� ��� ������� ���� � �����
	{
		int vertPos1 = GetVertPos(vertex1);												//������� ������� ������
		int vertPos2 = GetVertPos(vertex2);
		if (adjMatrix[vertPos1][vertPos2] == 0)	                                        //���� ����� ��������� ����� ���
		{
			cout << "����� ����� ������� ��������� ���\n" << endl;
			return;
		}
		else																			//����� ������� ����� (�������� ��������������� ������ � ������� ���������)
		{
			adjMatrix[vertPos1][vertPos2] = 0;
		}
	}
	else                                                                                //���� ���� �� ����� ������� � ����� ���
	{
		cout << "����� ������ (��� ����� �� ���) ��� � ����� " << endl;
		return;
	}
}

int Graph::GetAmountEdges()                                                             //��������� ���������� ����� � �����
{
	int numb = 0;
	for (int i = 0; i < vertList.size(); i++)
	{
		for (int j = 0; j < vertList.size(); j++)
		{
			if (adjMatrix[i][j] > 0)
			{
				numb++;
			}
		}
	}
	return numb;
}

void Graph::DrawGraph()                                                                 //��������� �����
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		if (!standView)
			setCoords(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0)
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
			if (a == adjMatrix[j][i] && a != 0)
				drawLine(a, vertC[j].x, vertC[j].y, vertC[i].x, vertC[i].y);
		}
	}
	drawVertex(n);
	glutPostRedisplay();
}

int** Change_Matrix()	
{
	int n = graph.GetAmountVerts();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int elem = graph.GetAdjMatrixElem(i, j);
			if (elem == 0 or i == j)		
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}
	}
	cout << "��������� �������: \n";
	Print_Matrix(matrix);
	return matrix;
}

int* Search_MinElem(int* line, int n)	
{
	int min = 1000000;
	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];
	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;
	return line;
}

void Print_Matrix(int** matrix)		
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << matrix[i][j];
		cout << endl;
	}
}

int** Reduct_Matrix(int** oldmatrix)		
{
	int** matrix = oldmatrix;
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
		matrix[i] = Search_MinElem(matrix[i], n);
	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];
		}
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0)
				matrix[j][i] -= min;
		}
	}
	cout << "\n�������������� �������: \n";
	Print_Matrix(matrix);
	return matrix;
}

int** High_Zero(int** oldmatrix)
{
	int n = graph.GetAmountVerts();
	int** matrix = Reduct_Matrix(oldmatrix);
	int max = -1;
	int line, column;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];
				}
				for (int k = 0; k < n; k++)
				{
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];
				}
				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}
	}

	pair<int, int> p;
	p.first = line + 1;
	p.second = column + 1;
	Way.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}
	cout << endl;
	cout << "������� ����� �������� 0 � ���������� �������: \n";
	Print_Matrix(matrix);
	cout << "\n������������� ������� �����: ";
	for (int i = 0; i < Way.size(); i++)
		cout << Way[i].first << " -> " << Way[i].second << "   ";
	cout << endl;
	return matrix;
}

void Print_Result()
{
	int second = Way[0].second;
	int i = 2;
	New_Way.push_back(Way[0].first);
	New_Way.push_back(Way[0].second);
	while (i != graph.GetAmountVerts() + 1)
		for (int j = 1; j < graph.GetAmountVerts(); j++)
			if (Way[j].first == second)
			{
				second = Way[j].second;
				New_Way.push_back(second);
				i++;
			}
	cout << "�����: ";
	for (int i = 0; i < New_Way.size(); i++)
	{
		cout << New_Way[i];
		if (i != New_Way.size() - 1)
			cout << " -> ";
	}
	int sum = 0;
	for (int i = 0; i < Way.size(); i++)
	{
		int line = Way[i].first - 1;
		int column = Way[i].second - 1;
		sum += graph.GetAdjMatrixElem(line, column);
	}
	cout << "\nS = " << sum << endl;;
}
//
// ���������� ������� ��������� ������ 
//
void drawButton1() 
{
	system("chcp 1251>nul");
	if (Button_Flag == 1)
	{
		glColor3f(255,0,0);
	
	}
	else
	glColor3f(0,0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 20);
	glVertex2i(50, WinH - WinH / 7);
	glVertex2i(WinW / 7, WinH - WinH / 7);
	glVertex2i(WinW / 7, WinH - 20);
	glEnd();
	glColor3f(192, 192, 192);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 20);
	glVertex2i(50, WinH - WinH / 7);
	glVertex2i(WinW / 7, WinH - WinH / 7);
	glVertex2i(WinW / 7, WinH - 20);
	glEnd();
	string name = "�";
	string name1 = "CIRCULAR VIEW ";
	glRasterPos2i(WinW / 21, 0.92 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
	glRasterPos2i(WinW / 18, (0.92 * WinH) - 15);
	for (int i = 0; i < name1.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name1[i]);
}
void drawButton2()
{
	if (Button_Flag == 2){

		glColor3f(255, 0, 0);

}
	else
	glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - WinH / 7 - 20);
	glVertex2i(50, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - WinH / 7 - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - WinH / 7 - 20);
	glVertex2i(50, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - WinH / 7 - 20);
	glEnd();
	string name = "\"SALESMAN\" TASK";
	glRasterPos2i(WinW / 19, 0.77 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
}
void drawButton3()
{
	if (Button_Flag == 3){

		glColor3f(255, 0, 0);

}
	else
	glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 2 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 3 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7) - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 2 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 3 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7) - 20);
	glEnd();
	string name = "PRINT MATRIX";
	string name1 = "IN CONSOLE";
	glRasterPos2i(WinW / 16.5, 0.63 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
	glRasterPos2i(WinW / 16, (0.63 * WinH) - 15);
	for (int i = 0; i < name1.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name1[i]);
}
void drawButton4()
{
	if (Button_Flag == 4)
	{
		glColor3f(255, 0, 0);

}
	else
	glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 3 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 4 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 7) - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 3 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 4 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 7) - 20);
	glEnd();
	string name = "ADD VERTEX";
	glRasterPos2i(WinW / 16, 0.48 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);

}
void drawButton5()
{
	if (Button_Flag == 5){
		glColor3f(255, 0, 0);

}
	else
	glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 4 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 5 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 7) - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 4 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 5 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 7) - 20);
	glEnd();
	string name = "DELETE VERTEX";
	glRasterPos2i(WinW / 17, 0.34 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
}
void drawButton6()
{
	if (Button_Flag == 6)
	{
		glColor3f(255, 0, 0);

}
	else
	glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 5 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 6 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 7) - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 5 * (WinH / 7) - 20);
	glVertex2i(50, WinH - 6 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 7) - 20);
	glEnd();
	string name = "ADD EDGE";
	glRasterPos2i(WinW / 14.8, 0.2 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
}
void drawButton7()
{
	if (Button_Flag == 7)
	{
		glColor3f(255, 0, 0);

	}
	else
		glColor3f(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - 6 * (WinH / 7) - 20);
	glVertex2i(50, 10);
	glVertex2i(WinW / 7, 10);
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 7) - 20);
	glEnd();
	glColor3f(192, 192, 192);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - 6 * (WinH / 7) - 20);
	glVertex2i(50, 10);
	glVertex2i(WinW / 7, 10);
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 7) - 20);
	glEnd();
	string name = "DELETE EDGE";
	glRasterPos2i(WinW / 16, 0.061 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
}

void drawCircle(int x, int y, int R)            //��������� �������� ����� (������ �� � ���� �������)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}
void drawBorderedCircle(int x, int y, int R)   //��������� ����� ������ ������ (������ � ���� �������)
{
	glColor3f(0.565, 0.933, 0.565);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();
	glColor3f(0.0, 0.392, 0.0);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int text, int x1, int y1)		            //��������� ���� ����� / �������� �������
{
	glColor3f(0.0, 0.0, 0.0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(text);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawLine(int text, int x0, int y0, int x1, int y1) //��������� ����� ���������������� ����������� �����
{
	glColor3i(0, 0, 0); 
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + R * vx;
	y1 = y1 + R * vy;

	glColor3i(0, 0, 0); 
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}

void drawVertex(int n)		                           //��������� ������� (���� + ��������)
{
	for (int i = 0; i < n; i++)
	{
		if (Mouse_Vert[i])
			drawBorderedCircle(vertC[i].x, vertC[i].y, R);
		else
			drawCircle(vertC[i].x, vertC[i].y, R);
		drawText(i + 1, vertC[i].x, vertC[i].y);
	}

}

void setCoords(int i, int n)			               //����������� ��������� ������ �� ����� ������� R_ � ��������� ������� ������ R
{
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else
	{
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * i / n;
	int y1 = R_ * cos(theta) + y0;
	int x1 = R_ * sin(theta) + x0;
	vertC[i].x = x1;
	vertC[i].y = y1;
}

void makeGraph()	                                  //�������� ����� 
{
	standView = false;
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight;
	cout << "������� ���������� ������ � �����: "; cin >> amountVerts;
	cout << "������� ���������� ����� � �����: "; cin >> amountEdges;
	for (int i = 1; i <= amountVerts; i++) {

		graph.InsertVertex(i);
	}
	for (int i = 0; i < amountEdges; i++)
	{
		cout << "�������� �������: "; cin >> sourceVertex;
		cout << "�������� �������: "; cin >> targetVertex;
		cout << "��� �����: "; cin >> edgeWeight;
		graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
	}
	cout << endl;
	graph.Print();
}

bool Salesman_Check(int** matrix)                   //��������: ��������� �� ������ ������������
{
	if (graph.IsEmpty())
		return false;
	for (int i = 0; i < graph.GetAmountVerts(); i++)
	{
		int cnt = 0;
		for (int j = 0; j < graph.GetAmountVerts(); j++)
		{
			if (matrix[i][j] > 0)
				cnt++;
		}
		if (cnt < 1)
			return false;
	}
	return true;
}

int Circle_Check(int x, int y)                     //��������: ������ � ���� ������� ��� ���
{
	for (int i = 0; i < graph.GetAmountVerts(); i++)
		if (pow(x - vertC[i].x, 2) + pow(y - vertC[i].y, 2) <= pow(R, 2))
			return i;
	return -1;
}

void Button_Check(int x, int y)                    //��������: ������ � ���� ������ ��� ���
{
	if (x > 50 && x < WinW / 7 && y < (WinH - 20) && y > (WinH - WinH / 7))
		Button_Flag = 1;
	else if (x > 50 && x < WinW / 7 && y < (WinH - WinH / 7 - 20) && y > WinH - 2 * (WinH / 7))
		Button_Flag = 2;
	else if (x > 50 && x < WinW / 7 && y < WinH - 2 * (WinH / 7) - 20 && y > WinH - 3 * (WinH / 7))
		Button_Flag = 3;
	else if (x > 50  && x < WinW / 7 && y > WinH - 4 * (WinH / 7) && y < WinH - 3 * (WinH / 7) - 20)
		Button_Flag = 4;
	else if (x > 50  && x < WinW / 7 && y > WinH - 5 * (WinH / 7) && y < WinH - 4 * (WinH / 7) - 20)
		Button_Flag = 5;
	else if (x > 50 && x < WinW / 7 && y > WinH - 6 * (WinH / 7) && y < WinH - 5 * (WinH / 7) - 20)
		Button_Flag = 6;
	else if (x > 50 && x < WinW / 7 && y > 10 && y < WinH - 6 * (WinH / 7) - 20)
		Button_Flag = 7;
	else
		Button_Flag = 0;
}

void mouseMove(int x, int y)                      //������������ �������� ������� � ����������� ������� �������
{
	y = WinH - y;
	CursorX = x;
	CursorY = y;
	int i = Circle_Check(x, y);
	if (i != -1)
		Mouse_Vert[i] = true;
	else
		for (int j = 0; j < graph.GetAmountVerts(); j++)
			Mouse_Vert[j] = false;
	if (Vert_Move)
	{
		vertC[Moving_Vertex].x = CursorX;
		vertC[Moving_Vertex].y = CursorY;
	}
	Button_Check(x, y);
	glutPostRedisplay();
}

void drawRadius()                                    //��������� �������� ������� ������ � ���� 
{
	int Rad = 0;
	if (graph.GetAmountVerts() != 0)
		Rad = R;
	int space = 24;
	string r = "RADIUS = " + to_string(Rad);
	glRasterPos2i((WinW / 7) + 50, WinH - 50);
	for (int i = 0; i < r.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r[i]);
}

void mouseClick(int button, int state, int x, int y) //����������� ������� ����
{
	int j = Circle_Check(x, WinH - y);
	if (Vert_Move)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			Vert_Move = false;
			return;
		}
	}

	if (j != -1)
	{
		standView = true;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			Vert_Move = true;
			Moving_Vertex = j;
			return;
		}
	}

	if (button == 3 || button == 4)
	{
		standView = true;
		if (button == 3)
		{
			if (R != 300)
				R++;
		}
		else if (button == 4)
		{
			if (R != 15)
				R--;
		}
	}

	if (x >= 50 and x <= (WinW / 7) and y >= 20 and y <= (WinH / 7))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			New_Way.clear();
			Way.clear();
			Graph New;
			graph = New;
			makeGraph();
			return;

		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			standView = false;
			return;
		}
	}
	if (x >= 50 and x <= (WinW / 7) and y >= ((WinH / 7) + 20) and y <= 2 * (WinH / 7))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			New_Way.clear();
			Way.clear();
			cout << "\n������ ������������:\n";
			int** matrix = Change_Matrix();
			bool checker = Salesman_Check(matrix);
			if (!checker)
			{
				cout << "\n������ ������������ ��� ������� ����� �����������\n\n";
				return;
			}
			int n = graph.GetAmountVerts();
			while (Way.size() < n)
				matrix = High_Zero(matrix);
			cout << endl;
			Print_Result();
			return;
		}
	}
	if (x >= 50 and x <= (WinW / 7) and y >= (2 * (WinH / 7) + 20) and y <= 3 * (WinH / 7))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			graph.Print();
			return;
		}
	}
	if (x >= 50 && x <= WinW / 7 && y <= 4 * (WinH / 7) && y >= 3 * (WinH / 7) + 20)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int cur = graph.GetAmountVerts();
			graph.InsertVertex(cur + 1);
			vertC[cur].x = WinW / 2;
			vertC[cur].y = WinH / 2;
			return;
		}

	}
	if (x >= 50 && x <= WinW / 7 && y <= 5 * (WinH / 7) && y >= 4 * (WinH / 7) + 20)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			graph.EraseLastVert();
			int cur = graph.GetAmountVerts();
			return;
		}
	}
	if (x >= 50 && x <= WinW / 7 && y <= 6 * (WinH / 7) && y >= 5 * (WinH / 7) + 20)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex, edgeWeight, vertNum;
			cout << "���������� ����������� �����: "; cin >> vertNum;
			for (int i = 0; i < vertNum; i++)
			{
				cout << "�������� �������: "; cin >> sourceVertex;
				cout << "�������� �������: "; cin >> targetVertex;
				cout << "��� �����: "; cin >> edgeWeight;
				graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
			}
			return;
		}
	}
	if (x > 50 && x < WinW / 7 && y <= WinH - 10 && y >= 6 * (WinH / 7) + 20)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex;
			cout << "�������� �������: "; cin >> sourceVertex;
			cout << "�������� �������: "; cin >> targetVertex;
			graph.EraseEdge(sourceVertex, targetVertex);
			return;
		}

	}
}

void reshape(int w, int h)	
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawButton1();
	drawButton2();
	drawButton3();
	drawButton4();
	drawButton5();
	drawButton6();
	drawButton7();
	graph.DrawGraph();
	drawRadius();
	glutSwapBuffers();
}