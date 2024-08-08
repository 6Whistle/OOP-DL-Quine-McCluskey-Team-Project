#include "link.h"

void FiletoData(Link*, Link*, unsigned short& bit_length);

int main()
{

	Link* allhead = new Link();		//dont care�װ� minterm���� ��� �����ϴ� ��ũ�� ����Ʈ ����
	Link* minhead = new Link();		//minterm���� �����ϴ� ��ũ�� ����Ʈ ����
	Link* PI = new Link();			//prime implicant�� ���� �� ��ũ�� ����Ʈ ����
	unsigned short bit_length = 0;
	int trans = -1;

	FiletoData(allhead, minhead, bit_length);		//input_minter.txt �Է¹޾� ����Ʈ�� �����ϴ� �Լ�
	cout << "Please check result.txt file.\nThank you.\n";
	allhead->Find(PI, bit_length);			//prime implicant�� ã�� �޼ҵ� ȣ��

	delete allhead;			//dont care�װ� minterm�� ������ ����Ʈ �Ҵ� ����

	Pos* pm = new Pos();

	pm->addLinkToPos(PI, minhead, bit_length);		//Pi�� product of sums�� ����� �޼ҵ�

	delete minhead;		//minhead ����Ʈ ���� �Ҵ�����
	delete PI;			//pi����Ʈ ���� �Ҵ� ����

	pm->combinePos(bit_length);						//POS ���� �� �й� �޼ҵ�
	pm->FindMinSums(trans, bit_length)->PtoFile(trans, bit_length);			//�й谡 ���� ������ ������ minterm�� �����ϴ� �������̱⶧���� transistor�� ���� ���� �������� ������ �Լ�

	

	pm->getHead()->getProduct()->getHead()->deletePlus();
	delete pm->getHead()->getProduct()->getHead();
	delete pm->getHead();
	delete pm;


	return 0;
}


void FiletoData(Link* allhead, Link* minhead, unsigned short& bit_length)
{
	ifstream fin;	

	fin.open("input_minterm.txt");	
	
	if (fin.fail())		//���Ͽ��⸦ �������� ���
	{
		cerr << "file open error\n";			//���� �޼��� ���
		exit(100);								//���α׷� ����
	}

	char* binary;								
	char MorD;
	fin >> bit_length;
	++bit_length;
	binary = new char[bit_length];			//binary�� ������ ���ڿ� �Էµ� bit length��ŭ �����Ҵ�

	while (!fin.eof())
	{
		fin >> MorD;
		fin >> binary;
		if (strcmp(binary, "") == 0)
			break;
		if (MorD == 'm' || MorD == 'M')
		{
			allhead->addNode(bit_length, binary);			//���� minterm�� ��� allhead�� ����
			minhead->addNode(bit_length, binary);			//���� minterm�� ��� minhead�� ����
		}
		else if (MorD == 'd'|| MorD == 'D')
		{
			allhead->addNode(bit_length, binary);			//���� dont care�� ��� allhead�� ����
		}
	}

	delete[] binary;

	fin.close();											//���� ����

	return;
}