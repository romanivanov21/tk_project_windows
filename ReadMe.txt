������ ��� Windows
�����: ������ ����� ���������� (�)
���: 2014 - 2015

Solution tk_project_windows.sh �������� �������:
	- network_server_dll (����������, ������� �������� ���������� ��������� ������������������ �������� ������� ������� � ��������)
	- test_server (���������� ���������� ��� ������������ ���������� network_server_dll)
	- test_client (���������� ����������, ������������ ������ ������� ��� Windows, ��� ������������ network_server_dll)
	- crypt_gost_28147-89 (����������, ������� �������� ���������� ������������������ ��������� ���� 28147-89, ����������������� ��� - ������� ����_�_34_11_2012, ����� ������� �� ��������� ����� - �������)
	- gost_test (���������� ���������� ��� ������������ ���������� server_network_dll)
	- client_gost_test (���������� ����������, ����������� �������, ��� ������������ ���������� crypt_gost_28147-89)
	����� �����:
	- shared_code (�������� ����� ������������ �����, ������� ������������ �� ������ ��������)
	- import_library (����� � ������� ������������ ��� ������ �������)
	- documents_for_applications (����� � ����������� � ����������)

��� �������� ������ ������� ������������:
	- boost 1.57.0 (���������)
	- cryptopp562 (���������)
	- tinyxml_2_6_2 (���������)
	- Microsoft Visual Studio 2012

�������� ������ �������:
	1) ������� (http://www.boost.org/users/history/version_1_57_0.html) � ������� ���������� boost 1.57.0 ��� windows, �������� � ���������� (\tk_project_windows\import_library\boost_1_57_0)
	2) ������� (http://www.cryptopp.com) � ������� ���������� cryptopp562 ��� windows, �������� � ���������� (\tk_project_windows\import_library\cryptopp562)
	3) ������� � ������� ���������� tinyxml_2_6_2 ��� windows, �������� � ���������� (\tk_project_windows\import_library\tinyxml_2_6_2)
	4) ��������� solution tk_project_windows.sh � ������� �� ���������� �������:
		a) crypt_gost_28147-89
		b) network_server_dll
		c) gost_test
		d) client_gost_test
