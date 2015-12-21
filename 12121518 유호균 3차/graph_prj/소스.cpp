/* ���ѻ���
(1) �л��� �ִ� 100���� �Էµȴ�.
(2) ���δ� �ִ� 4,950���� �Էµȴ�.
(3) ���Ǵ� �ִ� 10,000���� �Էµȴ�.
*/

/*���
1.�л� �߰�
2.�л����� ���
3.���� �߰�
4.�л� ����
5.���� ����
6.����� ���� ���
7.�������� ���1
8.�������� ���2
9.�������� ���� Ȯ��
*/

#include <iostream> //ǥ�������
#include <fstream>  //file stream ���� �Է�
#include <sstream>  //string stream split by space ���Ϸκ��� ������ ���پ� �Է��ϱ�����
#include <stdlib.h> //system("cls") �ܼ�â �����
#include <string>   //string ���

using namespace std;

struct road;                    //���� ����ü
struct student;                 //�л� ����ü
struct student_sequence_node;   //�л� ������ ����ü
struct road_sequence_node;      //���� ������ ����ü
struct para_sequence_node;      //�Ű� ������ ����ü

struct road{                                                //road struct
	para_sequence_node* pointer_first_para_node = NULL;     //ù��° �Ű������� ����Ű�� ������
	para_sequence_node* pointer_second_para_node = NULL;    //�ι�° �Ű������� ����Ű�� ������
	road_sequence_node* pointer_road_sequence_node = NULL;  //���� �������� ����Ŵ
	int road_id = NULL;                                     //���� ��ȣ
	int first_student_id = 0;                               //���ο� ����� �л�1
	int second_student_id = 0;                              //���ο� ����� �л�2
};

struct student{                                             //student struct
	student_sequence_node* pointer_student_node = NULL;     //�л� ������ ������
	para_sequence_node* pointer_para_node = NULL;           //�Ű� ������ ������
	int student_id = 0;                                     //�й�
	int degree = 0;                                         //degree ����
	string email = "";                                      //email �ּ�
};

struct student_sequence_node {                              //student sequence
	student_sequence_node *previous = NULL;                 //���� �л� ������
	student_sequence_node *next = NULL;                     //���� �л� ������
	student *point_student = NULL;                          //�л� ������
};


struct para_sequence_node{                                  //student struct�� road struct �Ű�
	para_sequence_node* next = NULL;                        //���� �Ű� ������
	para_sequence_node* previous = NULL;                    //���� �Ű� ������
	road *point_road = NULL;                                //���� ������
};

struct road_sequence_node{                                  //���� ������
	road_sequence_node *previous = NULL;                    //���� ����
	road_sequence_node *next = NULL;                        //���� ����
	road *pointer_road = NULL;                              //���� ������
};

class location_graph{                                       //Graph Class
private:
	road_sequence_node *first_road = NULL;                  //���� ����Ʈ(������)
	//para_sequence_node *first_para = NULL;                //�Ű����� ����Ʈ(������)
	student_sequence_node *first_student = NULL;            //�л� ����Ʈ(������)

	int total_student;                                      //��ü �л���
	int total_road;                                         //��ü ���μ�

public:
	location_graph(int, int);                               //������
	~location_graph();                                      //�Ҹ���
	void insert_student(int, string);                       //1.�л� �߰�
	void print_student(int);                                //2.�л����� ���
	void insert_road(int, int, int);                        //3.���� �߰�
	void remove_student(int);                               //4.�л� ����
	void remove_road(int);                                  //5.���� ����
	void print_incident_road(int);                          //6.����� �������� ��� INCIDENT
	void print_road_info(int);                              //7.�������� ���1
	void print_available_incident(int, int);                //8.�������� ���2
	void print_adjacent_student(int, int);                  //9. �������� ���� Ȯ��
	student_sequence_node* search_stduent_by_id(int);       //�й����� �л���������� ã��
	road_sequence_node* search_road_by_id(int);             //�й����� ���ν�������� ã��

};

