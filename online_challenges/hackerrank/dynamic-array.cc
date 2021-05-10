int N, Q;
cin >> N >> Q;
vector < vector <int> > seqList; //(N,vector<int>(5));
seqList.resize(N);
int lastAnswer=0;

int type, x, y, seq;

for (int i=0; i< Q; i++)
{
    cin >> type >> x >> y;
    seq = (x^ lastAnswer) % N;

    if (type == 1)
    {
        seqList[seq].push_back(y)
    }
    else if (type == 2)
    {
        int idx = y % seqList[seq].size();
        lastAnswer = seqList[seq][idx];
        cout << lastAnswer << endl;
    }


}

