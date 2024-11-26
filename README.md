## LostArk
언리얼 엔진으로 개발한 Lost Ark 카오스던전 모작

개발 기간 9주

[🎥 시연 영상 보기](https://youtu.be/AyR7zcpjJns)

---
### 목차
[1. 로딩](#1-로딩)  
[2. 데미지 시스템](#2-데미지-시스템)  
[3. 미니맵](#3-미니맵)  
[4. 몬스터 체력바](#4-몬스터-체력바)  
[5. 보스](#5-보스)  
[6. 핵](#6-핵)  
[7. 진행도](#7-진행도)  

---

### 1. 로딩

레벨을 Lighting, StaticMesh, Spawner와 같이 액터들을 구분하여 서브 레벨로 구성하여 UGameplayStatics::LoadStreamLevel을 통해 로딩을 구현

### 레벨구성
    
  <img src="https://github.com/user-attachments/assets/d1d1169a-33cd-40ba-9347-2628e833abb3"  width="400" height="200"/>

  레벨을 Lighting, StaticMesh, Spawner 등으로 나눠 서브레벨로 구성
    
### 코드흐름
    
   <img src="https://github.com/user-attachments/assets/b6ba92a7-fc08-4929-b394-943b8c3b05e4"  width="600" height="400"/>
    
  - GameMode에서 StartLoadingCheck() 함수에서 0.6초 간격으로 CheckLoadingComplete()를 실행
 - CheckLoadingComplete()에서 로딩이 완료되지 않으면 Loopback()을 호출
 - 서브레벨마다 Loading() 함수로 LoadStreamLevel을 실행
 - 모든 로딩이 완료되면 타이머를 제거하고 로딩 위젯 삭제
    

### 2. 데미지 시스템

플레이어의 CritRate로 치명타인지의 여부를 판단하고, 색상으로 출력
- 치명타 : 노란색
- 일반 공격 : 흰색
- 피격 시 : 빨간색


### 몬스터 공격 과정
        
  <img src="https://github.com/user-attachments/assets/f3b1798c-782b-49ba-b7eb-a3e33c2e2f2d"  width="600" height="400"/>
        
 - 행동트리에 따라 가장 가까운 플레이어를 탐색
 - GA_Attack으로 공격 시도 -> Overlap 이벤트 발생 시 데미지 계산
 - 데미지 계산 : MonsterATK, MonsterMaxATK, Player의 Block 값 기반
  
### 플레이어 공격과정
   <img src="https://github.com/user-attachments/assets/d0f54f56-c127-4205-af97-e3574d3c2ccd"  width="600" height="400"/>
        
 - 공격 키 입력 시  GA_Attack이 실행 -> 무기 장착 여부 확인
 - 공격 중 Overlap 이벤트 발생 -> 치명타 시 2배 데미지 적용
 - 데미지 계산 : ATK, MaxATK, Monster의 DEF 값 기반
        
### 3. 미니맵

- 축적 계산 : 텍스처와 레벨의 크기를 활용해 플레이어, 몬스터, 포탈 위치를 표시
- 몬스터의 사망 시 미니맵 아이콘 삭제

### 코드 흐름
    
  <img src="https://github.com/user-attachments/assets/f7e40411-6d0c-44a4-8eca-032e33e3ffa2"  width="600" height="400"/>
    
  - 월드 좌표 -> 2D 변환
  - 위치를 축적에 맞춰 계산 후 미니맵 위젯에 출력


### 4. 몬스터 체력바

플레이어의 마우스가 몬스터에 오버되면 타입별 체력바 표시

### 코드 흐름
    
  <img src="https://github.com/user-attachments/assets/d169ce49-5f84-4bfb-902a-4f3636d29f67"  width="600" height="400"/>
    
  - PlayerController의 CheckMouseOver()에서 마우스 월드 좌표를 계산
  - 라인트레이스로 몬스터를 탐지 -> 몬스터의 타입(Common, Named)에 따라 체력바 표시
    

### 5. 보스

FireAttack 나이아가라의 파티클에 충돌 검출 대신 라인트레이스를 통해 충돌 검출 후 데미지 처리

### 행동트리
    
   <img src="https://github.com/user-attachments/assets/a7e92b4c-1c2a-4049-95c7-1eaf0c3293f2"  width="600" height="400"/>
    
   - 가장 가까운 플레이어 탐색 -> 적정 거리로 이동
   - BossAttack(FireAttack)  실행(쿨타임 여부 확인)
   - 근접공격은 쿨타임 중 실행
    
### 코드흐름
    
  <img src="https://github.com/user-attachments/assets/dce47499-fa4a-4aac-87f4-6822036c6056"  width="600" height="400"/>
    
  - BTTask_BossAttack : GA_BossFire로 공격 실행
  - GC_BossFire : 나이아가라 파티클 발사 후 라인트레이스로 충돌 검출
  - Overlap 이벤트:
    - 충돌 시 데미지 계산 : Boss의 Skill Damage와 Player의 Block 값 기반
    

### 6. 핵

무기와 3번 충돌 시 핵이 파괴되어 몬스터 소환 

### 코드흐름
    
  <img src="https://github.com/user-attachments/assets/0011a2ef-af5f-4081-a3d4-ce4f6d8d2d5f"  width="600" height="400"/>
    
  - 핵과 칼이 Overlap 이벤트 발생 : 
    - 히트 횟수에 따라 'Component' 표시 및 소리 재생
    - 이전 'Component' 삭제
  - 3타 완료 시 : 몬스터 소환

### 7. 진행도

몬스터의 사망 시 Delegate를 통해 진행도 증가

특정 진행도에 따라 이벤트 발생 :
- 0.18 ≤ Progress Value && Stage1  : 포탈 소환
- 0.45 ≤ Progress Value ≤ 0.50 : 보스 소환 후 사망 시 포탈 소환
- Progress Value ≥ 1.0 : 클리어

### 코드흐름
    
  <img src="https://github.com/user-attachments/assets/e05cff26-c74c-470c-b1ea-da94d6f34dfb"  width="600" height="400"/>
    
  Monster 사망 시 타입에 따라 진행도가 증가
  Common : 0.018, Named : 0.05, Boss : 0.1  
  
    
  <img src="https://github.com/user-attachments/assets/6895efd2-f603-4895-9140-c37fc0b5a6ba"  width="600" height="400"/>
    
특정 진행도에 따라 이벤트 발생 :
- 0.18 ≤ Progress Value && Stage1  : 포탈 소환
- 0.45 ≤ Progress Value ≤ 0.50 : 보스 소환 후 사망 시 포탈 소환
- Progress Value ≥ 1.0 : 클리어
    
---

--- 사용 기술 ---

언어 :: C++

플랫폼 :: Windows

게임 엔진 :: Unreal Engine 5.4.4
