#include "stdafx.h"
#include "WeiboTestCaseHelper.h"

#include <IWeiboDef.hxx>
#include <IWeiboMethod.hxx>

#include "ParsingDefine.hxx"
#include "ParsingDataStruct.hxx"

#define LOG_SUPPORT

using namespace weibo;

#ifdef LOG_SUPPORT
#	define DEFAULT_SUBSYSTEM "WeiboSDK_UnitTest"
#	include <util/log/Logger.hxx>
#else
#	define CerrLog(args_) std::cout
#	define StackLog(args_) std::cout
#	define DebugLog(args_) std::cout
#	define InfoLog(args_) std::cout
#	define WarningLog(args_) std::cout
#	define ErrLog(args_) std::cout
#	define CritLog(args_) std::cout
#endif


struct IDDebugHelper
{
	unsigned int optionId;
	char *optionIdName;
};

#define HELPER_UNIT(option) { option, #option }

const IDDebugHelper gDebugHelperArray[] = 
{
	HELPER_UNIT(WBOPT_OAUTH2_ACCESS_TOKEN),

	HELPER_UNIT(WBOPT_GET_STATUSES_PUBLIC_TIMELINE),//��ȡ���¸��µĹ���΢����Ϣ 
	HELPER_UNIT(WBOPT_GET_STATUSES_FRIENDS_TIMELINE),//��ȡ��ǰ�û�����ע�û�������΢����Ϣ (����: statuses/home_timeline) 
	HELPER_UNIT(WBOPT_GET_STATUSES_HOME_TIMELINE),//��ȡ��ǰ��¼�û���������ע�û�������΢����Ϣ
	HELPER_UNIT(WBOPT_GET_STATUSES_USER_TIMELINE),//��ȡ�û�������΢����Ϣ�б� 
	HELPER_UNIT(WBOPT_GET_STATUSES_TIMELINE_BATCH),//�������ָ����ĳһ���û���timeline
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_TIMELINE),//����һ��΢��������n��ת��΢����Ϣ
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_BYME),//�����û�ת��������n��΢����Ϣ
	HELPER_UNIT(WBOPT_GET_STATUSES_MENTIONS),//��ȡ@��ǰ�û���΢���б� 
	HELPER_UNIT(WBOPT_GET_STATUSES_SHOW),//����ID��ȡ����΢����Ϣ
	HELPER_UNIT(WBOPT_GET_STATUSES_SHOW_BATCH),//������ȡ΢����Ϣ
	HELPER_UNIT(WBOPT_GET_STATUSES_QUERYMID),//ͨ��id��ȡmid
	HELPER_UNIT(WBOPT_GET_STATUSES_QUERYID),//ͨ��mid��ȡid
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_DAILY),//���췵������ת����
	HELPER_UNIT(WBOPT_GET_STATUSES_REPOST_WEEKLY),//���ܷ�������ת����
	HELPER_UNIT(WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY),//���췵���������۰�
	HELPER_UNIT(WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY),//���ܷ����������۰�
	HELPER_UNIT(WBOPT_POST_STATUSES_REPOST),//ת��һ��΢����Ϣ
	HELPER_UNIT(WBOPT_POST_STATUSES_DESTROY),//ɾ��΢��������Ϣ
	HELPER_UNIT(WBOPT_POST_STATUSES_UPDATE),//����һ��΢����Ϣ
	HELPER_UNIT(WBOPT_POST_STATUSES_UPLOAD_URL_TEXT),//����һ��΢����ͬʱָ���ϴ���ͼƬ��ͼƬurl
	HELPER_UNIT(WBOPT_POST_STATUSES_UPLOAD),//����һ��΢�����ϴ�ͼƬ������һ��΢����Ϣ

	HELPER_UNIT(WBOPT_GET_COMMENTS_SHOW),//��ȡĳ��΢���������б�
	HELPER_UNIT(WBOPT_GET_COMMENTS_BYME),//�ҷ����������б�
	HELPER_UNIT(WBOPT_GET_COMMENTS_TOME),//���յ��������б�
	HELPER_UNIT(WBOPT_GET_COMMENTS_TIMELINE),//��ȡ��ǰ�û����ͼ��յ��������б�
	HELPER_UNIT(WBOPT_GET_COMMENTS_MENTIONS),//@���ҵ�����
	HELPER_UNIT(WBOPT_GET_COMMENTS_SHOWBATCH),//@������ȡ��������

	HELPER_UNIT(WBOPT_POST_COMMENTS_CREATE),//����һ��΢��
	HELPER_UNIT(WBOPT_POST_COMMENTS_DESTROY),//ɾ��һ������
	HELPER_UNIT(WBOPT_POST_COMMENTS_DESTROY_BATCH ),//����ɾ������
	HELPER_UNIT(WBOPT_POST_COMMENTS_REPLY),//�ظ�һ������

	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES),//��ȡ��ǰ�û�����˽���б�
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_SENT),//��ȡ��ǰ�û����͵�����˽���б�
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_USER_LIST),//��ȡ˽�������û��б�
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_CONVERSATION),//��ȡ��ָ���û�������˽���б�
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH),//������ȡ˽������
	HELPER_UNIT(WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE),//�ж��Ƿ���Ը��Է���˽��
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_NEW),//����һ��˽��
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_DESTORY),//ɾ��һ��˽��
	HELPER_UNIT(WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH),//����ɾ��˽��

	HELPER_UNIT(WBOPT_GET_USERS_SHOW),//��ȡ�û�����
	HELPER_UNIT(WBOPT_GET_USERS_DOMAIN_SHOW),//ͨ������������ȡ�û���Ϣ
	HELPER_UNIT(WBOPT_GET_USERS_SHOW_BATCH),//������ȡ�û���Ϣ

	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_BASIC), //��ȡ�û�������Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION), //��ȡ������Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH), //������ȡ������Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_CAREER), //��ȡְҵ��Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH), //������ȡְҵ��Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_GET_PRIVACY), //��ȡ��˽������Ϣ
	HELPER_UNIT(WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST), //��ȡ����ѧУ�б�
	HELPER_UNIT(WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS), //��ȡ��ǰ�û�API����Ƶ������
	HELPER_UNIT(WBOPT_GET_ACCOUNT_GET_UID), //OAuth��Ȩ֮���ȡ�û�UID�������൱�ھɰ�ӿڵ�account/verify_credentials��
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE), // �����û�������Ϣ
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE), // �����û�������Ϣ
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY), // ɾ���û�������Ϣ
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE), // �����û�ְҵ��Ϣ
	HELPER_UNIT(WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY), // ɾ���û�ְҵ��Ϣ
	HELPER_UNIT(WBOPT_POST_ACCOUNT_AVATAR_UPLOAD), // �ϴ�ͷ��
	HELPER_UNIT(WBOPT_POST_ACCOUNT_UPDATE_PRIVACY), // ������˽����

	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS),//��ȡ�û��Ĺ�ע�б�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_IN_COMMON),//��ȡ��ͬ��ע���б��ӿ�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_BILATERAL),//��ȡ˫���ע�б�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS),//��ȡ˫���עID�б�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS),//��ȡ�û���ע����uid�б�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH),//������ȡ��ע
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS),//��ȡ�û���˿�б���ÿ����˿������һ��΢��
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS),//��ȡ�û���˿����uid�б�
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE),//��ȡ�û����ʷ�˿�б���ϵ��
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS),//��ȡ�ҵĹ�ע���й�ע��ָ���û��ķ���
	HELPER_UNIT(WBOPT_GET_FRIENDSHIPS_SHOW),//��ȡ�����û���ϵ����ϸ���
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_CREATE),//��עĳ�û�
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_CREATE_BATCH),//������ע�û�
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_DESTROY),//ȡ����עĳ�û�	
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY),//�Ƴ���˿
	HELPER_UNIT(WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE),//���¹�ע�˱�ע

	HELPER_UNIT(WBOPT_GET_FAVORITES),//��ȡ��ǰ��¼�û����ղ��б�
	HELPER_UNIT(WBOPT_GET_FAVORITES_SHOW),//��ȡ�����ղ���Ϣ
	HELPER_UNIT(WBOPT_GET_FAVORITES_BY_TAGS),//��ȡ��ǰ�û�ĳ����ǩ�µ��ղ��б�
	HELPER_UNIT(WBOPT_GET_FAVORITES_TAGS),//��ǰ��¼�û����ղر�ǩ�б�
	HELPER_UNIT(WBOPT_POST_FAVORITES_CREATE),//�����ղ�
	HELPER_UNIT(WBOPT_POST_FAVORITES_DESTROY),//ɾ���ղ�
	HELPER_UNIT(WBOPT_POST_FAVORITES_DESTROY_BATCH),//����ɾ���ղ�
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_UPDATE),//�����ղر�ǩ
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH),//���µ�ǰ�û������ղ��µ�ָ����ǩ
	HELPER_UNIT(WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH),//ɾ����ǰ�û������ղ��µ�ָ����ǩ

	HELPER_UNIT(WBOPT_GET_TRENDS),//��ȡĳ�˻���
	HELPER_UNIT(WBOPT_GET_TRENDS_STATUSES),//��ȡĳһ�����µ�΢��
	HELPER_UNIT(WBOPT_GET_TRENDS_HOURLY),//�������һСʱ�ڵ����Ż���
	HELPER_UNIT(WBOPT_GET_TRENDS_DAILY),//�������һ���ڵ����Ż���
	HELPER_UNIT(WBOPT_GET_TRENDS_WEEKLY),//�������һ���ڵ����Ż���
	HELPER_UNIT(WBOPT_POST_TRENDS_FOLLOW),//��עĳ����
	HELPER_UNIT(WBOPT_POST_TRENDS_DESTROY),//ȡ����ע��ĳһ������

	HELPER_UNIT(WBOPT_GET_TAGS),//����ָ���û��ı�ǩ�б�
	HELPER_UNIT(WBOPT_GET_TAGS_TAGS_BATCH),//������ȡ�û���ǩ
	HELPER_UNIT(WBOPT_GET_TAGS_SUGGESTIONS),//����ϵͳ�Ƽ��ı�ǩ�б�
	HELPER_UNIT(WBOPT_POST_TAGS_CREATE),//�����û���ǩ
	HELPER_UNIT(WBOPT_POST_TAGS_DESTROY),//ɾ���û���ǩ
	HELPER_UNIT(WBOPT_POST_TAGS_DESTROY_BATCH),//����ɾ���û���ǩ

	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_USERS),//���û���������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES),//��΢����������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS),//��ѧУ��������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES), //�ѹ�˾��������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_APPS),//��Ӧ����������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS), //@��������
	HELPER_UNIT(WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE),  //�ۺ���������
	HELPER_UNIT(WBOPT_GET_SEARCH_STATUSES),//΢������ 
	HELPER_UNIT(WBOPT_GET_SEARCH_GEO_STATUSES), //����ָ����Χ�ڵ�΢��
	HELPER_UNIT(WBOPT_GET_SEARCH_USERS),//�����û�

	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_FAVORITES_HOT),//�����ղ�
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_HOT),//��ȡϵͳ�Ƽ��û�
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED),//��ȡ�û����ܸ���Ȥ����
	HELPER_UNIT(WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED),//������Ȥ����
	HELPER_UNIT(WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS),//����΢�������Ƽ��û�

	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHORTEN), //��һ������������ת���ɶ�����
	HELPER_UNIT(WBOPT_GET_SHORT_URL_EXPAND), //��һ�����������ӻ�ԭ��ԭʼ�ĳ�����
	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHARE_COUNTS), //ȡ��һ����������΢���ϵ�΢��������������ԭ����ת����΢����
	HELPER_UNIT(WBOPT_GET_SHORT_URL_SHARE_STATUSES), //ȡ�ð���ָ�����������ӵ�����΢������
	HELPER_UNIT(WBOPT_GET_SHORT_URL_COMMENT_COUNTS), //ȡ��һ����������΢���ϵ�΢��������
	HELPER_UNIT(WBOPT_GET_SHORT_URL_COMMENT_COMMENTS), //ȡ�ð���ָ�����������ӵ�����΢����������
};

