/* 제한사항
(1) 학생은 최대 100명이 입력된다.
(2) 도로는 최대 4,950개가 입력된다.
(3) 질의는 최대 10,000개가 입력된다.
*/

/*기능
1.학생 추가
2.학생정보 출력
3.도로 추가
4.학생 삭제
5.도로 삭제
6.연결된 도로 출력
7.도로정보 출력1
8.도로정보 출력2
9.도로존재 여부 확인
*/

#include <iostream> //표준입출력
#include <fstream>  //file stream 파일 입력
#include <sstream>  //string stream split by space 파일로부터 데이터 한줄씩 입력하기위해
#include <stdlib.h> //system("cls") 콘솔창 지우기
#include <string>   //string 사용

using namespace std;

struct road;                    //도로 구조체
struct student;                 //학생 구조체
struct student_sequence_node;   //학생 시퀀스 구조체
struct road_sequence_node;      //도로 시퀀스 구조체
struct para_sequence_node;      //매개 시퀀스 구조체

struct road{                                                //road struct
	para_sequence_node* pointer_first_para_node = NULL;     //첫번째 매개시퀀스 가리키는 포인터
	para_sequence_node* pointer_second_para_node = NULL;    //두번째 매개시퀀스 가리키는 포인터
	road_sequence_node* pointer_road_sequence_node = NULL;  //도로 시퀀스를 가리킴
	int road_id = NULL;                                     //도로 번호
	int first_student_id = 0;                               //도로에 연결된 학생1
	int second_student_id = 0;                              //도로에 연결된 학생2
};

struct student{                                             //student struct
	student_sequence_node* pointer_student_node = NULL;     //학생 시퀀스 포인터
	para_sequence_node* pointer_para_node = NULL;           //매개 시퀀스 포인터
	int student_id = 0;                                     //학번
	int degree = 0;                                         //degree 차수
	string email = "";                                      //email 주소
};

struct student_sequence_node {                              //student sequence
	student_sequence_node *previous = NULL;                 //이전 학생 시퀀스
	student_sequence_node *next = NULL;                     //다음 학생 시퀀스
	student *point_student = NULL;                          //학생 포인터
};


struct para_sequence_node{                                  //student struct와 road struct 매개
	para_sequence_node* next = NULL;                        //이전 매개 시퀀스
	para_sequence_node* previous = NULL;                    //다음 매개 시퀀스
	road *point_road = NULL;                                //도로 포인터
};

struct road_sequence_node{                                  //도로 시퀀스
	road_sequence_node *previous = NULL;                    //이전 도로
	road_sequence_node *next = NULL;                        //다음 도로
	road *pointer_road = NULL;                              //도로 포인터
};

class location_graph{                                       //Graph Class
private:
	road_sequence_node *first_road = NULL;                  //도로 리스트(시퀀스)
	//para_sequence_node *first_para = NULL;                //매개변수 리스트(시퀀스)
	student_sequence_node *first_student = NULL;            //학생 리스트(시퀀스)

	int total_student;                                      //전체 학생수
	int total_road;                                         //전체 도로수

public:
	location_graph(int, int);                               //생성자
	~location_graph();                                      //소멸자
	void insert_student(int, string);                       //1.학생 추가
	void print_student(int);                                //2.학생정보 출력
	void insert_road(int, int, int);                        //3.도로 추가
	void remove_student(int);                               //4.학생 삭제
	void remove_road(int);                                  //5.도로 삭제
	void print_incident_road(int);                          //6.연결된 도로정보 출력 INCIDENT
	void print_road_info(int);                              //7.도로정보 출력1
	void print_available_incident(int, int);                //8.도로정보 출력2
	void print_adjacent_student(int, int);                  //9. 도로존재 여부 확인
	student_sequence_node* search_stduent_by_id(int);       //학번으로 학생시퀀스노드 찾기
	road_sequence_node* search_road_by_id(int);             //학번으로 도로시퀀스노드 찾기

};

