# ModuleAndPlugin

언리얼 엔진에서 **C++ 모듈**과 **플러그인**을 직접(수동으로) 구성하는 방법을 학습하기 위한 샘플 프로젝트입니다.
Third Person(C++) 템플릿을 기반으로, 별도 모듈·플러그인을 추가하고 모듈 간 상호작용을 구현했습니다.

- **엔진 버전:** Unreal Engine 5.8
- **템플릿:** Games > Third Person (C++, Scalable)

---

## 아키텍처 개요

```
ModuleAndPlugin/
├── ModuleAndPlugin.uproject          # 모듈/플러그인 등록
├── Source/
│   ├── ModuleAndPlugin/              # ① 주 게임 모듈 (Primary)
│   │   ├── ModuleAndPluginCharacter.*  # 캐릭터: Test/Temporary 참조
│   │   └── ...
│   ├── Test/                         # ② 사용자 추가 모듈
│   │   ├── Test.Build.cs
│   │   ├── Test.cpp                  # IMPLEMENT_MODULE(FDefaultModuleImpl, Test)
│   │   ├── TestActor.*               # BeginPlay에서 로그/메시지 출력
│   │   └── ...
│   ├── ModuleAndPlugin.Target.cs     # ExtraModuleNames에 Test 등록
│   └── ModuleAndPluginEditor.Target.cs
└── Plugins/
    └── Temporary/                    # ③ 독립 플러그인
        ├── Temporary.uplugin
        └── Source/Temporary/
            ├── Temporary.Build.cs
            ├── Public/
            │   ├── Temporary.h        # FTemporaryModule : IModuleInterface
            │   └── CharacterData.h    # UCharacterData : UObject (도전 과제)
            └── Private/
                ├── Temporary.cpp      # Startup/Shutdown + IMPLEMENT_MODULE
                └── CharacterData.cpp
```

### ① 주 게임 모듈 — `ModuleAndPlugin`
Third Person 템플릿의 기본 게임 모듈. `Test`, `Temporary` 모듈을 **Private 종속성**으로 참조합니다.

### ② 사용자 모듈 — `Test`
- `IMPLEMENT_MODULE(FDefaultModuleImpl, Test)` 로 동작하는 일반 런타임 모듈.
- `.uproject`에 `LoadingPhase: PreDefault` 로 등록되어 주 모듈보다 먼저 로드됩니다.
- `ATestActor` 는 `BeginPlay`에서 화면에 메시지를 출력하며, 주 모듈의 캐릭터가 `SpawnActor`로 생성합니다.

### ③ 독립 플러그인 — `Temporary`
- `FTemporaryModule : public IModuleInterface` 를 구현해 `StartupModule` / `ShutdownModule` 에서 로그를 남깁니다.
- `IMPLEMENT_MODULE(FTemporaryModule, Temporary)` 로 DLL 진입점을 등록합니다.
- 콘텐츠 폴더(`Content`)를 포함할 수 있는 재사용 가능한 패키지 구조입니다.

---

## 모듈 종속성 핵심 정리

| 구분 | 사용 위치 | 비고 |
|------|-----------|------|
| `PublicDependencyModuleNames`  | 헤더(.h) + 소스(.cpp) | 다른 모듈에 타입을 노출할 때 |
| `PrivateDependencyModuleNames` | 소스(.cpp)에서만      | 컴파일 의존성 최소화 |

- 모듈을 다른 모듈에서 참조하려면 클래스에 `MODULENAME_API` 매크로 필요 (`TEST_API`, `TEMPORARY_API`).
- 모든 모듈은 `.cpp` 전역에 `IMPLEMENT_MODULE` 이 **정확히 1번** 있어야 로드됩니다.

---

## 도전 과제 — `UCharacterData`

Temporary 플러그인에 `UObject` 자식 클래스를 만들어 캐릭터 데이터 저장용으로 사용합니다.

- 속성: `CharacterName`(FString), `Health`(int32), `MoveSpeed`(float)
- 생성자에서 초기값(`Hero` / `100` / `600`) 설정
- `ModuleAndPluginCharacter::BeginPlay` 에서 `NewObject<UCharacterData>(this)` 로 생성 후 화면에 값 출력

---

## 빌드 & 실행

1. `ModuleAndPlugin.uproject` 우클릭 → **Generate Visual Studio project files**
2. 솔루션을 `Development Editor | Win64` 로 빌드
3. 에디터 실행 후 **Play**
   - 초록색: `Hello from Test Module! (TestActor Spawned)`
   - 청록색: `[CharacterData] Name: Hero | HP: 100 | Speed: 600`
   - Output Log: `>>> Temporary Plugin Started!`

> 새 `UCLASS` / 모듈을 추가한 뒤에는 Live Coding 대신 **에디터 종료 후 전체 빌드**를 권장합니다.
