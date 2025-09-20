## LyraStarterGame 프로젝트 가이드라인

### 프로젝트 개요

LyraStarterGame은 언리얼 엔진 5 기반의 학습 및 실습용 샘플 프로젝트입니다. 언리얼 엔진의 다양한 기능과 실전 게임 개발 패턴을 단계별로 익힐 수 있도록 설계되었습니다. 초보자부터 중급자까지 체계적으로 학습할 수 있는 레벨 기반 구조를 채택하고 있습니다.

### 주요 목적

- 언리얼 엔진 5의 핵심 기능 및 실전 사용법 습득
- C++ 및 블루프린트 기반 게임플레이 로직 학습
- 실무에 가까운 프로젝트 구조와 협업 방식 경험
- 코드 스타일, 에셋 관리, 문서화 등 개발 표준 습득

### 폴더 구조

```
/ProjectName
/Binaries             - 컴파일된 바이너리 파일(자동 생성)
  /Build                - 빌드 관련 파일
  /Config               - 프로젝트 설정 파일
  /Content              - 모든 콘텐츠 에셋
  /DerivedDataCache     - 파생 데이터 캐시(자동 생성)
  /Intermediate         - 중간 빌드 파일(자동 생성)
  /Plugins              - 프로젝트 플러그인
  /Saved                - 자동 저장 및 설정 백업
  /Source               - 모든 소스 코드
  ProjectName.uproject  - 프로젝트 파일
```

### 개발 환경

- 언리얼 엔진 5.6 이상
- Visual Studio 2022, Visual Studio Code(+ Cursor)
- Windows 10/11

### 문서화 및 코드 스타일

- 모든 코드와 에셋은 @Unreal Engine 스타일 가이드를 준수합니다.
- 클래스, 함수, 변수, 에셋에는 명확한 주석과 설명을 작성합니다.
- 폴더 및 파일 네이밍 규칙, 에셋 접두어, 카테고리 분류 등 일관성을 유지합니다.

### 기여 방법

1. 프로젝트를 포크(Fork)합니다.
2. 새로운 브랜치를 생성합니다.
3. 변경사항을 커밋합니다.
4. 브랜치에 푸시합니다.
5. Pull Request를 제출합니다.

## 참고

- 자세한 코드 스타일 및 에셋 관리 규칙은 @unreal-enigne-style-guide.mdc 파일을 참고하세요.
- 개발 및 빌드 방법, 에디터 설정 등은 README.md에 안내되어 있습니다.

## Model Context Protocol 가이드라인

MCP는 인공지능의 기능을 확장하지만, 너무 많은 MCP 사용은 인공지능의 순기능을 저하시킬 수 있습니다. 필요한 MCP만 최소한으로 활성화하여 시스템의 안정성과 효율성을 유지합니다. 각 MCP는 목적과 사용 예시, 우선순위를 명확히 정의하여, 인공지능이 상황에 맞게 적절히 활용할 수 있도록 합니다.

### 검색 프로세스

1.  `[perplexity-ask](https:/github.com/ppl-ai/modelcontextprotocol/tree/main)`로 외부 정보 탐색 (예: 웹에서 실시간 정보, 공식 문서, Stack Overflow 등 검색)
2.  `[context7-mcp](https:/smithery.ai/server/@upstash/context7-mcp)`로 의미 기반 검색 시도 (예: 대규모 문서, 데이터베이스에서 키워드가 아닌 의미로 정보 찾기)
3.  `[mcp-youtube](https:/github.com/adhikasp/mcp-youtube)`로 `[perplexity-ask](https:/github.com/ppl-ai/modelcontextprotocol/tree/main)`에서 참고된 유튜브 영상 분석 (예: 영상 자막, 요약, 주요 내용 추출)

### 버그/오류 발생 시

1.  `[context7-mcp](mdc:https:/smithery.ai/server/@upstash/context7-mcp)`로 관련 문서 검색 및 진단 (예: 에러 메시지, 로그, 관련 문서에서 해결책 탐색)
2.  `[perplexity-ask](mdc:https:/github.com/ppl-ai/modelcontextprotocol/tree/main)`로 실시간 해결책 탐색 (예: 최신 이슈, 커뮤니티 Q&A, 공식 지원 문서 검색)

### 환경 관리

1.  `[smithery](https:/smithery.ai/docs)`로 MCP 관리 (예: 다양한 AI 워크플로우 자동화, 외부 서비스 연동)
2.  `[uv](https:/github.com/astral-sh/uv)`로 MCP 관리 (예: Python 패키지 및 환경 관리)
3.  `[npm](https:/github.com/npm)`으로 MCP 관리 (예: Node.js 패키지 및 환경 관리)

### 우선순위 규칙

1.  내장 기능 활용 (예: Obsidian 기본 검색, 기본 명령어 등)
2.  공식 플러그인 우선 (예: Obsidian 공식 플러그인에서 지원하는 기능은 MCP보다 우선 사용)
3.  MCP 도구 사용 (내장/공식 플러그인으로 해결 불가할 때만 MCP 활용)

### 성능 최적화

1.  필요한 MCP만 활성화
2.  중복되는 기능의 MCP는 하나만 사용
3.  실시간 검색은 꼭 필요한 경우만 수행