location_graph::location_graph(int _student_size, int _road_size){ //생성자
	total_student = 0;                                             //멤버 변수 초기화
	total_road = 0;
}
location_graph::~location_graph(){                                 //소멸자

}

student_sequence_node* location_graph::search_stduent_by_id(int _id) //학번으로 학생시퀀스노드 찾기
{
	bool found = false;
	student_sequence_node* temp_student_sequence_node = this->first_student; //처음은 처음시퀀스로
	while (temp_student_sequence_node != NULL){         //마지막놈 체크 안 하고 넘어감
		if (temp_student_sequence_node->point_student->student_id == _id){
			found = true;
			break;
		}
		else
			temp_student_sequence_node = temp_student_sequence_node->next;
	}
	//다 검사하고
	if (found == false) //못 찾으면
		temp_student_sequence_node = NULL; //NULL로 설정

	return temp_student_sequence_node;//반환
}

road_sequence_node* location_graph::search_road_by_id(int _id){ //학번으로 도로시퀀스노드 찾기
	bool found = false;
	road_sequence_node* temp_road_sequence_node = this->first_road; //처음은 처음 시퀀스로
	while (temp_road_sequence_node != NULL){ //마지막놈 체크 안 하고 넘어감
		if (temp_road_sequence_node->pointer_road->road_id == _id){
			found = true;
			break;
		}
		else
			temp_road_sequence_node = temp_road_sequence_node->next;
	}
	//다 검사하고
	if (found == false) //못찾으면
		temp_road_sequence_node = NULL;

	return temp_road_sequence_node;//반환
}

