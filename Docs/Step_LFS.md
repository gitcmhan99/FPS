# Git LFS 설정

Unreal Engine 프로젝트의 대용량 파일을 Git LFS로 관리하기 위한 설정입니다.

## 처음 설정할 때

### Step 1. Git LFS 설치 확인

Git Console에서 프로젝트 폴더로 이동한 후 실행합니다.

```bash
git lfs version
```

정상적으로 버전이 표시되면 다음 단계로 진행합니다.

### Step 2. Git LFS 초기화

```bash
git lfs install
```

### Step 3. .gitattributes 확인

프로젝트 최상위 폴더에 `.gitattributes`가 있는지 확인합니다.

주요 Unreal Engine 파일은 다음과 같이 LFS로 설정합니다.

```gitattributes
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text
*.fbx filter=lfs diff=lfs merge=lfs -text
```

프로젝트에서 사용하는 Texture, Audio, Video 등의 대용량 파일도 필요에 따라 추가합니다.

### Step 4. Git 상태 확인

```bash
git status
```

`.gitattributes`가 변경 사항에 표시되는지 확인합니다.

### Step 5. Commit

SourceTree 또는 Git Console에서 Commit합니다.

```bash
git add .gitattributes
git commit -m "Configure Git LFS"
```

### Step 6. Push

GitHub 저장소로 Push합니다.

```bash
git push origin main
```

현재 작업 브랜치가 `develop`이라면

```bash
git push origin develop
```

### Step 7. LFS 적용 확인

```bash
git lfs ls-files
```

`.uasset`, `.umap` 등의 파일이 표시되면 Git LFS가 정상적으로 적용된 것입니다.

## SourceTree를 사용하는 경우

Git LFS 초기 설정은 Git Console에서 한 번 진행하는 것을 권장합니다.

```bash
git lfs install
```

이후 실제 Commit과 Push는 SourceTree를 사용해도 됩니다.

```text
Git Console
    ↓
git lfs install
    ↓
.gitattributes 확인
    ↓
SourceTree
    ↓
Commit
    ↓
Push
    ↓
git lfs ls-files로 확인
```

## 신규 개발자가 프로젝트를 받는 경우

### Step 1. Git LFS 설치 확인

```bash
git lfs version
```

### Step 2. 프로젝트 Clone

SourceTree 또는 Git Console을 이용해 Clone합니다.

### Step 3. LFS 파일 확인

```bash
git lfs ls-files
```

필요한 경우 다음 명령으로 LFS 파일을 다시 받습니다.

```bash
git lfs pull
```

## 주의

`.uasset`과 `.umap`은 `.gitignore`에 추가하면 안 됩니다.

Git에 포함하되 Git LFS를 통해 관리해야 합니다.

```text
.gitignore
    Git에서 제외할 파일

.gitattributes
    Git LFS로 관리할 파일
```

Unreal Engine의 `Binaries`, `DerivedDataCache`, `Intermediate`, `Saved` 등은 Git LFS가 아니라 `.gitignore`에서 제외합니다.

## 전체 작업 순서

```text
.gitignore
    ↓
.editorconfig
    ↓
.gitattributes
    ↓
Git LFS 설치 확인
    ↓
git lfs install
    ↓
Commit
    ↓
Push
    ↓
git lfs ls-files
    ↓
LFS 정상 적용 확인
```

상세한 Git Console 및 SourceTree 사용 방법은 아래 내용을 참고합니다.

## 상세 설정

이 문서의 이후 내용에서 Git Console과 SourceTree를 이용한 Git LFS 설정 방법을 확인합니다.
