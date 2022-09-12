#include <SFML/Network.hpp>//��� ��� � ��������
#include <iostream>//��� �����/������ ������
#include <string>//��� ��������� �����
#include <windows.h>//��� ������������ ������� ������

using namespace std;

int main()
{
	sf::TcpSocket socket;//������� �����(������ ���� TCPSocket
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();//������ ��� ��������� ip ����� �������� ���� �������� ������
		//��� ����� �������� �� ����� ������� � ��������
	char type;//���, ������� ��������� ������������(������ ��� ������
	cout << "Enter your type: [c]-client, [s]-server\n";
	cin >> type;
	//��� ������ ����� ������ ����������
	if (type == 's')//���� ������, �� ������� ������ ��� ���listener, �������� � ������� ������ listen ��������� ����� �������������
	{
		sf::TcpListener listener;//���� �����-������ ������ �� ����������� ��������� ����������� �� ���� �����, ���� ����� ������ ����������� ����� �����
		listener.listen(2000);//����������� �������� ����������� ���� ����� ������� ����� ������������ ������

		if (listener.accept(socket) != sf::Socket::Done)//� ������� ������� accept ��������� ������� ��� ������ �������, ���� �� �����������, �� ������ ������
		{
			cout << "ERROR\n";
		}
	}

	else if (type == 'c')//��� �������. ������������ � ������� ����� ����� connect
	{
		if (socket.connect(ip, 2000) != sf::Socket::Done)//�������� ip ������� � ���� (��������� �� ����� �����, ������� �������� ��������� ip
		{
			cout << "ERROR\n";
		}
	}

	string name;//����� ����������� � ������� ������ ���
	cout << "Enter yuor name: ";
	cin >> name;

	socket.setBlocking(false);//������ ����� �� �������������, ����� ��� �������� ������ ���� �� ��������������� �� ���� �����, � ���������� ������ ���������� ������

	string message = "";
	sf::Packet packet;//����� ������ ������ , ���������� �� ���� � ���������������� ����

	while (true)//����������� ���� ��� ����� ���������
	{
		if (GetAsyncKeyState(VK_ESCAPE))//���� ������ ������� escape
		{
			cin >> message;
		}
		if (message != "")//���� ��������� �� ������ �� �������� ��� � �����
		{
			packet.clear();//������� �������� �����
			packet << name << message;//�������� ���������� � �����

			socket.send(packet);//��������� ���������� ����� ����� ������ send
			message = "";//�������� ���������
		}

		if (socket.receive(packet) == sf::Socket::Done)//��� �������� ������ ���������� ����� recive (���� ������ ���� �������, �� �� �� ��������� �� ������
		{
			string nameRec;
			string messageRec;

			packet >> nameRec >> messageRec;
			cout << nameRec << ": " << messageRec << endl;
		}
	}

}
