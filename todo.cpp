#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<filesystem>
#include<limits>

using namespace std;

struct ToDo
{
	string task;
	string dead_line;
	int priority;
	
};

void regist_task(vector<ToDo>& Todo_list);
void show_task(vector<ToDo>& Todo_list);
void sort_priority(vector<ToDo>& Todo_list);
void get_todolist(const string file_name, vector<ToDo>& Todo_list);
void save_todolist(const string file_name, vector<ToDo>& Todo_list);
void remove_todolist(vector<ToDo>& Todo_list);

int main() {

	int mode;
	string Todo_file = "todolist.csv";
	vector<ToDo> ToDo_list;
	
	//�t�@�C������ToDo���X�g�̓ǂݍ���
	get_todolist(Todo_file, ToDo_list);

	do
	{
		cout << "���[�h��I�����Ă��������B�ǉ�:0,�ꗗ:1,�폜:2,�I��:3"<<endl<<">";

		//���͒l�������ȊO�̏ꍇ
		while (!(cin >> mode)) {
			cerr << "���͒l���s���ł�" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "���[�h��I�����Ă��������B�ǉ�:0,�ꗗ:1,�폜:2,�I��:3" << endl << ">";
		}

		//���͒l�������̏ꍇ
		if (mode == 0)
		{
			regist_task(ToDo_list);
		}else if (mode == 1)
		{
			show_task(ToDo_list);
		}else if (mode == 2)
		{
			remove_todolist(ToDo_list);
		}else if (mode == 3)
		{
			break;
		}
		else
		{
			cerr << "���͒l���s���ł�" << endl;
		}
		

	} while (1);
	

	save_todolist(Todo_file, ToDo_list);

	return 0;

}

void regist_task(vector<ToDo>& Todo_list)
{
	string task,deadline;
	int priority;

	//�X�g���[�����̉��s�ǂݎ̂�
	cin.ignore();

	cout << "��邱�Ɓ�";
	getline(cin, task);
	
	cout << "����(YYYY/MM/DD/HH/mm)��";
	getline(cin, deadline);

	do
	{
		cout << "�D��x(1�`3�Œl�̒Ⴂ�����D��)��";
		//���͒l�`�F�b�N
		while (!(cin >> priority))
		{
			cerr << "���͒l���s���ł�" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�D��x(1�`3�Œl�̒Ⴂ�����D��)��";
		}

		if (priority>0&&priority<4)
		{
			break;
		}

		cerr << "���͒l���s���ł�" << endl;

	} while (1);
	

	
	//�^�X�N�̒ǉ�
	Todo_list.push_back({ task,deadline,priority });

	cout << "�^�X�N��ǉ����܂���" << endl;
}

void show_task(vector<ToDo>& Todo_list)
{
	string priority;
	int count = 1;

	cout << "��邱�� , ���� , �D��x" << endl;
	for (const auto& todo : Todo_list)
	{
		switch (todo.priority)
		{
		case 1:
			priority = "��";
			break;
		case 2:
			priority = "��";
			break;
		case 3:
			priority = "��";
			break;
		default:
			break;
		}

		cout <<setw(3)<< count << ":";
		cout << todo.task << " | " << todo.dead_line << " | " << priority << endl;
		
		count++;
	}
}

void sort_priority(vector<ToDo>& Todo_list)
{
	sort(Todo_list.begin(), Todo_list.end(), [](const ToDo& a, const ToDo& b) {
		return a.priority < b.priority;
		});
}

void get_todolist(const string file_name, vector<ToDo>& Todo_list)
{
	ifstream ifst;
	if (filesystem::exists(file_name))
	{
		
		ifst.open(file_name);
		if (!ifst)
		{
			cerr << "�t�@�C���̃I�[�v���Ɏ��s���܂���";
			exit(EXIT_FAILURE);
		}

		string line;
		while (getline(ifst,line))
		{
			istringstream iss(line);
			string task, deadline;
			int priority;
			
			if (getline(iss,task,',') && getline(iss, deadline,',') && iss >> priority)
			{
				Todo_list.push_back({ task,deadline,priority });
			}
			else
			{
				cerr << "�t�@�C���̎d�l���قȂ�܂�";
				exit(EXIT_FAILURE);
			}
		}

		ifst.close();
	}
	
}

void save_todolist(const string file_name, vector<ToDo>& Todo_list)
{
	ofstream ofs;
	
	ofs.open(file_name);
	if (!ofs)
	{
		cerr << "�t�@�C���̃I�[�v���Ɏ��s���܂���";
		exit(EXIT_FAILURE);
	}

	for (const auto& todo : Todo_list)
	{
		ofs << todo.task << ',' << todo.dead_line << ',' << todo.priority << endl;
	}

	ofs.close();
	cout << "�t�@�C���֕ۑ����܂���";
	
}

void remove_todolist(vector<ToDo>& Todo_list) {
	
	
	int remove_num;
	
	do
	{
		//�^�X�N�ꗗ�̕\��
		show_task(Todo_list);
		cout << "�폜����^�X�N�̔ԍ�����͂��Ă�������(0�ŏI��)��";

		//���͒l�������łȂ��ꍇ
		while (!(cin >> remove_num))
		{
			cerr << "���͒l���s���ł�" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			//�^�X�N�ꗗ�̕\��
			show_task(Todo_list);
			cout << "�폜����^�X�N�̔ԍ�����͂��Ă�������(0�ŏI��)��";
		}
		
		if (Todo_list.size() < remove_num)
		{
			cerr << "���͒l���s���ł�" << endl;
			continue;
		}

		if (remove_num==0)
		{
			cout << "�폜���I�����܂�" << endl;
			break;	//�폜�̏I��
		}

		

		//�^�X�N�̍폜
		Todo_list.erase(Todo_list.begin() + (remove_num - 1));
		cout << "�^�X�N" << remove_num << "���폜���܂���" << endl;
	} while (1);

}