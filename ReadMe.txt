Сервер для Windows
Автор: Иванов Роман Витальевич (с)
Год: 2014 - 2015

Solution tk_project_windows.sh содержит проекты:
	- network_server_dll (библиотека, которая содержит реализацию основного криптографического протокла общения сервера с клиентом)
	- test_server (консольное приложение для тестирования библиотеки network_server_dll)
	- test_client (консольное приложение, эмулируюущее работу клиента под Windows, для тестирования network_server_dll)
	- crypt_gost_28147-89 (библиотека, которая содержит реализацию криптографического алгоритма ГОСТ 28147-89, криптографической хэш - функции ГОСТ_Р_34_11_2012, обмен ключами по протоколу Диффи - Хелмана)
	- gost_test (консольное приложение для тестирования библиотеки server_network_dll)
	- client_gost_test (консольное приложение, эммулирущее клиента, для тестирования библиотеки crypt_gost_28147-89)
	Общие папки:
	- shared_code (содержит общие заголовочные файлы, которые используются во многих проектах)
	- import_library (папка с нужными библиотеками для сборки проекта)
	- documents_for_applications (папка с документами и описаниями)

Для успешной сборки проекта понадобиться:
	- boost 1.57.0 (собранное)
	- cryptopp562 (собранное)
	- tinyxml_2_6_2 (собранное)
	- Microsoft Visual Studio 2012

Порядрок сборки проекта:
	1) скачать (http://www.boost.org/users/history/version_1_57_0.html) и собрать библиотеку boost 1.57.0 для windows, положить в директорию (\tk_project_windows\import_library\boost_1_57_0)
	2) скачать (http://www.cryptopp.com) и собрать библиотеку cryptopp562 для windows, положить в директорию (\tk_project_windows\import_library\cryptopp562)
	3) скачать и собрать библиотеку tinyxml_2_6_2 для windows, положить в директорию (\tk_project_windows\import_library\tinyxml_2_6_2)
	4) запустить solution tk_project_windows.sh и собрать по следующему порядку:
		a) crypt_gost_28147-89
		b) network_server_dll
		c) gost_test
		d) client_gost_test
