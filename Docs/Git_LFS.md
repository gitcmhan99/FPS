# Unreal Engine GitHub Git LFS 설정 가이드

## 1. Git LFS란

Unreal Engine 프로젝트에서는 다음과 같은 대용량 바이너리 파일이 많이 사용됩니다.

* `.uasset`
* `.umap`
* `.fbx`
* `.png`
* `.wav`
* `.mp4`

일반 Git으로 이러한 파일을 관리하면 저장소 용량이 빠르게 증가하고, 바이너리 파일의 변경 이력이 비효율적으로 관리될 수 있습니다.

Git LFS는 대용량 파일 자체를 일반 Git 저장소에 직접 저장하지 않고 LFS 저장소를 통해 관리하는 기능입니다.

Unreal Engine 프로젝트에서는 `.uasset`과 `.umap`을 우선적으로 Git LFS 대상으로 설정하는 것을 권장합니다.

# 2. 준비 사항

다음 항목이 준비되어 있어야 합니다.

* Git 설치
* GitHub 저장소 생성
* Unreal Engine 프로젝트
* SourceTree 설치
* Git LFS 설치

SourceTree를 설치하면 Git LFS를 함께 사용할 수 있지만, 실제 설치 여부는 Git Console에서 확인하는 것이 가장 확실합니다.

# 3. Git LFS 설치 확인

Git Console을 실행합니다.

프로젝트 폴더로 이동합니다.

```bash
cd 프로젝트경로
```

Git LFS가 설치되어 있는지 확인합니다.

```bash
git lfs version
```

정상적으로 설치되어 있다면 다음과 같이 버전이 표시됩니다.

```text
git-lfs/3.x.x
```

버전이 정상적으로 출력되지 않는다면 Git LFS를 별도로 설치해야 합니다.

# 4. Git LFS 초기화

프로젝트 폴더에서 다음 명령을 실행합니다.

```bash
git lfs install
```

정상적으로 실행되면 다음과 비슷한 메시지가 출력됩니다.

```text
Git LFS initialized.
```

이 작업은 해당 PC의 Git에서 Git LFS를 사용할 수 있도록 초기화하는 과정입니다.

# 5. .gitattributes 설정

프로젝트 최상위 폴더에 `.gitattributes` 파일을 생성합니다.

프로젝트 구조는 다음과 같습니다.

```text
FPSProject
│
├── .gitignore
├── .gitattributes
├── .editorconfig
├── FPSProject.uproject
│
├── Config
├── Content
├── Source
└── Plugins
```

`.gitattributes`에는 Git LFS로 관리할 파일을 등록합니다.

## Unreal Engine 기본 설정

```gitattributes
# Unreal Engine Asset
*.uasset filter=lfs diff=lfs merge=lfs -text

# Unreal Engine Map
*.umap filter=lfs diff=lfs merge=lfs -text

# 3D Model
*.fbx filter=lfs diff=lfs merge=lfs -text

# Texture
*.png filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.jpeg filter=lfs diff=lfs merge=lfs -text
*.tga filter=lfs diff=lfs merge=lfs -text

# Audio
*.wav filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.ogg filter=lfs diff=lfs merge=lfs -text

# Video
*.mp4 filter=lfs diff=lfs merge=lfs -text
*.webm filter=lfs diff=lfs merge=lfs -text
```

# 6. Git Console에서 LFS 적용

`.gitattributes` 파일을 생성한 후 Git 상태를 확인합니다.

```bash
git status
```

`.gitattributes`가 변경된 파일로 표시되는지 확인합니다.

그 다음 파일을 추가합니다.

```bash
git add .gitattributes
```

프로젝트의 변경 사항도 함께 추가합니다.

```bash
git add .
```

커밋합니다.

```bash
git commit -m "Configure Git LFS"
```

GitHub에 Push합니다.

```bash
git push origin main
```

브랜치가 `develop`이라면 다음과 같이 사용합니다.

```bash
git push origin develop
```

# 7. LFS 파일 확인

현재 Git LFS가 관리하고 있는 파일을 확인할 수 있습니다.

```bash
git lfs ls-files
```

예를 들어 다음과 같이 표시됩니다.

```text
abc123 Content/FPS/Maps/FPSMap.umap
def456 Content/FPS/Character/BP_Player.uasset
```

이렇게 표시된다면 해당 파일은 Git LFS로 관리되고 있는 것입니다.

# 8. SourceTree에서 Git LFS 설정

SourceTree에서도 Git LFS를 사용할 수 있습니다.

SourceTree를 실행합니다.

프로젝트 저장소를 엽니다.

## Git LFS 설치 확인

상단 메뉴에서

```text
Tools
    Options
        Git
```

로 이동합니다.

Git LFS 관련 설정이 정상적으로 구성되어 있는지 확인합니다.

SourceTree에서 사용하는 Git과 Git Console에서 사용하는 Git이 서로 다를 수 있으므로 Git LFS 문제가 발생한다면 SourceTree의 Git 설정을 먼저 확인합니다.

# 9. SourceTree에서 .gitattributes 추가

프로젝트 루트에 `.gitattributes`를 생성합니다.

파일 내용은 다음과 같이 설정합니다.

```gitattributes
# Unreal Engine Asset
*.uasset filter=lfs diff=lfs merge=lfs -text

# Unreal Engine Map
*.umap filter=lfs diff=lfs merge=lfs -text

# 3D Model
*.fbx filter=lfs diff=lfs merge=lfs -text

# Texture
*.png filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.tga filter=lfs diff=lfs merge=lfs -text

# Audio
*.wav filter=lfs diff=lfs merge=lfs -text

# Video
*.mp4 filter=lfs diff=lfs merge=lfs -text
```

