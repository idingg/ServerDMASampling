# ServerDMASampling
- Oracle DB 서버에서 시스템 및 데이터베이스의 정보를 수집
- 시스템 리소스 소모 최소화, DMA 사용
- 로그 실시간 압축
- SSL 암호화 전송

## 개요도
<img width="100%" src="https://github.com/jin-mh/rts/assets/139682515/c8f33526-28d8-4558-8446-4a88f84b1208"/>
<img width="100%" src="https://github.com/jin-mh/rts/assets/139682515/a26d1e61-52e9-4f73-bc6d-d74caadb1265"/>

# 기능 목록
## Server sampler(Oracle server)
- Oracle DBMS 및 SampingProcess와 통신하는 SQL*Plus 프로세스
- 시스템의 CPU, Memory, Disk 사용량 샘플링
- 오라클 DB의 실행중인 SQL Text를 DMA로 수집
- 기록된 로그를 파일로 출력
- LZ4 알고리즘으로 로그파일 실시간 압축
- 전송 요청 메세지를 받는 SSL 서버
- 전송 요청 시 로그파일을 Data gather로 전송하는 SSL 클라이언트

## Request client
- Server Sampler에게 조건이 포함된 요청 메세지 전송
- SSL 사용

## Data gather
- DB 서버에 압축돼 저장된 로그 파일을 수신
- SSL 사용
- LZ4 알고리즘으로 압축 해제 후 저장