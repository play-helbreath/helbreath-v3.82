// Quest.h: interface for the CQuest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
#define AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>


#define DEF_QUESTTYPE_MONSTERHUNT				1		// 일반적인 몬스터 헌팅 
#define DEF_QUESTTYPE_MONSTERHUNT_TIMELIMIT		2		// 시간 제한이 걸려있는 몬스터 헌팅 
#define DEF_QUESTTYPE_ASSASSINATION 			3		// 암살 
#define DEF_QUESTTYPE_DELIVERY					4		// 배달: 특정 장소로 아이템을 배달한다.
#define DEF_QUESTTYPE_ESCORT					5		// 보호: 특정 캐릭터를 보호한다.
#define DEF_QUESTTYPE_GUARD						6		// 특정 지역을 적의 공격으로부터 방어한다. 
#define DEF_QUESTTYPE_GOPLACE					7		// 특정 장소로 간다. 적국 침투 
#define DEF_QUESTTYPE_BUILDSTRUCTURE			8		// 구조물 설치 임무
#define DEF_QUESTTYPE_SUPPLYBUILDSTRUCTURE		9		// 구조물 설치 보급 임무
#define DEF_QUESTTYPE_STRATEGICSTRIKE			10		// 전술적 폭격임무 
#define DEF_QUESTTYPE_SENDTOBATTLE				11		// 곧바로 교전장소 참가하는 임무
#define DEF_QUESTTYPE_SETOCCUPYFLAG				12		// 영토 점령 깃발을 설치하는 임무 

class CQuest  
{
public:
	
	char m_cSide;				// 0: Neutral, 1:Ares, 2:Elvine, 4:Executor
	
	int m_iType;				// Quest 종류 
	int m_iTargetType;			// Quest의 목표 종류. 각 Type에 따라 다른 값이 정해진다. 
	int m_iMaxCount;			// 최대 만족 횟수 

	int m_iFrom;				// Quest를 내려주는 NPC 종류 
	
	int m_iMinLevel;			// Quest를 받기 위한 최저 레벨. 
	int m_iMaxLevel;			// Quest를 받기 위한 최대 레벨 

	int m_iRequiredSkillNum;	// 조건 판단에 필요한 스킬 번호 
	int m_iRequiredSkillLevel;	// 조건 판단에 필요한 스킬 레벨 

	int m_iTimeLimit; 			// 시간 제한 잔존량 
	int m_iAssignType;			// 퀘스트 할당 타입. -1이면 아무때나. 1이면 Crusade 전면전일때만.

								// 상품 종류 및 수량. 3개 중 1개가 랜덤하게 정해짐. 0번 인덱스는 사용 안함.
	int m_iRewardType[4]; 
	int m_iRewardAmount[4];

	int m_iContribution;		// 공헌도 
	int m_iContributionLimit;	// 최대 공헌도 제한 

	int m_iResponseMode;		// 응답 모드: 0(ok) 1(Accept/Decline) 2(Next)

	char m_cTargetName[21];		// 퀘스트가 지정된 이름. 맵 혹은 캐릭터 이름  
	int  m_sX, m_sY, m_iRange;	// 퀘스트가 지정된 맵 장소 

	int  m_iQuestID;			// 퀘스트 ID. 만약 퀘스트의 내용이 변경되었을 경우를 대비한 것임.

	int  m_iReqContribution;	// 퀘스트를 맡기 위한 최저 공헌도 제한. 


	//CQuest();
	//virtual ~CQuest();

};

#endif // !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
