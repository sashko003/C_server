#ifndef C_SERVER_MOUSE_ACTIVITIES_H_
#define C_SERVER_MOUSE_ACTIVITIES_H_

typedef union unMouseActivities
{
	int iCoords[2];
	struct {
		char chX[sizeof(int)];
		char chY[sizeof(int)];
		char chClickType[3];
	};
	char chMessage[sizeof(int) * 2 + 3];
} MouseActivities;

#endif // !C_SERVER_MOUSE_ACTIVITIES_H_