const char* getOptionName(unsigned int optionId)
{
	for (int i = 0; i < sizeof(gDebugHelperArray)/sizeof(gDebugHelperArray[0]); ++ i) 
	{
		if (optionId == gDebugHelperArray[i].optionId)
		{
			return gDebugHelperArray[i].optionIdName;
		}
	}
	static char buf[10] = { 0 };
	memset(buf, sizeof(char), 10);
	itoa(optionId, buf, 10);
	return buf;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 

WeiboTestCaseResult::WeiboTestCaseResult()
: resultType_(ERT_UNKNOW)
, errorCode_(0)
, subErrorCode_(0)
{
}

WeiboTestCaseResult::~WeiboTestCaseResult()
{
}

std::string WeiboTestCaseResult::outputString()
{
	std::string outString;

	return outString;
}

//////////////////////////////////////////////////////////////////////////////
// Case helper

WeiboTestCaseHelper::WeiboTestCaseHelper()
{
	mWeiboPtr = weibo::WeiboFactory::getWeibo();

	mWeiboPtr->startup();
	mWeiboPtr->setOption(weibo::WOPT_CONSUMER, "1016351065", "186ea22b3ea58bfa90923f55fe8b2749");
	mWeiboPtr->OnDelegateComplated += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespComplated);
	mWeiboPtr->OnDelegateErrored += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespErrored);
	mWeiboPtr->OnDelegateWillRelease += std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespStoped);

	initializeParsingMap();

