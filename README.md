# ServerDMASampling
Oracle RDBMS 서버에서 시스템 및 데이터베이스의 정보 로그를 수집 및 압축, 암호화 전송하는 에이전트 프로그램

## 주요 기능
- Oracle RDBMS server sampler
  - Oracle SQL*Plus comunication thread 
    - Oracle RDBMS의 SQL*Plus 프로세스와 Samping Process 간 통신
  - System information sampling thread
    - 시스템의 CPU, Memory, Disk 사용량 샘플링
  - Database information sampling thread
    - Oracle RDBMS의 실행중인 SQL Text 수집
  - Logging thread
    - LZ4 알고리즘으로 로그파일 실시간 압축
    - 기록된 로그를 파일로 출력
  - SSL server thread
    - 로그 파일 전송 요청 메세지를 받는 SSL 서버
    - 로그 파일 전송 요청 시 로그파일을 Data gatherer로 전송하는 SSL 클라이언트

- Request client
  - Server Sampler에게 조건이 포함된 요청 메세지 전송
  - SSL 사용

- Data gatherer
  - DB 서버에 압축돼 저장된 로그 파일을 수신
  - SSL 사용
  - LZ4 알고리즘으로 압축 해제 후 파일로 출력

## 사용 기술
- 프로그래밍 언어: <img src="https://img.shields.io/badge/GNU C99-00599C?logo=c&logoColor=white">
- 운영체제: <img src="https://custom-icon-badges.demolab.com/badge/Oracle%20Linux 7.9-F80000?logo=oracle&logoColor=white">
- DBMS: <img src="https://custom-icon-badges.demolab.com/badge/Oracle%20Database 21c XE-F80000?logo=oracle&logoColor=white">
- 암호화: <img src="https://img.shields.io/badge/OpenSSL-721412?style=flat&logo=openssl&logoColor=white">
- 압축: <img src="https://img.shields.io/badge/LZ4-ffffff?style=flat&logo=&logoColor=white">

## 개요도
<img width="100%" src="https://github.com/jin-mh/rts/assets/139682515/c8f33526-28d8-4558-8446-4a88f84b1208"/>
<img width="100%" src="https://github.com/jin-mh/rts/assets/139682515/a26d1e61-52e9-4f73-bc6d-d74caadb1265"/>

## 실행 화면
- Oracle RDBMS server sampler
- 작업 스레드 실행시간, sleep 시간, sleep 제한시간, 프로그램 실행시간, 메모리 할당 크기, 실행중인 SQL 수 등
- 지정 시간마다 압축하여 저장한 로그 파일 정보
<img width="640" alt="1" src="https://github.com/user-attachments/assets/d2bd3ed9-1bd8-4ab5-bdf8-9f188a0a8c7d" />

- 로그파일 출력 내용
<img width="640" alt="2" src="https://github.com/user-attachments/assets/0cb1abad-73a1-45d6-a168-4e8df37ca48a" />

- 로그파일 중 오라클 공유 메모리 추출 내용
<img width="640" alt="4" src="https://github.com/user-attachments/assets/d4052b3d-76e8-42e7-becf-11b30ccb8eea" />

- Request client
- 로그 파일 전송 요청 송신 시 Request client의 표준 출력 내용
- Epoch time 1693862560 - 1693862680 사이의 로그 요청
<img width="453" height="111" alt="5" src="https://github.com/user-attachments/assets/3dab350d-239d-4c32-9f76-d043a2b95345" />

- 로그 파일 전송 요청 수신 시 Oracle RDBMS server sampler - SSL server thread의 표준 출력 내용
- Epoch time 1693862560 - 1693862680 사이의 로그 요청 메세지 수신
<img width="640" alt="6" src="https://github.com/user-attachments/assets/44ae70fa-cdcd-4e55-b1f2-a4e877644dfc" />

- 로그파일 수신 후 파일 목록
<img width="513" height="312" alt="7" src="https://github.com/user-attachments/assets/6c2da30a-91bd-46f4-abd2-67ca11abc3b4" />
