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
	
	//ファイルからToDoリストの読み込み
	get_todolist(Todo_file, ToDo_list);

	do
	{
		cout << "モードを選択してください。追加:0,一覧:1,削除:2,終了:3"<<endl<<">";

		//入力値が整数以外の場合
		while (!(cin >> mode)) {
			cerr << "入力値が不正です" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "モードを選択してください。追加:0,一覧:1,削除:2,終了:3" << endl << ">";
		}

		//入力値が整数の場合
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
			cerr << "入力値が不正です" << endl;
		}
		

	} while (1);
	

	save_todolist(Todo_file, ToDo_list);

	return 0;

}

void regist_task(vector<ToDo>& Todo_list)
{
	string task,deadline;
	int priority;

	//ストリーム内の改行読み捨て
	cin.ignore();

	cout << "やること＞";
	getline(cin, task);
	
	cout << "期限(YYYY/MM/DD/HH/mm)＞";
	getline(cin, deadline);

	do
	{
		cout << "優先度(1～3で値の低い方が優先)＞";
		//入力値チェック
		while (!(cin >> priority))
		{
			cerr << "入力値が不正です" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "優先度(1～3で値の低い方が優先)＞";
		}

		if (priority>0&&priority<4)
		{
			break;
		}

		cerr << "入力値が不正です" << endl;

	} while (1);
	

	
	//タスクの追加
	Todo_list.push_back({ task,deadline,priority });

	cout << "タスクを追加しました" << endl;
}

void show_task(vector<ToDo>& Todo_list)
{
	string priority;
	int count = 1;

	cout << "やること , 期限 , 優先度" << endl;
	for (const auto& todo : Todo_list)
	{
		switch (todo.priority)
		{
		case 1:
			priority = "高";
			break;
		case 2:
			priority = "中";
			break;
		case 3:
			priority = "低";
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
			cerr << "ファイルのオープンに失敗しました";
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
				cerr << "ファイルの仕様が異なります";
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
		cerr << "ファイルのオープンに失敗しました";
		exit(EXIT_FAILURE);
	}

	for (const auto& todo : Todo_list)
	{
		ofs << todo.task << ',' << todo.dead_line << ',' << todo.priority << endl;
	}

	ofs.close();
	cout << "ファイルへ保存しました";
	
}

void remove_todolist(vector<ToDo>& Todo_list) {
	
	
	int remove_num;
	
	do
	{
		//タスク一覧の表示
		show_task(Todo_list);
		cout << "削除するタスクの番号を入力してください(0で終了)＞";

		//入力値が整数でない場合
		while (!(cin >> remove_num))
		{
			cerr << "入力値が不正です" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			//タスク一覧の表示
			show_task(Todo_list);
			cout << "削除するタスクの番号を入力してください(0で終了)＞";
		}
		
		if (Todo_list.size() < remove_num)
		{
			cerr << "入力値が不正です" << endl;
			continue;
		}

		if (remove_num==0)
		{
			cout << "削除を終了します" << endl;
			break;	//削除の終了
		}

		

		//タスクの削除
		Todo_list.erase(Todo_list.begin() + (remove_num - 1));
		cout << "タスク" << remove_num << "を削除しました" << endl;
	} while (1);

}