# 10. SourceTree에서 커밋

SourceTree의 작업 공간에서 변경 사항을 확인합니다.

다음 파일이 변경 사항에 표시되는지 확인합니다.

```text
.gitattributes
```

필요한 프로젝트 파일을 Stage에 추가합니다.

커밋 메시지를 입력합니다.

```text
Configure Git LFS
```

Commit을 실행합니다.

# 11. SourceTree에서 Push

커밋이 완료되면 Push를 실행합니다.

```text
Push
    Remote
        origin
```

현재 작업 중인 브랜치를 선택합니다.

예를 들어

```text
main
```

또는

```text
develop
```

을 선택하고 Push합니다.

# 12. 기존 파일을 LFS로 변경하는 경우

이미 `.uasset`이나 `.umap` 파일을 일반 Git으로 커밋한 상태라면 `.gitattributes`만 추가한다고 기존 파일의 Git 이력이 자동으로 LFS로 변경되는 것은 아닙니다.

기존 파일을 LFS로 변경하려면 다음 명령을 사용할 수 있습니다.

```bash
git lfs migrate import --include="*.uasset,*.umap"
```

주의해야 합니다.

이 명령은 기존 Git History를 변경할 수 있습니다.

따라서 이미 여러 개발자가 작업하고 있는 저장소에서는 함부로 실행하지 않습니다.

프로젝트를 처음 구성하는 단계라면 기존 커밋을 정리한 후 LFS를 적용하는 것이 가장 안전합니다.

# 13. 새로운 PC에서 Clone하는 경우

팀원이 처음 프로젝트를 내려받는 경우에는 Git LFS가 설치되어 있어야 합니다.

먼저 확인합니다.

```bash
git lfs version
```

설치되어 있다면 다음과 같이 프로젝트를 Clone합니다.

```bash
git clone 저장소주소
```

Clone이 완료되면 LFS 파일도 정상적으로 내려받아집니다.

필요한 경우 다음 명령으로 LFS 파일을 다시 받을 수 있습니다.

```bash
git lfs pull
```

# 14. SourceTree로 Clone하는 경우

SourceTree에서 GitHub 저장소를 Clone합니다.

```text
New
    Clone from URL
```

GitHub 저장소 주소를 입력합니다.

Clone이 완료된 후 프로젝트 폴더에서 Git LFS가 정상적으로 동작하는지 확인합니다.

Git Console에서 다음 명령을 실행합니다.

```bash
git lfs ls-files
```

`.uasset`과 `.umap` 파일이 표시되면 정상적으로 설정된 것입니다.

# 15. Unreal Engine 프로젝트에서 관리하지 않는 폴더

Git LFS를 사용하는 것과 별개로 다음 폴더들은 `.gitignore`를 통해 Git에서 제외해야 합니다.

```text
Binaries
DerivedDataCache
Intermediate
Saved
.vs
```

이 폴더들은 Git LFS로 관리하는 것이 아니라 Git 자체에서 제외합니다.

# 16. 최종 구조

최종적으로 Unreal Engine 프로젝트는 다음과 같이 구성합니다.

```text
FPSProject
│
├── .gitignore
│   └── Git에 올리지 않을 파일
│
├── .gitattributes
│   └── Git LFS로 관리할 파일
│
├── .editorconfig
│   └── 코드 작성 규칙
│
├── FPSProject.uproject
│
├── Config
│
├── Content
│   ├── Maps
│   ├── Character
│   ├── Environment
│   └── UI
│
├── Source
│
└── Plugins
```

# 17. Git과 Git LFS의 역할

```text
Git
│
├── Source
├── Config
├── .uproject
├── .gitignore
├── .gitattributes
└── 일반 텍스트 파일
│
└── Git LFS
    │
    ├── .uasset
    ├── .umap
    ├── .fbx
    ├── .png
    ├── .jpg
    ├── .tga
    ├── .wav
    └── .mp4
```

# 18. 설정 확인

최종적으로 다음 명령을 실행합니다.

```bash
git status
```

Git LFS 파일을 확인합니다.

```bash
git lfs ls-files
```

Git LFS 환경을 확인합니다.

```bash
git lfs env
```

세 가지 명령을 통해 Git과 Git LFS가 정상적으로 구성되었는지 확인할 수 있습니다.

# 19. 권장 작업 순서

```text
.gitignore 작성
        ↓
.editorconfig 작성
        ↓
Git Repository 생성
        ↓
Git LFS 설치 확인
        ↓
git lfs install
        ↓
.gitattributes 작성
        ↓
.uasset
.umap
대용량 바이너리 파일 LFS 설정
        ↓
Git Add
        ↓
Commit
        ↓
Push
        ↓
git lfs ls-files 확인
        ↓
다른 PC에서 Clone 테스트
```

# 20. 주의 사항

`.gitignore`와 `.gitattributes`는 서로 다른 역할을 합니다.

`.gitignore`는 Git에 올리지 않을 파일을 지정합니다.

`.gitattributes`는 Git에 올리되 Git LFS를 통해 관리할 파일을 지정합니다.

따라서 `.uasset`과 `.umap`을 `.gitignore`에 넣으면 안 됩니다.

```text
.uasset
.umap
```

은 Git LFS로 관리해야 하므로 `.gitattributes`에 등록합니다.

반대로 다음 폴더는 Git LFS가 아니라 `.gitignore`에서 제외합니다.

```text
Binaries
DerivedDataCache
Intermediate
Saved
.vs
```

Unreal Engine 프로젝트에서는 이 두 설정을 명확하게 분리하는 것이 중요합니다.