#if defined(LOG_SUPPORT)
	std::wstring logfile = getAppModulePathW();
	logfile += L"UNIT_LOG.log";
	Util::Log::initialize(Util::Log::File | Util::Log::VSDebugWindow, 
		Util::Log::Debug, "WeiboSDK_UnitTest", logfile.c_str());
#endif //LOG_SUPPORT
}

WeiboTestCaseHelper::~WeiboTestCaseHelper()
{
	mResultMap.clear();

	mWeiboPtr->OnDelegateComplated -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespComplated);
	mWeiboPtr->OnDelegateErrored -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespErrored);
	mWeiboPtr->OnDelegateWillRelease -= std::make_pair(this, &WeiboTestCaseHelper::onWeiboRespStoped);
	mWeiboPtr->shutdown();
}

weibo::IWeiboMethod* WeiboTestCaseHelper::getWeiboMethod()
{
	if (mWeiboPtr)
	{
		return mWeiboPtr->getMethod();
	}
	return NULL;
}

WeiboTestCaseResultPtr WeiboTestCaseHelper::checkoutReqResult(unsigned int optionId)
{
	WeiboTestCaseResultPtr result;
	UnitTestResultMAP::iterator it = mResultMap.find(optionId);
	if (it != mResultMap.end())
	{
		result = it->second;
	}
	return result;
}

