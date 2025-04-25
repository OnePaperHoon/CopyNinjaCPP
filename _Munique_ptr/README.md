# 🧠 _Munique_ptr — C++ 스마트 포인터 직접 구현

> C++ 표준 라이브러리의 `std::unique_ptr`와 유사한 기능을 제공하는 스마트 포인터 구현

---

## 📌 개요

C++에서 메모리 관리는 항상 중요한 주제입니다.
개발자가 new로 메모리를 할당한 뒤 delete로 직접 해제하지 않으면, 프로그램은 메모리 누수(memory leak)를 일으키게 됩니다.

이러한 문제를 해결하기 위한 핵심 개념이 바로 RAII (Resource Acquisition Is Initialization) 입니다.

이 프로젝트는 RAII 개념을 바탕으로 unique_ptr을 직접 구현해보며 메모리 자원을 안전하게 다루는 방법을 학습하기 위한 것입니다.

---

## 📜 RAII라는 것은?

> **Resource Acquisition Is Initialization**
"자원의 획득을 객체의 초기화와 동시에 한다"

### ✅ 해당 아이디어

- **자원**(메모리, 파일, 랩 등)은 객체가 생성되면서 획득하고, 객체가 **소멸될 때 자동으로 해제**한다.
- 이렇게 하면 예외가 발생해도 자원 누수를 막을 수 있다.

### 📦 예시

```cpp
{
    _Munique_ptr<int> ptr(new int(42));
} // ptr이 스코프를 버시면서 자동으로 delete 호출됨
```

이처럼 `RAII`를 활용하면 `try-catch` 없이도 자원 정리가 **안전하고 예측 가능**하게 이루어집니다.

---

## ❓ 왜 직접 unique_ptr을 구현했을까?

- 스마트 포인터의 **핵심 원리인 소유권 관리**, **복사 금지**, **이동 가능성**, **RAII 기반 자동 소멸**을 직접 구현하며 정확히 이해할 수 있습니다.
- `std::unique_ptr`는 너무 편리하지만, 내부는 **마법 처럼 보일 수 있으므로** 직접 구현해보면 구조와 동작을 더 깊이 이해할 수 있습니다.

---

## ⚙️ 구현한 기능들

| 기능                     | 설명 |
|--------------------------|------|
| RAII 기반 자원 해제       | 객체 소멸 시 자동으로 delete 호출 |
| 복사 금지                | 복사 생성자/할당자 삭제 |
| 이동 지원                | 이동 생성자/이동 할당자를 통해 소유권 이동 가능 |
| 커스텀 deleter 지원       | `std::function`, 구조체 등 사용자 정의 deleter 사용 가능 |
| `get()`, `reset()`, `release()` | 기본 포인터 제어 기능 |
| `swap()`                 | 두 스마트 포인터 간 포인터/deleter 교환 |
| `get_deleter()`          | 내부 deleter 객체를 참조로 반환 |

---

## 🚪 사용 예시

```cpp
#include "_Munique_ptr.hpp"

int main() {
    _Munique_ptr<int> ptr(new int(42));
    std::cout << *ptr << std::endl; // 42

    _Munique_ptr<int> moved = std::move(ptr);
    if (!ptr.get()) std::cout << "ptr is now null\n";

    moved.reset(new int(10)); // 기존 메모리 해제 후 새로 할당
}
```

### 🔄 커스텀 deleter 사용 예시

```cpp
struct FreeDeleter {
    void operator()(int* p) const {
        std::cout << "custom delete\n";
        free(p);
    }
};

_Munique_ptr<int, FreeDeleter> ptr((int*)malloc(sizeof(int)), FreeDeleter{});
```

---

## 🛠️ 사용 환경

- C++17 이상
- clang++, g++, MSVC 등 대부분의 컴파일러에서 동작 가능
- 템플릿 클래스이므로 헤더파일에서 정의포함

---

## 🧰 어느 곳에 쓰여지는가?

- 일반적인 동적 메모리 관리 (`new`)
- 예외 안전성이 중요한 코드
- 리소스 해제를 명확히 하기 어려운 복잡한 로직
- C API와의 연동 (`FILE*`, `malloc/free` 등)에서 카스터 deleter와 함께 사용

---

## 📚 참고 자료

- [cppreference - std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [Scott Meyers - Effective Modern C++](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/)
- [Herb Sutter - RAII, Smart Pointers, and Exception Safety](https://herbsutter.com/)

---

## 🔖 마치며

스마트 포인터를 직접 구현하며 C++의 자원 관리 원리를 더 깊이 이해할 수 있었습니다.
이 프로젝트는 RAII, 이동 시멘틱, 템플릿, 컷스텀 함수 객체 등 현대 C++의 다양한 개념을 통합적으로 연습하기 위한 좋은 기반이 되었습니다.


