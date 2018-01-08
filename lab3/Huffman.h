
using namespace std;
const unsigned int n = 256; //�ַ���

const unsigned int m = 256 * 2 - 1; //�������


struct HTNode { //ѹ����Huffman�����

	unsigned long weight; //�ַ�Ƶ�ȣ�Ȩֵ��

	unsigned int parent, lchild, rchild;

};


struct Buffer { //�ֽڻ���ѹ����Huffman�� 

	char ch; //�ֽ�

	unsigned int bits; //ʵ�ʱ�����    

};


class HuffmanTree { //Huffman�� 

public:

	void Code(); //����

	void UnCode(); //����

private:

	HTNode HT[m + 1]; //������(HT[1]��HT[m])

	char Leaf[n + 1]; //Ҷ����Ӧ�ַ�(leaf[1]��leaf[n])

	char *HuffmanCode[n + 1]; //Ҷ����Ӧ����(*HuffmanCode[1]��*HuffmanCode[n])

	unsigned int count; //Ƶ�ȴ�������ַ���    

	unsigned int char_index[n];  //�ַ���Ӧ�����������±�(char_index[0]��char_index[n-1])

	unsigned long size;  //��ѹ���ļ�����

	FILE *infp, *outfp; //����/���ļ�

	Buffer buf; //�ַ�����

	void Stat(); //ͳ���ַ�����Ƶ�Ȳ����˵�Ƶ��Ϊ����ַ�

	//��HT[0]~HT[k]��ѡ��parentΪ-1����ֵ��С���������s1,s2

	void Select(unsigned int k, unsigned int &s1, unsigned int &s2);

	void Write(unsigned int bit); //��outfp��д��һ������

	void Write(unsigned int num, unsigned int k);//��outfp��д��k������

	void WriteToOutfp(); //ǿ��д��outfp

	void Read(unsigned int &bit); //��infp�ж���һ������

	void Read(unsigned int &num, unsigned int k);//��infp�ж���k������

	int  NToBits(unsigned int num); //0~num֮��������ö���λ��ʾ���������λ��

	void CreateFromCodeFile(); //�ɱ����ļ��д洢�����ṹ����Huffman��

	//�ɱ�ѹ���ļ�����Huffman��,�����ṹ��������ļ����ļ�ͷ����,����ÿ���ַ���Huffman����

	void CreateFromSourceFile();

};


void HuffmanTree::Code() //����

{

	char infName[256], outfName[256];

	cout << "Please input source file name(size less than 4GB):";  //��ѹ���ļ����GB

	cin >> infName;

	if ((infp = fopen(infName, "rb")) == NULL) {

		cout << "Can not open file:" << infName << endl;

		exit(1);

	}

	if (feof(infp) != 0) {

		cout << "Empty source file:" << infName << endl;

		exit(1);

	}

	cout << "Please input code file name:";

	cin >> outfName;

	if ((outfp = fopen(outfName, "wb")) == NULL) {

		cout << "Can not open file:" << outfName << endl;

		exit(1);

	}

	cout << "Pocessing..." << endl;

	unsigned char ch;

	unsigned int i, c;

	for (i = 0; i <= n; i++)HuffmanCode[i] = NULL;

	CreateFromSourceFile();

	rewind(infp);

	ch = fgetc(infp);

	while (feof(infp) == 0) {

		c = char_index[ch];

		for (i = 0; i < strlen(HuffmanCode[c]); i++) {

			if (HuffmanCode[c][i] == '0')Write(0);

			else Write(1);

		}

		ch = fgetc(infp);

	}

	WriteToOutfp();

	fclose(infp); fclose(outfp);

	cout << "Process end." << endl << endl;

}


void HuffmanTree::UnCode()

