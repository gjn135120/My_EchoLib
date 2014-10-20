.PHONY:clean
CC=g++
CFLAGS=-Wall -g -std=c++0x
BIN=libtiny.a
OBJS=MutexLock.o Condition.o \
	 Thread.o ThreadPool.o \
	 Timer.o TimerThread.o \
	 InetAddr.o Socket.o \
	 SocketIO.o TcpConnection.o \
	 EpollPoller.o TcpServer.o
$(BIN):$(OBJS)
	ar crsv $@  $^
	chmod +x $@
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o core tiny