void location_graph::insert_student(int _id, string _email){ //1.학생 추가
	student *new_student = new student; //학생 노드 생성
	student_sequence_node *new_student_sequence_node = new student_sequence_node; //학생시퀀스노드생성

	//학생 struct 생성, 초기화
	new_student->degree = 0;
	new_student->email = _email;
	new_student->student_id = _id;
	new_student->pointer_student_node = new_student_sequence_node;

	//학생 sequence 생성, 초기화
	new_student_sequence_node->next = NULL;
	new_student_sequence_node->previous = NULL;
	new_student_sequence_node->point_student = new_student;

	if (this->first_student == NULL) //처음 학생이 없으면 처음학생으로 지정
		this->first_student = new_student_sequence_node;

	else{ //처음 시퀀스 학생이 있으면
		student_sequence_node* temp_pointer_student_node = this->first_student;
		while (temp_pointer_student_node->next != NULL){//while 돌면서 끝을 찾고
			temp_pointer_student_node = temp_pointer_student_node->next;
		}
		//마지막에 넣기
		temp_pointer_student_node->next = new_student_sequence_node;
		new_student_sequence_node->previous = temp_pointer_student_node;
	}

	this->total_student++;
	cout << this->total_student << endl;
}
void location_graph::print_student(int _id){ //2.학생정보 출력
	student_sequence_node* temp_student_node = this->search_stduent_by_id(_id);//탐색
	if (temp_student_node != NULL){ //있으면
		string email = temp_student_node->point_student->email;
		int degree = temp_student_node->point_student->degree;
		cout << email << " " << degree << endl; // 연결된 도로의 수
	}
	else//없으면
		cout << "Not Found" << endl;


}
void location_graph::insert_road(int _road_id, int _first_student_id, int _second_student_id){
	//3.도로 추가

	student_sequence_node* temp_first_student_node = this->search_stduent_by_id(_first_student_id);
	student_sequence_node* temp_second_student_node = this->search_stduent_by_id(_second_student_id);
	// id로 있는지 없는지 검사
	if (temp_first_student_node != NULL && temp_second_student_node != NULL)//찾음
	{
		//도로 struct 생성, 멤버 초기화
		road *new_road = new road;
		new_road->first_student_id = _first_student_id;
		new_road->second_student_id = _second_student_id;
		new_road->road_id = _road_id;

		//도로 sequence 생성, 멤버 초기화
		road_sequence_node *new_road_sequence_node = new road_sequence_node;
		new_road->pointer_road_sequence_node = new_road_sequence_node;
		new_road_sequence_node->next = NULL;
		new_road_sequence_node->previous = NULL;

		//도로 시퀀스 연결
		//첫로드가 없으면 첫로드로 지정
		if (this->first_road == NULL){
			this->first_road = new_road_sequence_node;
			this->first_road->pointer_road = new_road;
		}
		else //첫로드가 있으면 마지막로드에 시퀀스 연결
		{
			road_sequence_node* temp_road_sequence_node = this->first_road;
			while (temp_road_sequence_node->next != NULL) //while돌면서 마지막 탐색
				temp_road_sequence_node = temp_road_sequence_node->next;
			temp_road_sequence_node->next = new_road_sequence_node;
			new_road_sequence_node->previous = temp_road_sequence_node;
			new_road_sequence_node->pointer_road = new_road;
		}

		//길 하나당 매개 sequence 2개필요
		//매개 sequence1 생성, 멤버 초기화
		para_sequence_node *new_para_sequence_node1 = new para_sequence_node;
		new_para_sequence_node1->point_road = new_road;
		new_para_sequence_node1->next = NULL;
		new_para_sequence_node1->previous = NULL;

		//매개 sequence2 생성, 멤버 초기화
		para_sequence_node *new_para_sequence_node2 = new para_sequence_node;
		new_para_sequence_node2->point_road = new_road;
		new_para_sequence_node2->next = NULL;
		new_para_sequence_node2->previous = NULL;


		//도로가 매개시퀀스 가리키도록
		//처음 가리키는 매개시퀀스가 없음
		if (temp_first_student_node->point_student->pointer_para_node == NULL)
			temp_first_student_node->point_student->pointer_para_node = new_para_sequence_node1;
		else //처음 가리키는 매개시퀀스가 있으면 마지막에다가 연결
		{
			para_sequence_node *temp_para_sequence_node = temp_first_student_node->point_student->pointer_para_node;
			while (temp_para_sequence_node->next != NULL) //매개시퀀스 마지막을 찾아서
			{
				temp_para_sequence_node = temp_para_sequence_node->next;
			}
			//매개 시퀀스 연결
			temp_para_sequence_node->next = new_para_sequence_node1;
			new_para_sequence_node1->previous = temp_para_sequence_node;
		}


		//위와 같은 패턴
		if (temp_second_student_node->point_student->pointer_para_node == NULL)
			temp_second_student_node->point_student->pointer_para_node = new_para_sequence_node2;
		else{
			para_sequence_node* temp_para_sequence_node = temp_second_student_node->point_student->pointer_para_node;
			while (temp_para_sequence_node->next != NULL)
			{
				temp_para_sequence_node = temp_para_sequence_node->next;
			}
			//매개 시퀀스 연결
			temp_para_sequence_node->next = new_para_sequence_node2;
			new_para_sequence_node2->previous = temp_para_sequence_node;
		}



		temp_first_student_node->point_student->degree++; //degree증가
		temp_second_student_node->point_student->degree++; //degree증가

		//도로가 매개시퀀스 가리키도록 설정
		new_road->pointer_first_para_node = new_para_sequence_node1;
		new_road->pointer_second_para_node = new_para_sequence_node2;

		this->total_road++;
		cout << this->total_road << endl;
	}
	else
		cout << this->total_road << " Not Found" << endl;
	//도로생성, 매개시퀀스 연결 끝


}
void location_graph::remove_student(int _student_id){ //4.학생 삭제 (총학생수 도로수 출력)
	student_sequence_node* temp_student_sequence_node = this->search_stduent_by_id(_student_id);
	//학생 id로 search
	if (temp_student_sequence_node != NULL){ //삭제할 학생이 존재하면
		student* temp_student_node = temp_student_sequence_node->point_student;
		//학생노드가 파라미터 노드를 안 가질 경우도 생각
		if (temp_student_node->pointer_para_node != NULL){ //학생이 매개 시퀀스를 가지면
			para_sequence_node* temp_para_sequence_node = temp_student_node->pointer_para_node;
			//연결된 도로 삭제
			while (temp_para_sequence_node != NULL){ //도로삭제 반복문 시작
				//도로, 매개시퀀스 삭제 시작 (remove_road와 비슷합니다) 설명은 remove_road에 적음
				temp_para_sequence_node = temp_student_node->pointer_para_node;
				road_sequence_node* temp_road_sequence_node = this->search_road_by_id(temp_para_sequence_node->point_road->road_id);
				if (temp_road_sequence_node != NULL){ //도로 찾음

					road* temp_road_node = temp_road_sequence_node->pointer_road;
					para_sequence_node* temp_para_sequence_node1 = temp_road_node->pointer_first_para_node;
					para_sequence_node* temp_para_sequence_node2 = temp_road_node->pointer_second_para_node;
					student_sequence_node* temp_stduent_sequence_node1 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->first_student_id);
					student_sequence_node* temp_stduent_sequence_node2 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->second_student_id);

					temp_stduent_sequence_node1->point_student->degree--;
					temp_stduent_sequence_node2->point_student->degree--;
					temp_para_sequence_node1->point_road = NULL;
					temp_para_sequence_node2->point_road = NULL;
					if (temp_road_sequence_node->next != NULL) // road 시퀀스 당김
					{
						if (temp_road_sequence_node->previous != NULL){
							temp_road_sequence_node->previous->next = temp_road_sequence_node->next;
							temp_road_sequence_node->next->previous = temp_road_sequence_node->previous;
						}
						else{ //road 시퀀스 다음이 있고, 이전은 없음 -> 첫 로드 삭제
							temp_road_sequence_node->next->previous = NULL;
							this->first_road = temp_road_sequence_node->next;
						}

					}
					else{ //road 시퀀스 노드의 다음이 NULL next == NULL,
						if (temp_road_sequence_node->previous != NULL)
							temp_road_sequence_node->previous->next = NULL;
					}

					//para 시퀀스 연결작업
					//para1 시퀀스 당김
					if (temp_para_sequence_node1->next != NULL){
						if (temp_para_sequence_node1->previous != NULL){
							temp_para_sequence_node1->previous->next = temp_para_sequence_node1->next;
							temp_para_sequence_node1->next->previous = temp_para_sequence_node1->previous;
						}
						else{//para시퀀스의 다음은 있고 이전은 없음
							temp_para_sequence_node1->next->previous = NULL;
							temp_stduent_sequence_node1->point_student->pointer_para_node = temp_para_sequence_node1->next;
						}
					}
					else{ //para 시퀀스의 다음이 없음
						if (temp_para_sequence_node1->previous != NULL)
							temp_para_sequence_node1->previous->next = NULL;
					}

					//para2 시퀀스 당김
					if (temp_para_sequence_node2->next != NULL){
						if (temp_para_sequence_node2->previous != NULL){
							temp_para_sequence_node2->previous->next = temp_para_sequence_node2->next;
							temp_para_sequence_node2->next->previous = temp_para_sequence_node2->previous;
						}
						else{//para시퀀스의 다음은 있고 이전은 없음
							temp_para_sequence_node2->next->previous = NULL;
							temp_stduent_sequence_node2->point_student->pointer_para_node = temp_para_sequence_node2
								->next;
						}
					}
					else{ //para 시퀀스의 다음이 없음
						if (temp_para_sequence_node2->previous != NULL)
							temp_para_sequence_node2->previous->next = NULL;
					}


					//road시퀀스가road 가리키는걸 삭제
					temp_road_sequence_node->pointer_road = NULL;
					//road가 road시퀀스 가리키는걸 삭제
					temp_road_node->pointer_road_sequence_node = NULL;
					//para시퀀스가 road가리키는걸 삭제
					temp_para_sequence_node1->point_road = NULL;//para 시퀀스 -> road 가 NULL 가리킴
					temp_para_sequence_node2->point_road = NULL;
					//road가 student가리키는걸 삭제
					temp_road_node->first_student_id = NULL;
					temp_road_node->second_student_id = NULL;
					//road가 para시퀀스 가리키는걸 삭제
					temp_road_node->pointer_first_para_node = NULL;
					temp_road_node->pointer_second_para_node = NULL;
					//매개 시퀀스 삭제
					temp_para_sequence_node1 = NULL;
					temp_para_sequence_node2 = NULL;
					//도로 노드 삭제
					temp_road_node = NULL;
					//도로 시퀀스 노드 삭제
					temp_road_sequence_node = NULL;
				}//도로 매개시퀀스 삭제부분 끝
				this->total_road--;
				if (temp_student_node->pointer_para_node->point_road == NULL) //매개시퀀스 비어있으면끝
					break;
				//총 도로수 감소
				//temp_para_sequence_node = temp_para_sequence_node -> next; // 다음 매개시퀀스로 이동
			} //도로삭제 반복문 끝
		}
		else//학생의 매개시퀀스가 없음
		{
			//아무일도 안함
		}


		//학생 시퀀스 당기고
		if (temp_student_sequence_node->next != NULL){
			if (temp_student_sequence_node->previous != NULL){//학생시퀀스 다음도 있고 이전도 있음
				temp_student_sequence_node->previous->next = temp_student_sequence_node->next;
				temp_student_sequence_node->next->previous = temp_student_sequence_node->previous;
			}
			else{//학생 시퀀스의 다음은 있고 이전은 없음 => 첫 학생을 삭제한거
				temp_student_sequence_node->next->previous = NULL;
				this->first_student = temp_student_sequence_node->next;
			}
		}
		else{ //학생 시퀀스의 다음이 없음
			if (temp_student_sequence_node->previous != NULL)//다음은없고 이전은 있음
				temp_student_sequence_node->previous->next = NULL;
		}

		//학생 시퀀스 삭제
		temp_student_sequence_node = NULL;
		//학생 노드 삭제
		temp_student_node = NULL;
		//총 학생수 감소
		this->total_student--;

		cout << this->total_student << " " << this->total_road << endl;

	} //삭제할 학생 존재 조건문 끝
	else{
		cout << this->total_student << " " << this->total_road << " Not found" << endl; //삭제할 학생 존재 X
	}

}
void location_graph::remove_road(int _road_id){ //5.도로 삭제
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);


	if (temp_road_sequence_node != NULL){ //도로 찾음

		road* temp_road_node = temp_road_sequence_node->pointer_road;
		para_sequence_node* temp_para_sequence_node1 = temp_road_node->pointer_first_para_node;
		para_sequence_node* temp_para_sequence_node2 = temp_road_node->pointer_second_para_node;
		student_sequence_node* temp_stduent_sequence_node1 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->first_student_id);
		student_sequence_node* temp_stduent_sequence_node2 = this->search_stduent_by_id(temp_road_sequence_node->pointer_road->second_student_id);

		/*
		각각 임시 도로 노드, 임시 매개 시퀀스 1,2 , 임시 학생 시퀀스 1,2
		*/

		//degree 감소
		temp_stduent_sequence_node1->point_student->degree--;
		temp_stduent_sequence_node2->point_student->degree--;

		//매개 시퀀스가 도로 NULL가리키도록
		temp_para_sequence_node1->point_road = NULL;
		temp_para_sequence_node2->point_road = NULL;
		//road 시퀀스 당김
		if (temp_road_sequence_node->next != NULL)//road시퀀스가 다음이 있음
		{
			if (temp_road_sequence_node->previous != NULL){ //road 시퀀스가 이전이 있음
				temp_road_sequence_node->previous->next = temp_road_sequence_node->next;
				temp_road_sequence_node->next->previous = temp_road_sequence_node->previous;
			}
			else{ //road 시퀀스 다음이 있고, 이전은 없음 -> 첫 로드 삭제
				temp_road_sequence_node->next->previous = NULL;
				this->first_road = temp_road_sequence_node->next;
			}

		}
		else{ //road 시퀀스 노드의 다음이 NULL next == NULL,
			if (temp_road_sequence_node->previous != NULL)
				temp_road_sequence_node->previous->next = NULL;
		}

		//para 시퀀스 연결작업
		//para1 시퀀스 당김
		if (temp_para_sequence_node1->next != NULL){//para 시퀀스가 다음이 있음
			if (temp_para_sequence_node1->previous != NULL){//para시퀀스가 이전이 있음
				temp_para_sequence_node1->previous->next = temp_para_sequence_node1->next;
				temp_para_sequence_node1->next->previous = temp_para_sequence_node1->previous;
			}
			else{//para시퀀스의 다음이 있고 이전이 없음
				temp_para_sequence_node1->next->previous = NULL;
				temp_stduent_sequence_node1->point_student->pointer_para_node = temp_para_sequence_node1->next;
			}
		}
		else{ //para 시퀀스의 다음이 없음
			if (temp_para_sequence_node1->previous != NULL) //para시퀀스의 이전이 있음
				temp_para_sequence_node1->previous->next = NULL;
		}

		//para2 시퀀스 당김
		if (temp_para_sequence_node2->next != NULL){//para 시퀀스가 다음이 있음
			if (temp_para_sequence_node2->previous != NULL){//para시퀀스가 이전이 있음
				temp_para_sequence_node2->previous->next = temp_para_sequence_node2->next;
				temp_para_sequence_node2->next->previous = temp_para_sequence_node2->previous;
			}
			else{//para시퀀스의 다음은 있고 이전은 없음
				temp_para_sequence_node2->next->previous = NULL;
				temp_stduent_sequence_node2->point_student->pointer_para_node = temp_para_sequence_node2
					->next;
			}
		}
		else{ //para 시퀀스의 다음이 없음
			if (temp_para_sequence_node2->previous != NULL)
				temp_para_sequence_node2->previous->next = NULL;
		}


		//road시퀀스가road 가리키는걸 삭제
		temp_road_sequence_node->pointer_road = NULL;
		//road가 road시퀀스 가리키는걸 삭제
		temp_road_node->pointer_road_sequence_node = NULL;
		//para시퀀스가 road가리키는걸 삭제
		temp_para_sequence_node1->point_road = NULL;//para 시퀀스 -> road 가 NULL 가리킴
		temp_para_sequence_node2->point_road = NULL;
		//road가 student가리키는걸 삭제
		temp_road_node->first_student_id = NULL;
		temp_road_node->second_student_id = NULL;
		//road가 para시퀀스 가리키는걸 삭제
		temp_road_node->pointer_first_para_node = NULL;
		temp_road_node->pointer_second_para_node = NULL;
		//매개 시퀀스 삭제
		temp_para_sequence_node1 = NULL;
		temp_para_sequence_node2 = NULL;
		//도로 노드 삭제
		temp_road_node = NULL;
		//도로 시퀀스 노드 삭제
		temp_road_sequence_node = NULL;
		this->total_road--;
		cout << total_road << endl;
	}
	else{//도로 못 찾음
		cout << this->total_road << " Not found" << endl;
	}

}
void location_graph::print_incident_road(int _student_id){ //6.연결된 도로정보 출력
	student_sequence_node* temp_student_node = this->search_stduent_by_id(_student_id);
	//학번으로 학생시퀀스 찾음
	if (temp_student_node != NULL){ //학생 시퀀스 찾으면
		if (temp_student_node->point_student != NULL){ //학생이 있으면
			if (temp_student_node->point_student->pointer_para_node != NULL){ //학생 시퀀스가 도로에 연결
				para_sequence_node* temp_para_node = temp_student_node->point_student->pointer_para_node; //임시 매개 노드
				int degree = temp_student_node->point_student->degree; //차수
				string connected_road = ""; //도로를 담기위한 string
				while (temp_para_node != NULL) //매개 시퀀스 선형탐색 끝까지
				{
					connected_road += " " + to_string(temp_para_node->point_road->road_id); //도로정보담음
					temp_para_node = temp_para_node->next;
				}
				cout << degree << connected_road << endl; //차수 출력
			}
			else//학생시퀀스가 도로에 연결 x
				cout << "Not found" << endl;
		}
		else//학생시퀀스가 학생을 가르키지 않음 => 존재하는 경우는 아니지만 혹시 몰라서 예외처리
			cout << "Not found" << endl;
	}
	else//학생 시퀀스가 존재 x
		cout << "Not found" << endl;
}
void location_graph::print_road_info(int _road_id){ //7.도로정보 출력1
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);
	//도로 번호로 도로 시퀀스 search
	if (temp_road_sequence_node != NULL){ //도로 시퀀스 노드가 존재
		int big_id = temp_road_sequence_node->pointer_road->first_student_id; //큰놈
		int small_id = temp_road_sequence_node->pointer_road->second_student_id;//작은놈
		int temp;//replace를 위한 임시변수

		if (temp_road_sequence_node->pointer_road != NULL)
		{
			if (big_id < small_id)//작은놈보다 큰놈이 작으면
			{   //큰놈은 큰놈으로, 작은놈 작은놈으로
				temp = small_id;
				small_id = big_id;
				big_id = temp;
			}
			//학번이 작은 학번이 먼저 출력
			cout << small_id << " " << big_id << endl;
		}
		else //도로노드 시퀀스 노드가 없음
			cout << "Not Found" << endl;
	}
	else //아예 도로정보에 의한 도로가 없음
		cout << "Not Found" << endl;
}
void location_graph::print_available_incident(int _student_id, int _road_id){ //8.도로정보 출력2
	road_sequence_node* temp_road_sequence_node = this->search_road_by_id(_road_id);
	//도로 정보로 도로 시퀀스노드 search
	if (temp_road_sequence_node != NULL){ //학생 시퀀스 노드가 존재
		if (temp_road_sequence_node->pointer_road->first_student_id == _student_id)
			//처음 학생이 찾고자하는 학생 -> 반대편 출력
			cout << temp_road_sequence_node->pointer_road->second_student_id << endl;
		else if (temp_road_sequence_node->pointer_road->second_student_id == _student_id)
			//다음 학생이 찾고자하는 학생 -> 반대편 출력
			cout << temp_road_sequence_node->pointer_road->first_student_id << endl;
		else cout << "Not available" << endl; //접근 불가

	}
	else //학생과 도로가 연결되어있지 않음
		cout << "Not available" << endl;
}
void location_graph::print_adjacent_student(int _student_id1, int _student_id2){ //9. 도로존재 여부 확인
	student_sequence_node* temp_student_sequence_node1 = this->search_stduent_by_id(_student_id1);
	student_sequence_node* temp_student_sequence_node2 = this->search_stduent_by_id(_student_id2);
	//임시 학생 시퀀스 1,2

	if (temp_student_sequence_node1 != NULL && temp_student_sequence_node2 != NULL){
		//둘다 존재하는 학생일때
		para_sequence_node* temp_para_sequence_node1 = temp_student_sequence_node1->point_student->pointer_para_node;
		para_sequence_node* temp_para_sequence_node2 = temp_student_sequence_node2->point_student->pointer_para_node;
		//O(min(deg(v), deg(w))
		while (temp_para_sequence_node1 != NULL && temp_para_sequence_node2 != NULL) //마지막까지 탐색
		{   //v에서 탐색
			if ((temp_para_sequence_node1->point_road->first_student_id == _student_id1 &&
				temp_para_sequence_node1->point_road->second_student_id == _student_id2) ||
				(temp_para_sequence_node1->point_road->first_student_id == _student_id2 &&
				temp_para_sequence_node1->point_road->second_student_id == _student_id1))
			{
				cout << temp_para_sequence_node1->point_road->road_id << endl;
				break;
			}
			//w에서 탐색
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
			// 둘중에 하나라도 degree 끝까지 탐색하면
			cout << "Not found" << endl;
	}
	else
		cout << "Not found" << endl;
}

int main() {
	string fileName; //파일 이름
	int total_student; //총학생 수
	int total_road; //총도로 수
	int line = 0; //파일입력시 라인
	int question_count = 0; //질의수
	string input_line_array[100]; //입력라인 배열
	string first_line_splited[2]; //첫라인 split
	string splited_by_space[3]; //둘째라인부터 끝라인까지 split

	getline(cin, fileName, '\n');
	ifstream fileIn; //파일이름

	fileIn.open(fileName, ios::binary); //파일 열기
	if (fileIn.fail())//파일열기 실패
		cout << "파일이 존재하지 않습니다" << endl;
	else//파일열기 성공
	{
		while (!fileIn.eof())
		{
			getline(fileIn, input_line_array[line]); //파일의 라인을 읽어들임
			line++;
		}

		stringstream firstLine(input_line_array[0]); //첫라인읽음


		for (int i = 0; i<2; i++) //첫라인을 배열에 집어넣음
		{
			firstLine >> first_line_splited[i]; //첫라인만 읽음
		}


		total_student = atoi(first_line_splited[0].c_str()); //학생수
		total_road = atoi(first_line_splited[1].c_str());    //도로수

		location_graph locationGraph(total_student, total_road); //첫줄 입력받은걸로 학생그래프 구축



		for (int i = 0; i<total_student; i++){ //학생수만큼 순회
			stringstream input_line(input_line_array[1 + i]);
			for (int i2 = 0; i2<2; i2++)
			{
				input_line >> splited_by_space[i2]; //학생정보 담음
			}

			int student_id = atoi(splited_by_space[0].c_str());
			string email = splited_by_space[1];
			locationGraph.insert_student(student_id, email); //학생 추가

		}

		for (int i = 0; i<total_road; i++){// 도로수만큼 순회
			stringstream input_line(input_line_array[1 + i + total_student]);
			for (int i2 = 0; i2<3; i2++)
			{
				input_line >> splited_by_space[i2]; //도로정보 담음
			}

			int road_id = atoi(splited_by_space[0].c_str());
			int first_student_id = atoi(splited_by_space[1].c_str());
			int second_student_id = atoi(splited_by_space[2].c_str());

			locationGraph.insert_road(road_id, first_student_id, second_student_id);
			//도로추가
		}
		//system("cmd /c cls"); //콘솔화면 지우기
		while (question_count < 10000){                            //최대 질의 10000번
			question_count++;
			//cin.clear();
			char input1;
			int input2, input3, input5;
			string input4;
			cin >> input1;

			if (input1 == 'Q')
				break;

			switch (input1) {                                  //학생 추가
			case 'A':
				cin >> input2;
				cin.ignore();
				getline(cin, input4);
				locationGraph.insert_student(input2, input4);
				break;
			case 'P':                                      //학생정보 출력
				cin >> input2;
				locationGraph.print_student(input2);
				break;
			case 'I':                                   //도로 추가
				cin >> input2 >> input3 >> input5;
				locationGraph.insert_road(input2, input3, input5);
				break;
			case 'X':
				cin >> input2;                            //학생 삭제
				locationGraph.remove_student(input2);
				break;
			case 'Z':                                      //도로 삭제
				cin >> input2;
				locationGraph.remove_road(input2);
				break;
			case 'L':                                      //연결된 도로 출력
				cin >> input2;
				locationGraph.print_incident_road(input2);
				break;
			case 'F':                                      //도로정보 출력 1
				cin >> input2;
				locationGraph.print_road_info(input2);
				break;
			case 'O':                                      //도로정보 출력 2
				cin >> input2 >> input3;
				locationGraph.print_available_incident(input2, input3);
				break;
			case 'K':                                      //도로존재 여부 확인
				cin >> input2 >> input3;
				locationGraph.print_adjacent_student(input2, input3);
				break;
			default:
				cout << "Wrong Question" << endl;         //잘못된 질의
				break;
			}
		}
	}//else문 끝
	fileIn.close(); //파일 닫기
	cout << "프로그램 종료" << endl;
	return 0;
}

/*기능
1.학생 추가
2.학생정보 출력
3.도로 추가
4.학생 삭제
5.도로 삭제
6.연결된 도로 출력
7.도로정보 출력1
8.도로정보 출력2
9.도로존재 여부 확인


*/