{

	char infName[256], outfName[256];

	cout << "Please input code file name:";

	cin >> infName;

	if ((infp = fopen(infName, "rb")) == NULL) {

		cout << "Can not open file:" << infName << endl;

		exit(1);

	}

	if (feof(infp) != 0) {

		cout << "Empty code file:" << infName << endl;

		exit(1);

	}

	cout << "Please input target file name:";

	cin >> outfName;

	if ((outfp = fopen(outfName, "wb")) == NULL) {

		cout << "Can not open file:" << outfName << endl;

		exit(1);

	}

	cout << "Pocessing..." << endl;

	unsigned int bit, c, i;

	CreateFromCodeFile(); //����Huffman��

	Read(bit);

	for (i = 0; i < size; i++) {

		c = 2 * count - 1; //2*count-1Ϊ�������±�

		while ((HT[c].lchild != 0 || HT[c].rchild != 0) && (feof(infp) == 0)) {

			if (bit == 0)c = HT[c].lchild;

			else c = HT[c].rchild;

			Read(bit);

		}

		fputc(Leaf[c], outfp); //���ַ�д��outfp��

	}

	fclose(infp); fclose(outfp);

	cout << "Process end." << endl << endl;

}


void HuffmanTree::Stat()

//ͳ���ַ�����Ƶ�Ȳ����˵�Ƶ��Ϊ����ַ�

{

	unsigned int i, cha;

	for (i = 1; i <= n; i++)HT[i].weight = 0;

	size = 0;

	rewind(infp);

	cha = fgetc(infp);

	while (feof(infp) == 0) //ͳ���ַ�����Ƶ��

	{

		HT[cha + 1].weight++;

		size++;

		cha = fgetc(infp);

	}

	count = 0;

	for (cha = 0; cha < n; cha++) { //���˵�Ƶ��Ϊ����ַ�

		if (HT[cha + 1].weight > 0) {

			count++;

			Leaf[count] = cha;

			HT[count].weight = HT[cha + 1].weight;

			char_index[cha] = count;

		}

	}

}


void HuffmanTree::Select(unsigned int k, unsigned int &s1, unsigned int &s2)

{//s1,s2ΪȨֵ��С�ĸ�,��s1��ȨֵС��s2��Ȩֵ

	unsigned int root_count = 0; //�������;

	unsigned int root_index[n]; //������±�;

	unsigned int tem, i, j;

	for (i = 1; i <= k; i++)

		if (HT[i].parent == 0)

			root_index[root_count++] = i;

	s1 = root_index[0]; s2 = root_index[1];

	if (HT[s1].weight > HT[s2].weight) {

		tem = s1; s1 = s2; s2 = tem;

	}

	for (i = 2; i < root_count; i++) {

		j = root_index[i];

		if (HT[j].weight < HT[s2].weight) {

			s2 = j;

			if (HT[s1].weight > HT[s2].weight) {

				tem = s1; s1 = s2; s2 = tem;

			}

		}

	}

}


void HuffmanTree::Write(unsigned int bit) //��outfp��д��һ������

{

	buf.bits++;

	buf.ch = (buf.ch << 1) + bit;

	if (buf.bits == 8) {  //����������,д��outfp

		fputc(buf.ch, outfp);

		buf.bits = 0;

		buf.ch = 0;

	}

}


void HuffmanTree::Write(unsigned int num, unsigned int k) //��outfp��д��k������

{

	Stack<unsigned int> s;

	unsigned int i, bit;

	for (i = 1; i <= k; i++) {

		s.push(num & 1);

		num = (num >> 1);

	}

	for (i = 1; i <= k; i++) {

		s.top(bit);

		Write(bit);

		s.pop();

	}

}


void HuffmanTree::WriteToOutfp() //ǿ��д��outfp

{

	unsigned int l = buf.bits;

	if (l > 0)

		for (unsigned int i = 0; i < 8 - l; i++)Write(0);

}


void HuffmanTree::Read(unsigned int &bit) //��infp�ж���һ������

{

	if (buf.bits == 0) {

		buf.ch = fgetc(infp);

		buf.bits = 8;

	}

	bit = (buf.ch & 128) >> 7;

	buf.ch = buf.ch << 1;

	buf.bits--;

}


