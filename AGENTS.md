# LyraStarterGameClone - 범용 프로젝트 가이드

## 프로젝트 개요

언리얼 엔진 5.6 기반의 Lyra Starter Game 클론 프로젝트입니다. C++과 블루프린트를 활용한 모던 게임 개발 학습을 목적으로 합니다.

## 코딩 스타일 및 규칙 참조

작업 시 반드시 다음 문서들을 참고해주세요:

### 핵심 가이드라인

- `@.cursor/rules/instructions/cpp-instructions.mdc` - C++ 코딩 스타일
- `@.cursor/rules/instructions/ue5-instructions.mdc` - 언리얼 엔진 5 개발 규칙
- `@.cursor/rules/instructions/markdown-instructions.mdc` - 마크다운 문서 작성 규칙
- `@.cursor/rules/project-instructions.mdc` - 프로젝트 전반 지침

### 프롬프트 템플릿

- `@.cursor/rules/prompts/git-prompt.mdc` - Git 커밋 메시지 가이드라인
- `@.cursor/rules/prompts/translation-prompt.mdc` - 번역 작업 가이드라인
- `@.cursor/rules/prompts/obsidian-external-link-conversion-prompt.mdc` - 링크 변환 규칙

## 작업 템플릿

### C++ 클래스 생성 시

```
@.cursor/rules/instructions/cpp-instructions.mdc @.cursor/rules/instructions/ue5-instructions.mdc
위 가이드라인을 준수해서 새로운 [클래스명] 클래스를 생성해줘.
- 언리얼 엔진 네이밍 규칙 (A*, U*, F* 접두사)
- 탭 문자 사용
- 적절한 주석 및 문서화
```

### 문서 작성 시

```
@.cursor/rules/instructions/markdown-instructions.mdc
이 가이드라인에 따라 [문서명] 문서를 작성해줘.
- 일관된 마크다운 스타일
- 적절한 제목 구조
- 명확한 설명
```

### Git 커밋 시

```
@.cursor/rules/prompts/git-prompt.mdc
이 가이드라인에 따라 커밋 메시지를 작성해줘.
- Conventional Commits 규칙
- 한국어 설명
- 적절한 유형 분류
```
