## Running the Program
`input.txt`라는 파일에 그래프의 정보가 있을 때, 문제 1의 DFS를 수행하려면
아래와 같이 실행할 수 있습니다:
```
./run -p1 input.txt
```
혹은
```
./run --problem 1 input.txt
```

이때 1번과 2번의 경우 기본적으로 directed graph에서 실행되며, undirected
graph이 주어졌을 경우에는
```
./run -p1 -u input.txt
```
혹은
```
./run --problem 1 --undirected input.txt
```
와 같이 flag를 줄 수 있습니다.

그러나 3번의 MST와 4번의 Dijkstra's algorithm의 경우 flag와 무관하게 각각
undirected, directed graph로 실행됩니다.

2번 BFS와 4번 Dijkstra's algorithm의 경우에는 runtime에 source vertex를
입력받습니다.

출력의 경우, 기본적으로 만들어진 tree를 표현하기 위해 각 vertex의 parent를
표시합니다.

추가로 BFS와 DFS의 경우에는 vertex 방문 순서를, Dijkstra's algorithm의 경우에는
source로부터 각 vertex의 거리를 나타냅니다.


## Building Source
```
make
```

Tested on macOS 10.15.1 using clang-1100.0.33.12.