void HuffmanTree::Read(unsigned int &num, unsigned int k) //��infp�ж���k������

{

	unsigned int bit;

	num = 0;

	for (unsigned int i = 0; i < k; i++) {

		Read(bit);

		num = (num << 1) + bit;

	}

}


int HuffmanTree::NToBits(unsigned int num) //0~num֮��������ö���λ��ʾ�����λ��

{

	unsigned int l = 0, power = 1;

	while (power <= num) {

		l++; power = power * 2;

	}

	return l;

}


void HuffmanTree::CreateFromCodeFile() //�ɱ����ļ��д洢�����ṹ����Huffman��

{

	buf.bits = 0; //��ջ�����

	buf.ch = 0;

	unsigned int num, l, i;

	rewind(infp);

	fread(&size, sizeof(unsigned long), 1, infp);

	Read(count, 8);

	count = count + 1;

	for (i = 1; i <= count; i++)

		fread(&Leaf[i], sizeof(char), 1, infp);

	l = NToBits(2 * count - 1);

	for (i = 1; i <= count; i++) {

		HT[i].lchild = 0;

		HT[i].rchild = 0;

	}

	for (i = count + 1; i <= 2 * count - 1; i++) {

		HT[i].lchild = (Read(num, l), num);

		HT[i].rchild = (Read(num, l), num);

	}

}


void HuffmanTree::CreateFromSourceFile()

//�ɱ�ѹ���ļ�����Huffman��,�����ṹ��������ļ����ļ�ͷ����,����ÿ���ַ���Huffman����

{

	Stat();//ͳ���ַ�����Ƶ�Ȳ����˵�Ƶ��Ϊ����ַ�

		//�ɱ�ѹ���ļ�����Huffman��

	unsigned int i, s1, s2;

	for (i = 1; i <= count; i++)HT[i].parent = HT[i].lchild = HT[i].rchild = 0;

	for (i = count + 1; i <= 2 * count - 1; i++) {//����Huffman��

		Select(i - 1, s1, s2);          //ѡ��parentΪ��Ȩֵ��С���������s1,s2

		HT[s1].parent = HT[s2].parent = i;

		HT[i].parent = 0; HT[i].lchild = s1; HT[i].rchild = s2;

		HT[i].weight = HT[s1].weight + HT[s2].weight;

	}


	//�����ṹ��������ļ����ļ�ͷ����

	unsigned int l;

	buf.bits = 0;    //��ջ�����

	buf.ch = 0;

	rewind(outfp);

	fwrite(&size, sizeof(unsigned int), 1, outfp);

	Write(count - 1, 8);

	for (i = 1; i <= count; i++)

		fwrite(&Leaf[i], sizeof(char), 1, outfp);

	l = NToBits(2 * count - 1);

	for (i = count + 1; i <= 2 * count - 1; i++) {

		Write(HT[i].lchild, l);

		Write(HT[i].rchild, l);

	}

	//��ÿ���ַ���Huffman����

	unsigned int start, c, f;

	char *cd;                 //������ʱ����

	for (i = 1; i <= n; i++)

		if (HuffmanCode[i] != NULL) {

			delete[]HuffmanCode[i];  //�ͷŴ洢�ռ�

			HuffmanCode[i] = NULL;

		}

	cd = new char[count];       //���������Ĺ����ռ�

	cd[count - 1] = '\0';         //���������

	for (i = 1; i <= count; i++) {    //��λ��Huffman����

		start = count - 1;        //���������λ��

		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[c].parent) //��Ҷ���������

			if (HT[f].lchild == c)cd[--start] = '0';

			else cd[--start] = '1';

			HuffmanCode[i] = new char[count - start]; //Ϊ��i���ַ��������ռ�

			strcpy(HuffmanCode[i], &cd[start]); //��cd���Ʊ��뵽HuffmanCode

	}

	delete[]cd;



}
