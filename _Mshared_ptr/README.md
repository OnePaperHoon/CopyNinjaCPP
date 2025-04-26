# 🧠 _Mshared_ptr — C++ 스마트 포인터 직접 구현

> C++ 표준 라이브러리의 `std::shared_ptr`와 유사한 기능을 제공하는 스마트 포인터 구현

---

## 📌 개요

C++에서 메모리 관리는 항상 중요한 주제입니다.
개발자가 new로 메모리를 할당한 뒤 delete로 직접 해제하지 않으면, 프로그램은 메모리 누수(memory leak)를 일으키게 됩니다.

특히 여러 곳에서 하나의 자원을 공유하려고 할 때 수동으로 카운트를 관리하는 것은 실수하기 쉽습니다.

이 문제를 해결하기 위한 핵심 개념이 바로 **참조 카운트(Reference Counting)** 입니다.
_Mshared_ptr은 이 개념을 바탕으로, 복수 포인터가 하나의 객체를 공유하고 관리하는 기능을 제공합니다.

---

## 📜 참조 카운팅이란?

> **Reference Counting**
"객체에 대한 참조 수를 관리하여 마지막 참조가 사라질 때 자동으로 자원을 해제하는 방법"

### ✅ 해당 아이디어

- **자원**(메모리, 파일 등)을 여러 포인터가 공유할 수 있다.
- 하나의 포인터가 복사될 때마다 참조 수를 증가시킨다.
- 포인터가 소멸될 때마다 참조 수를 감소시킨다.
- 참조 수가 0이 되면 자원을 해제한다.

### 📦 예시

```cpp
{
    _Mshared_ptr<int> p1(new int(42));
    {
        _Mshared_ptr<int> p2 = p1; // 참조 수 증가
    } // p2 소멸 → 참조 수 감소
} // p1 소멸 → 참조 수 0 → delete 호출
```
이처럼 Reference Counting을 활용하면 메모리 관리를 안전하고 예측 가능하게 할 수 있습니다.

## ❓ 왜 직접 shared_ptr을 구현했을까?

- 스마트 포인터의 **핵심 원리인 참조 수 관리**, **공유된 소유권**, **자동 메모리 해제**를 직접 구현하며 정확히 이해할 수 있습니다.
- `std::shared_ptr`는 너무 편리하지만, 내부 동작을 정확히 이해하면 포인터 안전성이나 메모리 최적화 측면에서 더 깊은 감을 얻을 수 있습니다.



## ⚙️ 구현한 기능들

| 기능                     | 설명 |
|--------------------------|------|
| 참조 수 기반 자원 해제    | 마지막 포인터 소멸 시 자동으로 delete 호출 |
| 복사 지원                | 복사 생성자/할당자로 참조 수 증가 |
| 이동 지원                | 이동 생성자/이동 할당자로 소유권 이동 가능 |
| `get()`                  | 내부 포인터를 반환 |
| `use_count()`             | 현재 참조 수를 반환 |
| `unique()`               | 참조 수가 1인지 확인 |
| `operator*`, `operator->` | 포인터처럼 객체에 접근 가능 |

---

## 🚪 사용 예시

```cpp
#include "_Mshared_ptr.hpp"
#include <iostream>

class Test {
public:
    Test() { std::cout << "Test 객체 생성\n"; }
    ~Test() { std::cout << "Test 객체 소멸\n"; }

    void hello() const {
        std::cout << "Hello from Test\n";
    }
};

int main() {
    {
        _Mshared_ptr<Test> sp1(new Test());
        std::cout << "sp1 use_count: " << sp1.use_count() << "\n";

        {
            _Mshared_ptr<Test> sp2 = sp1;
            std::cout << "sp2 use_count: " << sp2.use_count() << "\n";

            sp2->hello();
        } // sp2 소멸 → 참조 수 감소

        std::cout << "sp1 use_count after sp2 destroyed: " << sp1.use_count() << "\n";
    } // sp1 소멸 → 참조 수 0 → 객체 소멸
}
```
# 결과 예시
```
Test 객체 생성
sp1 use_count: 1
sp2 use_count: 2
Hello from Test
sp1 use_count after sp2 destroyed: 1
Test 객체 소멸
```

## 🛠️ 사용 환경

C++17 이상

clang++, g++, MSVC 등 대부분의 컴파일러에서 동작 가능

템플릿 클래스이므로 헤더파일에서 정의 포함
___

## 🧰 어느 곳에 쓰여지는가?
- 여러 곳에서 하나의 객체를 안전하게 공유할 때
- 복잡한 소유권 관계를 명시적으로 관리하기 어려운 코드
- 예외 발생 가능성이 높은 코드에서 메모리 누수 방지
- 리소스 수명 관리를 명확히 하고 싶을 때

## 📚 참고 자료

- [cppreference - std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [Scott Meyers - Effective Modern C++](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/)
- [Herb Sutter - Resource Management Techniques](https://herbsutter.com/)

---

## 🔖 마치며

스마트 포인터를 직접 구현하면서 참조 수 관리와 자원 해제 패턴을 깊이 이해할 수 있었습니다.
이 프로젝트는 소유권 관리, 메모리 안전성, 이동 시멘틱 등 현대 C++의 핵심 개념을 통합적으로 연습하기 위한 훌륭한 기반이 되었습니다.
