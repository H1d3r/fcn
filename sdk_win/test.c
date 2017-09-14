#include "fcn/fcn.h"
#include <conio.h>

#pragma comment(lib, "fcn/fcn.lib")
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsd;

	WSAStartup(MAKEWORD(2, 2), &wsd);

	FcnSetUid("FCN_0001");
	FcnSetHost("s1.xfconnect.com", 5000);
	FcnSetUser("fcn");
	FcnSetPass("fcnpass");
	FcnSetRouteMode(FALSE);
	FcnStartConnect("SERVER01");

	while (!kbhit()) {
		int Status, SndKbps, RcvKbps;
		char* desc, *status_desc[] = { "���ӹر�", "TCP���ӳɹ�", "TLS���ӳɹ�", "��������ѯ�ɹ�",
			"��������֤�ɹ�", "���������ӳɹ�" };

		SndKbps = RcvKbps = 0;
		FcnGetLinkKbps(&SndKbps, &RcvKbps);

		Status = FcnGetStatus();

		printf("\r%64s\r", " ");

		if (Status < 0) {
			desc = status_desc[-Status];
			printf("Status:%s error waiting...", desc, SndKbps, RcvKbps);
		} else {
			desc = status_desc[Status];
			printf("Status:%s up:%d KBps down:%d KBps", desc, SndKbps, RcvKbps);
		}

		Sleep(100);
	}

	FcnStopConnect();

    return 0;
}