const char* WeiboTestCaseHelper::getMYID()
{
	return mMYID.c_str();
}

void WeiboTestCaseHelper::onWeiboRespComplated(unsigned int optionId, const char* httpHeader, ParsingObject* result, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId));

	onResponseProcess(optionId, result, 0, 0, true);
}

void WeiboTestCaseHelper::onWeiboRespErrored(unsigned int optionId, const int errCode, const int errSubCode, ParsingObject* result, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId) << " | error code: "  << errCode << " | sub error Code: " << errSubCode);

	onResponseProcess(optionId, result, errCode, errSubCode, false);
}

void WeiboTestCaseHelper::onWeiboRespStoped(unsigned int optionId, const weibo::UserTaskInfo* pTask)
{
	DebugLog(<< __FUNCTION__ << "| Option Id: " << getOptionName(optionId));

	// Do noting!
}

using namespace weibo;

#define INSERT_PARSING_OBJECT(id, object)\
	mParsingMap.insert(std::make_pair(id, object))

#define INSERT_PARSING_OBJECT_BATCH(idbegin, idend, object)\
	for (int i = idbegin; i <= idend; ++ i){ mParsingMap.insert(std::make_pair(i, object)); }

void WeiboTestCaseHelper::initializeParsingMap()
{
	// Parsing for statuses
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_PUBLIC_TIMELINE,
		WBOPT_GET_STATUSES_TIMELINE_BATCH, boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_REPOST_TIMELINE,
		WBOPT_GET_STATUSES_REPOST_BYME, boost::make_shared<ParsingStatusesList>("reposts"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_MENTIONS,
		boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_SHOW,
		boost::make_shared<ParsingStatus>());

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_SHOW_BATCH, 
		boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_QUERYMID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "mid")));

	INSERT_PARSING_OBJECT (WBOPT_GET_STATUSES_QUERYID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "id")));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_STATUSES_REPOST_DAILY,
		WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY, boost::make_shared<ParsingStatusesList>("statuses"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_STATUSES_REPOST,
		WBOPT_POST_STATUSES_UPLOAD, boost::make_shared<ParsingStatus>());

	// Parsing for comment
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_COMMENTS_SHOW,
		WBOPT_GET_COMMENTS_SHOWBATCH, boost::make_shared<ParsingCommentsList>("comments"));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_COMMENTS_CREATE,
		WBOPT_POST_COMMENTS_REPLY, boost::make_shared<ParsingComment>());

	// Parsing for direct messages
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_DIRECTMESSAGES,
		WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH, boost::make_shared<ParsingDirectMessagesList>("direct_messages"));

	INSERT_PARSING_OBJECT (WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "result")));

	INSERT_PARSING_OBJECT_BATCH (WBOPT_POST_DIRECTMESSAGES_NEW,
		WBOPT_POST_DIRECTMESSAGES_DESTORY, boost::make_shared<ParsingDirectMessage>());

	INSERT_PARSING_OBJECT (WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH,
		boost::make_shared<ParsingDirectMessagesList>("direct_messages"));

	// Parsing for friendships
	INSERT_PARSING_OBJECT_BATCH (WBOPT_GET_FRIENDSHIPS_FRIENDS, 
		WBOPT_GET_FRIENDSHIPS_BILATERAL, boost::make_shared<ParsingUsersList>("users"));

	INSERT_PARSING_OBJECT (WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS, 
		boost::make_shared<ParsingUsersList>("users"));

	// Parsing for Accounts
	INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_BASIC,
		boost::make_shared<ParsingAccount>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION,
	//	boost::make_shared<ParsingEducation>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH,
	//	boost::make_shared<ParsingEducationsList>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH,
	//	boost::make_shared<ParsingEducationsList>());

	//INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_GET_UID,
	//	boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "uid")));

	// Parsing for favorites
	INSERT_PARSING_OBJECT (WBOPT_GET_FAVORITES, 
		boost::make_shared<ParsingFavoritesList>("favorites"));

	INSERT_PARSING_OBJECT (WBOPT_GET_FAVORITES_TAGS, 
		boost::make_shared<ParsingFavoriteTagsList>("tags"));

	INSERT_PARSING_OBJECT (WBOPT_GET_TAGS, 
		boost::make_shared<ParsingTagsList>());

	INSERT_PARSING_OBJECT (WBOPT_GET_TRENDS,
		boost::make_shared<ParsingTrendsList>());


	// parsing for id
	INSERT_PARSING_OBJECT (WBOPT_GET_ACCOUNT_GET_UID,
		boost::make_shared<ParsingResult>(ParsingResult::ResultKeyList(1, "uid")));
}