location_graph::location_graph(int _student_size, int _road_size){ //������
	total_student = 0;                                             //��� ���� �ʱ�ȭ
	total_road = 0;
}
location_graph::~location_graph(){                                 //�Ҹ���

}

student_sequence_node* location_graph::search_stduent_by_id(int _id) //�й����� �л���������� ã��
{
	bool found = false;
	student_sequence_node* temp_student_sequence_node = this->first_student; //ó���� ó����������
	while (temp_student_sequence_node != NULL){         //�������� üũ �� �ϰ� �Ѿ
		if (temp_student_sequence_node->point_student->student_id == _id){
			found = true;
			break;
		}
		else
			temp_student_sequence_node = temp_student_sequence_node->next;
	}
	//�� �˻��ϰ�
	if (found == false) //�� ã����
		temp_student_sequence_node = NULL; //NULL�� ����

	return temp_student_sequence_node;//��ȯ
}

road_sequence_node* location_graph::search_road_by_id(int _id){ //�й����� ���ν�������� ã��
	bool found = false;
	road_sequence_node* temp_road_sequence_node = this->first_road; //ó���� ó�� ��������
	while (temp_road_sequence_node != NULL){ //�������� üũ �� �ϰ� �Ѿ
		if (temp_road_sequence_node->pointer_road->road_id == _id){
			found = true;
			break;
		}
		else
			temp_road_sequence_node = temp_road_sequence_node->next;
	}
	//�� �˻��ϰ�
	if (found == false) //��ã����
		temp_road_sequence_node = NULL;

	return temp_road_sequence_node;//��ȯ
}

