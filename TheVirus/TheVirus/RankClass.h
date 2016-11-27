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

void RankClass::AddRank(int score) //게임이 끝난 후 사용자 이름과 시간을 랭킹에 저장
{
	rank[10] = score;

	RankSort();
	FileSave();
}

void RankClass::RankSort() //점수에 따라 랭크 정렬
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

void RankClass::FileLoad() //파일을 열어 저장되어있던 데이터를 불러옴
{
	FILE *savefile;

	fopen_s(&savefile, "rank.txt", "rt");

	if (savefile == NULL) { //파일이 없으면 새로 만들기
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

void RankClass::FileSave() //파일을 열어 TOP 10위 랭킹기록 후 저장
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