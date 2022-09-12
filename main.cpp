#include <SFML/Network.hpp>//для раб с сокетами
#include <iostream>//для ввода/вывода данных
#include <string>//для обработки строк
#include <windows.h>//для отслеживания нажатий клавиш

using namespace std;

int main()
{
	sf::TcpSocket socket;//создали сокет(объект типа TCPSocket
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();//узнаем наш локальный ip чтобы понимать куда посылать данные
		//ТСР сокет строится на связи клиента с сервером
	char type;//тип, который указывает пользователь(сервер или клиент
	cout << "Enter your type: [c]-client, [s]-server\n";
	cin >> type;
	//для разных типов разная реализация
	if (type == 's')//если сервер, то создаем объект тип ТСРlistener, котороый с помощью метода listen принимает новых пользователей
	{
		sf::TcpListener listener;//пока какой-нибудь клиент не подключится программа остановится на этом месте, либо будет ошибка подключения через время
		listener.listen(2000);//парамметром передаем виртуальный порт через который будут передаваться данные

		if (listener.accept(socket) != sf::Socket::Done)//с помощью функции accept принимаем клиента для обмена данными, если не выполняется, то выдаем ошибку
		{
			cout << "ERROR\n";
		}
	}

	else if (type == 'c')//для клиента. Подключаемся к серверу через метод connect
	{
		if (socket.connect(ip, 2000) != sf::Socket::Done)//передаем ip сервера и порт (тестируем на одном компе, поэтому передаем локальный ip
		{
			cout << "ERROR\n";
		}
	}

	string name;//после подключения к серверу вводим имя
	cout << "Enter yuor name: ";
	cin >> name;

	socket.setBlocking(false);//делаем сокет не блокирующимся, чтобы при передаче данных прог не останавливалась на этом месте, а возвращала статус выполнения метода

	string message = "";
	sf::Packet packet;//форма записи данных , посылаемых по сети в сформатированном виде

	while (true)//бесконечный цикл для ввода сообщений
	{
		if (GetAsyncKeyState(VK_ESCAPE))//если нажата клавища escape
		{
			cin >> message;
		}
		if (message != "")//если сообщение не пустое то передаем его в пакет
		{
			packet.clear();//сначала отчишаем пакет
			packet << name << message;//передаем информацию в пакет

			socket.send(packet);//отправлем полученный пакет через метода send
			message = "";//отчищаем сообщение
		}

		if (socket.receive(packet) == sf::Socket::Done)//для принятия данных используем метод recive (Если данные были приняты, то мы их извлекаем из пакета
		{
			string nameRec;
			string messageRec;

			packet >> nameRec >> messageRec;
			cout << nameRec << ": " << messageRec << endl;
		}
	}

}
