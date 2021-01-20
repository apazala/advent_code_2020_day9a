#include <cstdio>
#include <cinttypes>
#include <unordered_map>

#define MAX_LINES 1000

int64_t values[MAX_LINES];

using namespace std;

int main()
{
	FILE *fin;

//#define DEBUG
#ifdef DEBUG
	char inputfile[] = "input1.txt";
	int preamble = 5;
#else
	char inputfile[] = "input.txt";
	int preamble = 25;
#endif // DEBUG



	fin = fopen(inputfile, "r");
	if (!fin) {
		fprintf(stderr, "Can't open input file\n");
		return 1;
	}

	int64_t val;
	int clines = 0;
	while (fscanf(fin, "%" SCNd64, &val) == 1) {
		values[clines] = val;
		clines++;
	}
	fclose(fin);

	unordered_map<int64_t, int> previous;
	int i = 0;
	int f;

	unordered_map<int64_t, int>::iterator ret;
	for (f = 0; f < preamble; f++) {
		val = values[f];
		ret = previous.find(val);
		if (ret == previous.end())
			previous[val] = 1;
		else
			ret->second++;
	}

	for (bool found = true; ; f++, i++) {
		val = values[f];

		found = false;
		for (int j = i; !found && j < f; j++) {
			int64_t cand1 = values[j];
			int64_t cand2 = val - cand1;
			if (cand2 < 0 || cand2 == cand1)continue;
			auto ret = previous.find(cand2);
			found = (ret != previous.end());
		}

		if (!found)
			break;

		//add f
		ret = previous.find(val);
		if (ret == previous.end())
			previous[val] = 1;
		else
			ret->second++;

		//delete i
		val = values[i];
		ret = previous.find(val);
		if (ret->second == 1)
			previous.erase(ret);
		else
			ret->second--;

	}

	printf("%" PRId64 "\n", values[f]);

	return 0;
}