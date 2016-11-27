#pragma once
class RankClass {
	int rank[11];
public:
	int GetRank(int pos) {
		if (pos < 0 || pos >= 11) return -1;
		return rank[pos];
	}
	RankClass() {
		FileLoad();
	}
	void AddRank(int score);
	void RankSort();
	void FileLoad();
	void FileSave();
};

void RankClass::AddRank(int score) //������ ���� �� ����� �̸��� �ð��� ��ŷ�� ����
{
	rank[10] = score;

	RankSort();
	FileSave();
}

void RankClass::RankSort() //������ ���� ��ũ ����
{
	int temp;

	for (int i = 0; i<10; i++) {
		for (int j = i + 1; j<11; j++) {
			if (rank[j] > rank[i]) {
				temp = rank[i];
				rank[i] = rank[j];
				rank[j] = temp;
			}
		}
	}
	FileSave();
}

void RankClass::FileLoad() //������ ���� ����Ǿ��ִ� �����͸� �ҷ���
{
	FILE *savefile;

	fopen_s(&savefile, "rank.txt", "rt");

	if (savefile == NULL) { //������ ������ ���� �����
		fopen_s(&savefile, "rank.txt", "w");
		for (int i = 0; i < 10; i++) {
			fprintf(savefile, "%d\n", 0);
			rank[i] = 0;
		}
		fclose(savefile);
		return;
	}

	for (int i = 0; i<10; i++)
		fscanf_s(savefile, "%d\n", &rank[i]);
	fclose(savefile);
}

void RankClass::FileSave() //������ ���� TOP 10�� ��ŷ��� �� ����
{
	FILE *savefile;
	fopen_s(&savefile, "rank.txt", "wt");

	for (int i = 0; i<10; i++) {
		if (rank[i] == 0)
			fprintf(savefile, "0\n");
		else
			fprintf(savefile, "%d\n", rank[i]);
	}
	fclose(savefile);
}