void location_graph::insert_student(int _id, string _email){ //1.�л� �߰�
	student *new_student = new student; //�л� ��� ����
	student_sequence_node *new_student_sequence_node = new student_sequence_node; //�л�������������

	//�л� struct ����, �ʱ�ȭ
	new_student->degree = 0;
	new_student->email = _email;
	new_student->student_id = _id;
	new_student->pointer_student_node = new_student_sequence_node;

	//�л� sequence ����, �ʱ�ȭ
	new_student_sequence_node->next = NULL;
	new_student_sequence_node->previous = NULL;
	new_student_sequence_node->point_student = new_student;

	if (this->first_student == NULL) //ó�� �л��� ������ ó���л����� ����
		this->first_student = new_student_sequence_node;

	else{ //ó�� ������ �л��� ������
		student_sequence_node* temp_pointer_student_node = this->first_student;
		while (temp_pointer_student_node->next != NULL){//while ���鼭 ���� ã��
			temp_pointer_student_node = temp_pointer_student_node->next;
		}
		//�������� �ֱ�
		temp_pointer_student_node->next = new_student_sequence_node;
		new_student_sequence_node->previous = temp_pointer_student_node;
	}

	this->total_student++;
	cout << this->total_student << endl;
}
void location_graph::print_student(int _id){ //2.�л����� ���
	student_sequence_node* temp_student_node = this->search_stduent_by_id(_id);//Ž��
	if (temp_student_node != NULL){ //������
		string email = temp_student_node->point_student->email;
		int degree = temp_student_node->point_student->degree;
		cout << email << " " << degree << endl; // ����� ������ ��
	}
	else//������
		cout << "Not Found" << endl;


}
void location_graph::insert_road(int _road_id, int _first_student_id, int _second_student_id){
	//3.���� �߰�

	student_sequence_node* temp_first_student_node = this->search_stduent_by_id(_first_student_id);
	student_sequence_node* temp_second_student_node = this->search_stduent_by_id(_second_student_id);
	// id�� �ִ��� ������ �˻�
	if (temp_first_student_node != NULL && temp_second_student_node != NULL)//ã��
	{
		//���� struct ����, ��� �ʱ�ȭ
		road *new_road = new road;
		new_road->first_student_id = _first_student_id;
		new_road->second_student_id = _second_student_id;
		new_road->road_id = _road_id;

		//���� sequence ����, ��� �ʱ�ȭ
		road_sequence_node *new_road_sequence_node = new road_sequence_node;
		new_road->pointer_road_sequence_node = new_road_sequence_node;
		new_road_sequence_node->next = NULL;
		new_road_sequence_node->previous = NULL;

		//���� ������ ����
		//ù�ε尡 ������ ù�ε�� ����
		if (this->first_road == NULL){
			this->first_road = new_road_sequence_node;
			this->first_road->pointer_road = new_road;
		}
		else //ù�ε尡 ������ �������ε忡 ������ ����
		{
			road_sequence_node* temp_road_sequence_node = this->first_road;
			while (temp_road_sequence_node->next != NULL) //while���鼭 ������ Ž��
				temp_road_sequence_node = temp_road_sequence_node->next;
			temp_road_sequence_node->next = new_road_sequence_node;
			new_road_sequence_node->previous = temp_road_sequence_node;
			new_road_sequence_node->pointer_road = new_road;
		}

		//�� �ϳ��� �Ű� sequence 2���ʿ�
		//�Ű� sequence1 ����, ��� �ʱ�ȭ
		para_sequence_node *new_para_sequence_node1 = new para_sequence_node;
		new_para_sequence_node1->point_road = new_road;
		new_para_sequence_node1->next = NULL;
		new_para_sequence_node1->previous = NULL;

		//�Ű� sequence2 ����, ��� �ʱ�ȭ
		para_sequence_node *new_para_sequence_node2 = new para_sequence_node;
		new_para_sequence_node2->point_road = new_road;
		new_para_sequence_node2->next = NULL;
		new_para_sequence_node2->previous = NULL;


		//���ΰ� �Ű������� ����Ű����
		//ó�� ����Ű�� �Ű��������� ����
		if (temp_first_student_node->point_student->pointer_para_node == NULL)
			temp_first_student_node->point_student->pointer_para_node = new_para_sequence_node1;
		else //ó�� ����Ű�� �Ű��������� ������ ���������ٰ� ����
		{
			para_sequence_node *temp_para_sequence_node = temp_first_student_node->point_student->pointer_para_node;
			while (temp_para_sequence_node->next != NULL) //�Ű������� �������� ã�Ƽ�
			{
				temp_para_sequence_node = temp_para_sequence_node->next;
			}
			//�Ű� ������ ����
			temp_para_sequence_node->next = new_para_sequence_node1;
			new_para_sequence_node1->previous = temp_para_sequence_node;
		}


		//���� ���� ����
		if (temp_second_student_node->point_student->pointer_para_node == NULL)
			temp_second_student_node->point_student->pointer_para_node = new_para_sequence_node2;
		else{
			para_sequence_node* temp_para_sequence_node = temp_second_student_node->point_student->pointer_para_node;
			while (temp_para_sequence_node->next != NULL)
			{
				temp_para_sequence_node = temp_para_sequence_node->next;
			}
			//�Ű� ������ ����
			temp_para_sequence_node->next = new_para_sequence_node2;
			new_para_sequence_node2->previous = temp_para_sequence_node;
		}



		temp_first_student_node->point_student->degree++; //degree����
		temp_second_student_node->point_student->degree++; //degree����

		//���ΰ� �Ű������� ����Ű���� ����
		new_road->pointer_first_para_node = new_para_sequence_node1;
		new_road->pointer_second_para_node = new_para_sequence_node2;

		this->total_road++;
		cout << this->total_road << endl;
	}
	else
		cout << this->total_road << " Not Found" << endl;
	//���λ���, �Ű������� ���� ��


}
void location_graph::remove_student(int _student_id){ //4.�л� ���� (���л��� ���μ� ���)
	student_sequence_node* temp_student_sequence_node = this->search_stduent_by_id(_student_id);
	//�л� id�� search
	if (temp_student_sequence_node != NULL){ //������ �л��� �����ϸ�
		student* temp_student_node = temp_student_sequence_node->point_student;
		//�л���尡 �Ķ���� ��带 �� ���� ��쵵 ����
		if (temp_student_node->pointer_para_node != NULL){ //�л��� �Ű� �������� ������
			para_sequence_node* temp_para_sequence_node = temp_student_node->pointer_para_node;
			//����� ���� ����
			while (temp_para_sequence_node != NULL){ //���λ��� �ݺ��� ����
				//����, �Ű������� ���� ���� (remove_road�� ����մϴ�) ������ remove_road�� ����
				temp_para_sequence_node = temp_student_node->pointer_para_node;
				road_sequence_node* temp_road_sequence_node = this->search_road_by_id(temp_para_sequence_node->point_road->road_id);
				if (temp_road_sequence_node != NULL){ //���� ã��

					road* temp_road_node = temp_road_sequence_node->pointer_road;
					para_sequence_node* temp_para_sequence_node1 = temp_road_node->pointer_first_para_node;
					para_sequence_node* temp_para_sequence_node2 = temp_road_node->pointer_second_para_node;
					student_sequence_node* temp_stduent_sequence_node1 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->first_student_id);
					student_sequence_node* temp_stduent_sequence_node2 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->second_student_id);

					temp_stduent_sequence_node1->point_student->degree--;
					temp_stduent_sequence_node2->point_student->degree--;
					temp_para_sequence_node1->point_road = NULL;
					temp_para_sequence_node2->point_road = NULL;
					if (temp_road_sequence_node->next != NULL) // road ������ ���
					{
						if (temp_road_sequence_node->previous != NULL){
							temp_road_sequence_node->previous->next = temp_road_sequence_node->next;
							temp_road_sequence_node->next->previous = temp_road_sequence_node->previous;
						}
						else{ //road ������ ������ �ְ�, ������ ���� -> ù �ε� ����
							temp_road_sequence_node->next->previous = NULL;
							this->first_road = temp_road_sequence_node->next;
						}

					}
					else{ //road ������ ����� ������ NULL next == NULL,
						if (temp_road_sequence_node->previous != NULL)
							temp_road_sequence_node->previous->next = NULL;
					}

					//para ������ �����۾�
					//para1 ������ ���
					if (temp_para_sequence_node1->next != NULL){
						if (temp_para_sequence_node1->previous != NULL){
							temp_para_sequence_node1->previous->next = temp_para_sequence_node1->next;
							temp_para_sequence_node1->next->previous = temp_para_sequence_node1->previous;
						}
						else{//para�������� ������ �ְ� ������ ����
							temp_para_sequence_node1->next->previous = NULL;
							temp_stduent_sequence_node1->point_student->pointer_para_node = temp_para_sequence_node1->next;
						}
					}
					else{ //para �������� ������ ����
						if (temp_para_sequence_node1->previous != NULL)
							temp_para_sequence_node1->previous->next = NULL;
					}

					//para2 ������ ���
					if (temp_para_sequence_node2->next != NULL){
						if (temp_para_sequence_node2->previous != NULL){
							temp_para_sequence_node2->previous->next = temp_para_sequence_node2->next;
							temp_para_sequence_node2->next->previous = temp_para_sequence_node2->previous;
						}
						else{//para�������� ������ �ְ� ������ ����
							temp_para_sequence_node2->next->previous = NULL;
							temp_stduent_sequence_node2->point_student->pointer_para_node = temp_para_sequence_node2
								->next;
						}
					}
					else{ //para �������� ������ ����
						if (temp_para_sequence_node2->previous != NULL)
							temp_para_sequence_node2->previous->next = NULL;
					}


					//road��������road ����Ű�°� ����
					temp_road_sequence_node->pointer_road = NULL;
					//road�� road������ ����Ű�°� ����
					temp_road_node->pointer_road_sequence_node = NULL;
					//para�������� road����Ű�°� ����
					temp_para_sequence_node1->point_road = NULL;//para ������ -> road �� NULL ����Ŵ
					temp_para_sequence_node2->point_road = NULL;
					//road�� student����Ű�°� ����
					temp_road_node->first_student_id = NULL;
					temp_road_node->second_student_id = NULL;
					//road�� para������ ����Ű�°� ����
					temp_road_node->pointer_first_para_node = NULL;
					temp_road_node->pointer_second_para_node = NULL;
					//�Ű� ������ ����
					temp_para_sequence_node1 = NULL;
					temp_para_sequence_node2 = NULL;
					//���� ��� ����
					temp_road_node = NULL;
					//���� ������ ��� ����
					temp_road_sequence_node = NULL;
				}//���� �Ű������� �����κ� ��
				this->total_road--;
				if (temp_student_node->pointer_para_node->point_road == NULL) //�Ű������� ��������鳡
					break;
				//�� ���μ� ����
				//temp_para_sequence_node = temp_para_sequence_node -> next; // ���� �Ű��������� �̵�
			} //���λ��� �ݺ��� ��
		}
		else//�л��� �Ű��������� ����
		{
			//�ƹ��ϵ� ����
		}


		//�л� ������ ����
		if (temp_student_sequence_node->next != NULL){
			if (temp_student_sequence_node->previous != NULL){//�л������� ������ �ְ� ������ ����
				temp_student_sequence_node->previous->next = temp_student_sequence_node->next;
				temp_student_sequence_node->next->previous = temp_student_sequence_node->previous;
			}
			else{//�л� �������� ������ �ְ� ������ ���� => ù �л��� �����Ѱ�
				temp_student_sequence_node->next->previous = NULL;
				this->first_student = temp_student_sequence_node->next;
			}
		}
		else{ //�л� �������� ������ ����
			if (temp_student_sequence_node->previous != NULL)//���������� ������ ����
				temp_student_sequence_node->previous->next = NULL;
		}

		//�л� ������ ����
		temp_student_sequence_node = NULL;
		//�л� ��� ����
		temp_student_node = NULL;
		//�� �л��� ����
		this->total_student--;

		cout << this->total_student << " " << this->total_road << endl;

	} //������ �л� ���� ���ǹ� ��
	else{
		cout << this->total_student << " " << this->total_road << " Not found" << endl; //������ �л� ���� X
	}

}
void location_graph::remove_road(int _road_id){ //5.���� ����
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);


	if (temp_road_sequence_node != NULL){ //���� ã��

		road* temp_road_node = temp_road_sequence_node->pointer_road;
		para_sequence_node* temp_para_sequence_node1 = temp_road_node->pointer_first_para_node;
		para_sequence_node* temp_para_sequence_node2 = temp_road_node->pointer_second_para_node;
		student_sequence_node* temp_stduent_sequence_node1 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->first_student_id);
		student_sequence_node* temp_stduent_sequence_node2 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->second_student_id);

		/*
		���� �ӽ� ���� ���, �ӽ� �Ű� ������ 1,2 , �ӽ� �л� ������ 1,2
		*/

		//degree ����
		temp_stduent_sequence_node1->point_student->degree--;
		temp_stduent_sequence_node2->point_student->degree--;

		//�Ű� �������� ���� NULL����Ű����
		temp_para_sequence_node1->point_road = NULL;
		temp_para_sequence_node2->point_road = NULL;
		//road ������ ���
		if (temp_road_sequence_node->next != NULL)//road�������� ������ ����
		{
			if (temp_road_sequence_node->previous != NULL){ //road �������� ������ ����
				temp_road_sequence_node->previous->next = temp_road_sequence_node->next;
				temp_road_sequence_node->next->previous = temp_road_sequence_node->previous;
			}
			else{ //road ������ ������ �ְ�, ������ ���� -> ù �ε� ����
				temp_road_sequence_node->next->previous = NULL;
				this->first_road = temp_road_sequence_node->next;
			}

		}
		else{ //road ������ ����� ������ NULL next == NULL,
			if (temp_road_sequence_node->previous != NULL)
				temp_road_sequence_node->previous->next = NULL;
		}

		//para ������ �����۾�
		//para1 ������ ���
		if (temp_para_sequence_node1->next != NULL){//para �������� ������ ����
			if (temp_para_sequence_node1->previous != NULL){//para�������� ������ ����
				temp_para_sequence_node1->previous->next = temp_para_sequence_node1->next;
				temp_para_sequence_node1->next->previous = temp_para_sequence_node1->previous;
			}
			else{//para�������� ������ �ְ� ������ ����
				temp_para_sequence_node1->next->previous = NULL;
				temp_stduent_sequence_node1->point_student->pointer_para_node = temp_para_sequence_node1->next;
			}
		}
		else{ //para �������� ������ ����
			if (temp_para_sequence_node1->previous != NULL) //para�������� ������ ����
				temp_para_sequence_node1->previous->next = NULL;
		}

		//para2 ������ ���
		if (temp_para_sequence_node2->next != NULL){//para �������� ������ ����
			if (temp_para_sequence_node2->previous != NULL){//para�������� ������ ����
				temp_para_sequence_node2->previous->next = temp_para_sequence_node2->next;
				temp_para_sequence_node2->next->previous = temp_para_sequence_node2->previous;
			}
			else{//para�������� ������ �ְ� ������ ����
				temp_para_sequence_node2->next->previous = NULL;
				temp_stduent_sequence_node2->point_student->pointer_para_node = temp_para_sequence_node2
					->next;
			}
		}
		else{ //para �������� ������ ����
			if (temp_para_sequence_node2->previous != NULL)
				temp_para_sequence_node2->previous->next = NULL;
		}


		//road��������road ����Ű�°� ����
		temp_road_sequence_node->pointer_road = NULL;
		//road�� road������ ����Ű�°� ����
		temp_road_node->pointer_road_sequence_node = NULL;
		//para�������� road����Ű�°� ����
		temp_para_sequence_node1->point_road = NULL;//para ������ -> road �� NULL ����Ŵ
		temp_para_sequence_node2->point_road = NULL;
		//road�� student����Ű�°� ����
		temp_road_node->first_student_id = NULL;
		temp_road_node->second_student_id = NULL;
		//road�� para������ ����Ű�°� ����
		temp_road_node->pointer_first_para_node = NULL;
		temp_road_node->pointer_second_para_node = NULL;
		//�Ű� ������ ����
		temp_para_sequence_node1 = NULL;
		temp_para_sequence_node2 = NULL;
		//���� ��� ����
		temp_road_node = NULL;
		//���� ������ ��� ����
		temp_road_sequence_node = NULL;
		this->total_road--;
		cout << total_road << endl;
	}
	else{//���� �� ã��
		cout << this->total_road << " Not found" << endl;
	}

}
void location_graph::print_incident_road(int _student_id){ //6.����� �������� ���
	student_sequence_node* temp_student_node = this->search_stduent_by_id(_student_id);
	//�й����� �л������� ã��
	if (temp_student_node != NULL){ //�л� ������ ã����
		if (temp_student_node->point_student != NULL){ //�л��� ������
			if (temp_student_node->point_student->pointer_para_node != NULL){ //�л� �������� ���ο� ����
				para_sequence_node* temp_para_node = temp_student_node->point_student->pointer_para_node; //�ӽ� �Ű� ���
				int degree = temp_student_node->point_student->degree; //����
				string connected_road = ""; //���θ� ������� string
				while (temp_para_node != NULL) //�Ű� ������ ����Ž�� ������
				{
					connected_road += " " + to_string(temp_para_node->point_road->road_id); //������������
					temp_para_node = temp_para_node->next;
				}
				cout << degree << connected_road << endl; //���� ���
			}
			else//�л��������� ���ο� ���� x
				cout << "Not found" << endl;
		}
		else//�л��������� �л��� ����Ű�� ���� => �����ϴ� ���� �ƴ����� Ȥ�� ���� ����ó��
			cout << "Not found" << endl;
	}
	else//�л� �������� ���� x
		cout << "Not found" << endl;
}
void location_graph::print_road_info(int _road_id){ //7.�������� ���1
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);
	//���� ��ȣ�� ���� ������ search
	if (temp_road_sequence_node != NULL){ //���� ������ ��尡 ����
		int big_id = temp_road_sequence_node->pointer_road->first_student_id; //ū��
		int small_id = temp_road_sequence_node->pointer_road->second_student_id;//������
		int temp;//replace�� ���� �ӽú���

		if (temp_road_sequence_node->pointer_road != NULL)
		{
			if (big_id < small_id)//�����𺸴� ū���� ������
			{   //ū���� ū������, ������ ����������
				temp = small_id;
				small_id = big_id;
				big_id = temp;
			}
			//�й��� ���� �й��� ���� ���
			cout << small_id << " " << big_id << endl;
		}
		else //���γ�� ������ ��尡 ����
			cout << "Not Found" << endl;
	}
	else //�ƿ� ���������� ���� ���ΰ� ����
		cout << "Not Found" << endl;
}
void location_graph::print_available_incident(int _student_id, int _road_id){ //8.�������� ���2
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);
	//���� ������ ���� ��������� search
	if (temp_road_sequence_node != NULL){ //�л� ������ ��尡 ����
		if (temp_road_sequence_node->pointer_road->first_student_id == _student_id)
			//ó�� �л��� ã�����ϴ� �л� -> �ݴ��� ���
			cout << temp_road_sequence_node->pointer_road->second_student_id << endl;
		else if (temp_road_sequence_node->pointer_road->second_student_id == _student_id)
			//���� �л��� ã�����ϴ� �л� -> �ݴ��� ���
			cout << temp_road_sequence_node->pointer_road->first_student_id << endl;
		else cout << "Not available" << endl; //���� �Ұ�

	}
	else //�л��� ���ΰ� ����Ǿ����� ����
		cout << "Not available" << endl;
}
void location_graph::print_adjacent_student(int _student_id1, int _student_id2){ //9. �������� ���� Ȯ��
	student_sequence_node* temp_student_sequence_node1 = this->search_stduent_by_id(_student_id1);
	student_sequence_node* temp_student_sequence_node2 = this->search_stduent_by_id(_student_id2);
	//�ӽ� �л� ������ 1,2

	if (temp_student_sequence_node1 != NULL && temp_student_sequence_node2 != NULL){
		//�Ѵ� �����ϴ� �л��϶�
		para_sequence_node* temp_para_sequence_node1 = temp_student_sequence_node1->point_student->pointer_para_node;
		para_sequence_node* temp_para_sequence_node2 = temp_student_sequence_node2->point_student->pointer_para_node;
		//O(min(deg(v), deg(w))
		while (temp_para_sequence_node1 != NULL && temp_para_sequence_node2 != NULL) //���������� Ž��
		{   //v���� Ž��
			if ((temp_para_sequence_node1->point_road->first_student_id == _student_id1 &&
				temp_para_sequence_node1->point_road->second_student_id == _student_id2) ||
				(temp_para_sequence_node1->point_road->first_student_id == _student_id2 &&
				temp_para_sequence_node1->point_road->second_student_id == _student_id1))
			{
				cout << temp_para_sequence_node1->point_road->road_id << endl;
				break;
			}
			//w���� Ž��
			if ((temp_para_sequence_node2->point_road->first_student_id == _student_id1 &&
				temp_para_sequence_node2->point_road->second_student_id == _student_id2) ||
				(temp_para_sequence_node2->point_road->first_student_id == _student_id2 &&
				temp_para_sequence_node2->point_road->second_student_id == _student_id1))
			{
				cout << temp_para_sequence_node2->point_road->road_id << endl;
				break;
			}
			temp_para_sequence_node1 = temp_para_sequence_node1->next;
			temp_para_sequence_node2 = temp_para_sequence_node2->next;
		}
		if (temp_para_sequence_node1 == NULL || temp_para_sequence_node2 == NULL)
			// ���߿� �ϳ��� degree ������ Ž���ϸ�
			cout << "Not found" << endl;
	}
	else
		cout << "Not found" << endl;
}