void WeiboTestCaseHelper::onResponseProcess(unsigned int optionId, ParsingObject* resultObj, const int errCode, const int errSubCode, bool isComplated)
{
	UnitTestResultMAP::iterator it = mResultMap.find(optionId);
	if (it != mResultMap.end())
	{
		mResultMap.erase(it);
	}

	WeiboTestCaseResultPtr result = boost::make_shared<WeiboTestCaseResult>();
	//result->respBody_ = sc;
	result->errorCode_ = errCode;
	result->subErrorCode_ = errSubCode;
	result->resultType_ = isComplated ? WeiboTestCaseResult::ERT_CORRECT : WeiboTestCaseResult::ERT_ERROR;
	mResultMap.insert(std::make_pair(optionId, result));

	if (isComplated)
	{
		UnitTestParsingMAP::iterator it = mParsingMap.find(optionId);
		if (it != mParsingMap.end())
		{
			result->pasringPtr_ = it->second;
		}
		else
		{
			WarningLog(<< __FUNCTION__ << "| Warning: cannot find parsing object! Option id:" << optionId);
		}
	}
	else
	{
		result->pasringPtr_ = boost::make_shared<ParsingApiError>(false);
	}

	if (resultObj)
	{
		ParsingObject* tempObject = new ParsingObject(*resultObj);
		ParsingObjectPtr objPtr(tempObject);

		if (result->pasringPtr_ )
		{
			result->pasringPtr_->doParse(objPtr);
		}

		// The special event.
		switch(optionId)
		{
		case WBOPT_OAUTH2_ACCESS_TOKEN:
			{
				ParsingOauthRet ret;
				ret.doParse(objPtr);
				mWeiboPtr->setOption(WOPT_ACCESS_TOKEN, ret.access_token.c_str());
			}
			break;

		case WBOPT_GET_ACCOUNT_GET_UID:
			{
				ParsingResultPtr pret = boost::dynamic_pointer_cast<ParsingResult>(result->pasringPtr_);
				if (pret)
				{
					mMYID = pret->asAString("uid");
				}
			}
			break;

		default:
			break;
		}
	}
}

std::string filePath;
std::wstring filePathW;

const char* WeiboTestCaseHelper::getAppModulePath()
{
	if (filePath.empty())
	{
		char buf[MAX_PATH]={ 0 };
		GetModuleFileNameA(NULL, buf, sizeof(char) * MAX_PATH);
		char* tmp = strrchr(buf, '\\');
		*tmp = '\0';
		filePath = buf;
		filePath += "\\";
	}
	return filePath.c_str();
}

const wchar_t* WeiboTestCaseHelper::getAppModulePathW()
{
	if (filePathW.empty())
	{
		wchar_t buf[MAX_PATH]={ 0 };
		GetModuleFileNameW(NULL, buf, sizeof(wchar_t) * MAX_PATH);
		wchar_t* tmp = wcsrchr (buf, '\\');
		*tmp = '\0';
		filePathW = buf;
		filePathW += L"\\";
	}
	return filePathW.c_str();
}