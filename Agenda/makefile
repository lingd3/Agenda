All:Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o
main:All Agenda.cpp
	g++ All Agenda.cpp -std=c++0x
Date.o: 
	g++ Date.h Date.cpp -std=c++0x -c
User.o:
	g++ User.h User.cpp -std=c++0x -c
Meeting.o: User.o Date.o
	g++ Meeting.h Meeting.cpp -std=c++0x -c
Storage.o: Meeting.o
	g++ Storage.h Storage.cpp -std=c++0x -c
AgendaService.o: Storage.o
	g++ AgendaService.h AgendaService.cpp -std=c++0x -c
AgendaUI.o: AgendaService.o
	g++ AgendaUI.h AgendaUI.cpp -std=c++0x -c
clean:
	rm *.o *.h.gch
