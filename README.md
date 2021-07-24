# Linux_system_programming
리눅스 -  system call 구현해보면서 리눅스 배우기

# Linux

#
## * What is System programming?
   ## 개념소개
   #### 운영체제(OS)에 직접적으로 작동하는 프로그램을 만드는것
   #### * 리눅스에서 운영체제는 주로 커널(Kernel)을 말함.
   ####  커널(Kernel) : 다양한 기기들과 연결된 프로그램들의 모든 자원을 관리하고 보호하는 프로그램
   #### ? program VS Process
   #### • Processors(프로세서)
       − Program : 소스 코드에서 컴파일된 명령어의 집합
       - Processor(CPU) : 명령어를 실행하는 하드웨어
       (커널이 Processor에게 Programs를 할당함.)
   #### • Input/output
       − 커널을 통해서 들어오고 나가는 모든 데이터들.
   #### • System Resources
       − + Process management
       -     + Process : 실행중인 Program. 메모리, 파일, 다른 자원, 소켓, 디바이스 드라이버 등을 포함함.
   #### • Memory
       − 커널은 현재 사용되는 있는 메모리의 구역을 계속해서 감시함. 
       - 다른 프로세스로부터 손상을 입은 프로세스의 메모리를 보호함.
   #### • Devices
       − 어느 컴퓨터에나 연결할 수 있는 모든 종류의 디바이스들.
       − 커널이 디바이스에 접근하는 것을 도와줌
   #### • Timers
       − Timer에 의존하는 프로그램이 있음 ex) sleep, elapsed time,...
       - 커널이 타이머를 만듬. 그리고 프로세스에게 사용할 수 있도록 해줌.
   #### • Interprocess communication (IPC)
      − 컴퓨터간의 통신. 커널이 IPC를 지원해줌.
   #### •  Networking
      − 다른 컴퓨터가 나의 컴퓨터에 있는 프로세스에 접근하도록 한다. 또한 데이터 교환도 가능하다.
      - 리눅스에서는 Kernel이 서비스 해준다
      
 # 우리는 무엇이 목표인가? 
 ## 다양한 서비스들에 사용되는 프로그램을 만드는 방법을 배우는게 중요함.
   
 ### * About Linux
   #### ? Unix VS Lunux
      −  - Unix 
      -  - 60년대 후반에 AT&T 벨 연구소에서 개발된 OS. 
      -  - OS X(맥), Solaris, BSD 등으로 개발됨.
      -   
      -  - Linux
      -  - Linus Tovald가 개발하고 Richard Stallman이 GNU를 만듬.
      -  - Unix와 유사한 점이 많음. code base는 original Unix code와는 다름.
      
   #### The File System
     −  파일은 기본적으로 바이트의 연속된 값임
     −  파일의 Collections들은 Directories 안에 그룹화됨
     −  directory 그 자체로 파일임 (파일 시스템은 계층구조를 가짐)
   #### Absolute Path VS Relative Path
     − 둘다 Tree 구조를 따름  
     - 절대경로(Absolute Path)는 System root로부터 시작해서 파일이 어디에 있는지 나타냄.  ex) /proc/cpuinfo
     - 상대경로(Relative Path)는 현재 directory로부터 파일 시스템을 나타냄. ex) .././ff -> 상위폴더에 있는 ff 파일을 나타냄.
     
 ### * Linux Commands
   #### ls
     − directory contents를 list함.
     - ls -l 도 있음. 접근권한, 소유자, 파일 크기, 저장 날짜 등을 알 수 있음.
   #### mkdir, rmdir
     - directory를 만들거나 삭제함.
   #### cd
     - 현재 보고 있는 directory를 변경함
   #### cp
     - 파일을 다른 파일이나 디렉토리로 복사함
   #### mv
     - 파일을 다른 디렉토리로 옮김
     - 파일의 이름을 바꿈
   #### rm
     - 파일을 삭제함 (rm -r /home/test)를 하면 recursive하게 내용을 다 지울 수 있음.
   #### pwd
     - 현재 디렉토리의 경로를 출력함 (절대경로로 출력함)
   #### man 
     - 메뉴얼 페이지. ex) man ls 하면 ls에 대한 내용을 읽어볼 수 있음.
     
 ### * About vi
     - Text editor이자 standard Unix editor임