int main() {
	string fileName; //���� �̸�
	int total_student; //���л� ��
	int total_road; //�ѵ��� ��
	int line = 0; //�����Է½� ����
	int question_count = 0; //���Ǽ�
	string input_line_array[100]; //�Է¶��� �迭
	string first_line_splited[2]; //ù���� split
	string splited_by_space[3]; //��°���κ��� �����α��� split

	getline(cin, fileName, '\n');
	ifstream fileIn; //�����̸�

	fileIn.open(fileName, ios::binary); //���� ����
	if (fileIn.fail())//���Ͽ��� ����
		cout << "������ �������� �ʽ��ϴ�" << endl;
	else//���Ͽ��� ����
	{
		while (!fileIn.eof())
		{
			getline(fileIn, input_line_array[line]); //������ ������ �о����
			line++;
		}

		stringstream firstLine(input_line_array[0]); //ù��������


		for (int i = 0; i<2; i++) //ù������ �迭�� �������
		{
			firstLine >> first_line_splited[i]; //ù���θ� ����
		}


		total_student = atoi(first_line_splited[0].c_str()); //�л���
		total_road = atoi(first_line_splited[1].c_str());    //���μ�

		location_graph locationGraph(total_student, total_road); //ù�� �Է¹����ɷ� �л��׷��� ����



		for (int i = 0; i<total_student; i++){ //�л�����ŭ ��ȸ
			stringstream input_line(input_line_array[1 + i]);
			for (int i2 = 0; i2<2; i2++)
			{
				input_line >> splited_by_space[i2]; //�л����� ����
			}

			int student_id = atoi(splited_by_space[0].c_str());
			string email = splited_by_space[1];
			locationGraph.insert_student(student_id, email); //�л� �߰�

		}

		for (int i = 0; i<total_road; i++){// ���μ���ŭ ��ȸ
			stringstream input_line(input_line_array[1 + i + total_student]);
			for (int i2 = 0; i2<3; i2++)
			{
				input_line >> splited_by_space[i2]; //�������� ����
			}

			int road_id = atoi(splited_by_space[0].c_str());
			int first_student_id = atoi(splited_by_space[1].c_str());
			int second_student_id = atoi(splited_by_space[2].c_str());

			locationGraph.insert_road(road_id, first_student_id, second_student_id);
			//�����߰�
		}
		//system("cmd /c cls"); //�ܼ�ȭ�� �����
		while (question_count < 10000){                            //�ִ� ���� 10000��
			question_count++;
			//cin.clear();
			char input1;
			int input2, input3, input5;
			string input4;
			cin >> input1;

			if (input1 == 'Q')
				break;

			switch (input1) {                                  //�л� �߰�
			case 'A':
				cin >> input2;
				cin.ignore();
				getline(cin, input4);
				locationGraph.insert_student(input2, input4);
				break;
			case 'P':                                      //�л����� ���
				cin >> input2;
				locationGraph.print_student(input2);
				break;
			case 'I':                                   //���� �߰�
				cin >> input2 >> input3 >> input5;
				locationGraph.insert_road(input2, input3, input5);
				break;
			case 'X':
				cin >> input2;                            //�л� ����
				locationGraph.remove_student(input2);
				break;
			case 'Z':                                      //���� ����
				cin >> input2;
				locationGraph.remove_road(input2);
				break;
			case 'L':                                      //����� ���� ���
				cin >> input2;
				locationGraph.print_incident_road(input2);
				break;
			case 'F':                                      //�������� ��� 1
				cin >> input2;
				locationGraph.print_road_info(input2);
				break;
			case 'O':                                      //�������� ��� 2
				cin >> input2 >> input3;
				locationGraph.print_available_incident(input2, input3);
				break;
			case 'K':                                      //�������� ���� Ȯ��
				cin >> input2 >> input3;
				locationGraph.print_adjacent_student(input2, input3);
				break;
			default:
				cout << "Wrong Question" << endl;         //�߸��� ����
				break;
			}
		}
	}//else�� ��
	fileIn.close(); //���� �ݱ�
	cout << "���α׷� ����" << endl;
	return 0;
}

/*���
1.�л� �߰�
2.�л����� ���
3.���� �߰�
4.�л� ����
5.���� ����
6.����� ���� ���
7.�������� ���1
8.�������� ���2
9.�������� ���� Ȯ��


*/